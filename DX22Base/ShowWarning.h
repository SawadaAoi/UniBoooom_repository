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
	CShowWarning(int nStageNum);
	~CShowWarning();
	void Update();
	void Draw();
	void DrawWarningBG(TPos2d<float> fpos, TPos2d<float> fsize, float xMove);			// 警告背景描画
	void DrawWarningTex(TPos2d<float> fpos, TPos2d<float> fsize, float xMove);			// 警告文字描画
	void DrawWarningBoss(TPos2d<float> fpos, TPos2d<float> fsize, Texture* pBoss);		// 警告手配書描画
	void ArrangementAdjust();		//手配書調整関数

	void StartShowWarning();

	
	// ゲッター関数
	bool GetDispFlg();

private:
	Texture* m_pWarningBG;		// 警告BG
	Texture* m_pWarningTex;		// 警告文字
	Texture* m_pBossS2;			// ステージ２ボスの手配書
	Texture* m_pBossS3;			// ステージ３ボスの手配書
	float m_fBGMove;			// 警告背景移動量
	float m_fTopTexMove;		// 上警告文字移動量
	float m_fBotTexMove;		// 下警告文字移動量
	float m_fBGAlpha;			// 警告背景の透明度
	float m_fArrangementAlpha;	// 手配書のα値

	int m_nStageNum;			// ステージ番号
	bool m_bDispFlg;			// 警告表示フラグ
	int m_nDispCnt;				// 表示加算値

	TPos2d<float> m_fArrangementSizeAdjust;	// 手配書サイズ調整量
	
};





#endif // !__SHOW_WARNING_H__
