#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__
/*========================================
	HEW/UniBoooom!!
	---------------------------------------
	爆発用ヘッダ
	---------------------------------------
	Expplosion.h
	
	作成者 鄭 宇恩
	
	変更履歴
	・2023/11/03 ヘッダー作成 / 鄭 宇恩
	・2023/11/05 パラメータ設定 /　鄭 宇恩
	・2023/11/07 変数型TriType→CSphereに /鄭 宇恩
	・2023/11/08 変数、関数の変更 / 澤田蒼生
	・2023/11/10 カメラポインタを追加 /山下凌佑
======================================== */

// =============== インクルード ===================
#include "Model.h"
#include "Shader.h"
#include "Sphereinfo.h"
#include "Sphere.h"
#include "Camera.h"

//=============== クラス定義 =====================
class CExplosion
{
public:
// ===メンバ関数宣言===
	CExplosion(TTriType<float> pos,float size);
	~CExplosion();
	void Update();
	void Draw();
	void DisplayTimeAdd();

	void SetPos(TTriType<float> pos);
	//TTriType<float> GetPos();
	CSphereInfo::Sphere GetSphere();
	void SetSphere(CSphereInfo::Sphere sphere);
	bool GetDelFlg();
	void SetCamera(const CCamera* m_pCamera);	//他のオブジェクトと同一のカメラをセット

private:
// ===メンバ変数宣言===
	CSphereInfo::Sphere m_Sphere;	// 座標と当たり判定の大きさを持つ
	float			m_fSize;
	float			m_fMaxSize;
	float			m_fSizeAdd;
	int				m_fDelFrame;	// 爆発表示カウント
	bool			m_bDelFlg;		// 爆発終了フラグ
	CGeometry*		m_3dModel;		// 爆発仮3Dモデル
	const CCamera*	m_pCamera;	//カメラのポインタ
};

#endif // __EXPLOSION_H__
