//ヘッダー用　----------------------------------------------------
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
======================================== */

#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__
#include "Model.h"
#include "Shader.h"
#include "Sphereinfo.h"


//=============== 構造体定義 =====================

//=============== クラス定義 =====================

//=============== 列挙定義 =======================

class CExplosion
{
public:
	CExplosion();
	~CExplosion();
	void Update();
	void Draw();

	void SetExplode(bool YN);
	void SetPos(CSphereInfo::Sphere pos);
	bool GetExplode();
	CSphereInfo::Sphere GetPos();


protected:
	Model* m_pModel;
	VertexShader* m_pVS;
	CSphereInfo::Sphere m_Sphere;
	float m_fSize;
	bool m_bExploded;	//爆発したのフラグ

private:
};

#endif // __EXPLOSION_H__
