/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X�R�A�Ǘ��pcpp
	---------------------------------------
	ScoreManager.cpp

	�쐬��	�R�{�M��

	�ύX����
	�E2023/11/18�@�쐬

========================================== */

// =============== �C���N���[�h ===================
#include "ScoreOverHead.h"
#include "Sprite.h"
/* ========================================
	�֐��F�R���X�g���N�^
	-------------------------------------
	���e�F���s���ɍs������
	-------------------------------------
	����1�F�����̈ʒu,�X�R�A
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CScoreOverHead::CScoreOverHead(TPos3d<float> fPos, int nScore, float posY)
	: m_pScoreTexture(nullptr)
	, m_Transform(fPos, { 0.0f, 0.0f, 0.0f }, 0.0f)
	, digits{}
	, digitArray{}
	, ArraySize(0)
{
	m_pScoreTexture = new Texture();

	if (FAILED(m_pScoreTexture->Create("Assets/Texture/numbers_v1/number.png")))
	{
		MessageBox(NULL, "�����ǂݍ���", "Error", MB_OK);
	}
	m_Transform.fPos.y += posY;
	//slime�̃��x���ɂ���Ĕ����̑傫���ς�邩��slime�̂Ƃ��ō�����������K�v����H
	//m_Transform.fPos.y

	// �������e�����Ƃɔz��Ɋi�[
	digitArray = digitsToArray(nScore);
	ArraySize = digitArray.size();
}

CScoreOverHead::~CScoreOverHead()
{
	digits.clear();
	digitArray.clear();
}

void CScoreOverHead::Update()	//
{
}

void CScoreOverHead::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMFLOAT4X4 inv;//�t�s��̊i�[��
	inv = m_pCamera->GetViewMatrix();

	//�J�����̍s���GPU�ɓn���ۂɓ]�u����Ă��邽�߁A�t�s��̂��߂Ɉ�x���ɖ߂�
	DirectX::XMMATRIX matInv = DirectX::XMLoadFloat4x4(&inv);
	matInv = DirectX::XMMatrixTranspose(matInv);


	//�ړ������͋t�s��őł������K�v�������̂�0��ݒ肵�Ĉړ��𖳎�����
	DirectX::XMStoreFloat4x4(&inv, matInv);
	inv._41 = inv._42 = inv._43 = 0.0f;

	matInv = DirectX::XMLoadFloat4x4(&inv);
	matInv = DirectX::XMMatrixInverse(nullptr, matInv);

	
	for (int i = 0; i <= ArraySize; i++)
	{

		float width = 20.0f*i;


		DirectX::XMMATRIX world = matInv * DirectX::XMMatrixTranslation(m_Transform.fPos.x+width, m_Transform.fPos.y, m_Transform.fPos.z);
		DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));
		Sprite::SetSize(DirectX::XMFLOAT2(20.0f, -20.0f));
		int y = digitArray[i] % 5;	//�������O��W���܂�
		int x= digitArray[i] / 5;	//�z��ɓ����Ă鐔���̏ꏊ���v�Z���Ă܂�
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f*y, 0.5f*x));//0.2��0.5��time�Ɠ����Ȃ̂ł��ƂŃQ�[���p�����[�^�ɒǉ����ĕς��܂�
		Sprite::SetUVScale(DirectX::XMFLOAT2(0.2f, 0.5f));

		Sprite::SetWorld(mat[0]);
		Sprite::SetTexture(m_pScoreTexture);
		Sprite::Draw();
		
	}


}

std::vector<int> CScoreOverHead::digitsToArray(int score)
{
	while (score > 0) {
		digits.push_back(score % 10);
		score /= 10;
	}
	// �P�̈ʂ�������Ă���̂Ŕ��]����
	std::reverse(digits.begin(), digits.end());
	return digits;
}
