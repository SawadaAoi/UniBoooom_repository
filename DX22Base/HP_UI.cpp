/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	HPテクスチャ表示管理用ソース
	------------------------------------
	HP_UI.cpp
	------------------------------------
	作成者	nieda

	変更履歴
	・2023/11/16 新規作成 nieda
	・2023/11/28 半分ずつ減るように修正 sawada
	・2023/11/29 アニメーション追加 nieda
	・2023/12/01 半分のHPアニメーション追加 nieda
	・2023/12/07 ゲームパラメータから一部定数移動・不要物除去 takagi
	・2024/01/21 コメント改修・MessageBox改善 takagi

========================================== */

// =============== インクルード ===================
#include "HP_UI.h"					
#include "DirectXTex/TextureLoad.h"		
#include "Sprite.h"						
#include "Pos3d.h"						
#include "GameParameter.h"		
#include "Player.h"

// =============== 定数定義 ===================
const TTriType<float> HP_UI_POS = { 45.0f, 50.0f ,0.0f };	// テクスチャの縦幅、横幅
const TTriType<float> HP_UI_SIZE = { 60.0f, 55.0f ,0.0f };	// テクスチャの縦幅、横幅
const float DRAW_WIDTH = 65.0f;	// テクスチャの横幅
const int SWITCH_HP_ANIM = 0;				// アニメーション切り替えの間隔
const int HP_ANIM_WIDTH_NUM_MAX = 6;		// 横分割数最大数
const int HP_ANIM_HEIGHT_NUM_MAX = 6;		// 縦分割数最大数
const float HP_ANIM_SIZEX = 1.0f / HP_ANIM_WIDTH_NUM_MAX;	// テクスチャ横分割サイズ
const float HP_ANIM_SIZEY = 1.0f / HP_ANIM_HEIGHT_NUM_MAX;	// テクスチャ縦分割サイズ
const float DRAW_ANIM_HEIGHT = HP_UI_SIZE.y + 40.0f;		// アニメーションの表示位置
const float DRAW_ANIM_WIDTH = HP_UI_SIZE.x + 40.0f;		// アニメーションの表示位置
//TODO:早くカメラ使って
const float VIEW_LEFT = 0.0f;		// 画面左端の座標
const float VIEW_RIGHT = 1280.0f;	// 画面右端の座標（画面横幅）
const float VIEW_BOTTOM = 720.0f;	// 画面下端の座標（画面縦幅）
const float VIEW_TOP = 0.0f;		// 画面上端の座標
const float NEAR_Z = 0.1f;			// 画面に写り始める距離
const float FAR_Z = 10.0f;			// 写せる限界距離

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：生成時に行う処理
	-------------------------------------
	引数：プレイヤーのHPのアドレス
	-------------------------------------
	戻値：なし
=========================================== */
CHP_UI::CHP_UI()
	: m_bPlayAnim(false)
	, m_nPlayerOldHp(PLAYER_HP)
	, m_nCnt(0)
	, m_fUVposX(0)
	, m_fUVposY(0)
	, m_nCntWidth(0)
	, m_nCntHeight(0)
{
	m_pTexture[HEART_FULL] = new Texture();	// 満タンのHPのテクスチャ読み込み
	if (FAILED(m_pTexture[HEART_FULL]->Create("Assets/Texture/HP_UI/HP_Full_2.png")))
	{
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error：";	//エラー箇所
		MessageBox(nullptr, (ErrorSpot + "HP_Full_2.png読み込み失敗").c_str(), "Error", MB_OK | MB_ICONERROR);								//エラー通知
#endif
	}

	m_pTexture[HEART_HALF] = new Texture();	// 半分のHPのテクスチャ読み込み
	if (FAILED(m_pTexture[HEART_HALF]->Create("Assets/Texture/HP_UI/HP_Half_2.png")))
	{
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error：";	//エラー箇所
		MessageBox(nullptr, (ErrorSpot + "HP_Half_2.png読み込み失敗").c_str(), "Error", MB_OK | MB_ICONERROR);								//エラー通知
#endif
	}

	m_pTexture[HEART_NONE] = new Texture();	// 空のHPのテクスチャ読み込み
	if (FAILED(m_pTexture[HEART_NONE]->Create("Assets/Texture/HP_UI/HP_Lost_2.png")))
	{
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error：";	//エラー箇所
		MessageBox(nullptr, (ErrorSpot + "HP_Lost_2.png読み込み失敗").c_str(), "Error", MB_OK | MB_ICONERROR);								//エラー通知
#endif
	}

	m_pTexture[HEART_FH_ANIM] = new Texture();	// 満タン→半分のHPのテクスチャ読み込み
	if (FAILED(m_pTexture[HEART_FH_ANIM]->Create("Assets/Texture/HP_UI/hp_FtoH_sprite_2.png")))
	{
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error：";	//エラー箇所
		MessageBox(nullptr, (ErrorSpot + "hp_FtoH_sprite_2.png読み込み失敗").c_str(), "Error", MB_OK | MB_ICONERROR);						//エラー通知
#endif
	}

	m_pTexture[HEART_HE_ANIM] = new Texture();	// 半分→空のHPのテクスチャ読み込み
	if (FAILED(m_pTexture[HEART_HE_ANIM]->Create("Assets/Texture/HP_UI/HP_HtoE_sprite_2.png")))
	{
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error：";	//エラー箇所
		MessageBox(nullptr, (ErrorSpot + "HP_HtoE_sprite_2.png読み込み失敗").c_str(), "Error", MB_OK | MB_ICONERROR);						//エラー通知
#endif
	}

}

