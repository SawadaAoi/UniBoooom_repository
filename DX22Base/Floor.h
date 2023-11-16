/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	Floor�p�w�b�_
	------------------------------------
	Floor.h
	------------------------------------
	�쐬��
		yamashita
	�ύX����
	�E2023/11/16 h,�쐬 yamashita
	�E2023/11/16 ���f���A���_�V�F�[�_�[�A�J�����̃|�C���^�������o�ϐ��ɒǉ� yamashita
	�E2023/11/16 �J�����̃Z�b�g�֐����쐬 yamashita
========================================== */
#ifndef __FLOOR_H__
#define __FLOOR_H__

#include "Camera.h"
#include "Transform3d.h"
#include "Pos3d.h"
#include "Shader.h"
#include "Model.h"
#include "GameParameter.h"		//�萔��`�p�w�b�_�[

// =============== �N���X��` =====================
class CFloor
{
public:
	// ===�v���g�^�C�v�錾===
	CFloor();
	~CFloor();
	void Update();
	void Draw();

	void SetCamera(const CCamera* pCamera);

private:
	// ===�����o�ϐ��錾=====
	Model* m_pModel;				//3D���f��
	VertexShader* m_pVS;			//�o�[�e�b�N�X�V�F�[�_�[�̃|�C���^
	tagTransform3d m_Transform;		//���[���h���W�n���
	const CCamera* m_pCamera;		//�J�����̃|�C���^

};




#endif // !__FLOOR_H__
