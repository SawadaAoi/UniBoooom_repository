/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ロードインジケータ定義
	---------------------------------------
	LoadIndicator.h

	作成者	takagi

	変更履歴
	・2024/03/06 制作開始 takagi

========================================== */

#ifndef __LOAD_INDICATOR_H__	//LoadIndicator.hインクルードガード
#define __LOAD_INDICATOR_H__

// =============== インクルード =====================
#include <thread>			//スレッド
#include "DrawAnimation.h"	//2dアニメ
#include <memory>			//ptr管理

// =============== クラス定義 =====================
class CLoadIndicator
{
public:
	// ===プロトタイプ宣言===
	static CLoadIndicator& GetThis();	//自身のゲッタ
	virtual void BeginDraw() final;
	virtual void EndDraw() final;
private:
	// ===変数宣言===========
	std::jthread m_DrawThread;				//スレッド
	std::shared_ptr<CDrawAnim> m_p2d;		//アニメ画像
	// ===プロトタイプ宣言===
	CLoadIndicator();										//コンストラクタ
	CLoadIndicator(const CLoadIndicator& Obj);				//コピーコンストラクタ
	CLoadIndicator& operator=(const CLoadIndicator& Obj);	//代入演算子
	~CLoadIndicator();										//デストラクタ
};	//ロードインジケータ

#endif	//!__LOAD_INDICATOR_H__