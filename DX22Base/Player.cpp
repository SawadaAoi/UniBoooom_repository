/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   Player用cpp
   ---------------------------------------
   Player.cpp

   作成者
	山本凱翔
   変更履歴
   ・2023/11/03 移動作成 山本凱翔
   ・2023/11/06 方向追加、ダメージ判定、攻撃開始作成 山本凱翔
   ・2023/11/08 プレイヤーの当たり判定の大きさの定数を追加 /山下凌佑
   ・2023/11/08 攻撃中は移動できないように変更 /山下凌佑
   ・2023/11/09 カメラ対応 髙木駿輔


   ======================================== */

   // =============== インクルード ===================
#include"Player.h"
#include "Input.h"
#include "Sphere.h"
// =============== 定数定義 =======================
#define PLAYERMOVE (0.1f)	//playerの移動量
#define XM_PI (3.141593f)	//円周率
#define FORWARD_YES	(1.0f)	//その方向を向いる
#define FORWARD_NO (0.0f)	//その方向を向いていない
const int HP = 5;
const float PLAYER_RADIUS = 1.0f;	//プレイヤーの当たり判定の大きさ
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
	:m_pos{ 0.0f,0.0f,0.0f }
	/*,m_playerPosition{ 0.0f,0.0f,0.0f }*/
	,m_playerForward{ 0.0f,0.0f,0.0f }
	, m_playerRotation(0.0f)
	, m_pHammer(nullptr)
	, m_pPlayerGeo(nullptr)
	, m_bHammer(false)
	,m_nHp(0)
	,m_pCamera(nullptr)
{
	m_T = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);	//移動の変換行列を初期化
	m_S = DirectX::XMMatrixScaling(2.0f, 2.0f, 2.0f);		//拡縮の変換行列を初期化
	m_Ry = DirectX::XMMatrixRotationY(0.0f);				//Y軸回転の変換行列を初期化
	m_pHammer = new CHammer();								//Hammerクラスをインスタンス
	m_pPlayerGeo = new CSphere();							//プレイヤーとして仮表示する球体オブジェクトのインスタンス
	m_nHp = HP;												//プレイヤーのHPを決定
	m_sphere.pos = { 0.0f,0.0f,0.0f };	//当たり判定用の球体の座標を初期化
	m_sphere.radius = PLAYER_RADIUS;	//当たり判定用の球体の半径
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
	SAFE_DELETE(m_pHammer);
	SAFE_DELETE(m_pPlayerGeo);
}

