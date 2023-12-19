/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	���ʃ|���S����`
	------------------------------------
	2dPolygon.h
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/11/21 �쐬 takagi
	�E2023/11/28 TextureSet�֐��Ƀ|�C���^�w��ł��镨��ǉ�
	�E2023/12/01 �e�N�X�`���̈����������S�� takagi
	�E2023/12/05 �`��̃��[�h�ǉ� takagi
	�E2023/12/06 Draw()�֐��̃f�t�H���g�����ύX takagi
	�E2023/12/10 �ÓI�ϐ��̖��O���C���E�f�t�H���g�̃J�������ÓI�֐����B takagi
	�E2023/12/15 ��̍X�V�֐��ǉ� takagi
	�E2023/12/17 �����Q�Ɖ� takagi
	�E2023/12/20 �p���悪���ɂ��������̂Ń��[���h�ϐ���protected�� takagi

========================================== */

#ifndef ___2D_POLYGON_H___	//2dPolygon.h�C���N���[�h�K�[�h
#define ___2D_POLYGON_H___

// =============== �C���N���[�h ===================
#include "Shader.h"			//�����o�̃w�b�_
#include "Texture.h"		//�����o�̃w�b�_
#include "Camera.h"			//�����o�̃w�b�_
#include "Transform3d.h"	//�����o�̃w�b�_
#include "DiType.h"			//�����o�̃w�b�_
#include "TriType.h"		//�����o�̃w�b�_
#include "Transform3d.h"	//�����o�̃w�b�_

// =============== �N���X��` =====================
class C2dPolygon
{
public:
	enum E_DRAW_MODE
	{
		E_DRAW_MODE_NORMAL,		//�ʏ�̕`��
		E_DRAW_MODE_BILLBOARD,	//�r���{�[�h�Ƃ��ĕ`��
	};
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
public:
	// ===�v���g�^�C�v�錾===
	C2dPolygon();																//�R���X�g���N�^
	C2dPolygon(const C2dPolygon& Obj);											//�R�s�[�R���X�g���N�^
	virtual ~C2dPolygon();														//�f�X�g���N�^
	virtual void Update();														//�X�V
	virtual void Draw(const E_DRAW_MODE& eMode = E_DRAW_MODE_NORMAL);			//�`��
	virtual void SetCamera(const CCamera* pCamera);								//�J�����Z�b�^
	virtual void SetPos(const TPos3d<float>& fPos);								//�ʒu�Z�b�^
	virtual void SetSize(const TTriType<float>& fScale);						//�傫���Z�b�^
	virtual void SetRotate(const TTriType<float>& fRotate);						//��]�Z�b�^
	virtual void SetTransform(const tagTransform3d& Transform);					//���[���h���W�Z�b�^
	virtual void SetUvOffset(const TDiType<float>& fUvOffset);					//UV����Z�b�^
	virtual void SetUvScale(const TDiType<float>& fUvScale);					//UV�g�k�Z�b�^
	virtual void SetColor(const TTriType<float>& fRGB, const float& fAlpha);	//�F�Z�b�^RGBA
	virtual void SetColor(const TTriType<float>& fRGB);							//�F�Z�b�^RGB
	virtual void SetColor(const float& fColor);									//�F�Z�b�^(����l)
	virtual void SetAlpha(const float& fAlpha);									//�����x�Z�b�^
	virtual void SetTexture(const char* pcTexPass);								//�e�N�X�`���o�^
	virtual void SetTexture(Texture* pTexture);									//�e�N�X�`���o�^
	virtual void SetVertexShader(VertexShader* pVs);							//���_�V�F�[�_�Z�b�^
	virtual void SetPixelShader(PixelShader* pPs);								//�s�N�Z���V�F�[�_�Z�b�^
protected:
	// ===�����o�ϐ��錾=====
	tagTransform3d m_Transform;	//���[���h���W
private:
	// ===�����o�ϐ��錾=====
	DirectX::XMFLOAT4X4 m_aMatrix[3];		//�s��
	Param m_Param;							//�V�F�[�_�[�ɏ������ޏ��
	static VertexShader* ms_pDefVs;			//���_�V�F�[�_�[
	static PixelShader* ms_pDefPs;			//�s�N�Z���V�F�[�_�[
	VertexShader* m_pVs;					//���_�V�F�[�_�[
	PixelShader* m_pPs;						//�s�N�Z���V�F�[�_�[
	Texture* m_pTexture;					//�e�N�X�`�����
	Texture* m_pTextureLoad;				//�e�N�X�`�����	delete���Ȃ��A�|�C���^�͎󂯎�邾��
	static int ms_nCnt2dPolygon;			//���g�̐�����
	static const void* ms_pVtx;				//���_���
	static unsigned int ms_unVtxSize;		//���_�T�C�Y
	static unsigned int ms_unVtxCount;		//���_��
	static const void* ms_pIdx;				//���_�C���f�b�N�X
	static unsigned int ms_unIdxSize;		//�C���f�b�N�X�T�C�Y
	static unsigned int ms_unIdxCount;		//�C���f�b�N�X��
	static ID3D11Buffer* ms_pVtxBuffer;		//���_�o�b�t�@
	static ID3D11Buffer* ms_pIdxBuffer;		//�C���f�b�N�X�o�b�t�@
	const CCamera* m_pCamera;				//�J�����ǐ�
	static const CCamera* ms_pCameraDef;	//�^���J����
	// ===�v���g�^�C�v�錾===
	void MakeVertexShader();		//���_�V�F�[�_�쐬
	void MakePixelShader();			//�s�N�Z���V�F�[�_�[
	static void Make();				//�`�쐬
	static void CreateVtxBuffer();	//���_�o�b�t�@�쐬
	static void CreateIdxBuffer();	//�C���f�b�N�X�o�b�t�@�쐬
};	//�t�F�[�h

#endif // !___2D_POLYGON_H___