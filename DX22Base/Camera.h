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

========================================== */

#ifndef ___CAMERA_H___
#define ___CAMERA_H___

// =============== インクルード ===================
//#include "System.h"		//親のヘッダ
#include "Pos3d.h"			//メンバのヘッダ
#include "TriType.h"		//メンバのヘッダ
//#include "main.h"	//画面の情報
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
		E_BIT_FLAG_AS_2D = 0x01,		//2Dのように描画する(フラグが立っていないときは3Dとして描画)
		E_BIT_FLAG_VIBRATION = 0x02,	//画面振動
		E_BIT_FLAG_3 = 0x04,			//
		E_BIT_FLAG_4 = 0x08,			//
		E_BIT_FLAG_5 = 0x10,			//
		E_BIT_FLAG_6 = 0x20,			//
		E_BIT_FLAG_7 = 0x40,			//
		E_BIT_FLAG_8 = 0x80,			//
	};	//フラグ
protected:
	// ===メンバ変数宣言=====
	unsigned char m_ucFlag;	//フラグ	char:1バイト(8ビット)
	TPos3d<float> m_fPos;	//ワールド座標における自身の位置
	TPos3d<float> m_fLook;	//注視点の位置
	TTriType<float> m_fUp;	//上方ベクトル
	float m_fAngle;			//角度
	float m_fNear;			//画面手前
	float m_fFar;			//画面奥
	float m_fRadius;		//距離
public:
	// ===プロトタイプ宣言===
	CCamera(const E_DRAW_TYPE& eDraw = E_DRAW_TYPE_3D);	//コンストラクタ
	virtual~CCamera();									//デストラクタ
	virtual void Update() = 0;							//更新
	void UpFlag(const unsigned char& ucBitFlag);		//OR	 00:0,01:1,10:1,11:1
	void DownFlag(const unsigned char& ucBitFlag);		//A AND !B	00:0,01:0,10:1,11:0
	void SetFlag(const unsigned char& ucBitFlag);		//XOR：上げ下げどっちもできる	00:0,01:1,10:1,11:0
	virtual DirectX::XMFLOAT4X4 GetViewMatrix() const;	//ビュー行列変換
	DirectX::XMFLOAT4X4 GetProjectionMatrix() const;	//プロジェクション行列変換
protected:
	void HandleFlag();	//フラグ別処理
private:
	void Vibration();	//振動
	//void Zoom();	//ズームイン(アウト)
};	//カメラ

#endif // !___CAMERA_H___