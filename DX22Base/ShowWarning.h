/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ボス出現警告ヘッダ
	------------------------------------
	ShowWarning.h
	------------------------------------
	作成者
		鄭宇恩
	変更履歴
	・2024/02/11 クラス定義作成 Tei

========================================== */
#ifndef __SHOW_WARNING_H__
#define __SHOW_WARNING_H__

// =============== インクルード ===================
#include <Texture.h>
#include "Pos2d.h"	//二次元座標
#include "Timer.h"
#include "SlimeManager.h"


// =============== クラス定義 =====================
class CShowWarning
{
public:
	CShowWarning();
	~CShowWarning();
	void Update();
	void Draw();
	void DrawWarningBG(TPos2d<float> fpos, TPos2d<float> fsize, float xMove);
	void DrawWarningTex(TPos2d<float> fpos, TPos2d<float> fsize, float xMove);
	void DrawWarningBoss(TPos2d<float> fpos, TPos2d<float> fsize, Texture* pBoss);
	void ArrangementAdjust();

	// セット関数
	void SetTimer(CTimer* pTimer);
	void SetSlimeMng(CSlimeManager* pBoss);
private:
	CTimer* m_pTimer;
	Texture* m_pWarningBG;		// 警告BG
	Texture* m_pWarningTex;		// 警告文字
	Texture* m_pBossS2;
	Texture* m_pBossS3;
	CSlimeManager* m_pBoss;
	float m_fBGMove;			// 警告背景移動量
	float m_fTopTexMove;		// 上警告文字移動量
	float m_fBotTexMove;		// 下警告文字移動量
	float m_fBGAlpha;			// 警告背景の透明度
	float m_fArrangementAlpha;
	TPos2d<float> m_fArrangementSizeAdjust;
	
};





#endif // !__SHOW_WARNING_H__
