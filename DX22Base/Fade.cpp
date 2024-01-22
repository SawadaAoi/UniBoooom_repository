/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	フェード実装
	------------------------------------
	Fade.cpp
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/11/18 制作 takagi
	・2023/11/19 18の続き takagi
	・2023/11/20 整理 takagi
	・2023/11/21 更新・描画処理分割 takagi
	・2023/11/23 IsFade()関数追加・細かい書き換え takagi
	・2023/11/24 フェードの仕様変更対応 takagi
	・2023/11/27 疑似カメラ実装 takagi
	・2023/12/01 フェードの仕様変更 takagi 
	・2023/12/04 カメラのファイル改名適用 takagi
	・2023/12/17 フェード完了判定がずれ、最小・最大状態にならないことがある問題を修正・ブラックアウト対応 takagi
	・2024/01/16 フェードアウト・インにイージング適用 takagi

========================================== */

// =============== インクルード ===================
#include "Fade.h"		//自身のヘッダ
#include "CameraDef.h"	//疑似カメラ
#include <math.h>		//pow使用

#if _DEBUG
#include <Windows.h>	//メッセージボックス用
#endif

// =============== 定数・マクロ定義 =====================
const std::string VS_PASS("Assets/Shader/VsFade.cso");		//テクスチャのパス名
const std::string PS_PASS("Assets/Shader/PsFade.cso");		//テクスチャのパス名
const std::string TEX_PASS("Assets/Texture/Fade.png");		//テクスチャのパス名
const TPos3d<float> INIT_POS(640.0f, 360.0f, 0.0f);			//位置初期化
const TTriType<float> INIT_SCALE(4000.0f, 4000.0f, 0.0f);	//初期拡縮
const TTriType<float> INIT_RADIAN(0.0f);					//初期回転
const TTriType<int> FRAME_FADE_MAX(100, 60, 70);			//フェードにかけるフレーム数	x:アウト, y:ストップ, z:イン
const int FRAME_MIN(0);										//フェード時間の最小
const int FRAME_OUT_PATTERN_1_FIN(50);						//フェードアウト開始から拡縮が留まるまでのフレーム数
const int FRAME_OUT_PATTERN_2_FIN(80);						//フェードアウト開始から拡縮が留まり終わるまでのフレーム数
const float SCALE_OUT_MIN(500.0f);							//フェードアウト最小サイズ	uvの都合上、値が大きい程サイズが小さくなる
const float SCALE_IN_MIN(600.0f);							//フェードイン最小サイズ	uvの都合上、値が大きい程サイズが小さくなる
const float SCALE_OUT_STAY(10.0f);							//フェードアウト拡縮が一時収まるときのサイズ
const float SCALE_OUT_MAX(0.0f);							//フェード最大サイズ	uvの都合上、値が小さい程サイズが大きくなる
const float SCALE_IN_MAX(0.0f);								//フェード最大サイズ	uvの都合上、値が小さい程サイズが大きくなる
const float ROTATE_ACCEL_RATE(0.00025f);					//角速度増加割合
const double PI(3.14159265358979323846);					//円周率M_PIのコピー
#define ROTATE_EASE_IN_OUT(frame) (ROTATE_ACCEL_RATE * (0.5 ? 4 * pow((frame), 3.0)	\
	: 1 - pow(-2 * (frame) + 2, 3.0) / 2))					//フェードイン・アウト回転用のイーズ計算

