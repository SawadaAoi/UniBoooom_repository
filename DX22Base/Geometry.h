/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   ��Ԃɂ�����`��̒��ۃN���X��`
   ---------------------------------------
   Geometry.h

   �쐬��	takagi

   �ύX����
   �E���܂� �w�Z�̔z�z��(���Ƃɉ����ό`)
   �E2023/11/05 �t�@�C�������E���ۃN���X���E�R�����g�t�^ takagi
   �E2023/11/10 Uninit�폜 takagi
   �E2023/11/10 Uninit�쐬(�V�F�[�_�p) �V�c����

   ======================================== */

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

// =============== �C���N���[�h ===================
#include <DirectXMath.h>	//�s��v�Z�p
#include "Shader.h"			//�����o�̃w�b�_
#include "MeshBuffer.h"		//�����o�̃w�b�_
//#include "Pos.h"

// =============== �N���X��` =====================
class CGeometry
{
protected:
	// =============== �\���̒�` =====================
	struct Vertex
	{
		float pos[3];	//���_�̈ʒu
		float uv[2];	//�e�N�X�`�����W
	};	//�e�N�X�`����\��ꍇ�̒��_���
private:
	// =============== �\���̒�` =====================
	enum E_MATRIX
	{
		E_MATRIX_WORLD = 0,	//���[���h�s��
		E_MATRIX_VIEW,			//�r���[�s��
		E_MATRIX_PROJECTION,	//�v���W�F�N�V�����s��
	};	//�s��
public:
	// =============== �v���g�^�C�v�錾 ===============
	CGeometry();				//�R���X�g���N�^
	CGeometry(CGeometry& Obj);	//�R�s�[�R���X�g���N�^
	virtual ~CGeometry();		//�f�X�g���N�^
	static void MakeShader();	//�V�F�[�_�쐬
	virtual void Draw() = 0;	//�`��
	static void Uninit();

	void SetWorld(DirectX::XMFLOAT4X4 World);		//���[���h�s��o�^
	void SetView(DirectX::XMFLOAT4X4 View);			//�r���[�s��o�^
	void SetProjection(DirectX::XMFLOAT4X4 Proj);	//�v���W�F�N�V�����s��o�^
protected:
	// =============== �����o�[�ϐ��錾 ===============
	MeshBuffer* m_pObj;				//�`��̒��_�E�ӁE��
	static Shader* m_pVS;			//���_�V�F�[�_
	static Shader* m_pPS;			//�s�N�Z���V�F�[�_
	DirectX::XMFLOAT4X4 m_WVP[3];	//�e���W�n�ɂ�����s��(0:world, 1:view, 2:projection)
private:
	// =============== �v���g�^�C�v�錾 ===============
	static void MakeVS();	//���_�V�F�[�_�쐬
	static void MakePS();	//�s�N�Z���V�F�[�_�쐬
};	//��Ԍ`��

#endif	//!__GEOMETRY_H__