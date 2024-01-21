/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ポーズ背景定義
	---------------------------------------
	BgPause.h
	---------------------------------------
	作成者	takagi

	変更履歴
	・2023/12/10 制作 takagi
	・2023/12/16 コメント修正 takagi
	・2024/01/21 コメント改修 takagi

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
	~CBgPause();						//デストラクタ
private:
	// ===プロトタイプ宣言===
	void CulculatePos(TPos3d<float>& fPos) override;	//位置算出
	PixelShader* m_pBgPs;								//背景用ピクセルシェーダ
	VertexShader* m_pBgVs;								//背景用頂点シェーダ
};	//ポーズ用背景

#endif	//!__BG_PAUSE_H__