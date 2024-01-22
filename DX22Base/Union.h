/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	UNION定義
	---------------------------------------
	Union.h
	---------------------------------------
	作成者	takagi

	変更履歴
	・2023/12/20 制作 takagi
	・2023/12/24 フレーム変更をマネージャへ takagi
	・2024/01/20 リファクタリング takagi
	・2024/01/21 コメント改修 takagi
	・2024/01/22 Draw()関数const化 takagi

========================================== */

#ifndef __UNION_H__	//Union.hインクルードガード
#define __UNION_H__

// =============== インクルード =====================
#include "TitleAnime.h"	//親のヘッダ
#include "FrameCnt.h"	//メンバのヘッダ

// =============== クラス定義 =====================
class CUnion :public C2dObject	//アニメーション
{
public:
	// ===プロトタイプ宣言===
	CUnion(const int& nFrame);	//コンストラクタ
	~CUnion();					//デストラクタ
	void Update() override;		//更新
	void Draw() const override;	//描画
	bool IsFin();				//終了ゲッタ
private:
	// ===変数宣言===========
	CFrameCnt* m_pCnt;	//カウンタ
	float Decrease;		//減算量
};	//タイトルロゴ

#endif	//!__UNION_H__