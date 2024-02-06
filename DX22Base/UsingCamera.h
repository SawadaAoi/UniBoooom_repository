///* ========================================
//	HEW/UniBoooom!!
//	---------------------------------------
//	タイトル開始時ズームアウト用カウンタ定義
//	---------------------------------------
//	UsingCamera.h
//
//	作成者	takagi
//
//	変更履歴
//	・2024/02/02 制作 takagi
//	・2024/02/05 誤字修正・一部引数除去 takagi
//
//========================================== */
//
//#ifndef __TITLE_INIT_COUNTER_H__	//UsingCamera.hインクルードガード
//#define __TITLE_INIT_COUNTER_H__
//
//// =============== インクルード =====================
//#include "TitleObj.h"	//親のヘッダ
//#include <memory.h>		//ptr管理
//
//// =============== クラス定義 =====================
//class CUsingCamera
//{
//public:
//	// ===プロトタイプ宣言===
//	virtual void Update() final;											//更新
//	virtual void StartCount() final;										//カウンタ始動
//	static const std::weak_ptr<const CUsingCamera>& GetThis();			//自身のゲッタ
//	virtual const std::weak_ptr<const CFrameCnt>& GetCounter() const final;	//カウンタゲッタ
//private:
//	// ===変数宣言===========
//	static std::shared_ptr<CCamera> ms_pDefCamera;				//縮小カウンタ
//	static bool ms_bCountStarted;								//カウントを開始したことがあるか(true：ある)
//	// ===プロトタイプ宣言===
//	CUsingCamera();										//コンストラクタ
//	CUsingCamera(const CUsingCamera& Obj);			//コピーコンストラクタ
//	CUsingCamera& operator=(const CUsingCamera& Obj);	//代入演算子
//	~CUsingCamera();										//デストラクタ
//};	//タイトル開始時ズームアウトに使用するカウンタ
//
//#endif	//!__TITLE_INIT_COUNTER_H__