/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�ǐՃJ������`
	------------------------------------
	CameraChase.h
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/11/04 ���� takagi
	�E2023/11/06 �R�[�f�B���O�K��K�p�E�ǐՑΏۓo�^�@�\�쐬 takagi
	�E2023/11/07 GetViewMatrix()�֐���const�C���q�t�^�E�R�����g�C�� takagi
	�E2023/11/08 TPos�C�� takagi
	�E2023/11/10 �p�����^�C�� takagi
	�E2023/12/03 �ʒu�Q�b�^�p���� takagi
	�E2023/12/04 GetViewWithoutTranspose�̖߂�l��ύX ymaashita

========================================== */

#ifndef ___CAMERA_CHASE_H___
#define ___CAMERA_CHASE_H___

// =============== �C���N���[�h ===================
#include "Camera.h"	//�e�̃w�b�_

// =============== �N���X��` =====================
class CCameraChase :public CCamera	//�J����
{
public:
	// ===�v���g�^�C�v�錾===
	CCameraChase(const TPos3d<float>* pPos);					//�R���X�g���N�^
	~CCameraChase();											//�f�X�g���N�^
	void Update();												//�X�V
	DirectX::XMFLOAT4X4 GetViewWithoutTranspose() const override;	//�]�u�����r���[�s��擾
private:
	// ===�����o�ϐ��錾===
	const TPos3d<float>* m_pTarget;	//�ǐՖڕW
	// ===�v���g�^�C�v�錾===
	void UpdatePos();	//�ʒu�X�V
};	//�ǐՃJ����

#endif // !___CAMERA_CHASE_H___