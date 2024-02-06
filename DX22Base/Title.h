/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�^�C�g���V�[����`
	---------------------------------------
	Title.h

	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/10/26 ������ takagi
	�E2023/11/05 ���i�K�̃R�[�f�B���O�K��K�p takagi
	�E2023/11/07 �R�����g�C�� takagi
	�E2023/11/16 �I�[�o�[���C�h�֐��ǉ� takagi
	�E2023/12/16 �`�敨���P takagi
	�E2024/01/26 �I���A����SE�ǉ�
	�E2024/02/02 ���t�@�N�^�����O takagi
	�E2024/02/05 ���t�@�N�^�����O takagi
	�E2024/02/06 ���t�@�N�^�����O takagi

========================================== */

#ifndef __TITLE_H__	//Title.h�C���N���[�h�K�[�h
#define __TITLE_H__

// =============== �C���N���[�h ===================
#include "Scene.h"					//�e�̃w�b�_
#include <map>						//�A�z�R���e�i
#include "Sound.h"					//�T�E���h�w�b�_
#include <memory>					//shared_ptr/shared_ptr
#include "TitleBgBase.h"			//�����o�̃w�b�_
#include "TitleBgReaf.h"			//�����o�̃w�b�_
#include "TitleBgGrass.h"			//�����o�̃w�b�_
#include "TitleBgPlayer.h"			//�����o�̃w�b�_
#include "TitleBgCloud.h"			//�����o�̃w�b�_
#include "TitleCommandStart.h"	//�����o�̃w�b�_
#include "TitleCommandFinish.h"		//�����o�̃w�b�_
#include "TitleLogo.h"				//�����o�̃w�b�_

// =============== �N���X��` =====================
class CTitle :public CScene	//�V�[��
{
private:
	// ===�񋓒�`==========
	enum E_FLAG
	{
		//E_FLAG_PAUSEMODE = 0x01,		//�|�[�Y���[�h
		E_FLAG_COMMAND_START = 0x02,	//�J�n�R�}���h
		E_FLAG_COMMAND_FINISH = 0x04,	//�I���R�}���h
		E_FLAG_DECIDE_COMMAND = 0x08,	//�R�}���h������
		//E_FLAG_TIDYING_UP = 0x10,		//�Еt����
		//E_FLAG_CALL_FINISH = 0x20,		//�I���\��
	};	//�t���O

	enum SE
	{
		SE_DECISION,	//���艹
		SE_CHOOSE,		//���ڑI��SE
		SE_MAX			//SE�̑���
	};
public:
	// =============== �v���g�^�C�v�錾 ===============
	CTitle();							//�R���X�g���N�^
	~CTitle();							//�f�X�g���N�^
	void Update() override;				//�X�V
	void Draw() override;				//�`��	
	E_TYPE GetType() const override;	//���g�̎�ރQ�b�^
	E_TYPE GetNext() const override;	//���̃V�[���Q�b�^
private:
	// ===�����o�ϐ��錾=====
	std::shared_ptr<CTitleBgBase> m_pBgBase;				//�w�i
	std::shared_ptr<CTitleBgCloud> m_pBgCloud;				//�w�i�̉_
	std::shared_ptr<CTitleBgPlayer> m_pBgPlayer;			//�w�i�̃v���C���[
	std::shared_ptr<CTitleBgGrass> m_pBgGrass;				//�w�i�̑�
	//std::shared_ptr<CTitleBgLeaf> m_pBgLeaf;				//�w�i�̗t
	std::shared_ptr<CTitleCommandStart> m_pCommandStart;	//�J�n�R�}���h
	std::shared_ptr<CTitleCommandFinish> m_pCommandFinish;	//�I���R�}���h
	std::shared_ptr<CTitleLogo> m_pLogo;					//�^�C�g�����S
	unsigned char m_ucFlag;									//�t���O
	E_TYPE m_eNextScene;									//�V�[���J�ڐ�
	// ===�v���g�^�C�v�錾===
	void UpFlag(const unsigned char& ucBitFlag);	//�t���O�N����
	void DownFlag(const unsigned char& ucBitFlag);	//�t���O�~�낵
	void SetFlag(const unsigned char& ucBitFlag);	//�t���O���]
	void LoadSound();								//�^�C�g���p�̃T�E���h�����[�h
	void PlaySE(SE se, float volume = 1.0f);		//SE���Đ�����
	//=====SE�֘A=====
	XAUDIO2_BUFFER* m_pSE[SE_MAX];
	IXAudio2SourceVoice* m_pSESpeaker[SE_MAX];
	const std::string m_sSEFile[SE_MAX] = {
		"Assets/Sound/SE/Decision.mp3",			// ���艹
		"Assets/Sound/SE/Select_Cursor.mp3" 	// �I����
	};
};	//�^�C�g��

#endif	//!__TITLE_H__