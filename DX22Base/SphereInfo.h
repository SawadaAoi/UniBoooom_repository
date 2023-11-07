/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	スフィア用ヘッダ
	---------------------------------------
	SphereInfo.h
	
	作成者	山下凌佑
	
	変更履歴
	・2023/11/04 変更内容：CSphereInfoクラス作成 変更者名：山下凌佑
	・2023/11/04 変更内容：Sphere構造体を作成 変更者名：山下凌佑
	・2023/11/04 変更内容：距離を返す関数を作成 変更者名：山下凌佑
	・2023/11/04 変更内容：角度を返す関数を作成を作成 変更者名：山下凌佑
	・2023/11/07 変更内容：コンストラクタとデストラクタの説明を追加

=========================================== */
#ifndef __SPHEREINFO_H__
#define __SPHEREINFO_H__

#include "TriType.h"

// =============== クラス定義 =====================
class CSphereInfo
{
public:
	/* ========================================
		コンストラクタ
		----------------------------------------
		内容：生成時に処理
		----------------------------------------
		引数1：なし
		----------------------------------------
		戻値：なし
	======================================== */
	CSphereInfo() {}	//コンストラクタ

	/* ========================================
		デストラクタ
		----------------------------------------
		内容：消滅時に処理
		----------------------------------------
		引数1：なし
		----------------------------------------
		戻値：なし
	======================================== */
	~CSphereInfo() {}	//デストラクタ

	// =============== 構造体定義 =====================
	typedef struct Sphere {
		TTriType<float> pos;
		float radius;

		float Distance(CSphereInfo::Sphere Obj);	//引数のオブジェクトとの距離を測る関数
		float Angle(CSphereInfo::Sphere Obj);		//引数のオブジェクトとの角度を測る関数
	};
private:
	
};

#endif // !__SPHEREINFO_H__
