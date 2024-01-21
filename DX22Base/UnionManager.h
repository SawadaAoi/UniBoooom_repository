/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	UNION管理定義
	------------------------------------
	UnionManager.h
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/12/19 制作 takagi
	・2024/01/16 統一のため、インクルードガードの___を__に変更	takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __UNION_MANAGER_H__	//UnionManager.hインクルードガード
#define __UNION_MANAGER_H__

// =============== インクルード ===================
#include "Shader.h"			//メンバのヘッダ
#include "Texture.h"		//メンバのヘッダ
#include "Camera.h"			//メンバのヘッダ
#include "Transform3d.h"	//メンバのヘッダ
#include "DiType.h"			//メンバのヘッダ
#include "TriType.h"		//メンバのヘッダ
#include <map>				//連想コンテナ
#include <vector>			//配列コンテナ
#include <typeinfo>			//メンバのヘッダ
#include "2dObject.h"		//メンバのヘッダ
#include "Union.h"			//メンバのヘッダ

// =============== クラス定義 =====================
class CUnionManager
{
public:
	// ===プロトタイプ宣言===
	CUnionManager();									//コンストラクタ
	//CUnionManager(const CUnionManager& Obj);			//コピーコンストラクタ
	~CUnionManager();									//デストラクタ
	void Update();										//更新
	void Draw();										//描画
	void SetCamera(CCamera* pCamera);					//カメラセッタ
	void MakeUnion(const size_t& HashTypeId, const TPos3d<float>& fPos);
private:
	// ===メンバ変数宣言=====
	unsigned char m_ucFlag;							//フラグ
	static int ms_nCntUnionManager;					//自身の生成数
	static std::map<size_t, Texture*> ms_pTexture;	//テクスチャ情報
	std::vector<CUnion*> m_pUnion;					//UNION
	const CCamera* m_pCamera;						//カメラ(貰い専)
};	//フェード

#endif	//!__UNION_MANAGER_H__