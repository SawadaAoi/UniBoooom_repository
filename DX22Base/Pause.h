/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�|�[�Y��ʒ�`
	---------------------------------------
	Pause.h

	�쐬��	takagi

	�ύX����
	�E2023/12/01 ���� takagi
	�E2023/12/04 ���� takagi
	�E2023/12/06 pose��pause�C���A�|�[�Y�����\�� takagi
	�E2023/12/08 �A�N�Z�X�w��q�Ԉړ� takagi
	�E2023/12/09 �I�u�W�F�N�g���� takagi
	�E2023/12/10 ����i�s takagi
	�E2023/12/12 �t���O�ǉ� takagi
	�E2024/01/26 �I��.����.�|�[�YSE�ǉ� suzumura
	�E2024/02/09 �J�����폜 takagi

========================================== */

#ifndef __PAUSE_H__	//Pause.h�C���N���[�h�K�[�h
#define __PAUSE_H__

// =============== �C���N���[�h =====================
#include "Sound.h"		//��
#include "PauseObj.h"	//�����o�̃w�b�_
#include <vector>		//�z��R���e�i

// =============== �N���X��` =====================
class CPause
{
private:
	// ===�񋓒�`==========
	enum E_FLAG
	{
		E_FLAG_PAUSEMODE = 0x01,		//�|�[�Y���[�h
		E_FLAG_COMMAND_CONTINUE = 0x02,	//�p���R�}���h
		E_FLAG_COMMAND_FINISH = 0x04,	//�I���R�}���h
		E_FLAG_DECIDE_COMMAND = 0x08,	//�R�}���h������
		E_FLAG_TIDYING_UP = 0x10,		//�Еt����
		E_FLAG_CALL_FINISH = 0x20,		//�I���\��
	};	//�t���O

	enum SE
	{
		SE_DECISION,	//���艹
		SE_CHOOSE,		//���ڑI��SE
		SE_PAUSE,		//�|�[�Y��
		SE_MAX			//SE�̑���
	}; //SE
public:
	// ===�v���g�^�C�v�錾===
	CPause();				//�R���X�g���N�^
	~CPause();				//�f�X�g���N�^
	void Update();			//�X�V
	void Draw();			//�`��
	bool IsFin() const;		//�I���m�F
	bool IsPause() const;	//�|�[�Y����
private:
	// ===�����o�ϐ��錾=====
	unsigned char m_ucFlag;				//�t���O
	std::vector<CPauseObj*> m_p2dObj;	//���ʃ|���S��
	// ===�v���g�^�C�v�錾===
	void Boot();									//�|�[�Y���[�h�N��
	void InitObjects();								//�������E���I�m��
	void Destroy();									//�|�[�Y�I��
	void UpFlag(const unsigned char& ucBitFlag);	//�t���O�N����
	void DownFlag(const unsigned char& ucBitFlag);	//�t���O�~�낵
	void SetFlag(const unsigned char& ucBitFlag);	//�t���O���]
	void LoadSound();								//�T�E���h�����[�h
	void PlaySE(SE se, float volume = 1.0f);		//SE���Đ�����

	//=====SE�֘A=====
	XAUDIO2_BUFFER* m_pSE[SE_MAX];
	IXAudio2SourceVoice* m_pSESpeaker[SE_MAX];
	const std::string m_sSEFile[SE_MAX] = {
		"Assets/Sound/SE/Decision.mp3",				// ���艹
		"Assets/Sound/SE/Select_Cursor.mp3", 		// �I����
		"Assets/Sound/SE/Pause.mp3" 				// �|�[�Y��
	};
};

#endif	//!__PAUSE_H__