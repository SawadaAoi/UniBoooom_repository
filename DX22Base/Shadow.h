/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	影表示用クラス定義
	---------------------------------------
	Shadow.h

	作成者 nieda

	変更履歴
	・2023/11/27 制作 nieda
	・2024/02/13 カメラ削除 takagi

========================================== */

#ifndef __SHADOW_H__	// Shadow.hインクルードガード
#define __SHADOW_H__

// =============== インクルード ===================
#include "Texture.h"	// テクスチャ用ヘッダ
#include "Object.h"		// オブジェクト用ヘッダ

// =============== クラス定義 =====================
class CShadow
	:public CObject
{
public:
	CShadow();		// コンストラクタ
	CShadow(float fScale);		// コンストラクタ
	~CShadow();		// デストラクタ
	void Update();	// 更新関数
	void Draw(tagTransform3d m_Pos, float fscale);	// 描画関数
	void Draw();	// 描画関数
private:
	bool m_bDisp;				// 表示するか判定
	Texture* m_pTextureShadow;	// テクスチャクラスのポインタ
};	// 影

#endif	//!__SHADOW_H__
