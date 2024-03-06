/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	デバッグ用カメラ定義
	------------------------------------
	CameraDebug.h
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/11/04 制作 takagi
	・2023/11/06 コーディング規約適用・追跡対象登録機構作成 takagi
	・2023/11/07 コメント修正 takagi
	・2023/11/10 変数追加 takagi
	・2024/01/16 統一のため、インクルードガードの___を__に変更	takagi
	・2024/01/20 コメント改修 takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __CAMERA_DEBUG_H__	//CameraDebug.hインクルードガード
#define __CAMERA_DEBUG_H__

// =============== インクルード ===================
#include "Camera.h"	//親のヘッダ

// =============== クラス定義 =====================
class CCameraDebug :public CCamera	//カメラ
{
public:
	// ===プロトタイプ宣言===
	CCameraDebug();		//コンストラクタ
	~CCameraDebug();	//デストラクタ
	void Update();		//更新
private:
	// ===メンバ変数宣言=====
	float m_fRadXZ;			//X-Z座標の回転角(rad)
	float m_fRadY;			//Y-XZ座標の回転角(rad)
};	//デバッグ用カメラ

#endif	//!__CAMERA_DEBUG_H__