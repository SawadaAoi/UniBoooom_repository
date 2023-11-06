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
	・2023/11/06 コーディング規約適用・追跡対象登録機構作成

========================================== */

#ifndef ___CAMERA_CHASE_H___
#define ___CAMERA_CHASE_H___

// =============== インクルード ===================
#include "Camera.h"	//親のヘッダ

// =============== クラス定義 =====================
class CCameraChase :public CCamera	//カメラ
{
public:
	// ===メンバ関数宣言===
	CCameraChase(const TPos<float>* pPos);			//コンストラクタ
	~CCameraChase();								//デストラクタ
	void Update();									//更新
	//void Draw();									//描画		//UIをカメラの方に実装するなら実装
	DirectX::XMFLOAT4X4 GetViewMatrix() override;	//ビュー行列変換
private:
	// ===メンバ変数宣言===
	const TPos<float>* m_pTarget;	//追跡目標
};	//追跡カメラ

#endif // !___CAMERA_CHASE_H___