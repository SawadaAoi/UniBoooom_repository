/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   円柱定義
   ---------------------------------------
   Cylinder.h

   作成者	takagi

   変更履歴
   ・2023/11/05 制作 takagi


   ======================================== */

#ifndef __CYLINDER_H__
#define __CYLINDER_H__

   // =============== インクルード ===================
#include "Geometry.h"	//親のヘッダ

// =============== クラス定義 =====================
class CCylinder :public CGeometry	//形状
{
public:
	// ===プロトタイプ宣言===
	CCylinder();				//コンストラクタ
	CCylinder(CCylinder& Obj);	//コピーコンストラクタ
	~CCylinder();			//デストラクタ
	void Draw();		//描画
};	//立方体

#endif //!__CYLINDER_H__