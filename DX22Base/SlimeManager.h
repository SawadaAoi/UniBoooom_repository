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

enum E_SLIME_LEVEL
{
	LEVEL_1,
	LEVEL_2,
	LEVEL_3,
	LEVEL_4
};

#define MAX_SLIME_1 20
#define MAX_SLIME_2 12
#define MAX_SLIME_3 8
#define MAX_SLIME_4 4

class CSlimeManager
{
public:
	CSlimeManager();
	~CSlimeManager();

	void Update();
	void Draw();
	void Generate(TTriType<float> pos);

private:
	CSlimeBase* m_pSlime[MAX_SLIME_1];

	int m_nRandNum;	//�����p
};

#endif // __SLIME_MANAGER_H__