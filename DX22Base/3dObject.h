/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	3D�I�u�W�F�N�g��`
	------------------------------------
	3dObject.h
	------------------------------------
	�쐬��	yamamoto

	�ύX����
	�E2023/11/14 �쐬	yamamoto
	�E2024/01/16 ���l�[���A�p�� takagi
	�E2024/01/18 �����y�у��t�@�N�^�����O takagi
	�E2024/01/20 GetPos()�֐���e�Ɉړ� takagi
	�E2024/01/21 �R�����g���C�E�ĉ���� takagi

========================================== */

#ifndef __3D_OBJECT_H__	//3dObject.h�C���N���[�h�K�[�h
#define __3D_OBJECT_H__

// =============== �C���N���[�h ===================
#include "Object.h"		//�e�̃w�b�_
#include "SphereInfo.h"	//�����o�̃w�b�_

// =============== �N���X��` =====================
class C3dObject	:public CObject	//�I�u�W�F�N�g�p��
{
private:
	// ===�萔��`===========
	const float INIT_RADIUS = 0.0f;							//�������a
	const TPos3d<float> INIT_SHIFT = { 0.0f, 0.0f, 0.0f };	//�����ʒu����l
public:
	// ===�v���g�^�C�v�錾===
	C3dObject();												//�R���X�g���N�^
	C3dObject(const C3dObject& Obj);							//�R�s�[�R���X�g���N�^
	virtual ~C3dObject();										//�f�X�g���N�^
	virtual tagTransform3d GetTransform() const final;			//���[���h���W�Q�b�^
	virtual TTriType<float> GetRotate() const final;			//��]�Q�b�^
	virtual TTriType<float> GetScale() const final;				//�g�k�Q�b�^
	virtual tagSphereInfo GetSphere() const final;				//�q�b�g�{�b�N�X�Q�b�^
	virtual float GetRadius() const final;						//���a�Q�b�^
	virtual TPos3d<float> GetShift() const final;				//�ʒu����l�Q�b�^
	virtual void SetSphere(const tagSphereInfo& Sphere) final;	//�q�b�g�{�b�N�X�Z�b�^
	virtual void SetRadius(const float& Radius) final;			//���a�Z�b�^
	virtual void SetShift(const TPos3d<float>& Shift) final;	//�ʒu����Z�b�^
protected:
	// ===�����o�ϐ��錾=====
	tagSphereInfo m_Sphere;		//�����蔻��p�̋���
};	//3D�I�u�W�F�N�g

#endif	//!__3D_OBJECT_H__