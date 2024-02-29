/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	スライムサイズ4用cpp
	------------------------------------
	Slime_4.cpp
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
	・2024/01/31 アニメーションの追加 yamashita
	・2024/02/09 UsingCamera使用 takagi
	・2024/02/13 カメラ削除 takagi

========================================== */

// =============== インクルード ===================
#include "Slime_4.h"
#include "GameParameter.h"	//定数定義用ヘッダー
#include "UsingCamera.h"	//カメラ使用

// =============== 定数定義 =======================
#if MODE_GAME_PARAMETER
#else
const float LEVEL4_SCALE = 4.0f;
const float LEVEL4_SPEED = ENEMY_MOVE_SPEED * 0.85;
const int	LEVEL4_ATTACK = 2;	// 攻撃力
#endif
const float LEVEL_4_SHADOW_SCALE = 11.0f;	// スライム＿レベル４の影の大きさ

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：コンストラクタ
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
CSlime_4::CSlime_4()
{
	m_Transform.fScale = { LEVEL4_SCALE,LEVEL4_SCALE ,LEVEL4_SCALE };
	m_Sphere.fRadius *= LEVEL4_SCALE;
	m_eSlimeSize = E_SLIME_LEVEL::LEVEL_4;
	SetNormalSpeed();
	m_nAttack = LEVEL4_ATTACK;
	m_fScaleShadow = LEVEL_4_SHADOW_SCALE;	// 影の大きさを設定
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
CSlime_4::CSlime_4(TPos3d<float> pos, AnimeModel* pModel)
	: CSlime_4()
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
CSlime_4::~CSlime_4()
{
}

void CSlime_4::Update(tagTransform3d playerTransform, float fSlimeMoveSpeed)
{
	m_PlayerTran = playerTransform;
	m_fAnimeTime += ADD_ANIME;	//アニメーションの進行

	if (!m_bHitMove)	//敵が通常の移動状態の時
	{
		// 移動のアニメに遷移
		if (m_eCurAnime != MOTION_LEVEL4_MOVE)
		{
			m_eCurAnime = MOTION_LEVEL4_MOVE;
			m_fAnimeTime = 0.0f;
		}

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
		if (m_eCurAnime != MOTION_LEVEL4_HIT)
		{
			m_eCurAnime = MOTION_LEVEL4_HIT;
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
void CSlime_4::Draw()
{

	//-- 影の描画
	m_pShadow->Draw(m_Transform, m_fScaleShadow);

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
	m_pModel->Step(0.0f);

	// レンダーターゲット、深度バッファの設定
	RenderTarget* pRTV = GetDefaultRTV();	//デフォルトで使用しているRenderTargetViewの取得
	DepthStencil* pDSV = GetDefaultDSV();	//デフォルトで使用しているDepthStencilViewの取得
	SetRenderTargets(1, &pRTV, pDSV);		//DSVがnullだと2D表示になる

	//-- モデル表示(アニメーション対応ver)
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

}

void CSlime_4::NormalMove()
{
	TPos3d<float> playerPos = m_PlayerTran.fPos;

	// 敵からエネミーの距離、角度を計算
	float distancePlayer = m_Transform.fPos.Distance(playerPos);

	// プレイヤーと距離が一定以内だったら
	if (distancePlayer < 5)
	{
		// プレイヤーへの角度を取得
		float rad = atan2f(playerPos.x - m_Transform.fPos.x, playerPos.z - m_Transform.fPos.z);
		// プレイヤーと反対方向に移動
		m_move.x = -(sinf(rad)) * m_fSpeed;
		m_move.z = -(cosf(rad)) * m_fSpeed;
		m_Transform.fRadian.y = atan2f(m_move.x, m_move.z);
	}
	else
	{
		RandomMove();	// ランダム移動

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
void CSlime_4::SetNormalSpeed()
{
	m_fSpeed = LEVEL4_SPEED;	//移動速度に定数をセット
}



