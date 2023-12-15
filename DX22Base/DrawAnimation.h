/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	UIアニメーション描画用ヘッダ
	---------------------------------------
	DrawAnimation.h

	作成者
			nieda

	変更履歴
	・2023/12/08 新規作成 nieda
	・2023/12/09 続き nieda
	・2023/12/11 続き nieda
	・2023/12/12 tkg先生の指導により2dpolygonに対応 nieda
	・2023/12/15 描画サイズ関連の変数追加、コンストラクタ修正 nieda

========================================== */

#ifndef __DRAW_ANIMATION_H__	//DrawAnimation.hインクルードガード
#define __DRAW_ANIMATION_H__

// =============== インクルード ===================
#include "Texture.h"
#include "CameraChase.h"
#include "2dPolygon.h"

// =============== クラス定義 =====================
class CDrawAnim :public C2dPolygon	//平面オブジェ
{
public:
	// ===プロトタイプ宣言===
	CDrawAnim(const char*, CCamera*, int, TDiType<float>, TDiType<int>, int);	// コンストラクタ
	~CDrawAnim() {};	// デストラクタ
	void Update();		// 更新関数
	void Draw();		// 描画関数
	void SetLoopFlg(bool);	// ループ再生フラグをセット
	bool GetAnimFlg();	// フラグ取得

protected:
	// ===メンバ変数宣言=====
	Texture* m_pTexture;		// テクスチャクラスのポインタ
	int m_nNumAnim;				// アニメーション番号
	int m_nNumAnimMax;			// アニメーションの最大数
	TDiType<int> m_nSplitNum;	// 分割数
	TTriType<float> m_fSize;	// 描画サイズ
	TDiType<float> m_fUvPos;	// UV座標
	TDiType<float> m_fUvScale;	// UV分割サイズ格納用
	int m_nFrameCnt;			// アニメーションの切替間隔カウント用用
	int m_nSwitchCnt;			// アニメーションの切替間隔格納用
	bool m_bLoop;				// ループ判定フラグ
	bool m_bAnim;				// 描画判定フラグ
};	//2Dアニメーション

#endif	//!__DRAW_ANIMATION_H__

