/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	スライムベース クラス定義
	---------------------------------------
	SlimeBase.h
	
	作成者 鈴村 朋也
	
	変更履歴
	・2023/11/04 スライムベースクラス作成 Suzumura
	・2023/11/06 吹き飛び移動と吹き飛び移動関数を作成 Yamashita
	・2023/11/06 m_fSpped(敵の移動速度)とm_fVecAngle(敵の吹き飛ぶ方向)のメンバ変数を追加 Yamashita
	・2023/11/06 定数SPEED_DOWN_RATIO(ぶつかった先のスライムに速度を渡す際に減少する割合)を追加 Yamashita
	・2023/11/06 定数MOVE_RESIST(吹き飛び移動中のスライムの移動速度に毎フレームかかる減算数値)を追加 Yamashita
	・2023/11/07 HitBranch関数(スライムとの接触分岐処理)をSlimeManagerに移動するために削除 Yamashita
	・2023/11/08 スライムのサイズを表す列挙を定義 Yamashita
	・2023/11/08 スライムのサイズを返す関数を作成 Yamashita
	・2023/11/08 GetPos→GetSphereに名前を変更 Yamashita
	・2023/11/08 スライムの移動速度を取得する関数を作成 Yamashita
	・2023/11/08 定数定義がヘッダーにあったのでcppに移動 Yamashita
	・2023/11/08 UnionとExplosionを削除(マネージャーに移動させたので) Yamashita
	・2023/11/08 m_bUse、n_playerDistance、m_playerAngleを削除(一か所でしか使用していない為) Yamashita
	・2023/11/08 m_Playerを追加 Yamashita
	・2023/11/08 座標をTPos<Pos>に変更 Yamashita
	・2023/11/09 Update,NormalMoveの引数変更 Yamashita
	・2023/11/08 スライムの移動速度の定数をcppからhに移動 Yamashita
	・2023/11/10 カメラポインタを追加 Yamashita
	・2023/11/10 他のオブジェクトと同一のカメラをセットするようにした Yamashita
	・2023/11/12 m_Ryを追加（スライムの向きを変える時に使用） Yamamoto
	・2023/11/13 GetScale関数の追加 Suzumura
	・2023/11/14 列挙にFLAMEを追加、NormalMoveを仮想関数に Suzumura
	・2023/11/14 SphereInfoの変更に対応 Takagi
	・2023/11/15 Objectクラスを継承したので修正　yamamoto
	・2023/11/26 爆発から逃げるフラグ、最も近い爆発を入れる変数を作成　yamashita
	・2023/11/26 スライムが爆発から逃げる処理を作成　yamashita
	・2023/11/28 影の描画追加 nieda
	・2023/12/04 列挙にヒールスライムを追加 Tei
	・2023/12/07 ゲームパラメータから一部定数移動 takagi

========================================== */
#ifndef __SLIME_BASE_H__
#define __SLIME_BASE_H__

// =============== インクルード ===================
#include "Model.h"
#include "Shader.h"
#include "SphereInfo.h"
#include "Transform3d.h"
#include "Pos3d.h"
#include "Camera.h"
#include "GameParameter.h"		//定数定義用ヘッダー
#include "Object.h"
#include "Shadow.h"		// 影表示用ヘッダ
#include "Timer.h"

// =============== 列挙定義 =======================
enum E_SLIME_LEVEL
{
	LEVEL_NONE,	//SlimeBaseで生成してまだポリモーフィズムしていない状態

	LEVEL_1,		//1段階目
	LEVEL_2,		//2段階目
	LEVEL_3,		//3段階目
	LEVEL_4,		//4段階目
	LEVEL_4x4,		//赤アか
	LEVEL_FLAME,			// フレイムスライム
	LEVEL_HEAL,				// ヒールスライム

	LEVEL_BOSS = 999,		// ボススライム	(最強)

	MAX_LEVEL = LEVEL_4	//最大レベルを設定	(スライムの段階が増えたら変更)
};

// =============== 定数定義 =======================
const int LEVEL_1_SCORE = 10;				// スライム_1のスコア
const int LEVEL_2_SCORE = 30;				// スライム_2のスコア
const int LEVEL_3_SCORE = 100;				// スライム_3のスコア
const int LEVEL_4_SCORE = 500;				// スライム_4のスコア
const int LEVEL_4x4_SCORE = 1000;			// 赤々の爆発のスコア
const int LEVEL_Boss_SCORE = 3000;			// 赤々の爆発のスコア
#if MODE_GAME_PARAMETER
#else
const float ENEMY_MOVE_SPEED = 0.01f;	//敵の移動速度
const int FIRST_EXPLOSION_SCORE = 1000;		//赤同士の最初の爆発のスコア
#endif

// =============== クラス定義 =====================

class CSlimeBase
	: public CObject 
{
public:
	// ===プロトタイプ宣言===
	CSlimeBase();
	~CSlimeBase();
	virtual void Update(tagTransform3d playerTransform, float fSlimeMoveSpeed); 
	virtual void Draw(const CCamera* pCamera);

	virtual void NormalMove();	// 通常時の移動処理
	void RandomMove();
	void HitMove();									//スライムが吹き飛び移動状態の時に毎フレーム呼び出して移動させる
	void HitMoveStart(float speed, float angle);	//スライムが吹き飛ばされたときに速度と角度を決める
	void Reflect();									//スライムとぶつかって吹き飛ばした際に自分の移動量を減らす
	void Escape();

	// ゲット関数
	float GetSpeed();					// スライムの移動速度を取得
	E_SLIME_LEVEL GetSlimeLevel();		// スライムのレベルを取得
	bool GetHitMoveFlg();
	TPos3d<float> GetPos();
	bool GetEscapeFlag();
	int GetAttack();

	//セット関数
	virtual void SetNormalSpeed() = 0;
	void SetCamera(const CCamera* pCamera);
	void SetExplosionPos(TPos3d<float> expPos);
	void SetEscapeFlag(bool bEscape);
protected:
	Model* m_pModel;				//3Dモデル
	VertexShader* m_pVS;			//バーテックスシェーダーのポインタ
	TTriType<float> m_move;			//移動量
	TPos3d<float> m_ExpPos;			//最も近い爆発の座標
	float m_fSpeed;					//スライムの移動速度

	bool m_bHitMove;				//吹っ飛び中かどうか
	float m_fVecAngle;				//敵の吹き飛ぶ方向
	bool m_bEscape;					//スライムが逃げる状態かどうか
	int m_nEscapeCnt;				//逃げる状態になった時

	E_SLIME_LEVEL m_eSlimeSize;		//スライムの大きさの列挙
	const CCamera* m_pCamera;		//カメラのポインタ

	CShadow* m_pShadow;				//影のポインタ
	float m_fScaleShadow;			//影の大きさ
	
	DirectX::XMMATRIX m_Ry;			//回転

	int m_RanMoveCnt;				// ランダム移動の加算値
	int m_nAttack;					// 攻撃力

	tagTransform3d m_PlayerTran;	// プレイヤーの変形情報

};
#endif // __SLIME_BASE_H__