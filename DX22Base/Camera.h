/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�J�����p���ۃN���X��`
	------------------------------------
	CameraChase.h
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/10/24 ������ takagi
	�E2023/11/02 �����o�[�ϐ��ǉ� takagi
	�E2023/11/04 �t���O�ǉ��H�Eprivate��protected�E���̑����X�C�� takagi
	�E2023/11/06 �t���O�����E�R�����g�C�� takagi
	�E2023/11/07 GetViewMatrix()�֐���const�C���q�t�^�E�R�����g�C�� takagi
	�E2023/11/08 TPos�C�� takagi
	�E2023/11/10 �p�����^�C�� takagi
	�E2023/11/17 2D�\��/3D�\���̐؊����R���X�g���N�^�łȂ�GetProjectionMatrix()�֐��ōs���悤�ɕύX
					�E�t���O����2D/3D�̊T�O���폜�E�U���@�\�ǉ� takagi
	�E2023/11/28 �U���̎d�l�ύX takagi
	�E2023/11/29 �U���̐V�d�l��S�U���ɔ��f�����t�@�N�^�����O takagi
	�E2023/11/30 Effekseer�p�Ɋ֐��ǉ� takagi
	�E2023/12/03 �ʒu�Q�b�^�쐬 takagi
	�E2023/12/04 GetViewWithoutTranspose,GetProjectionWithoutTranspose�̖߂�l��ύX yamashita
	�E2023/12/05 �h��̃J�E���^�ǉ� takagi
	�E2023/12/16 �Y�[���@�\�ǉ� takagi
	�E2024/01/16 ����̂��߁A�C���N���[�h�K�[�h��___��__�ɕύX	takagi
	�E2024/01/20 �R�����g���C takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __CAMERA_H__	//Camera.h�C���N���[�h�K�[�h
#define __CAMERA_H__

// =============== �C���N���[�h ===================
//#include "System.h"		//�e�̃w�b�_
#include "Pos3d.h"			//�����o�̃w�b�_
#include "TriType.h"		//�����o�̃w�b�_
#include "DiType.h"			//�����o�̃w�b�_
#include "FrameCnt.h"		//�����o�̃w�b�_
#include <DirectXMath.h>	//�}�g���b�N�X�^�g�p
#include "Defines.h"		//��ʏ��

// =============== �N���X��` =====================
class CCamera	//�V�X�e��
{
public:
	// ===�񋓒�`===========
	enum E_DRAW_TYPE
	{
		E_DRAW_TYPE_2D,	//2D�\��
		E_DRAW_TYPE_3D	//3D�\��
	};	//�\���`��
	enum E_BIT_FLAG
	{
		E_BIT_FLAG_VIBRATION_UP_DOWN_WEAK = 0x01,	//�c�h��E��
		E_BIT_FLAG_VIBRATION_UP_DOWN_STRONG = 0x02,	//�c�h��E��
		E_BIT_FLAG_VIBRATION_SIDE_WEAK = 0x04,		//���h��E��
		E_BIT_FLAG_VIBRATION_SIDE_STRONG = 0x08,	//���h��E��
		E_BIT_FLAG_5 = 0x10,						//
		E_BIT_FLAG_6 = 0x20,						//
		E_BIT_FLAG_7 = 0x40,						//
		E_BIT_FLAG_8 = 0x80,						//
	};	//�t���O
public:
	// ===�v���g�^�C�v�錾===
	CCamera();																		//�R���X�g���N�^
	virtual~CCamera();																//�f�X�g���N�^
	virtual void Update() = 0;														//�X�V
	void UpFlag(const unsigned char& ucBitFlag);									//OR							00:0,01:1,10:1,11:1
	void DownFlag(const unsigned char& ucBitFlag);									//A AND !B						00:0,01:0,10:1,11:0
	void SetFlag(const unsigned char& ucBitFlag);									//XOR�F�グ�����ǂ������ł���	00:0,01:1,10:1,11:0
	DirectX::XMFLOAT4X4 GetViewMatrix() const;										//�r���[�s��ϊ�
	DirectX::XMMATRIX GetInverseViewMatrix() const;									//�r���[�s��̋t�s��擾
	DirectX::XMFLOAT4X4 GetProjectionMatrix(
		const E_DRAW_TYPE& eDraw = E_DRAW_TYPE_3D) const;							//�v���W�F�N�V�����s��ϊ�
	virtual DirectX::XMFLOAT4X4 GetViewWithoutTranspose() const;					//�]�u�����r���[�s��擾
	DirectX::XMFLOAT4X4 GetProjectionWithoutTranspose() const;						//�]�u�����v���W�F�N�V�����s��擾
	virtual TPos3d<float> GetPos() const;											//�J�����ʒu��
	void ChangeScaleVibrate(const int& nChangeFrame, const float& fChangegRateAmp);	//�U���̋K�͂�ύX����
	void BootZoom(const float& fFinRadius, const int& nFrame = 0,
		const bool& bDefMode = true, const float& fStartRadius = 1.0f);				//�Y�[��/�C���A�E�g�N��
	void SetRadius(const float& fRadius);											//�����Z�b�^
protected:
	// ===�����o�ϐ��錾=====
	TPos3d<float> m_fPos;					//���[���h���W�ɂ����鎩�g�̈ʒu
	TPos3d<float> m_fLook;					//�����_�̈ʒu
	TTriType<float> m_fUp;					//����x�N�g��
	float m_fAngle;							//�p�x
	float m_fNear;							//��ʎ�O
	float m_fFar;							//��ʉ�
	float m_fRadius;						//����
	TDiType<float> m_fOffsetVibrateEye;		//�J�����ʒu�U��(x,z)
	TDiType<float> m_fOffsetVibrateLook;	//�����_�U��(x,z)
	// ===�v���g�^�C�v�錾===
	void HandleFlag();	//�t���O�ʏ���
	void Zoom();		//�Y�[��/�C���A�E�g�@�\
private:
	// ===�����o�ϐ��錾=====
	unsigned char m_ucFlag;							//�t���O	char:1�o�C�g(8�r�b�g)
	TDiType<int> m_nFrameWeak;						//�t���[���J�E���^�F��U��	x:��, y:�c
	TDiType<int> m_nFrameStrong;					//�t���[���J�E���^�F���U��	x:��, y:�c
	TDiType<float> m_fChangeRateAmplitudeWeak;		//�U���␳���F��			x:��, y:�c
	TDiType<float> m_fChangeRateAmplitudeStrong;	//�U���␳���F��			x:��, y:�c
	int m_nCntChangeVibrate;						//�J�����h��ύX��
	CFrameCnt* m_pZoomCnt;							//�Y�[���@�\�p�J�E���^�[
	float* m_pfGoalRadius;							//�Y�[���ڕW����
	float* m_pfStartRadius;							//�Y�[���J�n����
};	//�J����

#endif	//!__CAMERA_H__