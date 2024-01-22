/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	UIアニメーション描画用ヘッダ
	---------------------------------------
	DrawAnimation.h
	---------------------------------------
	作成者	nieda

	変更履歴
	・2023/12/08 新規作成 nieda
	・2023/12/09 続き nieda
	・2023/12/11 続き nieda
	・2023/12/12 tkg先生の指導により2dpolygonに対応 nieda
	・2023/12/15 描画サイズ関連の変数追加、コンストラクタ修正 nieda
	・2023/12/16 描画位置追加 nieda
	・2023/12/16 コンストラクタの引数を最小化・不要なポインタ削除 takagi
	・2023/12/17 一部引数参照化 takagi
	・2024/01/20 リファクタリング takagi
	・2024/01/21 コメント改修 takagi
	・2024/01/22 Draw()関数const化 takagi

========================================== */

#ifndef __DRAW_ANIMATION_H__	//DrawAnimation.hインクルードガード
#define __DRAW_ANIMATION_H__

// =============== インクルード ===================
#include "Texture.h"
#include "CameraChase.h"
#include "Pos2d.h"
#include "2dObject.h"

// =============== クラス定義 =====================
class CDrawAnim :public C2dObject	//平面オブジェ
{
public:
	// ===プロトタイプ宣言===
	CDrawAnim(int, TDiType<int>, int = 1);	//コンストラクタ
	~CDrawAnim() {};						//デストラクタ
	void Update();							//更新関数
	void Draw() const override;				//描画関数
	void SetLoopFlg(bool);					//ループ再生フラグをセット
	bool GetAnimFlg();						//フラグ取得

protected:
	// ===メンバ変数宣言=====
	int m_nNumAnim;				//アニメーション番号
	int m_nNumAnimMax;			//アニメーションの最大数
	TDiType<int> m_nSplitNum;	//分割数
	TDiType<float> m_fUvPos;	//UV座標
	TDiType<float> m_fUvScale;	//UV分割サイズ格納用
	int m_nFrameCnt;			//アニメーションの切替間隔カウント用用
	int m_nSwitchCnt;			//アニメーションの切替間隔格納用
	bool m_bLoop;				//ループ判定フラグ
	bool m_bAnim;				//描画判定フラグ
};	//2Dアニメーション

#endif	//!__DRAW_ANIMATION_H__