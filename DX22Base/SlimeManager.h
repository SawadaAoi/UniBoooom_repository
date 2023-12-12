/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   スライムベース クラス定義
   ---------------------------------------
   SlimeManager.h

   作成者 鈴村 朋也

   変更履歴
	・2023/11/05 スライムマネージャークラス作成 Suzumura
	・2023/11/08 スライム同士が接触した際の分岐処理を作成(分岐した後に行う処理は未実装　※TODOをつけておいた)の Yamashita
	・2023/11/08 結合処理を作成(結合後の生成処理は未実装 Slime_2～Slime_4がまだ無いから) Yamashita
	・2023/11/09 スライム生成関数の名前変更 Sawada
	・2023/11/09 スライムのの生成をランダムに変更 Yamashita
	・2023/11/09 プレイヤー座標取得の型をTPos3d<float>に変更 Sawada
	・2023/11/11 スライム同士が重ならないようにする関数を作成 Yamashita
	・2023/11/14 炎スライムの接触時処理を作成 Suzumura
	・2023/11/15 各スライムのモデルのポインタと頂点シェーダーのポインタをbaseから移動 yamashita
	・2023/11/15 各モデルの読み込みを関数化 yamashita
	・2023/11/19 ボススライム用の配列を追加 Suzumura
	・2023/11/21 BoooomUI用変数追加 Tei
	・2023/11/26 ボス生成用関数追加	Sawada
	・2023/11/26 スライムと爆発の距離を調べ逃げるか判定する関数を作成 yamashita
	・2023/11/29 プレイヤーのポインタを取得 yamashita
	・2023/12/08 被討伐数のカウンタを追加 takagi

   ======================================== */

#ifndef __SLIME_MANAGER_H__
#define __SLIME_MANAGER_H__

// =============== インクルード ===================
#include "TriType.h"
//#include "SlimeBase.h"
#include "Camera.h"
#include "ExplosionManager.h"
#include "Slime_BossBase.h"
#include "GameParameter.h"		//定数定義用ヘッダー
#include "Sound.h"
#include "ScoreOHManager.h"
#include "HealItemManager.h"
#include "Player.h"
#include "Timer.h"
// =============== 定数定義 =======================
#if MODE_GAME_PARAMETER

#else
const int MAX_SLIME_NUM = 50;			// スライムの最大生成数
const int MAX_BOSS_SLIME_NUM = 5;		// ボススライムの最大生成数

#endif
// =============== クラス定義 =====================
class CSlimeManager
{
public:
	// ===プロトタイプ宣言===
	CSlimeManager(CPlayer* pPlayer);
	~CSlimeManager();

	void Update(CExplosionManager* pExpMng);
	void Draw();
	void Create(E_SLIME_LEVEL level);
	void CreateBoss();
	bool IsBossPtrExist();

	//-- ノーマル、その他
	void HitBranch(int HitSlimeArrayNum,int standSlimeArrayNum,CExplosionManager* pExpMng);			// スライムの接触が起きた際の分岐処理
	bool HitFlameBranch(int HitSlimeNum, int StandSlimeNum, CExplosionManager* pExpMng);			// フレイムスライムとの接触が起きた際の分岐処理
	bool HitHealBranch(int HitSlimeNum, int StandSlimeNum, CExplosionManager* pExpMng);				// フレイムスライムとの接触が起きた際の分岐処理
	void UnionSlime(E_SLIME_LEVEL level, TPos3d<float> pos);										// スライムの結合処理
	void TouchExplosion(int DelSlime, CExplosionManager* pExpMng, int comboNum);					// スライムの爆発処理

	//-- ボス
	void HitSlimeBossBranch(int HitSlimeNum, int StandBossNum, CExplosionManager* pExpMng);
	void HitBossSlimeBranch(int HitBossNum, int StandSlimeNum, CExplosionManager* pExpMng);
	void HitBossBossBranch(int HitBossNum, int StandBossNum, CExplosionManager* pExpMng);
	void TouchBossExplosion(int BossSlime, CExplosionManager* pExpMng, int ExpNum);



	E_SLIME_LEVEL GetRandomLevel();																	// ランダムなスライムのレベルを返す(1～3レべル)
	void PreventSlimeSlimeOverlap(CSlimeBase* pMoveSlime, CSlimeBase* pStandSlime);							// スライム同士が移動中に接触した時の処理
	void PreventSlimeBossOverlap(CSlimeBase* pMoveSlime, CSlime_BossBase* pStandBoss);							// スライム同士が移動中に接触した時の処理
	void PreventBossSlimeOverlap(CSlime_BossBase* pMoveBoss, CSlimeBase* pStandSlime);							// スライム同士が移動中に接触した時の処理
	void PreventBossBossOverlap(CSlime_BossBase* pMoveBoss, CSlime_BossBase* pStandBoss);							// スライム同士が移動中に接触した時の処理
	void LoadModel();
	void OutOfRange();
	void CheckEscape();

	//ゲット関数
	CSlimeBase* GetSlimePtr(int num);
	CSlime_BossBase* GetBossSlimePtr(int num);

	// セット関数
	void SetCamera(CCamera* pCamera);		//スライムを移すカメラのポインタをセット
	void SetScoreOHMng(CScoreOHManager* pScoreMng);
	void SetHealMng(CHealItemManager* pHealItemMng);
	void SetExplosionMng(CExplosionManager* pExpMng);
	void SetTimer(CTimer* pTimer);
	int GetKillCnt();									//被討伐数ゲッタ
private:
	// ===メンバ変数宣言=====
	int GetRandom(int min, int max);

	CSlimeBase* m_pSlime[MAX_SLIME_NUM];
	CSlime_BossBase* m_pBoss[MAX_BOSS_SLIME_NUM];
	CCamera* m_pCamera;

	CPlayer* m_pPlayer;	// プレイヤーの座標
	VertexShader* m_pVS;
	// スライムのモデル
	Model* m_pBlueModel;
	Model* m_pGreenModel;
	Model* m_pYellowModel;
	Model* m_pRedModel;
	Model* m_pFlameModel;
	Model* m_pHealModel;
	Model* m_pBossModel[2];

	CScoreOHManager* m_pScoreOHMng;				// スコアマネージャ―ポインタ
	CHealItemManager* m_pHealItemMng;			// 回復アイテムマネージャーポインタ
	CTimer* m_pTimer;							// タイマーポインタ

	XAUDIO2_BUFFER* m_pSEHitSlime;				//ハンマーでスライムを打った時のSEのデータ
	XAUDIO2_BUFFER* m_pSEUnion;					//ハンマーでスライムを打った時のSEのデータ
	IXAudio2SourceVoice* m_pSEHitSlimeSpeaker;	//ハンマーでスライムを打った時のSEを聞き取る側
	IXAudio2SourceVoice* m_pSEUnionSpeaker;		//ハンマーでスライムを打った時のSEを聞き取る側

	int m_CreateCnt;			// 生成間隔用カウント
	TPos3d<float> m_oldCreatePos;	//1つ前のスライムの生成場所
	CExplosionManager* m_pExpMng;
	
	int m_nKill;	//被討伐数

	bool m_bBossPtrExist;		// ボスのポインタが存在するかどうか
	// ===プロトタイプ宣言===
	void CntKill();	//被討伐数カウンタ
};

#endif // __SLIME_MANAGER_H__