#ifndef __FLOOR_H__
#define __FLOOR_H__

#include "Camera.h"
#include "Transform3d.h"
#include "Pos3d.h"
#include "Shader.h"
#include "Model.h"
#include "GameParameter.h"		//�萔��`�p�w�b�_�[

class CFloor
{
public:
	CFloor();
	~CFloor();
	void Update();
	void Draw();

	void SetCamera(const CCamera* pCamera);

private:
	Model* m_pModel;				//3D���f��
	VertexShader* m_pVS;			//�o�[�e�b�N�X�V�F�[�_�[�̃|�C���^
	tagTransform3d m_Transform;		//���[���h���W�n���
	const CCamera* m_pCamera;		//�J�����̃|�C���^

};




#endif // !__FLOOR_H__
