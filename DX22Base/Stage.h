/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ステージ用抽象クラス定義
	---------------------------------------
	Stage.h

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
	・2023/12/28 BattleData格納処理をまとめた関数を追加	Sawada
	・2024/01/01 ステージ分岐 Takagi
	・2024/01/15 GameFinish()関数の引数修正・RecordData()関数追加 Takagi
	・2024/01/25 ヒットエフェクト関係の変数、ヘッダー追加 Tei

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
#include "HitSlimeEffectManager.h"
#include "BattleData.h"			//メンバのヘッダ
#include "GameStartText.h"

// =============== デバッグモード ===================
#if _DEBUG
#define MODE_COORD_AXIS (true)	//座標軸映すかどうか
#define SCENE_TRANSITION(false)	// シーン遷移をボタン押下か自動化を切り替え（trueは自動)
#endif

// =============== クラス定義 =====================
class CStage :public CScene	//シーン
{
public:
	// =============== プロトタイプ宣言 ===============
	CStage(CUIStageManager::E_STAGE_NUM eStage);	//コンストラクタ
	virtual ~CStage();								//デストラクタ
	//virtual void Update();				//更新
	//virtual void Draw() const;			//描画	
	//virtual E_TYPE GetType() const = 0;	//自身の種類ゲッタ
	void Collision();


protected:
	virtual void RecordData() = 0;	//データ記録
	void GameFinish();
	void PlayerSlimeCollision();
	void PlayerBossCollision();		//追加
	void PlayerHealItemCollision();
	void HammerSlimeCollision();
	void HammerBossCollision();		//追加
	void SlimeSlimeCollision();
	void SlimeBossCollision();		//追加
	void BossSlimeCollision();		//追加
	void BossBossCollision();		//追加
	void ExplosionBossCollision();	//追加
	void ExplosionSlimeCollision();
	void SlimeSlimeNormalMoveCollision();
	void SlimeBossNormalMoveCollision();		//追加
	void BossSlimeNormalMoveCollision();		//追加
	void BossBossNormalMoveCollision();			//追加
	// ===メンバ変数宣言===
	VertexShader* m_pVs;
	CPlayer* m_pPlayer;
	CGeometry* m_pBox;
	CSlimeManager* m_pSlimeMng;
	CCOLLISION* m_pCollision;
	CExplosionManager* m_pExplosionMng;
	CFloor* m_pFloor;
	Texture* m_pTexture;
	CScoreOHManager* m_pScoreOHMng;
	CHealItemManager* m_pHealItemMng;
	CPause* m_pPause;						//ポーズ画面
	CUIStageManager* m_pUIStageManager;
	BattleData m_Data;	//戦闘データ記録用変数
	CStartText* m_pStartText;	// ゲームスタート描画
	CHitSlimeEffectManager* m_pHitEffectMng;
	
	//サウンド
	XAUDIO2_BUFFER* m_pSEHitHammer;
	IXAudio2SourceVoice* m_pSEHitHammerSpeaker;

private:
	void LoadSE();
};	//ステージ

#endif	//!__STAGE_H__