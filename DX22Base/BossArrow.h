/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ボス方向表示矢印用ヘッダ
	------------------------------------
	BossArrow.h
	------------------------------------
	作成者	tei

	変更履歴
	・2023/12/08 h,作成 tei
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __BOSS_ARROW_H__	//BossArrow.hインクルードガード
#define __BOSS_ARROW_H__

// =============== インクルード ===================
#include "2dObject.h"
#include "Sprite.h"
#include <Texture.h>
#include "Pos2d.h"
#include "Camera.h"
#include "SlimeManager.h"
#include "Player.h"
#include "Defines.h"

// =============== クラス定義 =====================
class CBossArrow :public C2dObject	//2Dオブジェクト
{
public:
	// ===プロトタイプ宣言===
	CBossArrow();
	~CBossArrow();
	void Update();
	void Draw();
	void SetSlimeMng(CSlimeManager* mSlimeMng);
	void SetPlayer(CPlayer* mPlayer);
	void ArrowMove();
protected:

private:
	// ===メンバ変数宣言===
	Texture* m_pArrowTex;
	TPos2d<float> m_pos;			// 描画の位置
	float m_radian;					// 描画の角度
	CSlimeManager* m_pBoss;			// スライムマネージャーポインタ取得
	CPlayer* m_pPlayer;				// プレイヤーポインタ取得
	bool m_bBossInsideScreen;		// ボスが画面内判定用フラグ
	float m_fDistanceX;		// ポスとプレイヤーのX座標の差
	float m_fDistanceZ;		// ポスとプレイヤーのZ座標の差
};	//ボス方向表示矢印


#endif	//!__BOSS_ARROW_H__