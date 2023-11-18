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
	・2023/11/09 カメラの移動が分かるように地面追加した 髙木駿輔
	・2023/11/11 スライム同士が重ならない処理を追加 yamashita

========================================== */
#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__

// =============== インクルード ===================
#include "Model.h"
#include "Shader.h"
#include "Camera.h"
#include "Geometry.h"
#include "SlimeManager.h"
#include "Collision.h"
#include "Player.h"
#include "ExplosionManager.h"
#include "DirectWrite.h"
#include "Timer.h"
#include "Floor.h"

// =============== クラス定義 =====================
class SceneGame
{
public:
	// ===メンバ関数宣言===
	SceneGame(DirectWrite* pDirectWrite);
	~SceneGame();
	void Update(float tick);
	void Draw();

	void SceneGameCollision();
	void PlayerSlimeCollision();
	void HammerSlimeCollision();
	void SlimeSlimeCollision();
	void ExplosionSlimeCollision();
	void SlimeSlimeNormalMoveCollision();
	void SetDirectWrite(DirectWrite* pDirectWrite);
private:
	// ===メンバ変数宣言===
	VertexShader* m_pVs;
	CCamera* m_pCamera;
	CPlayer* m_pPlayer;
	CGeometry* m_pBox;
	CSlimeManager* m_pSlimeMng;
	CCOLLISION* m_pCollision;
	CExplosionManager* m_pExplosionMng;
	DirectWrite* m_pDirectWrite;
	CTimer* m_pTimer;
	CFloor* m_pFloor;
};

#endif // __SCENE_GAME_H__