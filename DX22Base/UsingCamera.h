/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�g�p���J������`
	---------------------------------------
	UsingCamera.h

	�쐬��	takagi

	�ύX����
	�E2024/02/06 �t�@�C���쐬 takagi
	�E2024/02/08 ����J�n takagi

========================================== */

#ifndef __USING_CAMERA_H__	//UsingCamera.h�C���N���[�h�K�[�h
#define __USING_CAMERA_H__

// =============== �C���N���[�h =====================
#include "Camera.h"		//�J����
#include "CameraDef.h"	//�f�t�H���g�̃J����
#include <memory>		//ptr�Ǘ�

// =============== �N���X��` =====================
class CUsingCamera
{
public:
	// ===�v���g�^�C�v�錾===
	static CUsingCamera& GetThis();									//���g�̃Q�b�^
	virtual const std::shared_ptr<CCamera> GetCamera() const final;	//�J�����Q�b�^	���킴�Ɩ߂�l�͎Q�ƂłȂ�
	virtual void SetCamera(std::shared_ptr<CCamera> pCamera) final;	//�J�����Z�b�^
private:
	// ===�ϐ��錾===========
	static const std::shared_ptr<CCameraDef> ms_pDefCamera;	//�f�t�H���g�̃J����
	static std::weak_ptr<CCamera> ms_pUsingCamera;			//�g�p���̃J����
	// ===�v���g�^�C�v�錾===
	CUsingCamera();										//�R���X�g���N�^
	CUsingCamera(const CUsingCamera& Obj);				//�R�s�[�R���X�g���N�^
	CUsingCamera& operator=(const CUsingCamera& Obj);	//������Z�q
	~CUsingCamera();									//�f�X�g���N�^
};	//�g�p���̃J�����Ǘ�

#endif	//!__USING_CAMERA_H__