/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	スライムベース クラス実装
	---------------------------------------
	SlimeBase.cpp
	
	作成者：鈴村 朋也
	
	変更履歴
	・2023/11/04 スライムベースクラス作成 Suzumura
	・2023/11/06 ハンマーもしくは敵により吹っ飛ばされる関数を追加 Yamashita
	・2023/11/06 インクルード誤字の修正 Tei
	・2023/11/08 GetPos→GetSphereに名前を変更 Yamashita
	・2023/11/08 定数定義がヘッダーにあったのでcppに移動 Yamashita
	・2023/11/08 コメントを追加 Sawada
	・2023/11/09 プレイヤー追跡移動変更 Sawada
	・2023/11/09 Update,NormalMoveの引数変更 Sawada
	・2023/11/11 parameter用ヘッダ追加 Suzumura
	・2023/11/12 プレイヤーの方向を向きながら進むように変更  Yamamoto
	・2023/11/12 ランダム移動を追加  Sawada
	・2023/11/13 GetScale関数を追加 Suzumura
	・2023/11/14 SphereInfoの変更に対応 Takagi
	・2023/11/15 Objectクラスを継承したので修正　yamamoto
	・2023/11/26 スライムが爆発から逃げる処理を作成　yamashita
	・2023/11/28 攻撃力を追加 Sawada
	・2023/11/29 影メモリリーク除去 takagi
	・2023/11/30 モデルの読み込みが反転したのでradian.yが反対になるように変更 yamashita
	・2023/12/07 ゲームパラメータから一部定数移動 takagi
	・2024/01/18 炎スライムのエフェクト追加 Tei
	・2024/1/26  Drawの引数の const CCamera*　を削除 Yamashita
	・2024/02/09 UsingCamera使用 takagi
	・2024/02/13 カメラ削除 takagi

========================================== */

// =============== インクルード ===================
#include "SlimeBase.h"
#include "Geometry.h"
#include "GameParameter.h"	//定数定義用ヘッダー
#include "UsingCamera.h"	//カメラ使用

// =============== 定数定義 =======================
const float SLIME_BASE_RADIUS = 0.5f;			// スライムの基準の大きさ
const int	RANDOM_MOVE_SWITCH_TIME = 3 * 60;	// ランダム移動の方向切り替え
const float SPEED_DOWN_RATIO = 0.6f;			// 吹き飛ぶ際にかかる移動速度の変化の割合    RATIO=>割合
const float REFLECT_RATIO = 0.1f;				// スライムがスライムを吹き飛ばした際に吹き飛ばした側のスライムの移動量を変える割合
const float MOVE_RESIST = 0.05f;				// 吹き飛び移動中のスライムの移動速度に毎フレームかかる減算数値
const float MULTIPLE_SPEED = 1.3f;				// チャージハンマーに叩かれたときのスライムの移動速度に書ける倍率
#if MODE_GAME_PARAMETER
#else
const float MOVE_DISTANCE_PLAYER = 15;			// プレイヤー追跡移動に切り替える距離
#endif

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：コンストラクタ
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
CSlimeBase::CSlimeBase()
	: m_pModel(nullptr)
	//, m_pVS(nullptr)
	, m_move(0.0f, 0.0f, 0.0f)
	, m_fSpeed(ENEMY_MOVE_SPEED)
	, m_fVecAngle(0.0f)
	, m_bHitMove(false)
	, m_eSlimeSize(LEVEL_1)	//後でSLIME_NONEにする <=TODO
	, m_RanMoveCnt(RANDOM_MOVE_SWITCH_TIME)	// 初期
	, m_fStpDirPos{ 0.0f,0.0f,0.0f }
	, m_bMvStpFlg(false)
	, m_nMvStpCnt(0)
	, m_fScaleShadow(0.0f)
	, m_fAnimeTime(0.0f)
	, m_eCurAnime(MOTION_LEVEL1_MOVE)
	, m_bChargeHit(false)
{
	m_Transform.fScale = (1.0f, 1.0f, 1.0f);
	//当たり判定(自分)初期化
	m_Sphere.fRadius = SLIME_BASE_RADIUS;

	int random = abs(rand() % 360);	//ランダムに0〜359の数字を作成
	m_Ry = DirectX::XMMatrixRotationY((float)random);

	m_pShadow = new CShadow();	// 影生成


}

