/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   爆発管理ヘッダー
   ---------------------------------------
   ExplosionManager.h

   作成者 鄭 宇恩

   変更履歴
	・2023/11/06 爆発マネージャークラス作成 tei
	・2023/11/09 爆発配列を返す処理の追加 sawada
	・2023/11/10 他のオブジェクトと同一のカメラをセットするようにした yamashita

	

========================================== */
#ifndef __EXPLOSION_MANAGER_H__	//ExplosionManager.hインクルードガード
#define __EXPLOSION_MANAGER_H__
// =============== インクルード ===================
#include "TriType.h"			//同じ型を３つ持つテンプレートクラス定義ヘッダー
#include "Explosion.h"			//爆発処理ヘッダー
#include "GameParameter.h"		//定数定義用ヘッダー

// =============== 定数定義 =======================
#if MODE_GAME_PARAMETER
#else
const int MAX_EXPLOSION_NUM = 20;	//最大爆発数
#endif
// =============== クラス定義 =====================
class CExplosionManager
{
public:
	// ===メンバ関数宣言===
	CExplosionManager();		//コンストラクタ
	~CExplosionManager();		//デストラクタ

	void Update();		 		//更新関数
	void Draw();		 		//描画関数
	
	void Create(TTriType<float> pos,float size);   	//爆発生成関数
	void DeleteCheck();							   	//時間より爆発を削除関数

	CExplosion* GetExplosionPtr(int num);

	void SetCamera(const CCamera* pCamera);	//他のオブジェクトと同一のカメラをセット
protected:
	// ===メンバ変数宣言===
	CExplosion* m_pExplosion[MAX_EXPLOSION_NUM];	//爆発の配列
	const CCamera* m_pCamera;
private:
};

#endif // __EXPLOSION_MANAGER_H__