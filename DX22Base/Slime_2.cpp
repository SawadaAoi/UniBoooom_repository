/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	スライムサイズ2用cpp
	------------------------------------
	Slime_2.cpp
	------------------------------------
	作成者	山下凌佑

	変更履歴
	・2023/11/08 作成 yamashita
	・2023/11/08 大きさの定数を定義	yamashita
	・2023/11/08 スライムの移動速度を大きさごとに変更する関数を作成	yamashita
	・2023/11/08 スライムの移動速度を大きさごとに変更する関数を作成	yamashita
	・2023/11/08 コンストラクタでレベルごとのパラメータをセット	yamashita
	・2023/11/11 parameter用ヘッダ追加 suzumura
	・2023/11/14 Baseからモデル、シェーダの読み込みを移動 Suzumura
	・2023/11/14 SphereInfoの変更に対応 takagi
	・2023/11/15 スライムのモデルと頂点シェーダーをmanagerから受け取るように変更 yamashita
	・2023/11/28 影の大きさを設定する変数追加 nieda
	・2023/12/01 タックルの挙動を追加 yamashita
	・2023/12/07 ゲームパラメータから一部定数移動 takagi
	・2024/1/26  アニメーションの実装 Yamashita
	・2024/1/26  タックル中に叩くとタックルがまた再開される不具合を修正 Yamashita
	・2024/01/29 アニメーションの追加 yamashita
	・2024/02/09 UsingCamera使用 takagi
	・2024/02/13 カメラ削除 takagi

========================================== */

// =============== インクルード ===================
#include "Slime_2.h"
#include "GameParameter.h"	//定数定義用ヘッダー
#include "UsingCamera.h"	//カメラ使用

// =============== 定数定義 =======================
const int	LEVEL2_ATTACK = 1;						// 攻撃力
#if MODE_GAME_PARAMETER
#else
const float LEVEL2_SCALE = 2.0f;
const float LEVEL2_SPEED = ENEMY_MOVE_SPEED * 0.95;
#endif
const float LEVEL_2_SHADOW_SCALE = 2.5f;	// スライム＿レベル２の影の大きさ

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：コンストラクタ
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
CSlime_2::CSlime_2()
	: m_AtcMoveType(ATTACK_NONE)
	, m_nChargeCnt(0)
	, m_nTackleCnt(0)
	, m_nAtkInterval(0)
	, tackleDirection{0.0f,0.0f,0.0f,0.0f}
{
	m_Transform.fScale = { LEVEL2_SCALE,LEVEL2_SCALE ,LEVEL2_SCALE };
	m_Sphere.fRadius *= LEVEL2_SCALE;
	m_eSlimeSize = E_SLIME_LEVEL::LEVEL_2;
	SetNormalSpeed();
	m_nAttack = LEVEL2_ATTACK;
	m_fScaleShadow = LEVEL_2_SHADOW_SCALE;	// 影の大きさを設定
}