// =============== グローバル変数宣言 =====================
int CFade::ms_nCntFade;							//自身の生成数
VertexShader* CFade::ms_pVs = nullptr;			//頂点シェーダー
PixelShader* CFade::ms_pPs = nullptr;			//ピクセルシェーダー
Texture* CFade::ms_pTexture = nullptr;			//テクスチャ情報
const void* CFade::ms_pVtx = nullptr;			//頂点情報
unsigned int CFade::ms_unVtxSize;				//頂点サイズ
unsigned int CFade::ms_unVtxCount;				//頂点数
const void* CFade::ms_pIdx = nullptr;			//頂点のインデックス
unsigned int CFade::ms_unIdxSize;				//インデックスサイズ
unsigned int CFade::ms_unIdxCount;				//インデックス数
ID3D11Buffer* CFade::ms_pVtxBuffer = nullptr;	//頂点バッファ
ID3D11Buffer* CFade::ms_pIdxBuffer = nullptr;	//インデックスバッファ 
CCamera* CFade::ms_pDefCamera = nullptr;		//専用予備カメラ

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：生成時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CFade::CFade(const CCamera* pCamera)
	:m_ucFlag(0x00)									//フラグ
	,m_pCamera(pCamera)								//カメラ
	,m_Transform(INIT_POS, INIT_SCALE, INIT_RADIAN)	//ワールド座標
	,m_UvParam{ {SCALE_OUT_MIN}, {0.0f } }					//シェーダー用UV座標
	,m_nFrame(0)								
{
	// =============== 静的作成 ===================
	if (0 == ms_nCntFade)	//現在、他にこのクラスが作成されていない時
	{
		// =============== カメラ作成 ===================
		ms_pDefCamera = new CCameraDef();	//予備カメラ

		// =============== シェーダー作成 ===================
		ms_pVs = new VertexShader();	//頂点シェーダ作成
		ms_pVs->Load(VS_PASS.c_str());	//頂点シェーダ読み込み
		ms_pPs = new PixelShader();		//ピクセルシェーダ作成
		ms_pPs->Load(PS_PASS.c_str());	//ピクセルシェーダ読み込み

	// =============== テクスチャ作成 ===================
		SetTexture();	//テクスチャ登録

	// =============== 形状作成 ===================
		Make();	//平面ポリゴン作成
	}

	// =============== 初期化 ===================
	if (pCamera)	//ヌルチェック
	{
		m_pCamera = pCamera;	//カメラ初期化
	}
	else
	{
		m_pCamera = ms_pDefCamera;	//疑似カメラ
	}

	// =============== 行列作成 ===================
	m_aMatrix[0] = m_Transform.GetWorldMatrixSRT();							//ワールド行列
	DirectX::XMStoreFloat4x4(&m_aMatrix[1], DirectX::XMMatrixIdentity());	//ビュー行列：単位行列
	m_aMatrix[2] = m_pCamera->GetProjectionMatrix(CCamera::E_DRAW_TYPE_2D);	//プロジェクション行列

	// =============== カウンタ ===================
	ms_nCntFade++;	//自身の数カウント

	// =============== フレーム数登録 ===================
	m_nFrame = FRAME_FADE_MAX.z;	//フェードインのフレーム数登録

	// =============== フラグ操作 ===================
	UpFlag(E_BIT_FLAG_FADE_IN);	//フェードイン開始
}

/* ========================================
	コピーコンストラクタ関数
	-------------------------------------
	内容：コピー時に行う処理
	-------------------------------------
	引数1：const CFade & Obj：コピー元の参照
	-------------------------------------
	戻値：なし
=========================================== */
CFade::CFade(const CFade & Obj)
{
}

