/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ポーズ画面定義
	---------------------------------------
	Pose.h

	作成者	takagi

	変更履歴
	・2023/12/01 制作 takagi
	・2023/12/04 続き takagi

========================================== */

#ifndef __POSE_H__	//Pose.hインクルードガード
#define __POSE_H__

#include "Sound.h"		//音
#include "Camera.h"		//カメラ
#include "2dPolygon.h"	//平面ポリゴン
#include <vector>		//配列コンテナ

// =============== クラス定義 =====================
class CPose
{
private:
	enum E_FLAG
	{
		E_FLAG_POSEMODE = 0x00, //ポーズモード
	};	//フラグ
public:
	// ===プロトタイプ宣言===
	CPose(const CCamera* pCamera);						//コンストラクタ
	~CPose();											//デストラクタ
	void Update();										//更新
	void Draw();										//描画
	bool IsFin() const;									//終了確認
	void SetCamera(const CCamera* pCamera = nullptr);	//カメラセッタ
	bool IsPose() const;								//ポーズ中か
private:
	// ===メンバ変数宣言=====
	unsigned char m_ucFlag;							//フラグ
	bool m_bFinish;									//終了予約用(trueで終了)
	std::vector<C2dPolygon*> m_2dObj;				//平面ポリゴン
	PixelShader* m_pBgPs;							//背景用ピクセルシェーダ
	VertexShader* m_pBgVs;							//背景用頂点シェーダ
	//const CCamera* m_pCamera;						//カメラ
	const CCamera* m_pCameraDef;					//疑似カメラ
	XAUDIO2_BUFFER* m_pBGM;							//BGMの音声データ
	XAUDIO2_BUFFER* m_pSEHitHammer;					//SEの音声データ
	IXAudio2SourceVoice* m_pSpeaker;				//BGMを聞き取る側
	IXAudio2SourceVoice* m_pSEHitHammerSpeaker;		//SEを聞き取る側
};	//リザルト

#endif	//!__POSE_H__