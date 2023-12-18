/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	StageFinishUI用ヘッダ
	------------------------------------
	StageFinishUI.h
	------------------------------------
	作成者
		yamashita
	変更履歴
	・2023/11/20 h,作成 Yamashita
	・2023/11/20 ゲームのプレイ状態を列挙 yamashita
	・2023/12/07 自動でシーン遷移させるためのフラグ取得関数追加 nieda
	・2023/12/16 不要な変数など削除 nieda

========================================== */
#ifndef __STAGE_FINISH_UI_H__
#define __STAGE_FINISH_UI_H__

// =============== インクルード ===================
#include "Texture.h"
#include "GameParameter.h"
#include "GameClearText.h"
#include "GameOverText.h"

class CStageFinish
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

	CStageFinish(CCamera* pCamera, int* pPlayerHp,int* pTimeCnt);
	~CStageFinish();
	void Update();
	void Draw();
	bool GetDispFlg();
	bool GetDeleteDispFlg();	// 画面遷移フラグ取得用

private:
	bool m_bDispFlg;
	GAME_STATE m_eGameState;
	const int* m_pPlayerHp;
	const int* m_pTimeCnt;
	bool m_bDeleteDisp;

	CClearText* m_pClear;
	COverText* m_pOver;
};

#endif // !__STAGE_FINISH_UI_H__