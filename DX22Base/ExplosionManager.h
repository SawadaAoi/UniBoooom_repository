#ifndef __EXPLOSION_MANAGER_H__
#define __EXPLOSION_MANAGER_H__
/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   �����Ǘ�
   ---------------------------------------
   ExplosionManager.h

   �쐬�� �A �F��

   �ύX����
	�E2023/11/06 �����}�l�[�W���[�N���X�쐬 /�A�@�F��
	�E2023/11/10 ���̃I�u�W�F�N�g�Ɠ���̃J�������Z�b�g����悤�ɂ��� �R�����C

	�E2023/11/06 �����}�l�[�W���[�N���X�쐬 /�A�@�F��
	�E2023/11/09 �����z���Ԃ������̒ǉ�/ �V�c����
	
========================================== */

// =============== �C���N���[�h ===================
#include "TriType.h"
#include "Explosion.h"

// =============== �萔��` =======================
const int MAX_EXPLOSION_NUM = 20;

// =============== �N���X��` =====================
class CExplosionManager
{
public:
	// ===�����o�֐��錾===
	CExplosionManager();
	~CExplosionManager();

	void Update();
	void Draw();
	
	void Create(TTriType<float> pos,float size);
	void DeleteCheck();

	CExplosion* GetExplosionPtr(int num);

	void SetCamera(const CCamera* pCamera);	//���̃I�u�W�F�N�g�Ɠ���̃J�������Z�b�g
protected:
	// ===�����o�ϐ��錾===
	CExplosion* m_pExplosion[MAX_EXPLOSION_NUM];
	const CCamera* m_pCamera;
private:
};

#endif // __EXPLOSION_MANAGER_H__