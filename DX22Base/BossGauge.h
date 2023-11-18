/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	boss�o���p�w�b�_
	------------------------------------
	BossGauge.h
	------------------------------------
	�쐬��
		�A�F��
	�ύX����
	�E2023/11/17 h,�쐬 Tei
	
========================================== */
#ifndef __BOSS_GAUGE_H__
#define __BOSS_GAUGE_H__

// =============== �C���N���[�h ===================
#include "Sprite.h"
#include <Texture.h>
#include "Pos3d.h"

// =============== �N���X��` =====================
class CBossgauge
{
public:
	// ===�v���g�^�C�v�錾===
	CBossgauge();
	~CBossgauge();
	void Update();
	void Draw();

	void GetBossPos();	//�{�X���݂̈ʒu���擾(�v��H) ��ʊO�ɍs������A�C�R���ŕ\������


private:
	// ===�����o�ϐ��錾===
	Texture* m_pBossGauge;	
	int m_nGaugeCnt;		//�{�X�Q�[�W�t���[�����Z�l
	bool m_bGaugeFull;		//�Q�[�W���^���t���O(���^�� = true)
	TPos3d<float> pos;

};


#endif // __BOSS_GAUGE_H__