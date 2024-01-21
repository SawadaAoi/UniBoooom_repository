/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	カメラ用抽象クラス定義
	------------------------------------
	CameraChase.h
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/10/24 仮制作 takagi
	・2023/11/02 メンバー変数追加 takagi
	・2023/11/04 フラグ追加？・private→protected・その他諸々修正 takagi
	・2023/11/06 フラグ整理・コメント修正 takagi
	・2023/11/07 GetViewMatrix()関数にconst修飾子付与・コメント修正 takagi
	・2023/11/08 TPos修正 takagi
	・2023/11/10 パラメタ修正 takagi
	・2023/11/17 2D表示/3D表示の切換をコンストラクタでなくGetProjectionMatrix()関数で行うように変更
					・フラグから2D/3Dの概念を削除・振動機能追加 takagi
	・2023/11/28 振動の仕様変更 takagi
	・2023/11/29 振動の新仕様を全振動に反映しリファクタリング takagi
	・2023/11/30 Effekseer用に関数追加 takagi
	・2023/12/03 位置ゲッタ作成 takagi
	・2023/12/04 GetViewWithoutTranspose,GetProjectionWithoutTransposeの戻り値を変更 yamashita
	・2023/12/05 揺れのカウンタ追加 takagi
	・2023/12/16 ズーム機能追加 takagi
	・2024/01/16 統一のため、インクルードガードの___を__に変更	takagi
	・2024/01/20 コメント改修 takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __CAMERA_H__	//Camera.hインクルードガード
#define __CAMERA_H__

// =============== インクルード ===================
//#include "System.h"		//親のヘッダ
#include "Pos3d.h"			//メンバのヘッダ
#include "TriType.h"		//メンバのヘッダ
#include "DiType.h"			//メンバのヘッダ
#include "FrameCnt.h"		//メンバのヘッダ
#include <DirectXMath.h>	//マトリックス型使用
#include "Defines.h"		//画面情報

// =============== クラス定義 =====================
class CCamera	//システム
{
public:
	// ===列挙定義===========
	enum E_DRAW_TYPE
	{
		E_DRAW_TYPE_2D,	//2D表示
		E_DRAW_TYPE_3D	//3D表示
	};	//表示形式
	enum E_BIT_FLAG
	{
		E_BIT_FLAG_VIBRATION_UP_DOWN_WEAK = 0x01,	//縦揺れ・弱
		E_BIT_FLAG_VIBRATION_UP_DOWN_STRONG = 0x02,	//縦揺れ・強
		E_BIT_FLAG_VIBRATION_SIDE_WEAK = 0x04,		//横揺れ・弱
		E_BIT_FLAG_VIBRATION_SIDE_STRONG = 0x08,	//横揺れ・強
		E_BIT_FLAG_5 = 0x10,						//
		E_BIT_FLAG_6 = 0x20,						//
		E_BIT_FLAG_7 = 0x40,						//
		E_BIT_FLAG_8 = 0x80,						//
	};	//フラグ
public:
	// ===プロトタイプ宣言===
	CCamera();																		//コンストラクタ
	virtual~CCamera();																//デストラクタ
	virtual void Update() = 0;														//更新
	void UpFlag(const unsigned char& ucBitFlag);									//OR							00:0,01:1,10:1,11:1
	void DownFlag(const unsigned char& ucBitFlag);									//A AND !B						00:0,01:0,10:1,11:0
	void SetFlag(const unsigned char& ucBitFlag);									//XOR：上げ下げどっちもできる	00:0,01:1,10:1,11:0
	DirectX::XMFLOAT4X4 GetViewMatrix() const;										//ビュー行列変換
	DirectX::XMMATRIX GetInverseViewMatrix() const;									//ビュー行列の逆行列取得
	DirectX::XMFLOAT4X4 GetProjectionMatrix(
		const E_DRAW_TYPE& eDraw = E_DRAW_TYPE_3D) const;							//プロジェクション行列変換
	virtual DirectX::XMFLOAT4X4 GetViewWithoutTranspose() const;					//転置無しビュー行列取得
	DirectX::XMFLOAT4X4 GetProjectionWithoutTranspose() const;						//転置無しプロジェクション行列取得
	virtual TPos3d<float> GetPos() const;											//カメラ位置提供
	void ChangeScaleVibrate(const int& nChangeFrame, const float& fChangegRateAmp);	//振動の規模を変更する
	void BootZoom(const float& fFinRadius, const int& nFrame = 0,
		const bool& bDefMode = true, const float& fStartRadius = 1.0f);				//ズーム/インアウト起動
	void SetRadius(const float& fRadius);											//距離セッタ
protected:
	// ===メンバ変数宣言=====
	TPos3d<float> m_fPos;					//ワールド座標における自身の位置
	TPos3d<float> m_fLook;					//注視点の位置
	TTriType<float> m_fUp;					//上方ベクトル
	float m_fAngle;							//角度
	float m_fNear;							//画面手前
	float m_fFar;							//画面奥
	float m_fRadius;						//距離
	TDiType<float> m_fOffsetVibrateEye;		//カメラ位置振動(x,z)
	TDiType<float> m_fOffsetVibrateLook;	//注視点振動(x,z)
	// ===プロトタイプ宣言===
	void HandleFlag();	//フラグ別処理
	void Zoom();		//ズーム/インアウト機能
private:
	// ===メンバ変数宣言=====
	unsigned char m_ucFlag;							//フラグ	char:1バイト(8ビット)
	TDiType<int> m_nFrameWeak;						//フレームカウンタ：弱振動	x:横, y:縦
	TDiType<int> m_nFrameStrong;					//フレームカウンタ：強振動	x:横, y:縦
	TDiType<float> m_fChangeRateAmplitudeWeak;		//振幅補正率：弱			x:横, y:縦
	TDiType<float> m_fChangeRateAmplitudeStrong;	//振幅補正率：強			x:横, y:縦
	int m_nCntChangeVibrate;						//カメラ揺れ変更回数
	CFrameCnt* m_pZoomCnt;							//ズーム機能用カウンター
	float* m_pfGoalRadius;							//ズーム目標距離
	float* m_pfStartRadius;							//ズーム開始距離
};	//カメラ

#endif	//!__CAMERA_H__