/* ========================================
	コンストラクタ関数(座標指定)
	-------------------------------------
	内容：コンストラクタ
	-------------------------------------
	引数1：生成する座標
	引数2：頂点シェーダーのポインタ
	引数3：モデルのポインタ
	-------------------------------------
	戻値：無し
=========================================== */
CSlime_2::CSlime_2(TPos3d<float> pos, AnimeModel* pModel)
	: CSlime_2()
{
	m_Transform.fPos = pos;			// 初期座標を指定
	m_pModel = pModel;
	m_eCurAnime = MOTION_LEVEL2_MOVE;
	m_pModel->Play(m_eCurAnime,true);
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
CSlime_2::~CSlime_2()
{
}

/* ========================================
	更新処理関数
	-------------------------------------
	内容：更新処理
	-------------------------------------
	引数1：プレイヤーのtransform
	-------------------------------------
	戻値：無し
=========================================== */
void CSlime_2::Update(tagTransform3d playerTransform, float fSlimeMoveSpeed)
{
	m_PlayerTran = playerTransform;
	m_fAnimeTime += ADD_ANIME * 0.6f;		// アニメーションを進行

	if (!m_bHitMove)	//敵が通常の移動状態の時
	{
		if (!m_bMvStpFlg  && m_nMvStpCnt == 0)	//逃げるフラグがoffなら
		{
			NormalMove();	//通常移動
		}
		else
		{
			MoveStop();	//爆発から逃げる
		}
	}
	else
	{
		// 吹き飛びアニメーション再生
		if (m_eCurAnime != (int)MOTION_LEVEL2_HIT)
		{
			m_eCurAnime = (int)MOTION_LEVEL2_HIT;
			m_fAnimeTime = 0.0f;	// アニメーションタイムのリセット
		}

		//敵の吹き飛び移動
		HitMove();

		// タックルを中止して変数を初期化
		m_AtcMoveType = ATTACK_NONE;
		m_nChargeCnt = 0;
		m_nTackleCnt = 0;
	}

	// -- 座標更新
	m_Transform.fPos.x += m_move.x * fSlimeMoveSpeed;
	m_Transform.fPos.z += m_move.z * fSlimeMoveSpeed;
}

/* ========================================
	描画処理関数
	-------------------------------------
	内容：描画処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：無し
=========================================== */
void CSlime_2::Draw()
{
	//行列状態を取得してセット
	DirectX::XMFLOAT4X4 world;
	DirectX::XMStoreFloat4x4(&world, XMMatrixTranspose(
		DirectX::XMMatrixScaling(m_Transform.fScale.x, m_Transform.fScale.y, m_Transform.fScale.z) *
		DirectX::XMMatrixRotationY(m_Transform.fRadian.y + DirectX::g_XMPi[0]) *
		//DirectX::XMMatrixRotationY(m_Transform.fRadian.x + DirectX::XMConvertToRadians(20.0f)) *
		DirectX::XMMatrixTranslation(m_Transform.fPos.x, m_Transform.fPos.y, m_Transform.fPos.z)));


	DirectX::XMFLOAT4X4 mat[3] = {
	world,
	CUsingCamera::GetThis().GetCamera()->GetViewMatrix(),
	CUsingCamera::GetThis().GetCamera()->GetProjectionMatrix()
	};
	ShaderList::SetWVP(mat);

	// 複数体を共通のモデルで扱っているため描画のタイミングでモーションの種類と時間をセットする
	m_pModel->Play(m_eCurAnime, true);
	m_pModel->SetAnimationTime(m_eCurAnime, m_fAnimeTime);	// アニメーションタイムをセット
	// アニメーションタイムをセットしてから動かさないと反映されないため少しだけ進める
	m_pModel->Step(0.00000001f);

	// レンダーターゲット、深度バッファの設定
	RenderTarget* pRTV = GetDefaultRTV();	//デフォルトで使用しているRenderTargetViewの取得
	DepthStencil* pDSV = GetDefaultDSV();	//デフォルトで使用しているDepthStencilViewの取得
	SetRenderTargets(1, &pRTV, pDSV);		//DSVがnullだと2D表示になる

	//-- モデル表示
	if (m_pModel) {
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
		//m_pModel->DrawBone();
	}

	//-- 影の描画
	m_pShadow->Draw(m_Transform, m_fScaleShadow);
}

/* ========================================
	通常移動関数
	----------------------------------------
	内容：プレイヤーを追跡する移動を行う
	----------------------------------------
	引数1：プレイヤー当たり判定(Sphere)
	----------------------------------------
	戻値：なし
======================================== */
void CSlime_2::NormalMove()
{

	TPos3d<float> playerPos = m_PlayerTran.fPos;

	// 敵からエネミーの距離、角度を計算
	float distancePlayer = m_Transform.fPos.Distance(playerPos);

	// プレイヤーと距離が一定以内だったら
	if (distancePlayer < MOVE_DISTANCE_PLAYER)
	{
		if (m_nAtkInterval > LEVEL2_ATTACK_INTERVAL && m_AtcMoveType == ATTACK_NONE)
		{
			m_AtcMoveType = ATTACK_CHARGE;
			m_nAtkInterval = 0;

			// アニメーションを「攻撃」に変更
			if (m_eCurAnime != (int)MOTION_LEVEL2_ATTACK)
			{
				m_eCurAnime = (int)MOTION_LEVEL2_ATTACK;
				m_fAnimeTime = 0.0f;	//アニメーションタイムのリセット
			}

			return;
		}
	}

	//状態による分岐処理
	switch (m_AtcMoveType)
	{
	case(ATTACK_NONE):	//通常状態の時
		m_nAtkInterval++;
		CSlimeBase::NormalMove();

		// 現在のアニメーションが「移動」以外だったら移動モーションに変更
		if (m_eCurAnime != (int)MOTION_LEVEL2_MOVE)
		{
			m_eCurAnime = (int)MOTION_LEVEL2_MOVE;
			m_fAnimeTime = 0.0f;	//アニメーションタイムのリセット
		}

		return;
	case (ATTACK_CHARGE):
		if (m_nChargeCnt > LEVEL2_ATTACK_CHARGE_CNT)
		{	//チャージの時間を超えていたらタックル状態に移行する
			m_AtcMoveType = ATTACK_TACKLE;
			m_nChargeCnt = 0;

		}
		else 
		{ //まだだったらカウントを溜める
			m_nChargeCnt++; 
			CSlimeBase::NormalMove();
		}	

		//タックルの角度を確定
		// 敵からプレイヤーへのベクトル
		DirectX::XMFLOAT3 directionVector;
		directionVector.x = m_Transform.fPos.x - playerPos.x;
		directionVector.y = m_Transform.fPos.y - playerPos.y;
		directionVector.z = m_Transform.fPos.z - playerPos.z;
		
		// ベクトルを正規化して方向ベクトルを得る
		tackleDirection = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&directionVector));
		// 方向ベクトルから回転行列を計算
		m_Transform.fRadian.y = (atan2(-tackleDirection.m128_f32[0], -tackleDirection.m128_f32[2]));

		//移動を0に
		m_move = TTriType<float>(0.0f, 0.0f, 0.0f);

		return;
	case (ATTACK_TACKLE):
		if (m_nTackleCnt < LEVEL2_ATTACK_TACKLE_CNT)
		{	//タックル時間に満たないならタックル継続
			m_nTackleCnt++;
			m_move.x = (sin(m_Transform.fRadian.y)) * LEVEL2_TACKLE_SPEED;
			m_move.z = (cos(m_Transform.fRadian.y)) * LEVEL2_TACKLE_SPEED;

			return;
		}
		else //タックル時間を超えていればタックル終了
		{
			m_AtcMoveType = ATTACK_NONE;
			m_nTackleCnt = 0;
			CSlimeBase::NormalMove();

			// 移動アニメーションに変更
			m_eCurAnime = (int)MOTION_LEVEL2_MOVE;
			m_fAnimeTime = 0.0f;	//アニメーションタイムのリセット

		}
		break;
	}

	//上記のどのifにも当てはまらない場合ランダム移動
	RandomMove();

	// 現在のアニメーションが「移動」以外だったら移動モーションに変更
	if (m_eCurAnime != (int)MOTION_LEVEL2_MOVE)
	{
		m_eCurAnime = (int)MOTION_LEVEL2_MOVE;
		m_fAnimeTime = 0.0f;	//アニメーションタイムのリセット
	}
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
void CSlime_2::SetNormalSpeed()
{
	m_fSpeed = LEVEL2_SPEED;	//移動速度に定数をセット
}