/* ========================================
	デストラクタ関数
	-------------------------------------
	内容：デストラクタ
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
CSlimeBase::~CSlimeBase()
{
	// =============== メモリ開放 ===================
	SAFE_DELETE(m_pShadow);	//影解放
	
	//--エフェクト停止--
	LibEffekseer::GetManager()->StopEffect(m_efcFlameHandle);
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
void CSlimeBase::Update(tagTransform3d playerTransform, float fSlimeMoveSpeed)
{
	m_PlayerTran = playerTransform;	// プレイヤーの最新パラメータを取得

	if (!m_bHitMove)	//敵が通常の移動状態の時
	{
		if (!m_bMvStpFlg  && m_nMvStpCnt == 0)	//停止フラグがoffなら
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
		//敵の吹き飛び移動
		HitMove();
	}

	// -- 座標更新
	m_Transform.fPos.x += m_move.x * fSlimeMoveSpeed;
	m_Transform.fPos.z += m_move.z * fSlimeMoveSpeed;

	if (GetSlimeLevel() == LEVEL_FLAME)
	{
		//エフェクト位置、回転角度更新
		LibEffekseer::GetManager()->SetLocation(m_efcFlameHandle, m_Transform.fPos.x, m_Transform.fPos.y, m_Transform.fPos.z + 0.5f);
		LibEffekseer::GetManager()->SetRotation(m_efcFlameHandle, m_Transform.fRadian.x, m_Transform.fRadian.y, m_Transform.fRadian.z);
	}

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
void CSlimeBase::Draw()
{

	//-- 影の描画
	m_pShadow->Draw(m_Transform, m_fScaleShadow);

	//行列状態を取得してセット
	DirectX::XMFLOAT4X4 world;
	DirectX::XMStoreFloat4x4(&world, XMMatrixTranspose(
		DirectX::XMMatrixScaling(m_Transform.fScale.x, m_Transform.fScale.y, m_Transform.fScale.z) *
		DirectX::XMMatrixRotationY(m_Transform.fRadian.y + DirectX::g_XMPi[0]) *
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


/* ========================================
	通常移動関数
	----------------------------------------
	内容：プレイヤーを追跡する移動を行う
	----------------------------------------
	引数1：プレイヤー当たり判定(Sphere)
	----------------------------------------
	戻値：なし
======================================== */
void CSlimeBase::NormalMove()
{
	TPos3d<float> playerPos = m_PlayerTran.fPos;

	// 敵からエネミーの距離、角度を計算
	float distancePlayer	= m_Transform.fPos.Distance(playerPos);

	// プレイヤーと距離が一定以内だったら
	if (distancePlayer < MOVE_DISTANCE_PLAYER) 
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
		directionVector.x = m_Transform.fPos.x-playerPos.x;
		directionVector.y = m_Transform.fPos.y-playerPos.y;
		directionVector.z = m_Transform.fPos.z-playerPos.z;

		// ベクトルを正規化して方向ベクトルを得る
		DirectX::XMVECTOR direction = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&directionVector));
		// 方向ベクトルから回転行列を計算
		m_Transform.fRadian.y = atan2(-directionVector.x, -directionVector.z);
	}
	else
	{
		RandomMove();	// ランダム移動

	}

}

/* ========================================
	ランダム移動関数
	----------------------------------------
	内容：360度にランダム移動を行う
	----------------------------------------
	引数1：無し
	----------------------------------------
	戻値：無し
======================================== */
void CSlimeBase::RandomMove()
{
	m_RanMoveCnt++;		// 移動方向切り替え間隔時間加算

	// 移動方向切り替え時間が経ったら
	if (m_RanMoveCnt >= RANDOM_MOVE_SWITCH_TIME)
	{
		int ranAngle = rand() % 360;	// 移動方向決定

		// 角度方向に移動する
		m_move.x = -cosf(DirectX::XMConvertToRadians((float)ranAngle)) * m_fSpeed;
		m_move.z = sinf(DirectX::XMConvertToRadians((float)ranAngle)) * m_fSpeed;

		// 向きを変える
		m_Transform.fRadian.y = DirectX::XMConvertToRadians((float)ranAngle - 90.0f);

		m_RanMoveCnt = 0;	// 加算値をリセット
	}


}

/* ========================================
	ハンマーか敵に吹っ飛ばされて実際に移動量を確定する関数
	----------------------------------------
	内容：X方向とZ方向の移動量を確定する処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
======================================== */
void CSlimeBase::HitMove()
{
	//敵キャラの移動速度と移動角度に応じてX方向とZ方向の移動量を決める
	m_move.x = cos(m_fVecAngle) * (m_fSpeed * SPEED_DOWN_RATIO);
	m_move.z = sin(m_fVecAngle) * (m_fSpeed * SPEED_DOWN_RATIO);

	m_fSpeed -= MOVE_RESIST;	//毎フレームの速度の減算処理
	if (m_fSpeed <= 0)	//速度が0以下になったら
	{
		m_bHitMove = false;				//吹き飛び状態のフラグをOFFにする
		SetNormalSpeed();	// 継承した関数を使用して大きさごとのスピードをセットする
		m_RanMoveCnt = RANDOM_MOVE_SWITCH_TIME;
		m_bChargeHit = false;
	}
}

