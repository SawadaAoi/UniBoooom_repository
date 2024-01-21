/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	2Dオブジェクト実装
	------------------------------------
	2dObject.cpp
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/11/21 作成 takagi
	・2023/11/22 メッシュサイズを1x1に修正 takagi
	・2023/11/28 TextureSet関数にポインタ指定できる物を追加 takagi
	・2023/12/01 テクスチャの扱い方を安全化 takagi
	・2023/12/04 デストラクタの削除対象を修正 takagi
	・2023/12/05 描画のモード追加 takagi
	・2023/12/10 静的確保されたものの削除のタイミングを修正 takagi
	・2023/12/15 空の更新関数追加・警告文追加・改修
					・コンストラクタでカメラが作られない問題修正 takagi
	・2023/12/17 引数参照化 takagi
	・2023/12/20 ビルボードの処理修正 takagi
	・2024/01/16 リネーム・継承・不要箇所削除 takagi
	・2024/01/18 リファクタリング及びコメント追加 takagi
	・2024/01/19 switch文break抜け修正 takagi
	・2024/01/20 GetPos()関数追加 takagi
	・2024/01/21 コメント改修 takagi

========================================== */

// =============== インクルード ===================
#include "2dObject.h"	//自身のヘッダ
#include "CameraDef.h"	//疑似カメラ
#if _DEBUG
#include <Windows.h>	//メッセージボックス用
#endif

// =============== 定数定義 =====================	//コンパイルするプログラムを書いているのでここに記載
const char* VS = R"EOT(
struct VS_IN {
	float3 pos : POSITION0;
	float2 uv : TEXCOORD0;
};
struct VS_OUT {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};
cbuffer Matrix : register(b0) {
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};
cbuffer Param : register(b1) {
	float2 uvPos;
	float2 uvScale;
	float4 color;
};
VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos = mul(vout.pos, world);
	vout.pos = mul(vout.pos, view);
	vout.pos = mul(vout.pos, proj);
	vout.uv = vin.uv;
	vout.uv *= uvScale;
	vout.uv += uvPos;
	vout.color = color;
	return vout;
})EOT";	//頂点シェーダーコンパイル文
const char* PS = R"EOT(
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};
Texture2D tex : register(t0);
SamplerState samp : register(s0);
float4 main(PS_IN pin) : SV_TARGET {
	return tex.Sample(samp, pin.uv) * pin.color;
})EOT";	//ピクセルシェーダーコンパイル文

// =============== グローバル変数宣言 =====================
int C2dObject::ms_nCnt2dObject;						//自身の生成数
const void* C2dObject::ms_pVtx = nullptr;			//頂点情報
unsigned int C2dObject::ms_unVtxSize;				//頂点サイズ
unsigned int C2dObject::ms_unVtxCount;				//頂点数
const void* C2dObject::ms_pIdx = nullptr;			//頂点のインデックス
unsigned int C2dObject::ms_unIdxSize;				//インデックスサイズ
unsigned int C2dObject::ms_unIdxCount;				//インデックス数
ID3D11Buffer* C2dObject::ms_pVtxBuffer = nullptr;	//頂点バッファ
ID3D11Buffer* C2dObject::ms_pIdxBuffer = nullptr;	//インデックスバッファ 
VertexShader* C2dObject::ms_pDefVs;					//デフォルト頂点シェーダー
PixelShader* C2dObject::ms_pDefPs;					//デフォルトピクセルシェーダー
const CCamera* C2dObject::ms_pCameraDef;			//疑似カメラ

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：生成時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
C2dObject::C2dObject()
	:m_Param{{0.0f}, {1.0f, 1.0f}, {1.0f}, 1.0f}	//シェーダーに書き込む情報
	,m_pVs(nullptr)									//頂点シェーダー
	,m_pPs(nullptr)									//ピクセルシェーダー
	,m_pTexture(nullptr)							//テクスチャ
	,m_pTextureLoad(nullptr)						//テクスチャアドレス格納専用
	,m_eMode(DEFAULT_DRAW_MODE)						//描画方法
	,m_pCamera(nullptr)								//カメラ
{
	// =============== 静的作成 ===================
	if (0 == ms_nCnt2dObject)	//現在、他にこのクラスが作成されていない時
	{
		// =============== シェーダー作成 ===================
		MakeVertexShader();	//頂点シェーダー作成
		MakePixelShader();	//ピクセルシェーダー作成

		// =============== 疑似カメラ作成 ===================
		ms_pCameraDef = new CCameraDef();	//デフォルトのカメラ

	// =============== 形状作成 ===================
		Make();	//平面ポリゴン作成
	}

	// =============== 初期化 ===================
	m_pVs = ms_pDefVs;	//頂点シェーダー初期化
	m_pPs = ms_pDefPs;	//ピクセルシェーダー初期化
	SetCamera(nullptr);	//カメラ初期化

	// =============== 行列作成 ===================
	m_aMatrix[E_MATRIX_WORLD] = m_Transform.GetWorldMatrixSRT();							//ワールド行列
	DirectX::XMStoreFloat4x4(&m_aMatrix[E_MATRIX_VIEW], DirectX::XMMatrixIdentity());		//ビュー行列：単位行列
	DirectX::XMStoreFloat4x4(&m_aMatrix[E_MATRIX_PROJECTION], DirectX::XMMatrixIdentity());	//プロジェクション行列

	// =============== カウンタ ===================
	ms_nCnt2dObject++;	//自身の数カウント
}