/* ========================================
	デストラクタ関数
	-------------------------------------
	内容：破棄時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CFade::~CFade()
{
	// =============== 解放 ===================
	ms_nCntFade--;				//自身の数カウント
	if (ms_nCntFade == 0)
	{
		SAFE_DELETE(ms_pVs);		//頂点シェーダー解放
		SAFE_DELETE(ms_pPs);		//ピクセルシェーダー解放
		SAFE_DELETE(ms_pTexture);	//テクスチャ解放
		SAFE_DELETE(ms_pDefCamera);	//予備カメラ解放
		//SAFE_DELETE(ms_pVtx);		//頂点情報解放
		//SAFE_DELETE(ms_pIdx);		//頂点インデックス解放
		//SAFE_DELETE(ms_pVtxBuffer);	//頂点バッファ解放
		//SAFE_DELETE(ms_pIdxBuffer);	//インデックスバッファ解放
	}
}

/* ========================================
	更新関数
	-------------------------------------
	内容：更新処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CFade::Update()
{
	// =============== 検査 ===================
	if (!ms_pTexture || !(m_ucFlag & FLAG_FADE_ALL))	//描画できない時
	{
		return;	//処理中断
	}

	// =============== 退避 ===================
	unsigned char ucTemp = m_ucFlag;		//退避

	// =============== フラグ処理 ===================
	for (int nIdx = 0; nIdx < E_BIT_FLAG_MAX; nIdx++)
	{
		if (ucTemp & 0x01)	//下位ビットから優先して処理する
		{
			switch (0x01 << nIdx)	//添え字をビット列に変換
			{
				// =============== フェードアウト ===================
			case E_BIT_FLAG_FADE_OUT:	//フェードアウト
				FadeOut();	//フェードアウト処理
				break;		//分岐処理終了

				// =============== フェードストップ ===================
			case E_BIT_FLAG_FADE_STOP:	//フェードストップ
				FadeStop();	//フェードストップ処理
				break;		//分岐処理終了

				// =============== フェードイン ===================
			case E_BIT_FLAG_FADE_IN:	//フェードイン
				FadeIn();	//フェードイン処理
				break;		//分岐処理終了

				// =============== 未対応 ===================
			default:					//その他
#if _DEBUG
				MessageBox(nullptr, "想定されないフェードの種類です", "Fade.cpp->Update->Error", MB_OK);	//エラー通知
#endif
				break;						//分岐処理終了
			}
			break;	//ループ処理終了
		}
		else
		{
			ucTemp >>= 1;	//次のフラグ候補へ
		}
	}

	// =============== 行列更新 ===================
	m_aMatrix[0] = m_Transform.GetWorldMatrixSRT();							//ワールド行列更新
	m_aMatrix[2] = m_pCamera->GetProjectionMatrix(CCamera::E_DRAW_TYPE_2D);	//プロジェクション行列更新
}

/* ========================================
	描画関数
	-------------------------------------
	内容：描画処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CFade::Draw()
{
	// =============== 検査 ===================
	if (!ms_pTexture || !(m_ucFlag & FLAG_FADE_ALL))	//描画できない時
	{
		if (m_ucFlag & E_BIT_FLAG_BLACKOUT)
		{
			// =============== 処理変更 ===================
			m_UvParam.fUvOffset = 1000.0f;	//テクスチャ位置をずらしフェードを隠す
		}
		else
		{
			// =============== 終了 ===================
			return;	//処理中断
		}
	}

	// =============== 変数宣言 ===================
	float Param[4] = { m_UvParam.fUvScale.x, m_UvParam.fUvScale.y, m_UvParam.fUvOffset.x, m_UvParam.fUvOffset.y };	//定数バッファ書き込み用

	// =============== シェーダー使用 ===================
	ms_pVs->WriteBuffer(0, m_aMatrix);	//定数バッファに行列情報書き込み
	ms_pVs->WriteBuffer(1, &Param);	//定数バッファにUV情報書き込み
	ms_pVs->Bind();						//頂点シェーダー使用
	ms_pPs->SetTexture(0, ms_pTexture);	//テクスチャ登録
	ms_pPs->Bind();						//ピクセルシェーダー使用

	// =============== 変数宣言 ===================
	ID3D11DeviceContext* pContext = GetContext();	//描画属性の情報
	unsigned int unOffset = 0;						//頂点バッファ配列内のバッファ数

	// =============== トポロジー設定 ===================
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);		//三角ポリゴンのトポロジー		TODO:平面だからstripでも良さそうだけどどっちの方が軽いか調べる

	// =============== 頂点バッファ登録 ===================
	pContext->IASetVertexBuffers(0, 1, &ms_pVtxBuffer, &ms_unVtxSize, &unOffset);	//頂点バッファ登録

	// =============== インデックスの有無 ===================
	if (ms_unIdxCount > 0)	//インデックスがある時
	{
		// =============== サイズ違い ===================
		DXGI_FORMAT Format;	//リソースデータフォーマット
		switch (ms_unIdxSize)	//インデックスサイズ
		{
		case 4: Format = DXGI_FORMAT_R32_UINT; break;	//1成分32ビット符号なし整数(unsigned int (新しいやつ))
		case 2: Format = DXGI_FORMAT_R16_UINT; break;	//1成分16ビット符号なし整数(unsigned int (古いやつ))
		}

		// =============== インデックスバッファ登録 ===================
		pContext->IASetIndexBuffer(ms_pIdxBuffer, Format, 0);	//インデックスバッファ登録

		// =============== 描画 ===================
		pContext->DrawIndexed(ms_unIdxCount, 0, 0);	//頂点のインデックスを使って描画
	}
	else
	{
		// =============== 描画 ===================
		pContext->Draw(ms_unVtxCount, 0);	// 頂点バッファのみで描画
	}
}

/* ========================================
	スタート関数
	-------------------------------------
	内容：形状生成・情報登録
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CFade::Start()
{
	// =============== フレーム数登録 ===================
	m_nFrame = FRAME_FADE_MAX.x;	//フェードアウトのフレーム数登録

	// =============== フラグ操作 ===================
	UpFlag(E_BIT_FLAG_FADE_OUT);	//フェードアウト開始
}

/* ========================================
	フェード確認関数
	-------------------------------------
	内容：フェード中か確認する
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：フェード中でtrue, それ以外はfalse
=========================================== */
bool CFade::IsFade()
{	
	// =============== 提供 ===================
	if (m_ucFlag & FLAG_FADE_ALL)	//フェード中
	{
		return true;	//フェードしている
	}
	else
	{
		return false;	//フェードしていない
	}
}

