/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ハンマー用ヘッダ
	------------------------------------
	Hammer.h
	------------------------------------
	作成者	yamamoto

	変更履歴
	・2023/11/08 プレイヤー座標を入れる変数をTTriTypeからTPosに変更 yamashita
	・2023/11/08 めちゃくちゃコメント追加した yamashita
	・2023/11/08 回転による移動のSwing関数追加 yamashita
	・2023/11/10 当たり判定用のSphere変数を追加 yamashita
	・2023/11/10 当たり判定用のSphereのゲット関数を追加 yamashita
	・2023/11/14 全体的に処理の流れが分かりづらかったので修正 sawada
	・2023/11/14 SphereInfoの変更に対応 takagi
	・2023/11/15 Objectクラスを継承したので修正　yamamoto
	・2023/11/23 ジオメトリーからモデルに差し替え　yamashita
	・2023/11/29 Intervalの変数、関数追加　yamamoto
	・2023/12/01 IntervalをSwingSpeedに変更　yamamoto
	・2024/01/20 リファクタリング takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __HAMMER_H__	//Hammer.hインクルードガード
#define __HAMMER_H__

// =============== インクルード ===================
#include "Shader.h"
#include "SphereInfo.h"
#include "Transform3d.h"
#include "Geometry.h"
#include <DirectXMath.h>
#include "Camera.h"
#include "Model.h"
#include "Sphere.h"
#include "3dObject.h"

// =============== 定数定義 =======================
const float SwingSpeed_MIN = 9.0f;								//ハンマーのフ振りの最速値


// =============== クラス定義 =====================
class CHammer
	: public C3dObject
{
public:
	// ===プロトタイプ宣言===
	
	CHammer();	//コンストラクタ
	~CHammer();	//デストラクタ

	void Update();			// 更新関数
	void Draw();			// 描画関数
	void Swing();											// 移動による回転移動
	void AttackStart(TPos3d<float>pPos, float angle);		// 攻撃開始処理
	void SwingSpeedAdd();
	void SwingSpeedSubtract();
	float GetInterval();
	bool IsExist();
	void SetCamera(const CCamera* pCamera);
private:
	// ===メンバ変数宣言=====
	Model* m_pModel;			//プレイヤーのモデル
	VertexShader* m_pVS;		//頂点シェーダーのポインタ
	TPos3d<float> m_tPlayerPos;	//現在のプレイヤー座標
	float m_fAngleNow;			//今の角度
	int m_dAddAngleCnt;			//角度加算フレーム値
	const CCamera* m_pCamera;	//	
	float m_fSwingSpeed;		//ハンマーを振る時間
	float m_fAddAngle;			//1フレームで移動する角度量
	bool m_bExist;				//ハンマーが存在するか
	CSphere* m_pSphere;
};

#endif	//!__HAMMER_H__

