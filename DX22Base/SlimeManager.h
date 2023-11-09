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


   ======================================== */
#ifndef __SLIME_MANAGER_H__
#define __SLIME_MANAGER_H__

#include "TriType.h"
#include "SlimeBase.h"
#include "ExplosionManager.h"

const int MAX_SLIME = 20;	//�X���C���̍ő吶����

class CSlimeManager
{
public:
	CSlimeManager();
	~CSlimeManager();

	void Update();
	void Draw();
	void Generate(TTriType<float> pos);
	void HitBranch(int HitSlimeArrayNum,int standSlimeArrayNum);	//�X���C���̐ڐG���N�����ۂ̕��򏈗�
	void UnionSlime(E_SLIME_LEVEL level);							//�X���C���̌�������


	//�Q�b�g�֐�
	CSlimeBase* GetSlimePtr(int num);
private:
	CSlimeBase* m_pSlime[MAX_SLIME];


	int m_nRandNum;	//�����p
	int _RandNum;	//�����p
	
};

#endif // __SLIME_MANAGER_H__