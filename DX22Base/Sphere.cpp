/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   球実装
   ---------------------------------------
   Sphere.cpp

   作成者	takagi

   変更履歴
   ・2023/11/05 制作 takagi
   ・2023/11/06 コンストラクタ改修 takagi

   ======================================== */



// =============== インクルード ===================
#include "Sphere.h"	//自身のヘッダ

// =============== 定数定義 ===================
const int VTX_SPHERE_X_NUM = 18;	//頂点の横列の数
const int VTX_SPHERE_Y_NUM = 18;	//頂点の縦列の数
const int VTX_NUM = VTX_SPHERE_X_NUM * VTX_SPHERE_Y_NUM;	//頂点の総数
const int SURFACE_SPHERE_X_NUM = VTX_SPHERE_X_NUM - 1;	//横列の表面の数(四角形)
const int SURFACE_SPHERE_Y_NUM = VTX_SPHERE_Y_NUM - 1;	//縦列の表面の数(四角形)
const int SURFACE_SPHERE_NUM = SURFACE_SPHERE_X_NUM * SURFACE_SPHERE_Y_NUM;	//表面の総数(四角形)
const float SPHERE_DIAMETER = 1.0f;	//円の直径
const float SPHERE_RADIUS = SPHERE_DIAMETER / 2;	//円の半径



/* ========================================
   関数：コンストラクタ
   ----------------------------------------
   内容：生成時に行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
CSphere::CSphere()
{
	// =============== 頂点の作成 ===================
	Vertex vtx[VTX_NUM];
	float angle_XY = 0.0f;	//XY面の角度
	float angle_XZ = 0.0f;	//XZ面の角度
	float radian_XY;	//XY面のラジアン角
	float radian_XZ;	//XZ面のラジアン角
	float posX, posY, posZ;	//頂点のX,Y､Z座標
	float Rate_XZ;		//XZの座標をY座標によって調整する数
	float u, v;			//テクスチャを貼り付けるuv座標	※uが横、vが縦

	for (int i = 0; i < VTX_SPHERE_Y_NUM; i++)	//頂点の縦列の繰り返し
	{
		radian_XY = DirectX::XMConvertToRadians(angle_XY);
		posY = cosf(radian_XY) * SPHERE_RADIUS;		//XY面のラジアン角からY座標を割り出す
		Rate_XZ = sin(radian_XY);	//球体の1番大きい状態を1.0としたときのY座標に応じた円周の割合

		for (int j = 0; j < VTX_SPHERE_X_NUM; j++)	//頂点の横列の繰り返し
		{
			radian_XZ = DirectX::XMConvertToRadians(angle_XZ);	//XZ面のディグリー角をラジアン角に変換
			posX = sinf(radian_XZ) * Rate_XZ * SPHERE_RADIUS;		//XZ面のX座標を出してからY座標に応じて調整
			posZ = cosf(radian_XZ) * Rate_XZ * SPHERE_RADIUS;		//XZ面のZ座標を出してからY座標に応じて調整
			u = (1.0f / SURFACE_SPHERE_X_NUM) * j;			//面の数をで等分して0.0f,・・・,1.0fの数になる
			v = 0.5f - (posY / SPHERE_DIAMETER);	//Y座標を直径で割り-0.5f～0.5fに直してから0.0f～1.0fに調整

			vtx[i * VTX_SPHERE_X_NUM + j] = { {posX,posY,posZ},{u, v} };	//出した変数をvtxに入れる
			angle_XZ += 360.0f / SURFACE_SPHERE_X_NUM;	//XZ面の角度を面の数で等分した数だけ進める
		}
		angle_XY += 180.0f / SURFACE_SPHERE_Y_NUM;	//sinは0°～180°で0.0～1.0fになるため
		angle_XZ = 0;	//XZが360を超えないように調整
	}

	// =============== インデックスの作成 ===================
	int idx[SURFACE_SPHERE_NUM * 2 * 3];
	for (int i = 0; i < SURFACE_SPHERE_Y_NUM; i++)	//縦列の繰り返し
	{
		for (int j = 0; j < SURFACE_SPHERE_X_NUM; j++)	//横列の繰り返し
		{
			//VTX_SPHERE_X_NUMが9の場合{0,9,1,1,10,9,・・・}となる
			idx[(i * (6 * SURFACE_SPHERE_X_NUM)) + (j * 6)] = i * VTX_SPHERE_X_NUM + j;
			idx[(i * (6 * SURFACE_SPHERE_X_NUM)) + (j * 6) + 1] = i * VTX_SPHERE_X_NUM + VTX_SPHERE_X_NUM + j;
			idx[(i * (6 * SURFACE_SPHERE_X_NUM)) + (j * 6) + 2] = i * VTX_SPHERE_X_NUM + 1 + j;
			idx[(i * (6 * SURFACE_SPHERE_X_NUM)) + (j * 6) + 3] = i * VTX_SPHERE_X_NUM + 1 + j;
			idx[(i * (6 * SURFACE_SPHERE_X_NUM)) + (j * 6) + 4] = i * VTX_SPHERE_X_NUM + VTX_SPHERE_X_NUM + j;
			idx[(i * (6 * SURFACE_SPHERE_X_NUM)) + (j * 6) + 5] = i * VTX_SPHERE_X_NUM + VTX_SPHERE_X_NUM + 1 + j;
		}
	}

	// =============== バッファの作成 ===================
	MeshBuffer::Description desc = {};
	desc.pVtx = vtx;
	desc.vtxCount = _countof(vtx);					// 頂点の数
	desc.vtxSize = sizeof(vtx[0]);	// 頂点一つあたりのデータサイズ
	desc.pIdx = idx;
	desc.idxCount = _countof(idx);					// インデックスの数
	desc.idxSize = sizeof(int);			// インデックス一つあたりのデータサイズ
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
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
CSphere::CSphere(CSphere & Obj)
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
CSphere::~CSphere()
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
void CSphere::Draw()
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