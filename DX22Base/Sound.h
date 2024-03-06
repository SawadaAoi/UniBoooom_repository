/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	������p�w�b�_
	------------------------------------
	Sound.h
	------------------------------------
	�쐬��	yamashita

	�ύX����
	�E2023/11/18 h,�쐬 yamashita
	�E2023/11/18 �搶��Sound.h����R�s�[���ăN���X�� yamashita
	�E2023/11/18 �R�����g�ǉ� yamashita
	�E2023/11/18 �N���X��ÓI�ɕύX yamashita
	�E2024/01/20 ����ǂݍ��񂾃X�s�[�J�[���������鉹��������H�����}�N����` takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __SOUND_H__	//Sound.h�C���N���[�h�K�[�h
#define __SOUND_H__

// =============== �C���N���[�h ===================
#include <xaudio2.h>
#include <mmsystem.h>
#include <mmreg.h>
#include <MSAcm.h>
#include <Shlwapi.h>
#include <vector>
#include <map>
#include <string>

#pragma comment(lib, "xaudio2.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "msacm32.lib")
#pragma comment(lib, "shlwapi.lib")

// =============== �萔�E�}�N����` =======================
const BYTE CMP_MATCH = 0;	//���cpp�Ɉړ�
#define UNLOAD_SOUND(pSpeaker)	do{if(pSpeaker){pSpeaker->Stop(); pSpeaker->DestroyVoice();}}while(0)	//���ǂݍ��݉���

// =============== �N���X��` =====================
class CSound
{
public:
	//CSound();
	//~CSound();

	struct SoundData
	{
		WAVEFORMATEX	format;		//WAV�t�H�[�}�b�g
		BYTE*			pBuffer;	//�T�E���h�f�[�^
		DWORD			bufSize;	//�f�[�^�T�C�Y
		XAUDIO2_BUFFER	sound;		//�T�E���h�o�b�t�@
	};
	struct MP3FormatInfo
	{
		DWORD	offset;
		DWORD	dataSize;
	};
	struct MP3FrameInfo
	{
		BYTE	channel;
		BYTE	padding;
		DWORD	sampleRate;
		DWORD	bitRate;
		DWORD	frameSize;
	};
	typedef std::map<std::string, SoundData> SoundList;		//���̂ƃT�E���h�f�[�^���ϐ�


	static HRESULT InitSound(void);	//����������
	static void UninitSound(void);	//�I������
	// �T�E���h�̓ǂݍ���
	static XAUDIO2_BUFFER* LoadSound(const char *file, bool loop = false);
	// �T�E���h�̍Đ�
#undef PlaySound	//���łɁuPlaySound�v�Ƃ����}�N�������݂��邪����𖳎�����(PlaySound���֐����Ƃ��Ă������肭�邩��)
	static IXAudio2SourceVoice* PlaySound(XAUDIO2_BUFFER* pSound);
private:
	static HRESULT LoadWav(const char *file, SoundData *pData);	//wav�t�@�C���̓ǂݍ���
	static HRESULT LoadMP3(const char *file, SoundData *pData);	//mp3�t�@�C���̓ǂݍ���
	static DWORD ReadMP3Format(HANDLE hFile, MP3FormatInfo *pFormat);										//MP3�t�H�[�}�b�g�`�F�b�N
	static DWORD ReadMP3FrameHeader(HANDLE hFile, DWORD seek, MP3FrameInfo *pFrame);						//MP3�T�E���h�t���[���w�b�_�ǂݍ���
	static DWORD ReadMP3Data(HANDLE hFile, DWORD seek, DWORD size, MP3FrameInfo *pFrame, SoundData *pData);	//MP3�T�E���h�f�[�^�ǂݍ���

	typedef std::pair<std::string, SoundData> SoundKey;		//���̂ƃT�E���h�f�[�^���ϐ�

	static IXAudio2 *m_pXAudio;						//XAudio2�̃C���^�[�t�F�[�X�|�C���^�[
	static IXAudio2MasteringVoice *m_pMasterVoice;	//�}�X�^�[�{�C�X�̃C���^�[�t�F�[�X�|�C���^�[
	static SoundList m_soundList;					//�\�[�X�{�C�X�̃��X�g
};

#endif	//!__SOUND_H__