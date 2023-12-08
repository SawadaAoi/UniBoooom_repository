/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	リザルトシーン定義
	---------------------------------------
	Result.h

	作成者
			takagi
			nieda

	変更履歴
	・2023/11/16 制作 takagi
	・2023/12/08 シーン遷移用に変数追加 takagi

========================================== */

#ifndef __RESULT_H__	//Result.hインクルードガード
#define __RESULT_H__

// =============== インクルード ===================
#include "Scene.h"		//親のヘッダ
#include "Texture.h"
#include "BattleData.h"	//メンバのヘッダ

// =============== クラス定義 =====================
class CResult :public CScene	//シーン
{
public:
	// ===列挙定義===========
	enum E_RESULT
	{
		E_RESULT_RESULT,		//リザルト画像
		E_RESULT_BUTTON,		//ボタン押下指示
		E_RESULT_MAX,			//要素数
	};	//タイトルシーンのテクスチャの種類
public:
	// =============== プロトタイプ宣言 ===============
	CResult();							//コンストラクタ
	~CResult();							//デストラクタ
	void Update();						//更新
	void Draw();					//描画	
	E_TYPE GetType() const override;	//自身の種類ゲッタ
	E_TYPE GetNext() const override;	//次のシーンゲッタ
private:
	// =============== メンバ変数定義 ===============
	Texture* m_pTexture[E_RESULT_MAX];
	BattleData m_Data;					//戦闘結果
};	//リザルト

#endif	//!__RESULT_H__