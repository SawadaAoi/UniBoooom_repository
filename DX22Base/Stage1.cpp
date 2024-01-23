/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ステージ1実装
	---------------------------------------
	Stage1.cpp
	---------------------------------------
	作成者
			takagi
			nieda

	変更履歴
	・2023/11/05 制作 takagi
	・2023/11/07 コメント修正 takagi
	・2023/11/16 Prot.cpp→Stage1.cpp takagi
	・2023/11/20 SceneGameから移植 nieda
	・2023/11/21 ゲーム開始時テクスチャ表示 nieda
	・2023/11/22 動くよう足りない変数など追加 nieda
	・2023/11/27 バグ修正 takagi
	・2023/11/29 ヒットストップ仕様変更対応 takagi
	・2023/12/03 カメラ更新の記述改訂 takagi
	・2023/12/05 ステージにポーズ実装 takagi
	・2023/12/06 pose→pause修正、ポーズ文字表示 takagi
	・2023/12/07 ステージ→リザルト遷移方法切り替え実装 nieda
	・2023/12/07 ビュー行列取得にカメラ使用 takagi
	・2023/12/08 リザルトシーン遷移用に処理追加 takagi
	・2023/12/12 メンバ変数を親クラスに移動 yamashita
	・2023/12/14 BGMの管理をSceneManagerに移動 yamashita
	・2023/12/15 ゲームスタート表示を書き変え nieda
	・2023/12/18 デバッグモード削除反映 takagi
	・2024/01/01 親コンストラクタ呼び出し takagi
	・2024/01/15 GameFinish()関数修正・RecordData()関数追加 takagi
	・2024/01/20 リファクタリング takagi
	・2024/01/21 コメント改修 takagi
	・2024/01/23 親関数呼出 takagi

	========================================== */

// =============== インクルード ===================
#include "Stage1.h"	//自身のヘッダ
#include "CameraChase.h"
#include "Input.h"
#include "HitStop.h"	//ヒットストップ
#include "Fade.h"
#include "ControllMap.h"	//マップ操作
#include <algorithm>

// =============== 定数・マクロ定義 ===================
const int STAGE_NUM = 1;	//ステージ番号

