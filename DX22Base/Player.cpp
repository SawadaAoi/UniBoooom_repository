/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   Player用cpp
   ---------------------------------------
   Player.cpp

   作成者
	山本凱翔
   変更履歴
	・2023/11/03 移動作成 yamamoto
	・2023/11/06 方向追加、ダメージ判定、攻撃開始作成 yamamoto
	・2023/11/08 プレイヤーの当たり判定の大きさの定数を追加 yamashita
	・2023/11/08 攻撃中は移動できないように変更 yamashita
	・2023/11/09 カメラ対応 takagi
	・2023/11/09 GameOverの表示 yamashita
	・2023/11/09 コントローラ移動の追加 sawada
	・2023/11/11 parameter用ヘッダ追加 suzumura
	・2023/11/11 プレイヤーの点滅処理追加 Tei
	・2023/11/14 SphereInfoの変更に対応 Takagi

======================================== */

// =============== インクルード ===================
#include "Player.h"
#include "Input.h"
#include "Sphere.h"
#include "GameParameter.h"		//定数定義用ヘッダー

// =============== 定数定義 =======================
const float FORWARD_YES(1.0f);	//その方向を向いる
const float FORWARD_NO(0.0f);	//その方向を向いていない
const float XM_PI(3.141593f);	//円周率

#if MODE_GAME_PARAMETER
#else
const float PLAYER_MOVE_SPEED	= 0.1f;		//プレイヤーの移動量
const int	PLAYER_HP			= 5;
const float PLAYER_RADIUS = 0.3f;		// プレイヤーの当たり判定の大きさ
const float PLAYER_SIZE			= 1.0f;		// プレイヤーの大きさ
const int	NO_DAMAGE_TIME		= 3 * 60;	//プレイヤーの無敵時間
const int	DAMAGE_FLASH_FRAME	= 0.1 * 60;	// プレイヤーのダメージ点滅の切り替え間隔

#endif

// =============== グローバル変数定義 =============


