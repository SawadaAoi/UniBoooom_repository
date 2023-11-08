#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__
/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ゲームシーン用ヘッダ
	------------------------------------
	SceneGame.h
	------------------------------------
	作成者 澤田

	変更履歴
	・2023/11/08 コメント追加と、無駄な箇所を削除

========================================== */

// =============== インクルード ===================
#include "Model.h"
#include "Shader.h"
#include "Camera.h"
#include "Geometry.h"
#include "SlimeManager.h"
#include "Collision.h"
#include "Player.h"
#include "ExplosionManager.h"

// =============== クラス定義 =====================
class SceneGame
{
public:
	// ===メンバ関数宣言===
	SceneGame();
	~SceneGame();
	void Update(float tick);
	void Draw();

	void SceneGameCollision();
	void PlayerSlimeCollision();
	void HammerSlimeCollision();
	void SlimeSlimeCollision();
	void ExplosionSlimeCollision();
private:
	// ===メンバ変数宣言===
	VertexShader* m_pVs;
	CCamera* m_pCamera;
	CPlayer* m_pPlayer;
	CSlimeManager* m_pSlimeMng;
	CExplosionManager* m_pExplodeMng;
	CCOLLISION* m_pCollision;
};

#endif // __SCENE_GAME_H__