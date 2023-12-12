/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�{�X�����\�����p�w�b�_
	------------------------------------
	BossArrow.h
	------------------------------------
	�쐬��
		�A�F��
	�ύX����
	�E2023/12/08 h,�쐬 Tei

========================================== */
#ifndef __BOSS_ARROW_H__
#define __BOSS_ARROW_H__

// =============== �C���N���[�h ===================
#include "Sprite.h"
#include <Texture.h>
#include "Pos2d.h"
#include "Camera.h"
#include "SlimeManager.h"
#include "Player.h"

// =============== �N���X��` =====================
class CBossArrow
{
public:
	// ===�v���g�^�C�v�錾===
	CBossArrow();
	~CBossArrow();
	void Update();
	void Draw();
	void SetSlimeMng(CSlimeManager* mSlimeMng);
	void SetPlayer(CPlayer* mPlayer);
protected:

private:
	// ===�����o�ϐ��錾===
	Texture* m_pArrowTex;
	TPos2d<float> m_pos;			// �`��̈ʒu
	float m_radian;					// �`��̊p�x
	CSlimeManager* m_pBoss;			// �X���C���}�l�[�W���[�|�C���^�擾
	CPlayer* m_pPlayer;				// �v���C���[�|�C���^�擾
	bool m_bShowArrowFlg;			// �\���I���t���O
	
};


#endif // __BOSS_ARROW_H__