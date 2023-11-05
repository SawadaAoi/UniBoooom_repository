/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   直線定義
   ---------------------------------------
   Line.h

   作成者	takagi

   変更履歴
   ・↓まで 学校の配布物(授業に沿い変形)
   ・2023/11/05 ファイル分割・抽象クラス化・コメント付与 takagi


   ======================================== */

#ifndef __LINE_H__
#define __LINE_H__

// =============== インクルード ===================
#include <DirectXMath.h>	//行列計算用
#include "Shader.h"			//メンバのヘッダ
#include "MeshBuffer.h"		//メンバのヘッダ

// =============== クラス定義 =====================
class CLine
{
protected:
	// =============== 構造体定義 =====================
	struct LineVertex
	{
		float pos[3];	//位置
		float color[4];	//色
	};	//テクスチャを貼らない場合の頂点情報？
private:
	// =============== 構造体定義 =====================
	enum E_MATRIX
	{
		E_MATRIX_WORLD = 0,		//ワールド行列
		E_MATRIX_VIEW,			//ビュー行列
		E_MATRIX_PROJECTION,	//プロジェクション行列
	};	//行列
public:
	// =============== プロトタイプ宣言 ===============
	static void Init();			//コンストラクタ
	CLine(CLine& Obj);	//コピーコンストラクタ
	virtual ~CLine();	//デストラクタ

	static void MakeShader();	//シェーダ作成

	static void Make();
	static void Draw();

	void Uninit();				//終了

	static void Add(DirectX::XMFLOAT3 start, DirectX::XMFLOAT3 end,
		DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	static void SetWorld(DirectX::XMFLOAT4X4 World);		//ワールド行列登録
	static void SetView(DirectX::XMFLOAT4X4 View);			//ビュー行列登録
	static void SetProjection(DirectX::XMFLOAT4X4 Proj);	//プロジェクション行列登録
protected:
	// =============== メンバー変数宣言 ===============
	static Shader* m_pVS;			//頂点シェーダ
	static Shader* m_pPS;			//ピクセルシェーダ
	static DirectX::XMFLOAT4X4 m_WVP[3];	//各座標系における行列(0:world, 1:view, 2:projection)

	static const int MAX_LINE_NUM = 1000;
	static MeshBuffer* m_pLines;	//形状の頂点・辺・面
	static void* m_pLineVtx;
	static int m_lineCnt;
private:
	// =============== プロトタイプ宣言 ===============
	static void MakeVS();	//頂点シェーダ作成
	static void MakePS();	//ピクセルシェーダ作成
};	//空間形状

#endif	//!__LINE_H__