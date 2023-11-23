/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	Hammer用ヘッダ
	------------------------------------
	Hammer.h
	------------------------------------
	作成者
		山本凱翔
	変更履歴
	・2023/11/08 プレイヤー座標を入れる変数をTTriTypeからTPosに変更 Yamashita
	・2023/11/08 めちゃくちゃコメント追加した Yamashita
	・2023/11/08 回転による移動のSwing関数追加 Yamashita
	・2023/11/10 当たり判定用のSphere変数を追加 Yamashita
	・2023/11/10 当たり判定用のSphereのゲット関数を追加 Yamashita
	・2023/11/14 全体的に処理の流れが分かりづらかったので修正 Sawada
	・2023/11/14 SphereInfoの変更に対応 Takagi
	・2023/11/15 Objectクラスを継承したので修正　yamamoto
========================================== */

#ifndef __HAMMER_H__
#define __HAMMER_H__

// =============== インクルード ===================
#include "Shader.h"
#include "SphereInfo.h"
#include "Transform3d.h"
#include "Geometry.h"
#include <DirectXMath.h>
#include "Camera.h"
#include "Object.h"
#include "Model.h"
// =============== クラス定義 =====================
class CHammer
	: public CObject
{
public:
	// ===プロトタイプ宣言===
	
	CHammer();	//コンストラクタ
	~CHammer();	//デストラクタ

	bool Update();	// 更新関数
	void Draw(const CCamera* pCamera);				// 描画関数
	void Swing();									// 移動による回転移動
	void AttackStart(TPos3d<float>pPos, float angle);								// 攻撃開始処理
private:
	// ===メンバ変数宣言=====
	Model* m_pModel;				//プレイヤーのモデル
	VertexShader* m_pVS;			//頂点シェーダーのポインタ
	CGeometry* m_pHammerGeo;		// ハンマーを仮表示する図形
	TPos3d<float> m_tPlayerPos;		// 現在のプレイヤー座標
	float m_fAngleNow;				// 今の角度
	int m_dAddAngleCnt;				// 角度加算フレーム値
};

#endif // !__HAMMER_H__

