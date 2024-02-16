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
	・2023/11/27 影の描画を追加 nieda
	・2023/11/27 Update内ハンマー振り間隔処理追加 Tei
	・2023/11/27 Update内ハンマー振り間隔処理追加 Tei
	・2023/11/28 ダメージ処理に受けるダメージ量を追加 Sawada
	・2023/11/28 回復処理を追加 yamashita
	・2023/11/28 ダメージ処理に受けるダメージ量を追加 Sawada
	・2023/11/28 回復処理を追加 yamashita
	・2023/11/29 ハンマーのインターバル追加 yamamoto
	・2023/12/03 カメラの更新を担うため、ポインタのconstを仕方なく除去 takagi
	・2023/12/07 ゲームパラメータから一部定数移動 takagi
	・2023/12/14 プレイヤーのアニメーション実装 yamashita
	・2023/12/14 SEの変数を整理 yamashita
	・2023/12/15 SEを外から再生できるように変更 yamashita
	・2023/01/25 待機モーションを変更 takagi
	・2024/01/26 警告SE追加 suzumura
	・2024/01/28 死亡モーション追加 Sawada
	・2024/01/28 プレイヤーを傾けてカメラからよく見えるように変更 Yamashita
	・2024/01/30 プレイヤー移動エフェクト用処理追加 Tei
	・2024/02/02 汗エフェクト処理追加 Tei
	・2024/02/08 汗エフェクト処理修正&&ハンマーの振る速度もついでに修正 sawada
	・2024/02/09 カメラ更新除去・UsingCamera使用 takagi

======================================== */

// =============== インクルード ===================
#include "Player.h"
#include "Input.h"
#include "Sphere.h"
#include "GameParameter.h"		//定数定義用ヘッダー
#include "ShaderList.h"
#include "ModelManager.h"
#include "UsingCamera.h"	//カメラ使用

// =============== 定数定義 =======================
const float KEYBOARD_INPUT_SIZE = 1.0f;						// キーボードの入力値の大きさ
#if MODE_GAME_PARAMETER
#else
const float PLAYER_MOVE_SPEED = 0.1f;			//プレイヤーの移動量
const int	PLAYER_HP = 5;
const float PLAYER_RADIUS = 0.3f;			// プレイヤーの当たり判定の大きさ
const float PLAYER_SIZE = 1.0f;			// プレイヤーの大きさ
const int	NO_DAMAGE_TIME = 3 * 60;		//プレイヤーの無敵時間
const int	DAMAGE_FLASH_FRAME = 0.1f * 60;	// プレイヤーのダメージ点滅の切り替え間隔
const float PLAYER_ROTATE_X_NORMAL = DirectX::XMConvertToRadians(30.0f);	// プレイヤーの傾き
#endif
const int	HEAL_NUM = 2;									// プレイヤーの回復量
const float HAMMER_INTERVAL_TIME = 0.0f * 60;				// ハンマー振り間隔
const float PLAYER_SHADOW_SCALE = 2.5f;						// プレイヤーの影の大きさ
const int	SE_RUN_INTERVAL = static_cast<int>(0.4f * 60);	// プレイヤーの移動によるSE発生の間隔
const float	SE_RUN_VOLUME = 0.3f;							// 移動によるSEの音量
const float PLAYER_MOVE_ANIME_SPEED = 1.2f;					// プレイヤーの移動アニメーション再生速度
const float PLAYER_SWING_ANIME_SPEED = 5.0f;				// プレイヤーの移動アニメーション再生速度
const float	ADD_ANIM_FRAME = 1.0f / 60.0f;					
const int   PLAYER_WARNING_HP = 1;							//瀕死の警告を行うプレイヤー残りHP

const int	SWING_FAST_INTERVAL = 0.1f * 60;				// ハンマーを振る速度を早くする間隔

