/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	SceneGame内当たり判定用ヘッダ
	------------------------------------
	SceneGameCollision.h
	------------------------------------
	作成者 仁枝潤哉

	変更履歴
	・2023/11/07 新規作成 仁枝潤哉

========================================== */


#ifndef __SCENE_GAME_COLLISION_H__
#define __SCENE_GAME_COLLISION_H__

#include "Collision.h"


// =============== 構造体定義 =====================

// =============== クラス定義 =====================
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
// ===列挙定義=========
// ===構造体定義=======
// ===メンバ変数宣言===
// ===メンバ関数宣言===


// =============== 列挙定義 =======================

#endif // !__SCENE_GAME_COLLISION_H__
