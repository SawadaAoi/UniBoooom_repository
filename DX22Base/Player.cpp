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
	・2023/11/14 キーボードの入力移動処理内容を適切な形に変更 Sawada
	・2023/11/15 Objectクラスを継承したので修正　yamamoto
	・2023/11/19 移動のSEを再生 yamashita
	・2023/11/19 被ダメージ時とハンマーを振るSEを再生 yamashita
	・2023/11/19 サウドファイル読み込み関数を作成 yamashita
	・2023/11/23 ジオメトリーからモデルに差し替え yamashita
	・2023/11/23 ゲームオーバーの仮表示を削除 yamashita
	・2023/11/27 Update内ハンマー振り間隔処理追加 Tei
	・2023/11/28 ダメージ処理に受けるダメージ量を追加 Sawada
	・2023/11/28 回復処理を追加 yamashita

======================================== */

// =============== インクルード ===================
#include "Player.h"
#include "Input.h"
#include "Sphere.h"
#include "GameParameter.h"		//定数定義用ヘッダー
#define _USE_MATH_DEFINES		// 円周率
#include <math.h>				// 円周率

// =============== 定数定義 =======================
const float KEYBOARD_INPUT_SIZE = 1.0f;	// キーボードの入力値の大きさ

#if MODE_GAME_PARAMETER
#else
const float PLAYER_MOVE_SPEED	= 0.1f;			//プレイヤーの移動量
const int	PLAYER_HP			= 5;
const float PLAYER_RADIUS		= 0.3f;			// プレイヤーの当たり判定の大きさ
const float PLAYER_SIZE			= 1.0f;			// プレイヤーの大きさ
const int	NO_DAMAGE_TIME		= 3 * 60;		//プレイヤーの無敵時間
const int	DAMAGE_FLASH_FRAME	= 0.1f * 60;	// プレイヤーのダメージ点滅の切り替え間隔
const int	SE_RUN_INTERVAL		= 0.4f * 60;	//プレイヤーの移動によるSE発生の間隔
const int	HEAL_NUM			= 1;			//プレイヤーの回復量
const float	SE_RUN_VOLUME		= 0.3f;			//移動によるSEの音量
const float HAMMER_INTERVAL_TIME	= 1.0f * 60;	// ハンマー振り間隔

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
	: m_pHammer(nullptr)
	, m_bAttackFlg(false)
	, m_nHp(0)
	, m_pCamera(nullptr)
	, m_nNoDamageCnt(0)
	, m_bCollide(false)
	, m_DrawFlg(true)
	, m_FlashCnt(0)
	, m_pSESwingHammer(nullptr)
	, m_pSESwingHamSpeaker(nullptr)
	, m_pSERun(nullptr)
	, m_pSERunSpeaker(nullptr)
	, m_pSEDamaged(nullptr)
	, m_pSEDamagedSpeaker(nullptr)
	, m_nMoveCnt(0)
	, m_bIntFlg(false)
	, m_fIntCnt(0.0f)
{
	m_pHammer = new CHammer();								// Hammerクラスをインスタンス
	m_nHp = PLAYER_HP;										// プレイヤーのHPを決定
	m_Sphere.fRadius = PLAYER_RADIUS;						// 当たり判定用の球体の半径
	m_Transform.fScale = PLAYER_SIZE;
	LoadSound();	//サウンドファイル読み込み

	//頂点シェーダ読み込み
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}
	//プレイヤーのモデル読み込み
	m_pModel = new Model;
	if (!m_pModel->Load("Assets/Model/player/player.FBX", 1.0f, Model::None)) {		//倍率と反転は省略可
		MessageBox(NULL, "player", "Error", MB_OK);	//ここでエラーメッセージ表示
	}
	m_pModel->SetVertexShader(m_pVS);
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
	SAFE_DELETE(m_pModel);
	SAFE_DELETE(m_pVS);
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
	// ハンマー攻撃中
	if (m_bAttackFlg == true)
	{
		// ハンマーの攻撃が終了したら
		if (m_pHammer->Update() == false)
		{
			m_bAttackFlg = false;	// 攻撃中フラグをオフにする
			m_bIntFlg = true;		// ハンマー振り間隔フラグオン
		}

	}
	else
	{
		// ハンマー間隔時間フラグがオンの時
		if (m_bIntFlg)
		{
			m_fIntCnt++;				// ハンマー間隔時間カウント加算
			if (m_fIntCnt >= HAMMER_INTERVAL_TIME)
			{
				m_bIntFlg = false;		// ハンマー間隔時間フラグオン
				m_fIntCnt = 0.0f;		//ハンマー間隔時間リセット
			}
		}

		// コントローラが接続されてない場合
		if (GetUseVController() == false)
		{
			MoveKeyboard();
		}
		// コントローラが接続されている場合
		else
		{
			MoveController();
		}


		// スペースキーを押した時、またはコントローラのBボタンを押した時 && ハンマー間隔時間経過済み
		if ((IsKeyTrigger(VK_SPACE) || IsKeyTriggerController(BUTTON_B)) && !m_bIntFlg)
		{
			m_pHammer->AttackStart(m_Transform.fPos, m_Transform.fRadian.y);	// ハンマー攻撃開始
			m_bAttackFlg = true;	// 攻撃フラグを有効にする
			m_pSESwingHamSpeaker = CSound::PlaySound(m_pSESwingHammer);	//ハンマーを振るSEの再生
		}

	}
	
	// 無敵状態になっている場合
	if (m_bCollide)							
	{
		m_nNoDamageCnt++;					// 毎フレームでカウントを追加
		DamageAnimation();					// プレイヤー点滅関数呼び出す

		// カウントが一定時間を超えたら
		if (m_nNoDamageCnt >= NO_DAMAGE_TIME)	
		{
			m_DrawFlg = true;				// 点滅を解除
			m_bCollide = false;				// 無敵を解除
		}
		
	}

	SE_Move();	//移動によるSEの処理
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
	// 描画しない(点滅処理中)
	if (m_DrawFlg == true)
	{
		DirectX::XMFLOAT4X4 mat[3];

		mat[0] = m_Transform.GetWorldMatrixSRT();
		mat[1] = m_pCamera->GetViewMatrix();
		mat[2] = m_pCamera->GetProjectionMatrix();

		//-- 行列をシェーダーへ設定
		m_pVS->WriteBuffer(0, mat);

		//-- モデル表示
		if (m_pModel) {
			// レンダーターゲット、深度バッファの設定
			RenderTarget* pRTV = GetDefaultRTV();	//デフォルトで使用しているRenderTargetViewの取得
			DepthStencil* pDSV = GetDefaultDSV();	//デフォルトで使用しているDepthStencilViewの取得
			SetRenderTargets(1, &pRTV, pDSV);		//DSVがnullだと2D表示になる

			m_pModel->Draw();
		}
	}
	
	if (m_bAttackFlg)
	{
		m_pHammer->Draw();		//ハンマーの描画
	}

}

