/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   ������`
   ---------------------------------------
   Line.h

   �쐬��	takagi

   �ύX����
   �E���܂� �w�Z�̔z�z��(���Ƃɉ����ό`)
   �E2023/11/05 �t�@�C�������E���ۃN���X���E�R�����g�t�^ takagi


   ======================================== */

#ifndef __LINE_H__
#define __LINE_H__

// =============== �C���N���[�h ===================
#include <DirectXMath.h>	//�s��v�Z�p
#include "Shader.h"			//�����o�̃w�b�_
#include "MeshBuffer.h"		//�����o�̃w�b�_

// =============== �N���X��` =====================
class CLine
{
protected:
	// =============== �\���̒�` =====================
	struct LineVertex
	{
		float pos[3];	//�ʒu
		float color[4];	//�F
	};	//�e�N�X�`����\��Ȃ��ꍇ�̒��_���H
private:
	// =============== �\���̒�` =====================
	enum E_MATRIX
	{
		E_MATRIX_WORLD = 0,		//���[���h�s��
		E_MATRIX_VIEW,			//�r���[�s��
		E_MATRIX_PROJECTION,	//�v���W�F�N�V�����s��
	};	//�s��
public:
	// =============== �v���g�^�C�v�錾 ===============
	static void Init();			//�R���X�g���N�^
	CLine(CLine& Obj);	//�R�s�[�R���X�g���N�^
	virtual ~CLine();	//�f�X�g���N�^

	static void MakeShader();	//�V�F�[�_�쐬

	static void Make();
	static void Draw();

	void Uninit();				//�I��

	static void Add(DirectX::XMFLOAT3 start, DirectX::XMFLOAT3 end,
		DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	static void SetWorld(DirectX::XMFLOAT4X4 World);		//���[���h�s��o�^
	static void SetView(DirectX::XMFLOAT4X4 View);			//�r���[�s��o�^
	static void SetProjection(DirectX::XMFLOAT4X4 Proj);	//�v���W�F�N�V�����s��o�^
protected:
	// =============== �����o�[�ϐ��錾 ===============
	static Shader* m_pVS;			//���_�V�F�[�_
	static Shader* m_pPS;			//�s�N�Z���V�F�[�_
	static DirectX::XMFLOAT4X4 m_WVP[3];	//�e���W�n�ɂ�����s��(0:world, 1:view, 2:projection)

	static const int MAX_LINE_NUM = 1000;
	static MeshBuffer* m_pLines;	//�`��̒��_�E�ӁE��
	static void* m_pLineVtx;
	static int m_lineCnt;
private:
	// =============== �v���g�^�C�v�錾 ===============
	static void MakeVS();	//���_�V�F�[�_�쐬
	static void MakePS();	//�s�N�Z���V�F�[�_�쐬
};	//��Ԍ`��

#endif	//!__LINE_H__