/* ========================================
	コピーコンストラクタ関数
	-------------------------------------
	内容：コピー時に行う処理
	-------------------------------------
	引数1：const C2dObject & Obj：コピー元の参照
	-------------------------------------
	戻値：なし
=========================================== */
C2dObject::C2dObject(const C2dObject & Obj)
	:m_Param(Obj.m_Param)				//シェーダーに書き込む情報
	,m_eMode(Obj.m_eMode)				//描画方法
	,m_pTextureLoad(Obj.m_pTextureLoad)	//テクスチャアドレス格納専用
{
	// =============== 初期化 ===================
	for (int nIdx = 0; nIdx < E_MATRIX_MAX; nIdx++)
	{
		m_aMatrix[nIdx] = Obj.m_aMatrix[nIdx];	//行列初期化
	}

	// =============== 動的確保 ===================
	if (Obj.m_pVs)	//ヌルチェック
	{
		m_pVs = new VertexShader(*Obj.m_pVs);	//頂点シェーダー
	}
	else
	{
		m_pVs = nullptr;	//空アドレス代入
	}
	if (Obj.m_pPs)	//ヌルチェック
	{
		m_pPs = new PixelShader(*Obj.m_pPs);	//ピクセルシェーダー
	}
	else
	{
		m_pPs = nullptr;	//空アドレス代入
	}
	if (Obj.m_pTexture)	//ヌルチェック
	{
		m_pTexture = new Texture(*Obj.m_pTexture);	//テクスチャ
	}
	else
	{
		m_pTexture = nullptr;	//空アドレス代入
	}
	if (Obj.m_pCamera)	//ヌルチェック
	{	//TODO:臨時処置！子クラスの型で動的確保できるようにする
		m_pCamera = Obj.m_pCamera;	//カメラ
	}
	else
	{
		m_pCamera = nullptr;	//空アドレス代入
	}
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
C2dObject::~C2dObject()
{
	// =============== カウンタ ===================
	ms_nCnt2dObject--;			//自身の数カウント

	// =============== 解放 ===================
	SAFE_DELETE(m_pTexture);	//テクスチャ解放
	if (0 == ms_nCnt2dObject)	//静的確保物を解放するか
	{
		//SAFE_DELETE(ms_pVtx);		//頂点情報解放
		//SAFE_DELETE(ms_pIdx);		//頂点インデックス解放
		//SAFE_DELETE(ms_pVtxBuffer);	//頂点バッファ解放
		//SAFE_DELETE(ms_pIdxBuffer);	//インデックスバッファ解放
		SAFE_DELETE(ms_pCameraDef);		//疑似カメラ削除
		SAFE_DELETE(ms_pDefVs);			//頂点シェーダー削除
		SAFE_DELETE(ms_pDefPs);			//ピクセルシェーダー削除
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
void C2dObject::Update()
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
void C2dObject::Draw()
{
	// =============== 検査 ===================
	if (!m_pTextureLoad)	//ヌルチェック
	{
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error：";	//エラー箇所
		MessageBox(nullptr, (ErrorSpot + "テクスチャが登録されていません").c_str(), "Error", MB_OK | MB_ICONERROR);							//エラー通知
#endif
		return;	//処理中断
	}
	if (!m_pCamera)	//ヌルチェック
	{
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error：";	//エラー箇所
		MessageBox(nullptr, (ErrorSpot + "カメラが登録されていません").c_str(), "Error", MB_OK | MB_ICONERROR);							//エラー通知
#endif
		return;	//処理中断
	}

	// =============== 行列更新 ===================
	switch (m_eMode)	//描画状態分岐
	{
		// =============== 通常描画 ===================
	case E_DRAW_MODE_NORMAL:	//通常時
		m_aMatrix[E_MATRIX_WORLD] = m_Transform.GetWorldMatrixSRT();								//ワールド行列更新
		DirectX::XMStoreFloat4x4(&m_aMatrix[E_MATRIX_VIEW], DirectX::XMMatrixIdentity());			//ビュー行列：単位行列
		m_aMatrix[E_MATRIX_PROJECTION] = m_pCamera->GetProjectionMatrix(CCamera::E_DRAW_TYPE_2D);	//プロジェクション行列更新
		break;																						//分岐処理終了
		
		// =============== ビルボード描画 ===================
	case E_DRAW_MODE_BILLBOARD:	//ビルボード仕様
		m_aMatrix[E_MATRIX_WORLD] = m_Transform.GetWorldMatrixSRT(m_pCamera->GetInverseViewMatrix());	//ビルボードの行列変換
		m_aMatrix[E_MATRIX_VIEW] = m_pCamera->GetViewMatrix();											//ビュー行列更新
		m_aMatrix[E_MATRIX_PROJECTION] = m_pCamera->GetProjectionMatrix(CCamera::E_DRAW_TYPE_3D);		//プロジェクション行列更新
		break;																							//分岐処理終了
#if _DEBUG
		// =============== 例外 ===================
	default:	//上記以外
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error：";	//エラー箇所
		MessageBox(nullptr, (ErrorSpot + "想定外の描画法が指定されました").c_str(), "Error", MB_OK | MB_ICONERROR);							//エラー通知
		break;																																//分岐処理終了
#endif
	}

	// =============== 変数宣言 ===================
	float Param[8] = { m_Param.fUvOffset.x, m_Param.fUvOffset.y, m_Param.fUvScale.x, m_Param.fUvScale.y,
			m_Param.fColor.x, m_Param.fColor.y, m_Param.fColor.z, m_Param.fAlpha};	//定数バッファ書き込み用

	// =============== シェーダー使用 ===================
	m_pVs->WriteBuffer(0, m_aMatrix);	//定数バッファに行列情報書き込み
	m_pVs->WriteBuffer(1, &Param);		//定数バッファにUV情報書き込み
	m_pVs->Bind();						//頂点シェーダー使用
	m_pPs->SetTexture(0, m_pTextureLoad);	//テクスチャ登録
	m_pPs->Bind();						//ピクセルシェーダー使用

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
		// =============== 変数宣言 ===================
		DXGI_FORMAT Format;	//リソースデータフォーマット

		// =============== サイズ違い ===================
		switch (ms_unIdxSize)	//インデックスサイズ
		{
			// =============== int型=4バイト ===================
		case 4:	//intが4バイトの大きさ
			Format = DXGI_FORMAT_R32_UINT;	//1成分32ビット符号なし整数(unsigned int (新しいやつ))
			break;							//処理中断

			// =============== int型=2バイト ===================
		case 2:	//intが2バイトの大きさ
			Format = DXGI_FORMAT_R16_UINT;	//1成分16ビット符号なし整数(unsigned int (古いやつ))
			break;							//処理中断
#if _DEBUG
		// =============== 例外 ===================
		default:	//上記以外
			std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error：";	//エラー箇所
			MessageBox(nullptr, (ErrorSpot + "型のサイズがint型と一致しません").c_str(), "Error", MB_OK | MB_ICONERROR);							//エラー通知
			break;	//分岐処理終了
#endif
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
	描画方法セッタ関数
	-------------------------------------
	内容：描画方法登録
	-------------------------------------
	引数1：const E_DRAW_MODE & eMode：描画モード
	-------------------------------------
	戻値：なし
=========================================== */
void C2dObject::SetDrawMode(const E_DRAW_MODE & eMode)
{
	// =============== 格納 ===================
	m_eMode = eMode;	//描画モード格納
}

/* ========================================
	カメラセッタ関数
	-------------------------------------
	内容：カメラ登録
	-------------------------------------
	引数1：const CCamera* pCamera：自身を映すカメラ
	-------------------------------------
	戻値：なし
=========================================== */
void C2dObject::SetCamera(const CCamera* pCamera)
{
	// =============== 変数宣言 ===================
	int nCnt = 0;				//ループカウント用
	const CCamera* pCameraUse;	//カメラアドレス退避用

	// =============== 初期化 ===================
	if (pCamera)	//ヌルチェック
	{
		pCameraUse = pCamera;		//新規カメラ登録
	}
	else
	{
		pCameraUse = ms_pCameraDef;	//カメラ代用
	}

	// =============== カメラ登録 ===================
	m_pCamera = pCameraUse;	//カメラ登録
}

/* ========================================
	UVずれセッタ関数
	-------------------------------------
	内容：UVずれ登録
	-------------------------------------
	引数1：const TDiType<float> & fUvPos：新規uvずれ情報
	-------------------------------------
	戻値：なし
=========================================== */
void C2dObject::SetUvOffset(const TDiType<float> & fUvOffset)
{
	// =============== 格納 ===================
	m_Param.fUvOffset = fUvOffset;	//UVずれ情報格納
}

/* ========================================
	UV拡縮セッタ関数
	-------------------------------------
	内容：UV拡縮登録
	-------------------------------------
	引数1：const TDiType<float> & fUvPos：新規uv拡縮情報
	-------------------------------------
	戻値：なし
=========================================== */
void C2dObject::SetUvScale(const TDiType<float> & fUvScale)
{
	// =============== 格納 ===================
	m_Param.fUvScale = fUvScale;	//UV拡縮情報格納
}

/* ========================================
	色セッタ関数
	-------------------------------------
	内容：色情報登録
	-------------------------------------
	引数1：const TTriType<float> & fRGB：RGB情報
	引数2：const float & fAlpha：透明度
	-------------------------------------
	戻値：なし
=========================================== */
void C2dObject::SetColor(const TTriType<float> & fRGB, const float & fAlpha)
{
	// =============== 格納 ===================
	m_Param.fColor = fRGB;		//RGB情報格納
	m_Param.fAlpha = fAlpha;	//透明度情報格納
}

/* ========================================
	色セッタ関数
	-------------------------------------
	内容：色情報登録
	-------------------------------------
	引数1：const TTriType<float> & fRGB：RGB情報
	-------------------------------------
	戻値：なし
=========================================== */
void C2dObject::SetColor(const TTriType<float> & fRGB)
{
	// =============== 格納 ===================
	m_Param.fColor = fRGB;	//RGB情報格納
}

/* ========================================
	色セッタ関数
	-------------------------------------
	内容：色情報登録
	-------------------------------------
	引数1：const float & fColor：RGBA全てに登録する値
	-------------------------------------
	戻値：なし
=========================================== */
void C2dObject::SetColor(const float & fColor)
{
	// =============== 格納 ===================
	m_Param.fColor = 0.0f;	//RGB情報格納
	m_Param.fAlpha = 0.0f;	//透明度格納
}

/* ========================================
	透明度セッタ関数
	-------------------------------------
	内容：透明度情報登録
	-------------------------------------
	引数1：const float & fAlpha：透明度
	-------------------------------------
	戻値：なし
=========================================== */
void C2dObject::SetAlpha(const float & fAlpha)
{
	// =============== 格納 ===================
	m_Param.fAlpha = fAlpha;	//透明度格納
}


/* ========================================
	テクスチャセッタ関数
	-------------------------------------
	内容：テクスチャ作成・登録
	-------------------------------------
	引数1：const char* pcTexPass：テクスチャのパス
	-------------------------------------
	戻値：なし
=========================================== */
void C2dObject::SetTexture(const char* pcTexPass)
{
	// =============== 解放 ===================
	SAFE_DELETE(m_pTexture);	//テクスチャ解放

	// =============== 作成 ===================
	m_pTexture = new Texture;		//動的確保
	if (FAILED(m_pTexture->Create(pcTexPass)))	//新規テクスチャ登録
	{
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error：";	//エラー箇所
		MessageBox(nullptr, (ErrorSpot + "テクスチャの読み込みに失敗しました").c_str(), "Error", MB_OK | MB_ICONERROR);						//エラー通知
#endif
	}
	m_pTextureLoad = m_pTexture;	//アドレス格納
}

/* ========================================
	テクスチャセッタ関数
	-------------------------------------
	内容：テクスチャ登録
	-------------------------------------
	引数1：Textureポインタ
	-------------------------------------
	戻値：なし
=========================================== */
void C2dObject::SetTexture(Texture* pTexture)
{
	// =============== 登録 ===================
	m_pTextureLoad = pTexture;	//アドレス格納
}

/* ========================================
	頂点シェーダー関数
	-------------------------------------
	内容：頂点シェーダー登録
	-------------------------------------
	引数1：VertexShader* pVs：頂点シェーダーのポインタ
	-------------------------------------
	戻値：なし
=========================================== */
void C2dObject::SetVertexShader(VertexShader* pVs)
{
	// =============== ポインタ初期化 ===================
	m_pVs = pVs;	//ピクセルシェーダ登録
}

/* ========================================
	ピクセルシェーダー関数
	-------------------------------------
	内容：ピクセルシェーダー登録
	-------------------------------------
	引数1：PixelShader* pPs：ピクセルシェーダーのポインタ
	-------------------------------------
	戻値：なし
=========================================== */
void C2dObject::SetPixelShader(PixelShader* pPs)
{
	// =============== ポインタ初期化 ===================
	m_pPs = pPs;	//ピクセルシェーダ登録
}

/* ========================================
	頂点シェーダー作成関数
	-------------------------------------
	内容：頂点シェーダーのコンパイル
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void C2dObject::MakeVertexShader()
{
	// =============== 作成 ===================
	if (ms_pDefVs)	//ヌルチェック
	{
		SAFE_DELETE(ms_pDefVs);	//解放
	}
	ms_pDefVs = new VertexShader();	//動的確保
	ms_pDefVs->Compile(VS);			//コンパイル
}

/* ========================================
	ピクセルシェーダー作成関数
	-------------------------------------
	内容：ピクセルシェーダーのコンパイル
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void C2dObject::MakePixelShader()
{
	// =============== 作成 ===================
	if (ms_pDefPs)	//ヌルチェック
	{
		SAFE_DELETE(ms_pDefPs);	//解放
	}
	ms_pDefPs = new PixelShader();	//動的確保
	ms_pDefPs->Compile(PS);			//コンパイル
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
void C2dObject::Make()
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
	頂点バッファ作成関数
	-------------------------------------
	内容：インデックス情報からデータ作成
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void C2dObject::CreateVtxBuffer()
{
	// =============== バッファ情報設定 ===================
	D3D11_BUFFER_DESC BufDesc;							//バッファ情報
	ZeroMemory(&BufDesc, sizeof(BufDesc));				//中身を全て0で初期化
	BufDesc.ByteWidth = ms_unVtxSize * ms_unVtxCount;	//バッファの大きさ
	BufDesc.Usage = D3D11_USAGE_DEFAULT;				//メモリ上での管理方法
	BufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;		//GPU上での利用方法

	// =============== バッファ初期データ設定 ===================
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
void C2dObject::CreateIdxBuffer()
{
	// =============== インデックスサイズの確認 ===================
	switch (ms_unIdxSize)
	{
		// =============== int型=4バイト ===================
	case 4:	//intが4バイトの大きさ
		break;							//処理中断

		// =============== int型=2バイト ===================
	case 2:	//intが2バイトの大きさ
		break;							//処理中断

		// =============== 例外 ===================
		default:	//上記以外
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error：";	//エラー箇所
		MessageBox(nullptr, (ErrorSpot + "型のサイズがint型と一致しません").c_str(), "Error", MB_OK | MB_ICONERROR);						//エラー通知
#endif
		return;	//処理中断
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