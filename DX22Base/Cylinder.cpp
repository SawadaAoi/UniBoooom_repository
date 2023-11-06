/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   円柱実装
   ---------------------------------------
   Cylinder.cpp

   作成者	takagi

   変更履歴
   ・2023/11/05 制作 takagi
   ・2023/11/06 コンストラクタ改修 takagi

   ======================================== */



// =============== インクルード ===================
#include "Cylinder.h"	//自身のヘッダ

// =============== 定数定義 ===================
const float CYLINDER_RADIUS = 0.5f;
const float CYLINDER_HEIGHT = 2.0f;
const int CORNER_NUM = 8;
const int VTX_TOP_SURFACE = CORNER_NUM;
const int VTX_BOTTOM_SURFACE = VTX_TOP_SURFACE;
const int VTX_CIRCLE = VTX_TOP_SURFACE + VTX_BOTTOM_SURFACE;
const int VTX_SIDE_SURFACE = VTX_TOP_SURFACE + VTX_BOTTOM_SURFACE + 2;
const int SURFACE_TOP = CORNER_NUM - 2;
const int SURFACE_BOTTOM = CORNER_NUM - 2;
const int SURFACE_SIDE = CORNER_NUM * 2;
const int SURFACE_CYLINDER_NUM = SURFACE_TOP + SURFACE_BOTTOM + SURFACE_SIDE;