/* ========================================
	フェードアウト確認関数
	-------------------------------------
	内容：フェードアウト中か確認する
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：フェードアウト中でtrue, それ以外はfalse
=========================================== */
bool CFade::IsFadeOut()
{
	// =============== 退避 ===================
	unsigned char ucTemp = m_ucFlag;		//退避

	// =============== フラグ処理 ===================
	for (int nIdx = 0; nIdx < E_BIT_FLAG_MAX; nIdx++)
	{
		if (ucTemp & 0x01)	//Update関数と同等の優先度で処理する
		{
			// =============== 提供 ===================
			switch (0x01 << nIdx)	//添え字をビット列に変換
			{
				// =============== フェードアウト中 ===================
			case E_BIT_FLAG_FADE_OUT:	//フェードアウト
				return true;	//フェードアウトしている
				break;			//分岐処理終了
			}
			break;	//ループ処理終了
		}
		else
		{
			ucTemp >>= 1;	//次のフラグ候補へ
		}
	}
	return false;	//フェードアウトしていない
}

/* ========================================
	フェードイン確認関数
	-------------------------------------
	内容：フェードイン中か確認する
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：フェードイン中でtrue, それ以外はfalse
=========================================== */
bool CFade::IsFadeIn()
{
	// =============== 退避 ===================
	unsigned char ucTemp = m_ucFlag;		//退避

	// =============== フラグ処理 ===================
	for (int nIdx = 0; nIdx < E_BIT_FLAG_MAX; nIdx++)
	{
		if (ucTemp & 0x01)	//Update関数と同等の優先度で処理する
		{
			// =============== 提供 ===================
			switch (0x01 << nIdx)	//添え字をビット列に変換
			{
				// =============== フェードイン中 ===================
			case E_BIT_FLAG_FADE_IN:	//フェードイン
				return true;	//フェードインしている
				break;			//分岐処理終了
			}
			break;	//ループ処理終了
		}
		else
		{
			ucTemp >>= 1;	//次のフラグ候補へ
		}
	}
	return false;	//フェードインしていない
}

