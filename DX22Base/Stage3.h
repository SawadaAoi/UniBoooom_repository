/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ステージ3定義
	---------------------------------------
	Stage3.h

	作成者
			takagi
			nieda

	変更履歴
	・2023/11/16 制作 takagi
	・2023/12/12 LoadSEをオーバーライド yamashita

========================================== */

#ifndef __STAGE3_H__	//Stage3.hインクルードガード
#define __STAGE3_H__

// =============== インクルード ===================
#include "Stage.h"	//親のヘッダ

// =============== クラス定義 =====================
class CStage3 :public CStage	//ステージ
{
public:
	// ===プロトタイプ宣言===
	CStage3();							//コンストラクタ
	~CStage3();							//デストラクタ
	void Update();						//更新
	void Draw();					//描画	
	E_TYPE GetType() const override;	//自身の種類ゲッタ
	E_TYPE GetNext() const override;	//次のシーンゲッタ
};	//ステージ3

#endif	//!__STAGE3_H__