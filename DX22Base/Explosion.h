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
	void DeleteExplosion();

private:
	
	DirectX::XMMATRIX Position;
	float m_fSize;

};

#endif // __EXPLOSION_H__

