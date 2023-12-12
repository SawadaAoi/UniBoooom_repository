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
#include "Geometry.h"
#include "HP_UI.h"
#include "DirectWrite.h"
#include "Timer.h"
#include "Fade.h"
#include "Pause.h"				//メンバのヘッダ
#include "BossGauge.h"
#include "ScoreOHManager.h"
#include "TotalScore.h"
#include "Sound.h"
#include "UIStageManager.h"
#include "BattleData.h"			//メンバのヘッダ

// =============== クラス定義 =====================
class CStage :public CScene	//シーン
{
public:
	// =============== プロトタイプ宣言 ===============
	CStage();							//コンストラクタ
	virtual ~CStage();					//デストラクタ
	//virtual void Update();				//更新
	//virtual void Draw() const;			//描画	
	//virtual E_TYPE GetType() const = 0;	//自身の種類ゲッタ
	void Collision();
protected:
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
	//CTimer* m_pTimer;
	//CCombo* m_pCombo;
	CFloor* m_pFloor;
	CFade* m_pFade;
	//CStageFinish* m_pStageFin;
	Texture* m_pTexture;
	CScoreOHManager* m_pScoreOHMng;
	////CTotalScore* m_pTotalScore;
	//CHP_UI* m_pHpMng;
	//CBossgauge* m_pBossgauge;
	CHealItemManager* m_pHealItemMng;
	CPause* m_pPause;						//ポーズ画面
	CUIStageManager* m_pUIStageManager;
	BattleData m_Data;	//戦闘データ記録用変数

	int m_nNum;			// ゲームスタート表示カウント用
	float m_fSize;		// ゲームスタート表示のサイズ
	float m_fResize;	// ゲームスタート表示のサイズ変更用
	bool m_bStart;		// ゲームを開始させるか判定
	const int* m_pPlayerHp;		// プレイヤーHP取得用
	const int* m_pTimeCnt;		// 制限時間取得用

	TPos2d<float> m_fUVPos;	// UV座標保存用
	int m_nCntSwitch;	// アニメーション切り替えカウント用
	int m_nCntW;		// 横カウント用
	int m_nCntH;		// 縦カウント用
	bool m_bStartSign;		// スタート合図開始フラ


	//サウンド
	XAUDIO2_BUFFER* m_pSEHitHammer;
	IXAudio2SourceVoice* m_pSEHitHammerSpeaker;

private:
	void LoadSE();
};	//ステージ

#endif	//!__STAGE_H__