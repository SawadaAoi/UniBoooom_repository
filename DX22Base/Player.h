/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	プレイヤー用ヘッダ
	------------------------------------
	Player.h
	------------------------------------
	作成者	yamamoto

	変更履歴
	・2023/11/03 h,作成 yamamoto
	・2023/11/06 ダメージ処理追加,コメント追加 yamamoto
	・2023/11/08 Pos.hをインクルード yamashita
	・2023/11/08 当たり判定用の球体m_sphereを追加 yamashita
	・2023/11/08 プレイヤー座標を入れる変数をTTriTypeからTPosに変更 yamashita
	・2023/11/09 GetPosAddress追加、カメラ追加 takagi
	・2023/11/09 プレイヤーの無敵時間をカウントの変数と無敵状態のフラグを追加 yamashita
	・2023/11/09 プレイヤーの無敵状態を取得するゲット関数を追加 yamashita
	・2023/11/11 プレイヤーの点滅処理追加 tei
	・2023/11/14 SphereInfoの変更に対応 takagi
	・2023/11/14 キーボードの入力移動処理内容を適切な形に変更 sawada
	・2023/11/15 Objectクラスを継承したので修正　yamamoto
	・2023/11/19 移動のSEを再生 yamashita
	・2023/11/19 被ダメージ時とハンマーを振るSEを再生 yamashita
	・2023/11/19 サウドファイル読み込み関数を作成 yamashita
	・2023/11/27 ハンマー振り間隔用カウント追加 tei	
	・2023/11/28 ダメージ処理に受けるダメージ量を追加 sawada
	・2023/12/03 カメラの更新を担うため、ポインタのconstを仕方なく除去 takagi
	・2023/12/14 アニメーション用の列挙を作成 yamashita
	・2023/12/14 SE用の列挙を作成 yamashita
	・2023/12/15 SEを外から再生できるように変更 yamashita
	・2023/12/15 回復SE追加 yamashita
	・2024/01/20 リファクタリング takagi
	・2024/01/21 コメント改修・汎化作業 takagi

========================================== */

#ifndef __PLAYER_H__	//Player.hインクルードガード
#define __PLAYER_H__

// =============== インクルード ===================
#include "Shader.h"
#include "hammer.h"
#include "Geometry.h"
#include "SphereInfo.h"
#include "Transform3d.h"
#include "Pos3d.h"
#include "Camera.h"
#include "3dObject.h"		//3Dオブジェクト
#include "Model.h"
#include "Shadow.h"

// =============== クラス定義 =====================
class CPlayer :public C3dObject
{
public:
	// === 列挙 ===
	enum E_SE
	{
		E_SE_SWING,			//ハンマーを振るSE
		E_SE_RUN,			//移動のSE
		E_SE_DAMAGED,		//被ダメージのSE
		E_SE_HIT_HAMMER,	//ハンマーとスライムの接触SE
		E_SE_HEAL,			//回復のSE
		E_SE_MAX			//SEの総数
	};	//SE
private:
	enum E_MOTION
	{
		E_MOTION_STOP,	//待機
		E_MOTION_MOVE,	//移動
		E_MOTION_SWING,	//ハンマーを振る
		E_MOTION_MAX,	//モーションの総数
	};	//モーション
	// ===定数定義===========
	const std::map<int, XAUDIO2_BUFFER*> MAP_SE = {
	{E_SE_SWING, CSound::LoadSound("Assets/Sound/SE/Swing.mp3", true)},				//ハンマーを振る
	{ E_SE_RUN, CSound::LoadSound("Assets/Sound/SE/Run.mp3", true) },				//移動のSE
	{ E_SE_DAMAGED, CSound::LoadSound("Assets/Sound/SE/PlayerDamage.mp3", true) },	//プレイヤーの被ダメージ時
	{ E_SE_HIT_HAMMER, CSound::LoadSound("Assets/Sound/BGM/BGM_maou.mp3", true) },	//ハンマーとスライムの接触SE
	{ E_SE_HEAL, CSound::LoadSound("Assets/Sound/SE/回復1.mp3", true) },			//回復アイテム取得時
	};	//SEデータ
	const std::map<int, std::string> MAP_ANIMATION_PASS = {
	{E_MOTION_STOP, "Assets/Model/player/Player.FBX"},	//待機
	{E_MOTION_MOVE, "Assets/Model/player/Dash.FBX"},	//移動
	{E_MOTION_SWING, "Assets/Model/player/pow.FBX"},	//スイング
	};	//アニメーションのファイル
	const std::string MODEL_PASS = "Assets/Model/player/POW.fbx";	//モデルのファイル
public:
	// ===プロトタイプ宣言===
	CPlayer();					//コンストラクタ
	~CPlayer();					//デストラクタ
	void Update();				//更新
	void Draw() const;			//描画
	void Damage(int DmgNum);	//自身のHPを減らす
	void MoveKeyboard();			// キーボード用入力移動
	void MoveController();								// コントローラ用入力移動
	void MoveSizeInputSet(TPos3d<float> fInput);
	void DamageAnimation();
	void MoveCheck();
	void Healing();
	tagSphereInfo GetHammerSphere();	//当たり判定を取るためゲッター
	TPos3d<float>* GetPosAddress();
	CHammer* GetHammerPtr();
	bool GetCollide();							//当たり判定があるかの確認
	int* GetHpPtr();
	bool GetAttackFlg();
	virtual void SetCamera(const CCamera* pCamera) override;			//カメラセッタ
	virtual void PlaySe(const E_SE& eKey, const float& fVolume = 1.0f);	//SE音源登録
private:
	// ===メンバ変数宣言=====
	TPos3d<float> m_fMove;	//移動量
	int m_nHp;				//プレイヤーの体力
	bool m_bAttackFlg;		//攻撃中かどうかのフラグ
	int m_nNoDamageCnt;		//プレイヤーの無敵時間をカウント
	bool m_bCollide;		//プレイヤーの無敵状態のフラグ(当たり判定をOFF)
	CHammer* m_pHammer;		//ハンマークラスのポインタ(プレイヤーが管理する)
	bool m_DrawFlg;			//プレイヤーがダメージを受けたら点滅するフラグ
	int m_FlashCnt;			//点滅の時間の長さ
	int m_nMoveCnt;			//プレイヤーの移動によるSEの間隔
	bool m_bIntFlg;			//ハンマー間隔時間フラグ
	float m_fIntCnt;		//ハンマー間隔時間カウント
	float m_fTick;			//レームカウンタ(0to60)
	CShadow* m_pShadow;		//影
};

#endif	//!__PLAYER_H__