/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   �X���C���x�[�X �N���X��`
   ---------------------------------------
   SlimeManager.h

   �쐬�� �鑺 ����

   �ύX����
   �E2023/11/05 �X���C���}�l�[�W���[�N���X�쐬 /�鑺 ����
   �E2023/11/09 �X���C�������֐��̖��O�ύX/�V�c

   ======================================== */
#ifndef __SLIME_MANAGER_H__
#define __SLIME_MANAGER_H__

#include "TriType.h"
#include "SlimeBase.h"
#include "Camera.h"



const int MAX_SLIME = 20;	//�X���C���̍ő吶����

class CSlimeManager
{
public:
	CSlimeManager();
	~CSlimeManager();

	void Update();
	void Draw();
	void Create();
	void HitBranch(int HitSlimeArrayNum,int standSlimeArrayNum);	//�X���C���̐ڐG���N�����ۂ̕��򏈗�
	void UnionSlime(E_SLIME_LEVEL level);							//�X���C���̌�������
	CSlimeBase* GetSlimePtr(int num);

	void SetCamera(CCamera* pCamera);
	void SetPlayerSphere(CSphereInfo::Sphere pSphere);
private:
	int GetRandom(int min, int max);

	CSlimeBase* m_pSlime[MAX_SLIME];
	CCamera* m_pCamera;

	CSphereInfo::Sphere m_pPlayerSphere;	// �v���C���[�̓����蔻�菈��

	int m_GeneCnt;


	
};

#endif // __SLIME_MANAGER_H__