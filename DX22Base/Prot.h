/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	プロトタイプシーン定義
	---------------------------------------
	Prot.h

	作成者
			takagi
			nieda

	変更履歴
	・2023/11/05 制作 takagi
	・2023/11/07 コメント修正 takagi

========================================== */

#ifndef __PROT_H__
#define __PROT_H__

// =============== インクルード ===================
#include "Scene.h"	//親のヘッダ

// =============== クラス定義 =====================
class CProt :public CScene	//シーン
{
public:
	// =============== プロトタイプ宣言 ===============
	CProt();							//コンストラクタ
	~CProt();							//デストラクタ
	void Update();						//更新
	void Draw() const;					//描画	
	E_TYPE GetType() const override;	//自身の種類ゲッタ
};	//タイトル

#endif	//!__PROT_H__