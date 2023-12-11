/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	カメラ用抽象クラス実装
	------------------------------------
	Camera.cpp
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/10/24 仮制作 takagi
	・2023/11/02 メンバー変数追加 takagi
	・2023/11/04 更新関数の実装部分削除 takagi
	・2023/11/06 フラグ整理・コメント修正 takagi
	・2023/11/07 GetViewMatrix()関数にconst修飾子付与・コメント修正 takagi
	・2023/11/09 カメラの様々動作チェック。 takagi
	・2023/11/10 パラメタ修正 takagi
	・2023/11/11 define用ヘッダ追加 suzumura
	・2023/11/17 2D表示/3D表示の切換をコンストラクタでなくGetProjectionMatrix()関数で行うように変更・振動機能追加 takagi
	・2023/11/18 2D表示のミスを訂正 takagi
	・2023/11/24 定数値修正・フラグバグ修正・一部コメント詳細化 takagi
	・2023/11/28 振動の仕様変更 takagi
	・2023/11/29 振動の新仕様を全振動に反映しリファクタリング・フレームのコメントないのは書き換える予定のため takagi
	・2023/11/30 Effekseer用に関数追加 takagi
	・2023/12/03 位置ゲッタ作成 takagi
	・2023/12/04 GetViewWithoutTranspose,GetProjectionWithoutTransposeの戻り値を変更 yamashita
	・2023/12/06 ゲームパラメータ対応 takagi
	・2023/12/07 ゲームパラメータから定数移動・不要物除去 takagi

========================================== */

// =============== インクルード ===================
#include "Camera.h"		//自身のヘッダ
#include "Defines.h"	//画面情報
#include "Random.h"		//乱数生成用
#include <vector>		//配列型コンテナ

// =============== 列挙定義 =====================
enum E_DIRECT_VIBRATE
{
	E_DIRECT_VIBRATE_SIDE,		//横方向
	E_DIRECT_VIBRATE_VERTICAL,	//縦方向
	E_DIRECT_VIBRATE_MAX,		//要素数
};	//振動方向

// =============== 定数定義 =====================
const float ASPECT = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;	//画面比率(y / x)
const TPos3d<float> INIT_LOOK(0.0f, 0.0f, 0.0f);					//初期注視地点
const TTriType<float> INIT_UP_VECTOR(0.0f, 1.0f, 0.0f);				//カメラの上方向
const float INIT_CHANGE_RATE_AMPLITUDE = 1.0f;						//初期振幅変化率
const TPos3d<float> INIT_POS(0.0f, 1.6f, -3.0f);					//初期位置
const float INIT_ANGLE = DirectX::XMConvertToRadians(73.0f);        //カメラの角度
const float INIT_NEAR = 1.0f;										//画面手前初期z値
const float INIT_FAR = 150.0f;										//画面奥初期z値
const float INIT_RADIUS = 15.0f;									//カメラと注視点との距離(初期値)
const int MAX_CNT_CHANGE_VIBRATE = 10;								//最大振動変化数
const TDiType<int> INIT_FRAME_WEAK = { 125, 125 };					//弱振動のフレーム数	x:横, y:縦
const TDiType<int> INIT_FRAME_STRONG = { 150, 150 };				//強振動のフレーム数	x:横, y:縦
const TDiType<float> CHANGE_RATE_AMPLITUDE_WEAK{ 0.99f, 0.99f };	//強振幅変化率	1を超えると増加方向、下回ると減少方向	x:横, y:縦
const TDiType<float> CHANGE_RATE_AMPLITUDE_STRONG{ 0.97f, 0.97f };	//強振幅変化率	1を超えると増加方向、下回ると減少方向	x:横, y:縦
///<summary>振幅の確率：弱
///<para>合計が1になる必要はない</para>
///</summary>
const std::vector<double> PROBABILITY_AMPITUDE_WEAK[E_DIRECT_VIBRATE_MAX] = {
	{ 0.1, 0.3, 0.5, 0.3, 0.1 }, //横弱振動
	{ 0.1, 0.3, 0.5, 0.3, 0.1 }, //縦弱振動
};
///<summary>
///<see cref="PROBABILITY_AMPITUDE_WEAK">←上記定数</see>のテーブル
///<para>順番がそのまま対応しており、同じ数ないと機能しない(添削は自由)</para>
///<para>各値は振幅の大きさを表す</para>
///</summary>
const std::vector<float> TABLE_AMPITUDE_WEAK[E_DIRECT_VIBRATE_MAX] = {
	{ -0.05f, -0.025f, 0.0f, 0.025f, 0.05f },	//横弱振幅
	{ -0.05f, -0.025f, 0.0f, 0.025f, 0.05f },	//縦弱振幅
};
///<summary>振幅の確率：強
///<para>合計が1になる必要はない</para>
///</summary>
const std::vector<double> PROBABILITY_AMPITUDE_STRONG[E_DIRECT_VIBRATE_MAX] = {
	{ 0.1, 0.3, 0.5, 0.3, 0.1 },	//横強振動
	{ 0.1, 0.3, 0.5, 0.3, 0.1 },	//縦強振動
};
///<summary>
///<see cref="PROBABILITY_AMPITUDE_STRONG">←上記定数</see>のテーブル
///<para>順番がそのまま対応しており、同じ数ないと機能しない(添削は自由)</para>
///<para>各値は振幅の大きさを表す</para>
///</summary>
const std::vector<float> TABLE_AMPITUDE_STRONG[E_DIRECT_VIBRATE_MAX] = {
	{ -0.1f, -0.05f, 0.0f, 0.05f, 0.1f },	//横強振幅
	{ -1.25f, -0.7f, 0.0f, 0.7f, 1.25f },	//縦強振幅
};



