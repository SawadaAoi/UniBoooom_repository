/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	SceneGame�������蔻��p�w�b�_
	------------------------------------
	SceneGameCollision.h
	------------------------------------
	�쐬�� �m�}����

	�ύX����
	�E2023/11/07 �V�K�쐬 �m�}����

========================================== */


#ifndef __SCENE_GAME_COLLISION_H__
#define __SCENE_GAME_COLLISION_H__

#include "Collision.h"


// =============== �\���̒�` =====================

// =============== �N���X��` =====================
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
// ===�񋓒�`=========
// ===�\���̒�`=======
// ===�����o�ϐ��錾===
// ===�����o�֐��錾===


// =============== �񋓒�` =======================

#endif // !__SCENE_GAME_COLLISION_H__