/* ========================================
	フェード進捗ゲッタ関数
	-------------------------------------
	内容：現在フェードモードの進行割合を提供する
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：現在フェードモードの 進捗時間 / 最大時間 の結果	非フェード時は0.0f
=========================================== */
float CFade::GetFrameRate()
{
	// =============== 退避 ===================
	unsigned char ucTemp = m_ucFlag;		//退避

	// =============== フラグ処理 ===================
	for (int nIdx = 0; nIdx < E_BIT_FLAG_MAX; nIdx++)
	{
		if (ucTemp & 0x01)	//下位ビットから優先して処理する
		{
			// =============== 提供 ===================
			switch (0x01 << nIdx)	//添え字をビット列に変換
			{
				// =============== フェードアウト ===================
			case E_BIT_FLAG_FADE_OUT:	//フェードアウト
#if _DEBUG
				if (0 == FRAME_FADE_MAX.x)
				{
					MessageBox(nullptr, "0除算の危険性があります", "Fade.cpp->GetFrameRate->Error", MB_OK);	//エラー通知
					return 0.0f;	//臨時対応
				}
#endif
				return static_cast<float>(m_nFrame) / static_cast<float>(FRAME_FADE_MAX.x);	//アウトの進行割合
				break;		//分岐処理終了

				// =============== フェードストップ ===================
			case E_BIT_FLAG_FADE_STOP:	//フェードストップ
#if _DEBUG
				if (0 == FRAME_FADE_MAX.y)
				{
					MessageBox(nullptr, "0除算の危険性があります", "Fade.cpp->GetFrameRate->Error", MB_OK);	//エラー通知
					return 0.0f;	//臨時対応
				}
#endif
				return static_cast<float>(m_nFrame) / static_cast<float>(FRAME_FADE_MAX.y);	//ストップの進行割合
				break;		//分岐処理終了

				// =============== フェードイン ===================
			case E_BIT_FLAG_FADE_IN:	//フェードイン
#if _DEBUG
				if (0 == FRAME_FADE_MAX.z)
				{
					MessageBox(nullptr, "0除算の危険性があります", "Fade.cpp->GetFrameRate->Error", MB_OK);	//エラー通知
					return 0.0f;	//代替値で対応
				}
#endif
				return static_cast<float>(m_nFrame) / static_cast<float>(FRAME_FADE_MAX.z);	//インの進行割合
				break;		//分岐処理終了
#if _DEBUG
				// =============== 未対応 ===================
			default:					//その他
				MessageBox(nullptr, "想定されないフェードの種類です", "Fade.cpp->GetFrameRate->Error", MB_OK);	//エラー通知
				break;			//分岐処理終了
#endif
			}
			break;	//ループ処理終了
		}
		else
		{
			ucTemp >>= 1;	//次のフラグ候補へ
		}
	}
		return 0.0f;	//フェードしていない
}

