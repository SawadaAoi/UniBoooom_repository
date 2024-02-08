/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	スライムサイズ1用cpp
	------------------------------------
	Slime_1.cpp
	------------------------------------
	作成者	澤田

	変更履歴
	・2023/11/08 作成 sawada
	・2023/11/08 大きさの定数を定義	yamashita
	・2023/11/08 スライムの移動速度を大きさごとに変更する関数を作成	yamashita
	・2023/11/08 スライムの移動速度を大きさごとに変更する関数を作成	yamashita
	・2023/11/08 コンストラクタでレベルごとのパラメータをセット	yamashita
	・2023/11/11 define用ヘッダ追加 suzumura
	・2023/11/14 Baseからモデル、シェーダの読み込みを移動 Suzumura
	・2023/11/14 SphereInfoの変更に対応 takagi
	・2023/11/15 スライムのモデルと頂点シェーダーをmanagerから受け取るように変更 yamashita
	・2023/11/28 影の大きさを設定する変数追加 nieda
	・2023/12/07 ゲームパラメータから一部定数移動 takagi
	・2024/1/26  アニメーションの実装 Yamashita

========================================== */

// =============== インクルード ===================
#include "Slime_1.h"
#include "GameParameter.h"		//定数定義用ヘッダー

// =============== 定数定義 =======================
const int	LEVEL1_ATTACK = 1;						// 攻撃力
#if MODE_GAME_PARAMETER
#else
const float LEVEL1_SCALE = 1.0f;
const float LEVEL1_SPEED = ENEMY_MOVE_SPEED;
#endif
const float LEVEL_1_SHADOW_SCALE = 1.0f;	// スライム＿レベル１の影の大きさ

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：コンストラクタ
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
CSlime_1::CSlime_1()
{
	m_Transform.fScale = { LEVEL1_SCALE,LEVEL1_SCALE ,LEVEL1_SCALE };
	m_Sphere.fRadius *= LEVEL1_SCALE;
	m_eSlimeSize = E_SLIME_LEVEL::LEVEL_1;
	SetNormalSpeed();
	m_nAttack = LEVEL1_ATTACK;
	m_fScaleShadow = LEVEL_1_SHADOW_SCALE;	// 影の大きさを設定
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
CSlime_1::CSlime_1(TPos3d<float> pos, AnimeModel* pModel)
	: CSlime_1()
{
	m_Transform.fPos = pos;			// 初期座標を指定
	m_pModel = pModel;
	// アニメーションのセット
	m_eCurAnime = (int)MOTION_LEVEL1_MOVE;	// 現在のアニメーションをセット
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
CSlime_1::~CSlime_1()
{
}

/* ========================================
	更新処理関数
	-------------------------------------
	内容：更新処理
	-------------------------------------
	引数1：プレイヤー座標(TPos3d)
	-------------------------------------
	戻値：無し
=========================================== */
void CSlime_1::Update(tagTransform3d playerTransform, float fSlimeMoveSpeed)
{
	m_PlayerTran = playerTransform;	// プレイヤーの最新パラメータを取得

	// アニメーションの状態によってアニメーションの進行速度を変更
	if (m_eCurAnime == (int)MOTION_LEVEL1_HIT)
	{
		m_fAnimeTime += (ADD_ANIME * 0.7f);		// アニメーションを進行
	}
	else if (m_eCurAnime == (int)MOTION_LEVEL1_MOVE)
	{
		m_fAnimeTime += ADD_ANIME;		// アニメーションを進行
	}

	if (!m_bHitMove)	//敵が通常の移動状態の時
	{
		// 現在のアニメーションが「吹き飛び」だったら移動モーションに変更
		if (m_eCurAnime == (int)MOTION_LEVEL1_HIT)
		{
			m_eCurAnime = (int)MOTION_LEVEL1_MOVE;
			m_fAnimeTime = 0.0f;	//アニメーションタイムのリセット
		}

		if (!m_bMvStpFlg  && m_nMvStpCnt == 0)	//停止フラグがoffなら
		{
			NormalMove();	//通常移動
		}
		else
		{
			MoveStop();	//爆発から逃げる

			// 停止中はアニメーションも停止させるためにアニメーションタイムを戻す
			m_fAnimeTime -= ADD_ANIME;
		}
	}
	else
	{
		// 吹き飛びアニメーション再生
		if (m_eCurAnime == (int)MOTION_LEVEL1_MOVE)
		{
			m_eCurAnime = (int)MOTION_LEVEL1_HIT;
			m_fAnimeTime = 0.0f;	// アニメーションタイムのリセット
		}

		//敵の吹き飛び移動
		HitMove();
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
void CSlime_1::Draw()
{
	if (!m_pCamera) { return; }	//ヌルチェック

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
	m_pModel->Play(m_eCurAnime,true);
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

	//-- 影の描画
	m_pShadow->Draw(m_Transform, m_fScaleShadow, m_pCamera);
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
void CSlime_1::SetNormalSpeed()
{
	m_fSpeed = LEVEL1_SPEED;	//移動速度に定数をセット
}