const int	WALK_EFFECT_INTERVAL = 0.2f * 60;				// 歩くエフェクトの出現間隔
const int	SWEAT_EFFECT_INTERVAL = 0.7f * 60;				// 汗エフェクトの出現間隔
const float	SWEAT_EFFECT_DISP_SPEED = 0.5f;					// 汗エフェクトの表示するハンマーのスピード(これ以下の場合に表示)
const int	DIE_AFTER_INTERVAL = int(2.0f * 60);			// 死亡してからGameOverテキストが出るまでの猶予時間
const int	CHARGE_HAMMER_CNT = 60;							// チャージが完了するまでの時間
const TTriType<float> CHARGING_EFFECT_SIZE = {2.0f,2.0f,2.0f};// エフェクトのサイズ
const TTriType<float> CHARGED_EFFECT_SIZE = {3.0f,3.0f,3.0f};// エフェクトのサイズ
const float CHARGE_EFFECT_SPEED = 1.0f;						// チャージエフェクトの再生速度
const int DISP_CHARGE_EFC_CNT = 15;							// チャージエフェクトの見え始めるカウント

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
	, m_nHp(PLAYER_HP)		// プレイヤーのHPを決定
	, m_bDieFlg(false)
	, m_nSafeTimeCnt(0)
	, m_bSafeTimeFlg(false)
	, m_DrawFlg(true)
	, m_FlashCnt(0)
	, m_pSE{ nullptr,nullptr ,nullptr }
	, m_pSESpeaker{ nullptr ,nullptr, nullptr }
	, m_nWalkSECnt(0)
	, m_bHumInvFlg(false)
	, m_fHumInvCnt(0.0f)
	, m_pWaitFrameCnt(nullptr)
	, m_bDieInvFlg(false)
	, m_fDieInvCnt(0.0f)
	, m_pWalkEffectMng(nullptr)
	, m_nWalkEffeCnt(0)
	, m_nSweatEffeCnt(0)
	, m_nSwingFastCnt(0)
	, m_fRotate_x(PLAYER_ROTATE_X_NORMAL)
	, m_fChargeCnt(0.0f)
	, m_ChargeState(PLAYER_CHARGE_NONE)
{
	m_pHammer = new CHammer();			// Hammerクラスをインスタンス

	m_Sphere.fRadius = PLAYER_RADIUS;	// 当たり判定用の球体の半径
	m_Transform.fScale = PLAYER_SIZE;
	LoadSound();						//サウンドファイル読み込み

	//プレイヤーのモデル読み込み
	m_pModel = GetModelMng.GetModelPtr(MODEL_PLAYER);
	m_pModel->Play(MOTION_PLAYER_MOVE,true);
	m_pModel->Step(0.0f);	// Tポーズから立ち状態に移行

	//LoadAnime();	//アニメーションの読み込み
	m_pShadow = new CShadow();

	// エフェクトマネージャーを作成
	m_pWalkEffectMng = new CWalkEffectManager();
	m_pSweatEffectMng = new CSweatEffectManager();

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
	SAFE_DELETE(m_pWaitFrameCnt);
	SAFE_DELETE(m_pSweatEffectMng);
	SAFE_DELETE(m_pWalkEffectMng);
	SAFE_DELETE(m_pShadow);
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
	// 死亡した場合
	if (m_bDieInvFlg)
	{
		m_bAttackFlg	= false;				// 攻撃中フラグをオフにする
		m_DrawFlg		= true;					// 点滅を解除
		m_bSafeTimeFlg	= false;				// 無敵を解除

		m_fDieInvCnt++;
		// 死亡猶予時間が経過しているか
		if (DIE_AFTER_INTERVAL <= m_fDieInvCnt)
		{
			m_bDieFlg = true;	// 死亡判定をオン
		}
	}
	// ハンマー攻撃中
	else if (m_bAttackFlg)
	{
		// ハンマーの攻撃が終了したら
		if (m_pHammer->Update() == false)
		{
			m_pHammer->SwingSpeedSlow();	// ハンマーのスイングスピードを遅くする
			m_pModel->SetAnimationSpeed(MOTION_PLAYER_SWING, m_pHammer->GetSwingSpeed() * SWING_ANIM_ADJUST);	// アニメの速さを設定
			m_bAttackFlg = false;			// 攻撃中フラグをオフにする
			m_bHumInvFlg = true;			// ハンマー振り間隔フラグオン
		}
	}
	// ハンマー攻撃以外
	else
	{
		CheckCharge();	// チャージカウントを参照してチャージ状態を判定
		// ハンマースイングのアニメーションが終了していたらチャージ状態をNONEに変更
		if (!m_pModel->IsPlay(MOTION_PLAYER_SWING))
		{
			m_ChargeState = PLAYER_CHARGE_NONE;
		}

		// チャージ状態がNONEでスイングアニメーションが終了しているとき
		if (!m_ChargeState == PLAYER_CHARGE_NONE && m_pModel->IsPlay(MOTION_PLAYER_SWING))
		{
			m_fChargeCnt = 0;
			m_ChargeState = PLAYER_CHARGING;
		}

		// ハンマー間隔時間フラグがオンの時
		if (m_bHumInvFlg)
		{
			m_fHumInvCnt++;				// ハンマー間隔時間カウント加算
			if (m_fHumInvCnt >= HAMMER_INTERVAL_TIME)
			{
				m_bHumInvFlg = false;		// ハンマー間隔時間フラグオン
				m_fHumInvCnt = 0.0f;		// ハンマー間隔時間リセット
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

		// スペースキーもしくはコントローラのBボタンに対しての押し続け && ハンマー間隔時間経過済み
		if ((IsKeyPress(VK_SPACE) || IsKeyPressController(BUTTON_B)) && !m_bHumInvFlg
					&& !m_ChargeState == PLAYER_CHARGING)
		{	
			SAFE_DELETE(m_pWaitFrameCnt);	// カウンタ削除

			// カウントが0ならアニメーションをリセットして再生
			if (m_fChargeCnt == 0)
			{
				m_pModel->Play(MOTION_PLAYER_CHARGE, true, 1.0);		// アニメーションの再生
				m_pModel->SetAnimationTime(MOTION_PLAYER_CHARGE, 0.0f);	// アニメーションタイムをスタート位置にセット
			}


			m_fChargeCnt++;	// チャージカウントを増加

			if (m_fChargeCnt == DISP_CHARGE_EFC_CNT)
			{
				// エフェクトの再生
				EffectStart();
			}

			// カウントがマックスになった時のSE再生
			if (m_fChargeCnt == CHARGE_HAMMER_CNT)
			{
				PlaySE(SE_CHARGED);
			}
		}
		else if ((IsKeyRelease(VK_SPACE) || IsKeyReleaseController(BUTTON_B)) && !m_bHumInvFlg && !m_pModel->IsPlay(MOTION_PLAYER_SWING))
		{	// スペースキーもしくはコントローラのBボタンに対しての離した時 && ハンマー間隔時間経過済み

			SAFE_DELETE(m_pWaitFrameCnt);	// カウンタ削除

			m_pModel->Play(MOTION_PLAYER_SWING, false, m_pHammer->GetSwingSpeed() * SWING_ANIM_ADJUST);	// アニメーションの再生
			m_pModel->SetAnimationTime(MOTION_PLAYER_SWING, 0.0f);				// アニメーションタイムをスタート位置にセット


			m_pHammer->AttackStart(m_Transform.fPos, m_Transform.fRadian.y);	// ハンマー攻撃開始
			m_bAttackFlg = true;	// 攻撃フラグを有効にする

			LibEffekseer::GetManager()->StopEffect(m_chgEfcHandle);

			//SEの再生
			PlaySE(SE_SWING);
		}
		else
		{
			m_fChargeCnt = 0;
			m_nSwingFastCnt++;
			if (SWING_FAST_INTERVAL < m_nSwingFastCnt)
			{
				// 攻撃ボタンを押してない時はハンマーのスイングスピードを通常に戻していく
				m_pHammer->SwingSpeedFast();
				m_pModel->SetAnimationSpeed(
					MOTION_PLAYER_SWING,
					m_pHammer->GetSwingSpeed() * SWING_ANIM_ADJUST);	// アニメの速さを設定
				m_nSwingFastCnt = 0;
			}
		}
	}

	// 無敵状態になっている場合
	if (m_bSafeTimeFlg)
	{
		m_nSafeTimeCnt++;					// 毎フレームでカウントを追加
		DamageAnimation();					// プレイヤー点滅関数呼び出す

		// カウントが一定時間を超えたら
		if (m_nSafeTimeCnt >= NO_DAMAGE_TIME)
		{
			m_DrawFlg = true;				// 点滅を解除
			m_bSafeTimeFlg = false;			// 無敵を解除
		}

	}

	//移動によるSEとアニメーションの処理
	MoveCheck();

	//アニメーションの更新
	if (!m_pWaitFrameCnt)	//待機時間中は止める
	{
		m_pModel->Step(ADD_ANIM_FRAME);
	}
	
	DisplaySweatEffect();			// 汗エフェクト作成

	UpdateEffect();	// エふぇくtの更新

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
		//-- モデル表示
		if (m_pModel) {
			// レンダーターゲット、深度バッファの設定
			RenderTarget* pRTV = GetDefaultRTV();	//デフォルトで使用しているRenderTargetViewの取得
			DepthStencil* pDSV = GetDefaultDSV();	//デフォルトで使用しているDepthStencilViewの取得
			SetRenderTargets(1, &pRTV, pDSV);		//DSVがnullだと2D表示になる

			//m_pModel->Draw();
		}

		DirectX::XMFLOAT4X4 mat[3];

		//拡縮、回転、移動(Y軸回転を先にしたかったのでSRTは使わない)
		DirectX::XMStoreFloat4x4(&mat[0], 
			DirectX::XMMatrixTranspose(
				DirectX::XMMatrixScaling(m_Transform.fScale.x, m_Transform.fScale.y, m_Transform.fScale.z)		// 大きさ
				* DirectX::XMMatrixRotationY(m_Transform.fRadian.y)	// Y角度
				* DirectX::XMMatrixRotationX(m_fRotate_x)			// X角度
				* DirectX::XMMatrixRotationZ(m_Transform.fRadian.z)	// Z角度
				* DirectX::XMMatrixTranslation(m_Transform.fPos.x, m_Transform.fPos.y, m_Transform.fPos.z)));	// 座標
		mat[1] = CUsingCamera::GetThis().GetCamera()->GetViewMatrix();
		mat[2] = CUsingCamera::GetThis().GetCamera()->GetProjectionMatrix();


		ShaderList::SetWVP(mat);

		//アニメーション対応したプレイヤーの描画
		m_pModel->Draw(nullptr, [this](int index)
		{
			const AnimeModel::Mesh* pMesh = m_pModel->GetMesh(index);
			const AnimeModel::Material* pMaterial = m_pModel->GetMaterial(pMesh->materialID);
			ShaderList::SetMaterial(*pMaterial);

			DirectX::XMFLOAT4X4 bones[200];
			for (int i = 0; i < pMesh->bones.size() && i < 200; ++i)
			{
				// この計算はゲームつくろー「スキンメッシュの仕組み」が参考になる
				DirectX::XMStoreFloat4x4(&bones[i], DirectX::XMMatrixTranspose(
					pMesh->bones[i].invOffset *
					m_pModel->GetBone(pMesh->bones[i].index)
				));
			}
			ShaderList::SetBones(bones);
		});
#ifdef _DEBUG
		//アニメーションの動きが確認できるボーンの描画(中心から動かない)
		//m_pModel->DrawBone();	
#endif
	}

	//=====アニメーションの調整用に一応残しておく=====
	if (m_bAttackFlg)
	{
		//m_pHammer->Draw();		// ハンマーの描画
	}

	m_pShadow->Draw(m_Transform, PLAYER_SHADOW_SCALE);	// 影の描画

	m_nWalkEffeCnt++;
	m_pWalkEffectMng->Draw();
	m_pSweatEffectMng->Draw();
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
	if (m_bDieInvFlg) return;	// 死亡したあとは処理しない

	m_nHp -= DmgNum;
	m_bSafeTimeFlg = true;	//プレイヤーを一定時間、無敵にする
	m_nSafeTimeCnt = 0;	//プレイヤー無敵時間のカウントを0に戻す
	//=== SEの再生 =====
	PlaySE(SE_DAMAGED);

	// プレイヤーが瀕死になったら警告音を流す
	if(m_nHp == PLAYER_WARNING_HP) PlaySE(SE_WARNING);

	if (m_nHp <= 0)
	{
		m_bDieInvFlg = true;
		m_fRotate_x = PLAYER_ROTATE_X_DIE;			// プレイヤーの傾きをセット(地面に埋まらないように)
		m_pModel->Play(MOTION_PLAYER_DIE,false);	// アニメーションの再生

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
	if (IsKeyPress('W')) { fMoveInput.z = KEYBOARD_INPUT_SIZE; }		// ↑	
	else if (IsKeyPress('S')) { fMoveInput.z = -KEYBOARD_INPUT_SIZE; }	// ↓
	else { fMoveInput.z = 0.0f; }										// 入力無し

	// 左右
	if (IsKeyPress('D')) { fMoveInput.x = KEYBOARD_INPUT_SIZE; }		// →	
	else if (IsKeyPress('A')) { fMoveInput.x = -KEYBOARD_INPUT_SIZE; }	// ←
	else { fMoveInput.x = 0.0f; }										// 入力無し

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
			(atan2(fInput.z * -1, fInput.x)			// DirectXと三角関数で回転方向が逆なので調整
				- DirectX::XMConvertToRadians(90.0f));	// DirectXと三角関数で0度の位置が90度ずれている(↑が0)ので調整
		
		// プレイヤー移動煙エフェクト表示
		if (WALK_EFFECT_INTERVAL <= m_nWalkEffeCnt)
		{
			m_pWalkEffectMng->Create(m_Transform);	// プレイヤー移動エフェクト作成
			m_nWalkEffeCnt = 0;
		}
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
   汗エフェクト出現関数
   ----------------------------------------
   内容：ハンマーの速度によって汗エフェクトを表示させる
   ----------------------------------------
   引数1：なし
   ----------------------------------------
   戻値：なし
======================================== */
void CPlayer::DisplaySweatEffect()
{
	// 振る速度が一定以下になったら
	if (m_pHammer->GetSwingSpeed() < SWEAT_EFFECT_DISP_SPEED)
	{
		m_nSweatEffeCnt++;

		// 表示間隔が経過したか(GetSwingSpeedを掛けることで間隔が徐々に短くなるように)
		if (SWEAT_EFFECT_INTERVAL * m_pHammer->GetSwingSpeed() <= m_nSweatEffeCnt)
		{
			m_pSweatEffectMng->Create(m_Transform.fPos, m_Transform.fRadian);	// 汗エフェクト作成
			m_nSweatEffeCnt = 0;
		}
	}
	else
	{
		m_nSweatEffeCnt = 0;	// 振る速度が回復したらリセット
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
   無敵時間フラグ取得関数
   ----------------------------------------
   内容：プレイヤーが無敵状態かの確認
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：bool(true=無敵状態) 
======================================== */
bool CPlayer::GetSafeTime()
{
	return m_bSafeTimeFlg;
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
   プレイヤー死亡フラグ取得関数
   ----------------------------------------
   内容：プレイヤー死亡フラグを取得
   ----------------------------------------
   引数：無し
   ----------------------------------------
   戻値：true = 死亡 / false = 生存
======================================== */
bool CPlayer::GetDieFlg() const
{
	return m_bDieFlg;
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
   チャージハンマー取得関数
   ----------------------------------------
   内容：チャージ状態か取得する関数
   ----------------------------------------
   引数：無し
   ----------------------------------------
   戻値：チャージ状態
======================================== */
bool CPlayer::GetCharge()
{
	return m_bCharge;
}

void CPlayer::SetSweatEffectMng(CSweatEffectManager* pSweatefcMng)
{
	m_pSweatEffectMng = pSweatefcMng;
}

/* ========================================
   アニメーション読み込み関数
   ----------------------------------------
   内容：アニメーションを読み込む
   ----------------------------------------
   引数：無し
   ----------------------------------------
   戻値：無し
======================================== */
void CPlayer::LoadAnime()
{
	//for (int i = 0; i < MOTION_PLAYER_MAX; i++)
	//{
	//	//各アニメーションの読み込み
	//	m_Anime[i] = m_pModel->AddAnimation(m_sAnimeFile[i].c_str());
	//	//読み込みに失敗したらエラーメッセージ
	//	if (!m_pModel->GetAnimation(m_Anime[i]))
	//	{
	//		MessageBox(NULL, m_sAnimeFile[i].c_str(), "Error", MB_OK);	//ここでエラーメッセージ表示
	//	}
	//}
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
   プレイヤーが移動確認関数
   ----------------------------------------
   内容：プレイヤーが移動しているか確認して、それに応じた処理を行う
   ----------------------------------------
   引数：無し
   ----------------------------------------
   戻値：無し
======================================== */
void CPlayer::MoveCheck()
{
	if (m_bDieInvFlg) return;	// 死亡したあとは処理しない

	//移動量が縦横どちらも0の時はカウントをリセット(移動していない時)
	if (m_fMove.x == 0.0f && m_fMove.z == 0.0f)
	{
		// 待機中のアニメーションを再生してない、なおかつ攻撃中じゃない場合
		if (m_pModel->GetPlayNo() != MOTION_PLAYER_STOP
			&& !m_bAttackFlg && !m_pModel->IsPlay(MOTION_PLAYER_SWING)
			&& m_ChargeState == PLAYER_CHARGE_NONE)
		{
			// カウントダウン開始前の場合
			if (!m_pWaitFrameCnt)	// 値がnullptr
			{
				m_pWaitFrameCnt = new CFrameCnt(CNT_START_WAIT);	//カウントダウン開始
			}
			// カウントダウン開始済みの場合
			else
			{	
				m_pWaitFrameCnt->Count();	//カウントダウン中

			}
			// カウントダウン完了
			if (m_pWaitFrameCnt->IsFin())
			{
				SAFE_DELETE(m_pWaitFrameCnt);						// カウンタ削除
				m_pModel->Play(MOTION_PLAYER_STOP, false);	// 待機モーション開始
			}
		}
	}
	// 移動中の場合(待機モーション遷移前に移動を始めた)
	else
	{
		if (m_pWaitFrameCnt)
		{
			SAFE_DELETE(m_pWaitFrameCnt);	//カウンタ削除
		}

		m_nWalkSECnt++;	//カウントを増やす

		//　カウントが一定以上になればSEを発生してカウントをリセット
		if (SE_RUN_INTERVAL <= m_nWalkSECnt)
		{
			//SEの再生
			PlaySE(SE_RUN, SE_RUN_VOLUME);
			m_nWalkSECnt = 0;	//カウントをリセット
		}

		// 移動中のアニメーションを再生してない場合、なおかつ攻撃中じゃない場合
		if (m_pModel->GetPlayNo() != MOTION_PLAYER_MOVE && !m_pModel->IsPlay(MOTION_PLAYER_SWING)
			&& !m_pModel->IsPlay(MOTION_PLAYER_CHARGE))
		{	
			m_pModel->Play(MOTION_PLAYER_MOVE, true, PLAYER_MOVE_ANIME_SPEED);	// アニメーションを再生
		}

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
	//SEの読み込み
	for (int i = 0; i < SE_MAX; i++)
	{
		m_pSE[i] = CSound::LoadSound(m_sSEFile[i].c_str());
		if (!m_pSE[i])
		{
			MessageBox(NULL, m_sSEFile[i].c_str(), "Error", MB_OK);	//ここでエラーメッセージ表示
		}
	}
}

/* ========================================
	SEの読み込み関数
	----------------------------------------
	内容：SEの読み込み
	----------------------------------------
	引数1：SEの種類(enum)
	引数2：音量
	----------------------------------------
	戻値：なし
======================================== */
void CPlayer::PlaySE(SE se, float volume)
{
	m_pSESpeaker[se] = CSound::PlaySound(m_pSE[se]);	//SE再生
	m_pSESpeaker[se]->SetVolume(volume);				//音量の設定
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
	m_nHp += HEAL_NUM;
	if (m_nHp >= PLAYER_HP) { m_nHp = PLAYER_HP; }
	PlaySE(SE_HEAL);
}

/* ========================================
   チャージハンマー判定関数
   ----------------------------------------
   内容：チャージカウントを参照して判定する関数
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
void CPlayer::CheckCharge()
{
	// チャージ時間が一定以上か否か
	if (CHARGE_HAMMER_CNT > m_fChargeCnt)
	{	// チャージ時間が足りていない場合
		m_bCharge = false;
	}
	else
	{	// チャージが完了している場合
		m_bCharge = true;
		m_ChargeState = PLAYER_CHARGED;
	}
}

/* ========================================
	エフェクト表示開始関数
	-------------------------------------
	内容：エフェクトの表示を開始する
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CPlayer::EffectStart()
{
	m_chgEfcHandle = LibEffekseer::GetManager()->Play(m_chargeEfc, 	//エフェクトの開始
		m_Transform.fPos.x,
		m_Transform.fPos.y,
		m_Transform.fPos.z);

	LibEffekseer::GetManager()->SetScale(m_chgEfcHandle, 					//エフェクトのサイズを設定
		CHARGING_EFFECT_SIZE.x,
		CHARGING_EFFECT_SIZE.y,
		CHARGING_EFFECT_SIZE.z);

	LibEffekseer::GetManager()->SetSpeed(m_chgEfcHandle,					//エフェクトの再生速度を設定
		CHARGE_EFFECT_SPEED);
}

/* ========================================
	エフェクト更新関数
	-------------------------------------
	内容：エフェクトを更新する
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CPlayer::UpdateEffect()
{
	// チャージエフェクトの座標をセット
	LibEffekseer::GetManager()->SetLocation(m_chgEfcHandle,
		m_Transform.fPos.x,
		m_Transform.fPos.y,
		m_Transform.fPos.z);

	if (m_bCharge)
	{
		LibEffekseer::GetManager()->SetScale(m_chgEfcHandle, 	//エフェクトのサイズを設定
			CHARGED_EFFECT_SIZE.x,
			CHARGED_EFFECT_SIZE.y,
			CHARGED_EFFECT_SIZE.z);
	}
	else
	{
		LibEffekseer::GetManager()->SetScale(m_chgEfcHandle, 	//エフェクトのサイズを設定
			CHARGING_EFFECT_SIZE.x,
			CHARGING_EFFECT_SIZE.y,
			CHARGING_EFFECT_SIZE.z);
	}


	m_pWalkEffectMng->Update();						// 歩きの土煙エフェクトの更新
	m_pSweatEffectMng->Update(m_Transform.fPos);	// 汗エフェクトの更新

}

