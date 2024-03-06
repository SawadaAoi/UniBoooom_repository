/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	使用中カメラ定義
	---------------------------------------
	UsingCamera.h

	作成者	takagi

	変更履歴
	・2024/02/06 ファイル作成 takagi
	・2024/02/08 制作開始 takagi

========================================== */

#ifndef __USING_CAMERA_H__	//UsingCamera.hインクルードガード
#define __USING_CAMERA_H__

// =============== インクルード =====================
#include "Camera.h"		//カメラ
#include "CameraDef.h"	//デフォルトのカメラ
#include <memory>		//ptr管理

// =============== クラス定義 =====================
class CUsingCamera
{
public:
	// ===プロトタイプ宣言===
	static CUsingCamera& GetThis();									//自身のゲッタ
	virtual const std::shared_ptr<CCamera> GetCamera() const final;	//カメラゲッタ	※わざと戻り値は参照でない
	virtual void SetCamera(std::shared_ptr<CCamera> pCamera) final;	//カメラセッタ
private:
	// ===変数宣言===========
	static const std::shared_ptr<CCameraDef> ms_pDefCamera;	//デフォルトのカメラ
	static std::weak_ptr<CCamera> ms_pUsingCamera;			//使用中のカメラ
	// ===プロトタイプ宣言===
	CUsingCamera();										//コンストラクタ
	CUsingCamera(const CUsingCamera& Obj);				//コピーコンストラクタ
	CUsingCamera& operator=(const CUsingCamera& Obj);	//代入演算子
	~CUsingCamera();									//デストラクタ
};	//使用中のカメラ管理

#endif	//!__USING_CAMERA_H__