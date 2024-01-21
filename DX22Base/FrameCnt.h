/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�t���[���J�E���^��`
	------------------------------------
	FrameCnt.h
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/12/16 �쐬 takagi
	�E2024/01/16 ����̂��߁A�C���N���[�h�K�[�h��___��__�ɕύX	takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __FRAME_CNT_H__	//FrameCnt.h�C���N���[�h�K�[�h
#define __FRAME_CNT_H__

// =============== �N���X��` =====================
class CFrameCnt	//�V�X�e��
{
public:
	// ===�v���g�^�C�v�錾===
	CFrameCnt(const unsigned int& nEndFrame, const bool& bCntDown = true);	//�R���X�g���N�^
	~CFrameCnt();															//�f�X�g���N�^
	CFrameCnt& operator++();												//'++'���Z�q�̃I�[�o�[���[�h(�J�E���g�A�b�v�p)
	CFrameCnt& operator--();												//'--'���Z�q�̃I�[�o�[���[�h
	void Count();															//�J�E���g�i�s
	bool IsFin();															//�J�E���g�̏I���m�F
	float GetRate();														//�i�s���l��
	int GetCnt();															//���݃t���[�����擾
private:
	// ===�����o�ϐ��錾=====
	unsigned int m_nEndFrame;	//�ŏI�t���[����
	unsigned int m_nFrame;		//���݃t���[����
	bool m_bCntDown;	//true:�J�E���g�_�E��	false:�J�E���g�A�b�v
};	//�J�E���^

#endif	//!__FRAME_CNT_H__