/* ========================================
   関数：コンストラクタ
   ----------------------------------------
   内容：生成時に行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
CCylinder::CCylinder()
{
	// =============== 頂点の作成 ===================
	// 天面、底面
	Vertex vtx[CORNER_NUM + VTX_BOTTOM_SURFACE + VTX_SIDE_SURFACE];
	float angle = 0.0f;
	float radian;
	float posX;
	float posY;
	float posZ;
	float u, v;

	for (int i = 0; i < VTX_TOP_SURFACE; i++)
	{
		angle = i * (360 / CORNER_NUM);
		radian = DirectX::XMConvertToRadians(angle);
		posX = sin(radian) * CYLINDER_RADIUS;
		posY = CYLINDER_HEIGHT / 2;
		posZ = cos(radian) * CYLINDER_RADIUS;
		u = (posX / CYLINDER_RADIUS) + 0.5f;
		v = -(posZ / CYLINDER_RADIUS) + 0.5f;

		vtx[i] = { {posX,posY,posZ},{u,v} };
	}

	for (int i = 0; i < VTX_BOTTOM_SURFACE; i++)
	{
		angle = i * (360 / CORNER_NUM);
		radian = DirectX::XMConvertToRadians(angle);
		posX = sin(radian) * CYLINDER_RADIUS;
		posY = -CYLINDER_HEIGHT / 2;
		posZ = cos(radian) * CYLINDER_RADIUS;
		u = (posX / CYLINDER_RADIUS) + 0.5f;
		v = -(posZ / CYLINDER_RADIUS) + 0.5f;

		vtx[VTX_TOP_SURFACE + i] = { {posX,posY,posZ},{u,v} };
	}

	// 側面

	//TOOD==>u,vの調整

	for (int i = 0; i < VTX_SIDE_SURFACE; i++)
	{
		if (i < VTX_SIDE_SURFACE / 2)
		{
			angle = (i % (VTX_SIDE_SURFACE / 2)) * (360 / CORNER_NUM);
			radian = DirectX::XMConvertToRadians(angle);
			posX = sin(radian) * CYLINDER_RADIUS;
			posY = CYLINDER_HEIGHT / 2;
			posZ = cos(radian) * CYLINDER_RADIUS;
			u = 1.0f / CORNER_NUM * (i % (VTX_SIDE_SURFACE / 2));
			v = 0.5f + -(posY / CYLINDER_HEIGHT);

			vtx[VTX_TOP_SURFACE + VTX_BOTTOM_SURFACE + i] = { {posX,posY,posZ},{u,v} };
		}
		else
		{
			angle = (i % (VTX_SIDE_SURFACE / 2)) * (360 / CORNER_NUM);
			radian = DirectX::XMConvertToRadians(angle);
			posX = sin(radian) * CYLINDER_RADIUS;
			posY = -CYLINDER_HEIGHT / 2;
			posZ = cos(radian) * CYLINDER_RADIUS;
			u = 1.0f / CORNER_NUM * (i % (VTX_SIDE_SURFACE / 2));
			v = 0.5f + -(posY / CYLINDER_HEIGHT);

			vtx[VTX_TOP_SURFACE + VTX_BOTTOM_SURFACE + i] = { {posX,posY,posZ},{u,v} };
		}
	}

	// =============== インデックスの作成 ===================
	// 天面
	int idx[SURFACE_CYLINDER_NUM * 3];

	for (int i = 0; i < SURFACE_TOP; i++)
	{
		idx[i * 3] = 0;
		idx[i * 3 + 1] = i + 1;
		idx[i * 3 + 2] = i + 2;
	}
	// 底面
	for (int i = 0; i < SURFACE_BOTTOM; i++)
	{
		idx[(SURFACE_TOP * 3) + i * 3] = VTX_TOP_SURFACE;
		idx[(SURFACE_TOP * 3) + i * 3 + 1] = VTX_TOP_SURFACE + i + 2;
		idx[(SURFACE_TOP * 3) + i * 3 + 2] = VTX_TOP_SURFACE + i + 1;
	}
	// 側面
	for (int i = 0; i < SURFACE_SIDE / 2; i++)
	{
		idx[((SURFACE_TOP + SURFACE_BOTTOM) * 3) + (6 * i)] = VTX_CIRCLE + i;
		idx[((SURFACE_TOP + SURFACE_BOTTOM) * 3) + (6 * i) + 1] = VTX_CIRCLE + (VTX_SIDE_SURFACE / 2) + i;
		idx[((SURFACE_TOP + SURFACE_BOTTOM) * 3) + (6 * i) + 2] = VTX_CIRCLE + i + 1;
		idx[((SURFACE_TOP + SURFACE_BOTTOM) * 3) + (6 * i) + 3] = VTX_CIRCLE + i + 1;
		idx[((SURFACE_TOP + SURFACE_BOTTOM) * 3) + (6 * i) + 4] = VTX_CIRCLE + (VTX_SIDE_SURFACE / 2) + i;
		idx[((SURFACE_TOP + SURFACE_BOTTOM) * 3) + (6 * i) + 5] = VTX_CIRCLE + (VTX_SIDE_SURFACE / 2) + i + 1;
	}

	// =============== バッファの作成 ===================
	MeshBuffer::Description desc = {};
	desc.pVtx = vtx;
	desc.vtxCount = _countof(vtx);					// 頂点の数
	desc.vtxSize = sizeof(vtx[0]);	// 頂点一つあたりのデータサイズ
	desc.pIdx = idx;
	desc.idxCount = _countof(idx);					// インデックスの数
	desc.idxSize = sizeof(int);			// インデックス一つあたりのデータサイズ
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
	m_pObj = new MeshBuffer(desc);
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
CCylinder::CCylinder(CCylinder & Obj)
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
CCylinder::~CCylinder()
{
}

/* ========================================
   関数：描画関数
   ----------------------------------------
   内容：描画処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
void CCylinder::Draw()
{
	// =============== 検査 ===============
	if (m_pObj == nullptr)	//ヌルチェック
	{
		// =============== 終了 ===============
		return;	//処理終了
	}

	// =============== 描画 ===============
	m_pVS->WriteBuffer(0, m_WVP);	//書き込み
	m_pVS->Bind();					//頂点シェーダ使用
	m_pPS->Bind();					//ピクセルシェーダ使用
	m_pObj->Draw();					//立方体描画
}