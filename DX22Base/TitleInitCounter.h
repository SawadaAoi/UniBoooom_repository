/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	タイトル開始時ズームアウト用カウンタ定義
	---------------------------------------
	TitleInitCounter.h

	作成者	takagi

	変更履歴
	・2024/02/02 制作 takagi
	・2024/02/05 誤字修正・一部引数除去 takagi
	・2024/02/08 ヘッダ名修正 takagi

========================================== */

#ifndef __TITLE_INIT_COUNTER_H__	//TitleInitCounter.hインクルードガード
#define __TITLE_INIT_COUNTER_H__

// =============== インクルード =====================
#include "TitleObj.h"	//親のヘッダ
#include <memory>		//ptr管理
#include "FrameCnt.h"	//カウンタ

// =============== クラス定義 =====================
class CTitleInitCounter
{
public:
	// ===プロトタイプ宣言===
	virtual void Update() final;											//更新
	virtual void StartCount() final;										//カウンタ始動
	static CTitleInitCounter& GetThis();									//自身のゲッタ
	virtual const std::weak_ptr<const CFrameCnt> GetCounter() const final;	//カウンタゲッタ	※わざと戻り値は参照でない
private:
	// ===変数宣言===========
	static std::shared_ptr<CFrameCnt> ms_pCounter;	//縮小カウンタ
	static bool ms_bCountStarted;					//カウントを開始したことがあるか(true：ある)
	// ===プロトタイプ宣言===
	CTitleInitCounter();										//コンストラクタ
	CTitleInitCounter(const CTitleInitCounter& Obj);			//コピーコンストラクタ
	CTitleInitCounter& operator=(const CTitleInitCounter& Obj);	//代入演算子
	~CTitleInitCounter();										//デストラクタ	※shared_ptrがアクセスする用
};	//タイトル開始時ズームアウトに使用するカウンタ

#endif	//!__TITLE_INIT_COUNTER_H__