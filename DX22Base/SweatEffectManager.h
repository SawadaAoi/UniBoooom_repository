/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   ���G�t�F�N�g�}�l�[�W���[ �N���X��`
   ---------------------------------------
   SweatEffectManager.h

   �쐬�ҁF�A�F��

   �ύX����
	�E2024/02/02 ���G�t�F�N�g�}�l�[�W���[�N���X�쐬 Tei
	�E2024/02/13 �J�����폜 takagi

=========================================== */
#ifndef __SWEAT_EFFECT_MANAGER_H__
#define __SWEAT_EFFECT_MANAGER_H__

// =============== �C���N���[�h ===================
#include "SweatEffect.h"

// =============== �萔��` =======================
const int	MAX_SWEAT_EFFECT_NUM = 1;	// �ő�G�t�F�N�g������

// =============== �N���X��` =====================
class CSweatEffectManager
{
public:
	CSweatEffectManager();
	~CSweatEffectManager();
	void Update(TTriType<float> pos);
	void Draw();
	void Create(TTriType<float> pos,  TTriType<float> radian);		// �G�t�F�N�g����
	void DeleteCheck();							// �g�����G�t�F�N�g���폜�֐�

private:
	CSweatEffect* m_pSweatEffect[MAX_SWEAT_EFFECT_NUM];
	//=======Effekseer=======
	Effekseer::EffectRef m_SweatEffect;
};


#endif // !__SWEAT_EFFECT_MANAGER_H__