/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CStage1::CStage1()
	:CStage()	//親関数呼び出し
{
	// =============== 動的確保 =====================
	if (m_p3dObject.find(E_3D_PLAYER) != m_p3dObject.end() && m_p3dObject.at(E_3D_PLAYER) &&
		typeid(*m_pCamera).hash_code() == typeid(CCameraChase).hash_code() &&
		typeid(*m_p3dObject.at(E_3D_PLAYER)).hash_code() == typeid(CPlayer).hash_code())	//アクセスチェック・ヌルチェック・型チェック
	{
		m_p3dObject.emplace(E_3D_FLOOR, new CFloor(static_cast<CPlayer*>(m_p3dObject.at(E_3D_PLAYER))->GetPosAddress(), CFloor::Stage1));	// 床生成
	}

	// =============== 初期化 =====================
	if (m_p3dObject.find(E_3D_PLAYER) != m_p3dObject.end() && m_p3dObject.at(E_3D_PLAYER) &&
		typeid(*m_p3dObject.at(E_3D_PLAYER)).hash_code() == typeid(CPlayer).hash_code())	//アクセスチェック・ヌルチェック・型チェック
	{
		m_p3dObject.at(E_3D_FLOOR)->SetCamera(m_pCamera);	//カメラ登録
	}
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
CStage1::~CStage1()
{
	// =============== 記録 =====================
	RecordData();	//データ記録
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
void CStage1::Update()
{
	// =============== 更新 ===================
	if (ACCESS_NULL_TYPE_CHECK(m_p2dObjectOnScreen, E_2D_ON_SCREEN_OPENING, typeid(CStartText).hash_code()) && 
		static_cast<CStartText*>(m_p2dObjectOnScreen.at(E_2D_ON_SCREEN_OPENING))->GetAnimFlg())	// シーン遷移後ゲームを開始するか判定
	{
		m_p2dObjectOnScreen.at(E_2D_ON_SCREEN_OPENING)->Update();	//一部更新
	}
	else
	{
		if (m_pPause)	//ヌルチェック
		{
			m_pPause->Update();	//ポーズ更新
			if (m_pPause->IsPause())	//ポーズ中
			{
				return;	//処理中断
			}
			m_bFinish = m_pPause->IsFin();	//終了判定
		}

		// =============== 関数呼出 ===================
		CStage::Update();	//親関数呼び出し
	}
}

/* ========================================
	描画関数
	----------------------------------------
	内容：描画処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CStage1::Draw()
{
	// =============== 関数呼出 ===================
	CStage::Draw();	//親関数呼び出し

	// =============== 描画 ===================
	if (m_pPause)	//ヌルチェック
	{
		m_pPause->Draw();	// ポーズ描画
	}
}

/* ========================================
	次シーンゲッタ
	----------------------------------------
	内容：遷移したいシーンが何かを示す
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：遷移先シーンの種類
=========================================== */
CStage1::E_TYPE CStage1::GetNext() const
{
	// =============== 提供 ===================
	return CStage1::E_TYPE_RESULT;	//遷移先シーンの種類
}

/* ========================================
	データ記録関数
	----------------------------------------
	内容：リザルト用にデータ記録
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CStage1::RecordData()
{
	// =============== 退避 =====================
	if (ACCESS_NULL_TYPE_CHECK(m_p2dObjectOnScreen, E_2D_ON_SCREEN_FINISH, typeid(CTotalScore).hash_code()))	//アクセス・ヌル・型チェック
	{
		m_Data.nTotalScore = static_cast<CTotalScore*>(m_p2dObjectOnScreen.at(E_2D_ON_SCREEN_FINISH))->GetTotalScore();	//スコア退避
	}

	// =============== データ登録 =====================
	if (m_Data.nHighScore[STAGE_NUM - 1] < m_Data.nTotalScore)	// ハイスコアを更新しているか？
	{
		m_Data.nHighScore[STAGE_NUM - 1] = m_Data.nTotalScore;	// ハイスコア更新
	}
	if (ACCESS_NULL_TYPE_CHECK(m_p2dObjectOnScreen, E_2D_ON_SCREEN_TIMER, typeid(CTimer).hash_code()))	//アクセス・ヌル・型チェック
	{
		m_Data.nTotalScore = static_cast<CTimer*>(m_p2dObjectOnScreen.at(E_2D_ON_SCREEN_TIMER))->GetErapsedTime();	// 経過時間退避
	}
	if (ACCESS_NULL_TYPE_CHECK(m_p2dObjectOnScreen, E_2D_ON_SCREEN_COMBO, typeid(CCombo).hash_code()))	//アクセス・ヌル・型チェック
	{
		m_Data.nTotalScore = static_cast<CCombo*>(m_p2dObjectOnScreen.at(E_2D_ON_SCREEN_COMBO))->GetMaxCombo();		// 最大コンボ数退避
	}
	if (ACCESS_NULL_TYPE_CHECK(m_p2dObjectOnScreen, E_2D_ON_SCREEN_COMBO, typeid(CStageFinish).hash_code()))	//アクセス・ヌル・型チェック
	{
		m_Data.nTotalScore = static_cast<CStageFinish*>(m_p2dObjectOnScreen.at(E_2D_ON_SCREEN_COMBO))->GetClearFlg();	// ゲームクリアしたか
	}
	if (ACCESS_NULL_TYPE_CHECK(m_pObjectManager, E_MANAGER_SLIME, typeid(CSlimeManager).hash_code()))	//アクセス・ヌル・型チェック
	{
		m_Data.nTotalKill = static_cast<CSlimeManager*>(m_pObjectManager.at(E_MANAGER_SLIME))->GetTotalKillCnt();	// 総討伐数退避
		static_cast<CSlimeManager*>(m_pObjectManager.at(E_MANAGER_SLIME))->GetKillCntArray(m_Data.nKill);			// スライム別討伐数退避
	}
	m_Data.nStageNum = STAGE_NUM;	// プレイしたステージ番号
}