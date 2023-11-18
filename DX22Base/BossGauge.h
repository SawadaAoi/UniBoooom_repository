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
	
========================================== */
#ifndef __BOSS_GAUGE_H__
#define __BOSS_GAUGE_H__

// =============== インクルード ===================
#include "Sprite.h"
#include <Texture.h>
#include "Pos3d.h"

// =============== クラス定義 =====================
class CBossgauge
{
public:
	// ===プロトタイプ宣言===
	CBossgauge();
	~CBossgauge();
	void Update();
	void Draw();

	void GetBossPos();	//ボス現在の位置を取得(要る？) 画面外に行ったらアイコンで表示する


private:
	// ===メンバ変数宣言===
	Texture* m_pBossGauge;	
	int m_nGaugeCnt;		//ボスゲージフレーム加算値
	bool m_bGaugeFull;		//ゲージ満タンフラグ(満タン = true)
	TPos3d<float> pos;

};


#endif // __BOSS_GAUGE_H__