/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	平面ポリゴン実装
	------------------------------------
	2dPolygon.cpp
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/11/21 作成 takagi
	・2023/11/22 メッシュサイズを1x1に修正 takagi
	・2023/11/28 TextureSet関数にポインタ指定できる物を追加
	・2023/12/01 テクスチャの扱い方を安全化 takagi
	・2023/12/04 デストラクタの削除対象を修正 takagi
	・2023/12/05 描画のモード追加 takagi
	・2023/12/10 静的確保されたものの削除のタイミングを修正 takagi
	・2023/12/15 空の更新関数追加・警告文追加・改修
					・コンストラクタでカメラが作られない問題修正 takagi
	・2023/12/17 引数参照化 takagi
	・2023/12/20 ビルボードの処理修正 takagi

========================================== */

// =============== デバッグモード ===================
#if _DEBUG
#define USE_2D_POLYGON (true)	//フェード試運転
#endif

// =============== インクルード ===================
#include "2dPolygon.h"	//自身のヘッダ
#include "CameraDef.h"	//疑似カメラ

#if _DEBUG
#include <Windows.h>	//メッセージボックス用
#endif

// =============== 定数定義 =====================
const TPos3d<float> INIT_POS(640.0f, 360.0f, 0.0f);	//位置初期化
const TTriType<float> INIT_SCALE(1.0f, 1.0f, 0.0f);	//初期拡縮
const TTriType<float> INIT_RADIAN(0.0f);			//初期回転
const int FRAME_MIN(0);								//フェード時間の最小
const int FRAME_TURNING_1(50);						//拡縮反転１反転
const int FRAME_TURNING_2(100);						//拡縮反転２反転
const int FRAME_MAX(150);							//フェード時間の最大
const float SCALE_MIN(0.0f);						//最小サイズ
const float SCALE_TURNINIG_2(30.0f);				//サイズ反転２反転
const float SCALE_TURNINIG_1(100.0f);				//サイズ反転１反転
const float SCALE_MAX(1000.0f);						//最大サイズ
const float ROTATE_ACCEL_RATE(4.0f);				//角速度増加割合
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
})EOT";	//頂点シェーダーコンパイル対象
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
})EOT";	//ピクセルシェーダーコンパイル対象

// =============== グローバル変数宣言 =====================
int C2dPolygon::ms_nCnt2dPolygon;								//自身の生成数
const void* C2dPolygon::ms_pVtx = nullptr;						//頂点情報
unsigned int C2dPolygon::ms_unVtxSize;							//頂点サイズ
unsigned int C2dPolygon::ms_unVtxCount;							//頂点数
const void* C2dPolygon::ms_pIdx = nullptr;						//頂点のインデックス
unsigned int C2dPolygon::ms_unIdxSize;							//インデックスサイズ
unsigned int C2dPolygon::ms_unIdxCount;							//インデックス数
ID3D11Buffer* C2dPolygon::ms_pVtxBuffer = nullptr;				//頂点バッファ
ID3D11Buffer* C2dPolygon::ms_pIdxBuffer = nullptr;				//インデックスバッファ 
VertexShader* C2dPolygon::ms_pDefVs;							//頂点シェーダー
PixelShader* C2dPolygon::ms_pDefPs;								//ピクセルシェーダー
const CCamera* C2dPolygon::ms_pCameraDef;						//疑似カメラ

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：生成時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
C2dPolygon::C2dPolygon()
	:m_Transform(INIT_POS, INIT_SCALE, INIT_RADIAN)	//ワールド座標
	,m_Param{{0.0f}, {1.0f, 1.0f}, {1.0f}, 1.0f}	//シェーダーに書き込む情報
	,m_pVs(nullptr)									//頂点シェーダー
	,m_pPs(nullptr)									//ピクセルシェーダー
	,m_pTexture(nullptr)							//テクスチャ
	,m_pTextureLoad(nullptr)						//テクスチャアドレス格納専用
	,m_pCamera(nullptr)								//カメラ
{
	// =============== 静的作成 ===================
	if (0 == ms_nCnt2dPolygon)	//現在、他にこのクラスが作成されていない時
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
	m_aMatrix[0] = m_Transform.GetWorldMatrixSRT();							//ワールド行列
	DirectX::XMStoreFloat4x4(&m_aMatrix[1], DirectX::XMMatrixIdentity());	//ビュー行列：単位行列
	DirectX::XMStoreFloat4x4(&m_aMatrix[2], DirectX::XMMatrixIdentity());	//プロジェクション行列

	// =============== カウンタ ===================
	ms_nCnt2dPolygon++;	//自身の数カウント
}

