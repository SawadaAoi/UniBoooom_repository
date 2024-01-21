/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�I�u�W�F�N�g��`
	------------------------------------
	Object.h
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2024/01/18 �쐬 takagi
	�E2024/01/21 �R�����g���C�E�p����Ŋ֐���`���Ȃ��łق����֐���final�t�^ takagi

========================================== */

#ifndef __OBJECT_H__	//Object.h�C���N���[�h�K�[�h
#define __OBJECT_H__

// =============== �C���N���[�h ===================
#include "Transform3d.h"	//�����o�̃w�b�_

// =============== �N���X��` =====================
class CObject
{
private:
	// ===�萔��`===========
	const TPos3d<float> INIT_POS = { 640.0f, 360.0f, 0.0f };	//�����ʒu
	const TTriType<float> INIT_SCALE = { 1.0f, 1.0f, 0.0f };	//�����g�k
	const TTriType<float> INIT_RADIAN = 0.0f;					//������]
public:
	// ===�v���g�^�C�v�錾===
	CObject();															//�R���X�g���N�^
	CObject(const CObject& Obj);										//�R�s�[�R���X�g���N�^
	virtual ~CObject();													//�f�X�g���N�^
	virtual void Update() = 0;											//�X�V
	virtual void Draw() = 0;											//�`��
	virtual TPos3d<float> GetPos() const final;							//�ʒu�Q�b�^
	virtual const float& GetPosZ() const final;							//Z���W�Q�b�^
	virtual void SetPos(const TPos3d<float>& fPos) final;				//�ʒu�Z�b�^
	virtual void SetSize(const TTriType<float>& fScale) final;			//�傫���Z�b�^
	virtual void SetRotate(const TTriType<float>& fRotate) final;		//��]�Z�b�^
	virtual void SetTransform(const tagTransform3d& Transform) final;	//���[���h���W�Z�b�^
protected:
	// ===�����o�ϐ��錾=====
	tagTransform3d m_Transform;	//���[���h���W
};	//�I�u�W�F�N�g

#endif	//!__OBJECT_H__