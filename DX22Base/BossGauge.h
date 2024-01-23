/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	boss出現用ヘッダ
	------------------------------------
	BossGauge.h
	------------------------------------
	作成者	tei

	変更履歴
	・2023/11/17 h,作成 tei
	・2023/11/19 ボスゲージ増加する変数、関数を作成 tei
	・2023/11/22 ボスゲージフェード用変数追加 tei
	・2023/11/26 スライム管理メンバ変数追加	sawada
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __BOSS_GAUGE_H__	//BossGauge.hインクルードガード
#define __BOSS_GAUGE_H__

// =============== インクルード ===================
#include "Sprite.h"
#include <Texture.h>
#include "Pos3d.h"
#include "Timer.h"
#include "SlimeManager.h"
#include "2dObject.h"	//平面ポリゴン
#include <vector>
#include "Camera.h"

// =============== クラス定義 =====================
class CBossGauge :public C2dObject	//2Dオブジェクト
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
	CBossGauge();
	~CBossGauge();
	void Update();
	void Draw();

	void DrawFrame(std::vector<BossGauge>::iterator itr);	// ボスゲージ枠表示
	void DrawGauge(std::vector<BossGauge>::iterator itr);	// ボスゲージ増加量描画関数

	void SetSlimeManager(CSlimeManager* pSlimeMng);
	void SetTimer(CTimer* pTimer);

	void AddBossGauge(int BossNum, float fStartTime, float fMaxTime);

private:
	// ===メンバ変数宣言===
	Texture* m_pTexFrame;
	Texture* m_pTexGauge;
	CTimer* m_pTimer;						// 残り時間のポインタ
	CSlimeManager* m_pSlimeMng;				// スライム管理(ボス生成で使用する)
	std::vector<BossGauge> m_BossGauges;	// ボスゲージ管理配列(ステージ毎に生成する数配列に格納する)
};	//ボスゲージ


#endif	//!__BOSS_GAUGE_H__