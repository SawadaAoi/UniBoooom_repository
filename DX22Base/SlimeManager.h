/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   スライムベース クラス定義
   ---------------------------------------
   SlimeManager.h

   作成者 鈴村 朋也

   変更履歴
   ・2023/11/05 スライムマネージャークラス作成 /鈴村 朋也
   ・2023/11/08 スライム同士が接触した際の分岐処理を作成(分岐した後に行う処理は未実装　※TODOをつけておいた)の /山下凌佑
   ・2023/11/08 結合処理を作成(結合後の生成処理は未実装 Slime_2～Slime_4がまだ無いから) /山下凌佑
   ・2023/11/09 スライム生成関数の名前変更/澤田
   ・2023/11/09 スライムのの生成をランダムに変更	/山下凌佑
   ・2023/11/09 プレイヤー座標取得の型をTPos3d<float>に変更

   ======================================== */
#ifndef __SLIME_MANAGER_H__
#define __SLIME_MANAGER_H__

#include "TriType.h"
#include "SlimeBase.h"
#include "ExplosionManager.h"
#include "Camera.h"
#include "ExplosionManager.h"


const int MAX_SLIME = 30;	//スライムの最大生成数

class CSlimeManager
{
public:
	CSlimeManager();
	~CSlimeManager();

	void Update(CExplosionManager* pExpMng);
	void Draw();
	void Create(E_SLIME_LEVEL level);
	void HitBranch(int HitSlimeArrayNum,int standSlimeArrayNum,CExplosionManager* pExpMng);	//スライムの接触が起きた際の分岐処理
	void UnionSlime(E_SLIME_LEVEL level, TPos3d<float> pos);							//スライムの結合処理
	void TouchExplosion(int DelSlime, CExplosionManager* pExpMng);	// スライムの爆発処理
	E_SLIME_LEVEL GetRandomLevel();									//ランダムなスライムのレベルを返す(1～3レべル)

	//ゲット関数
	CSlimeBase* GetSlimePtr(int num);

	void SetCamera(CCamera* pCamera);		//スライムを移すカメラのポインタをセット
	void SetPlayerPos(TPos3d<float> pos);
private:
	int GetRandom(int min, int max);

	CSlimeBase* m_pSlime[MAX_SLIME];
	CCamera* m_pCamera;

	TPos3d<float> m_pPlayerPos;	// プレイヤーの座標

	int m_CreateCnt;	// 生成間隔用カウント


	
};

#endif // __SLIME_MANAGER_H__