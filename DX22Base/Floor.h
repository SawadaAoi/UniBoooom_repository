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
	・2023/11/22 座標算出関数を作成 yamashita
========================================== */
#ifndef __FLOOR_H__
#define __FLOOR_H__

#include "Camera.h"
#include "Transform3d.h"
#include "Pos3d.h"
#include "Shader.h"
#include "Model.h"
#include "GameParameter.h"		//定数定義用ヘッダー

// =============== 定数定義 =====================
const int FLOOR_NUM = 9;

// =============== クラス定義 =====================
class CFloor
{
public:
	enum StageKinds
	{
		Stage1,
		Stage2,
		Stage3,
	};
public:
	// ===プロトタイプ宣言===
	CFloor(TPos3d<float>* pPlayerPos,StageKinds stageKind);
	~CFloor();
	void Update();
	void Draw();

	void calculationPosition();				//座標算出関数
	void SetCamera(const CCamera* pCamera);	//カメラセット関数
	void SetFloorModel();
private:
	// ===メンバ変数宣言=====
	tagTransform3d m_Transform[FLOOR_NUM];		//ワールド座標系情報
	Model* m_pModel;				//3Dモデル
	VertexShader* m_pVS;			//バーテックスシェーダーのポインタ
	const CCamera* m_pCamera;		//カメラのポインタ
	TPos3d<float>* m_pPlayePos;		//プレイヤーのポジションのポインタ
	TPos3d<int> m_pPlayerFloor;		//プレイヤーが現在いる座標にある床が何枚目の床なのか
	StageKinds m_stage;
};




#endif // !__FLOOR_H__
