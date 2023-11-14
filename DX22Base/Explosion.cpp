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

======================================== */

// =============== インクルード ===================
#include "Explosion.h"			//自身のヘッダー
#include "Geometry.h"			//空間における形状の抽象クラス定義のヘッダー
#include "Sphere.h"				//球定義のヘッダー
#include "GameParameter.h"		//定数定義用ヘッダー

// =============== 定数定義 =======================
#if MODE_GAME_PARAMETER
#else
//const float MAX_DISPLAY_TIME = 3.0f * 60;	// 爆発持続秒数
const float EXPAND_QUICK_RATE = 0.2f;   // 膨張加速割合 


#endif

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：コンストラクタ
	-------------------------------------
	引数1：生成座標(x,y,z)
	-------------------------------------
	戻値：無し
=========================================== */
CExplosion::CExplosion(TTriType<float> pos, float size,float time)
	: m_fSize(0.0f)
	, m_fSizeAdd(0.0f)
	, m_fDelFrame(0.0f)
	, m_bDelFlg(false)
	, m_fExplodeTime(0.0f)
	, m_fMaxSize(0.0f)
{

	//爆発オブジェクト初期化
	m_Sphere.fPos = pos;
	m_Sphere.radius = size / 2;	// 当たり判定をセットする
	//m_fSizeAdd = size / ONE_SECOND_FRAME;
	m_3dModel = new CSphere();

	m_fExplodeTime = time;		//爆発総時間をセットする
	m_fMaxSize = size;	//最大サイズをセットする
	
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


	DisplayTimeAdd();
}



/* ========================================
	描画関数
	-------------------------------------
	内容：爆発の描画処理
	-------------------------------------
	引数1：
	-------------------------------------
	戻値：
=========================================== */
void CExplosion::Draw()
{
	DirectX::XMMATRIX mat = DirectX::XMMatrixTranslation(m_Sphere.fPos.x, m_Sphere.fPos.y, m_Sphere.fPos.z);
	DirectX::XMMATRIX Scale = DirectX::XMMatrixScaling(m_fSize, m_fSize, m_fSize);
	mat = Scale * mat;
	mat = DirectX::XMMatrixTranspose(mat);
	DirectX::XMFLOAT4X4 fMat;	//行列の格納先
	DirectX::XMStoreFloat4x4(&fMat, mat);
	m_3dModel->SetWorld(fMat);

	m_3dModel->SetView(m_pCamera->GetViewMatrix());
	m_3dModel->SetProjection(m_pCamera->GetProjectionMatrix());

	m_3dModel->Draw();	// 爆発仮3Dモデルの描画
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
	m_fDelFrame++;	// フレーム加算

	// 一定秒数まで大きくする
	if (m_fDelFrame <= m_fExplodeTime )
	{
		// m_fTimeに基づいてm_fSizeAddを決定
		m_fSizeAdd = m_fMaxSize / m_fExplodeTime / EXPAND_QUICK_RATE;

		// 最大サイズになるまでSizeを加算
		if (m_fSize < m_fMaxSize)
		{
			m_fSize += m_fSizeAdd;
		}

	}
	// 一定秒数時間が経ったら
	if (m_fExplodeTime <= m_fDelFrame)
	{
		m_bDelFlg = true;	// 削除フラグを立てる
	}

	
	m_Sphere.radius = m_fSize / 2;	// 当たり判定をセットする

}

/* ========================================
	座標設定処理関数
	-------------------------------------
	内容：座標に値をセットする
	-------------------------------------
	引数1：座標情報(x,y,z)
	-------------------------------------
	戻値：無し
=========================================== */
void CExplosion::SetPos(TTriType<float> pos)
{
	m_Sphere.fPos = pos;
}


/* ========================================
	Sphere情報設定処理関数
	-------------------------------------
	内容：Sphereに値をセットする
	-------------------------------------
	引数1：Sphere情報
	-------------------------------------
	戻値：無し
=========================================== */
void CExplosion::SetSphere(tagSphereInfo sphere)
{
	m_Sphere = sphere;
}

/* ========================================
	Sphere情報取得処理関数
	-------------------------------------
	内容：Sphere情報を取得する
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：Sphere情報
=========================================== */
tagSphereInfo CExplosion::GetSphere()
{
	return m_Sphere;
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



