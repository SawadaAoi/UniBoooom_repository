/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	���p�w�b�_
	------------------------------------
	Floor.h
	------------------------------------
	�쐬��	yamashita

	�ύX����
	�E2023/11/16 h,�쐬 yamashita
	�E2023/11/16 ���f���A���_�V�F�[�_�[�A�J�����̃|�C���^�������o�ϐ��ɒǉ� yamashita
	�E2023/11/16 �J�����̃Z�b�g�֐����쐬 yamashita
	�E2023/11/22 ���W�Z�o�֐����쐬 yamashita
	�E2024/01/20 ���t�@�N�^�����O takagi
	�E2024/01/21 �R�����g���C�E�ĉ���� takagi

========================================== */

#ifndef __FLOOR_H__	//Floor.h�C���N���[�h�K�[�h
#define __FLOOR_H__

#include "Camera.h"
#include "Transform3d.h"
#include "Pos3d.h"
#include "Shader.h"
#include "Model.h"
#include "GameParameter.h"		//�萔��`�p�w�b�_�[
#include "3dObject.h"

// =============== �萔��` =====================
const int FLOOR_NUM = 9;

// =============== �N���X��` =====================
class CFloor :public C3dObject
{
public:
	enum StageKinds
	{
		Stage1,
		Stage2,
		Stage3,
	};
public:
	// ===�v���g�^�C�v�錾===
	CFloor(TPos3d<float>* pPlayerPos,StageKinds stageKind);
	~CFloor();
	void Update();
	void Draw();

	void calculationPosition();				//���W�Z�o�֐�
	void SetFloorModel();
private:
	// ===�����o�ϐ��錾=====
	tagTransform3d m_Transform[FLOOR_NUM];		//���[���h���W�n���
	Model* m_pModel;				//3D���f��
	VertexShader* m_pVS;			//�o�[�e�b�N�X�V�F�[�_�[�̃|�C���^
	TPos3d<float>* m_pPlayePos;		//�v���C���[�̃|�W�V�����̃|�C���^
	TPos3d<int> m_pPlayerFloor;		//�v���C���[�����݂�����W�ɂ��鏰�������ڂ̏��Ȃ̂�
	StageKinds m_stage;
};

#endif	//!__FLOOR_H__
