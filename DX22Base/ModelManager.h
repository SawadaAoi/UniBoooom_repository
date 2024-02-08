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

using namespace std;

class CModelManager
{
private:
	CModelManager();
	CModelManager(const CModelManager& em) {}
	CModelManager& operator=(const CModelManager& em) { return *this; }


public:
	~CModelManager() {};
	// �g�p���邽�߂ɂ�����Ă�
	static CModelManager& GetInstance();
	// �Ăяo�����}�N���ɂ��Ċȗ���
#define GetModelMng CModelManager::GetInstance()

	// �����o�ϐ�
	unordered_map<MODEL_KIND, AnimeModel*> m_pModelList;
	string m_sFileName[MODEL_MAX];
	float m_fModelSize[MODEL_MAX];
};


#endif // !__MODEL_MANAGER_H__