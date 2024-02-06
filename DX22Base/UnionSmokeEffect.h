/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	結合エフェクト描画用ヘッダ
	---------------------------------------
	UnionEffectText.h

	作成者
			Tei

	変更履歴
	・2024/02/06 クラス定義作成 Tei

========================================== */

#ifndef __UNION_EFFECT_TEXT_H__	
#define __UNION_EFFECT_TEXT_H__

// =============== インクルード ===================
#include "DrawAnimation.h"
#include "Pos3d.h"
#include "Texture.h"

// =============== クラス定義 =====================
class CUnionSmokeEffect :public CDrawAnim	//UIアニメーション
{
public:
	// ===プロトタイプ宣言===
	CUnionSmokeEffect(TPos3d<float> pos, TPos3d<float> size, Texture* pTex, const CCamera* pCamera);	// コンストラクタ
	~CUnionSmokeEffect();
	void Update();
	void Draw();
	void DisplayTimeAdd();					// 結合エフェクト表示カウント加算処理関数

	// ゲット関数
	bool GetDelFlg();						// 削除フラグ取得処理関数


protected:
	// ===メンバ変数宣言=====
	CDrawAnim* m_pTexUnionSmoke;		// 結合の煙
	bool			m_bDelFlg;			// 結合エフェクト終了フラグ
	int				m_nDelFrame;		// 結合エフェクト表示カウント
	float			m_fEffectTime;		// ヒットエフェクト総時間
};	

#endif	//!__UNION_EFFECT_TEXT_H__