/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   空間における形状の抽象クラス実装
   ---------------------------------------
   Geometry.cpp

   作成者	takagi

   変更履歴
   ・↓まで 学校の配布物(授業に沿い変形)
   ・2023/11/05 ファイル分割・抽象クラス化・コメント付与 takagi
   ・2023/11/10 Uninit削除(内容はデストラクタへ移動) takagi

   ======================================== */



// =============== インクルード ===================
#include "Geometry.h"	//自身のヘッダ
#include "Defines.h"

// =============== グローバル変数定義 =============
//MeshBuffer* CGeometry::m_pLines;
Shader* CGeometry::m_pVS;					//頂点シェーダ(共有)
Shader* CGeometry::m_pPS;					//ピクセルシェーダ(共有)



/* ========================================
   関数：コンストラクタ
   ----------------------------------------
   内容：生成時に行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
CGeometry::CGeometry()
{
	for (int i = 0; i < 3; ++i)
		DirectX::XMStoreFloat4x4(&m_WVP[i], DirectX::XMMatrixIdentity());

	// ジオメトリ用カメラ初期化
	DirectX::XMFLOAT4X4 mat[2];
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(
		DirectX::XMMatrixLookAtLH(
			DirectX::XMVectorSet(1.5f, 2.5f, -3.0f, 0.0f),
			DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
			DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
		)));
	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixTranspose(
		DirectX::XMMatrixPerspectiveFovLH(
			DirectX::XMConvertToRadians(60.0f), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f)
	));
	SetView(mat[0]);
	SetProjection(mat[1]);
}

/* ========================================
   関数：コピーコンストラクタ
   ----------------------------------------
   内容：複製時に行う処理
   ----------------------------------------
   引数：CGeometry & Obj：コピー元
   ----------------------------------------
   戻値：なし
   ======================================== */
CGeometry::CGeometry(CGeometry & Obj)
{
}

/* ========================================
   関数：デストラクタ
   ----------------------------------------
   内容：破棄時に行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
CGeometry::~CGeometry()
{
	// =============== 終了 ===============
	SAFE_DELETE(m_pPS);
	SAFE_DELETE(m_pVS);
	if (m_pObj)	//ヌルチェック
	{
		delete m_pObj;		//メモリ解放
		m_pObj = nullptr;	//空アドレス代入
	}
}

/* ========================================
   関数：シェーダ作成関数
   ----------------------------------------
   内容：シェーダを作って読み込む
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
void CGeometry::MakeShader()
{
	// =============== 作成 ===============
	MakeVS();	//頂点シェーダ作成
	MakePS();	//ピクセルシェーダ作成
}

/* ========================================
   関数：ワールド行列登録関数
   ----------------------------------------
   内容：ワールド行列を受け取り、格納する
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
void CGeometry::SetWorld(DirectX::XMFLOAT4X4 World)
{
	// =============== 代入 ===============
	m_WVP[E_MATRIX_WORLD] = World;	//ワールド行列代入
}

/* ========================================
   関数：ビュー行列登録関数
   ----------------------------------------
   内容：ビュー行列を受け取り、格納する
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
void CGeometry::SetView(DirectX::XMFLOAT4X4 View)
{
	// =============== 代入 ===============
	m_WVP[E_MATRIX_VIEW] = View;	//ビュー行列代入
}

/* ========================================
   関数：プロジェクション行列登録関数
   ----------------------------------------
   内容：プロジェクション行列を受け取り、格納する
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
void CGeometry::SetProjection(DirectX::XMFLOAT4X4 Proj)
{
	// =============== 代入 ===============
	m_WVP[E_MATRIX_PROJECTION] = Proj;	//プロジェクション行列代入
}

/* ========================================
   関数：頂点シェーダ作成関数
   ----------------------------------------
   内容：頂点シェーダを作って読み込む
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
void CGeometry::MakeVS()
{
	const char* VSCode = R"EOT(
struct VS_IN {
	float3 pos : POSITION0;
	float2 uv : TEXCOORD0;
};
struct VS_OUT {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};
cbuffer Matrix : register(b0) {
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};
VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos = mul(vout.pos, world);
	vout.pos = mul(vout.pos, view);
	vout.pos = mul(vout.pos, proj);
	vout.uv = vin.uv;
	return vout;
})EOT";

	m_pVS = new VertexShader();
	m_pVS->Compile(VSCode);
}

/* ========================================
   関数：ピクセルシェーダ作成関数
   ----------------------------------------
   内容：ピクセルシェーダを作って読み込む
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
void CGeometry::MakePS()
{
#ifdef _DEBUG
	const char* PSCode = R"EOT(
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};
float4 main(PS_IN pin) : SV_TARGET0 {
	float4 color = float4(1,1,1,1);
	float2 halfGrid = floor(abs(pin.uv) * 2.0f);
	float2 quatGrid = floor(abs(pin.uv) * 8.0f);

	float half = fmod(halfGrid.x + halfGrid.y, 2.0f);
	float quat = fmod(quatGrid.x + quatGrid.y, 2.0f);

	color.rgb = ((half * 0.1f) * quat + 0.45f) + (1 - quat) * 0.05f;
	return color;
})EOT";
#else
	const char* PSCode = R"EOT(
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};
float4 main(PS_IN pin) : SV_TARGET0 {
	return float4(1.0f, 0.0f, 1.0f, 1.0f);
})EOT";
#endif

	m_pPS = new PixelShader();
	m_pPS->Compile(PSCode);
}