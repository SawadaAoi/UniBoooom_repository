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
	�E2023/12/07 �Q�[���p�����[�^����萔�ړ� takagi
	�E2024/02/09 UsingCamera�g�p takagi
	�E2024/02/13 �J�����폜 takagi
	�E2024/02/20 �g�k�A�j���[�V�������� suzumura

========================================== */

// =============== �C���N���[�h ===================
#include "BoooomUI.h"
#include "UsingCamera.h"	//�J�����g�p

// =============== �萔��` ===================
const float BOOOOM_UI_SIZE_X = 1.0f;		//BoooomUI��X�̒����itexture�̔䗦�ƍ��킹��j
const float BOOOOM_UI_SIZE_Y = 0.565f;		//BoooomUI��Y�̒����itexture�̔䗦�ƍ��킹��j

#if MODE_GAME_PARAMETER
#else
const float BOOOOM_UI_SCALE_X = 6.0f;		//BoooomUI�T�C�Y�̃X�P�[��
const float BOOOOM_UI_SCALE_Y = 6.0f;		//BoooomUI�T�C�Y�̃X�P�[��
const float BOOOOM_UI_MAX_SCALE_X = BOOOOM_UI_SCALE_X * 2.2f;	//�A�j���[�V�����p�g�k�ő�T�C�Y_X
const float BOOOOM_UI_MAX_SCALE_Y = BOOOOM_UI_SCALE_Y * 2.2f;	//�A�j���[�V�����p�g�k�ő�T�C�Y_Y
const float ANIM_TIME_RATE = 0.7f;	// ���������Ԃ̓��ABOOOOM�\�����s���͉̂�����(0.0f~1.0f)
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
CBoooomUI::CBoooomUI(TPos3d<float> pos, Texture* pTex, float fTime)
	:m_pBoooomTex(pTex)
	,m_pos(pos)
	,m_scale{ BOOOOM_UI_SCALE_X, BOOOOM_UI_SCALE_Y, 0.0f}
	,m_fExplodeTime(fTime * ANIM_TIME_RATE)
	,m_nDelFrame(0)
	,m_bDelFlg(false)
	,m_nAnimFrame(0)
	,m_fAnimRate(0.0f)
	,m_fAddScaleX(0.0f)
	,m_fAddScaleY(0.0f)
	,m_fScalingTime(fTime * ANIM_TIME_RATE)
	,m_fAlpha(1.0f)
{
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

	m_nAnimFrame++;
	ScalingAnim();	//�g�k�A�j���[�V����
	


}

/* ========================================
	�`��֐�
	----------------------------------------
	���e�FBoooom�̕`��
	----------------------------------------
	����1�F�`�惂�[�h
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CBoooomUI::Draw()
{

	RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
	DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
	SetRenderTargets(1, &pRTV, nullptr);		//DSV��null����2D�\���ɂȂ�

	DirectX::XMFLOAT4X4 mat[3];
	mat[1] = CUsingCamera::GetThis().GetCamera()->GetViewMatrix();
	mat[2] = CUsingCamera::GetThis().GetCamera()->GetProjectionMatrix();

	DirectX::XMFLOAT4X4 inv;	//�t�s��(inverse)�̊i�[��
	inv = CUsingCamera::GetThis().GetCamera()->GetViewMatrix();

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
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, m_fAlpha));
	Sprite::Draw();

	SetRenderTargets(1, &pRTV, pDSV);		//�������f���ƈꏏ�ɕ`�悷�邽�߂�3D�ɖ߂�
}

/*========================================
boooomUI�A�j���[�V���������֐�
------------------------------------ -
���e�FboooomUI�̊g�k�̃A�j���[�V��������������
------------------------------------ -
����1�F����
------------------------------------ -
�ߒl�F����
========================================== = */
void CBoooomUI::ScalingAnim()
{
	// �g�k���Ԃ̓��A"�g��"���鎞�Ԃ�ݒ�
	float fExpandTime = m_fScalingTime / 2.0f;

	//-- �g��
	if (m_nAnimFrame < (int)fExpandTime)
	{
		m_fAnimRate += 1.0f / fExpandTime;	//�t���[�����Z

	}
	//-- �k��
	else if (m_nAnimFrame >= 0)
	{
		m_fAnimRate -= 1.0f / (m_fScalingTime - fExpandTime);	//�t���[�����Z

		//-- ���X�ɏ����Ă�������
		m_fAlpha -= 0.01f;	//�����x�X�V
	}
	// 0�������Ȃ��悤��
	if (m_fAnimRate < 0) m_fAnimRate = 0;

	// ��Ԓl���g�p���ăX�P�[�����v�Z
	float scalingFactor = (sqrt(1 - pow(m_fAnimRate - 1, 2)));
	// �X�P�[���̐ݒ�
	m_scale = TPos3d<float>(BOOOOM_UI_SCALE_X + ((BOOOOM_UI_MAX_SCALE_X - BOOOOM_UI_SCALE_X) * scalingFactor),
		BOOOOM_UI_SCALE_Y + ((BOOOOM_UI_MAX_SCALE_Y - BOOOOM_UI_SCALE_Y) * scalingFactor), 0.0f);
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
