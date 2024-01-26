/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   �q�b�g�X���C���G�t�F�N�g�Ǘ��w�b�_�[
   ---------------------------------------
   HitSlimeEffectManager.h

   �쐬�� �A �F��

   �ύX����
	�E2024/01/25 HitSlimeEffectManager�N���X�쐬 Tei

========================================== */
#ifndef __HIT_SLIME_EFFECT_MANAGER_H__	
#define __HIT_SLIME_EFFECT_MANAGER_H__

// =============== �萔��` =======================
const int	MAX_HIT_NUM = 5;	// �ő�G�t�F�N�g������

// =============== �C���N���[�h ===================
#include "HitSlimeEffect.h"


// =============== �N���X��` =====================
class CHitSlimeEffectManager
{
public:
	// ===�����o�֐��錾===
	CHitSlimeEffectManager();		//�R���X�g���N�^
	~CHitSlimeEffectManager();		//�f�X�g���N�^

	void Draw();		 			//�`��֐�
	void Update();

	CHitEffect* GetHitPtr(int num);				//�q�b�g�G�t�F�N�g�z����Q�b�g
	void Create(TTriType<float> pos);   		//�q�b�g�G�t�F�N�g�����֐�
	void SetCamera(const CCamera* pCamera);		//���̃I�u�W�F�N�g�Ɠ���̃J�������Z�b�g
	void DeleteCheck();							// �g�����G�t�F�N�g���폜�֐�


private:
	// ===�����o�ϐ��錾===
	CHitEffect* m_phitEffect[MAX_HIT_NUM];		//�q�b�g�G�t�F�N�g�̔z��

	const CCamera* m_pCamera;					//�J����

	Effekseer::EffectRef m_hitEffect;			//�q�b�g��Effekseer
};

#endif // __HIT_SLIME_EFFECT_MANAGER_H__