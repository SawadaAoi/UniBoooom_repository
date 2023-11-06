//ヘッダー用　----------------------------------------------------
/*========================================
HEW/UniBoooom!!
---------------------------------------
爆発用ヘッダ
---------------------------------------
Expplosion.h

TeiUon

変更履歴
・2023/11/03 ヘッダー作成　鄭宇恩
・2023/11/05 パラメータ設定　鄭宇恩

======================================== */

#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__
#include "Model.h"
#include "Shader.h"
#include "TriType.h"


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
	void SetPos(TTriType<float> pos);
	bool GetExplode();
	TTriType<float> GetPos();
	

protected:
	Model* m_pModel;
	VertexShader* m_pVS;
	TTriType<float> m_pos;
	float m_fSize;
	bool m_bExploded;	//爆発したのフラグ

private:
};

#endif // __EXPLOSION_H__