/* ========================================
	コピーコンストラクタ関数
	-------------------------------------
	内容：コピー時に行う処理
	-------------------------------------
	引数1：const C2dPolygon & Obj：コピー元の参照
	-------------------------------------
	戻値：なし
=========================================== */
C2dPolygon::C2dPolygon(const C2dPolygon & Obj)
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
C2dPolygon::~C2dPolygon()
{
	// =============== カウンタ ===================
	ms_nCnt2dPolygon--;			//自身の数カウント

	// =============== 解放 ===================
	SAFE_DELETE(m_pTexture);	//テクスチャ解放
	//SAFE_DELETE(ms_pVtx);		//頂点情報解放
	//SAFE_DELETE(ms_pIdx);		//頂点インデックス解放
	//SAFE_DELETE(ms_pVtxBuffer);	//頂点バッファ解放
	//SAFE_DELETE(ms_pIdxBuffer);	//インデックスバッファ解放
	if (0 == ms_nCnt2dPolygon)	//静的確保物を解放するか
	{
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
void C2dPolygon::Update()
{
}

/* ========================================
	描画関数
	-------------------------------------
	内容：描画処理
	-------------------------------------
	引数1：const E_DRAW_MODE & eMode：描画モード
	-------------------------------------
	戻値：なし
=========================================== */
void C2dPolygon::Draw(const E_DRAW_MODE & eMode)
{
	// =============== 検査 ===================
	if (!m_pTextureLoad)	//ヌルチェック
	{
#if _DEBUG
		std::string ErrorSpot = typeid(*this).name(); ErrorSpot += "->Error";				//エラー箇所
		MessageBox(nullptr, "テクスチャが登録されていません", ErrorSpot.c_str(), MB_OK);	//エラー通知
#endif
		return;	//処理中断
	}
	if (!m_pCamera)	//ヌルチェック
	{
#if _DEBUG
		std::string ErrorSpot = typeid(*this).name(); ErrorSpot += "->Error";				//エラー箇所
		MessageBox(nullptr, "カメラが登録されていません", ErrorSpot.c_str(), MB_OK);	//エラー通知
#endif
		return;	//処理中断
	}

	// =============== 行列更新 ===================
	switch (eMode)
	{
		// =============== 通常描画 ===================
	case E_DRAW_MODE_NORMAL:	//通常時
		m_aMatrix[0] = m_Transform.GetWorldMatrixSRT();	//ワールド行列更新
		DirectX::XMStoreFloat4x4(&m_aMatrix[1], DirectX::XMMatrixIdentity());	//ビュー行列：単位行列
		m_aMatrix[2] = m_pCamera->GetProjectionMatrix(CCamera::E_DRAW_TYPE_2D);	//プロジェクション行列更新
		break;											//分岐処理終了
		
		// =============== ビルボード描画 ===================
	case E_DRAW_MODE_BILLBOARD:	//ビルボード仕様
		m_aMatrix[0] = m_Transform.GetWorldMatrixSRT(m_pCamera->GetInverseViewMatrix());	//ビルボードの行列変換
		m_aMatrix[1] = m_pCamera->GetViewMatrix();
		m_aMatrix[2] = m_pCamera->GetProjectionMatrix(CCamera::E_DRAW_TYPE_3D);	//プロジェクション行列更新
		break;																				//分岐処理終了
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
	カメラセッタ関数
	-------------------------------------
	内容：カメラ登録
	-------------------------------------
	引数1：const CCamera* pCamera：自身を映すカメラ
	-------------------------------------
	戻値：なし
=========================================== */
void C2dPolygon::SetCamera(const CCamera* pCamera)
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
	位置セッタ関数
	-------------------------------------
	内容：位置登録
	-------------------------------------
	引数1：const TPos3d<float> & fPos：新規位置情報
	-------------------------------------
	戻値：なし
=========================================== */
void C2dPolygon::SetPos(const TPos3d<float> & fPos)
{
	// =============== 格納 ===================
	m_Transform.fPos = fPos;	//位置情報格納
}

/* ========================================
	大きさセッタ関数
	-------------------------------------
	内容：大きさ登録
	-------------------------------------
	引数1：const TTriType<float> & fScale：新規拡縮情報
	-------------------------------------
	戻値：なし
=========================================== */
void C2dPolygon::SetSize(const TTriType<float> & fScale)
{
	// =============== 格納 ===================
	m_Transform.fScale = fScale;	//拡縮格納
}

/* ========================================
	回転セッタ関数
	-------------------------------------
	内容：回転登録
	-------------------------------------
	引数1：const TTriType<float> & fRotate：新規回転情報
	-------------------------------------
	戻値：なし
=========================================== */
void C2dPolygon::SetRotate(const TTriType<float> & fRotate)
{
	// =============== 格納 ===================
	m_Transform.fRadian = fRotate;	//回転格納
}

/* ========================================
	ワールド行列セッタ関数
	-------------------------------------
	内容：ワールド行列登録
	-------------------------------------
	引数1：const TPos3d<float> & fPos：新規ワールド系情報
	-------------------------------------
	戻値：なし
=========================================== */
void C2dPolygon::SetTransform(const tagTransform3d & Transform)
{
	// =============== 格納 ===================
	m_Transform = Transform;	//ワールド行列格納
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
void C2dPolygon::SetUvOffset(const TDiType<float> & fUvOffset)
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
void C2dPolygon::SetUvScale(const TDiType<float> & fUvScale)
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
void C2dPolygon::SetColor(const TTriType<float> & fRGB, const float & fAlpha)
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
void C2dPolygon::SetColor(const TTriType<float> & fRGB)
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
void C2dPolygon::SetColor(const float & fColor)
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
void C2dPolygon::SetAlpha(const float & fAlpha)
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
void C2dPolygon::SetTexture(const char* pcTexPass)
{
	// =============== 解放 ===================
	SAFE_DELETE(m_pTexture);	//テクスチャ解放

	// =============== 作成 ===================
	m_pTexture = new Texture;		//動的確保
#if _DEBUG
	if (FAILED(m_pTexture->Create(pcTexPass)))	//新規テクスチャ登録
	{
		std::string ErrorSpot = typeid(*this).name(); ErrorSpot += "->Error";					//エラー箇所
		MessageBox(nullptr, "テクスチャの読み込みに失敗しました", ErrorSpot.c_str(), MB_OK);	//エラー通知
	}
#else
	m_pTexture->Create(pcTexPass);	//新規テクスチャ登録
#endif
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
void C2dPolygon::SetTexture(Texture* pTexture)
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
void C2dPolygon::SetVertexShader(VertexShader* pVs)
{
	//ポインタ初期化
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
void C2dPolygon::SetPixelShader(PixelShader* pPs)
{
	//ポインタ初期化
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
void C2dPolygon::MakeVertexShader()
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
void C2dPolygon::MakePixelShader()
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
void C2dPolygon::Make()
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
void C2dPolygon::CreateVtxBuffer()
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
void C2dPolygon::CreateIdxBuffer()
{
	// =============== インデックスサイズの確認 ===================
	switch (ms_unIdxSize)
	{
		// =============== サイズ違い ===================
	default:	//下記以外
#if _DEBUG
		MessageBox(nullptr, "型のサイズがint型と一致しません", "2dPolygon.cpp->Error", MB_OK);	//エラー通知
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