/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ゲームシーンのステージ１用ヘッダ
	------------------------------------
	SceneGameStage1.h
	------------------------------------
	作成者 仁枝潤哉

	変更履歴
	・2023/11/17 新規作成 仁枝潤哉

========================================== */
#ifndef __SCENE_GAME_STAGE1_H__
#define __SCENE_GAME_STAGE1_H__

// =============== インクルード ===================
#include "Model.h"
#include "Shader.h"
#include "Camera.h"
#include "Geometry.h"
#include "SlimeManager.h"
#include "Collision.h"
#include "Player.h"
#include "ExplosionManager.h"
#include "HpManager.h"
#include "CollisionOfStage.h"
#include "DirectWrite.h"

// =============== クラス定義 =====================
class CSceneGameStage1
{
public:
	// ===メンバ関数宣言===
	CSceneGameStage1(DirectWrite* pDirectWrite);
	~CSceneGameStage1();
	void Update();
	void Draw();

	void SetDirectWrite(DirectWrite* pDirectWrite);
private:
	// ===メンバ変数宣言===
	VertexShader* m_pVs;
	CCamera* m_pCamera;
	CPlayer* m_pPlayer;
	CGeometry* m_pBox;
	CSlimeManager* m_pSlimeMng;
	CExplosionManager* m_pExplosionMng;
	ChpManager* m_pHpMng;
	CCollisionOfStage* m_pColOfStg;
	DirectWrite* m_pDirectWrite;
};

#endif // !__SCENE_GAME_STAGE1_H__
