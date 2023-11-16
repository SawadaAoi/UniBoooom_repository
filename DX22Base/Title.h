/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	タイトルシーン定義
	---------------------------------------
	Title.h

	作成者
			takagi
			nieda

	変更履歴
	・2023/10/26 仮制作 takagi
	・2023/11/05 現段階のコーディング規約適用 takagi
	・2023/11/07 コメント修正 takagi
	・2023/11/16 オーバーライド関数追加 takagi

========================================== */

#ifndef __TITLE_H__	//Title.hインクルードガード
#define __TITLE_H__

// =============== インクルード ===================
#include "Scene.h"	//親のヘッダ

// =============== クラス定義 =====================
class CTitle :public CScene	//シーン
{
public:
	// =============== プロトタイプ宣言 ===============
	CTitle();							//コンストラクタ
	~CTitle();							//デストラクタ
	void Update();						//更新
	void Draw() const;					//描画	
	E_TYPE GetType() const override;	//自身の種類ゲッタ
	E_TYPE GetNext() const override;	//次のシーンゲッタ
};	//タイトル

#endif	//!__TITLE_H__