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
	�E2023/11/19 �{�X�Q�[�W��������ϐ��A�֐����쐬 Tei
	�E2023/11/22 �{�X�Q�[�W�t�F�[�h�p�ϐ��ǉ� Tei
	�E2023/11/26 �X���C���Ǘ������o�ϐ��ǉ�	Sawada

========================================== */
#ifndef __BOSS_GAUGE_H__
#define __BOSS_GAUGE_H__

// =============== �C���N���[�h ===================
#include "Sprite.h"
#include <Texture.h>
#include "Pos3d.h"
#include "Timer.h"
#include "SlimeManager.h"

// =============== �N���X��` =====================
class CBossgauge
{
public:
	// ===�v���g�^�C�v�錾===
	CBossgauge(int* pTime);
	~CBossgauge();
	void Update();
	void Draw();

	void FillGaugeDraw(float textureRange);		//�{�X�Q�[�W�����ʕ`��֐�
	bool FirstBossGauge();
	bool SecondBossGauge();

	//void GetBossPos();	//�{�X���݂̈ʒu���擾(�v��H) ��ʊO�ɍs��������ŕ\������

	void SetSlimeManager(CSlimeManager* pSlimeMng);

private:
	// ===�����o�ϐ��錾===
	Texture* m_pBossGaugeEmpty;
	Texture* m_pBossGaugeFull;
	int m_nGaugeCnt;		//�{�X�Q�[�W�t���[�����Z�l
	bool m_bGaugeFull;		//�Q�[�W���^���t���O(���^�� = true)
	bool m_bShowBossGauge;	//�{�X�Q�[�W�\���t���O
	int* m_pTime;			//�c�莞�Ԃ̃|�C���^
	int m_nAdjustTime;		//�{�X�Q�[�W�\���^�C������
	float m_fFillGauge;		//�Q�[�W�̊���
	int m_nFadeCnt;			//�t�F�[�h�A�E�g����

	CSlimeManager* m_pSlimeMng;	// �X���C���Ǘ�(�{�X�����Ŏg�p����)
};


#endif // __BOSS_GAUGE_H__