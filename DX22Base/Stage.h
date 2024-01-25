/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ステージ用抽象クラス定義
	---------------------------------------
	Stage.h
	---------------------------------------
	作成者
			takagi
			nieda

	変更履歴
	・2023/11/16 制作 takagi
	・2023/11/22 メンバ変数大量追加 nieda
	・2023/12/04 ポーズクラス追加・デストラクタ復活 takagi
	・2023/12/05 コメント修正 takagi
	・2023/12/06 pose→pause修正、ポーズ文字表示 takagi
	・2023/12/08 シーン遷移用に変数追加 takagi
	・2023/12/12 Stage1からメンバ変数を移動 yamashita
	・2023/12/14 BGMの管理をSceneManagerに移動 yamashita
	・2023/12/15 フェード削除 takagi
	・2023/12/16 不要な変数など削除 nieda
	・2023/12/28 BattleData格納処理をまとめた関数を追加	sawada
	・2024/01/01 ステージ分岐 takagi
	・2024/01/15 GameFinish()関数の引数修正・RecordData()関数追加 takagi
	・2024/01/19 GetType()関数削除・その他リファクタリング takagi
	・2024/01/20 リファクタリング続き takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __STAGE_H__	//Stage.hインクルードガード
#define __STAGE_H__

// =============== インクルード ===================
#include "Scene.h"				//親のヘッダ
#include "Shader.h"
#include "Collision.h"
#include "Player.h"
#include "SlimeManager.h"
#include "ExplosionManager.h"
#include "Floor.h"
#include "Timer.h"
#include "StageFinishUI.h"
#include "Combo.h"
#include "HP_UI.h"
#include "DirectWrite.h"
#include "Timer.h"
#include "Pause.h"				//メンバのヘッダ
#include "BossGauge.h"
#include "ScoreOHManager.h"
#include "TotalScore.h"
#include "Sound.h"
#include "UIStageManager.h"
#include "BattleData.h"			//メンバのヘッダ
#include "GameStartText.h"
#include "BossArrow.h"

// =============== クラス定義 =====================
class CStage :public CScene	//シーン
{
public:
	// ===プロトタイプ宣言===
	CStage();				//コンストラクタ
	virtual ~CStage();		//デストラクタ
	virtual void Update() override;	//更新
	virtual void Draw() const override;	//描画
	void Collision();		//当たり判定
protected:
	// ===メンバ変数宣言===
	CPause* m_pPause;							//ポーズ画面
	BattleData m_Data;							//戦闘データ記録用変数


	CHP_UI* m_pHpMng;
	CTimer* m_pTimer;
	CCombo* m_pCombo;
	CBossGauge* m_pBossGauge;
	CTotalScore* m_pTotalScore;
	CScoreOHManager* m_pScoreOHMng;
	CStageFinish* m_pStageFin;
	CBossArrow* m_pBossArrow;

	CFloor* m_pFloor;
	CPlayer* m_pPlayer;
	CGeometry* m_pBox;
	CSlimeManager* m_pSlimeMng;
	CCollision* m_pCollision;
	CExplosionManager* m_pExplosionMng;
	Texture* m_pTexture;
	CHealItemManager* m_pHealItemMng;
	CStartText* m_pStartText;	// ゲームスタート描画

	// ===プロトタイプ宣言===
	virtual void RecordData() = 0;	//データ記録
private:
	// ===プロトタイプ宣言===
	void PlayerSlimeCollision();			//プレイヤーとスライムの当たり判定
	void PlayerBossCollision();				//プレイヤーとボスの当たり判定
	void PlayerHealItemCollision();			//プレイヤーと回復アイテムの当たり判定
	void HammerSlimeCollision();			//ハンマーと回復アイテムの当たり判定
	void HammerBossCollision();				//ハンマーとボスの当たり判定
	void SlimeSlimeCollision();				//スライムとスライムの当たり判定
	void SlimeBossCollision();				//スライムとボスの当たり判定
	void BossSlimeCollision();				//ボスとスライムの当たり判定
	void BossBossCollision();				//ボスとボスの当たり判定
	void ExplosionBossCollision();			//爆発とボスの当たり判定
	void ExplosionSlimeCollision();			//爆発とスライムの当たり判定
	void SlimeSlimeNormalMoveCollision();	//スライムとスライムの重複判定
	void SlimeBossNormalMoveCollision();	//スライムからボスへの重複判定
	void BossSlimeNormalMoveCollision();	//ボスからスライムへの重複判定
	void BossBossNormalMoveCollision();		//ボスからボスへの重複判定
};	//ステージ

#endif	//!__STAGE_H__