/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：生成時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CCamera::CCamera()
	:m_ucFlag(0x00)												//フラグ
	, m_fPos(INIT_POS)											//位置
	, m_fLook(INIT_LOOK)										//注視点
	, m_fUp(INIT_UP_VECTOR)										//上方ベクトル
	, m_fAngle(INIT_ANGLE)										//角度
	, m_fNear(INIT_NEAR)										//画面手前
	, m_fFar(INIT_FAR)											//画面奥
	, m_fRadius(INIT_RADIUS)									//注視点とカメラの距離
	, m_fOffsetVibrateEye(0.0f)									//カメラ位置振動
	, m_fOffsetVibrateLook(0.0f)								//注視点振動
	, m_nFrameWeak(INIT_FRAME_WEAK)								//フレーム数：弱振動	x:横, y:縦
	, m_nFrameStrong(INIT_FRAME_STRONG)							//フレーム数：強振動	x:横, y:縦
	, m_fChangeRateAmplitudeWeak(INIT_CHANGE_RATE_AMPLITUDE)	//振幅変動率：弱		x:横, y:縦
	, m_fChangeRateAmplitudeStrong(INIT_CHANGE_RATE_AMPLITUDE)	//振幅変動率：強		x:横, y:縦
	, m_nCntChangeVibrate(0)									//振動回数カウンタ
{
}

/* ========================================
	デストラクタ関数
	-------------------------------------
	内容：破棄時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CCamera::~CCamera()
{
}

/* ========================================
	フラグオン関数
	-------------------------------------
	内容：引数で立っているフラグを立てる
	-------------------------------------
	引数1：const unsigned char & ucBitFlag
	-------------------------------------
	戻値：なし
=========================================== */
void CCamera::UpFlag(const unsigned char & ucBitFlag)
{
	// =============== 代入 ===================
	m_ucFlag |= ucBitFlag;	//フラグ操作
}

