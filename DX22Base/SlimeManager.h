/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   �X���C���x�[�X �N���X��`
   ---------------------------------------
   SlimeManager.h

   �쐬�� �鑺 ����

   �ύX����
   �E2023/11/05 �X���C���}�l�[�W���[�N���X�쐬 /�鑺 ����


   ======================================== */
#ifndef __SLIME_MANAGER_H__
#define __SLIME_MANAGER_H__

#include "TriType.h"
#include "SlimeBase.h"

#define MAX_SLIME_1 20
#define MAX_SLIME_2 12
#define MAX_SLIME_3 8
#define MAX_SLIME_4 4

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
	
private:
	CSlimeBase* m_pSlime[MAX_SLIME_1];

	int m_nRandNum;	//�����p
};

#endif // __SLIME_MANAGER_H__