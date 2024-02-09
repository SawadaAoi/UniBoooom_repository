/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�r�b�g���t���O��`(char�^)
	------------------------------------
	UcFlag.h
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2024/01/18 �쐬 takagi
	�E2024/01/20 �R���X�g���N�^�����ǉ� takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __UC_FLAG_H__	//UcFlag.h�C���N���[�h�K�[�h
#define __UC_FLAG_H__

// =============== �N���X��` =====================
class CUcFlag
{
public:
	// ===�v���g�^�C�v�錾===
	CUcFlag(const unsigned char& ucFlag = 0x00);	//�R���X�g���N�^
	CUcFlag(const CUcFlag& Obj);					//�R�s�[�R���X�g���N�^
	~CUcFlag();										//�f�X�g���N�^
	void Up(const unsigned char& ucFlag);			//�t���O�I��
	void Down(const unsigned char& ucFlag);			//�t���O�I�t
	bool Check(const unsigned char& ucFlag) const;	//�t���O�`�F�b�N
	const unsigned char& GetFlag() const;			//�t���O�Q�b�^
private:
	// ===�����o�ϐ��錾=====
	unsigned char m_ucFlag;	//�t���O�{��
};	//char�^�̃t���O

#endif	//!__UC_FLAG_H__