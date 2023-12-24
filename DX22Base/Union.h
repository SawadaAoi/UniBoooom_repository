/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	UNION��`
	---------------------------------------
	Union.h

	�쐬��	takagi

	�ύX����
	�E2023/12/20 ���� takagi
	�E2023/12/24 �t���[���ύX���}�l�[�W���� takagi

========================================== */

#ifndef __UNION_H__	//Union.h�C���N���[�h�K�[�h
#define __UNION_H__

// =============== �C���N���[�h =====================
#include "TitleAnime.h"	//�e�̃w�b�_
#include "FrameCnt.h"	//�����o�̃w�b�_

// =============== �N���X��` =====================
class CUnion :public CTitleAnime	//�A�j���[�V����
{
public:
	// ===�v���g�^�C�v�錾===
	CUnion(const int& nFrame);											//�R���X�g���N�^
	~CUnion();															//�f�X�g���N�^
	void Update() override;												//�X�V
	void Draw(const E_DRAW_MODE & eMode = E_DRAW_MODE_NORMAL) override;	//�`��
	bool IsFin();														//�I���Q�b�^
private:
	// ===�ϐ��錾===========
	CFrameCnt* m_pCnt;	//�J�E���^
	float Decrease;		//���Z��
};	//�^�C�g�����S

#endif	//!__UNION_H__