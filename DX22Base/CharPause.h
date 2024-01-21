/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ポーズ文字定義
	---------------------------------------
	CharPause.h
	---------------------------------------
	作成者	takagi

	変更履歴
	・2023/12/09 制作 takagi
	・2023/12/10 制作進行 takagi
	・2023/12/16 コメント修正 takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __CHAR_PAUSE_H__	//CharPause.hインクルードガード
#define __CHAR_PAUSE_H__

// =============== インクルード =====================
#include "PauseObj.h"	//親のヘッダ

// =============== クラス定義 =====================
class CCharPause :public CPauseObj	//平面オブジェ
{
public:
	// ===プロトタイプ宣言===
	CCharPause(const int& nWaitTime = 0);	//コンストラクタ
private:
	// ===変数宣言===
	float m_fMoveAngle;	//単振動における回転角[rad]
	// ===プロトタイプ宣言===
	void CulculatePos(TPos3d<float>& fPos) override;	//位置算出
};	//ポーズ用の文字

#endif	//!__CHAR_PAUSE_H__