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

   ======================================== */
#ifndef __SLIME_MANAGER_H__
#define __SLIME_MANAGER_H__

// =============== インクルード ===================
#include "TriType.h"
#include "SlimeBase.h"
#include "ExplosionManager.h"
#include "Camera.h"

// =============== 定数定義 =======================
const int MAX_SLIME = 20;	//スライムの最大生成数

// =============== クラス定義 =====================
class CSlimeManager
{
public:
	// ===プロトタイプ宣言===
	CSlimeManager();
	~CSlimeManager();

	void Update();
	void Draw();
	void Create();	//スライムを生成する処理
	void HitBranch(int HitSlimeArrayNum,int standSlimeArrayNum);	//スライムの接触が起きた際の分岐処理
	void UnionSlime(E_SLIME_LEVEL level);							//スライムの結合処理


	//ゲット関数
	CSlimeBase* GetSlimePtr(int num);

	//セット関数
	void SetCamera(CCamera* pCamera);
	void SetPlayerSphere(CSphereInfo::Sphere pSphere);

private:
	int GetRandom(int min, int max);
	int m_GeneCnt;

	CSlimeBase* m_pSlime[MAX_SLIME];
	CCamera* m_pCamera;
	CSphereInfo::Sphere m_pPlayerSphere;	// プレイヤーの当たり判定処理



	
};

#endif // __SLIME_MANAGER_H__