#ifndef __FLOOR_H__
#define __FLOOR_H__

#include "Camera.h"
#include "Transform3d.h"
#include "Pos3d.h"
#include "Shader.h"
#include "Model.h"
#include "GameParameter.h"		//定数定義用ヘッダー

class CFloor
{
public:
	CFloor();
	~CFloor();
	void Update();
	void Draw();

	void SetCamera(const CCamera* pCamera);

private:
	Model* m_pModel;				//3Dモデル
	VertexShader* m_pVS;			//バーテックスシェーダーのポインタ
	tagTransform3d m_Transform;		//ワールド座標系情報
	const CCamera* m_pCamera;		//カメラのポインタ

};




#endif // !__FLOOR_H__
