/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�����G�t�F�N�g�}�l�[�W���\�w�b�_
	---------------------------------------
	UnionSmokeEffectManager.h

	�쐬��
			Tei

	�ύX����
	�E2024/02/06 �N���X��`�쐬 Tei
	�E2024/02/13 �J�����폜 takagi

========================================== */

#ifndef __UNION_SMOKE_EFFECT_MANAGER_H__
#define __UNION_SMOKE_EFFECT_MANAGER_H__

// =============== �C���N���[�h ===================
#include "UnionSmokeEffect.h"

// =============== �萔��` ===================
const int MAX_UNION_SMOKE_NUM = 55;

// =============== �N���X��` =====================
class CUnionSmokeEffectManager
{
public:
	// ===�񋓒�`===========
	enum E_SMOKE	// �\���摜
	{
		GREEN_SMOKE,	// �������̉摜�i�΁j
		YELLOW_SMOKE,	// �������̉摜�i���j
		RED_SMOKE,		// �������̉摜�i�ԁj

		SMOKE_MAX,
	};
public:
	CUnionSmokeEffectManager();
	~CUnionSmokeEffectManager();
	void Create(TPos3d<float> fpos, int slimelevel);
	void Update();
	void Draw();
	void DeleteCheck();							// �g�����G�t�F�N�g���폜�֐�

private:
	CUnionSmokeEffect* m_pUnionSmokeEffect[MAX_UNION_SMOKE_NUM];
	Texture* m_pTexture[SMOKE_MAX];
};



#endif //!__UNION_SMOKE_EFFECT_MANAGER_H__