/* ========================================
	ハンマーか敵に吹っ飛ばされる関数
	----------------------------------------
	内容：引数に応じて飛ぶ方向と移動速度を決める処理
	----------------------------------------
	引数1：速度
	引数2：角度
	----------------------------------------
	戻値：なし
======================================== */
void CSlimeBase::HitMoveStart(float speed, float angle,bool ChargeHit)
{
	m_fSpeed = speed;			//移動量を入れる
	m_fVecAngle = angle;		//移動方向を入れる
	m_bHitMove = true;			//吹き飛び状態をONにする
	m_bChargeHit = ChargeHit;	// チャージハンマーに叩かれたか
}

/* ========================================
	反発関数
	----------------------------------------
	内容：スライムに反発の割合を乗算する処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
======================================== */
void CSlimeBase::Reflect()
{
	m_fSpeed *= REFLECT_RATIO;
}


/* ========================================
	停止動作関数
	----------------------------------------
	内容：スライムを暫く硬直させる
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
======================================== */
void CSlimeBase::MoveStop()
{
	//爆発への角度を取得
	float rad = atan2f(m_fStpDirPos.x - m_Transform.fPos.x, m_fStpDirPos.z - m_Transform.fPos.z);
	//爆発と反対方向に移動
	m_move.x = 0.0f;//-(cosf(rad)) * ENEMY_MOVE_SPEED;
	m_move.z = 0.0f;//-(sinf(rad)) * ENEMY_MOVE_SPEED;
	m_Transform.fRadian.y = rad;

	m_nMvStpCnt++;	//カウントを増加
	if (m_nMvStpCnt > ESCAPE_TIME) 
	{ 
		m_bMvStpFlg = false; 
		m_nMvStpCnt = 0;
	}
}

/* ========================================
	停止時方向対象オブジェクト座標セット関数
	----------------------------------------
	内容：停止時方向対象の座標をセットする
	----------------------------------------
	引数1：停止時方向対象の座標
	----------------------------------------
	戻値：なし
======================================== */
void CSlimeBase::SetStopDirectionObjPos(TPos3d<float> stpDirPos)
{
	m_fStpDirPos = stpDirPos;
}


/* ========================================
	停止状態セット関数
	----------------------------------------
	内容：移動停止状態をセットする
	----------------------------------------
	引数1：true：停止中 / false：移動中
	----------------------------------------
	戻値：なし
======================================== */
void CSlimeBase::SetMoveStopFlg(bool bEscape)
{
	m_bMvStpFlg = bEscape;
}



/* ========================================
	スライムレベル取得関数
	----------------------------------------
	内容：スライムのレベルを返す
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：スライムのレベル
======================================== */
E_SLIME_LEVEL CSlimeBase::GetSlimeLevel()
{
	return m_eSlimeSize;
}

/* ========================================
	吹飛状態フラグ取得関数
	----------------------------------------
	内容：吹飛状態フラグを返す
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：吹飛状態フラグ
======================================== */
bool CSlimeBase::GetHitMoveFlg()
{
	return m_bHitMove;
}

/* ========================================
	座標取得関数
	----------------------------------------
	内容：スライムの座標を取得
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：スライムの座標
======================================== */
TPos3d<float> CSlimeBase::GetPos()
{
	return m_Transform.fPos;
}

/* ========================================
	停止状態取得関数
	----------------------------------------
	内容：停止状態かの確認
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：bool
======================================== */
bool CSlimeBase::GetMoveStopFlg()
{
	return m_bMvStpFlg;
}

/* ========================================
	攻撃力取得関数
	----------------------------------------
	内容：攻撃力を取得する
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：攻撃力
======================================== */
int CSlimeBase::GetAttack()
{
	return m_nAttack;
}

/* ========================================
	チャージハンマーによる吹き飛ぶ取得関数
	----------------------------------------
	内容：チャージハンマーによる吹き飛びかどうかを取得する
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：チャージハンマーによる吹き飛びかどうか
======================================== */
bool CSlimeBase::GetChargeHit()
{
	return m_bChargeHit;
}

/* ========================================
	吹き飛び角度取得関数
	----------------------------------------
	内容：吹き飛び角度を取得する
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：吹き飛び角度
======================================== */
float CSlimeBase::GetVecAngle()
{
	return m_fVecAngle;
}

CShadow* CSlimeBase::GetShadowPtr()
{
	return m_pShadow;
}

/* ========================================
	移動速度取得関数
	----------------------------------------
	内容：スライムの移動速度を返す
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：スライムの移動速度
======================================== */
float CSlimeBase::GetSpeed()
{
	return m_fSpeed;
}








