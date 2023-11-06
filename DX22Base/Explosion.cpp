//CPP�p----------------------------------------------------
/*========================================
HEW/UniBoooom!!
---------------------------------------
�����pcpp
---------------------------------------
Explosion.cpp

TeiUon

�ύX����
�E2023/11/03 cpp�쐬 �A�F��
�E2023/11/05 ����cpp�̏����ݒ�@�A�F��

======================================== */


//=============== �C���N���[�h ===================
#include "Explosion.h"
#include "Geometry.h"
#include <DirectXMath.h>

//=============== �萔��` =======================
#define MAX_EXPLOSION_NUM (30)	//��ʓ��ő唚����(��

//=============== �v���g�^�C�v�錾 ===============

//=============== �O���[�o���ϐ���` =============
Model* m_pExplosion;

CExplosion::CExplosion()
{
	RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
	DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
	SetRenderTargets(1, &pRTV, pDSV);		//DSV��null����2D�\���ɂȂ�
	
	m_pExplosion = new Model[MAX_EXPLOSION_NUM];				//�������̊i�[
	Position = DirectX::XMMatrixTranslation(1.0f, 1.0f, 1.0f);	//�����ʒu������
	m_fSize = 1.0f;												//�����̑傫���i�X�P�[���j
}

CExplosion::~CExplosion()
{
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		if (m_pExplosion) {
			delete[] m_pExplosion;
			m_pExplosion = nullptr;
		}

	}
	
	
}

/*========================================
�֐��FUpdate�֐�
----------------------------------------
���e�F�������̍X�V����
----------------------------------------
�����F��U�Ȃ�
----------------------------------------
�ߒl�F��U�Ȃ�
======================================== */

void CExplosion::Update()
{
	
}

/*========================================
�֐��FDraw�֐�
----------------------------------------
���e�F�����̕`�揈��
----------------------------------------
�����F��U�Ȃ�
----------------------------------------
�ߒl�F��U�Ȃ�
======================================== */

void CExplosion::Draw()
{
	
	
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		if (m_pExplosion) {
			m_pExplosion->Draw();
		}
	}

	//CGeometory::DrawBox();
}

void CExplosion::DeleteExplosion()
{

}
