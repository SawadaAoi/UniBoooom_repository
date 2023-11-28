/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	BoooomUI�\��
	------------------------------------
	BoooomUI.cpp
	------------------------------------
	�쐬��
		�A�F��
	�ύX����
	�E2023/11/20 cpp,�쐬 Tei
	�E2023/11/20 �`��ŕK�v�Ȋ֐����쐬 Tei

========================================== */

// =============== �C���N���[�h ===================
#include "BoooomUI.h"
#include "GameParameter.h"

// =============== �萔��` ===================
#if MODE_GAME_PARAMETER
#else
const float BOOOOM_UI_SIZE_X = 1.0f;		//BoooomUI��X�̒���
const float BOOOOM_UI_SIZE_Y = 0.565f;		//BoooomUI��Y�̒���
const float BOOOOM_UI_SCALE_X = 6.0f;		//BoooomUI�̃X�P�[��
const float BOOOOM_UI_SCALE_Y = 6.0f;		//BoooomUI�̃X�P�[��
#endif
/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CBoooomUI::CBoooomUI(TPos3d<float> pos, Texture* pTex, const CCamera* pCamera, float fTime)
	:m_pBoooomTex(pTex)
	,m_pos(pos)
	,m_scale{ BOOOOM_UI_SCALE_X, BOOOOM_UI_SCALE_Y, 0.0f}
	,m_fExplodeTime(0.0f)
	,m_nDelFrame(0)
	,m_bDelFlg(false)
{
	
	m_pCamera = pCamera;		//�J�����Z�b�g
	m_fExplodeTime = fTime;		//���������Ԃ��Z�b�g����
		
}

/* ========================================
	�f�X�g���N�^
	----------------------------------------
	���e�F�j�����ɍs������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CBoooomUI::~CBoooomUI()
{
	
}

void CBoooomUI::Update()
{
	DisplayTimeAdd();
	//TODO�����A������Ƃ��̃X�P�[�� ?
}

/* ========================================
	�`��֐�
	----------------------------------------
	���e�FBoooom�̕`��
	----------------------------------------
	����1�F�����ʒu
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CBoooomUI::Draw()
{

	RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
	DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
	SetRenderTargets(1, &pRTV, nullptr);		//DSV��null����2D�\���ɂȂ�

	DirectX::XMFLOAT4X4 mat[3];
	mat[1] = m_pCamera->GetViewMatrix();
	mat[2] = m_pCamera->GetProjectionMatrix();

	DirectX::XMFLOAT4X4 inv;	//�t�s��(inverse)�̊i�[��
	inv = m_pCamera->GetViewMatrix();

	//�J�����̍s���GPU�ɓn���ۂɓ]�u����Ă��邽�߁A�t�s��̌v�Z�̂��߂Ɉ�x���ɖ߂�
	DirectX::XMMATRIX matInv = DirectX::XMLoadFloat4x4(&inv);	//inv�Ɋi�[���ꂽ�J�����s���ϊ�
	matInv = DirectX::XMMatrixTranspose(matInv);	//matInv��]�u����

	////�ړ������͋t�s��ł��������K�v���Ȃ��̂ŁA0��ݒ肵�Ĉړ��𖳎�����
	DirectX::XMStoreFloat4x4(&inv, matInv);
	inv._41 = inv._42 = inv._43 = 0.0f;

	matInv = DirectX::XMLoadFloat4x4(&inv);
	matInv = DirectX::XMMatrixInverse(nullptr, matInv);	//�t�s��̌v�Z

	DirectX::XMMATRIX UI = matInv * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);	//���[���h�s��ƃr���{�[�h�̍s����������킹�����́i�����s�j
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(UI));
	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(BOOOOM_UI_SIZE_X * m_scale.x, BOOOOM_UI_SIZE_Y * m_scale.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pBoooomTex);	//�r���{�[�h�ŕ\���������e�N�X�`��
	Sprite::Draw();

	SetRenderTargets(1, &pRTV, pDSV);		//�������f���ƈꏏ�ɕ`�悷�邽�߂�3D�ɖ߂�
}

/* ========================================
	boooomUI�\���J�E���g���Z�����֐�
	-------------------------------------
	���e�FboooomUI�\���J�E���g�����Z���Ĉ��b����������I���t���O���I���ɂ���
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CBoooomUI::DisplayTimeAdd()
{
	m_nDelFrame++;		// �t���[�����Z

	// ���b�����Ԃ��o������
	if (m_fExplodeTime <= m_nDelFrame)
	{
		m_bDelFlg = true;	// �폜�t���O�𗧂Ă�
	}

}
/* ========================================
	�폜�t���O�擾�����֐�
	-------------------------------------
	���e�F�폜�t���O���擾����
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F�폜�t���O(bool)
=========================================== */
bool CBoooomUI::GetDelFlg()
{
	return m_bDelFlg;
}

/* ========================================
	�J�������Z�b�g�֐�
	----------------------------------------
	���e�F�`�揈���Ŏg�p����J�������Z�b�g
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CBoooomUI::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;
}