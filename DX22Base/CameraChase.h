/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	追跡カメラ定義
	------------------------------------
	CameraChase.h
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/11/04 制作 takagi
	・2023/11/06 コーディング規約適用・追跡対象登録機構作成 takagi
	・2023/11/07 GetViewMatrix()関数にconst修飾子付与・コメント修正 takagi
	・2023/11/08 TPos修正 takagi
	・2023/11/10 パラメタ修正 takagi
	・2023/12/03 位置ゲッタ用調整 takagi
	・2023/12/04 GetViewWithoutTransposeの戻り値を変更 yamashita
	・2024/01/16 統一のため、インクルードガードの___を__に変更	takagi
	・2024/01/20 コメント改修 takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __CAMERA_CHASE_H__	//CameraChase.hインクルードガード
#define __CAMERA_CHASE_H__

// =============== インクルード ===================
#include "Camera.h"	//親のヘッダ

// =============== クラス定義 =====================
class CCameraChase :public CCamera	//カメラ
{
public:
	// ===プロトタイプ宣言===
	CCameraChase(const TPos3d<float>* pPos);						//コンストラクタ
	~CCameraChase();												//デストラクタ
	void Update();													//更新
	DirectX::XMFLOAT4X4 GetViewWithoutTranspose() const override;	//転置無しビュー行列取得
private:
	// ===メンバ変数宣言===
	const TPos3d<float>* m_pTarget;	//追跡目標
	// ===プロトタイプ宣言===
	void UpdatePos();	//位置更新
};	//追跡カメラ

#endif	//!__CAMERA_CHASE_H__