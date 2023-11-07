/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	SceneGameเฝ่ป่pwb_
	------------------------------------
	SceneGameCollision.h
	------------------------------------
	์ฌา m}ฦ

	ฯX๐
	E2023/11/07 VK์ฌ m}ฦ

========================================== */


#ifndef __SCENE_GAME_COLLISION_H__
#define __SCENE_GAME_COLLISION_H__

#include "Collision.h"


// =============== \ขฬ่` =====================

// =============== NX่` =====================
class CSceneGameCollision
{
public:
	CSceneGameCollision();
	~CSceneGameCollision();

	void PlayerSlimeCollision();
	void HammerSlimeCollision();
	void SlimeSlimeCollision();
	void ExplosionSlimeCollision();
private:
	CCOLLISION* m_pCollision;
};
// ===๑่`=========
// ===\ขฬ่`=======
// ===oฯ้พ===
// ===oึ้พ===


// =============== ๑่` =======================

#endif // !__SCENE_GAME_COLLISION_H__
