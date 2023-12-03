/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	爆発処理cpp
	---------------------------------------
	Explosion.cpp

	TeiUon

	変更履歴
	・2023/11/03 cpp作成 Tei
	・2023/11/05 爆発cppの初期設定 Tei
	・2023/11/06 爆発のモデル設定、描画、位置
	・2023/11/06 boolの設定と取得関数制作 Tei
	・2023/11/08 変数、関数の変更 Sawada
	・2023/11/10 他のオブジェクトと同一カメラでビューとプロジェクションをセットできるようにした Yamashita
	・2023/11/10 爆発の大きさを徐々に大きくなるように変更 Sawada
	・2023/11/11 parameter用ヘッダ追加 Suzumura
	・2023/11/13 スライムレベルによって爆破の膨らみの速度の調整ができるように変更 Suzumura
	・2023/11/14 SphereInfoの変更に対応 Takagi
	・2023/11/15 Objectクラスを継承したので修正　yamamoto
	・2023/11/20 コンボ数配列添え字の追加 Sawada
	・2023/11/21 初期値の設定と、遅延処理の追加 Sawada
	・2023/11/21 ボスに一度触ったかを判定用の関数実装 Suzumura

	・2023/11/21 DisplayAddTimeの中にBoooomUIの表示時間処理追加 Tei

======================================== */

// =============== インクルード ===================
#include "Explosion.h"			//自身のヘッダー
#include "Geometry.h"			//空間における形状の抽象クラス定義のヘッダー
#include "Sphere.h"				//球定義のヘッダー
#include "GameParameter.h"		//定数定義用ヘッダー
#include "DirectWrite.h"

// =============== 定数定義 =======================
#if MODE_GAME_PARAMETER
#else
//const float MAX_DISPLAY_TIME = 3.0f * 60;	// 爆発持続秒数
const float EXPAND_QUICK_RATE = 0.2f;   // 膨張加速割合 
const int DELAY_TIME = 0.5f * 60;
#endif
const float EXPLODE_STANDARD_SIZE = 0.15f;
const float EXPLODE_STANDARD_ONE_FRAME = 1.38 * 60.0;

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：コンストラクタ
	-------------------------------------
	引数1：生成座標(x,y,z)
	引数2：生成サイズ(x,y,z)
	引数3：発生時間
	引数4：コンボ配列の位置(添え字)
	引数5：遅延フラグ
	-------------------------------------
	戻値：無し