/* ========================================
	形状生成関数
	-------------------------------------
	内容：形状生成・情報登録
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CFade::Make()
{
	// =============== 変数宣言 ===================
	Vertex aVtx[] = {
		{{-0.5f, 0.5f, -0.0f}, {0.0f, 0.0f}},	//平面ポリゴン左上
		{{ 0.5f, 0.5f, -0.0f}, {1.0f, 0.0f}},	//平面ポリゴン右上
		{{-0.5f,-0.5f, -0.0f}, {0.0f, 1.0f}},	//平面ポリゴン左下
		{{ 0.5f,-0.5f, -0.0f}, {1.0f, 1.0f}},	//平面ポリゴン右下
	};	//頂点情報
	int aIdx[] = {
		0, 1, 2, 2, 1, 3	//平面ポリゴン
	};	//頂点インデックス

	// =============== 初期化 ===================
	ms_pVtx = aVtx;					//頂点情報
	ms_unVtxSize = sizeof(Vertex);	//頂点型サイズ
	ms_unVtxCount = _countof(aVtx);	//頂点数
	ms_pIdx = aIdx;					//頂点のインデックス
	ms_unIdxSize = sizeof(int);		//インデックスサイズ
	ms_unIdxCount = _countof(aIdx);	//インデックス数

	// =============== 生成 ===================
	CreateVtxBuffer();	//頂点バッファ作成
	CreateIdxBuffer();	//インデックスバッファ
}

/* ========================================
	テクスチャセッタ関数
	-------------------------------------
	内容：テクスチャー作成・登録
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CFade::SetTexture()
{
	// =============== 解放 ===================
	SAFE_DELETE(ms_pTexture);	//テクスチャ解放

	// =============== 作成 ===================
	ms_pTexture = new Texture;				//動的確保
	ms_pTexture->Create(TEX_PASS.c_str());	//新規テクスチャ登録
}

/* ========================================
	頂点バッファ作成関数
	-------------------------------------
	内容：インデックス情報からデータ作成
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CFade::CreateVtxBuffer()
{
	// =============== バッファ情報設定 ===================
	D3D11_BUFFER_DESC BufDesc;							//バッファ情報
	ZeroMemory(&BufDesc, sizeof(BufDesc));				//中身を全て0で初期化
	BufDesc.ByteWidth = ms_unVtxSize * ms_unVtxCount;	//バッファの大きさ
	BufDesc.Usage = D3D11_USAGE_DEFAULT;				//メモリ上での管理方法
	BufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;		//GPU上での利用方法

	//＞バッファ初期データ設定
	D3D11_SUBRESOURCE_DATA SubResource;				//サブリソース
	ZeroMemory(&SubResource, sizeof(SubResource));	//データ初期化
	SubResource.pSysMem = ms_pVtx;					//バッファに入れ込むデータ

	// =============== 作成 ===================
	HRESULT hr = GetDevice()->CreateBuffer(&BufDesc, &SubResource, &ms_pVtxBuffer);	//頂点バッファ作成
	if (FAILED(hr))	//エラー検査
	{
		// =============== 代替処理 ===================
		ms_pVtxBuffer = nullptr;	//空アドレス代入
	}
}

/* ========================================
	インデックスバッファ作成関数
	-------------------------------------
	内容：インデックス情報からデータ作成
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CFade::CreateIdxBuffer()
{
	// =============== インデックスサイズの確認 ===================
	switch (ms_unIdxSize)
	{
		// =============== サイズ違い ===================
	default:	//下記以外
#if _DEBUG
		MessageBox(nullptr, "型のサイズがint型と一致しません", "Fade.cpp->CreateIdxBuffer->Error", MB_OK);	//エラー通知
#endif
		return;	//処理中断

		// =============== int型と同一 ===================
	case 2:	//古いint型のサイズ
	case 4:	//今のint型のサイズ
		break;	//分岐処理終了
	}

	// =============== バッファの情報を設定 ===================
	D3D11_BUFFER_DESC BufDesc;							//バッファ情報
	ZeroMemory(&BufDesc, sizeof(BufDesc));				//中身を全て0で初期化
	BufDesc.ByteWidth = ms_unIdxSize * ms_unIdxCount;	//データのバイト数
	BufDesc.Usage = D3D11_USAGE_DEFAULT;				//メモリ上での管理方法
	BufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;		//GPU上での利用方法

	// =============== バッファの初期データ ===================
	D3D11_SUBRESOURCE_DATA SubResource = {};	//サブリソース
	SubResource.pSysMem = ms_pIdx;				//バッファに入れ込むデータ

	// =============== 作成 ===================
	HRESULT hr = GetDevice()->CreateBuffer(&BufDesc, &SubResource, &ms_pIdxBuffer);	//インデックスのバッファ作成
	if (FAILED(hr))	//エラー検査
	{
		// =============== 代替処理 ===================
		ms_pIdxBuffer = nullptr;	//空アドレス代入
	}
}

/* ========================================
	フラグオン関数
	-------------------------------------
	内容：引数に対応したフラグを起こす
	-------------------------------------
	引数1：const unsigned char & ucBitFlag：対象フラグ
	-------------------------------------
	戻値：なし
=========================================== */
void CFade::UpFlag(const unsigned char & ucBitFlag)
{
	// =============== 代入 ===================
	m_ucFlag |= ucBitFlag;	//フラグ操作
}

