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
	�E2024/02/02 �ꕔ�֐�const���A���łɌp�����Ă��G��Ȃ��悤��final�֐��� takagi

========================================== */

#ifndef __FRAME_CNT_H__	//FrameCnt.h�C���N���[�h�K�[�h
#define __FRAME_CNT_H__

// =============== �N���X��` =====================
class CFrameCnt	//�V�X�e��
{
public:
	// ===�v���g�^�C�v�錾===
	CFrameCnt(const unsigned int& nEndFrame, const bool& bCntDown = true);	//�R���X�g���N�^
	virtual ~CFrameCnt();													//�f�X�g���N�^
	virtual CFrameCnt& operator++() final;									//'++'���Z�q�̃I�[�o�[���[�h(�J�E���g�A�b�v�p)
	virtual CFrameCnt& operator--() final;									//'--'���Z�q�̃I�[�o�[���[�h
	virtual void Count() final;												//�J�E���g�i�s
	virtual bool IsFin() const final;										//�J�E���g�̏I���m�F
	virtual float GetRate() const final;									//�i�s���l��
	virtual int GetCnt() const final;										//���݃t���[�����擾
private:
	// ===�����o�ϐ��錾=====
	unsigned int m_nEndFrame;	//�ŏI�t���[����
	unsigned int m_nFrame;		//���݃t���[����
	bool m_bCntDown;	//true:�J�E���g�_�E��	false:�J�E���g�A�b�v
};	//�J�E���^

#endif // !__FRAME_CNT_H__