/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ステージ1定義
	---------------------------------------
	Stage1.h

	作成者
			takagi
			nieda

	変更履歴
	・2023/11/05 制作 takagi
	・2023/11/07 コメント修正 takagi
	・2023/11/16 Prot.h→Stage1.h takagi

========================================== */

#ifndef __STAGE1_H__	//Stage1.hインクルードガード
#define __STAGE1_H__

// =============== インクルード ===================
#include "Stage.h"	//親のヘッダ

// =============== クラス定義 =====================
class CStage1 :public CStage	//ステージ
{
public:
	// ===プロトタイプ宣言===
	CStage1();		//コンストラクタ
	~CStage1();									//デストラクタ
	void Update();						//更新
	void Draw();						//描画	
	E_TYPE GetType() const override;	//自身の種類ゲッタ
	E_TYPE GetNext() const override;	//次のシーンゲッタ
private:
	
private:
	void LoadBGM() override final;
};	//ステージ1

#endif	//!__STAGE1_H__