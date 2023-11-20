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

========================================== */

// =============== デバッグモード ===================
#if _DEBUG
#define USE_FADE (true)	//フェード試運転
#endif

// =============== インクルード ===================
#include "Fade.h"	//自身のヘッダ

#if USE_FADE
#include "Input.h"	//キー入力用
#endif

#if _DEBUG
#include <Windows.h>	//メッセージボックス用
#endif

// =============== 定数定義 =====================
const std::string VS_PASS("Assets/Shader/VsFade.cso");	//テクスチャのパス名
const std::string PS_PASS("Assets/Shader/PsFade.cso");	//テクスチャのパス名
const std::string TEX_PASS("Assets/Fade.png");			//テクスチャのパス名
const TPos3d<float> INIT_POS(640.0f, 360.0f, 0.0f);		//位置初期化
const TTriType<float> INIT_SCALE(80.0f, 80.0f, 0.0f);	//初期拡縮
const TTriType<float> INIT_RADIAN(0.0f);				//初期回転
const int FRAME_MIN(0);									//フェード時間の最小
const int FRAME_TURNING_1(50);							//拡縮反転１反転
const int FRAME_TURNING_2(100);							//拡縮反転２反転
const int FRAME_MAX(150);								//フェード時間の最大
const float SCALE_MIN(0.0f);							//最小サイズ
const float SCALE_TURNINIG_2(15.0f);					//サイズ反転２反転
const float SCALE_TURNINIG_1(100.0f);					//サイズ反転１反転
const float SCALE_MAX(1000.0f);							//最大サイズ
const float ROTATE_ACCEL_RATE(4.0f);					//角速度増加割合

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
	,m_UvParam{{ 1.0f, 1.0f }, { 0.0f, 0.0f }}		//シェーダー用UV座標	//TODO:DiTypeの情報が更新されたら反映する
	,m_nFrameOut(0)
	,m_nFrameStop(0)
	,m_nFrameIn(0)
{
	// =============== 静的作成 ===================
	if (0 == ms_nCntFade)	//現在、他にこのクラスが作成されていない時
	{
		// =============== シェーダー作成 ===================
		ms_pVs = new VertexShader();		//頂点シェーダ作成
		ms_pVs->Load("Assets/Shader/VsFade.cso");		//頂点シェーダ読み込み
		ms_pPs = new PixelShader();			//ピクセルシェーダ作成
		ms_pPs->Load("Assets/Shader/PsFade.cso");		//ピクセルシェーダ読み込み

	// =============== テクスチャ作成 ===================
		SetTexture();	//テクスチャ登録

	// =============== 形状作成 ===================
		Make();	//平面ポリゴン作成
	}

	// =============== 行列作成 ===================
	m_aMatrix[0] = m_Transform.GetWorldMatrixSRT();							//ワールド行列
	DirectX::XMStoreFloat4x4(&m_aMatrix[1], DirectX::XMMatrixIdentity());	//ビュー行列：単位行列
	m_aMatrix[2] = m_pCamera->GetProjectionMatrix(CCamera::E_DRAW_TYPE_2D);	//プロジェクション行列

	// =============== カウンタ ===================
	ms_nCntFade++;	//自身の数カウント
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
	SAFE_DELETE(ms_pVs);		//頂点シェーダー解放
	SAFE_DELETE(ms_pPs);		//ピクセルシェーダー解放
	SAFE_DELETE(ms_pTexture);	//テクスチャ解放
	//SAFE_DELETE(ms_pVtx);		//頂点情報解放
	//SAFE_DELETE(ms_pIdx);		//頂点インデックス解放
	//SAFE_DELETE(ms_pVtxBuffer);	//頂点バッファ解放
	//SAFE_DELETE(ms_pIdxBuffer);	//インデックスバッファ解放
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
#if USE_FADE
	if (IsKeyTrigger('7'))
	{
		Start();	//フェード開始
	}
#endif

	// =============== 検査 ===================
	if (!ms_pTexture || !(m_ucFlag & FLAG_FADE_ALL))	//描画できない時
	{
		return;	//処理中断
	}

	// =============== フェードストップ ===================
	if (m_ucFlag & E_BIT_FLAG_FADE_STOP)	//ストップ処理
	{
		if (m_nFrameStop <= FRAME_MIN)	//カウント終了
		{
			DownFlag(E_BIT_FLAG_FADE_STOP);	//ストップ終了
			UpFlag(E_BIT_FLAG_FADE_IN);		//フェードイン開始
			m_nFrameOut = FRAME_MAX;		//フェード時間再登録
		}

		// =============== カウンタ ===================
		m_nFrameStop--;	//フレームカウント
	}
	else
	{
		// =============== フェード ===================
#if _DEBUG
		if (m_ucFlag & (E_BIT_FLAG_FADE_IN | E_BIT_FLAG_FADE_OUT))
		{
#endif
			// =============== 変数宣言 ===================
			int nFrameTemp;	//フレーム退避用

			// =============== 分岐処理 ===================
			if (m_ucFlag & E_BIT_FLAG_FADE_OUT)	//フェードアウト時
			{
				// =============== 初期化 ===================
				nFrameTemp = FRAME_MAX - m_nFrameOut;	//退避

				// =============== カウンタ ===================
				m_nFrameOut--;	//フレームカウント
			}
			if (m_ucFlag & E_BIT_FLAG_FADE_IN)	//フェードイン時
			{
				// =============== 初期化 ===================
				nFrameTemp = m_nFrameIn;	//退避

				// =============== カウンタ ===================
				m_nFrameIn--;	//フレームカウント
			}

			// =============== 状態分岐 ===================
			if (m_nFrameIn <= FRAME_MIN && m_ucFlag & E_BIT_FLAG_FADE_IN || m_nFrameOut <= FRAME_MIN && m_ucFlag & E_BIT_FLAG_FADE_OUT)	//フェードアウト・イン終了
			{
				if (m_ucFlag & E_BIT_FLAG_FADE_OUT)	//フェードアウト時
				{
					DownFlag(E_BIT_FLAG_FADE_OUT);	//フェードアウト終了
					UpFlag(E_BIT_FLAG_FADE_STOP);	//フェードストップ開始
				}
				if (m_ucFlag & E_BIT_FLAG_FADE_IN)	//フェードイン時
				{
					DownFlag(E_BIT_FLAG_FADE_IN);	//フェードイン終了
				}
			}
			else
			{
				if (nFrameTemp <= FRAME_TURNING_1)	//アウト時：第１ターニングポイントから終了まで
				{
					m_UvParam.fUvScale.x =(SCALE_TURNINIG_1 - SCALE_MIN) * (float)(nFrameTemp - FRAME_MIN) / (float)(FRAME_TURNING_1);	//拡縮セット
				}
				else
				{
					if (nFrameTemp <= FRAME_TURNING_2)	//アウト時：第２ターニングポイントから第１ターニングポイントまで
					{
						m_UvParam.fUvScale.x = SCALE_TURNINIG_1 + (SCALE_TURNINIG_2 - SCALE_TURNINIG_1) * (float)(nFrameTemp - FRAME_TURNING_1) / (float)(FRAME_TURNING_2 - FRAME_TURNING_1);	//拡縮セット
					}
					else
					{
						if (nFrameTemp <= FRAME_MAX)	//アウト時：開始から第１ターニングポイントまで
						{
							m_UvParam.fUvScale.x = SCALE_TURNINIG_2 + (SCALE_MAX - SCALE_TURNINIG_2) * (float)(nFrameTemp - FRAME_TURNING_2) / (float)(FRAME_MAX - FRAME_TURNING_2);	//拡縮セット
						}
#if _DEBUG
						else
						{
							MessageBox(nullptr, "フレーム数が想定を超過しました", "Fade.cpp->Error", MB_OK);	//エラー通知
						}
#endif
					}
				}
				m_UvParam.fUvScale.y = m_UvParam.fUvScale.x;	//変更を揃える
			}

			// =============== 角更新 ===================
			m_Transform.fRadian.z = DirectX::XMConvertToRadians(nFrameTemp * ROTATE_ACCEL_RATE);	//フレーム数で角更新
#if _DEBUG
		}
		else
		{
			MessageBox(nullptr, "想定されないフェードの種類です", "Fade.cpp->Error", MB_OK);	//エラー通知
		}
#endif
	}

	// =============== 行列更新 ===================
	m_aMatrix[0] = m_Transform.GetWorldMatrixSRT();							//ワールド行列更新
	m_aMatrix[2] = m_pCamera->GetProjectionMatrix(CCamera::E_DRAW_TYPE_2D);	//プロジェクション行列更新

	// =============== 変数宣言 ===================
	float Param[4] = { m_UvParam.fUvScale.x, m_UvParam.fUvScale.y, m_UvParam.fDummy.x, m_UvParam.fDummy.y };	//定数バッファ書き込み用

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
	引数1：TTriType<int> nFrame：フレーム数(x：フェードアウト, y：フェードストップ, z：フェードイン)
	-------------------------------------
	戻値：なし
=========================================== */
void CFade::Start(TTriType<int> nFrame)
{
	// =============== フレーム数登録 ===================
	m_nFrameOut = nFrame.x;		//フェードアウトのフレーム数登録
	m_nFrameStop = nFrame.y;	//フェードストップのフレーム数登録
	m_nFrameIn = nFrame.z;		//フェードインのフレーム数登録

	// =============== フラグ操作 ===================
	UpFlag(E_BIT_FLAG_FADE_OUT);	//フェードアウト開始
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
		{{-10.5f, 10.5f, -0.0f}, {0.0f, 0.0f}},	//平面ポリゴン左上
		{{ 10.5f, 10.5f, -0.0f}, {1.0f, 0.0f}},	//平面ポリゴン右上
		{{-10.5f,-10.5f, -0.0f}, {0.0f, 1.0f}},	//平面ポリゴン左下
		{{ 10.5f,-10.5f, -0.0f}, {1.0f, 1.0f}},	//平面ポリゴン右下
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
		MessageBox(nullptr, "型のサイズがint型と一致しません", "Fade.cpp->Error", MB_OK);	//エラー通知
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
	フラグオン関数
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
	m_ucFlag &= !ucBitFlag;	//フラグ操作
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