/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�R���{UI�pcpp
	------------------------------------
	Combo.cpp
	------------------------------------
	�쐬��
		�V�c����
	�ύX����
	�E2023/11/21 �쐬 Sawada

========================================== */

// =============== �C���N���[�h ===================
#include "Combo.h"
#include "ExplosionManager.h"
#include "GameParameter.h"
#include "Pos2d.h"

// =============== �萔��` =======================
#if MODE_GAME_PARAMETER
#else
const TPos2d<float> COMBO_UI_POSITION = { 1100.0f,600.0f };
const TPos2d<float> COMBO_UI_SIZE = { 70.0f,70.0f };
const float COMBO_UI_NUM_SPACE = 80.0f;
const float COMBO_UI_MULTI_DISP_SPACE = 100.0f;
const int COMBO_UI_DISP_DILAY_TIME = 2.0f * 60;
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
CCombo::CCombo()
	: m_pTextureNum(nullptr)
{

	// �����摜��ǂݍ���
	m_pTextureNum = new Texture();
	if (FAILED(m_pTextureNum->Create("Assets/Texture/numbers_v1/number.png")))
	{
		MessageBox(NULL, "number.png", "Error", MB_OK);
	}

	// �R���{���̏�����
	for (int i = 0; i < MAX_COMBO_NUM; i++)
	{
		m_dComboInfo[i].dCnt = 0;
		m_dComboInfo[i].dDispFrame = 0;
		m_dComboInfo[i].bEndFlg = false;
	}
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
CCombo::~CCombo()
{
	SAFE_DELETE(m_pTextureNum);
}

/* ========================================
	�X�V�֐�
	----------------------------------------
	���e�F�X�V����
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CCombo::Update()
{

}

/* ========================================
	�`��֐�
	----------------------------------------
	���e�F�`��p����
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CCombo::Draw()
{
	int dispCnt = 0;	// �`��R���{��
	for (int i = 0; i < MAX_COMBO_NUM; i++)
	{
		// 0�R���{�͕\�����Ȃ�
		if (m_dComboInfo[i].dCnt == 0) continue;

		float shiftPosY = dispCnt * COMBO_UI_MULTI_DISP_SPACE;	// �R���{�����\���̍ۂ̏㉺�̋󔒂��Z�b�g
		DisplayNumber(m_dComboInfo[i].dCnt, shiftPosY);			// �����̕\��

		// �R���{���r�؂ꂽ�ꍇ
		if (m_dComboInfo[0].bEndFlg == true)
		{	
			// �b���R���{����\������
			m_dComboInfo[0].dDispFrame++;
			// �w�莞�ԕ\��������R���{���̕\��������
			if (m_dComboInfo[0].dDispFrame >= COMBO_UI_DISP_DILAY_TIME)
			{
				m_dComboInfo[0].dCnt = 0;
				m_dComboInfo[0].dDispFrame = 0;
				m_dComboInfo[0].bEndFlg = false;
			}
		}

		dispCnt++;	// �����ɔ������Ă���R���{���𐔂���

	}
}


/* ========================================
	�����`��֐�
	----------------------------------------
	���e�F�R���{����\������
	----------------------------------------
	����1�F�R���{��
	����2�F���������̕\�������̒��ߒl
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CCombo::DisplayNumber(int cnt, float shiftPosY)
{
	DirectX::XMFLOAT4X4 mat[3];	// �`��p�̍s��

	int num[2];			// �e�������Z�b�g����
	num[0] = cnt % 10;	// �ꌅ��
	num[1] = cnt / 10;	// �\����

	// ��������
	for (int j = 0; j < 2; j++)
	{
		// �R���{����2���ȉ��ŁA��̌��ȊO�̏ꍇ�͕\�����Ȃ�(0���߂��Ȃ�)
		if (cnt < 10 && j != 0 ) continue;

		// �����ƂɈʒu�����炷
		float width = j * COMBO_UI_NUM_SPACE;

		//���[���h�s���X��Y�݂̂��l�����č쐬
		DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(COMBO_UI_POSITION.x - width, COMBO_UI_POSITION.y - shiftPosY, 0.0f);
		DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

		//�r���[�s���2D���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��
		DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

		//�v���W�F�N�V�����s��ɂ�2D�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
		//���̍s���2D�̃X�N���[���̑����������܂�
		DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);
		DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));

		//�X�v���C�g�̐ݒ�
		Sprite::SetWorld(mat[0]);
		Sprite::SetView(mat[1]);
		Sprite::SetProjection(mat[2]);
		Sprite::SetSize(DirectX::XMFLOAT2(COMBO_UI_SIZE.x, -COMBO_UI_SIZE.y));
		//sprite�V�[�g�̏㕔���\���i0�`4�j
		if (num[j] < 5)
		{
			Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f * num[j], 0.0f));
		}
		//sprite�V�[�g�̉������\���i5�`9�j
		else
		{
			Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f * (num[j] - 5), 0.5f));
		}
		Sprite::SetUVScale(DirectX::XMFLOAT2(0.2f, 0.5f));
		Sprite::SetTexture(m_pTextureNum);
		Sprite::Draw();
	}
}

/* ========================================
	�R���{�z��l�Z�b�g�֐�
	----------------------------------------
	���e�F���������������ۂɃR���{�z��ɒl���Z�b�g����
	----------------------------------------
	�����F�Ȃ�
	----------------------------------------
	�ߒl�F�z��̓Y����
======================================== */
int CCombo::FirstComboSet()
{
	int num;	// �Ԃ��R���{�z��̓Y����

	for (int i = 0; i < MAX_COMBO_NUM; i++)
	{
		// ���ɃR���{���𐔂��Ă���z��͔�΂�
		if (m_dComboInfo[i].dCnt != 0) continue;

		m_dComboInfo[i].dCnt++;	// 1�R���{�ڂ��Z�b�g
		num = i;				// �Y�������L�^����
		break;					// �R���{���L�^�����̂Ŕ�����
	}

	return num;
}

/* ========================================
	�R���{�����Z�֐�
	----------------------------------------
	���e�F���������������ۂɃR���{���𑝂₷
	----------------------------------------
	�����F�z��̓Y����
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CCombo::AddCombo(int num)
{
	m_dComboInfo[num].dCnt++;
}

/* ========================================
	�R���{���擾�֐�
	----------------------------------------
	���e�F�Ή��Y�����̃R���{�����擾����
	----------------------------------------
	�����F�z��̓Y����
	----------------------------------------
	�ߒl�F�R���{��
======================================== */
int CCombo::GetCombo(int num)
{
	return m_dComboInfo[num].dCnt;
}

/* ========================================
	�R���{�I���֐�
	----------------------------------------
	���e�F�����̘A�����I���������̏���
	----------------------------------------
	�����F�z��̓Y����
	----------------------------------------
	�ߒl�F����
======================================== */
void CCombo::EndCombo(int num)
{
	m_dComboInfo[num].bEndFlg = true;	// �R���{�I���t���O���I��
}