/* ========================================
	フラグオフ関数
	-------------------------------------
	内容：引数で立っているフラグを降ろす
	-------------------------------------
	引数1：const unsigned char & ucBitFlag
	-------------------------------------
	戻値：なし
=========================================== */
void CCamera::DownFlag(const unsigned char & ucBitFlag)
{
	// =============== 代入 ===================
	m_ucFlag &= (ucBitFlag ^ 0xFF);	//フラグ操作
}

/* ========================================
	フラグセッタ関数
	-------------------------------------
	内容：引数で立っているフラグを逆転させる
	-------------------------------------
	引数1：const unsigned char & ucBitFlag
	-------------------------------------
	戻値：なし
=========================================== */
void CCamera::SetFlag(const unsigned char & ucBitFlag)
{
	// =============== 代入 ===================
	m_ucFlag ^= ucBitFlag;	//フラグ操作
}

/* ========================================
	ビュー行列取得関数
	-------------------------------------
	内容：カメラのビュー行列を提供
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：作成した行列
=========================================== */
DirectX::XMFLOAT4X4 CCamera::GetViewMatrix() const
{
	// =============== 変数宣言 ===================
	DirectX::XMFLOAT4X4 Mat;

	// =============== ビュー行列の計算 ===================
	DirectX::XMStoreFloat4x4(&Mat, DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&GetViewWithoutTranspose())));	//ビュー転置

	// =============== 提供 ===================
	return Mat;	//行列提供
}

/* ========================================
	逆行列取得関数
	-------------------------------------
	内容：ビュー行列の逆行列を提供
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：作成した行列
=========================================== */
DirectX::XMMATRIX CCamera::GetInverseViewMatrix() const
{
	// =============== 変数宣言 ===================
	DirectX::XMMATRIX Mat;			//行列格納用
	DirectX::XMFLOAT4X4 pFlt44;	//行列編集用

	// =============== ビュー行列の計算 ===================
	DirectX::XMFLOAT4X4 view = GetViewWithoutTranspose();
	Mat = DirectX::XMLoadFloat4x4(&view);	//ビュー変換

	// =============== 行列編集 ===================
	DirectX::XMStoreFloat4x4(&pFlt44, Mat);				//行列編集用に変換
	pFlt44._41 = pFlt44._42 = pFlt44._43 = 0.0f;		//移動値打消し
	Mat = DirectX::XMLoadFloat4x4(&pFlt44);				//行列更新

	// =============== 提供 ===================
	return DirectX::XMMatrixInverse(nullptr, Mat);	//逆行列
}

/* ========================================
	プロジェクション行列取得関数
	-------------------------------------
	内容：カメラのプロジェクション行列を提供
	-------------------------------------
	引数1：const E_DRAW_TYPE& eDraw：2D表示か3D表示か
	-------------------------------------
	戻値：作成した行列
=========================================== */
DirectX::XMFLOAT4X4 CCamera::GetProjectionMatrix(const E_DRAW_TYPE& eDraw) const
{
	// =============== 変数宣言 ===================
	DirectX::XMFLOAT4X4 mat;	//行列格納用

	// =============== プロジェクション行列の計算 ===================
	switch (eDraw)	//投影選択
	{
		// =============== 2D表示 ===================
	case E_DRAW_TYPE_2D:	//2Dのプロジェクション座標作成
		DirectX::XMStoreFloat4x4(&mat, DirectX::XMMatrixTranspose(
			DirectX::XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT, m_fNear, m_fFar)));	//左下を原点(0,0)とした座標系
		break;	//分岐処理終了

	// =============== 3D表示 ===================
	case E_DRAW_TYPE_3D:	//3Dのプロジェクション座標作成
		DirectX::XMStoreFloat4x4(&mat, DirectX::XMMatrixTranspose(
			DirectX::XMMatrixPerspectiveFovLH(m_fAngle, ASPECT, m_fNear, m_fFar)));	//3Dプロジェクション変換
		break;	//分岐処理終了
	}

	// =============== 提供 ===================
	return mat;	//行列提供
}

