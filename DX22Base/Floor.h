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
	�E2023/11/22 ���W�Z�o�֐����쐬 yamashita
========================================== */
#ifndef __FLOOR_H__
#define __FLOOR_H__

#include "Camera.h"
#include "Transform3d.h"
#include "Pos3d.h"
#include "Shader.h"
#include "Model.h"
#include "GameParameter.h"		//�萔��`�p�w�b�_�[

// =============== �萔��` =====================
const int FLOOR_NUM = 9;

// =============== �N���X��` =====================
class CFloor
{
public:
	// ===�v���g�^�C�v�錾===
	CFloor(TPos3d<float>* pPlayerPos);
	~CFloor();
	void Update();
	void Draw();

	void calculationPosition();				//���W�Z�o�֐�
	void SetCamera(const CCamera* pCamera);	//�J�����Z�b�g�֐�

private:
	// ===�����o�ϐ��錾=====
	tagTransform3d m_Transform[FLOOR_NUM];		//���[���h���W�n���
	Model* m_pModel;				//3D���f��
	VertexShader* m_pVS;			//�o�[�e�b�N�X�V�F�[�_�[�̃|�C���^
	const CCamera* m_pCamera;		//�J�����̃|�C���^
	TPos3d<float>* m_pPlayePos;		//�v���C���[�̃|�W�V�����̃|�C���^
	TPos3d<int> m_pPlayerFloor;		//�v���C���[�����݂�����W�ɂ��鏰�������ڂ̏��Ȃ̂�
};




#endif // !__FLOOR_H__
