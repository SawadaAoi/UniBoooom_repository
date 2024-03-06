/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X�R�A�Ǘ��pcpp
	---------------------------------------
	ScoreManager.cpp

	�쐬��	�R�{�M��

	�ύX����
	�E2023/11/18�@�쐬 yamamoto
	�E2023/11/24�@�R�����g�ǉ� yamamoto
	�E2024/02/13 UsingCamera�g�p takagi

========================================== */

// =============== �C���N���[�h ===================
#include "ScoreOverHead.h"
#include "Sprite.h"
#include "GameParameter.h"		//�萔��`�p�w�b�_�[
#include "UsingCamera.h"	//�J�����g�p

/* ========================================
	�֐��F�R���X�g���N�^
	-------------------------------------
	���e�F���s���ɍs������
	-------------------------------------
	����1�F�����̈ʒu,�X�R�A
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CScoreOverHead::CScoreOverHead(TPos3d<float> fPos, int nScore, float posY,float fTime, bool delayFlg)
	: m_pScoreTexture(nullptr)
	, m_Transform(fPos, { 1.0f, 1.0f, 1.0f }, 0.0f)
	, digits{}
	, digitArray{}
	, nArraySize(0)
	, m_fDelFrame(0.0f)
	, m_fExplodeTime(fTime)	
	, m_bDelFlg(false)
	, m_bDelayFlg(delayFlg)
	, m_nDelayCnt(0)
{
	
	m_pScoreTexture = new Texture();
	//if (FAILED(m_pScoreTexture->Create("Assets/Texture/numbers_v1/number.png")))
	if (FAILED(m_pScoreTexture->Create("Assets/Texture/Score/score_numbers.png")))
	{
		MessageBox(NULL, "�����ǂݍ���", "Error", MB_OK);
	}
	m_Transform.fPos.y += posY;
	//slime�̃��x���ɂ���Ĕ����̑傫���ς�邩��slime�̂Ƃ��ō�����������K�v����H
	//m_Transform.fPos.y

	// �������e�����Ƃɔz��Ɋi�[
	digitArray = digitsToArray(nScore);
	
	nArraySize = int(digitArray.size());
}

/* ========================================
	�f�X�g���N�^�֐�
	-------------------------------------
	���e�F�f�X�g���N�^
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
CScoreOverHead::~CScoreOverHead()
{
	digits.clear();
	digitArray.clear();
	SAFE_DELETE(m_pScoreTexture);
}

/* ========================================
	�X�V�����֐�
	-------------------------------------
	���e�F�X�V����
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CScoreOverHead::Update()	//
{
	// �X�R�A�\���x���������L���ȏꍇ
	if (m_bDelayFlg)
	{
		Delay();	// �x������
		return;
	}

	DisplayTimeAdd();
}

/* ========================================
	�`�揈���֐�
	-------------------------------------
	���e�F�`�揈��
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CScoreOverHead::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
	DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
	SetRenderTargets(1, &pRTV, nullptr);		//DSV��null����2D�\���ɂȂ�

	DirectX::XMFLOAT4X4 mat[3];
	mat[1] = CUsingCamera::GetThis().GetCamera()->GetViewMatrix();
	mat[2] = CUsingCamera::GetThis().GetCamera()->GetProjectionMatrix();
	DirectX::XMFLOAT4X4 inv;//�t�s��̊i�[��
	inv = CUsingCamera::GetThis().GetCamera()->GetViewMatrix();

	//�J�����̍s���GPU�ɓn���ۂɓ]�u����Ă��邽�߁A�t�s��̂��߂Ɉ�x���ɖ߂�
	DirectX::XMMATRIX matInv = DirectX::XMLoadFloat4x4(&inv);
	matInv = DirectX::XMMatrixTranspose(matInv);

	//�ړ������͋t�s��őł������K�v�������̂�0��ݒ肵�Ĉړ��𖳎�����
	DirectX::XMStoreFloat4x4(&inv, matInv);
	inv._41 = inv._42 = inv._43 = 0.0f;

	matInv = DirectX::XMLoadFloat4x4(&inv);
	matInv = DirectX::XMMatrixInverse(nullptr, matInv);

	
	for (int i = 0; i < nArraySize; i++)
	{

		float width = 0.5f*i;


		DirectX::XMMATRIX world = matInv * DirectX::XMMatrixTranslation(m_Transform.fPos.x-width, m_Transform.fPos.y, m_Transform.fPos.z);
		DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));
		Sprite::SetSize(DirectX::XMFLOAT2(0.5f, 0.5f));
		int y = digitArray[i] % 5;	//�������O��W���܂�
		int x= digitArray[i] / 5;	//�z��ɓ����Ă鐔���̏ꏊ���v�Z���Ă܂�
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f*y, 0.5f*x));//0.2��0.5��time�Ɠ����Ȃ̂ł��ƂŃQ�[���p�����[�^�ɒǉ����ĕς��܂�
		Sprite::SetUVScale(DirectX::XMFLOAT2(0.2f, 0.5f));

		Sprite::SetWorld(mat[0]);
		Sprite::SetView(mat[1]);
		Sprite::SetProjection(mat[2]);
		Sprite::SetTexture(m_pScoreTexture);
		Sprite::Draw();
		
	}


}
/* ========================================
	�x�������֐�
	-------------------------------------
	���e�F�X�R�A�̕\����x�点��
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CScoreOverHead::Delay()
{
	m_nDelayCnt++;

	// �x���b�����o������
	if (m_nDelayCnt >= DELAY_TIME)
	{
		m_bDelayFlg = false;	// �x���t���O���I�t�ɂ���
	}
}

/* ========================================
	�X�R�A�\���J�E���g���Z�����֐�
	-------------------------------------
	���e�F�X�R�A�\���J�E���g�����Z���Ĉ��b����������I���t���O���I���ɂ���
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CScoreOverHead::DisplayTimeAdd()
{
	m_fDelFrame++;	// �t���[�����Z
	// ���b�����Ԃ��o������
	if (m_fExplodeTime <= m_fDelFrame)
	{
		m_bDelFlg = true;	// �폜�t���O�𗧂Ă�
	}
}
/* ========================================
	�z����[�����֐�
	-------------------------------------
	���e�F�\���������������ꌅ���z��ɓ����
	-------------------------------------
	����1�F�\���������X�R�A
	-------------------------------------
	�ߒl�F���[�����z��
=========================================== */
std::vector<int> CScoreOverHead::digitsToArray(int score)
{
	//�P�̈ʂ�����[
	while (score > 0) {
		digits.push_back(score % 10);
		score /= 10;
	}
	
	return digits;
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
bool CScoreOverHead::GetDelFlg()
{
	return m_bDelFlg;
}