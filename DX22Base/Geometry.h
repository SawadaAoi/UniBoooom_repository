/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   空間における形状の抽象クラス定義
   ---------------------------------------
   Geometry.h

   作成者	takagi

   変更履歴
   ・↓まで 学校の配布物(授業に沿い変形)
   ・2023/11/05 ファイル分割・抽象クラス化・コメント付与 takagi
   ・2023/11/10 Uninit削除 takagi
   ・2023/11/10 Uninit作成(シェーダ用) 澤田蒼生

   ======================================== */

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

// =============== インクルード ===================
#include <DirectXMath.h>	//行列計算用
#include "Shader.h"			//メンバのヘッダ
#include "MeshBuffer.h"		//メンバのヘッダ
//#include "Pos.h"

// =============== クラス定義 =====================
class CGeometry
{
protected:
	// =============== 構造体定義 =====================
	struct Vertex
	{
		float pos[3];	//頂点の位置
		float uv[2];	//テクスチャ座標
	};	//テクスチャを貼る場合の頂点情報
private:
	// =============== 構造体定義 =====================
	enum E_MATRIX
	{
		E_MATRIX_WORLD = 0,	//ワールド行列
		E_MATRIX_VIEW,			//ビュー行列
		E_MATRIX_PROJECTION,	//プロジェクション行列
	};	//行列
public:
	// =============== プロトタイプ宣言 ===============
	CGeometry();				//コンストラクタ
	CGeometry(CGeometry& Obj);	//コピーコンストラクタ
	virtual ~CGeometry();		//デストラクタ
	static void MakeShader();	//シェーダ作成
	virtual void Draw() = 0;	//描画
	static void Uninit();

	void SetWorld(DirectX::XMFLOAT4X4 World);		//ワールド行列登録
	void SetView(DirectX::XMFLOAT4X4 View);			//ビュー行列登録
	void SetProjection(DirectX::XMFLOAT4X4 Proj);	//プロジェクション行列登録
protected:
	// =============== メンバー変数宣言 ===============
	MeshBuffer* m_pObj;				//形状の頂点・辺・面
	static Shader* m_pVS;			//頂点シェーダ
	static Shader* m_pPS;			//ピクセルシェーダ
	DirectX::XMFLOAT4X4 m_WVP[3];	//各座標系における行列(0:world, 1:view, 2:projection)
private:
	// =============== プロトタイプ宣言 ===============
	static void MakeVS();	//頂点シェーダ作成
	static void MakePS();	//ピクセルシェーダ作成
};	//空間形状

#endif	//!__GEOMETRY_H__