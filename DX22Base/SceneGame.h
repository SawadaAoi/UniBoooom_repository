/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ゲームシーン用ヘッダ
	------------------------------------
	SceneGame.h
	------------------------------------
	作成者 澤田

	変更履歴
	・2023/11/08 コメント追加と、無駄な箇所を削除
	・2023/11/09 カメラの移動が分かるように地面追加した Takagi
	・2023/11/11 スライム同士が重ならない処理を追加 Yamashita
	・2023/11/19 サウンドファイルの読み込み関数を追加 Yamashita
	・2023/11/19 サウンド用のメンバ変数を追加 Yamashita
	・2023/11/21 コンボ用のメンバ変数を追加 Sawada
	・2023/11/21 ボス用の当たり判定を多数追加 Suzumura

========================================== */
#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__

// =============== インクルード ===================
#include "Model.h"
#include "Shader.h"
#include "Camera.h"
#include "Geometry.h"
#include "SlimeManager.h"
#include "Collision.h"
#include "Player.h"
#include "ExplosionManager.h"
#include "DirectWrite.h"
#include "Timer.h"
#include "Floor.h"
#include "StageFinishUI.h"
#include "Combo.h"
#include "Fade.h"

// =============== クラス定義 =====================
class SceneGame
{
public:
	// ===メンバ関数宣言===
	SceneGame();
	~SceneGame();
	void Update(float tick);
	void Draw();

	void SceneGameCollision();
	void PlayerSlimeCollision();
	void PlayerBossCollision();		//追加
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
	void SetDirectWrite(DirectWrite* pDirectWrite);
private:
	void LoadSound();	//サウンドファイルの読み込み
	// ===メンバ変数宣言===
	VertexShader* m_pVs;
	CCamera* m_pCamera;
	CPlayer* m_pPlayer;
	CGeometry* m_pBox;
	CSlimeManager* m_pSlimeMng;
	CCOLLISION* m_pCollision;
	CExplosionManager* m_pExplosionMng;
	CTimer* m_pTimer;
	CCombo* m_pCombo;
	CFloor* m_pFloor;
	CStageFinish* m_pStageFin;
	CFade* m_pFade;

	XAUDIO2_BUFFER* m_pBGM;							//BGMの音声データ
	XAUDIO2_BUFFER* m_pSEHitHammer;					//SEの音声データ
	IXAudio2SourceVoice* m_pSpeaker;				//BGMを聞き取る側
	IXAudio2SourceVoice* m_pSEHitHammerSpeaker;		//SEを聞き取る側

};

#endif // __SCENE_GAME_H__