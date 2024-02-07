/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	スライムサイズ3用cpp
	------------------------------------
	Slime_3.cpp
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
	・2023/11/16 引数付きコンストラクタの引数に頂点シェーダーとモデルのポインタを追加 山下凌佑
	・2023/11/28 影の大きさを設定する変数追加 nieda
	・2023/11/30 プレイヤーに見られていたら止まる処理を追加 yamashita
	・2023/12/07 ゲームパラメータから一部定数移動 takagi
	・2024/01/31 アニメーションの追加 yamashita

========================================== */

// =============== インクルード ===================
#include "Slime_3.h"
#include "GameParameter.h"		//定数定義用ヘッダー
#include "DirectWrite.h"
// =============== 定数定義 =======================
const int	LEVEL3_ATTACK = 1;						// 攻撃力
#if MODE_GAME_PARAMETER
#else
const float LEVEL3_SCALE = 3.0f;
const float LEVEL3_SPEED = ENEMY_MOVE_SPEED * 0.90;
const float LEVEL3_STOP_RANGE = DirectX::XMConvertToRadians(20.0f);	// スライムが止まる角度の範囲
#endif
const float LEVEL_3_SHADOW_SCALE = 3.5f;	// スライム＿レベル３の影の大きさ

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：コンストラクタ
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
CSlime_3::CSlime_3()
{
	m_Transform.fScale = { LEVEL3_SCALE,LEVEL3_SCALE ,LEVEL3_SCALE };
	m_Sphere.fRadius *= LEVEL3_SCALE;
	m_eSlimeSize = E_SLIME_LEVEL::LEVEL_3;
	SetNormalSpeed();
	m_nAttack = LEVEL3_ATTACK;
	m_fScaleShadow = LEVEL_3_SHADOW_SCALE;	// 影の大きさを設定
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
CSlime_3::CSlime_3(TPos3d<float> pos, AnimeModel* pModel)
	: CSlime_3()
{
	m_Transform.fPos = pos;			// 初期座標を指定
	m_pModel = pModel;
	// アニメーションのセット
	m_eCurAnime = (int)MOTION_LEVEL3_MOVE;	// 現在のアニメーションをセット
	m_pModel->Play(m_eCurAnime, true);
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
CSlime_3::~CSlime_3()
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
void CSlime_3::Update(tagTransform3d playerTransform, float fSlimeMoveSpeed)
{
	m_PlayerTran = playerTransform;
	m_fAnimeTime += ADD_ANIME * 0.6f;

	if (!m_bHitMove)	//敵が通常の移動状態の時
	{
		if (!m_bMvStpFlg  && m_nMvStpCnt == 0)	//逃げるフラグがoffなら
		{
			NormalMove();	//通常異動
		}
		else
		{
			MoveStop();	//爆発から逃げる
		}
	}
	else
	{
		//敵の吹き飛び移動
		HitMove();

		// 吹き飛び状態のアニメに遷移
		if (m_eCurAnime != MOTION_LEVEL3_HIT)
		{
			m_eCurAnime = MOTION_LEVEL3_HIT;
			m_fAnimeTime = 0.0f;
		}
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
void CSlime_3::Draw()
{
	if (!m_pCamera) { return; }

	//行列状態を取得してセット
	DirectX::XMFLOAT4X4 world;
	DirectX::XMStoreFloat4x4(&world, XMMatrixTranspose(
		DirectX::XMMatrixScaling(m_Transform.fScale.x, m_Transform.fScale.y, m_Transform.fScale.z) *
		DirectX::XMMatrixRotationY(m_Transform.fRadian.y) *
		DirectX::XMMatrixTranslation(m_Transform.fPos.x, m_Transform.fPos.y, m_Transform.fPos.z)));

	DirectX::XMFLOAT4X4 mat[3] = {
	world,
	m_pCamera->GetViewMatrix(),
	m_pCamera->GetProjectionMatrix()
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
	m_pShadow->Draw(m_Transform, m_fScaleShadow, m_pCamera);
}

/* ========================================
	通常移動関数
	----------------------------------------
	内容：プレイヤーを追跡する移動を行う
		  プレイヤーに見られていたら止まる
	----------------------------------------
	引数1：プレイヤーのtransform
	----------------------------------------
	戻値：なし
======================================== */
void CSlime_3::NormalMove()
{

	TPos3d<float> playerPos = m_PlayerTran.fPos;
	TTriType<float> playerRad = m_PlayerTran.fRadian;

	// 敵からエネミーの距離、角度を計算
	float distancePlayer = m_Transform.fPos.Distance(playerPos);

	// プレイヤーと距離が一定以内だったら
	if (distancePlayer < MOVE_DISTANCE_PLAYER)
	{
		//プレイヤーがスライムの方向を向いているか確認
	 	float PlayerToSlimeRad = m_PlayerTran.Angle(m_Transform);	//プレイヤーからスライムへの角度
		if (PlayerToSlimeRad < 0.0f) { PlayerToSlimeRad = PlayerToSlimeRad + (DirectX::g_XMTwoPi[0]); }			//角度を正の数に変換
		float adjustPlayerRad = playerRad.y + DirectX::XMConvertToRadians(90.0f);			//プレイヤーの見ている角度
		if(adjustPlayerRad < 0.0f){adjustPlayerRad = adjustPlayerRad + (DirectX::g_XMTwoPi[0]);}	//角度を正の数に変換
		float sumRad = PlayerToSlimeRad + adjustPlayerRad;
		//プレイヤーの向いている方向がスライムの止まる角度の中だったら
		float checkRad = (abs(sumRad - (DirectX::g_XMTwoPi[0]))) > DirectX::g_XMTwoPi[0] ?
			(abs(sumRad - (DirectX::g_XMTwoPi[0]))) - DirectX::g_XMTwoPi[0] :
			(abs(sumRad - (DirectX::g_XMTwoPi[0])));
		if (checkRad < LEVEL3_STOP_RANGE)
		{
			m_move = TTriType<float>(0.0f, 0.0f, 0.0f);	//移動量を0にする
			m_Transform.fRadian.y = -(m_Transform.Angle(m_PlayerTran) + DirectX::XMConvertToRadians(90.0f));	//角度をDirectX用に変更

			// 静止状態のアニメに遷移
			if (m_eCurAnime != MOTION_LEVEL3_STOP)
			{
				m_eCurAnime = MOTION_LEVEL3_STOP;
				m_fAnimeTime = 0.0f;
			}

			return;
		}
		else	//プレイヤーがスライムと別の方向を向いていたら
		{
			TPos3d<float> movePos;
			movePos = playerPos - m_Transform.fPos;	// プレイヤーへのベクトルを計算
			if (distancePlayer != 0)	//0除算回避
			{
				m_move.x = movePos.x / distancePlayer * m_fSpeed;
				m_move.z = movePos.z / distancePlayer * m_fSpeed;
			}
			// 敵からプレイヤーへのベクトル
			DirectX::XMFLOAT3 directionVector;
			directionVector.x = m_Transform.fPos.x - playerPos.x;
			directionVector.y = m_Transform.fPos.y - playerPos.y;
			directionVector.z = m_Transform.fPos.z - playerPos.z;

			// ベクトルを正規化して方向ベクトルを得る
			DirectX::XMVECTOR direction = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&directionVector));
			// 方向ベクトルから回転行列を計算
			m_Transform.fRadian.y = atan2(directionVector.x, directionVector.z);
		}
	}
	else	//索敵範囲外だったら
	{
		RandomMove();	// ランダム移動
	}

	// 移動状態のアニメに遷移
	if (m_eCurAnime != MOTION_LEVEL3_MOVE)
	{
		m_eCurAnime = MOTION_LEVEL3_MOVE;
		m_fAnimeTime = 0.0f;
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
void CSlime_3::SetNormalSpeed()
{
	m_fSpeed = LEVEL3_SPEED;	//移動速度に定数をセット
}


