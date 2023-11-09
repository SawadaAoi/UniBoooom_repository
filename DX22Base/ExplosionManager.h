/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   爆発管理ヘッダー
   ---------------------------------------
   ExplosionManager.h

   作成者 鄭 宇恩

   変更履歴
   ・2023/11/06 爆発マネージャークラス作成 /鄭　宇恩

========================================== */
#ifndef __EXPLOSION_MANAGER_H__	//ExplosionManager.hインクルードガード
#define __EXPLOSION_MANAGER_H__
// =============== インクルード ===================
#include "TriType.h"		//同じ型を３つ持つテンプレートクラス定義ヘッダー
#include "Explosion.h"		//爆発処理ヘッダー

// =============== 定数定義 =======================
const int MAX_EXPLOSION_NUM = 20;	//最大爆発数

// =============== クラス定義 =====================
class CExplosionManager
{
public:
	// ===メンバ関数宣言===
	CExplosionManager();		//コンストラクタ
	~CExplosionManager();		//デストラクタ

	void Update();				//更新関数
	void Draw();				//描画関数


	void Create(TTriType<float> pos);	//爆発生成関数
	void DeleteCheck();					//時間より爆発を削除関数
protected:
	// ===メンバ変数宣言===
	CExplosion* m_pExplosion[MAX_EXPLOSION_NUM];	//爆発の配列
private:
};

#endif // __EXPLOSION_MANAGER_H__