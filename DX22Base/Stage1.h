/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X�e�[�W1��`
	---------------------------------------
	Stage1.h

	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/11/05 ���� takagi
	�E2023/11/07 �R�����g�C�� takagi
	�E2023/11/16 Prot.h��Stage1.h takagi

========================================== */

#ifndef __STAGE1_H__	//Stage1.h�C���N���[�h�K�[�h
#define __STAGE1_H__

// =============== �C���N���[�h ===================
#include "Stage.h"	//�e�̃w�b�_

// =============== �N���X��` =====================
class CStage1 :public CStage	//�X�e�[�W
{
public:
	// ===�v���g�^�C�v�錾===
	CStage1();		//�R���X�g���N�^
	~CStage1();									//�f�X�g���N�^
	void Update();						//�X�V
	void Draw();						//�`��	
	E_TYPE GetType() const override;	//���g�̎�ރQ�b�^
	E_TYPE GetNext() const override;	//���̃V�[���Q�b�^
private:
	int m_nNum;			// �Q�[���X�^�[�g�\���J�E���g�p
	float m_fSize;		// �Q�[���X�^�[�g�\���̃T�C�Y
	float m_fResize;	// �Q�[���X�^�[�g�\���̃T�C�Y�ύX�p
	bool m_bStart;		// �Q�[�����J�n�����邩����
	const int* m_pPlayerHp;		// �v���C���[HP�擾�p
	const int* m_pTimeCnt;		// �������Ԏ擾�p

	TPos2d<float> m_fUVPos;	// UV���W�ۑ��p
	int m_nCntSwitch;	// �A�j���[�V�����؂�ւ��J�E���g�p
	int m_nCntW;		// ���J�E���g�p
	int m_nCntH;		// �c�J�E���g�p
	bool m_bStartSign;		// �X�^�[�g���}�J�n�t��
};	//�X�e�[�W1

#endif	//!__STAGE1_H__