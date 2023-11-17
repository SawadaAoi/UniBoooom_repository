/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�I�u�W�F�N�g�p�w�b�_
	------------------------------------
	Object.h
	------------------------------------
	�쐬��
		�R�{�M��
	�ύX����
	�E2023/11/14 �쐬	yamamoto

========================================== */

#ifndef __OBJECT_H__
#define __OBJECT_H__
// =============== �C���N���[�h ===================
#include "SphereInfo.h"
#include "Transform3d.h"

// =============== �N���X��` =====================
class CObject
{
public:
	// ===�v���g�^�C�v�錾===
	CObject();//�R���X�g���N�^
	~CObject();//�f�X�g���N�^
	
	// �Q�b�g�֐�
	tagTransform3d GetTransform(); 
	TPos3d<float> GetPos();
	TTriType<float> GetRadian();
	TTriType<float> GetScale();
	tagSphereInfo GetSphere();
	float GetRadius();
	TPos3d<float> GetShift();

	//�Z�b�g�֐�
	void SetTransform(tagTransform3d Transform);
	void SetPos(TPos3d<float> Pos);
	void SetRadian(TTriType<float> Radian);
	void SetScale(TTriType<float> Scale);
	void SetSphere(tagSphereInfo Sphere);
	void SetRadius(float Radius);
	void SetShift(TPos3d<float> Shift);

protected:
	// ===�����o�ϐ��錾=====
	tagTransform3d m_Transform;	//���[���h���W�n���
	tagSphereInfo m_Sphere;		//�����蔻��p�̋���
};

#endif //!__OBJECT_H__