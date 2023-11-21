/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	コンボUI用ヘッダ
	------------------------------------
	Combo.h
	------------------------------------
	作成者
		澤田蒼生
	変更履歴
	・2023/11/21 作成 Sawada

========================================== */
#ifndef __COMBO_H__
#define __COMBO_H__

// =============== インクルード ===================
#include "Sprite.h"
#include <Texture.h>
#include "Pos3d.h"

// =============== クラス定義 =====================
class CCombo
{
public:
	// ===プロトタイプ宣言===
	CCombo();
	~CCombo();
	void Update();
	void Draw();



private:
	// ===メンバ変数宣言===
	Texture* m_pTextureNum;



};


#endif // __COMBO_H__