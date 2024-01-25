/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	2D�I�u�W�F�N�g��`
	------------------------------------
	2dObject.h
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/11/21 �쐬 takagi
	�E2023/11/28 TextureSet�֐��Ƀ|�C���^�w��ł��镨��ǉ� takagi
	�E2023/12/01 �e�N�X�`���̈����������S�� takagi
	�E2023/12/05 �`��̃��[�h�ǉ� takagi
	�E2023/12/06 Draw()�֐��̃f�t�H���g�����ύX takagi
	�E2023/12/10 �ÓI�ϐ��̖��O���C���E�f�t�H���g�̃J�������ÓI�֐����B takagi
	�E2023/12/15 ��̍X�V�֐��ǉ� takagi
	�E2023/12/17 �����Q�Ɖ� takagi
	�E2023/12/20 �p���悪���ɂ��������̂Ń��[���h�ϐ���protected�� takagi
	�E2024/01/16 ����̂��߁A�C���N���[�h�K�[�h��___��__�ɕύX	takagi
	�E2024/01/16 ���l�[���E�p���E�s�v�ӏ��폜 takagi
	�E2024/01/18 ���t�@�N�^�����O�y�уR�����g�ǉ� takagi
	�E2024/01/20 GetPos()�֐��ǉ� takagi
	�E2024/01/21 �R�����g���C�E�萔�C���E�ĉ���� takagi
	�E2024/01/22 Draw()�֐�const�� takagi

========================================== */

#ifndef __2D_OBJECT_H__	//2dObject.h�C���N���[�h�K�[�h
#define __2D_OBJECT_H__

// =============== �C���N���[�h ===================
#include "Object.h"		//�e�̃w�b�_
#include "Texture.h"	//�����o�̃w�b�_

// =============== �N���X��` =====================
class C2dObject	:public CObject	//�I�u�W�F�N�g�p��
{
public:
	// ===�񋓒�`===========
	enum E_DRAW_MODE
	{
		E_DRAW_MODE_NORMAL,		//�ʏ�̕`��
		E_DRAW_MODE_BILLBOARD,	//�r���{�[�h�Ƃ��ĕ`��
	};	//�`����@
private:
	// ===�\���̒�`=========
	typedef struct
	{
		float fPos[3];	//�ʒu���
		float fUv[2];	//UV���
	}Vertex;	//���_���
	typedef struct
	{
		TDiType<float> fUvOffset;	//UV���W�̃Y��
		TDiType<float> fUvScale;	//UV�g�k
		TTriType<float> fColor;		//�F
		float fAlpha;				//�����x
	}Param;	//�V�F�[�_�[�ɑ�����
	// ===�萔��`===========
	static const E_DRAW_MODE DEFAULT_DRAW_MODE = E_DRAW_MODE_NORMAL;	//�`����@�̋K��l
	const int FRAME_MIN = 0;											//�t�F�[�h���Ԃ̍ŏ�
	const int FRAME_TURNING_1 = 50;										//�g�k���]�P���]
	const int FRAME_TURNING_2 = 100;									//�g�k���]�Q���]
	const int FRAME_MAX = 150;											//�t�F�[�h���Ԃ̍ő�
	const float SCALE_MIN = 0.0f;										//�ŏ��T�C�Y
	const float SCALE_TURNINIG_2 = 30.0f;								//�T�C�Y���]�Q���]
	const float SCALE_TURNINIG_1 = 100.0f;								//�T�C�Y���]�P���]
	const float SCALE_MAX = 1000.0f;									//�ő�T�C�Y
	const float ROTATE_ACCEL_RATE = 4.0f;								//�p���x��������
	const TPos3d<float> INIT_POS = { 640.0f, 360.0f, 0.0f };			//�����ʒu
	const TTriType<float> INIT_SCALE = { 1.0f, 1.0f, 0.0f };			//�����g�k
public:
	// ===�v���g�^�C�v�錾===
	C2dObject();																	//�R���X�g���N�^
	C2dObject(const C2dObject& Obj);												//�R�s�[�R���X�g���N�^
	virtual ~C2dObject();															//�f�X�g���N�^
	virtual void Update();															//�X�V
	virtual void Draw() const override;												//�`��
	virtual void SetDrawMode(const E_DRAW_MODE& eMode = DEFAULT_DRAW_MODE) final;	//�`��@�Z�b�^
	virtual void SetUvOffset(const TDiType<float>& fUvOffset) final;				//UV����Z�b�^
	virtual void SetUvScale(const TDiType<float>& fUvScale) final;					//UV�g�k�Z�b�^
	virtual void SetColor(const TTriType<float>& fRGB, const float& fAlpha) final;	//�F�Z�b�^RGBA
	virtual void SetColor(const TTriType<float>& fRGB) final;						//�F�Z�b�^RGB
	virtual void SetColor(const float& fColor) final;								//�F�Z�b�^(����l)
	virtual void SetAlpha(const float& fAlpha) final;								//�����x�Z�b�^
	virtual void SetTexture(const char* pcTexPass) final;							//�e�N�X�`���o�^
	virtual void SetTexture(Texture* pTexture) final;								//�e�N�X�`���o�^
	virtual void SetVertexShader(VertexShader* pVs) final;							//���_�V�F�[�_�Z�b�^
	virtual void SetPixelShader(PixelShader* pPs) final;							//�s�N�Z���V�F�[�_�Z�b�^
private:
	// ===�����o�ϐ��錾=====
	Param m_Param;									//�V�F�[�_�[�ɏ������ޏ��
	static VertexShader* ms_pDefVs;					//�f�t�H���g���_�V�F�[�_�[
	static PixelShader* ms_pDefPs;					//�f�t�H���g�s�N�Z���V�F�[�_�[
	VertexShader* m_pVs;							//���_�V�F�[�_�[
	PixelShader* m_pPs;								//�s�N�Z���V�F�[�_�[
	Texture* m_pTexture;							//�e�N�X�`�����
	Texture* m_pTextureLoad;						//�e�N�X�`�����	delete���Ȃ��A�|�C���^�͎󂯎�邾��
	E_DRAW_MODE m_eMode;							//�`����@
	static int ms_nCnt2dObject;						//���g�̐�����
	static const void* ms_pVtx;						//���_���
	static unsigned int ms_unVtxSize;				//���_�T�C�Y
	static unsigned int ms_unVtxCount;				//���_��
	static const void* ms_pIdx;						//���_�C���f�b�N�X
	static unsigned int ms_unIdxSize;				//�C���f�b�N�X�T�C�Y
	static unsigned int ms_unIdxCount;				//�C���f�b�N�X��
	static ID3D11Buffer* ms_pVtxBuffer;				//���_�o�b�t�@
	static ID3D11Buffer* ms_pIdxBuffer;				//�C���f�b�N�X�o�b�t�@
	// ===�v���g�^�C�v�錾===
	void MakeVertexShader();		//���_�V�F�[�_�쐬
	void MakePixelShader();			//�s�N�Z���V�F�[�_�[
	static void Make();				//�`�쐬
	static void CreateVtxBuffer();	//���_�o�b�t�@�쐬
	static void CreateIdxBuffer();	//�C���f�b�N�X�o�b�t�@�쐬
};	//2D�I�u�W�F�N�g

#endif	//!__2D_OBJECT_H__