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

========================================== */
#ifndef __SHOW_WARNING_H__
#define __SHOW_WARNING_H__

// =============== CN[h ===================
#include <Texture.h>
#include "Pos2d.h"	//ñ³ÀW
#include "Timer.h"
#include "SlimeManager.h"


// =============== NXè` =====================
class CShowWarning
{
public:
	CShowWarning();
	~CShowWarning();
	void Update();
	void Draw();
	void DrawWarningBG(TPos2d<float> fpos, TPos2d<float> fsize, float xMove);
	void DrawWarningTex(TPos2d<float> fpos, TPos2d<float> fsize, float xMove);
	void DrawWarningBoss(TPos2d<float> fpos, TPos2d<float> fsize, Texture* pBoss, float fSping);
	void SetTimer(CTimer* pTimer);
	void SetSlimeMng(CSlimeManager* pBoss);
private:
	CTimer* m_pTimer;
	Texture* m_pWarningBG;		// xBG
	Texture* m_pWarningTex;		// x¶
	Texture* m_pBossS2;
	Texture* m_pBossS3;
	CSlimeManager* m_pBoss;
	float m_fBGMove;			// xwiÚ®Ê
	float m_fTopTexMove;		// ãx¶Ú®Ê
	float m_fBotTexMove;		// ºx¶Ú®Ê
	float m_fBGalpha;			// xwiÌ§¾x
	float m_fArrangementSping;
	TPos2d<float> m_fArrangementSizeAdjust;
	
};





#endif // !__SHOW_WARNING_H__
