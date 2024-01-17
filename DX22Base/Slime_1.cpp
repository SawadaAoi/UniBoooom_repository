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
CSlime_1::CSlime_1(TPos3d<float> pos,VertexShader* pVS, AnimeModel* pModel, vector<AnimeModel::AnimeNo> anime)
	: CSlime_1()
{
	m_Transform.fPos = pos;			// 初期座標を指定
	m_pVS = pVS;
	m_pModel = pModel;
	pModel->SetVertexShader(ShaderList::GetVS(ShaderList::VS_ANIME));
	// アニメーションの受け渡し
	m_Anime = anime;
	m_pModel->Play(m_Anime[MOTION_LEVEL1_MOVE],true);
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
	// m_pModel->Step(ADD_ANIME);
	m_fAnimeTime += ADD_ANIME;		// アニメーションを進行


	if (!m_bHitMove)	//敵が通常の移動状態の時
	{
		if (!m_bEscape  && m_nEscapeCnt == 0)	// 逃げるフラグがoffなら
		{
			NormalMove();	//通常移動
		}
		else
		{
			Escape();	//爆発から逃げる
			//m_pModel->Step(-ADD_ANIME);	// 近くに爆発がある場合アニメを戻して静止させる
		}
	}
	else
	{
		// 吹き飛びアニメーション再生
		if (m_pModel->GetPlayNo() == m_Anime[MOTION_LEVEL1_MOVE])
		{
			//m_pModel->Play(m_Anime[MOTION_LEVEL1_HIT],false);
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
	引数1：カメラ
	-------------------------------------
	戻値：無し
=========================================== */
void CSlime_1::Draw(const CCamera * pCamera)
{

	DirectX::XMFLOAT4X4 mat[3];

	mat[0] = m_Transform.GetWorldMatrixSRT();
	mat[1] = pCamera->GetViewMatrix();
	mat[2] = pCamera->GetProjectionMatrix();

	//-- 行列をシェーダーへ設定
	m_pVS->WriteBuffer(0, mat);

	ShaderList::SetWVP(mat);

	// アニメーションの現在時間をセット
	m_pModel->SetAnimationTime(m_pModel->GetPlayNo(), m_fAnimeTime);

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
	}

	//-- 影の描画
	m_pShadow->Draw(m_Transform, m_fScaleShadow, pCamera);
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