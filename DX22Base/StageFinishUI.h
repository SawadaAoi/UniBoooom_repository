/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	StageFinishUI用ヘッダ
	------------------------------------
	StageFinishUI.h
	------------------------------------
	作成者	yamashita

	変更履歴
	・2023/11/20 h,作成 yamashita
	・2023/11/20 ゲームのプレイ状態を列挙 yamashita
	・2023/12/07 自動でシーン遷移させるためのフラグ取得関数追加 nieda
	・2023/12/16 不要な変数など削除 nieda
	・2024/01/20 コメント改修 takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __STAGE_FINISH_UI_H__	//StageFinishUI.hインクルードガード
#define __STAGE_FINISH_UI_H__

// =============== インクルード ===================
#include "2dObject.h"
#include "Texture.h"
#include "GameParameter.h"
#include "GameClearText.h"
#include "GameOverText.h"

class CStageFinish :public C2dObject
{
public:
	enum GAME_STATE
	{
		GAME_NONE,

		GAME_PLAY,
		GAME_CLEAR,
		GAME_OVER,

		MAX_STATE
	};

	CStageFinish();
	~CStageFinish();
	void Update();
	void Draw();
	virtual void SetCamera(const CCamera* pCamera) override;
	bool GetGameEndFlg();	// 画面遷移フラグ取得用

	bool GetClearFlg();
	void SetPlHp(int* pPlayerHp);
	void SetTime(int* pTimeCnt);
private:
	GAME_STATE m_eGameState;
	const int* m_pPlayerHp;
	const int* m_pTimeCnt;
	bool m_bGameEnd;

	CClearText* m_pClear;
	COverText* m_pOver;
};

#endif	//!__STAGE_FINISH_UI_H__