/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	player用ヘッダ
	------------------------------------
	player.h
	------------------------------------
	作成者
		山本凱翔
	変更履歴
	・2023/11/03 h,作成 山本凱翔
	・2023/11/06 ダメージ処理追加,コメント追加 山本凱翔
	・2023/11/08 Pos.hをインクルード /山下凌佑
	・2023/11/08 当たり判定用の球体m_sphereを追加 /山下凌佑
	・2023/11/08 プレイヤー座標を入れる変数をTTriTypeからTPosに変更 /山下凌佑


========================================== */

#ifndef __PLAYER_H__
#define __PLAYER_H_

// =============== インクルード ===================
#include "Shader.h"
#include"hammer.h"
#include "Geometry.h"
#include "SphereInfo.h"
#include "Pos.h"
// =============== クラス定義 =====================
class CPlayer
{
public:
	// =============== プロトタイプ宣言 ===============
	CPlayer();
	~CPlayer();

	void Update();	//更新
	void Draw();	//描画
	void Damege();	//自身のHPを減らす
	void Move();	//移動関数
	CSphereInfo::Sphere GetPlayerSphere();	//当たり判定を取るためゲッター
	CSphereInfo::Sphere GetHammerSphere();	//当たり判定を取るためゲッター
	TPos<float> GetPos();	//プレイヤーの座標を取得

private:
	// ===============メンバ関数宣言===============
	DirectX::XMMATRIX m_T;				//位置
	DirectX::XMMATRIX m_S;				//拡縮
	DirectX::XMMATRIX m_Ry;				//回転
	//TTriType<float> m_playerPosition;	//プレイヤーの位置
	TPos<float> m_pos;					//プレイヤーの座標
	CSphereInfo::Sphere m_sphere;		//プレイヤーの当たり判定用の球体
	TTriType<float> m_playerForward;	// プレイヤーの初期進行方向
	float m_playerRotation;				// プレイヤーの回転角度
	int m_nHp;							//プレイヤーの体力
	CHammer* m_pHammer;
	CGeometry* m_pPlayerGeo;
	bool m_bHammer;						//攻撃中かどうかのフラグ
};


#endif // !__PLAYER_H__



