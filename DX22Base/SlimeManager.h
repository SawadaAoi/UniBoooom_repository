/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   スライムベース クラス定義
   ---------------------------------------
   SlimeManager.h

   作成者 鈴村 朋也

   変更履歴
   ・2023/11/05 スライムマネージャークラス作成 /鈴村 朋也
   ・2023/11/09 スライム生成関数の名前変更/澤田

   ======================================== */
#ifndef __SLIME_MANAGER_H__
#define __SLIME_MANAGER_H__

#include "TriType.h"
#include "SlimeBase.h"
#include "Camera.h"



const int MAX_SLIME = 20;	//スライムの最大生成数

class CSlimeManager
{
public:
	CSlimeManager();
	~CSlimeManager();

	void Update();
	void Draw();
	void Create();
	void HitBranch(int HitSlimeArrayNum,int standSlimeArrayNum);	//スライムの接触が起きた際の分岐処理
	void UnionSlime(E_SLIME_LEVEL level);							//スライムの結合処理
	CSlimeBase* GetSlimePtr(int num);

	void SetCamera(CCamera* pCamera);
	void SetPlayerSphere(CSphereInfo::Sphere pSphere);
private:
	int GetRandom(int min, int max);

	CSlimeBase* m_pSlime[MAX_SLIME];
	CCamera* m_pCamera;

	CSphereInfo::Sphere m_pPlayerSphere;	// プレイヤーの当たり判定処理

	int m_GeneCnt;


	
};

#endif // __SLIME_MANAGER_H__