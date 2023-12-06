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
	int m_nNum;			// ゲームスタート表示カウント用
	float m_fSize;		// ゲームスタート表示のサイズ
	float m_fResize;	// ゲームスタート表示のサイズ変更用
	bool m_bStart;		// ゲームを開始させるか判定
	const int* m_pPlayerHp;		// プレイヤーHP取得用
	const int* m_pTimeCnt;		// 制限時間取得用

	TPos2d<float> m_fUVPos;	// UV座標保存用
	int m_nCntSwitch;	// アニメーション切り替えカウント用
	int m_nCntW;		// 横カウント用
	int m_nCntH;		// 縦カウント用
	bool m_bStartSign;		// スタート合図開始フラ
};	//ステージ1

#endif	//!__STAGE1_H__