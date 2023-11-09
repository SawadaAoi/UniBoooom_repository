/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   直線実装
   ---------------------------------------
   Line.cpp

   作成者	takagi

   変更履歴
   ・↓まで 学校の配布物(授業に沿い変形)
   ・2023/11/05 ファイル分割・抽象クラス化・コメント付与 takagi

   ======================================== */



// =============== インクルード ===================
#include "Line.h"	//自身のヘッダ
#include "Defines.h"

// =============== グローバル変数定義 =============
MeshBuffer* CLine::m_pLines;
DirectX::XMFLOAT4X4 CLine::m_WVP[3];	//各座標系における行列
Shader* CLine::m_pVS;					//頂点シェーダ(共有)
Shader* CLine::m_pPS;					//ピクセルシェーダ(共有)
void* CLine::m_pLineVtx;
int CLine::m_lineCnt = 0;



/* ========================================
   関数：コンストラクタ
   ----------------------------------------
   内容：生成時に行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
void CLine::Init()
{
	MakeShader();
	Make();

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
   引数：CLine & Obj：コピー元
   ----------------------------------------
   戻値：なし
   ======================================== */
CLine::CLine(CLine & Obj)
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
CLine::~CLine()
{
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
void CLine::MakeShader()
{
	// =============== 作成 ===============
	MakeVS();	//頂点シェーダ作成
	MakePS();	//ピクセルシェーダ作成
}

/* ========================================
   関数：終了関数
   ----------------------------------------
   内容：終了処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
void CLine::Uninit()
{
	// =============== 終了 ===============
	SAFE_DELETE_ARRAY(m_pLineVtx);
	SAFE_DELETE(m_pPS);
	SAFE_DELETE(m_pVS);
	SAFE_DELETE(m_pLines);
}

/* ========================================
   関数：ワールド行列登録関数
   ----------------------------------------
   内容：ワールド行列を受け取り、格納する
   ----------------------------------------
   引数：ワールド行列(XMFLOAT4X4)
   ----------------------------------------
   戻値：なし
   ======================================== */
void CLine::SetWorld(DirectX::XMFLOAT4X4 World)
{
	// =============== 代入 ===============
	m_WVP[E_MATRIX_WORLD] = World;	//ワールド行列代入
}

/* ========================================
   関数：ビュー行列登録関数
   ----------------------------------------
   内容：ビュー行列を受け取り、格納する
   ----------------------------------------
   引数：ビュー行列(XMFLOAT4X4)
   ----------------------------------------
   戻値：なし
   ======================================== */
void CLine::SetView(DirectX::XMFLOAT4X4 View)
{
	// =============== 代入 ===============
	m_WVP[E_MATRIX_VIEW] = View;	//ビュー行列代入
}

/* ========================================
   関数：プロジェクション行列登録関数
   ----------------------------------------
   内容：プロジェクション行列を受け取り、格納する
   ----------------------------------------
   引数：プロジェクション行列(XMFLOAT4X4)
   ----------------------------------------
   戻値：なし
   ======================================== */
void CLine::SetProjection(DirectX::XMFLOAT4X4 Proj)
{
	// =============== 代入 ===============
	m_WVP[E_MATRIX_PROJECTION] = Proj;	//プロジェクション行列代入
}


void CLine::Add(DirectX::XMFLOAT3 start, DirectX::XMFLOAT3 end, DirectX::XMFLOAT4 color)
{
	if (m_lineCnt < MAX_LINE_NUM)
	{
		LineVertex* pVtx = reinterpret_cast<LineVertex*>(m_pLineVtx);
		pVtx[m_lineCnt * 2 + 0] = { start.x, start.y, start.z, color.x, color.y, color.z, color.w };
		pVtx[m_lineCnt * 2 + 1] = { end.x, end.y, end.z, color.x , color.y, color.z, color.w
		};
		++m_lineCnt;
	}
}

/* ========================================
	描画処理関数
	-------------------------------------
	内容：描画処理
	-------------------------------------
	引数：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CLine::Draw()
{
	// =============== 検査 ===============
	//if (m_pLines == nullptr)	//ヌルチェック
	//{
	//	// =============== 終了 ===============
	//	return;	//処理終了
	//}

	// =============== 描画 ===============
	m_pVS->WriteBuffer(0, m_WVP);	//書き込み
	m_pVS->Bind();					//頂点シェーダ使用
	m_pPS->Bind();					//ピクセルシェーダ使用
	m_pLines->Write(m_pLineVtx);	//書き込み
	m_pLines->Draw(m_lineCnt * 2);	//立方体描画
	m_lineCnt = 0;					//未描画数0
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
void CLine::MakeVS()
{
	const char* VSCode = R"EOT(
struct VS_IN {
	float3 pos : POSITION0;
	float4 color : COLOR0;
};
struct VS_OUT {
	float4 pos : SV_POSITION;
	float4 color : COLOR0;
};
cbuffer Matrix : register(b0) {
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};
VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos = mul(vout.pos, view);
	vout.pos = mul(vout.pos, proj);
	vout.color = vin.color;
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
void CLine::MakePS()
{

	const char* PSCode = R"EOT(
struct PS_IN {
	float4 pos : SV_POSITION;
	float4 color : COLOR0;
};
float4 main(PS_IN pin) : SV_TARGET0 {
	return pin.color;
})EOT";

	m_pPS = new PixelShader();
	m_pPS->Compile(PSCode);
}

void CLine::Make()
{
	m_pLineVtx = new LineVertex[MAX_LINE_NUM * 2];
	m_lineCnt = 0;
	MeshBuffer::Description desc = {};
	desc.pVtx = m_pLineVtx;
	desc.vtxCount = MAX_LINE_NUM * 2;
	desc.vtxSize = sizeof(LineVertex);
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
	desc.isWrite = true;
	m_pLines = new MeshBuffer(desc);
}