/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	音操作用ヘッダ
	------------------------------------
	Sound.h
	------------------------------------
	作成者	yamashita

	変更履歴
	・2023/11/18 h,作成 yamashita
	・2023/11/18 先生のSound.hからコピーしてクラス化 yamashita
	・2023/11/18 コメント追加 yamashita
	・2023/11/18 クラスを静的に変更 yamashita
	・2024/01/20 音を読み込んだスピーカーが所持する音を手放す工程をマクロ定義 takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __SOUND_H__	//Sound.hインクルードガード
#define __SOUND_H__

// =============== インクルード ===================
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

// =============== 定数・マクロ定義 =======================
const BYTE CMP_MATCH = 0;	//後でcppに移動
#define UNLOAD_SOUND(pSpeaker)	do{if(pSpeaker){pSpeaker->Stop(); pSpeaker->DestroyVoice();}}while(0)	//音読み込み解除

// =============== クラス定義 =====================
class CSound
{
public:
	//CSound();
	//~CSound();

	struct SoundData
	{
		WAVEFORMATEX	format;		//WAVフォーマット
		BYTE*			pBuffer;	//サウンドデータ
		DWORD			bufSize;	//データサイズ
		XAUDIO2_BUFFER	sound;		//サウンドバッファ
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
	typedef std::map<std::string, SoundData> SoundList;		//名称とサウンドデータ持つ変数


	static HRESULT InitSound(void);	//初期化処理
	static void UninitSound(void);	//終了処理
	// サウンドの読み込み
	static XAUDIO2_BUFFER* LoadSound(const char *file, bool loop = false);
	// サウンドの再生
#undef PlaySound	//すでに「PlaySound」というマクロが存在するがそれを無視する(PlaySoundが関数名としてしっくりくるから)
	static IXAudio2SourceVoice* PlaySound(XAUDIO2_BUFFER* pSound);
private:
	static HRESULT LoadWav(const char *file, SoundData *pData);	//wavファイルの読み込み
	static HRESULT LoadMP3(const char *file, SoundData *pData);	//mp3ファイルの読み込み
	static DWORD ReadMP3Format(HANDLE hFile, MP3FormatInfo *pFormat);										//MP3フォーマットチェック
	static DWORD ReadMP3FrameHeader(HANDLE hFile, DWORD seek, MP3FrameInfo *pFrame);						//MP3サウンドフレームヘッダ読み込み
	static DWORD ReadMP3Data(HANDLE hFile, DWORD seek, DWORD size, MP3FrameInfo *pFrame, SoundData *pData);	//MP3サウンドデータ読み込み

	typedef std::pair<std::string, SoundData> SoundKey;		//名称とサウンドデータ持つ変数

	static IXAudio2 *m_pXAudio;						//XAudio2のインターフェースポインター
	static IXAudio2MasteringVoice *m_pMasterVoice;	//マスターボイスのインターフェースポインター
	static SoundList m_soundList;					//ソースボイスのリスト
};

#endif	//!__SOUND_H__