/* ========================================
   ダメージ関数
   ----------------------------------------
   内容：プレイヤーがダメージを受ける
   ----------------------------------------
   引数：攻撃力
   ----------------------------------------
   戻値：なし
======================================== */
void CPlayer::Damage(int DmgNum)
{
	m_nHp -= DmgNum;
	m_bCollide = true;	//プレイヤーを一定時間、無敵にする
	m_nNoDamageCnt = 0;	//プレイヤー無敵時間のカウントを0に戻す
	m_pSEDamagedSpeaker = CSound::PlaySound(m_pSEDamaged);	//被ダメージ時のSE再生

	if (m_nHp <= 0)
	{
		//ゲームオーバー処理 <= TODO
	}
}

/* ========================================
   キーボード用入力移動関数
   ----------------------------------------
   内容：キーボード入力の移動処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
void CPlayer::MoveKeyboard()
{
	TPos3d<float> fMoveInput;	// キーボードの入力値を入れる変数

	// キー入力
	// 上下
	if		(IsKeyPress('W'))	{ fMoveInput.z =  KEYBOARD_INPUT_SIZE; }	// ↑
	else if (IsKeyPress('S'))	{ fMoveInput.z = -KEYBOARD_INPUT_SIZE; }	// ↓
	else						{ fMoveInput.z =  0.0f; }					// 入力無し
	// 左右
	if		(IsKeyPress('D'))	{ fMoveInput.x =  KEYBOARD_INPUT_SIZE; }	// →
	else if (IsKeyPress('A'))	{ fMoveInput.x = -KEYBOARD_INPUT_SIZE; }	// ←
	else						{ fMoveInput.x =  0.0f; }					// 入力無し


	MoveSizeInputSet(fMoveInput);	// 入力値から移動量と向きをセット

	// 座標を移動
	m_Transform.fPos.x += m_fMove.x;
	m_Transform.fPos.z += m_fMove.z;

	

}

/* ========================================
   コントローラ用入力移動関数
   ----------------------------------------
   内容：コントローラ入力の移動処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
void CPlayer::MoveController()
{

	TPos3d<float> fMoveInput;	// スティックの入力値を入れる変数

	// コントローラーの左スティックの傾きを取得
	fMoveInput.x = IsStickLeft().x;
	fMoveInput.z = IsStickLeft().y * -1;	// 上下逆(↑が－1)

	MoveSizeInputSet(fMoveInput);	// 入力値から移動量と向きをセット

	// 座標を移動
	m_Transform.fPos.x += m_fMove.x;
	m_Transform.fPos.z += m_fMove.z;


}

/* ========================================
   移動量インプットセット関数
   ----------------------------------------
   内容：入力値から移動量と向きをセットする
   ----------------------------------------
   引数1：入力値(xとzを使用する)
   ----------------------------------------
   戻値：なし
======================================== */
void CPlayer::MoveSizeInputSet(TPos3d<float> fInput)
{
	// キー入力がある場合
	if (fInput.z != 0 || fInput.x != 0)
	{
		float moveRad = atan2(fInput.z, fInput.x);	// 移動入力した方向の角度を求める

		// 角度方向に移動する移動量をセット
		m_fMove.x = cosf(moveRad) * PLAYER_MOVE_SPEED;
		m_fMove.z = sinf(moveRad) * PLAYER_MOVE_SPEED;

		// 方向セット
		m_Transform.fRadian.y =
			atan2(fInput.z * -1, fInput.x)			// DirectXと三角関数で回転方向が逆なので調整
			+ DirectX::XMConvertToRadians(90.0f);	// DirectXと三角関数で0度の位置が90度ずれている(↑が0)ので調整
	}
	// キー入力がない場合
	else
	{
		// 移動しない
		m_fMove.z = 0.0f;
		m_fMove.x = 0.0f;
	}
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
   プレイヤー座標ポインタ取得関数
   ----------------------------------------
   内容：プレイヤーの座標のポインタの取得する関数(カメラに使用する)
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：座標ポインタアドレス
======================================== */
TPos3d<float>* CPlayer::GetPosAddress()
{
	return &m_Transform.fPos;
}

/* ========================================
   ハンマーポインタ取得関数
   ----------------------------------------
   内容：プレイヤーのハンマーポインタを取得する関数
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：ハンマーポインタ
======================================== */
CHammer* CPlayer::GetHammerPtr()
{ 
	return m_pHammer; 
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
   プレイヤーHP取得関数
   ----------------------------------------
   内容：プレイヤーのHPを取得
   ----------------------------------------
   引数：無し
   ----------------------------------------
   戻値：無し
======================================== */
int* CPlayer::GetHpPtr()
{
	return &m_nHp;
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
	m_pHammer->SetCamera(m_pCamera);
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
bool CPlayer::GetAttackFlg()
{
	return m_bAttackFlg;
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

/* ========================================
   プレイヤー点滅関数
   ----------------------------------------
   内容：プレイヤーがダメージを受けたら点滅する
   ----------------------------------------
   引数：無し
   ----------------------------------------
   戻値：無し
======================================== */
void CPlayer::SE_Move()
{
	m_nMoveCnt++;	//カウントを増やす

	//移動量が縦横どちらも0の時はカウントをリセット
	if (m_fMove.x == 0.0f && m_fMove.z == 0.0f)	
	{
		m_nMoveCnt = 0;
	}

	//カウントが一定以上になればSEを発生してカウントをリセット
	if (SE_RUN_INTERVAL <= m_nMoveCnt)	
	{
		m_pSERunSpeaker = CSound::PlaySound(m_pSERun);
		m_pSERunSpeaker->SetVolume(SE_RUN_VOLUME);
		m_nMoveCnt = 0;
	}
}

/* ========================================
   プレイヤー用SE読み込み関数
   ----------------------------------------
   内容：プレイヤー用のSEのファイルを読み込む
   ----------------------------------------
   引数：無し
   ----------------------------------------
   戻値：無し
======================================== */
void CPlayer::LoadSound()
{
	m_pSEDamaged = CSound::LoadSound("Assets/Sound/SE/PlayerDamage.mp3");	//SEの読み込み
	m_pSESwingHammer = CSound::LoadSound("Assets/Sound/SE/Swing.mp3");		//SEの読み込み
	m_pSERun = CSound::LoadSound("Assets/Sound/SE/Run.mp3");				//SEの読み込み
}

/* ========================================
   プレイヤー回復関数
   ----------------------------------------
   内容：プレイヤーのHPを回復する
   ----------------------------------------
   引数：無し
   ----------------------------------------
   戻値：無し
======================================== */
void CPlayer::Healing()
{
	if (m_nHp == PLAYER_HP) { return; }
	m_nHp += HEAL_NUM;
}
