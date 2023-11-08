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
	・2023/11/09 GetPosAddress追加、カメラ追加 髙木駿輔

========================================== */

#ifndef __PLAYER_H__
#define __PLAYER_H_

// =============== インクルード ===================
#include "Shader.h"
#include"hammer.h"
#include "Geometry.h"
#include "Pos.h"
#include "Camera.h"
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
	void Move();

	TPos<float> GetPos() { return m_playerPosition; }
	TPos<float>* GetPosAddress() { return &m_playerPosition; }
	void GetCamera(const CCamera* pCamera);
	CHammer* GetHammer() { return m_pHammer; }

private:
	// ===============メンバ関数宣言===============
	DirectX::XMMATRIX m_T;				//位置
	DirectX::XMMATRIX m_S;				//拡縮
	DirectX::XMMATRIX m_Ry;				//回転
	TPos<float> m_playerPosition;	//プレイヤーの位置
	TTriType<float> m_playerForward;	// プレイヤーの初期進行方向
	float m_playerRotation;				// プレイヤーの回転角度
	int m_nHp;							//プレイヤーの体力
	CHammer* m_pHammer;
	CGeometry* m_pPlayer;
	bool m_bHammer;						//攻撃中かどうかのフラグ
	const CCamera* m_pCamera;
};


#endif // !__PLAYER_H__



