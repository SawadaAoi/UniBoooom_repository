/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
  �v���C���[�ړ��G�t�F�N�g�Ǘ��w�b�_�[
   ---------------------------------------
   WalkEffectManager.h

   �쐬�� �A �F��

   �ύX����
	�E2024/01/30 WalkEffectManager�N���X�쐬 Tei

========================================== */
#ifndef __WALK_EFFECT_MANAGER_H__	
#define __WALK_EFFECT_MANAGER_H__

// =============== �萔��` =======================
const int	MAX_STEP_NUM = 3;	// �ő�G�t�F�N�g������

// =============== �C���N���[�h ===================
#include "WalkEffect.h"

// =============== �N���X��` =====================
class CWalkEffectManager
{
public:
	// ===�����o�֐��錾===
	CWalkEffectManager();		//�R���X�g���N�^
	~CWalkEffectManager();		//�f�X�g���N�^

	void Draw();		 			//�`��֐�
	void Update();

	CWalkEffect* GetWalkPtr(int num);			//�v���C���[�ړ��G�t�F�N�g�z����Q�b�g
	void Create(tagTransform3d transform);   		//�v���C���[�ړ��G�t�F�N�g�����֐�
	void SetCamera(const CCamera* pCamera);		//���̃I�u�W�F�N�g�Ɠ���̃J�������Z�b�g
	void DeleteCheck();							// �g�����G�t�F�N�g���폜�֐�
	float GetRandomSize();						// �����_���ŃT�C�Y���Z�l�Q�b�g

private:
	// ===�����o�ϐ��錾===
	CWalkEffect* m_pwalkEffect[MAX_STEP_NUM];		//�v���C���[�ړ��G�t�F�N�g�̔z��

	const CCamera* m_pCamera;					//�J����
	float m_fRandSize;

	Effekseer::EffectRef m_walkEffect;			//�v���C���[�ړ���Effekseer
};

#endif // __WALK_EFFECT_MANAGER_H__