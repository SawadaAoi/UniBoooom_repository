/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	タイトル用コマンド実装
	---------------------------------------
	TitleCommand.cpp

	作成者	takagi

	変更履歴
	・2023/12/16 制作 takagi
	・2023/12/18 サイズ変更*2.0f→*3.5f takagi
	・2024/02/05 リファクタリング takagi

========================================== */

// =============== インクルード ===================
#include "TitleCommand.h"	//自身のヘッダ

// =============== 定数定義 ===================
const unsigned int ALPHA_FRAME = 30;	//透明度変化の片道時間

// =============== グローバル変数宣言 ===================
bool CTitleCommand::m_bCntUpDwn = true;																			//カウントアップ・ダウン切換フラグ
std::shared_ptr<CFrameCnt> CTitleCommand::m_pAlphaCnt = std::make_shared<CFrameCnt>(ALPHA_FRAME, m_bCntUpDwn);	//透明度変化用カウンタ

/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：const E_STATE& eInitState：初期状態
	----------------------------------------
	戻値：なし
=========================================== */
CTitleCommand::CTitleCommand(const E_STATE& eInitState)
	:m_eTexNo(eInitState)	//テクスチャ番号
	,m_unAnimeNo(0)			//アニメーションコマ番号
	,m_pAnimeInterval(0)	//アニメーション間隔
{
	// =============== 初期化 ===================
#if _DEBUG
	if (MAP_SCALE.find(m_eTexNo) == MAP_SCALE.end())	//アクセスチェック
	{
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error：";	//エラー箇所
		MessageBox(nullptr, (ErrorSpot + "連想コンテナのキーが不足しています").c_str(), "Error", MB_OK | MB_ICONERROR);						//エラー通知
	}
#endif	//!_DEBUG
	m_fScale = MAP_SCALE.at(m_eTexNo);	//拡縮
	SetSize(m_fScale);					//大きさ初期化
#if _DEBUG
	if (MAP_MAX_ANIMATION_NUM.find(m_eTexNo) == MAP_MAX_ANIMATION_NUM.end())	//アクセスチェック
	{
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error：";	//エラー箇所
		MessageBox(nullptr, (ErrorSpot + "連想コンテナのキーが不足しています").c_str(), "Error", MB_OK | MB_ICONERROR);						//エラー通知
	}
#endif	//!_DEBUG
	SetUvScale({ 1.0f / static_cast<float>(E_STATE_MAX), 1.0f / static_cast<float>(MAP_MAX_ANIMATION_NUM.at(m_eTexNo)) });	//UV拡縮初期化
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
CTitleCommand::~CTitleCommand()
{
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
void CTitleCommand::Update()
{
	// =============== アニメーション番号更新 ===================
	if (!(m_pAnimeInterval && !m_pAnimeInterval->IsFin()))	//インターバル中でない
	{
		m_unAnimeNo++;																			//アニメーション番号進行
		m_pAnimeInterval.reset();																//削除
#if _DEBUG
		if (MAP_ANIMATION_INTERVAL.find(m_eTexNo) == MAP_ANIMATION_INTERVAL.end())	//アクセスチェック
		{
			std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error：";	//エラー箇所
			MessageBox(nullptr, (ErrorSpot + "連想コンテナのキーが不足しています").c_str(), "Error", MB_OK | MB_ICONERROR);						//エラー通知
		}
#endif	//!_DEBUG
		m_pAnimeInterval = std::make_shared<CFrameCnt>(MAP_ANIMATION_INTERVAL.at(m_eTexNo));	//インターバルリセット
	}
#if _DEBUG
	if (MAP_MAX_ANIMATION_NUM.find(m_eTexNo) == MAP_MAX_ANIMATION_NUM.end())	//アクセスチェック
	{
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error：";	//エラー箇所
		MessageBox(nullptr, (ErrorSpot + "連想コンテナのキーが不足しています").c_str(), "Error", MB_OK | MB_ICONERROR);						//エラー通知
	}
#endif	//!_DEBUG
	while (m_unAnimeNo > MAP_MAX_ANIMATION_NUM.at(m_eTexNo))	//定義域チェック
	{
		m_unAnimeNo -= MAP_MAX_ANIMATION_NUM.at(m_eTexNo);	//定義域に収める
	}

	// =============== UV移動 ===================
	SetUvOffset({ static_cast<float>(m_eTexNo) / static_cast<float>(E_STATE_MAX),
		static_cast<float>(m_unAnimeNo) / static_cast<float>(MAP_MAX_ANIMATION_NUM.at(m_eTexNo)) });	//UV座標移動

	// =============== 拡縮 ===================
	if (m_pFrameCnt && m_pfReScalingStartSize)	//ヌルチェック
	{
		// =============== 更新 ===================
		m_pFrameCnt->Count();	//カウント進行
#if _DEBUG
		if (MAP_SCALE.find(m_eTexNo) == MAP_SCALE.end())	//アクセスチェック
		{
			std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error：";	//エラー箇所
			MessageBox(nullptr, (ErrorSpot + "連想コンテナのキーが不足しています").c_str(), "Error", MB_OK | MB_ICONERROR);						//エラー通知
		}
#endif	//!_DEBUG
		m_fScale = (*m_pfReScalingStartSize - MAP_SCALE.at(m_eTexNo)) * m_pFrameCnt->GetRate() + MAP_SCALE.at(m_eTexNo);	//拡縮更新

		// =============== サイズ変更 ===================
		SetSize(m_fScale);	//拡縮調整

		// =============== 削除 ===================
		if (m_pFrameCnt->IsFin())	//カウント完了
		{
			m_pFrameCnt.reset();			//カウンタ削除
			m_pfReScalingStartSize.reset();	//大きさ退避情報削除
		}
	}

	// =============== 明滅 ===================
	if (E_STATE_SELECTED == m_eTexNo)	//選択状態
	{
		// =============== 透明度更新 =====================
		if (m_pAlphaCnt)	//ヌルチェック
		{
			m_pAlphaCnt->Count();				//カウント進行
			SetAlpha(m_pAlphaCnt->GetRate());	//選択状態のとき明滅する
			if (m_pAlphaCnt->IsFin())	//カウント完了
			{
				m_bCntUpDwn ^= 1;														//カウントアップダウン逆転
				m_pAlphaCnt.reset();													//カウンタ削除
				m_pAlphaCnt = std::make_shared<CFrameCnt>(ALPHA_FRAME, m_bCntUpDwn);	//カウントアップ・ダウン
			}
		}
	}

	// =============== 更新 ===================
	CTitleObj::Update();	//親の関数使用
}

/* ========================================
	状態変更関数
	----------------------------------------
	内容：自身の状態を変更
	----------------------------------------
	引数1：const E_STATE & eState：変化先の状態
	----------------------------------------
	戻値：なし
=========================================== */
void CTitleCommand::ChangeState(const E_STATE & eState)
{
	// =============== 状態遷移 ===================
	m_eTexNo = eState;	//テクスチャ番号切換

	// =============== 退避 ===================
	if (m_pfReScalingStartSize)	//ヌルチェック
	{
		// =============== 初期化 ===================
		*m_pfReScalingStartSize = m_fScale;	//大きさ退避
	}
	else
	{
		// =============== 動的確保 ===================
		m_pfReScalingStartSize = std::make_shared<TTriType<float>>(m_fScale);	//大きさ退避
	}

	// =============== 破棄 ===================
	if (m_pFrameCnt)	//ヌルチェック
	{
		m_pFrameCnt.reset();	//カウンタ削除
	}

	// =============== 動的確保 ===================
#if _DEBUG
	if (MAP_ANIMATION_FRAME.find(m_eTexNo) == MAP_ANIMATION_FRAME.end())	//アクセスチェック
	{
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error：";	//エラー箇所
		MessageBox(nullptr, (ErrorSpot + "連想コンテナのキーが不足しています").c_str(), "Error", MB_OK | MB_ICONERROR);						//エラー通知
	}
#endif	//!_DEBUG
	m_pFrameCnt = std::make_shared<CFrameCnt>(MAP_ANIMATION_FRAME.at(m_eTexNo));	//カウンタ確保
	
	// =============== 透明度リセット ===================
	if (E_STATE_SELECTED != m_eTexNo)	//選択状態でない
	{
		SetAlpha(1.0f);	//不透明
	}
}

/* ========================================
	決定アニメ再生確認関数
	----------------------------------------
	内容：決定アニメ再生済か確認する
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：決定アニメ再生完了でtrue, それ以外でfalse
=========================================== */
bool CTitleCommand::DesideAnimeFin()
{
	// =============== 検査 ===================
	if (E_STATE_DECIDE == m_eTexNo && !m_pFrameCnt)	//決定アニメ再生完了時
	{
		// =============== 提供 ===================
		return true;	//決定アニメ再生完了
	}
	// =============== 提供 ===================
	return false;	//決定アニメ再生未完了
}