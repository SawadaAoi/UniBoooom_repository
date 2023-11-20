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
	・2023/11/14 SphereInfoの変更に対応 Takagi
	・2023/11/15 Objectクラスを継承したので修正　yamamoto
	・2023/11/20 コンボ数配列添え字の追加 Sawada

======================================== */
#ifndef __EXPLOSION_H__	//Explosion.hインクルードガード
#define __EXPLOSION_H__

// =============== インクルード ===================
#include "Model.h"			//modelクラス定義ヘッダ―
#include "Shader.h"			//シェーダークラス定義ヘッダー
#include "Sphereinfo.h"		//球体情報用ヘッダー
#include "Transform3d.h"	//ワールド座標系情報ヘッダー
#include "Sphere.h"			//球定義ヘッダー
#include "Camera.h"			//カメラ定義ヘッダー
#include "Object.h"			//

//=============== クラス定義 =====================
class CExplosion
	:public CObject
{
public:
	// ===メンバ関数宣言===
	CExplosion(TPos3d<float> fPos, float fSize, float fTime, int comboNum);	//コンストラクタ
	~CExplosion();												// デストラクタ
	void Update();												// 更新関数
	void Draw();												// 描画関数
	void DisplayTimeAdd();										// 爆発表示カウント加算処理関数

	bool GetDelFlg();							// 削除フラグ取得処理関数
	int GetComboNum();							// コンボ配列番号取得
	void SetCamera(const CCamera* m_pCamera);	// 他のオブジェクトと同一のカメラをセット


private:
	// ===メンバ変数宣言===
	float			m_fMaxSize;
	TTriType<float>	m_fSizeAdd;
	int				m_fDelFrame;		// 爆発表示カウント
	bool			m_bDelFlg;			// 爆発終了フラグ
	float			m_fExplodeTime;		// 爆発総時間

	CGeometry*		m_3dModel;		// 爆発仮3Dモデル
	const CCamera*	m_pCamera;	//カメラのポインタ

	int m_dComboNum;			// コンボ配列番号


};

#endif // __EXPLOSION_H__
