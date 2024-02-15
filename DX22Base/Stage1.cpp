/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ステージ1実装
	---------------------------------------
	Stage1.cpp

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
	・2024/01/25 ヒットエフェクト関係の処理追加 Tei
	・2024/01/30 プレイヤー移動エフェクト関係の処理追加 Tei
	・2024/02/02 汗エフェクト処理追加 Tei
	・2024/02/05 ゲーム終了間際の加算スコアがトータルスコアに反映されるように(改) sawada
	・2024/02/09 GetType()関数削除・カメラ削除 takagi

========================================== */

// =============== インクルード ===================
#include "Stage1.h"	//自身のヘッダ
#include "CameraChase.h"
#include "Input.h"
#include "HitStop.h"	//ヒットストップ
#include "Fade.h"

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
	:CStage(CUIStageManager::E_STAGE_1)	//親関数呼び出し
{
	m_pFloor = new CFloor(m_pPlayer->GetPosAddress(), CFloor::Stage1);	// 床生成

	m_nStageNum = STAGE_NUM;
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

	// =============== 終了 =====================
	SAFE_DELETE(m_pFloor);
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

