/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   立方体定義
   ---------------------------------------
   Box.h

   作成者	takagi

   変更履歴
   ・2023/11/05 制作 takagi


   ======================================== */

#ifndef __BOX_H__
#define __BOX_H__

// =============== インクルード ===================
#include "Geometry.h"	//親のヘッダ

// =============== クラス定義 =====================
class CBox	:public CGeometry	//形状
{
public:
	// =============== プロトタイプ宣言 ===============
	CBox();				//コンストラクタ
	CBox(CBox& Obj);	//コピーコンストラクタ
	~CBox();			//デストラクタ
	void Draw();		//描画
};	//立方体

#endif //!__BOX_H__