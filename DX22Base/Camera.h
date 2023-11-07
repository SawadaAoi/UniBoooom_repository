/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�J�����p���ۃN���X��`
	------------------------------------
	CameraChase.h
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/10/24	������
	�E2023/11/02	�����o�[�ϐ��ǉ�
	�E2023/11/04	�t���O�ǉ��H�Eprivate��protected�E���̑����X�C��
	�E2023/11/06	�t���O�����E�R�����g�C��

========================================== */

#ifndef ___CAMERA_H___
#define ___CAMERA_H___

// =============== �C���N���[�h ===================
//#include "System.h"		//�e�̃w�b�_
#include "Pos.h"			//�����o�̃w�b�_
#include "TriType.h"		//�����o�̃w�b�_
//#include "main.h"	//��ʂ̏��
#include <DirectXMath.h>	//�}�g���b�N�X�^�g�p

// =============== �萔��` =====================
//const float ASPECT = _WIDTH / _HEIGHT;
const float ASPECT = 16.0f / 9.0f;	//��ʔ䗦(y / x)

// =============== �N���X��` =====================
class CCamera	//�V�X�e��
{
public:
	//���񋓒�`
	enum E_DRAW_TYPE
	{
		E_DRAW_TYPE_2D,	//2D�\��
		E_DRAW_TYPE_3D	//3D�\��
	};	//�\���`��
	enum E_BIT_FLAG
	{
		E_BIT_FLAG_AS_2D = 0x00,		//2D�̂悤�ɕ`�悷��(�t���O�������Ă��Ȃ��Ƃ���3D�Ƃ��ĕ`��)
		E_BIT_FLAG_VIBRATION = 0x01,	//��ʐU��
		E_BIT_FLAG_3,					//
		E_BIT_FLAG_4,					//
		E_BIT_FLAG_5,					//
		E_BIT_FLAG_6,					//
		E_BIT_FLAG_7,					//
		E_BIT_FLAG_MAX,					//�v�f��
	};	//�t���O
protected:
	//���ϐ��錾
	unsigned char m_ucFlag;	//�t���O	char:1�o�C�g(8�r�b�g)
	TPos<float> m_fPos;		//���[���h���W�ɂ����鎩�g�̈ʒu
	TPos<float> m_fLook;	//�����_�̈ʒu
	TTriType<float> m_fUp;	//����x�N�g��
	float m_fAngle;			//�p�x
	float m_fNear;			//��ʎ�O
	float m_fFar;			//��ʉ�
	float m_fRadius;		//����
	float m_fRadXZ;			//X-Z���W�̉�]�p(rad)
	float m_fRadY;			//Y-XZ���W�̉�]�p(rad)
public:
	//���v���g�^�C�v�錾
	CCamera(const E_DRAW_TYPE& eDraw = E_DRAW_TYPE_3D);	//�R���X�g���N�^
	virtual~CCamera();									//�f�X�g���N�^
	virtual void Update() = 0;							//�X�V
	//void ZoomIn();
	//void ZoomOut();
	void UpFlag(const unsigned char& ucBitFlag);		//OR	 00:0,01:1,10:1,11:1
	void DownFlag(const unsigned char& ucBitFlag);		//A AND !B	00:0,01:0,10:1,11:0
	void SetFlag(const unsigned char& ucBitFlag);		//XOR�F�グ�����ǂ������ł���	00:0,01:1,10:1,11:0
	virtual DirectX::XMFLOAT4X4 GetViewMatrix();		//�r���[�s��ϊ�
	DirectX::XMFLOAT4X4 GetProjectionMatrix();			//�v���W�F�N�V�����s��ϊ�
};	//�J����

#endif // !___CAMERA_H___