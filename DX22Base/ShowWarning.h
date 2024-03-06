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
	・2024/02/20 手配書描画調整 Tei

========================================== */
#ifndef __SHOW_WARNING_H__
#define __SHOW_WARNING_H__

// =============== インクルード ===================
#include <Texture.h>
#include "Pos2d.h"	//二次元座標
#include "Timer.h"
#include "SlimeManager.h"

class CUIStageManager;

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
	void DrawWarningBoss(TPos2d<float> fpos, TPos2d<float> fsize, TPos2d<float> fScale, Texture* pBoss);		// 警告手配書描画
	void ShowArrangement();		//手配書調整関数
	void ArrangementColorMotion(float fColor, int nFlame, float fAlpha);	// 手配書色調整関数
	void ArrangementScaleMotion(TPos2d<float> fSize, int nFlame, float fAlpha);	// 手配書拡縮関数


	void StartShowWarning();
	void SetUIStageManagerPtr(CUIStageManager* pUIMng);

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
	float m_fArrangementColorAdjust;
	TPos2d<float> m_fArrangementScaleAdjust;	// 手配書スケール調整量
	int m_nArrangementCnt;		// 手配書調整用カウント
	bool m_bArrangementShow;	// 手配書表示フラグ


	int m_nStageNum;			// ステージ番号
	bool m_bDispFlg;			// 警告表示フラグ
	int m_nDispCnt;				// 表示加算値

	TPos2d<float> m_fArrangementSizeAdjust;	// 手配書サイズ調整量
	CUIStageManager* m_pUIMng;
};





#endif // !__SHOW_WARNING_H__
