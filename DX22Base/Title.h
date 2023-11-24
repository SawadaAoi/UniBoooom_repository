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
#include "Texture.h"

// =============== クラス定義 =====================
class CTitle :public CScene	//シーン
{
public:
	// ===列挙定義===========
	enum E_TITLE
	{
		E_TITLE_TITLE,			//タイトル画像
		E_TITLE_BUTTON,			//ボタン押下指示
		E_TITLE_MAX,			//要素数
	};	//タイトルシーンのテクスチャの種類
public:
	// =============== プロトタイプ宣言 ===============
	CTitle();							//コンストラクタ
	~CTitle();							//デストラクタ
	void Update();						//更新
	void Draw();					//描画	
	E_TYPE GetType() const override;	//自身の種類ゲッタ
	E_TYPE GetNext() const override;	//次のシーンゲッタ
private:
	Texture* m_pTexture[E_TITLE_MAX];
};	//タイトル

#endif	//!__TITLE_H__