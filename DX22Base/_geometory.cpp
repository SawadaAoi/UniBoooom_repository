/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	_geometry用cpp
	---------------------------------------
	_geometry.cpp
	
	作成者
	
	変更履歴
	・2023/11/05 変更内容:MakeSphereの中身を書いた 変更者名：山下凌佑
	・2023/11/05 変更内容:球体用の定数定義 変更者名：山下凌佑
	
======================================== */

// =============== インクルード ===================
#include "Geometory.h"

// =============== 定数定義 =======================
//球体の定数
const int VTX_SPHERE_X_NUM = 18;	//頂点の横列の数
const int VTX_SPHERE_Y_NUM = 18;	//頂点の縦列の数
const int VTX_NUM = VTX_SPHERE_X_NUM * VTX_SPHERE_Y_NUM;	//頂点の総数
const int SURFACE_SPHERE_X_NUM = VTX_SPHERE_X_NUM - 1;	//横列の表面の数(四角形)
const int SURFACE_SPHERE_Y_NUM = VTX_SPHERE_Y_NUM - 1;	//縦列の表面の数(四角形)
const int SURFACE_SPHERE_NUM = SURFACE_SPHERE_X_NUM * SURFACE_SPHERE_Y_NUM;	//表面の総数(四角形)
const float SPHERE_DIAMETER = 1.0f;	//円の直径
const float SPHERE_RADIUS = SPHERE_DIAMETER / 2;	//円の半径


void Geometory::MakeBox()
{

	// 元データの作成
	Vertex vtx[] = {

		// 手前、奥 ----------------------------------
			// -Z面
			{{-0.5f, 0.5f,-0.5f},{0.0f,0.0f}},	// 0
			{{ 0.5f, 0.5f,-0.5f},{1.0f,0.0f}},	// 1
			{{-0.5f,-0.5f,-0.5f},{0.0f,1.0f}},	// 2	
			{{ 0.5f,-0.5f,-0.5f},{1.0f,1.0f}},	// 3

		// +Z面
			{{  0.5f, 0.5f,0.5f},{0.0f,0.0f}},
			{{ -0.5f, 0.5f,0.5f},{1.0f,0.0f}},
			{{  0.5f,-0.5f,0.5f},{0.0f,1.0f}},
			{{ -0.5f,-0.5f,0.5f},{1.0f,1.0f}},

		// 左右 ----------------------------------
			// -X面
			{{-0.5f, 0.5f, 0.5f},{0.0f,0.0f}},
			{{-0.5f, 0.5f,-0.5f},{1.0f,0.0f}},
			{{-0.5f,-0.5f,0.5f},{0.0f,1.0f}},
			{{-0.5f,-0.5f,-0.5f},{1.0f,1.0f}},

			// +X面
			{{0.5f, 0.5f,-0.5f},{0.0f,0.0f}},
			{{0.5f, 0.5f, 0.5f},{1.0f,0.0f}},
			{{0.5f,-0.5f,-0.5f},{0.0f,1.0f}},
			{{0.5f,-0.5f, 0.5f},{1.0f,1.0f}},

		// 上下 ----------------------------------
			// -Y面
			{{-0.5f,-0.5f,-0.5f},{0.0f,0.0f}},
			{{ 0.5f,-0.5f,-0.5f},{1.0f,0.0f}},
			{{-0.5f,-0.5f, 0.5f},{0.0f,1.0f}},
			{{ 0.5f,-0.5f, 0.5f},{1.0f,1.0f}},

			// +Y面
			{{-0.5f,0.5f, 0.5f},{0.0f,0.0f}},
			{{ 0.5f,0.5f, 0.5f},{1.0f,0.0f}},
			{{-0.5f,0.5f,-0.5f},{0.0f,1.0f}},
			{{ 0.5f,0.5f,-0.5f},{1.0f,1.0f}},
	};
	int idx[] = {
		0,1,2,1,3,2,
		4,5,6,5,7,6,
		8,9,10,9,11,10,
		12,13,14,13,15,14,
		16,17,18,17,19,18,
		20,21,22,21,23,22,

	};

	// バッファの作成
	MeshBuffer::Description desc = {};
	desc.pVtx		= vtx;
	//desc.vtxCount	= sizeof(vtx) / sizeof(Vertex);			// 頂点の数
	desc.vtxCount	= _countof(vtx);		// 頂点の数(_countofは配列の数を数える)
	desc.vtxSize	= sizeof(Vertex);		// 頂点一つあたりのデータサイズ
	desc.pIdx		= idx;					 
	desc.idxCount	= _countof(idx);		// インデックスの数
	desc.idxSize	= sizeof(int);			// インデックス一つあたりのデータサイズ
	desc.topology	= D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	//desc.topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
	m_pBox			= new MeshBuffer(desc);
}

void Geometory::MakeCylinder()
{
	//--- 頂点の作成
	// 天面、底面
	for (int i = 0; i < 8; i++)
	{

	}

	// 側面

	//--- インデックスの作成
	// 天面、底面


	// 側面


	//--- バッファの作成
}

void Geometory::MakeSphere()
{
	//--- 頂点の作成
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

	//--- インデックスの作成
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


	// バッファの作成
	MeshBuffer::Description desc = {};
	desc.pVtx = vtx;
	desc.vtxCount = _countof(vtx);					// 頂点の数
	desc.vtxSize = sizeof(vtx[0]);	// 頂点一つあたりのデータサイズ
	desc.pIdx = idx;
	desc.idxCount = _countof(idx);					// インデックスの数
	desc.idxSize = sizeof(int);			// インデックス一つあたりのデータサイズ
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	m_pSphere = new MeshBuffer(desc);
}