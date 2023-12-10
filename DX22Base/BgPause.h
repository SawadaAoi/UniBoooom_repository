/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ポーズオブジェ定義
	---------------------------------------
	BgPause.h

	作成者	takagi

	変更履歴
	・2023/12/10 制作 takagi

========================================== */

#ifndef __BG_PAUSE_H__	//BgPause.hインクルードガード
#define __BG_PAUSE_H__

// =============== インクルード =====================
#include "PauseObj.h"	//親のヘッダ

// =============== クラス定義 =====================
class CBgPause :public CPauseObj	//平面オブジェ
{
public:
	// ===プロトタイプ宣言===
	CBgPause(const int& nWaitTime = 0);	//コンストラクタ
private:
	// ===変数宣言===
	float m_fMoveAngle;	//単振動における回転角[rad]
	// ===プロトタイプ宣言===
	void CulculatePos(TPos3d<float>& fPos) override;	//位置算出
};	//ポーズ用オブジェクト

#endif	//!__BG_PAUSE_H__