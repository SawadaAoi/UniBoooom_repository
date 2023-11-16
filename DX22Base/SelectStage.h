/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ステージセレクト定義
	---------------------------------------
	SelectStage.h

	作成者
			takagi
			nieda

	変更履歴
	・2023/11/16 制作 takagi

========================================== */

#ifndef __SELECT_STAGE_H__	//SelectStage.hインクルードガード
#define __SELECT_STAGE_H__

// =============== インクルード ===================
#include "Scene.h"	//親のヘッダ

// =============== クラス定義 =====================
class CSelectStage :public CScene	//シーン
{
public:
	// =============== プロトタイプ宣言 ===============
	CSelectStage();						//コンストラクタ
	~CSelectStage();					//デストラクタ
	void Update();						//更新
	void Draw() const;					//描画	
	E_TYPE GetType() const override;	//自身の種類ゲッタ
	E_TYPE GetNext() const override;	//次のシーンゲッタ
};	//ステージセレクト

#endif	//!__SELECT_STAGE_H__