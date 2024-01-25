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
	・2023/01/25 待機モーションを変更 takagi

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
#include "Camera.h"
#include "Object.h"
#include "Sound.h"
#include "Model.h"
#include "Shadow.h"
#include "AnimeModel.h"
#include "FrameCnt.h"
// =============== クラス定義 =====================
class CPlayer
	: public CObject
{
public:
	// === 列挙 ===
	enum SE
	{
		SE_SWING,	//ハンマーを振るSE
		SE_RUN,			//移動のSE
		SE_DAMAGED,		//被ダメージのSE
		SE_HIT_HAMMER,	//ハンマーとスライムの接触SE
		SE_HEAL,

		SE_MAX			//SEの総数
	};
private:
	// ===定数定義===========
	const int CNT_START_WAIT = 100;	//待機モーションを始めるまでの時間
public:
	// ===プロトタイプ宣言===
	CPlayer();		//コンストラクタ
	~CPlayer();		//デストラクタ

	void Update();	//更新
	void Draw();	//描画
	void Damage(int DmgNum);	//自身のHPを減らす
	void MoveKeyboard();	// キーボード用入力移動
	void MoveController();	// コントローラ用入力移動
	void MoveSizeInputSet(TPos3d<float> fInput);
	void DamageAnimation();
	void MoveCheck();
	void LoadSound();	//サウンド読み込み関数
	void PlaySE(SE se, float volume = 1.0f);
	void Healing();

	// ゲット関数
	tagSphereInfo GetHammerSphere();	//当たり判定を取るためゲッター
	TPos3d<float>* GetPosAddress();
	CHammer* GetHammerPtr();
	bool GetCollide();							//当たり判定があるかの確認
	int* GetHpPtr();
	// セット関数
	void SetCamera(CCamera* pCamera);
	bool GetAttackFlg();
	

private:
	// ===プロトタイプ宣言===
	void LoadAnime();	//アニメーション読み込み関数

	// ===メンバ変数宣言=====
	TPos3d<float> m_fMove;				// 移動量
	AnimeModel* m_pModel;				//プレイヤーのモデル
	int m_nHp;							// プレイヤーの体力
	bool m_bAttackFlg;					// 攻撃中かどうかのフラグ
	int m_nNoDamageCnt;					// プレイヤーの無敵時間をカウント
	bool m_bCollide;					// プレイヤーの無敵状態のフラグ(当たり判定をOFF)
	CHammer* m_pHammer;					// ハンマークラスのポインタ(プレイヤーが管理する)
	CCamera* m_pCamera;					// プレイヤーを追従するカメラ
	bool m_DrawFlg;						// プレイヤーがダメージを受けたら点滅するフラグ
	int m_FlashCnt;						// 点滅の時間の長さ
	int m_nMoveCnt;						// プレイヤーの移動によるSEの間隔
	bool m_bIntFlg;						// ハンマー間隔時間フラグ
	float m_fIntCnt;					// ハンマー間隔時間カウント
	float m_fTick;						//フレームカウンタ(0to60)
	CShadow* m_pShadow;
	CFrameCnt* m_pWaitFrameCnt;			//待機モーション用フレームカウントダウン

	// ===列挙===
	enum MOTION
	{
		MOTION_STOP,	//待機
		MOTION_MOVE,	//移動
		MOTION_SWING,	//ハンマーを振る
		MOTION_MAX,	//モーションの総数
	};

	//=====SE関連=====
	XAUDIO2_BUFFER* m_pSE[SE_MAX];
	IXAudio2SourceVoice* m_pSESpeaker[SE_MAX];
	const std::string m_sSEFile[SE_MAX] = {
		"Assets/Sound/SE/Swing.mp3",			//ハンマーを振る
		"Assets/Sound/SE/Run.mp3",				//移動のSE
		"Assets/Sound/SE/PlayerDamage.mp3",		//プレイヤーの被ダメージ時
		"Assets/Sound/SE/HammerHit.mp3",			//ハンマーとスライムの接触SE
		"Assets/Sound/SE/HealSE.mp3" };			//回復アイテム取得時

	//=====アニメーション関連=====
	AnimeModel::AnimeNo m_Anime[MOTION_MAX];		//プレイヤーのアニメーション
	const std::string m_sAnimeFile[MOTION_MAX] = {	//アニメーションのファイル
		"Assets/Model/player/wait_end.FBX",			//待機
		"Assets/Model/player/Dash.FBX",				//移動
		"Assets/Model/player/pow.FBX",				//スイング
	};			
};


#endif // !__PLAYER_H__