/* ========================================
	転置無しビュー行列取得関数
	-------------------------------------
	内容：転置していないビュー行列を提供
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：作成した行列
=========================================== */
DirectX::XMFLOAT4X4 CCamera::GetViewWithoutTranspose() const
{
	DirectX::XMFLOAT4X4 view;
	DirectX::XMStoreFloat4x4(&view, DirectX::XMMatrixLookAtLH(
		DirectX::XMVectorSet(m_fPos.x, m_fPos.y, m_fPos.z, 0.0f),		//カメラ位置
		DirectX::XMVectorSet(m_fLook.x, m_fLook.y, m_fLook.z, 0.0f),	//注視点
		DirectX::XMVectorSet(m_fUp.x, m_fUp.y, m_fUp.z, 0.0f)));			//アップベクトル
	// =============== 提供 ===================
	return view;	//ビュー座標系
}

/* ========================================
	転置無しプロジェクション行列取得関数
	-------------------------------------
	内容：転置していないプロジェクション行列(2D固定)を提供
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：作成した行列
=========================================== */
DirectX::XMFLOAT4X4 CCamera::GetProjectionWithoutTranspose() const
{
	DirectX::XMFLOAT4X4 projection;
	DirectX::XMStoreFloat4x4(&projection, DirectX::XMMatrixPerspectiveFovLH(m_fAngle, ASPECT, m_fNear, m_fFar));
	// =============== 提供 ===================
	return projection;
}


/* ========================================
	位置ゲッタ関数
	-------------------------------------
	内容：カメラ位置を提供
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：現在位置
=========================================== */
TPos3d<float> CCamera::GetPos() const
{
	// =============== 提供 ===================
	return m_fPos;	//自身の現在位置
}

/* ========================================
	振動規模変更関数
	-------------------------------------
	内容：振動している時のみ、振動に関する変数に干渉
	-------------------------------------
	引数1：int nChangeFrame：振動しているm_nFrameに足す引数。正の値なら持続時間が延び、負なら縮む
	引数2：float fChangegRateAmp：振動しているm_fChangeRateAmplitudeに掛ける引数。正の値なら持続時間が延び、負なら縮む
	-------------------------------------
	戻値：なし
=========================================== */
void CCamera::ChangeScaleVibrate(int nChangeFrame, float fChangegRateAmp)	//TODO:任意の振動に絞った拡張
{
	// =============== 振動フラグ ===================
	if (m_nCntChangeVibrate > MAX_CNT_CHANGE_VIBRATE)
	{
		// =============== 終了 ===================
		return;	//処理中断
	}
	if (m_ucFlag & E_BIT_FLAG_VIBRATION_SIDE_WEAK)
	{
		// =============== 更新 ===================
		m_nFrameWeak.x += nChangeFrame;						//フレームカウンタ干渉
		m_fChangeRateAmplitudeWeak.x *= fChangegRateAmp;	//補正率干渉
		m_nCntChangeVibrate++;								//振動回数カウント
	}
	if (m_ucFlag & E_BIT_FLAG_VIBRATION_UP_DOWN_WEAK)
	{
		// =============== 更新 ===================
		m_nFrameWeak.y += nChangeFrame;						//フレームカウンタ干渉
		m_fChangeRateAmplitudeWeak.y *= fChangegRateAmp;	//補正率干渉
		m_nCntChangeVibrate++;								//振動回数カウント
	}
	if (m_ucFlag & E_BIT_FLAG_VIBRATION_SIDE_STRONG)
	{
		// =============== 更新 ===================
		m_nFrameStrong.x += nChangeFrame;					//フレームカウンタ干渉
		m_fChangeRateAmplitudeStrong.x *= fChangegRateAmp;	//補正率干渉
		m_nCntChangeVibrate++;								//振動回数カウント
	}
	if (m_ucFlag & E_BIT_FLAG_VIBRATION_UP_DOWN_STRONG)
	{
		// =============== 更新 ===================
		m_nFrameStrong.y += nChangeFrame;					//フレームカウンタ干渉
		m_fChangeRateAmplitudeStrong.y *= fChangegRateAmp;	//補正率干渉
		m_nCntChangeVibrate++;								//振動回数カウント
	}
}