=========================================== */
CExplosion::CExplosion(TPos3d<float> fPos, float fSize, float fTime, int comboNum, bool delayFlg, int nDamage, Effekseer::EffectRef explodeEffect, const CCamera* pCamera)
	: m_fSizeAdd(0.0f)
	, m_nDelFrame(0)
	, m_bDelFlg(false)
	, m_fExplodeTime(fTime)	// 爆発総時間をセットする
	, m_fMaxSize(fSize)		// 最大サイズをセットする
	, m_dComboNum(comboNum)
	, m_bDelayFlg(delayFlg)
	, m_dDelayCnt(0)
	, m_fDamage(0)
	, m_pCamera(nullptr)
	, m_bBossTouched(false)
{
	//爆発オブジェクト初期化
	m_Sphere.fRadius = fSize / 2;	// 当たり判定をセットする
	m_3dModel = new CSphere();
	m_Transform.fPos = fPos;		// スライムがいた場所に生成する
	m_fExplodeTime = fTime;		// 爆発総時間をセットする
	m_fMaxSize = fSize;			// 最大サイズをセットする
	m_fDamage = (float)nDamage;		// 与えるダメージ量をセットする
	m_pCamera = pCamera;		//カメラをセット
	TPos3d<float> cameraPos = m_pCamera->GetPos();
	m_cameraPos = { cameraPos.x, cameraPos.y, cameraPos.z };
	m_explodeEffect = explodeEffect;
	m_efcHnadle = LibEffekseer::GetManager()->Play(m_explodeEffect, fPos.x, fPos.y, fPos.z);
	LibEffekseer::GetManager()->SetScale(m_efcHnadle,EXPLODE_STANDARD_SIZE * fSize, EXPLODE_STANDARD_SIZE * fSize, EXPLODE_STANDARD_SIZE * fSize);
	LibEffekseer::GetManager()->SetSpeed(m_efcHnadle, EXPLODE_STANDARD_ONE_FRAME / fTime);
	LibEffekseer::GetManager()->SetModelRenderer(m_efcHnadle, EXPLODE_STANDARD_ONE_FRAME / fTime);

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
CExplosion::~CExplosion()
{

	SAFE_DELETE(m_3dModel);	// メモリ解放
}


/* ========================================
	更新関数
	-------------------------------------
	内容：爆発内の更新処理
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CExplosion::Update()
{
	// 爆発遅延処理が有効な場合
	if (m_bDelayFlg)
	{
		Delay();	// 遅延処理
		return;
	}

	DisplayTimeAdd();
}



/* ========================================
	描画関数
	-------------------------------------
	内容：爆発の描画処理
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CExplosion::Draw()
{
	m_3dModel->SetWorld(m_Transform.GetWorldMatrixSRT());

	m_3dModel->SetView(m_pCamera->GetViewMatrix());
	m_3dModel->SetProjection(m_pCamera->GetProjectionMatrix());

	//m_3dModel->Draw();	// 爆発仮3Dモデルの描画
	m_pCamera->GetInverseViewMatrix();
	m_pCamera->GetProjectionMatrix();
	//エフェクトの描画
	TPos3d<float> cameraPos = m_pCamera->GetPos();						//カメラ座標を取得
	DirectX::XMFLOAT3 fCameraPos(cameraPos.x, cameraPos.y, cameraPos.z);	//XMFLOAT3に変換
	LibEffekseer::SetViewPosition(fCameraPos);								//カメラ座標をセット
	LibEffekseer::SetCameraMatrix(m_pCamera->GetViewWithoutTranspose(), m_pCamera->GetProjectionWithoutTranspose());	//転置前のviewとprojectionをセット

	Effekseer::Vector3D vec = LibEffekseer::GetManager()->GetLocation(m_efcHnadle);
	std::string txt = "X = " + std::to_string(vec.X) + "\nY = " + std::to_string(vec.Y) + "\nZ = " + std::to_string(vec.Z);
	DirectWrite::DrawString(txt, DirectX::XMFLOAT2(0.0f,200.0f));
}


/* ========================================
	爆発表示カウント加算処理関数
	-------------------------------------
	内容：爆発表示カウントを加算して一定秒数超えたら終了フラグをオンにする
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CExplosion::DisplayTimeAdd()
{
	m_nDelFrame++;	// フレーム加算

	// 一定秒数まで大きくする
	if (m_nDelFrame <= m_fExplodeTime )
	{
		// m_fTimeに基づいてm_fSizeAddを決定
		m_fSizeAdd = m_fMaxSize / m_fExplodeTime / EXPAND_QUICK_RATE;

		// 最大サイズになるまでSizeを加算
		if (m_Transform.fScale.y < m_fMaxSize)
		{
			m_Transform.fScale += m_fSizeAdd;
		}

	}
	// 一定秒数時間が経ったら
	if (m_fExplodeTime <= m_nDelFrame)
	{
		m_bDelFlg = true;	// 削除フラグを立てる
	}

	
	m_Sphere.fRadius = m_Transform.fScale.y / 2;	// 当たり判定をセットする
}


/* ========================================
	ボスにふれたことを知らせる関数
	-------------------------------------
	内容：ボスと接触時フラグをon
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CExplosion::BossTouched()
{
	m_bBossTouched = true;
}

/* ========================================
	座標設定処理関数
	-------------------------------------
	内容：爆発の発生を遅らせる
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CExplosion::Delay()
{
	m_dDelayCnt++;

	// 遅延秒数が経ったら
	if (m_dDelayCnt >= DELAY_TIME)
	{
		m_bDelayFlg = false;	// 遅延フラグをオフにする
	}
}

/* ========================================
	削除フラグ取得処理関数
	-------------------------------------
	内容：削除フラグを取得する
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：削除フラグ(bool)
=========================================== */
bool CExplosion::GetDelFlg()
{
	return m_bDelFlg;
}

/* ========================================
	コンボ配列番号取得処理関数
	-------------------------------------
	内容：コンボ配列番号を取得する
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：コンボ配列番号(int)
=========================================== */
int CExplosion::GetComboNum()
{
	return m_dComboNum;
}

/* ========================================
	ダメージ量取得処理関数
	-------------------------------------
	内容：与えるダメージを取得する
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：ダメージ量(int)
=========================================== */
int CExplosion::GetDamage()
{
	return (int)m_fDamage;
}

/* ========================================
	既に当たっているか取得処理関数
	-------------------------------------
	内容：既にボスとあたっているかどうかを取得する
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：接触フラグ(bool)
=========================================== */
bool CExplosion::GetBossTouched()
{
	return m_bBossTouched;
}

/* ========================================
	カメラ情報セット関数
	----------------------------------------
	内容：描画処理で使用するカメラ情報セット
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
======================================== */
void CExplosion::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;
}