/* ========================================
	デストラクタ関数
	-------------------------------------
	内容：破棄時に行う処理
	-------------------------------------
	引数：なし
	-------------------------------------
	戻値：なし
=========================================== */
CHP_UI::~CHP_UI()
{
	SAFE_DELETE(m_pTexture[HEART_FULL]);
	SAFE_DELETE(m_pTexture[HEART_HALF]);
	SAFE_DELETE(m_pTexture[HEART_NONE]);
	SAFE_DELETE(m_pTexture[HEART_FH_ANIM]);
	SAFE_DELETE(m_pTexture[HEART_HE_ANIM]);
}

/* ========================================
	更新関数
	-------------------------------------
	内容：HPの更新処理
	-------------------------------------
	引数：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CHP_UI::Update()
{
	if (m_nPlayerOldHp != *m_pPlayerHp)	// HPに変更があったら
	{
		// HP減少時のみアニメーション再生
		if (m_nPlayerOldHp > *m_pPlayerHp)
		{
			m_bPlayAnim = true;		// アニメ再生をON
		}

		m_nPlayerOldHp = *m_pPlayerHp;	// 現在のHPを格納

	}

	if (m_bPlayAnim)	// アニメーション再生がONなら
	{
		m_nCnt++;	// カウントを進める

		if (m_nCnt > SWITCH_HP_ANIM)	// 一定時間経過したら切り替える
		{
			m_nCnt = 0;		// カウントを初期化

			m_fUVposX = (HP_ANIM_SIZEX) * m_nCntWidth;		// 横方向のUV座標計算
			m_fUVposY = (HP_ANIM_SIZEY) * m_nCntHeight;		// 縦方向のUV座標計算

			++m_nCntWidth;		// 横方向に座標を1つ進める
			if (m_nCntWidth == HP_ANIM_WIDTH_NUM_MAX)	// テクスチャの右端まで行ったら 
			{
				m_nCntWidth = 0;	// カウントを初期化
				++m_nCntHeight;		// 縦に1進める
			}
			if (m_nCntHeight == HP_ANIM_HEIGHT_NUM_MAX)		// テクスチャの下端まで行ったr
			{ 
				m_nCntHeight = 0;	// カウントを初期化
				m_nCntHeight = 0; 
				m_bPlayAnim = false;	// アニメーション再生をOFF
			}
		}
	}
}

/* ========================================
	描画関数
	-------------------------------------
	内容：HPの描画処理
	-------------------------------------
	引数：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CHP_UI::Draw()
{
	int hpNum = 0;	// 何個目のハートか(表示位置調整用)
	// 空のハートを表示
	for (int i = 1; i <= PLAYER_HP; i++)
	{
		// 奇数個目のライフかどうか
		if (i % 2 != 0)
		{	
			// 現在の表示ライフ位置が最大値でない(最大値が奇数の場合はハートを表示する(例:HP3の場合は5個表示する))
			if (i != PLAYER_HP)
			{
				continue;

			}
		}

		DirectX::XMFLOAT4X4 mat[3];

		// ワールド行列はXとYのみを考慮して作成
		DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(HP_UI_POS.x + (hpNum * DRAW_WIDTH), HP_UI_POS.y, 0.0f);	// ワールド行列（必要に応じて変数を増やしたり、複数処理を記述したりする）
		DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

		// ビュー行列は2Dだとカメラの位置があまり関係ないので、単位行列を設定する
		DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

		// プロジェクション行列には2Dとして表示するための行列を設定する
		// この行列で2Dのスクリーンの大きさが決まる
		DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(VIEW_LEFT, VIEW_RIGHT, VIEW_BOTTOM, VIEW_TOP, NEAR_Z, FAR_Z);	// 平衡投影行列を設定
		DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));

		// スプライトの設定
		Sprite::SetWorld(mat[0]);
		Sprite::SetView(mat[1]);
		Sprite::SetProjection(mat[2]);
		Sprite::SetSize(DirectX::XMFLOAT2(HP_UI_SIZE.x, -HP_UI_SIZE.y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
		Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
		Sprite::SetTexture(m_pTexture[HEART_NONE]);
		Sprite::Draw();


		hpNum++;	// 表示したら位置を進める
	}

	HEART_STATE tex;	// 表示画像を指定する
	int hpCnt = 0;		// 偶数の時に進める(表示位置調整用)
	for (int i = 1; i <= *m_pPlayerHp; i++)
	{
		DirectX::XMFLOAT4X4 mat_Full[3];

		// ワールド行列はXとYのみを考慮して作成
		DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(HP_UI_POS.x + (hpCnt * DRAW_WIDTH), HP_UI_POS.y, 0.0f);	// ワールド行列（必要に応じて変数を増やしたり、複数処理を記述したりする）
		DirectX::XMStoreFloat4x4(&mat_Full[0], DirectX::XMMatrixTranspose(world));

		// ビュー行列は2Dだとカメラの位置があまり関係ないので、単位行列を設定する
		DirectX::XMStoreFloat4x4(&mat_Full[1], DirectX::XMMatrixIdentity());

		// プロジェクション行列には2Dとして表示するための行列を設定する
		// この行列で2Dのスクリーンの大きさが決まる
		DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(VIEW_LEFT, VIEW_RIGHT, VIEW_BOTTOM, VIEW_TOP, NEAR_Z, FAR_Z);	// 平衡投影行列を設定
		DirectX::XMStoreFloat4x4(&mat_Full[2], DirectX::XMMatrixTranspose(proj));

		// 奇数の場合
		if (i % 2 != 0)
		{
			tex = HEART_HALF;	// ハート半分
		}
		// 偶数の場合
		else
		{
			tex = HEART_FULL;	// ハート1個分
			hpCnt++;

		}

		// スプライトの設定
		Sprite::SetWorld(mat_Full[0]);
		Sprite::SetView(mat_Full[1]);
		Sprite::SetProjection(mat_Full[2]);
		Sprite::SetSize(DirectX::XMFLOAT2(HP_UI_SIZE.x, -HP_UI_SIZE.y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
		Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
		Sprite::SetTexture(m_pTexture[tex]);
		Sprite::Draw();


	}

	if (m_bPlayAnim)	// アニメーション再生がONなら描画する
	{
		DirectX::XMFLOAT4X4 mat_Anim[3];

		// ワールド行列はXとYのみを考慮して作成
		DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(HP_UI_POS.x + (hpCnt * DRAW_WIDTH), HP_UI_POS.y, 0.0f);	// ワールド行列（必要に応じて変数を増やしたり、複数処理を記述したりする）
		DirectX::XMStoreFloat4x4(&mat_Anim[0], DirectX::XMMatrixTranspose(world));

		// ビュー行列は2Dだとカメラの位置があまり関係ないので、単位行列を設定する
		DirectX::XMStoreFloat4x4(&mat_Anim[1], DirectX::XMMatrixIdentity());

		// プロジェクション行列には2Dとして表示するための行列を設定する
		// この行列で2Dのスクリーンの大きさが決まる
		DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(VIEW_LEFT, VIEW_RIGHT, VIEW_BOTTOM, VIEW_TOP, NEAR_Z, FAR_Z);	// 平衡投影行列を設定
		DirectX::XMStoreFloat4x4(&mat_Anim[2], DirectX::XMMatrixTranspose(proj));


		// スプライトの設定
		Sprite::SetWorld(mat_Anim[0]);
		Sprite::SetView(mat_Anim[1]);
		Sprite::SetProjection(mat_Anim[2]);
		Sprite::SetSize(DirectX::XMFLOAT2(DRAW_ANIM_HEIGHT, -DRAW_ANIM_WIDTH));
		Sprite::SetUVPos(DirectX::XMFLOAT2(m_fUVposX, m_fUVposY));				
		Sprite::SetUVScale(DirectX::XMFLOAT2(HP_ANIM_SIZEX, HP_ANIM_SIZEY));
		if (*m_pPlayerHp % 2 == 0)	// HPが偶数か奇数かによって表示するテクスチャを変更する
		{
			Sprite::SetTexture(m_pTexture[HEART_HE_ANIM]);
		}
		else
		{
			Sprite::SetTexture(m_pTexture[HEART_FH_ANIM]);
		}
		Sprite::Draw();
	}

}

void CHP_UI::SetPlayerHp(const int * pPlayerHp)
{
	m_pPlayerHp = pPlayerHp;
}


