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

========================================== */
#ifndef __STAGE_FINISH_UI_H__
#define __STAGE_FINISH_UI_H__

// =============== インクルード ===================
#include "Texture.h"
#include "GameParameter.h"

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

	CStageFinish(int* pPlayerHp,int* pTimeCnt);
	~CStageFinish();
	void Update();
	void Draw();
	bool GetDispFlg();

private:
	void EditSprite(int);

	bool m_bDispFlg;
	GAME_STATE m_eGameState;
	const int* m_pPlayerHp;
	const int* m_pTimeCnt;
	bool m_bDeleteDisp;

	Texture* m_pTexGameClear;
	Texture* m_pTexGameOver;

	TPos2d<float> m_fUVPos;	// UV座標保存用
	int m_nCntSwitch;		// アニメーション切り替えカウント用
	int m_nCntW;			// 横カウント用
	int m_nCntH;			// 縦カウント用
};

#endif // !__STAGE_FINISH_UI_H__