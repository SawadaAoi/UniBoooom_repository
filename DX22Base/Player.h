/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	player用ヘッダ
	------------------------------------
	player.h
	------------------------------------
	作成者
		山本凱翔
	変更履歴
	・2023/11/03 h,作成 山本凱翔
	・2023/11/06 ダメージ処理追加,コメント追加 山本凱翔
	・2023/11/08 Pos.hをインクルード /山下凌佑
	・2023/11/08 当たり判定用の球体m_sphereを追加 /山下凌佑
	・2023/11/08 プレイヤー座標を入れる変数をTTriTypeからTPosに変更 /山下凌佑
	・2023/11/09 GetPosAddress追加、カメラ追加 髙木駿輔
	・2023/11/09 プレイヤーの無敵時間をカウントの変数と無敵状態のフラグを追加 山下凌佑
	・2023/11/09 プレイヤーの無敵状態を取得するゲット関数を追加 山下凌佑
	・2023/11/11 プレイヤーの点滅処理追加 Tei
	・2023/11/14 SphereInfoの変更に対応 Takagi
	・2023/11/14 キーボードの入力移動処理内容を適切な形に変更 Sawada
	・2023/11/15 Objectクラスを継承したので修正　yamamoto
	・2023/11/19 移動のSEを再生 yamashita
	・2023/11/19 被ダメージ時とハンマーを振るSEを再生 yamashita
	・2023/11/19 サウドファイル読み込み関数を作成 yamashita
	・2023/11/27 ハンマー振り間隔用カウント追加 Tei	
	・2023/11/28 ダメージ処理に受けるダメージ量を追加 Sawada
	・2023/12/03 カメラの更新を担うため、ポインタのconstを仕方なく除去 takagi
	・2023/12/14 アニメーション用の列挙を作成 yamashita
	・2023/12/14 SE用の列挙を作成 yamashita
	・2023/12/15 SEを外から再生できるように変更 yamashita
	・2023/12/15 回復SE追加 yamashita
	・2024/01/25 待機モーションを変更 takagi
	・2024/01/26 警告SE追加 suzumura
	・2024/01/28 死亡モーション追加 Sawada
	・2024/01/30 プレイヤー移動エフェクト用変数、関数追加
	・2024/02/02 汗エフェクト処理追加 Tei
	・2024/02/09 カメラ削除 takagi

========================================== */
#ifndef __PLAYER_H__
#define __PLAYER_H__

// =============== インクルード ===================
#include "Shader.h"
#include "hammer.h"
#include "Geometry.h"
#include "SphereInfo.h"
#include "Transform3d.h"
#include "Pos3d.h"
#include "Object.h"
#include "Sound.h"
#include "Model.h"
#include "Shadow.h"
#include "AnimeModel.h"
#include "FrameCnt.h"
#include "WalkEffectManager.h"
#include "SweatEffectManager.h"

// =============== クラス定義 =====================
class CPlayer: public CObject
{
public:
	// === 列挙 ===
	enum SE
	{
		SE_SWING,		// ハンマーを振るSE
		SE_RUN,			// 移動のSE
		SE_DAMAGED,		// 被ダメージのSE
		SE_HIT_HAMMER,	// ハンマーとスライムの接触SE
		SE_HEAL,		// 回復SE
		SE_WARNING,		// 残り体力１
		SE_CHARGED,		// チャージ完了時

		SE_MAX			// SEの総数
	};

	// ===列挙===
	enum PLAYER_MOTION
	{
		MOTION_PLAYER_STOP,		// 待機
		MOTION_PLAYER_MOVE,		// 移動
		MOTION_PLAYER_SWING,	// ハンマーを振る
		MOTION_PLAYER_CHARGE,	// チャージ状態
		MOTION_PLAYER_DIE,		// 死亡

		MOTION_PLAYER_MAX,		//モーションの総数
	};

	enum PLAYER_CHARGE_STATE {
		PLAYER_CHARGE_NONE,
		PLAYER_CHARGING,
		PLAYER_CHARGED,
		

	};

private:
	// ===定数定義===========
	const int CNT_START_WAIT = 10;	//待機モーションを始めるまでの時間
public:
	// ===プロトタイプ宣言===
	CPlayer();		//コンストラクタ
	~CPlayer();		//デストラクタ

	void Update();	//更新
	void Draw();	//描画
	void Damage(int DmgNum);	//自身のHPを減らす
	