/* ========================================
   関数：コンストラクタ
   ----------------------------------------
   内容：生成時に行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
CPlayer::CPlayer()
	: m_Transform({0.0f}, {PLAYER_SIZE}, {0.0f})
	, m_playerForward{ 0.0f,0.0f,0.0f }
	, m_pHammer(nullptr)
	, m_pPlayerGeo(nullptr)
	, m_pGameOver(nullptr)
	, m_bHammer(false)
	, m_nHp(0)
	, m_pCamera(nullptr)
	, m_nNoDamageCnt(0)
	, m_bCollide(false)
	, m_DrawFlg(true)
	, m_FlashCnt(0)
{
	m_pHammer = new CHammer();								// Hammerクラスをインスタンス
	m_pPlayerGeo = new CSphere();							// プレイヤーとして仮表示する球体オブジェクトのインスタンス
	m_pGameOver = new CSphere();
	m_nHp = PLAYER_HP;										// プレイヤーのHPを決定
	m_sphere.fRadius = PLAYER_RADIUS;				// 当たり判定用の球体の半径
}
/* ========================================
   関数：デストラクタ
   ----------------------------------------
   内容：破棄時に行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
CPlayer::~CPlayer()
{
	SAFE_DELETE(m_pGameOver);
	SAFE_DELETE(m_pPlayerGeo);
	SAFE_DELETE(m_pHammer);
}

/* ========================================
   更新処理関数関数
   ----------------------------------------
   内容：更新処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
void CPlayer::Update()
{
	if (!m_bHammer)	//攻撃中は移動しない
	{
		if (GetUseVController() == false)
		{
			Move();
		}
		else
		{
			ControllerMove();
		}
	}


	if ((IsKeyTrigger(VK_SPACE)|| IsKeyTriggerController(BUTTON_B)) || m_pHammer->Gethammer())	//スペースキーを押した時もしくはハンマーを振るフラグがONの時
	{
		m_pHammer->Update(m_Transform.fPos, m_Transform.fRadian.y);			//ハンマーを振るUpdate処理を行う
	}
	
	m_bHammer = m_pHammer->Gethammer();	//ハンマーを使用中か確認
	if (m_bCollide)							//無敵状態になっている場合
	{
		m_nNoDamageCnt++;					//毎フレームでカウントを追加
		DamageAnimation();					//プレイヤー点滅関数呼び出す
		if (m_nNoDamageCnt >= NO_DAMAGE_TIME)	//カウントが一定時間を超えたら
		{
			m_DrawFlg = true;				//点滅を解除
			m_bCollide = false;				//無敵を解除
		}
		
	}
	
}

/* ========================================
   描画処理関数
   ----------------------------------------
   内容：描画処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
void CPlayer::Draw()
{
	if (!m_pCamera)
	{
		return;
	}

	// 描画しない(点滅処理中)
	if (m_DrawFlg == false)
	{
		return;
	}

	m_pPlayerGeo->SetWorld(m_Transform.GetWorldMatrixSRT());	//ワールド座標にセット
	m_pPlayerGeo->SetView(m_pCamera->GetViewMatrix());
	m_pPlayerGeo->SetProjection(m_pCamera->GetProjectionMatrix());

	
	m_pPlayerGeo->Draw();		//プレイヤーを描画
	
	if (m_pHammer->Gethammer())	//ハンマーを振るフラグがONの時
	{
		m_pHammer->Draw(m_pCamera);		//ハンマーの描画
	}

	if (m_nHp <= 0)	//ゲームオーバーを表すオブジェクトの描画	<=TODO 後々消します
	{
		m_pGameOver->SetView(m_pCamera->GetViewMatrix());										//ビューのセット
		m_pGameOver->SetProjection(m_pCamera->GetProjectionMatrix());							//プロジェクションのセット
		DirectX::XMMATRIX mat = DirectX::XMMatrixTranslation(0.0f, 2.0f, 0.0f);					//移動の変換行列
		mat = DirectX::XMMatrixTranspose(mat);													//転置
		DirectX::XMFLOAT4X4 fmat;																//セットワールド用の変数
		DirectX::XMStoreFloat4x4(&fmat, mat);													//MATRIX型から変換
		m_pGameOver->SetWorld(fmat);															//ワールドのセット
		m_pGameOver->Draw();																	//GameOverの描画
	}
}

/* ========================================
   ダメージ関数
   ----------------------------------------
   内容：プレイヤーがダメージを受ける
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
void CPlayer::Damage()
{
	m_nHp -= 1;
	m_bCollide = true;	//プレイヤーを一定時間、無敵にする
	m_nNoDamageCnt = 0;	//プレイヤー無敵時間のカウントを0に戻す

	if (m_nHp <= 0)
	{
		//ゲームオーバー処理 <= TODO
	}
}

/* ========================================
   プレイヤーの移動関数
   ----------------------------------------
   内容：プレイヤーが移動する関数
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
void CPlayer::Move()
{//＝＝＝playerの位置と進行方向を更新＝＝＝
	if (IsKeyPress('W'))
	{	//前に移動
		m_Transform.fPos.z += PLAYER_MOVE_SPEED;					//playerを+Z方向に移動
		m_playerForward.z = FORWARD_YES;		//向いている方向
		m_playerForward.x = FORWARD_NO;
		if (IsKeyPress('A'))
		{//左前に移動
			m_Transform.fPos.x -= PLAYER_MOVE_SPEED;
			m_playerForward.x = -FORWARD_YES;
		}
		else if (IsKeyPress('D'))
		{//右前に移動
			m_Transform.fPos.x += PLAYER_MOVE_SPEED;
			m_playerForward.x = FORWARD_YES;
		}
	}
	else if (IsKeyPress('S'))
	{//後ろに移動
		m_Transform.fPos.z -= PLAYER_MOVE_SPEED;
		m_playerForward.z = -FORWARD_YES;
		m_playerForward.x = FORWARD_NO;
		if (IsKeyPress('A'))
		{//左後ろに移動
			m_Transform.fPos.x -= PLAYER_MOVE_SPEED;
			m_playerForward.x = -FORWARD_YES;
		}
		else if (IsKeyPress('D'))
		{//右後ろに移動
			m_Transform.fPos.x += PLAYER_MOVE_SPEED;
			m_playerForward.x = FORWARD_YES;
		}
	}
	else if (IsKeyPress('D'))
	{//右に移動
		m_Transform.fPos.x += PLAYER_MOVE_SPEED;
		m_playerForward.x = FORWARD_YES;
		m_playerForward.z = FORWARD_NO;
	}
	else if (IsKeyPress('A'))
	{//左に移動
		m_Transform.fPos.x -= PLAYER_MOVE_SPEED;
		m_playerForward.x = -FORWARD_YES;
		m_playerForward.z = FORWARD_NO;
	}

	//進行方向からplayerの向きを決める
	if (m_playerForward.x == FORWARD_NO)	//x方向を向いてなかったらZ軸（前後）に動くだけ
	{
		if (m_playerForward.z > 0.0f) {//+Z前方向にする
			m_Transform.fRadian.y = 0.0f; // 前方向
		}
		else {
			m_Transform.fRadian.y = XM_PI; // 後方向
		}
	}
	else {//Zの方向にも向いてるなら斜め、向いてないなら横の方向を向く
		m_Transform.fRadian.y = atan(m_playerForward.x / m_playerForward.z);	//ここで斜めか判断
		if (m_playerForward.z < 0.0f) {
			m_Transform.fRadian.y += XM_PI; // ｚが-なら後ろなので足して後ろ側に
		}
	}
}

/* ========================================
   コントローラ入力関数
   ----------------------------------------
   内容：コントローラ入力の移動処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
void CPlayer::ControllerMove()
{
	// コントローラーの左スティックの傾きを取得
	float stick_x = IsStickLeft().x;
	float stick_y = IsStickLeft().y;	

	// スティックが真ん中の場合移動しない
	if (stick_x != 0 || stick_y != 0)
	{
		float moveRad = atan2(stick_y * -1, stick_x);	// スティックを倒した方向の角度を求める(y軸が逆なので－1を掛ける)

		// 角度方向に移動する処理
		m_Transform.fPos.x += cosf(moveRad) * PLAYER_MOVE_SPEED;
		m_Transform.fPos.z += sinf(moveRad) * PLAYER_MOVE_SPEED;

		m_Transform.fRadian.y = atan2(stick_y, stick_x) + (XM_PI/2);	// XMMatrixTranslationが時計回りで角度が90度ずれている(↑が0)ので調整
	}
}



/* ========================================
   プレイヤー当たり判定取得関数
   ----------------------------------------
   内容：プレイヤーの当たり判定用の球体を取得する関数
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：当たり判定(Sphere)
======================================== */
tagSphereInfo CPlayer::GetPlayerSphere()
{
	return m_sphere;
}