/* ========================================
	フラグ別処理関数
	-------------------------------------
	内容：フラグによって判断される各処理を実行する
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CCamera::HandleFlag()
{
	// =============== 振動フラグ ===================
		//割合減少なら0にならないため理論的な無限振動が可能！(実際には誤差程度の値以下になると視認できなくなり、そのうち情報落ちする)
	if (!m_ucFlag)	//何もフラグ無し
	{
		// =============== 初期化 ===================
		m_nCntChangeVibrate = 0;	//カウンタ初期化
	}
	if (m_ucFlag & E_BIT_FLAG_VIBRATION_SIDE_WEAK)
	{
		// =============== 横弱振動 ===================
		if (m_nFrameWeak.x > 0)
		{
			// =============== 振動 ===================
			m_fOffsetVibrateEye.x = TABLE_AMPITUDE_WEAK[E_DIRECT_VIBRATE_SIDE][std::discrete_distribution<>{
				PROBABILITY_AMPITUDE_WEAK[E_DIRECT_VIBRATE_SIDE].begin(), PROBABILITY_AMPITUDE_WEAK[E_DIRECT_VIBRATE_SIDE].end() }(CRandom::GetEngine())]	//ランダムな振幅
				* m_fChangeRateAmplitudeWeak.x;											//振幅補正
				m_fOffsetVibrateLook.x = m_fOffsetVibrateEye.x + m_fOffsetVibrateEye.x;	//注視点振動
				m_fChangeRateAmplitudeWeak.x *= CHANGE_RATE_AMPLITUDE_WEAK.x;			//補正率変化

				// =============== カウンタ ===================
				m_nFrameWeak.x--;	//フレームカウント
		}
		else
		{
			// =============== 初期化 ===================
			DownFlag(E_BIT_FLAG_VIBRATION_SIDE_WEAK);				//フラグ下降
			m_fOffsetVibrateEye.x = 0.0f;								//カメラ位置ずれ初期化
			m_fOffsetVibrateLook.x = 0.0f;								//注視点ずれ初期化
			m_fChangeRateAmplitudeWeak.x = INIT_CHANGE_RATE_AMPLITUDE;	//振幅補正初期化
			m_nFrameWeak.x = INIT_FRAME_WEAK.x;
		}
	}
	if (m_ucFlag & E_BIT_FLAG_VIBRATION_UP_DOWN_WEAK)
	{
		// =============== 縦弱振動 ===================
		if (m_nFrameWeak.y > 0)
		{
			// =============== 振動 ===================
			m_fOffsetVibrateEye.y = TABLE_AMPITUDE_WEAK[E_DIRECT_VIBRATE_VERTICAL][std::discrete_distribution<>{
				PROBABILITY_AMPITUDE_WEAK[E_DIRECT_VIBRATE_VERTICAL].begin(), PROBABILITY_AMPITUDE_WEAK[E_DIRECT_VIBRATE_VERTICAL].end() }(CRandom::GetEngine())]	//ランダムな振幅
				* m_fChangeRateAmplitudeWeak.y;											//振幅補正
				m_fOffsetVibrateLook.y = m_fOffsetVibrateEye.y + m_fOffsetVibrateEye.y;	//注視点振動
				m_fChangeRateAmplitudeWeak.y *= CHANGE_RATE_AMPLITUDE_WEAK.y;			//補正率変化

				// =============== カウンタ ===================
				m_nFrameWeak.y--;	//フレームカウント
		}
		else
		{
			// =============== 初期化 ===================
			DownFlag(E_BIT_FLAG_VIBRATION_UP_DOWN_WEAK);				//フラグ下降
			m_fOffsetVibrateEye.y = 0.0f;								//カメラ位置ずれ初期化
			m_fOffsetVibrateLook.y = 0.0f;								//注視点ずれ初期化
			m_fChangeRateAmplitudeWeak.y = INIT_CHANGE_RATE_AMPLITUDE;	//振幅補正初期化
			m_nFrameWeak.y = INIT_FRAME_WEAK.y;
		}
	}
	if (m_ucFlag & E_BIT_FLAG_VIBRATION_SIDE_STRONG)
	{
		// =============== 横強振動 ===================
		if (m_nFrameStrong.x > 0)
		{
			// =============== 振動 ===================
			m_fOffsetVibrateEye.x = TABLE_AMPITUDE_STRONG[E_DIRECT_VIBRATE_SIDE][std::discrete_distribution<>{
				PROBABILITY_AMPITUDE_STRONG[E_DIRECT_VIBRATE_SIDE].begin(), PROBABILITY_AMPITUDE_STRONG[E_DIRECT_VIBRATE_SIDE].end() }(CRandom::GetEngine())]	//ランダムな振幅
				* m_fChangeRateAmplitudeStrong.x;									//振幅補正
				m_fOffsetVibrateLook.x = m_fOffsetVibrateEye.x + m_fOffsetVibrateEye.x;	//注視点振動
				m_fChangeRateAmplitudeStrong.x *= CHANGE_RATE_AMPLITUDE_STRONG.x;		//補正率変化

				// =============== カウンタ ===================
				m_nFrameStrong.x--;	//フレームカウント
		}
		else
		{
			// =============== 初期化 ===================
			DownFlag(E_BIT_FLAG_VIBRATION_SIDE_STRONG);					//フラグ下降
			m_fOffsetVibrateEye.x = 0.0f;									//カメラ位置ずれ初期化
			m_fOffsetVibrateLook.x = 0.0f;									//注視点ずれ初期化
			m_fChangeRateAmplitudeStrong.x = INIT_CHANGE_RATE_AMPLITUDE;	//振幅補正初期化
			m_nFrameStrong.x = INIT_FRAME_STRONG.x;
		}
	}
	if (m_ucFlag & E_BIT_FLAG_VIBRATION_UP_DOWN_STRONG)
	{
		// =============== 縦強振動 ===================
		if (m_nFrameStrong.y > 0)
		{
			// =============== 振動 ===================
			m_fOffsetVibrateEye.y = TABLE_AMPITUDE_STRONG[E_DIRECT_VIBRATE_VERTICAL][std::discrete_distribution<>{
				PROBABILITY_AMPITUDE_STRONG[E_DIRECT_VIBRATE_VERTICAL].begin(), PROBABILITY_AMPITUDE_STRONG[E_DIRECT_VIBRATE_VERTICAL].end() }(CRandom::GetEngine())]	//ランダムな振幅
				* m_fChangeRateAmplitudeStrong.y;									//振幅補正
				m_fOffsetVibrateLook.y = m_fOffsetVibrateEye.y + m_fOffsetVibrateEye.y;	//注視点振動
				m_fChangeRateAmplitudeStrong.y *= CHANGE_RATE_AMPLITUDE_STRONG.y;		//補正率変化

				// =============== カウンタ ===================
				m_nFrameStrong.y--;	//フレームカウント
		}
		else
		{
			// =============== 初期化 ===================
			DownFlag(E_BIT_FLAG_VIBRATION_UP_DOWN_STRONG);					//フラグ下降
			m_fOffsetVibrateEye.y = 0.0f;									//カメラ位置ずれ初期化
			m_fOffsetVibrateLook.y = 0.0f;									//注視点ずれ初期化
			m_fChangeRateAmplitudeStrong.y = INIT_CHANGE_RATE_AMPLITUDE;	//振幅補正初期化
			m_nFrameStrong.y = INIT_FRAME_STRONG.y;
		}
	}
}