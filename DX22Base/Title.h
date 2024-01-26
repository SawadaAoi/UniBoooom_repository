/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	タイトルシーン定義
	---------------------------------------
	Title.h

	作成者
			takagi
			nieda

	変更履歴
	・2023/10/26 仮制作 takagi
	・2023/11/05 現段階のコーディング規約適用 takagi
	・2023/11/07 コメント修正 takagi
	・2023/11/16 オーバーライド関数追加 takagi
	・2023/12/16 描画物改善 takagi
	・2024/01/26 選択、決定SE追加

========================================== */

#ifndef __TITLE_H__	//Title.hインクルードガード
#define __TITLE_H__

// =============== インクルード ===================
#include "Scene.h"		//親のヘッダ
#include "2dPolygon.h"	//メンバのヘッダ
#include <map>			//連想コンテナ
#include "Sound.h"		//サウンドヘッダ

// =============== クラス定義 =====================
class CTitle :public CScene	//シーン
{
private:
	// ===列挙定義==========
	enum E_FLAG
	{
		//E_FLAG_PAUSEMODE = 0x01,		//ポーズモード
		E_FLAG_COMMAND_CONTINUE = 0x02,	//継続コマンド
		E_FLAG_COMMAND_FINISH = 0x04,	//終了コマンド
		E_FLAG_DECIDE_COMMAND = 0x08,	//コマンド決定状態
		E_FLAG_TIDYING_UP = 0x10,		//片付け中
		//E_FLAG_CALL_FINISH = 0x20,		//終了予約
	};	//フラグ

	enum SE
	{
		SE_DECISION,	//決定音
		SE_CHOOSE,		//項目選択SE

		SE_MAX			//SEの総数
	};
public:
	// =============== プロトタイプ宣言 ===============
	CTitle();							//コンストラクタ
	~CTitle();							//デストラクタ
	void Update() override;				//更新
	void Draw() override;				//描画	
	E_TYPE GetType() const override;	//自身の種類ゲッタ
	E_TYPE GetNext() const override;	//次のシーンゲッタ
private:
	// ===メンバ変数宣言=====
	unsigned char m_ucFlag;					//フラグ
	std::map<int, C2dPolygon*> m_p2dObj;	//平面ポリゴン
	E_TYPE m_eNextScene;					//シーン遷移先
	// ===プロトタイプ宣言===
	void UpFlag(const unsigned char& ucBitFlag);	//フラグ起こし
	void DownFlag(const unsigned char& ucBitFlag);	//フラグ降ろし
	void SetFlag(const unsigned char& ucBitFlag);	//フラグ反転
	void LoadSound();								//タイトル用のサウンドをロード
	void PlaySE(SE se, float volume = 1.0f);		//SEを再生する

	//=====SE関連=====
	XAUDIO2_BUFFER* m_pSE[SE_MAX];
	IXAudio2SourceVoice* m_pSESpeaker[SE_MAX];
	const std::string m_sSEFile[SE_MAX] = {
		"Assets/Sound/SE/Decision.mp3",			// 決定音
		"Assets/Sound/SE/Select_Cursor.mp3" 	// 選択音
	};
};	//タイトル

#endif	//!__TITLE_H__