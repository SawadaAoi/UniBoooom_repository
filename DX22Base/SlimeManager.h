/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   �X���C���x�[�X �N���X��`
   ---------------------------------------
   SlimeManager.h

   �쐬�� �鑺 ����

   �ύX����
   �E2023/11/05 �X���C���}�l�[�W���[�N���X�쐬 /�鑺 ����
   �E2023/11/08 �X���C�����m���ڐG�����ۂ̕��򏈗����쐬(���򂵂���ɍs�������͖������@��TODO�����Ă�����)�� /�R�����C
   �E2023/11/08 �����������쐬(������̐��������͖����� Slime_2�`Slime_4���܂���������) /�R�����C
   �E2023/11/09 �X���C�������֐��̖��O�ύX/�V�c

   ======================================== */
#ifndef __SLIME_MANAGER_H__
#define __SLIME_MANAGER_H__

// =============== �C���N���[�h ===================
#include "TriType.h"
#include "SlimeBase.h"
#include "ExplosionManager.h"
#include "Camera.h"

// =============== �萔��` =======================
const int MAX_SLIME = 20;	//�X���C���̍ő吶����

// =============== �N���X��` =====================
class CSlimeManager
{
public:
	// ===�v���g�^�C�v�錾===
	CSlimeManager();
	~CSlimeManager();

	void Update();
	void Draw();
	void Create();	//�X���C���𐶐����鏈��
	void HitBranch(int HitSlimeArrayNum,int standSlimeArrayNum);	//�X���C���̐ڐG���N�����ۂ̕��򏈗�
	void UnionSlime(E_SLIME_LEVEL level);							//�X���C���̌�������


	//�Q�b�g�֐�
	CSlimeBase* GetSlimePtr(int num);

	//�Z�b�g�֐�
	void SetCamera(CCamera* pCamera);
	void SetPlayerSphere(CSphereInfo::Sphere pSphere);

private:
	int GetRandom(int min, int max);
	int m_GeneCnt;

	CSlimeBase* m_pSlime[MAX_SLIME];
	CCamera* m_pCamera;
	CSphereInfo::Sphere m_pPlayerSphere;	// �v���C���[�̓����蔻�菈��



	
};

#endif // __SLIME_MANAGER_H__