/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ポーズオブジェ定義
	---------------------------------------
	PauseObj.h
	---------------------------------------
	作成者	takagi

	変更履歴
	・2023/12/09 制作 takagi
	・2023/12/10 制作進行 takagi
	・2023/12/17 引数参照化 takagi
	・2024/01/20 リファクタリング takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __PAUSE_OBJ_H__	//PauseObj.hインクルードガード
#define __PAUSE_OBJ_H__

// =============== インクルード =====================
#include "2dObject.h"	//親のヘッダ

// =============== クラス定義 =====================
class CPauseObj	:public C2dObject	//平面オブジェ
{
public:
	// ===プロトタイプ宣言===
	CPauseObj(const int& nWaitTime = 0);		//コンストラクタ
	virtual ~CPauseObj() ;						//デストラクタ
	virtual void Update();						//更新
	virtual void Draw() override;				//描画
	void SetReach(const TPos3d<float>& fReach);	//到達地点セッタ
	void Destroy(const int& nWaitTime = 0);		//破棄
	bool IsDestroyed();							//破棄準備フラグゲッタ
protected:
	// ===メンバ変数宣言=====
	TPos3d<float> m_fReach;	//到達地点
	// ===プロトタイプ宣言===
	virtual void CulculatePos(TPos3d<float>& fPos);	//位置算出
private:
	// ===メンバ変数宣言=====
	float m_fOffset;		//最終位置とのxズレ
	int* m_pnWaitTime;		//初動待機時間計測
	int* m_pnRewaitTime;	//終了待機時間計測
	int* m_pnMoveTime;		//ずれた位置から戻るのにかける時間
	int* m_pnRemoveTime;	//ずれた位置から戻るのにかける時間
	bool m_bDestroyed;		//破棄準備が完了したか
};	//ポーズ用オブジェクト

#endif	//!__PAUSE_OBJ_H__