/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	シーン用抽象クラス定義
	---------------------------------------
	Scene.h

	作成者
			takagi
			nieda

	変更履歴
	・2023/10/24 仮制作 takagi
	・2023/10/26 GetType()関数の戻り値を修正 takagi
	・2023/11/04 列挙中身追加 takagi
	・2023/11/05 現段階のコーディング規約適用 takagi
	・2023/11/07 コメント修正 takagi
	・2023/11/16 列挙追加・GetNext()関数追加・終了フラグ周り実装・コメント修正 takagi

========================================== */

#ifndef __SCENE_H__	//Scene.hインクルードガード
#define __SCENE_H__

// =============== クラス定義 =====================
class CScene
{
public:
	// ===列挙定義===========
	enum E_TYPE
	{
		E_TYPE_TITLE,			//タイトルシーン
		//E_TYPE_PROT,			//プロトタイプ
		E_TYPE_SELECT_STAGE,	//ステージセレクト
		E_TYPE_STAGE1,			//ステージ1
		E_TYPE_STAGE2,			//ステージ2
		E_TYPE_STAGE3,			//ステージ3
		E_TYPE_RESULT,			//リザルトシーン
		E_TYPE_MAX,				//要素数
		E_TYPE_NONE = -1,		//該当なし
	};	//シーンの種類
public:
	// ===プロトタイプ宣言===
	CScene();							//コンストラクタ
	virtual ~CScene();					//デストラクタ
	virtual void Update();				//更新
	virtual void Draw() const;			//描画
	bool IsFin() const;					//終了確認
	virtual E_TYPE GetType() const = 0;	//自身の種類ゲッタ
	virtual E_TYPE GetNext() const = 0;	//次のシーンゲッタ
protected:
	// ===メンバ変数宣言=====
	bool m_bFinish;	//終了予約用(trueで終了)
};	//シーン

#endif	//!__SCENE_H__