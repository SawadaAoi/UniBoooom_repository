/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�X���C���T�C�Y3�pcpp
	------------------------------------
	Slime_3.cpp
	------------------------------------
	�쐬��	�R�����C

	�ύX����
	�E2023/11/08 �쐬 yamashita
	�E2023/11/08 �傫���̒萔���`	yamashita
	�E2023/11/08 �X���C���̈ړ����x��傫�����ƂɕύX����֐����쐬	yamashita
	�E2023/11/08 �X���C���̈ړ����x��傫�����ƂɕύX����֐����쐬	yamashita
	�E2023/11/08 �R���X�g���N�^�Ń��x�����Ƃ̃p�����[�^���Z�b�g	yamashita
	�E2023/11/11 parameter�p�w�b�_�ǉ� suzumura
	�E2023/11/14 Base���烂�f���A�V�F�[�_�̓ǂݍ��݂��ړ� Suzumura
	�E2023/11/14 SphereInfo�̕ύX�ɑΉ� takagi

========================================== */

// =============== �C���N���[�h ===================
#include "Slime_3.h"
#include "GameParameter.h"		//�萔��`�p�w�b�_�[

// =============== �萔��` =======================
#if MODE_GAME_PARAMETER
#else
const float LEVEL3_SCALE = 3.0f;
const float LEVEL3_SPEED = ENEMY_MOVE_SPEED * 0.90;
#endif

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�R���X�g���N�^
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
CSlime_3::CSlime_3()
{
	RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
	DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
	SetRenderTargets(1, &pRTV, pDSV);		//DSV��null����2D�\���ɂȂ�
	m_pModel = new Model;
	if (!m_pModel->Load("Assets/Model/eyeBat/eyeBat.FBX", 0.1f, Model::XFlip)) {		//�{���Ɣ��]�͏ȗ���
		MessageBox(NULL, "eyeBat", "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
	}

	//���_�V�F�[�_�ǂݍ���
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}
	m_pModel->SetVertexShader(m_pVS);

	m_Transform.fScale = { LEVEL3_SCALE,LEVEL3_SCALE ,LEVEL3_SCALE };
	m_sphere.fRadius *= LEVEL3_SCALE;
	m_eSlimeSize = E_SLIME_LEVEL::LEVEL_3;
	SetNormalSpeed();

}

/* ========================================
	�R���X�g���N�^�֐�(���W�w��)
	-------------------------------------
	���e�F�R���X�g���N�^
	-------------------------------------
	����1�F����������W
	-------------------------------------
	�ߒl�F����
=========================================== */
CSlime_3::CSlime_3(TPos3d<float> pos)
	: CSlime_3()
{
	m_Transform.fPos = pos;			// �������W���w��
}

/* ========================================
	�f�X�g���N�^�֐�
	-------------------------------------
	���e�F�f�X�g���N�^
	-------------------------------------
	����1�F
	-------------------------------------
	�ߒl�F
=========================================== */
CSlime_3::~CSlime_3()
{
}

/* ========================================
	�X�s�[�h����֐�
	-------------------------------------
	���e�F�X���C���̈ړ����x��ݒ�
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CSlime_3::SetNormalSpeed()
{
	m_fSpeed = LEVEL3_SPEED;	//�ړ����x�ɒ萔���Z�b�g
}