/* ========================================
   ハンマー当たり判定取得関数
   ----------------------------------------
   内容：ハンマーの当たり判定用の球体を取得する関数
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：当たり判定(Sphere)
======================================== */
tagSphereInfo CPlayer::GetHammerSphere()
{
	return m_pHammer->GetSphere();
}

/* ========================================
   プレイヤー座標の取得関数
   ----------------------------------------
   内容：プレイヤーの座標を取得する関数
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：座標(x,y,z)
======================================== */
TPos3d<float> CPlayer::GetPos()
{
	return m_Transform.fPos;
}

/* ========================================
   Collision確認関数
   ----------------------------------------
   内容：プレイヤーが無敵状態かの確認
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：bool
======================================== */
bool CPlayer::GetCollide()
{
	return m_bCollide;
}

/* ========================================
   カメラのセット関数
   ----------------------------------------
   内容：プレイヤー追従カメラをセットする
   ----------------------------------------
   引数：カメラ
   ----------------------------------------
   戻値：なし
======================================== */
void CPlayer::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;	//中身は変えられないけどポインタはかえれるのでヨシ！
}

/* ========================================
   ハンマー攻撃フラグ取得関数
   ----------------------------------------
   内容：ハンマー攻撃フラグ取得する
   ----------------------------------------
   引数：無し
   ----------------------------------------
   戻値：ハンマー攻撃フラグ
======================================== */
bool CPlayer::GetHammerFlg()
{
	return m_bHammer;
}

/* ========================================
   プレイヤー点滅関数
   ----------------------------------------
   内容：プレイヤーがダメージを受けたら点滅する
   ----------------------------------------
   引数：無し
   ----------------------------------------
   戻値：無し
======================================== */
void CPlayer::DamageAnimation()
{
					
	m_FlashCnt++;						//毎フレームでカウントを追加
	if (m_FlashCnt >= DAMAGE_FLASH_FRAME)
	{
		// 描画するかしない切り替え
		if (m_DrawFlg)
		{
			m_DrawFlg = false;
		}	
		else
		{
			m_DrawFlg = true;
		}

		m_FlashCnt = 0;
	}

}
