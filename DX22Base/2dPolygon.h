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
	C2dPolygon();										//�R���X�g���N�^
	C2dPolygon(const C2dPolygon& Obj);					//�R�s�[�R���X�g���N�^
	~C2dPolygon();										//�f�X�g���N�^
	void Draw();										//�`��
	void SetCamera(const CCamera* pCamera);				//�J�����Z�b�^
	void SetPos(TPos3d<float> fPos);					//�ʒu�Z�b�^
	void SetSize(TTriType<float> fScale);				//�傫���Z�b�^
	void SetRotate(TTriType<float> fRotate);			//��]�Z�b�^
	void SetTransform(tagTransform3d Transform);		//���[���h���W�Z�b�^
	void SetUvOffset(TDiType<float> fUvOffset);			//UV����Z�b�^
	void SetUvScale(TDiType<float> fUvScale);			//UV�g�k�Z�b�^
	void SetColor(TTriType<float> fRGB, float fAlpha);	//�F�Z�b�^RGBA
	void SetColor(TTriType<float> fRGB);				//�F�Z�b�^RGB
	void SetColor(float fColor);						//�F�Z�b�^(����l)
	void SetAlpha(float fAlpha);						//�����x�Z�b�^
	void SetTexture(const char* pcTexPass);				//�e�N�X�`���o�^
	void SetTexture(Texture* pTexture);				//�e�N�X�`���o�^
	void SetVertexShader(VertexShader* pVs);			//���_�V�F�[�_�Z�b�^
	void SetPixelShader(PixelShader* pPs);				//�s�N�Z���V�F�[�_�Z�b�^
private:
	// ===�����o�ϐ��錾=====
	tagTransform3d m_Transform;			//���[���h���W
	DirectX::XMFLOAT4X4 m_aMatrix[3];	//�s��
	Param m_Param;						//�V�F�[�_�[�ɏ������ޏ��
	static VertexShader* m_pDefVs;				//���_�V�F�[�_�[
	static PixelShader* m_pDefPs;					//�s�N�Z���V�F�[�_�[
	VertexShader* m_pVs;				//���_�V�F�[�_�[
	PixelShader* m_pPs;					//�s�N�Z���V�F�[�_�[
	Texture* m_pTexture;				//�e�N�X�`�����
	static int ms_nCnt2dPolygon;		//���g�̐�����
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
	void MakeVertexShader();		//���_�V�F�[�_�쐬
	void MakePixelShader();			//�s�N�Z���V�F�[�_�[
	static void Make();				//�`�쐬
	static void CreateVtxBuffer();	//���_�o�b�t�@�쐬
	static void CreateIdxBuffer();	//�C���f�b�N�X�o�b�t�@�쐬
};	//�t�F�[�h

#endif // !___2D_POLYGON_H___