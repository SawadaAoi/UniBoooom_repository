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
	・2023/11/08 プレイヤー座標を入れる変数をTTriTypeからTPosに変更 /山下凌佑
	・2023/11/08 めちゃくちゃコメント追加した /山下凌佑
	・2023/11/08 回転による移動のSwing関数追加 /山下凌佑
	・当たり判定用のSphere変数を追加 /山下凌佑
	・当たり判定用のSphereのゲット関数を追加 /山下凌佑

========================================== */

#ifndef __HAMMER_H__
#define __HAMMER_H__

// =============== インクルード ===================
#include "Shader.h"
#include "Pos3d.h"
#include "SphereInfo.h"
#include "Geometry.h"
#include <DirectXMath.h>
#include "Camera.h"

// =============== クラス定義 =====================
class CHammer
{
public:
	// ===プロトタイプ宣言===
	
	CHammer();	//コンストラクタ
	~CHammer();	//デストラクタ

	void Update(TPos3d<float> pPos, float angle);	// 更新関数
	void Draw(const CCamera* pCamera);				// 描画関数
	void Swing(TPos3d<float>pPos,float angle);		// 移動による回転移動
	void AttackStart();								// 攻撃開始処理

	bool GetAttackFlg();								// ハンマーを使用中かどうかのフラグを取得
	CSphereInfo::Sphere GetSphere();				// あたり判定取得
private:
	// ===メンバ変数宣言=====
	TPos3d<float> m_pos;			// ハンマーの位置座標
	CSphereInfo::Sphere m_sphere;	// ハンマーの当たり判定用の球体
	TTriType<float> m_scale;		// サイズ

	float m_nowangle;				// 今の角度
	float m_stateangle;				//
	bool m_bAttackFlg;				//ハンマーを使用中のフラグ
	CGeometry* m_pHammerGeo;		//ハンマーを仮表示する図形
};

#endif // !__HAMMER_H__

