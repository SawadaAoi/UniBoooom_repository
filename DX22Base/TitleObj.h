/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�^�C�g���p2D�I�u�W�F��`
	---------------------------------------
	TitleObj.h

	�쐬��	takagi

	�ύX����
	�E2023/12/16 ���� takagi
	�E2023/12/17 ChackPutOut()�֐��ǉ��E�����Q�Ɖ� takagi

========================================== */

#ifndef __TITLE_OBJ_H__	//TitleObj.h�C���N���[�h�K�[�h
#define __TITLE_OBJ_H__

// =============== �C���N���[�h =====================
#include "2dPolygon.h"	//�e�̃w�b�_

// =============== �N���X��` =====================
class CTitleObj :public C2dPolygon	//���ʃI�u�W�F
{
public:
	// ===�v���g�^�C�v�錾===
	CTitleObj(const int& nWaitTime = 0);								//�R���X�g���N�^
	~CTitleObj();														//�f�X�g���N�^
	void Update() override;												//�X�V
	void Draw(const E_DRAW_MODE & eMode = E_DRAW_MODE_NORMAL) override;	//�`��
	bool ChackDraw();													//�\�����Ă��邩
private:
	// ===�����o�ϐ��錾=====
	int* m_pnWaitTime;	//�����ҋ@���Ԍv��
};	//�^�C�g���p�I�u�W�F

#endif	//!__TITLE_OBJ_H__