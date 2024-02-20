/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	{Xo»xwb_
	------------------------------------
	ShowWarning.h
	------------------------------------
	ì¬Ò
		AF¶
	ÏXð
	E2024/02/11 NXè`ì¬ Tei
	E2024/02/20 èz`æ²® Tei

========================================== */
#ifndef __SHOW_WARNING_H__
#define __SHOW_WARNING_H__

// =============== CN[h ===================
#include <Texture.h>
#include "Pos2d.h"	//ñ³ÀW
#include "Timer.h"
#include "SlimeManager.h"

class CUIStageManager;

// =============== NXè` =====================
class CShowWarning
{
public:
	CShowWarning(int nStageNum);
	~CShowWarning();
	void Update();
	void Draw();
	void DrawWarningBG(TPos2d<float> fpos, TPos2d<float> fsize, float xMove);			// xwi`æ
	void DrawWarningTex(TPos2d<float> fpos, TPos2d<float> fsize, float xMove);			// x¶`æ
	void DrawWarningBoss(TPos2d<float> fpos, TPos2d<float> fsize, TPos2d<float> fScale, Texture* pBoss);		// xèz`æ
	void ShowArrangement();		//èz²®Ö
	void ArrangementColorMotion(float fColor, int nFlame, float fAlpha);	// èzF²®Ö
	void ArrangementScaleMotion(TPos2d<float> fSize, int nFlame, float fAlpha);	// èzgkÖ


	void StartShowWarning();
	void SetUIStageManagerPtr(CUIStageManager* pUIMng);

	// Qb^[Ö
	bool GetDispFlg();

private:
	Texture* m_pWarningBG;		// xBG
	Texture* m_pWarningTex;		// x¶
	Texture* m_pBossS2;			// Xe[WQ{XÌèz
	Texture* m_pBossS3;			// Xe[WR{XÌèz
	float m_fBGMove;			// xwiÚ®Ê
	float m_fTopTexMove;		// ãx¶Ú®Ê
	float m_fBotTexMove;		// ºx¶Ú®Ê
	float m_fBGAlpha;			// xwiÌ§¾x
	float m_fArrangementAlpha;	// èzÌ¿l
	float m_fArrangementColorAdjust;
	TPos2d<float> m_fArrangementScaleAdjust;	// èzXP[²®Ê
	int m_nArrangementCnt;		// èz²®pJEg
	bool m_bArrangementShow;	// èz\¦tO


	int m_nStageNum;			// Xe[WÔ
	bool m_bDispFlg;			// x\¦tO
	int m_nDispCnt;				// \¦ÁZl

	TPos2d<float> m_fArrangementSizeAdjust;	// èzTCY²®Ê
	CUIStageManager* m_pUIMng;
};





#endif // !__SHOW_WARNING_H__
