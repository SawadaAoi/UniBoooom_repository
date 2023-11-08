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
	:m_playerPosition{ 0.0f,0.0f,0.0f }
	,m_playerForward{ 0.0f,0.0f,1.0f }
	, m_playerRotation(0.0f)
	, m_pHammer(nullptr)
	, m_pPlayer(nullptr)
	, m_bHammer(false)
	,m_nHp(0)
	,m_pCamera(nullptr)
{
	m_T = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	m_S = DirectX::XMMatrixScaling(2.0f, 2.0f, 2.0f);
	m_Ry = DirectX::XMMatrixRotationY(0.0f);
	m_pHammer = new CHammer();
	m_pPlayer = new CSphere();
	m_nHp = HP;

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
	if (m_pHammer != nullptr)
	{
		delete m_pHammer;
		m_pHammer = nullptr;
	}
}

void CPlayer::Update()
{
	
	Move();

	if (IsKeyTrigger(VK_SPACE) || m_pHammer->Gethammer())	//ハンマーを振る
	{
		m_pHammer->Update(m_playerPosition, m_playerRotation);
	}
}

void CPlayer::Draw()
{
	if (!m_pCamera)
	{
		return;
	}

	m_pPlayer->SetView(m_pCamera->GetViewMatrix());
	m_pPlayer->SetProjection(m_pCamera->GetProjectionMatrix());
	m_pPlayer->Draw();
	if (m_pHammer->Gethammer())
	{
		m_pHammer->Draw();
	}
}

void CPlayer::Damege()
{
	m_nHp -= 1;
}

void CPlayer::Move()
{//＝＝＝playerの位置と信仰方向を更新＝＝＝
	if (IsKeyPress('W'))
	{		//前
		m_playerPosition.z += PLAYERMOVE;			//playerを+Z方向に移動
		m_playerForward.z = FORWARD_YES;			//向いている方向
		m_playerForward.x = FORWARD_NO;
		if (IsKeyPress('A'))
		{//左前
			m_playerPosition.x -= PLAYERMOVE;
			m_playerForward.x = -FORWARD_YES;
		}
		else if (IsKeyPress('D'))
		{//右前
			m_playerPosition.x += PLAYERMOVE;
			m_playerForward.x = FORWARD_YES;
		}
	}
	else if (IsKeyPress('S'))
	{//後ろ
		m_playerPosition.z -= PLAYERMOVE;
		m_playerForward.z = -FORWARD_YES;
		m_playerForward.x = FORWARD_NO;
		if (IsKeyPress('A'))
		{//左後ろ
			m_playerPosition.x -= PLAYERMOVE;
			m_playerForward.x = -FORWARD_YES;
		}
		else if (IsKeyPress('D'))
		{//右後ろ
			m_playerPosition.x += PLAYERMOVE;
			m_playerForward.x = FORWARD_YES;
		}
	}
	else if (IsKeyPress('D'))
	{//右
		m_playerPosition.x += PLAYERMOVE;
		m_playerForward.x = FORWARD_YES;
		m_playerForward.z = FORWARD_NO;
	}
	else if (IsKeyPress('A'))
	{//左
		m_playerPosition.x -= PLAYERMOVE;
		m_playerForward.x = -FORWARD_YES;
		m_playerForward.z = FORWARD_NO;
	}

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
	m_T = DirectX::XMMatrixTranslation(m_playerPosition.x, m_playerPosition.y, m_playerPosition.z);
	DirectX::XMMATRIX Ry = DirectX::XMMatrixRotationY(m_playerRotation);
	DirectX::XMMATRIX mat = Ry * m_T;
	mat = DirectX::XMMatrixTranspose(mat);
	DirectX::XMFLOAT4X4 fMat;	//行列の格納先
	DirectX::XMStoreFloat4x4(&fMat, mat);
	m_pPlayer->SetWorld(fMat);
}

//コメントめんどいtkg
void CPlayer::GetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;	//中身は変えられないけどポインタはかえれるのでヨシ！
}