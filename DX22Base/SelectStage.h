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
	・2023/12/12 ステージセレクト用の構造体、配列、関数追加 yamamoto
	・2024/01/26 拡縮実装 takagi

========================================== */

#ifndef __SELECT_STAGE_H__	//SelectStage.hインクルードガード
#define __SELECT_STAGE_H__

// =============== インクルード ===================
#include "Scene.h"	//親のヘッダ
#include "2dPolygon.h"
#include "FrameCnt.h"	//割合検出用
// =============== 定数定義 =======================
const int SUTAGE_NUM = 3;						// ステージの数

// =============== クラス定義 =====================
class CSelectStage :public CScene	//シーン
{
	// ===定数定義===========
	const float MIN_SIZE_ARR_LET = 450.0f;	//手配書最小サイズ
	const float MAX_SIZE_ARR_LET = 550.0f;	//手配書最大サイズ
	const int CHANGE_SCALE_HALF_TIME = 120;	//拡縮半周あたりにかかる時間
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
	void Update();						//更新
	void Draw();// const;					//描画	
	void Select();
	E_TYPE GetType() const override;	//自身の種類ゲッタ
	E_TYPE GetNext() const override;	//次のシーンゲッタ
protected:
	StageSelect mStageNum[SUTAGE_NUM];
private:
	int m_nSelectNum;			// 選択中のステージ番号
	C2dPolygon* m_2dObj[5];
	StageSelect EscapeStageNum;
	Texture* m_pStageSelectBG;
	Texture* m_pStageSelectUI;
	bool m_bStickFlg;			// コントローラーのスティックをたおしているか
	CFrameCnt* m_pFrameCnt;		//イージング用タイマー
	bool m_bCntUpDwn;			//カウントアップ・ダウン

};	//ステージセレクト

#endif	//!__SELECT_STAGE_H__