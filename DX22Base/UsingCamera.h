///* ========================================
//	HEW/UniBoooom!!
//	---------------------------------------
//	�^�C�g���J�n���Y�[���A�E�g�p�J�E���^��`
//	---------------------------------------
//	UsingCamera.h
//
//	�쐬��	takagi
//
//	�ύX����
//	�E2024/02/02 ���� takagi
//	�E2024/02/05 �뎚�C���E�ꕔ�������� takagi
//
//========================================== */
//
//#ifndef __TITLE_INIT_COUNTER_H__	//UsingCamera.h�C���N���[�h�K�[�h
//#define __TITLE_INIT_COUNTER_H__
//
//// =============== �C���N���[�h =====================
//#include "TitleObj.h"	//�e�̃w�b�_
//#include <memory.h>		//ptr�Ǘ�
//
//// =============== �N���X��` =====================
//class CUsingCamera
//{
//public:
//	// ===�v���g�^�C�v�錾===
//	virtual void Update() final;											//�X�V
//	virtual void StartCount() final;										//�J�E���^�n��
//	static const std::weak_ptr<const CUsingCamera>& GetThis();			//���g�̃Q�b�^
//	virtual const std::weak_ptr<const CFrameCnt>& GetCounter() const final;	//�J�E���^�Q�b�^
//private:
//	// ===�ϐ��錾===========
//	static std::shared_ptr<CCamera> ms_pDefCamera;				//�k���J�E���^
//	static bool ms_bCountStarted;								//�J�E���g���J�n�������Ƃ����邩(true�F����)
//	// ===�v���g�^�C�v�錾===
//	CUsingCamera();										//�R���X�g���N�^
//	CUsingCamera(const CUsingCamera& Obj);			//�R�s�[�R���X�g���N�^
//	CUsingCamera& operator=(const CUsingCamera& Obj);	//������Z�q
//	~CUsingCamera();										//�f�X�g���N�^
//};	//�^�C�g���J�n���Y�[���A�E�g�Ɏg�p����J�E���^
//
//#endif	//!__TITLE_INIT_COUNTER_H__