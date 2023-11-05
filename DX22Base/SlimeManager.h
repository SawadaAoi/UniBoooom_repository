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

#define MAX_SLIME_1 10

class CSlimeManager
{
public:
	CSlimeManager();
	~CSlimeManager();

	void Update();
	void Draw();
	void Generate(TTriType<float> pos);

private:
	int m_nRandNum;	//�����p
};

#endif // __SLIME_MANAGER_H__