	void DamageAnimation();
	void MoveCheck();
	void LoadSound();	//サウンド読み込み関数
	void PlaySE(SE se, float volume = 1.0f);
	void Healing();
	void CheckCharge();
	void EffectStart();
	void UpdateEffect();

	// ゲット関数
	tagSphereInfo GetHammerSphere();	//当たり判定を取るためゲッター
	TPos3d<float>* GetPosAddress();
	CHammer* GetHammerPtr();
	bool GetSafeTime();					//当たり判定があるかの確認
	int* GetHpPtr();
	bool GetDieFlg() const;
	bool GetAttackFlg();
	bool GetCharge();

	// セット関数
	void SetSweatEffectMng(CSweatEffectManager* pSweatefcMng);

private:
	void MoveKeyboard();	// キーボード用入力移動
	void MoveController();	// コントローラ用入力移動
	void MoveSizeInputSet(TPos3d<float> fInput);
	void DisplaySweatEffect();

	// ===プロトタイプ宣言===
	void LoadAnime();	//アニメーション読み込み関数

	// ===メンバ変数宣言=====
	TPos3d<float> m_fMove;				// 移動量
	AnimeModel* m_pModel;				// プレイヤーのモデル

	CHammer* m_pHammer;					// ハンマークラスのポインタ(プレイヤーが管理する)

	CShadow* m_pShadow;
	CFrameCnt* m_pWaitFrameCnt;				// 待機モーション用フレームカウントダウン
	CWalkEffectManager* m_pWalkEffectMng;	// プレイヤー移動エフェクト用
	CSweatEffectManager* m_pSweatEffectMng;

	int m_nHp;							// プレイヤーの体力
	bool m_bDieFlg;						// プレイヤー死亡フラグ(trueの場合死亡)

	bool m_bAttackFlg;					// 攻撃中かどうかのフラグ

	int m_nSafeTimeCnt;					// プレイヤーの無敵時間をカウント
	bool m_bSafeTimeFlg;				// プレイヤーの無敵状態のフラグ(当たり判定をOFF)

	bool m_DrawFlg;						// プレイヤーがダメージを受けたら点滅するフラグ(trueの場合表示)
	int m_FlashCnt;						// 点滅の時間の長さ

	int m_nWalkSECnt;					// プレイヤーの移動によるSEの間隔

	bool m_bHumInvFlg;					// ハンマー間隔時間フラグ
	float m_fHumInvCnt;					// ハンマー間隔時間カウント

	bool m_bDieInvFlg;					// 死亡猶予時間フラグ
	float m_fDieInvCnt;					// 死亡猶予時間カウント

	float m_fRotate_x;					// プレイヤーの表示用傾き
	float m_fChargeCnt;					// プレイヤーのチャージハンマーのカウント
	bool m_bCharge;						// チャージが完了しているか

	int m_nWalkEffeCnt;					// 歩き煙エフェクトの表示間隔加算値
	int m_nSweatEffeCnt;				// 汗エフェクトの表示間隔加算値
	int m_nSwingFastCnt;				// ハンマーを振る時間の加算間隔

	//=====SE関連=====
	XAUDIO2_BUFFER* m_pSE[SE_MAX];
	IXAudio2SourceVoice* m_pSESpeaker[SE_MAX];
	const std::string m_sSEFile[SE_MAX] = {
		"Assets/Sound/SE/Swing.mp3",			//ハンマーを振る
		"Assets/Sound/SE/Run.mp3",				//移動のSE
		"Assets/Sound/SE/PlayerDamage.mp3",		//プレイヤーの被ダメージ時
		"Assets/Sound/SE/HammerHit.mp3",		//ハンマーとスライムの接触SE
		"Assets/Sound/SE/HealSE.mp3",			//回復アイテム取得時
		"Assets/Sound/SE/Warning.mp3",			//残りHPが１の時
		"Assets/Sound/SE/charge.mp3"			//チャージ完了
	};

	//=====アニメーション関連=====
	const std::string m_sAnimeFile[MOTION_PLAYER_MAX] = {	//アニメーションのファイル
		"Assets/Model/player/wait_end.FBX",			//待機
		"Assets/Model/player/Dash.FBX",				//移動
		"Assets/Model/player/pow.FBX",				//スイング
		"Assets/Model/player/down.fbx",				//死亡
	};			

	//エフェクト初期化
	Effekseer::EffectRef m_chargeEfc = LibEffekseer::Create("Assets/Effect/charge/charge.efkefc");
	Effekseer::Handle m_chgEfcHandle;
	
	PLAYER_CHARGE_STATE m_ChargeState;
};

#endif // !__PLAYER_H__