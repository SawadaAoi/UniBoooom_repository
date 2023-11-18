/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	Floor用ヘッダ
	------------------------------------
	Floor.h
	------------------------------------
	作成者
		yamashita
	変更履歴
	・2023/11/16 h,作成 yamashita
	・2023/11/16 モデル、頂点シェーダー、カメラのポインタをメンバ変数に追加 yamashita
	・2023/11/16 カメラのセット関数を作成 yamashita
========================================== */
#ifndef __FLOOR_H__
#define __FLOOR_H__

#include "Camera.h"
#include "Transform3d.h"
#include "Pos3d.h"
#include "Shader.h"
#include "Model.h"
#include "GameParameter.h"		//定数定義用ヘッダー

// =============== クラス定義 =====================
class CFloor
{
public:
	// ===プロトタイプ宣言===
	CFloor();
	~CFloor();
	void Update();
	void Draw();

	void SetCamera(const CCamera* pCamera);

private:
	// ===メンバ変数宣言=====
	Model* m_pModel;				//3Dモデル
	VertexShader* m_pVS;			//バーテックスシェーダーのポインタ
	tagTransform3d m_Transform;		//ワールド座標系情報
	const CCamera* m_pCamera;		//カメラのポインタ

};




#endif // !__FLOOR_H__
