/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	���f���Ǘ��N���X
	---------------------------------------
	ModelManager.h

	�쐬��
			yamashita
	�ύX����
	�E2024/02/08 �V�K�쐬

========================================== */

#ifndef __MODEL_MANAGER_H__
#define __MODEL_MANAGER_H__

enum MODEL_KIND
{
	// �v���C���[
	MODEL_PLAYER,
	// �X���C��
	MODEL_SLIME_BLUE,
	MODEL_SLIME_GREEN,
	MODEL_SLIME_YELLOW,
	MODEL_SLIME_RED,
	MODEL_SLIME_FLAME,
	MODEL_SLIME_HEAL,
	MODEL_SLIME_ROCK,
	MODEL_SLIME_DEVIL,
	// �A�C�e��
	MODEL_ITEM_HEART,

	MODEL_MAX,
};

// =============== �C���N���[�h ===================
#include "AnimeModel.h"
#include <unordered_map>
#include <string>
#include "SlimeBase.h"
#include "Slime_BossBase.h"
#include "Player.h"

using namespace std;

class CModelManager
{
private:
	CModelManager();
	CModelManager(const CModelManager& em) {}
	CModelManager& operator=(const CModelManager& em) { return *this; }


public:
	~CModelManager();
	// �g�p���邽�߂ɂ�����Ă�
	static CModelManager& GetInstance();
	// �Ăяo�����}�N���ɂ��Ċȗ���
#define GetModelMng CModelManager::GetInstance()
	void LoadAnime();
	AnimeModel* GetModelPtr(MODEL_KIND model);	// ���f���擾�֐�

	// �����o�ϐ�
	unordered_map<MODEL_KIND, AnimeModel*> m_ModelList;
	string m_sFileName[MODEL_MAX];
	float m_fModelSize[MODEL_MAX];

	//========== �A�j�� ==========
	// �v���C���[
	const std::string m_sPlayerMotion[CPlayer::MOTION_PLAYER_MAX] = {	//�A�j���[�V�����̃t�@�C��
		"Assets/Model/player/wait_end.FBX",			//�ҋ@
		"Assets/Model/player/dash_v2.FBX",				//�ړ�
		"Assets/Model/player/POW.FBX",				//�X�C���O
		"Assets/Model/player/ChargeDash_v1.FBX",				//�`���[�W���
		"Assets/Model/player/down.fbx",				//���S

	};

	// �X���C��
	const std::string m_sLevel1_Motion[CSlimeBase::MOTION_LEVEL1_MAX] = {
		"Assets/Model/slime/Blue/slime_blue_walk_1.0.fbx",		// ���x��1�X���C���̈ړ����[�V����
		"Assets/Model/slime/Blue/slime_blue_damaged_1.1.fbx",	// ���x��1�X���C���̒@���ꂽ�Ƃ��̃��[�V����
	};

	// �΃X���C��
	const std::string m_sLevel2_Motion[CSlimeBase::MOTION_LEVEL2_MAX] = {
	"Assets/Model/slime/Green/slime_green_walk_1.0.fbx",		// ���x��2�X���C���̈ړ����[�V����
	"Assets/Model/slime/Green/slime_green_damaged_1.0.fbx",		// ���x��2�X���C���̒@���ꂽ�Ƃ��̃��[�V����
	"Assets/Model/slime/Green/slime_green_rush_1.0.fbx",		// ���x��2�X���C���̍U�����[�V����
	};

	// ���F�X���C��
	const std::string m_sLevel3_Motion[CSlimeBase::MOTION_LEVEL3_MAX] = {
	"Assets/Model/slime/Yellow/slime_yellow_walk_1.0.fbx",		// ���x��3�X���C���̈ړ����[�V����
	"Assets/Model/slime/Yellow/slime_yellow_damaged_1.0.fbx",	// ���x��3�X���C���̒@���ꂽ�Ƃ��̃��[�V����
	"Assets/Model/slime/Yellow/slime_yellow_mekakushi_1.1.fbx",	// ���x��3�X���C���Î~��Ԃ̃��[�V����
	};

	// �ԃX���C��
	const std::string m_sLevel4_Motion[CSlimeBase::MOTION_LEVEL4_MAX] = {
		"Assets/Model/slime/Red/slime_red_walk_1.0.fbx",		// ���x��1�X���C���̈ړ����[�V����
		"Assets/Model/slime/Red/slime_red_damaged_1.0.fbx",	// ���x��1�X���C���̒@���ꂽ�Ƃ��̃��[�V����
	};

	// ���X���C��
	const std::string m_sFlameSlime_Motion[CSlimeBase::FLAME_SLIME_MAX] = {
		"Assets/Model/flameSlime/fire_walk.fbx",	// ���X���C���̈ړ����[�V����
		"Assets/Model/flameSlime/fire_damaged.fbx",	// ���X���C���̔�_�����[�V����
	};

	// �q�[���X���C��
	const std::string m_sHealSlime_Motion[CSlimeBase::HEAL_SLIME_MAX] = {
		"Assets/Model/healSlime/heal_walk.fbx",		// �q�[���X���C���̈ړ����[�V����
		"Assets/Model/healSlime/heal_damaged.fbx",	// �q�[���X���C���̔�_�����[�V����
	};

	// ��X���C��
	const std::string m_sRockSlime_Motion[CSlime_BossBase::ROCK_SLIME_MAX] = {
		"Assets/Model/boss_slime_rock/rock_walk_1.1.fbx",		// ��X���C���̈ړ����[�V����
		"Assets/Model/boss_slime_rock/rock_damaged_2.0.fbx",	// ��X���C���̔�_�����[�V����
		"Assets/Model/boss_slime_rock/rock_rolling_2.0.fbx",	// ��X���C���̍U�����[�V����
	};

	// �f�r���X���C��
	const std::string m_sDevilSlime_Motion[CSlime_BossBase::DEVIL_SLIME_MAX] = {
		"Assets/Model/boss_slime_devil/devil_walk.fbx",		// �f�r���X���C���̈ړ����[�V����
		"Assets/Model/boss_slime_devil/devil_damaged.fbx",	// �f�r���X���C���̔�_�����[�V����
	};
};


#endif // !__MODEL_MANAGER_H__