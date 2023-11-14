/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	爆発処理クラス定義ヘッダ
	---------------------------------------
	Expplosion.h

	作成者 鄭 宇恩

	変更履歴
	・2023/11/03 ヘッダー作成 Tei
	・2023/11/05 パラメータ設定 Tei
	・2023/11/07 変数型TriType→CSphereに Tei
	・2023/11/08 変数、関数の変更 Sawada
	・2023/11/10 カメラポインタを追加 Ymashita
	・2023/11/13 コンストラクタにtimeを追加 Suzumura
	・2023/11/13 爆発総時間の変数を追加 Suzumura

======================================== */
#ifndef __EXPLOSION_H__	//Explosion.hインクルードガード
#define __EXPLOSION_H__
// =============== インクルード ===================
#include "Model.h"		//modelクラス定義ヘッダ―
#include "Shader.h"		//シェーダークラス定義ヘッダー
#include "Sphereinfo.h"	//球体情報用ヘッダー
#include "Sphere.h"		//球定義ヘッダー
#include "Camera.h"

//=============== クラス定義 =====================
class CExplosion
{
public:
	// ===メンバ関数宣言===
	CExplosion(TTriType<float> pos, float size, float time);	//コンストラクタ
	~CExplosion();												//デストラクタ
	void Update();												//更新関数
	void Draw();												//描画関数
	void DisplayTimeAdd();										//爆発表示カウント加算処理関数

	void SetPos(TTriType<float> pos);	//爆発座標設定関数
	TTriType<float> GetPos();			//使ってない関数
	tagSphereInfo GetSphere();	//Sphere情報取得処理関数
	void SetSphere(tagSphereInfo sphere);	//Sphere情報設定処理関数
	bool GetDelFlg();					//削除フラグ取得処理関数
	void SetCamera(const CCamera* m_pCamera);	//他のオブジェクトと同一のカメラをセット


private:
	// ===メンバ変数宣言===
	tagSphereInfo m_Sphere;	// 座標と当たり判定の大きさを持つ
	float			m_fSize;		// 爆発の大きさ
	float			m_fMaxSize;
	float			m_fSizeAdd;
	int				m_fDelFrame;		// 爆発表示カウント
	bool			m_bDelFlg;			// 爆発終了フラグ
	float			m_fExplodeTime;		// 爆発総時間

	CGeometry*		m_3dModel;		// 爆発仮3Dモデル
	const CCamera*	m_pCamera;	//カメラのポインタ
};

#endif // __EXPLOSION_H__
