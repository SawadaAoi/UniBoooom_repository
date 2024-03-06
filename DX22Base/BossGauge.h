/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	boss出現用ヘッダ
	------------------------------------
	BossGauge.h
	------------------------------------
	作成者
		鄭宇恩
	変更履歴
	・2023/11/17 h,作成 Tei
	・2023/11/19 ボスゲージ増加する変数、関数を作成 Tei
	・2023/11/22 ボスゲージフェード用変数追加 Tei
	・2023/11/26 スライム管理メンバ変数追加	Sawada
	・2024/02/16 ボスゲージスケールモーション追加 Tei

========================================== */
#ifndef __BOSS_GAUGE_H__
#define __BOSS_GAUGE_H__

// =============== インクルード ===================
#include "Sprite.h"
#include <Texture.h>
#include "Pos3d.h"
#include "Timer.h"
#include "SlimeManager.h"
#include "2dPolygon.h"	//平面ポリゴン
#include <vector>
#include "Camera.h"
#include "ShowWarning.h"

// =============== クラス定義 =====================
class CBossgauge
{
public:
	// ===列挙定義===========
	typedef struct
	{
		int	 nBossNum;			// 生成ボス種類
		bool bDelFlg;			// 削除フラグ
		bool bFadeFlg;			// フェードフラグ
		int	nStartFrame;		// 開始時間Frame
		int nMaxGaugeFrame;		// 最大値Frame
		int nGaugeCnt;			// ゲージ加算
		int nFadeCnt;			// フェード加算
		float fGaugeDispPer;	// 表示割合 

	}BossGauge;	// ボスゲージパラメータ

public:
	// ===プロトタイプ宣言===
	CBossgauge(CTimer* pTimer);
	~CBossgauge();
	void Update();
	void Draw();

	void DrawFrame(std::vector<BossGauge>::iterator itr);	// ボスゲージ枠表示
	void DrawGauge(std::vector<BossGauge>::iterator itr);	// ボスゲージ増加量描画関数

	void SetSlimeManager(CSlimeManager* pSlimeMng);
	void SetShowWarning(CShowWarning* pShowWarn);

	void AddBossGauge(int BossNum, float fStartTime, float fMaxTime);
	void BossGaugeScaleMotion(float fSize, int nFlame);	//ボスゲージスケール関数

private:
	// ===メンバ変数宣言===
	Texture* m_pTexFrame;
	Texture* m_pTexGauge;
	CTimer* m_pTimer;						// 残り時間のポインタ
	CSlimeManager* m_pSlimeMng;				// スライム管理(ボス生成で使用する)
	std::vector<BossGauge> m_BossGauges;	// ボスゲージ管理配列(ステージ毎に生成する数配列に格納する)

	CShowWarning* m_pShowWarn;				// ボス警告

	float m_fBossgaugeScale;				// ボスゲージスケール倍率
	int m_nBossgaugeScaleCnt;				// ボスゲージスケールのフレームカウント
};


#endif // __BOSS_GAUGE_H__