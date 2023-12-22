/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ポーズコマンド実装
	---------------------------------------
	CommandPause.cpp

	作成者	takagi

	変更履歴
	・2023/12/10 制作 takagi
	・2023/12/16 コメント追加 takagi
	・2023/12/17 ゲームパラメータ無効化 takagi

========================================== */

// =============== インクルード ===================
#include "CommandPause.h"	//自身のヘッダ

// =============== 定数定義 ===================
const float AMPITUDE(25.0f);										//振幅
const float ANGLE_SPEED(DirectX::XMConvertToRadians(1.5f));			//単振動の角速度
const TDiType<float> UV_SCALE(1.0f / 3.0f, 1.0f);					//UV拡縮
const float COMMAND_WIDTH = 360.0f;									//コマンド縦幅
const float COMMAND_HEIGHT = 78.0f;									//コマンド横幅
const TDiType<float> SCALE_UNSELECT(COMMAND_WIDTH, COMMAND_HEIGHT);	//非選択時の最大拡縮率
const TDiType<float> SCALE_SELECT(SCALE_UNSELECT * 1.1f);			//選択時の最小拡縮率
const TDiType<float> SCALE_DESIDE(SCALE_UNSELECT * 1.2f);			//決定時の拡大率
const TDiType<float> ADD_SCALE(60.0f * 0.04f, 13.0f * 0.04f);		//拡縮率増加量
const int DISPLAY_DECIDE(15);										//決定テクスチャを表示する時間

/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：const int& nWaitTime：待機時間
	----------------------------------------
	戻値：なし
=========================================== */
CCommandPause::CCommandPause(const int& nWaitTime)
	:m_eTexNo(E_TEXTURE_UNSELECTED)	//テクスチャ番号
	,m_fScale(SCALE_UNSELECT)		//拡縮
	,m_pnTimer(nullptr)				//タイマー
	,CPauseObj(nWaitTime)			//委譲
{
	// =============== 初期化 ===================
	SetSize({ m_fScale.x, m_fScale.y, 0.0f });	//大きさ初期化
	SetUvScale(UV_SCALE);						//UV拡縮初期化
}

/* ========================================
	デストラクタ
	----------------------------------------
	内容：破棄時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CCommandPause::~CCommandPause()
{
	// =============== 終了 ===================
	SAFE_DELETE(m_pnTimer);	//タイマー削除
}

/* ========================================
	更新関数
	----------------------------------------
	内容：更新処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CCommandPause::Update()
{
	// =============== 更新 ===================
	CPauseObj::Update();	//親の関数使用

	// =============== UV移動 ===================
	SetUvOffset({ static_cast<float>(m_eTexNo) / static_cast<float>(E_TEXTURE_MAX), 0.0f });	//UV座標移動

	// =============== 状態分岐 ===================
	if (E_TEXTURE_DECIDE == m_eTexNo)	//決定状態
	{
		// =============== タイマー ===================
		if (m_pnTimer)	//ヌルチェック
		{
			if (--(*m_pnTimer) > 0)	//カウントダウン
			{
			}
			else
			{
				SAFE_DELETE(m_pnTimer);	//タイマ削除
				// =============== 状態管理 ===================
				m_eTexNo = E_TEXTURE_SELECTED;	//選択状態に戻す
			}
		}

	}
	else
	{
		// =============== サイズ管理 ===================
		if (E_TEXTURE_SELECTED == m_eTexNo)	//決定状態
		{
			m_fScale += ADD_SCALE;	//サイズ増加
			if (m_fScale.x > SCALE_SELECT.x)	//限界値チェック
			{
				m_fScale.x = SCALE_SELECT.x;	//補正
			}
			if (m_fScale.y > SCALE_SELECT.y)	//限界値チェック
			{
				m_fScale.y = SCALE_SELECT.y;	//補正
			}
		}
		else 
		{
			if (E_TEXTURE_UNSELECTED == m_eTexNo)	//決定状態
			{
				m_fScale -= ADD_SCALE;	//サイズ増加
				if (m_fScale.x < SCALE_UNSELECT.x)	//限界値チェック
				{
					m_fScale.x = SCALE_UNSELECT.x;	//補正
				}
				if (m_fScale.y < SCALE_UNSELECT.y)	//限界値チェック
				{
					m_fScale.y = SCALE_UNSELECT.y;	//補正
				}
			}
		}
	}

	// =============== サイズ変更 ===================
	SetSize(TPos3d<float>(m_fScale.x, m_fScale.y, 0.0f));	//拡縮調整
}

/* ========================================
	選択化関数
	----------------------------------------
	内容：表示を選択状態化する
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CCommandPause::Selected()
{
	// =============== 状態遷移 ===================
	m_eTexNo = E_TEXTURE_SELECTED;	//テクスチャ番号切換
}

/* ========================================
	非選択化関数
	----------------------------------------
	内容：表示を非選択状態化する
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CCommandPause::UnSelected()
{
	// =============== 状態遷移 ===================
	m_eTexNo = E_TEXTURE_UNSELECTED;	//テクスチャ番号切換
}

/* ========================================
	決定関数
	----------------------------------------
	内容：表示を決定状態化する
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CCommandPause::Decide()
{
	// =============== 状態遷移 ===================
	m_eTexNo = E_TEXTURE_DECIDE;	//テクスチャ番号切換
	m_fScale = SCALE_DESIDE;		//UV拡縮変更

	// =============== タイマー作成 ===================
	if (m_pnTimer)	//ヌルチェック
	{
		SAFE_DELETE(m_pnTimer);	//タイマ削除
	}
	m_pnTimer = new int(DISPLAY_DECIDE);	//動的確保
}