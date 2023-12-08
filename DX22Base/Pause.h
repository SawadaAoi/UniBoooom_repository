/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ポーズ画面定義
	---------------------------------------
	Pause.h

	作成者	takagi

	変更履歴
	・2023/12/01 制作 takagi
	・2023/12/04 続き takagi
	・2023/12/06 pose→pause修正、ポーズ文字表示 takagi
	・2023/12/08 アクセス指定子間移動 takagi

========================================== */

#ifndef __PAUSE_H__	//Pause.hインクルードガード
#define __PAUSE_H__

#include "Sound.h"		//音
#include "Camera.h"		//カメラ
#include "2dPolygon.h"	//平面ポリゴン
#include <vector>		//配列コンテナ

// =============== クラス定義 =====================
class CPause
{
private:
	enum E_FLAG
	{
		E_FLAG_PAUSEMODE = 0x01,		//ポーズモード
		E_FLAG_COMMAND_CONTINUE = 0x02,	//継続コマンド
		E_FLAG_COMMAND_FINISH = 0x04,	//終了コマンド
		E_FLAG_DECIDE_COMMAND = 0x08,	//コマンド決定状態
		E_FLAG_CALL_FINISH = 0x10,		//終了予約
	};	//フラグ
public:
	// ===プロトタイプ宣言===
	CPause(const CCamera* pCamera);						//コンストラクタ
	~CPause();											//デストラクタ
	void Update();										//更新
	void Draw();										//描画
	bool IsFin() const;									//終了確認
	void SetCamera(const CCamera* pCamera = nullptr);	//カメラセッタ
	bool IsPause() const;								//ポーズ中か
private:
	// ===メンバ変数宣言=====
	unsigned char m_ucFlag;							//フラグ
	std::vector<C2dPolygon*> m_2dObj;				//平面ポリゴン
	PixelShader* m_pBgPs;							//背景用ピクセルシェーダ
	VertexShader* m_pBgVs;							//背景用頂点シェーダ
	//const CCamera* m_pCamera;						//カメラ
	const CCamera* m_pCameraDef;					//疑似カメラ
	XAUDIO2_BUFFER* m_pBGM;							//BGMの音声データ
	XAUDIO2_BUFFER* m_pSEHitHammer;					//SEの音声データ
	IXAudio2SourceVoice* m_pSpeaker;				//BGMを聞き取る側
	IXAudio2SourceVoice* m_pSEHitHammerSpeaker;		//SEを聞き取る側
	// ===プロトタイプ宣言===
	void Boot();									//ポーズモード起動
	void UpFlag(const unsigned char& ucBitFlag);	//フラグ起こし
	void DownFlag(const unsigned char& ucBitFlag);	//フラグ降ろし
	void SetFlag(const unsigned char& ucBitFlag);	//フラグ反転
};	//リザルト

#endif	//!__PAUSE_H__