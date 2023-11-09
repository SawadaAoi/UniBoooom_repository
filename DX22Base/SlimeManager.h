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
   �E2023/11/09 �v���C���[���W�擾�̌^��TPos3d<float>�ɕύX

   ======================================== */
#ifndef __SLIME_MANAGER_H__
#define __SLIME_MANAGER_H__

#include "TriType.h"
#include "SlimeBase.h"
#include "ExplosionManager.h"
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


	//�Q�b�g�֐�
	CSlimeBase* GetSlimePtr(int num);

	void SetCamera(CCamera* pCamera);
	void SetPlayerPos(TPos3d<float> pos);
private:
	int GetRandom(int min, int max);

	CSlimeBase* m_pSlime[MAX_SLIME];
	CCamera* m_pCamera;

	TPos3d<float> m_pPlayerPos;	// �v���C���[�̍��W

	int m_CreateCnt;	// �����Ԋu�p�J�E���g


	
};

#endif // __SLIME_MANAGER_H__