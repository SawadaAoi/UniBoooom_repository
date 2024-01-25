/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ステージセレクト定義
	---------------------------------------
	SelectStage.h
	---------------------------------------
	作成者
			takagi
			nieda

	変更履歴
	・2023/11/16 制作 takagi
	・2023/12/12 ステージセレクト用の構造体、配列、関数追加 yamamoto
	・2024/01/20 リファクタリング takagi

========================================== */

#ifndef __SELECT_STAGE_H__	//SelectStage.hインクルードガード
#define __SELECT_STAGE_H__

// =============== インクルード ===================
#include "Scene.h"	//親のヘッダ
#include "2dObject.h"
// =============== 定数定義 =======================
const int SUTAGE_NUM = 3;						// ステージの数

// =============== クラス定義 =====================
class CSelectStage :public CScene	//シーン
{
public:
	// ===構造体定義=========
	typedef struct
	{
		E_TYPE Type;
		Texture* m_pTexture;
	}StageSelect;

public:
	// =============== プロトタイプ宣言 ===============
	CSelectStage();						//コンストラクタ
	~CSelectStage();					//デストラクタ
	void Update() override;				//更新	
	void Select();
	E_TYPE GetNext() const override;	//次のシーンゲッタ
protected:
	StageSelect mStageNum[SUTAGE_NUM];
private:
	int Num;
	C2dObject* m_2dObj[5];
	StageSelect EscapeStageNum;
	Texture* m_pStageSelectBG;
	Texture* m_pStageSelectUI;

};	//ステージセレクト

#endif	//!__SELECT_STAGE_H__