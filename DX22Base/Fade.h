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

========================================== */

#ifndef ___FADE_H___	//Fade.h�C���N���[�h�K�[�h
#define ___FADE_H___

// =============== �C���N���[�h ===================
#include "Sprite.h"
#include "Camera.h"		//�J����

// =============== �N���X��` =====================
class CFade : public Sprite
{
};	//�t�F�[�h

#endif // !___FADE_H___


















//
///* ========================================
//	HEW/UniBoooom!!
//	------------------------------------
//	�t�F�[�h��`
//	------------------------------------
//	Fade.h
//	------------------------------------
//	�쐬��	takagi
//
//	�ύX����
//	�E2023/11/18 ���� takagi
//
//========================================== */
//
//#ifndef ___FADE_H___	//Fade.h�C���N���[�h�K�[�h
//#define ___FADE_H___
//
//// =============== �C���N���[�h ===================
//#include "Shader.h"		//�V�F�[�_�[
//#include "Texture.h"	//�e�N�X�`��
//#include "Camera.h"		//�J����
//
//// =============== �N���X��` =====================
//class CFade
//{
//private:
//	// ===�\���̒�`=========
//	struct Vertex
//	{
//		float pos[3];
//		float uv[2];
//	};
//public:
//	// ===�v���g�^�C�v�錾===
//	CFade(const CCamera*);					//�R���X�g���N�^
//	CFade(const CFade& Obj);	//�R�s�[�R���X�g���N�^
//	~CFade();					//�f�X�g���N�^
//	void Update();				//�X�V
//	void Draw();				//�`��
//	void SetTexture(const std::string sTexPass);	//�e�N�X�`���o�^
//private:
//	// ===�����o�ϐ��錾=====
//	Texture* m_pTexture;			//�e�N�X�`�����
//	static int ms_nCntFade;			//���g�̐�����
//	static VertexShader* ms_pVs;	//���_�V�F�[�_�[
//	static PixelShader* ms_pPs;		//�s�N�Z���V�F�[�_�[
//
//	static const void* ms_pVtx;
//	static unsigned int ms_unVtxSize;
//	static unsigned int ms_unVtxCount;
//	//static bool isWrite;
//	static const void* ms_pIdx;
//	static unsigned int ms_unIdxSize;
//	static unsigned int ms_unIdxCount;
//	static ID3D11Buffer* ms_pVtxBuffer;
//	static ID3D11Buffer* ms_pIdxBuffer;
//	DirectX::XMFLOAT4X4 matrix[3];
//	const CCamera* m_pCamera;
//
//	// ===�v���g�^�C�v�錾===
//	static void MakeShader();						//�V�F�[�_�[�쐬
//	static void Make();								//�`�쐬
//	static void CreateVtxBuffer();
//	static void CreateIdxBuffer();
//};	//�t�F�[�h
//
//#endif // !___FADE_H___