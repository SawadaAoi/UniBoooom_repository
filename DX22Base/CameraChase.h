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
	�E2023/11/06 �R�[�f�B���O�K��K�p�E�ǐՑΏۓo�^�@�\�쐬

========================================== */

#ifndef ___CAMERA_CHASE_H___
#define ___CAMERA_CHASE_H___

// =============== �C���N���[�h ===================
#include "Camera.h"	//�e�̃w�b�_

// =============== �N���X��` =====================
class CCameraChase :public CCamera	//�J����
{
public:
	// ===�����o�֐��錾===
	CCameraChase(const TPos<float>* pPos);			//�R���X�g���N�^
	~CCameraChase();								//�f�X�g���N�^
	void Update();									//�X�V
	//void Draw();									//�`��		//UI���J�����̕��Ɏ�������Ȃ����
	DirectX::XMFLOAT4X4 GetViewMatrix() override;	//�r���[�s��ϊ�
private:
	// ===�����o�ϐ��錾===
	const TPos<float>* m_pTarget;	//�ǐՖڕW
};	//�ǐՃJ����

#endif // !___CAMERA_CHASE_H___