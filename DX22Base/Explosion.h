#ifndef __EXPLOSION_H__	//Explosion.hインクルードガード
#define __EXPLOSION_H__
/*========================================
	HEW/UniBoooom!!
	---------------------------------------
	爆発処理クラス定義ヘッダ
	---------------------------------------
	Expplosion.h

	作成者 鄭 宇恩

	変更履歴
	・2023/11/03 ヘッダー作成 / 鄭 宇恩
	・2023/11/05 パラメータ設定 /　鄭 宇恩
	・2023/11/07 変数型TriType→CSphereに /鄭 宇恩
	・2023/11/08 変数、関数の変更 / 澤田蒼生

======================================== */

// =============== インクルード ===================
#include "Model.h"		//modelクラス定義ヘッダ―
#include "Shader.h"		//シェーダークラス定義ヘッダー
#include "Sphereinfo.h"	//球体情報用ヘッダー
#include "Sphere.h"		//球定義ヘッダー


//=============== クラス定義 =====================
class CExplosion
{
public:
	// ===メンバ関数宣言===
	CExplosion(TTriType<float> pos);	//コンストラクタ
	~CExplosion();						//デストラクタ
	void Update();						//更新関数
	void Draw();						//描画関数
	void DisplayTimeAdd();				//爆発表示カウント加算処理関数

	void SetPos(TTriType<float> pos);	//爆発座標設定関数
	TTriType<float> GetPos();			//使ってない関数
	CSphereInfo::Sphere GetSphere();	//Sphere情報取得処理関数
	void SetSphere(CSphereInfo::Sphere sphere);	//Sphere情報設定処理関数
	bool GetDelFlg();					//削除フラグ取得処理関数

private:
	// ===メンバ変数宣言===
	CSphereInfo::Sphere m_Sphere;	// 座標と当たり判定の大きさを持つ
	float	m_fSize;				// 爆発の大きさ（？
	int	m_fDelFrame;				// 爆発表示カウント
	bool	m_bDelFlg;				// 爆発終了フラグ
	CGeometry* m_3dModel;			// 爆発仮3Dモデル

};

#endif // __EXPLOSION_H__
