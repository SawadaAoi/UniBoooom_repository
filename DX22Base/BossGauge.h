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

========================================== */
#ifndef __BOSS_GAUGE_H__
#define __BOSS_GAUGE_H__

// =============== インクルード ===================
#include "Sprite.h"
#include <Texture.h>
#include "Pos3d.h"
#include "Timer.h"

// =============== クラス定義 =====================
class CBossgauge
{
public:
	// ===プロトタイプ宣言===
	CBossgauge();
	~CBossgauge();
	void Update();
	void Draw();

	void FillGaugeDraw(float textureRange);		//ボスゲージ増加量描画関数
	void GetBossPos();	//ボス現在の位置を取得(要る？) 画面外に行ったら矢印で表示する


private:
	// ===メンバ変数宣言===
	Texture* m_pBossGaugeEmpty;
	Texture* m_pBossGaugeFull;
	int m_nGaugeCnt;		//ボスゲージフレーム加算値
	bool m_bGaugeFull;		//ゲージ満タンフラグ(満タン = true)
	bool m_bShowBossGauge;	//ボスゲージ表示フラグ
	CTimer* m_pTimer;		//タイマーポインタ

};


#endif // __BOSS_GAUGE_H__