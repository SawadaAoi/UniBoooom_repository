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
	�E2023/11/23 �X�R�A�����Z���鏈���̒ǉ��@yamamoto
	�E2023/11/30 UI�A�j���[�V�����ǉ��@nieda
	�E2023/12/07 �Q�[���p�����[�^����萔�ړ� takagi

========================================== */

// =============== �C���N���[�h ===================
#include "Combo.h"
#include "ExplosionManager.h"
#include "GameParameter.h"
#include "Pos2d.h"
#include "TotalScore.h"

// =============== �萔��` =======================
const TPos2d<float> COMBO_UI_POSITION = { 930.0f, 600.0f };	// �R���{UI�̕`��ʒu
const TPos2d<float> COMBO_UI_SIZE = { 70.0f, 130.0f };	// �R���{UI�̑傫��
const float COMBO_UI_NUM_SPACE = 80.0f;				// �����̊ԃX�y�[�X
const float COMBO_UI_MULTI_DISP_SPACE = 100.0f;			// �����R���{�`�掞�̏㉺�̋�
const int COMBO_UI_DISP_DILAY_TIME = int(2.0f * 60);			// �c�R���{���\���̕b��

const TPos2d<float> COMBO_UI_BACK_POS = { 1030.0f, 600.0f };	// �R���{UI�̔w�i�̕`��ʒu
const TPos2d<float> COMBO_UI_BACK_SIZE = { 370.0f, 300.0f };	// �R���{UI�̔w�i�̑傫��
const TPos2d<float> COMBO_UI_STRING_POS = { 1150.0f, 615.5f };	// �R���{UI�̕����̕`��ʒu
const TPos2d<float> COMBO_UI_STRING_SIZE = { 180.0f, 100.0f };		// �R���{UI�̕����̑傫��

const int SWITCH_COMBO_ANIM = 5;			// �A�j���[�V�����؂�ւ��̊Ԋu
const int COMBO_ANIM_WIDTH_NUM_MAX = 3;		// ���������ő吔
const int COMBO_ANIM_HEIGHT_NUM_MAX = 3;	// �c�������ő吔
const float COMBO_ANIM_SIZEX = 1.0f / COMBO_ANIM_WIDTH_NUM_MAX;		// �e�N�X�`���������T�C�Y
const float COMBO_ANIM_SIZEY = 1.0f / COMBO_ANIM_HEIGHT_NUM_MAX;	// �e�N�X�`���c�����T�C�Y

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
	:m_fSizeX(0.0f)
	,m_fSizeY(0.0f)
	,m_nCntWidth(0)
	,m_nCntHeight(0)
	,m_nCnt(0)
	, m_nMaxComboNum(0)
{
	// �����摜��ǂݍ���
	m_pTextureNum[0] = new Texture();
	if (FAILED(m_pTextureNum[0]->Create("Assets/Texture/Combo/combo_numbers.png")))
	{
		MessageBox(NULL, "combo_numbers.png", "Error", MB_OK);
	}

	// �R���{�w�i�摜�ǂݍ���
	m_pTextureNum[1] = new Texture();
	if (FAILED(m_pTextureNum[1]->Create("Assets/Texture/Combo/combo_back_sprite_1.png")))
	{
		MessageBox(NULL, "combo_back_sprite_1.png", "Error", MB_OK);
	}

	// �R���{���̏�����
	for (int i = 0; i < MAX_COMBO_NUM; i++)
	{
		m_dComboInfo[i].dCnt = 0;
		m_dComboInfo[i].dDispFrame = 0;
		m_dComboInfo[i].bEndFlg = false;
		m_dComboInfo[i].dScore = 0;
		m_nCntOldCombo[i] = 0;		// ���O�܂ł̃R���{���i�[�p�ϐ���������
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
	for (int i = 0; i < 2; ++i)
	{
		SAFE_DELETE(m_pTextureNum[i]);
	}
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
	for (int i = 0; i < MAX_COMBO_NUM; i++)
	{
		if (m_dComboInfo[i].dCnt == 0) continue;
		m_pTotalScore->AddScore(m_dComboInfo[i],i);

		// �R���{�w�iUI�A�j���[�V�����Đ�
		if (m_nCntOldCombo[i] != m_dComboInfo[i].dCnt)	// �R���{�������O�ƈ������
		{
			m_nCntWidth = 0;	// �A�j���[�V���������Z�b�g
			m_nCntHeight = 0;
			m_nCntOldCombo[i] = m_dComboInfo[i].dCnt;	// ���݂̃R���{�����i�[
		}

		m_nCnt++;	// �J�E���g��i�߂�

		if (m_nCnt > SWITCH_COMBO_ANIM)	// ��莞�Ԍo�߂�����A�j���[�V������i�߂�
		{
			m_nCnt = 0;		// �J�E���g�����Z�b�g

			m_fSizeX = COMBO_ANIM_SIZEX * m_nCntWidth;		// ��������UV���W�v�Z
			m_fSizeY = COMBO_ANIM_SIZEY * m_nCntHeight;		// �c������UV���W�v�Z

			++m_nCntWidth;	// ����1�i�߂�

			if (m_nCntWidth == COMBO_ANIM_WIDTH_NUM_MAX)	// �E�[�܂ōs������
			{
				m_nCntWidth = 0;	// �������̃J�E���g�����Z�b�g
				++m_nCntHeight;		// �c��1�i�߂�
			}

			if (m_nCntHeight == 2)	// ��ԉ��̒i���E�[�݂̂Ȃ̂ł����Ŏ~�߂�
			{
				m_nCntWidth = 0;
			}

			if (m_dComboInfo[i].bEndFlg)	// �R���{���r�؂ꂽ��
			{
				m_nCnt = 0;		// �J�E���g�����Z�b�g
			}
		}
	}
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

		// �R���{�w�i�\��
		DrawTexture(COMBO_UI_BACK_POS.x,
					COMBO_UI_BACK_POS.y,
					COMBO_UI_BACK_SIZE.x,
					COMBO_UI_BACK_SIZE.y,
					m_pTextureNum[1]);

		float shiftPosY = dispCnt * COMBO_UI_MULTI_DISP_SPACE;	// �R���{�����\���̍ۂ̏㉺�̋󔒂��Z�b�g
		DisplayNumber(m_dComboInfo[i].dCnt, shiftPosY);			// �����̕\��

		// �R���{���r�؂ꂽ�ꍇ
		if (m_dComboInfo[i].bEndFlg == true)
		{	
			// �b���R���{����\������
			m_dComboInfo[i].dDispFrame++;
			// �w�莞�ԕ\��������R���{���̕\��������
			if (m_dComboInfo[i].dDispFrame >= COMBO_UI_DISP_DILAY_TIME)
			{
				if (m_nMaxComboNum < m_dComboInfo[i].dCnt) m_nMaxComboNum = m_dComboInfo[i].dCnt;

				m_dComboInfo[i].dCnt = 0;
				m_dComboInfo[i].dDispFrame = 0;
				m_dComboInfo[i].bEndFlg = false;
				m_dComboInfo[i].dScore = 0;
				m_nCntOldCombo[i] = 0;		// �R���{�������Z�b�g
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
		Sprite::SetTexture(m_pTextureNum[0]);
		Sprite::Draw();
	}
}

/* ========================================
	�e�N�X�`���`��֐�
	-------------------------------------
	���e�F�����ȊO�̃R���{�֌W�e�N�X�`���̕`�揈��
	-------------------------------------
	����1�F�\���ʒu��X���W
	����2�F�\���ʒu��Y���W
	����3�F�\������e�N�X�`���̏c��
	����4�F�\������e�N�X�`���̉���
	����5�F�\������e�N�X�`���̃|�C���^
	-------------------------------------
	�ߒl�F�Ȃ�
========================================== = */
void CCombo::DrawTexture(float posX, float posY, float h, float w, Texture* pTexture)
{
	DirectX::XMFLOAT4X4 mat[3];

	// ���[���h�s���X��Y�݂̂��l�����č쐬
	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(posX, posY, 0.0f);	// ���[���h�s��i�K�v�ɉ����ĕϐ��𑝂₵����A�����������L�q�����肷��j
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

	// �r���[�s���2D���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��
	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

	// �v���W�F�N�V�����s��ɂ�2D�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	// ���̍s���2D�̃X�N���[���̑傫�������܂�
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);	// ���t���e�s���ݒ�
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));

	// �X�v���C�g�̐ݒ�
	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(h, -w));
	Sprite::SetUVPos(DirectX::XMFLOAT2(m_fSizeX, m_fSizeY));
	Sprite::SetUVScale(DirectX::XMFLOAT2(COMBO_ANIM_SIZEX, COMBO_ANIM_SIZEY));
	Sprite::SetTexture(pTexture);
	Sprite::Draw();
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

void CCombo::AddScore(int num, int combo)
{
	switch (num) {
	case LEVEL_1:		m_dComboInfo[combo].dScore += LEVEL_1_SCORE;	break;
	case LEVEL_2:		m_dComboInfo[combo].dScore += LEVEL_2_SCORE;	break;
	case LEVEL_3:		m_dComboInfo[combo].dScore += LEVEL_3_SCORE;	break;
	case LEVEL_4:		m_dComboInfo[combo].dScore += LEVEL_4_SCORE;	break;
	case LEVEL_4x4:		m_dComboInfo[combo].dScore += LEVEL_4x4_SCORE;	break;
	case LEVEL_BOSS:	m_dComboInfo[combo].dScore += LEVEL_Boss_SCORE;	break;
	case LEVEL_FLAME:	m_dComboInfo[combo].dScore += LEVEL_1_SCORE;	break;	// ���X���C���Ɣ������ڐG�����ۂ͈�ԏ���������
	case LEVEL_HEAL:	m_dComboInfo[combo].dScore += LEVEL_1_SCORE;	break;	// �񕜃X���C���Ɣ������ڐG�����ۂ͈�ԏ���������
	}
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
	�ő�R���{���擾�֐�
	----------------------------------------
	���e�F�ő�R���{�����擾����
	----------------------------------------
	�����F����
	----------------------------------------
	�ߒl�F�ő�R���{��
======================================== */
int CCombo::GetMaxCombo()
{
	return m_nMaxComboNum;
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
	
	m_pTotalScore->ComboCheck(m_dComboInfo[num], num);	//�{�������߂�
}

/* ========================================
	�g�[�^���X�R�A���Z�b�g�֐�
	----------------------------------------
	���e�F�g�[�^���X�R�A���Z�b�g
	----------------------------------------
	����1�F�g�[�^���X�R�A
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CCombo::SetTotalScore(CTotalScore* pTotalScore)
{
	m_pTotalScore = pTotalScore;
}




