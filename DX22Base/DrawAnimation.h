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

========================================== */

#ifndef __DRAW_ANIMATION_H__	//DrawAnimation.hインクルードガード
#define __DRAW_ANIMATION_H__

// =============== インクルード ===================
#include "Pos2d.h"
#include "Texture.h"
#include "CameraChase.h"
#include "2dPolygon.h"
#include "GameParameter.h"
#include "Transform3d.h"

// =============== クラス定義 =====================
class CDrawAnim :public C2dPolygon	//平面オブジェ
{
public:
	// ===プロトタイプ宣言===
	CDrawAnim(const char*, CCamera*, int, TDiType<int>, int);	// コンストラクタ
	~CDrawAnim() {};		// デストラクタ
	void Update();		// 更新関数
	void Draw();		// 更新関数

protected:
	// ===メンバ変数宣言=====
	Texture* m_pTexture;
	int m_nNumAnim;				// アニメーション番号
	int m_nNumAnimMax;			// アニメーションの最大数
	TDiType<int> m_NumCut;		// 分割数
	TDiType<float> m_fUvpos;	// UV座標
	TDiType<float> m_fUvscale;	// UV分割サイズ格納用
	int m_nCntSwitch;			// アニメーションの切替間隔
	bool bRoop;					// ループ判定フラグ
};	//UIアニメーション

#endif	//!__DRAW_ANIMATION_H__

