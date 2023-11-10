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

========================================== */

#ifndef ___CAMERA_H___
#define ___CAMERA_H___

// =============== �C���N���[�h ===================
//#include "System.h"		//�e�̃w�b�_
#include "Pos3d.h"			//�����o�̃w�b�_
#include "TriType.h"		//�����o�̃w�b�_
//#include "main.h"	//��ʂ̏��
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
		E_BIT_FLAG_AS_2D = 0x01,		//2D�̂悤�ɕ`�悷��(�t���O�������Ă��Ȃ��Ƃ���3D�Ƃ��ĕ`��)
		E_BIT_FLAG_VIBRATION = 0x02,	//��ʐU��
		E_BIT_FLAG_3 = 0x04,			//
		E_BIT_FLAG_4 = 0x08,			//
		E_BIT_FLAG_5 = 0x10,			//
		E_BIT_FLAG_6 = 0x20,			//
		E_BIT_FLAG_7 = 0x40,			//
		E_BIT_FLAG_8 = 0x80,			//
	};	//�t���O
protected:
	// ===�����o�ϐ��錾=====
	unsigned char m_ucFlag;	//�t���O	char:1�o�C�g(8�r�b�g)
	TPos3d<float> m_fPos;	//���[���h���W�ɂ����鎩�g�̈ʒu
	TPos3d<float> m_fLook;	//�����_�̈ʒu
	TTriType<float> m_fUp;	//����x�N�g��
	float m_fAngle;			//�p�x
	float m_fNear;			//��ʎ�O
	float m_fFar;			//��ʉ�
	float m_fRadius;		//����
public:
	// ===�v���g�^�C�v�錾===
	CCamera(const E_DRAW_TYPE& eDraw = E_DRAW_TYPE_3D);	//�R���X�g���N�^
	virtual~CCamera();									//�f�X�g���N�^
	virtual void Update() = 0;							//�X�V
	void UpFlag(const unsigned char& ucBitFlag);		//OR	 00:0,01:1,10:1,11:1
	void DownFlag(const unsigned char& ucBitFlag);		//A AND !B	00:0,01:0,10:1,11:0
	void SetFlag(const unsigned char& ucBitFlag);		//XOR�F�グ�����ǂ������ł���	00:0,01:1,10:1,11:0
	virtual DirectX::XMFLOAT4X4 GetViewMatrix() const;	//�r���[�s��ϊ�
	DirectX::XMFLOAT4X4 GetProjectionMatrix() const;	//�v���W�F�N�V�����s��ϊ�
protected:
	void HandleFlag();	//�t���O�ʏ���
private:
	void Vibration();	//�U��
	//void Zoom();	//�Y�[���C��(�A�E�g)
};	//�J����

#endif // !___CAMERA_H___