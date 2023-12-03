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

========================================== */

#ifndef ___CAMERA_CHASE_H___
#define ___CAMERA_CHASE_H___

// =============== インクルード ===================
#include "Camera.h"	//親のヘッダ

// =============== クラス定義 =====================
class CCameraChase :public CCamera	//カメラ
{
public:
	// ===プロトタイプ宣言===
	CCameraChase(const TPos3d<float>* pPos);			//コンストラクタ
	~CCameraChase();								//デストラクタ
	void Update();									//更新
	DirectX::XMFLOAT4X4 GetViewMatrix() const override;	//ビュー行列変換
	TPos3d<float> GetChasePos()const;
private:
	// ===メンバ変数宣言===
	const TPos3d<float>* m_pTarget;	//追跡目標
};	//追跡カメラ

#endif // !___CAMERA_CHASE_H___