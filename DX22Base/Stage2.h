/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ステージ2定義
	---------------------------------------
	Stage2.h

	作成者
			takagi
			nieda

	変更履歴
	・2023/11/16 制作 takagi

========================================== */

#ifndef __STAGE2_H__	//Stage2.hインクルードガード
#define __STAGE2_H__

// =============== インクルード ===================
#include "Stage.h"	//親のヘッダ

// =============== クラス定義 =====================
class CStage2 :public CStage	//ステージ
{
public:
	// ===プロトタイプ宣言===
	CStage2();							//コンストラクタ
	~CStage2();							//デストラクタ
	void Update();						//更新
	void Draw() const;					//描画	
	E_TYPE GetType() const override;	//自身の種類ゲッタ
	E_TYPE GetNext() const override;	//次のシーンゲッタ
};	//ステージ2

#endif	//!__STAGE2_H__