/* ========================================
   Update関数
   ----------------------------------------
   内容：毎フレーム行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
void CPlayer::Update()
{
	if (!m_bHammer)	//攻撃中は移動しない
	{
		Move();
	}


	if (IsKeyTrigger(VK_SPACE) || m_pHammer->Gethammer())	//スペースキーを押した時もしくはハンマーを振るフラグがONの時
	{
		m_pHammer->Update(m_pos, m_playerRotation);			//ハンマーを振るUpdate処理を行う
	}
	m_bHammer = m_pHammer->Gethammer();	//ハンマーを使用中か確認
}

/* ========================================
   Draw関数
   ----------------------------------------
   内容：描画を行う
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

	m_pPlayerGeo->SetView(m_pCamera->GetViewMatrix());
	m_pPlayerGeo->SetProjection(m_pCamera->GetProjectionMatrix());
	m_pPlayerGeo->Draw();		//プレイヤーを描画
	if (m_pHammer->Gethammer())	//ハンマーを振るフラグがONの時
	{
		m_pHammer->Draw(m_pCamera);		//ハンマーの描画
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
void CPlayer::Damege()
{
	m_nHp -= 1;

	if (m_nHp <= 0)
	{
		//ゲームオーバー処理 <= TODO
	}
}

void CPlayer::Move()
{//＝＝＝playerの位置と信仰方向を更新＝＝＝
	if (IsKeyPress('W'))
	{	//前に移動
		m_pos.z += PLAYERMOVE;					//playerを+Z方向に移動
		m_playerForward.z = FORWARD_YES;		//向いている方向
		m_playerForward.x = FORWARD_NO;
		if (IsKeyPress('A'))
		{//左前に移動
			m_pos.x -= PLAYERMOVE;
			m_playerForward.x = -FORWARD_YES;
		}
		else if (IsKeyPress('D'))
		{//右前に移動
			m_pos.x += PLAYERMOVE;
			m_playerForward.x = FORWARD_YES;
		}
	}
	else if (IsKeyPress('S'))
	{//後ろに移動
		m_pos.z -= PLAYERMOVE;
		m_playerForward.z = -FORWARD_YES;
		m_playerForward.x = FORWARD_NO;
		if (IsKeyPress('A'))
		{//左後ろに移動
			m_pos.x -= PLAYERMOVE;
			m_playerForward.x = -FORWARD_YES;
		}
		else if (IsKeyPress('D'))
		{//右後ろに移動
			m_pos.x += PLAYERMOVE;
			m_playerForward.x = FORWARD_YES;
		}
	}
	else if (IsKeyPress('D'))
	{//右に移動
		m_pos.x += PLAYERMOVE;
		m_playerForward.x = FORWARD_YES;
		m_playerForward.z = FORWARD_NO;
	}
	else if (IsKeyPress('A'))
	{//左に移動
		m_pos.x -= PLAYERMOVE;
		m_playerForward.x = -FORWARD_YES;
		m_playerForward.z = FORWARD_NO;
	}

	m_sphere.pos = m_pos;	//プレイヤーの座標を当たり判定用の球体にコピー

	//進行方向からplayerの向きを決める
	if (m_playerForward.x == FORWARD_NO)	//x方向を向いてなかったらZ軸（前後）に動くだけ
	{
		if (m_playerForward.z > 0.0f) {//+Z前方向にする
			m_playerRotation = 0.0f; // 前方向
		}
		else {
			m_playerRotation = XM_PI; // 後方向
		}
	}
	else {//Zの方向にも向いてるなら斜め、向いてないなら横の方向を向く
		m_playerRotation = atan(m_playerForward.x / m_playerForward.z);	//ここで斜めか判断
		if (m_playerForward.z < 0.0f) {
			m_playerRotation += XM_PI; // ｚが-なら後ろなので足して後ろ側に
		}
	}

	//=====playerの座標、回転をセット=====
	m_T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);		//移動の変換行列
	DirectX::XMMATRIX Ry = DirectX::XMMatrixRotationY(m_playerRotation);//Y軸の回転行列
	DirectX::XMMATRIX mat = Ry * m_T;									//変換行列を結合
	mat = DirectX::XMMatrixTranspose(mat);								//変換行列を転置
	DirectX::XMFLOAT4X4 fMat;											//行列の格納先
	DirectX::XMStoreFloat4x4(&fMat, mat);								//XMFLOAT4X4に変換して格納
	m_pPlayerGeo->SetWorld(fMat);										//ワールド座標にセット
}

/* ========================================
   プレイヤーのsphereのゲット関数
   ----------------------------------------
   内容：プレイヤーの当たり判定用の球体を取得する関数
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：Sphere型
   ======================================== */
CSphereInfo::Sphere CPlayer::GetPlayerSphere()
{
	return m_sphere;
}

/* ========================================
   ハンマーのsphereのゲット関数
   ----------------------------------------
   内容：ハンマーの当たり判定用の球体を取得する関数
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：Sphere型
   ======================================== */
CSphereInfo::Sphere CPlayer::GetHammerSphere()
{
	return m_pHammer->GetSphere();
}

/* ========================================
   プレイヤーの座標のゲット関数
   ----------------------------------------
   内容：プレイヤーの座標を取得する関数
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：TPos
   ======================================== */
TPos3d<float> CPlayer::GetPos()
{
	return m_pos;
}

//コメントめんどいtkg
void CPlayer::GetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;	//中身は変えられないけどポインタはかえれるのでヨシ！
}