/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   球定義
   ---------------------------------------
   Sphere.h

   作成者	takagi

   変更履歴
   ・2023/11/05 制作 takagi
   ・2023/11/09 インクルードガード修正 takagi


   ======================================== */

#ifndef __SPHERE_H__
#define __SPHERE_H__

// =============== インクルード ===================
#include "Geometry.h"	//親のヘッダ

// =============== クラス定義 =====================
class CSphere :public CGeometry	//形状
{
	//static const int CIRCLE_DETAIL = 16;
public:
	// =============== プロトタイプ宣言 ===============
	CSphere();				//コンストラクタ
	CSphere(CSphere& Obj);	//コピーコンストラクタ
	~CSphere();				//デストラクタ
	void Draw();			//描画
};	//球

#endif //!__SPHERE_H__