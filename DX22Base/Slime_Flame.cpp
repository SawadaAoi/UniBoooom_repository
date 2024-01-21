/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	フレイムスライムcpp
	------------------------------------
	Slime_Flame.cpp
	------------------------------------
	作成者	鈴村朋也

	変更履歴
	・2023/11/14 クラス作成 Suzumura
	・2023/11/14 炎スライム仕様の実装 Suzumura
	・2023/11/15 スライムのモデルと頂点シェーダーをmanagerから受け取るように変更 yamashita
	・2023/11/28 影の大きさを設定する変数追加 nieda
	・2023/12/07 ゲームパラメータから一部定数移動 takagi
	・2024/01/18 炎スライムエフェクト追加 Tei

========================================== */

// =============== インクルード ===================
#include "Slime_Flame.h"
#include "GameParameter.h"		//定数定義用ヘッダー

// =============== 定数定義 =======================
#if MODE_GAME_PARAMETER
#else
const float LEVEL_FLAME_SCALE = 1.0f;
const float LEVEL_FLAME_SPEED = ENEMY_MOVE_SPEED * 0.2f;
const int	LEVEL_FLAME_ATTACK = 1;	// 攻撃力
#endif
const float LEVEL_FLAME_SHADOW_SCALE = 2.0f;// スライム＿フレイムの影の大きさ

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：コンストラクタ
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
CSlime_Flame::CSlime_Flame()
{
	m_Transform.fScale = { LEVEL_FLAME_SCALE,LEVEL_FLAME_SCALE ,LEVEL_FLAME_SCALE };
	m_Sphere.fRadius *= LEVEL_FLAME_SCALE;
	m_eSlimeSize = E_SLIME_LEVEL::LEVEL_FLAME;
	SetNormalSpeed();	
	m_nAttack = LEVEL_FLAME_ATTACK;
	m_fScaleShadow = LEVEL_FLAME_SHADOW_SCALE;	// 影の大きさを設定
}

/* ========================================
	コンストラクタ関数(座標指定)
	-------------------------------------
	内容：コンストラクタ
	-------------------------------------
	引数1：生成する座標
	-------------------------------------
	戻値：無し
=========================================== */
CSlime_Flame::CSlime_Flame(TPos3d<float> pos, float fSize, Effekseer::EffectRef flameSlimeEffect, VertexShader* pVS, Model* pModel)
	: CSlime_Flame()
{
	m_Transform.fPos = pos;			// 初期座標を指定
	m_pVS = pVS;
	m_pModel = pModel;
	// エフェクト初期化
	m_flameSlimeEffect = flameSlimeEffect;	//エフェクトをセット
	m_efcslimeHnadle = LibEffekseer::GetManager()->Play(m_flameSlimeEffect, pos.x, pos.y, pos.z);	//エフェクトの開始
	LibEffekseer::GetManager()->SetScale(m_efcslimeHnadle, LEVEL_FLAME_SCALE* fSize, LEVEL_FLAME_SCALE * fSize, LEVEL_FLAME_SCALE * fSize);	//エフェクトのサイズを設定
	LibEffekseer::GetManager()->SetLocation(m_efcslimeHnadle, pos.x, pos.y, pos.z);
}

/* ========================================
	デストラクタ関数
	-------------------------------------
	内容：デストラクタ
	-------------------------------------
	引数1：
	-------------------------------------
	戻値：
=========================================== */
CSlime_Flame::~CSlime_Flame()
{
}

//void CSlime_Flame::Draw()
//{
//	//エフェクトの描画
//	TPos3d<float> cameraPos = m_pCamera->GetPos();							//カメラ座標を取得
//	DirectX::XMFLOAT3 fCameraPos(cameraPos.x, cameraPos.y, cameraPos.z);	//XMFLOAT3に変換
//	LibEffekseer::SetViewPosition(fCameraPos);								//カメラ座標をセット
//	LibEffekseer::SetCameraMatrix(m_pCamera->GetViewWithoutTranspose(), m_pCamera->GetProjectionWithoutTranspose());	//転置前のviewとprojectionをセット
//}
//
//void CSlime_Flame::Update()
//{
//	LibEffekseer::GetManager()->SetLocation(m_efcslimeHnadle, m_Transform.fPos.x, m_Transform.fPos.y, m_Transform.fPos.z);
//
//}

/* ========================================
	通常移動関数
	-------------------------------------
	内容：スライムの通常移動をオーバーライド
	-------------------------------------
	引数1：プレイヤー当たり判定(Sphere) ※使用してない
	-------------------------------------
	戻値：なし
=========================================== */
void CSlime_Flame::NormalMove()
{
	RandomMove();	// ランダム移動

}

/* ========================================
	スピード決定関数
	-------------------------------------
	内容：スライムの移動速度を設定
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CSlime_Flame::SetNormalSpeed()
{
	m_fSpeed = LEVEL_FLAME_SPEED;	//移動速度に定数をセット
}