/* ========================================
	フラグオフ関数
	-------------------------------------
	内容：引数に対応したフラグを降ろす
	-------------------------------------
	引数1：const unsigned char & ucBitFlag：対象フラグ
	-------------------------------------
	戻値：なし
=========================================== */
void CFade::DownFlag(const unsigned char & ucBitFlag)
{
	// =============== 代入 ===================
	m_ucFlag &= (ucBitFlag ^ 0xFF);	//フラグ操作
}

/* ========================================
	フラグスイッチ関数
	-------------------------------------
	内容：引数に対応したフラグの反転
	-------------------------------------
	引数1：const unsigned char & ucBitFlag：対象フラグ
	-------------------------------------
	戻値：なし
=========================================== */
void CFade::SetFlag(const unsigned char & ucBitFlag)
{
	// =============== 代入 ===================
	m_ucFlag ^= ucBitFlag;	//フラグ操作
}

/* ========================================
	フェードアウト更新関数
	-------------------------------------
	内容：フェードアウト処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CFade::FadeOut()
{
#if _DEBUG
	// =============== 検査 ===================
	if (!(m_ucFlag & E_BIT_FLAG_FADE_OUT))	//アウト処理
	{
		MessageBox(nullptr, "フェードアウト中でない時にフェードアウトしようとしています", "Fade.cpp->FadeOut->Error", MB_OK);	//エラー通知
		return;	//処理中断
	}
#endif
		// =============== 状態分岐 ===================
		if (m_nFrame < FRAME_MIN)	//フェードアウト終了
		{
			DownFlag(E_BIT_FLAG_FADE_OUT);	//フェードアウト終了
			//m_nFrame = FRAME_FADE_MAX.y;	//フェードストップのフレーム数登録
			//UpFlag(E_BIT_FLAG_FADE_STOP);	//フェードストップ開始
			UpFlag(E_BIT_FLAG_BLACKOUT);	//フェードストップ開始
		}
		else
		{
			// =============== 初期化子付き変数宣言 ===================
			int nFrameTemp = FRAME_FADE_MAX.x - m_nFrame;	//退避
			
			// =============== 拡縮更新 ===================
			if (nFrameTemp <= FRAME_OUT_PATTERN_1_FIN)	//フェードアウトパターン１：フェードアウト開始から拡縮が留まるまで
			{
				m_UvParam.fUvScale.x = SCALE_OUT_MAX + (SCALE_OUT_STAY - SCALE_OUT_MAX) * (float)(nFrameTemp - FRAME_MIN) / (float)(FRAME_OUT_PATTERN_1_FIN);	//拡縮セット
			}
			else
			{
				if (nFrameTemp <= FRAME_OUT_PATTERN_2_FIN)	//フェードアウトパターン２：拡縮が留まり始めてから留まり終わるまで
				{
					m_UvParam.fUvScale.x = SCALE_OUT_STAY;	//拡縮セット
				}
				else
				{
					if (nFrameTemp <= FRAME_FADE_MAX.x)	//フェードアウトパターン３：拡縮再開からフェードアウト終了まで
					{
						m_UvParam.fUvScale.x = SCALE_OUT_STAY + (SCALE_OUT_MIN - SCALE_OUT_STAY) * (float)(nFrameTemp - FRAME_OUT_PATTERN_2_FIN) / (float)(FRAME_FADE_MAX.x - FRAME_OUT_PATTERN_2_FIN);	//拡縮セット
					}
#if _DEBUG
					else
					{
						MessageBox(nullptr, "フレーム数が想定を超過しました", "Fade.cpp->FadeOut->Error", MB_OK);	//エラー通知
					}
#endif
				}
			}
			m_UvParam.fUvScale.y = m_UvParam.fUvScale.x;	//x値の変更をy値に反映する

			// =============== 回転角更新 ===================
			m_Transform.fRadian.z = DirectX::XMConvertToRadians(ROTATE_EASE_IN_OUT(nFrameTemp));	//フレーム数で角更新
		}

		// =============== カウンタ ===================
		m_nFrame--;	//フレームカウント
}

/* ========================================
	フェードストップ更新関数
	-------------------------------------
	内容：フェードストップ処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CFade::FadeStop()
{	
#if _DEBUG
	// =============== 検査 ===================
	if (!(m_ucFlag & E_BIT_FLAG_FADE_STOP))	//ストップ処理
	{
		MessageBox(nullptr, "フェードストップ中でない時にフェードストップしようとしています", "Fade.cpp->FadeStop->Error", MB_OK);	//エラー通知
		return;	//処理中断
	}
#endif
	// =============== フェードストップ ===================
		if (m_nFrame <= FRAME_MIN)	//カウント終了
		{
			m_UvParam.fUvOffset = 0.0f;		//テクスチャ位置を戻しフェードを見せる
			DownFlag(E_BIT_FLAG_FADE_STOP);	//ストップ終了
			//m_nFrame = FRAME_FADE_MAX.z;	//フェードインのフレーム数登録
			//UpFlag(E_BIT_FLAG_FADE_IN);		//フェードイン開始
		}

		// =============== カウンタ ===================
		m_nFrame--;	//フレームカウント
}

/* ========================================
	フェードイン更新関数
	-------------------------------------
	内容：フェードイン処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CFade::FadeIn()
{
#if _DEBUG
	// =============== 検査 ===================
	if (!(m_ucFlag & E_BIT_FLAG_FADE_IN))	//イン処理
	{
		MessageBox(nullptr, "フェードイン中でない時にフェードインしようとしています", "Fade.cpp->FadeIn->Error", MB_OK);	//エラー通知
		return;	//処理中断
	}
#endif
	// =============== 状態分岐 ===================
	if (m_nFrame < FRAME_MIN)	//フェードイン終了
	{
		DownFlag(E_BIT_FLAG_FADE_IN);	//フェードイン終了
	}
	else
	{
		// =============== 初期化子付き変数宣言 ===================
		int nFrameTemp = FRAME_FADE_MAX.z - m_nFrame;	//退避

		// =============== 拡縮更新 ===================
#if _DEBUG
		if (m_nFrame <= FRAME_FADE_MAX.z)	//フェードイン
		{
#endif
			m_UvParam.fUvScale.x = SCALE_IN_MAX + (SCALE_IN_MIN - SCALE_IN_MAX) * (float)(m_nFrame - FRAME_MIN) / (float)(FRAME_FADE_MAX.z);	//拡縮セット
#if _DEBUG
		}
		else
		{
			MessageBox(nullptr, "フレーム数が想定を超過しました", "Fade.cpp->FadeIn->Error", MB_OK);	//エラー通知
		}
#endif
	}
	m_UvParam.fUvScale.y = m_UvParam.fUvScale.x;	//x値の変更をy値に反映する

	// =============== 回転角更新 ===================
	m_Transform.fRadian.z = DirectX::XMConvertToRadians(ROTATE_EASE_IN_OUT(FRAME_FADE_MAX.x - m_nFrame));	//フレーム数で角更新
	//m_Transform.fRadian.z = DirectX::XMConvertToRadians(ROTATE_ACCEL_RATE * -cosf(3.14159265358979323846264338327950188419f * (float)(m_nFrame - FRAME_MIN) / (float)(FRAME_FADE_MAX.z) - 1) / 2);

	// =============== カウンタ ===================
	m_nFrame--;	//フレームカウント
}