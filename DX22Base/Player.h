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
========================================== */

#ifndef __PLAYER_H__
#define __PLAYER_H_

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
// =============== クラス定義 =====================
class CPlayer
	: public CObject
{
public:
	// ===プロトタイプ宣言===
	CPlayer();		//コンストラクタ
	~CPlayer();		//デストラクタ

	void Update();	//更新
	void Draw();	//描画
	void Damage();	//自身のHPを減らす
	void MoveKeyboard();	// キーボード用入力移動
	void MoveController();	// コントローラ用入力移動
	void MoveSizeInputSet(TPos3d<float> fInput);
	void DamageAnimation();
	void SE_Move();
	void LoadSound();	//サウンド読み込み関数

	// ゲット関数
	tagSphereInfo GetHammerSphere();	//当たり判定を取るためゲッター
	TPos3d<float>* GetPosAddress();
	CHammer* GetHammerPtr();
	bool GetCollide();							//当たり判定があるかの確認
	int* GetHP();
	// セット関数
	void SetCamera(const CCamera* pCamera);
	bool GetAttackFlg();
	

private:
	// ===メンバ変数宣言=====
	

	TPos3d<float> m_fMove;				// 移動量
	
	int m_nHp;							// プレイヤーの体力
	bool m_bAttackFlg;					// 攻撃中かどうかのフラグ
	int m_nNoDamageCnt;					// プレイヤーの無敵時間をカウント
	bool m_bCollide;					// プレイヤーの無敵状態のフラグ(当たり判定をOFF)
	CHammer* m_pHammer;					// ハンマークラスのポインタ(プレイヤーが管理する)
	CGeometry* m_pPlayerGeo;			// プレイヤーを仮表示するジオメトリー
	const CCamera* m_pCamera;			// プレイヤーを追従するカメラ
	CGeometry* m_pGameOver;				// ゲームオーバーを仮表示するジオメトリー
	bool m_DrawFlg;						// プレイヤーがダメージを受けたら点滅するフラグ
	int m_FlashCnt;						// 点滅の時間の長さ
	int m_nMoveCnt;						// プレイヤーの移動によるSEの間隔

	XAUDIO2_BUFFER* m_pSESwingHammer;
	XAUDIO2_BUFFER* m_pSERun;
	XAUDIO2_BUFFER* m_pSEDamaged;
	IXAudio2SourceVoice* m_pSESwingHamSpeaker;
	IXAudio2SourceVoice* m_pSERunSpeaker;
	IXAudio2SourceVoice* m_pSEDamagedSpeaker;
};


#endif // !__PLAYER_H__



