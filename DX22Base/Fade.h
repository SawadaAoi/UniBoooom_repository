/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�t�F�[�h��`
	------------------------------------
	Fade.h
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/11/18 ���� takagi
	�E2023/11/19 18�̑��� takagi
	�E2023/11/20 ���� takagi

========================================== */

#ifndef ___FADE_H___	//Fade.h�C���N���[�h�K�[�h
#define ___FADE_H___

// =============== �C���N���[�h ===================
#include "Shader.h"			//�����o�̃w�b�_
#include "Texture.h"		//�����o�̃w�b�_
#include "Camera.h"			//�����o�̃w�b�_
#include "Transform3d.h"	//�����o�̃w�b�_
#include "DiType.h"			//�����o�̃w�b�_
#include "TriType.h"		//�����o�̃w�b�_

// =============== �萔��` ===================
const TTriType<int> SUBSTITUTE_FRAME_FADE(150, 60, 150);	//�t�F�[�h�ɂ�����t���[�����̑�֒l

// =============== �N���X��` =====================
class CFade
{
private:
	// ===�\���̒�`=========
	typedef struct
	{
		float fPos[3];	//�ʒu���
		float fUv[2];	//UV���
	}Vertex;	//���_���
	typedef struct
	{
		//TDiType<float> fOffset;		//
		//TDiType<float> fSize;		//
		TDiType<float> fUvPos;		//
		TDiType<float> fUvScale;	//
		//TTriType<float> fColor;		//
		//float fAlpha;				//
	}UvParam;	//
	// ===�񋓒�`===========
	enum E_BIT_FLAG
	{
		E_BIT_FLAG_FADE_OUT = 0x01,		//�t�F�[�h�A�E�g�t���O
		E_BIT_FLAG_FADE_IN = 0x02,		//�t�F�[�h�C���t���O
		E_BIT_FLAG_FADE_STOP = 0x04,	//�t�F�[�h�X�g�b�v�t���O
		E_BIT_FLAG_4 = 0x08,			//
		E_BIT_FLAG_5 = 0x10,			//
		E_BIT_FLAG_6 = 0x20,			//
		E_BIT_FLAG_7 = 0x40,			//
		E_BIT_FLAG_8 = 0x80,			//

		E_BIT_FLAG_MAX = 3,				//�v�f��(�����ł�)
	};	//�t���O
	// ===�萔��`===========
	const unsigned char FLAG_FADE_ALL = E_BIT_FLAG_FADE_OUT | E_BIT_FLAG_FADE_STOP | E_BIT_FLAG_FADE_IN;	//�t�F�[�h�n�t���O�S��
public:
	// ===�v���g�^�C�v�錾===
	CFade(const CCamera* pCamera);								//�R���X�g���N�^
	CFade(const CFade& Obj);									//�R�s�[�R���X�g���N�^
	~CFade();													//�f�X�g���N�^
	void Update();												//�X�V
	void Draw();												//�`��
	void Start(TTriType<int> nFrame = SUBSTITUTE_FRAME_FADE);	//�t�F�[�h�J�n
private:
	// ===�����o�ϐ��錾=====
	unsigned char m_ucFlag;				//�t���O
	tagTransform3d m_Transform;			//���[���h���W
	DirectX::XMFLOAT4X4 m_aMatrix[3];	//�s��
	DirectX::XMFLOAT4 param[3];			//
	UvParam m_UvParam;					//UV���
	//FrameCnt
	int m_nFrameOut;
	int m_nFrameStop;
	//int m_nFrameIn;
	//bool m_bFadeOut;
	//bool m_bFadeIn;
	//bool m_bStop;
	static int ms_nCntFade;				//���g�̐�����
	static VertexShader* ms_pVs;		//���_�V�F�[�_�[
	static PixelShader* ms_pPs;			//�s�N�Z���V�F�[�_�[
	static Texture* ms_pTexture;		//�e�N�X�`�����
	static const void* ms_pVtx;			//���_���
	static unsigned int ms_unVtxSize;	//���_�T�C�Y
	static unsigned int ms_unVtxCount;	//���_��
	static const void* ms_pIdx;			//���_�C���f�b�N�X
	static unsigned int ms_unIdxSize;	//�C���f�b�N�X�T�C�Y
	static unsigned int ms_unIdxCount;	//�C���f�b�N�X��
	static ID3D11Buffer* ms_pVtxBuffer;	//���_�o�b�t�@
	static ID3D11Buffer* ms_pIdxBuffer;	//�C���f�b�N�X�o�b�t�@
	const CCamera* m_pCamera;			//�J�����ǐ�
	// ===�v���g�^�C�v�錾===
	static void Make();								//�`�쐬
	static void SetTexture();						//�e�N�X�`���o�^
	static void CreateVtxBuffer();					//���_�o�b�t�@�쐬
	static void CreateIdxBuffer();					//�C���f�b�N�X�o�b�t�@�쐬
	void UpFlag(const unsigned char& ucBitFlag);	//�t���O�N����
	void DownFlag(const unsigned char& ucBitFlag);	//�t���O�~�낵
	void SetFlag(const unsigned char& ucBitFlag);	//�t���O���]
};	//�t�F�[�h

#endif // !___FADE_H___