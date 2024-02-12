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
#include "DiType.h"	//2�̓����^�����^


// =============== �萔��` =======================
const TTriType<float> COMBO_NUM_POS = { 930.0f, 120.0f, 1.0f };	// �R���{UI�̑傫��
const TTriType<float> COMBO_NUM_SIZE = { 70.0f, 130.0f, 1.0f };	// �R���{UI�̑傫��
const TDiType<float> COMBO_NUM_UV_SCALE = { 0.2f, 0.5f };

const float COMBO_UI_NUM_SPACE = 80.0f;							// �����̊ԃX�y�[�X
const float COMBO_UI_LINE_SPACE_X = 50.0f;						// �����R���{�`�掞�̏㉺�̋�
const float COMBO_UI_LINE_SPACE_Y = 100.0f;						// �����R���{�`�掞�̏㉺�̋�
const int COMBO_END_DISP_DILAY_TIME = int(2.0f * 60);			// �c�R���{���\���̕b��

const TTriType<float> COMBO_UI_BG_POS = { 1030.0f, 120.0f, 1.0f };	// �R���{UI�̔w�i�̕`��ʒu
const TTriType<float> COMBO_UI_BG_SIZE = { 370.0f, 300.0f, 1.0f };	// �R���{UI�̔w�i�̑傫��
const TDiType<int> COMBO_UI_BG_SPLIT_NUM = { 3,3 };					// �R���{UI�̉摜�̏c���̕�����

const int COMBO_UI_BG_MAX_NUM = 7;					// BG�A�j���[�V�����ő�R�}��
const int SWITCH_COMBO_BG_ANIM_FLAME = 5;			// BG�A�j���[�V�����؂�ւ��̊Ԋu

const std::string TEXTURE_PATH[CCombo::TEXTURE_KIND::TEX_MAX] =	// �摜�p�X
{
	{"Assets/Texture/Combo/combo_numbers.png"},
	{"Assets/Texture/Combo/combo_back_sprite_1.png"},
};

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
	: m_nMaxComboNum(0)
	, m_pTexNumber(nullptr)
{
	// �摜������
	for (int i = 0; i < TEXTURE_KIND::TEX_MAX; i++)
	{
		// �摜��ǂݍ���
		m_pTexture[i] = new Texture();
		if (FAILED(m_pTexture[i]->Create(TEXTURE_PATH[i].c_str())))
		{
			MessageBox(NULL, "combo Texture", "Error", MB_OK);
		}
	}

	// �R���{���̏�����
	for (int i = 0; i < MAX_COMBO_NUM; i++)
	{
		m_dComboInfo[i].dComboCnt = 0;
		m_dComboInfo[i].dDispFrame = 0;
		m_dComboInfo[i].bEndFlg = false;
		m_dComboInfo[i].dScore = 0;
		m_dComboInfo[i].nOldComboCnt = 0;		// ���O�܂ł̃R���{���i�[�p�ϐ���������


		m_pComboBG[i] = new CDrawAnim(COMBO_UI_BG_MAX_NUM, COMBO_UI_BG_SPLIT_NUM, SWITCH_COMBO_BG_ANIM_FLAME);
		m_pComboBG[i]->SetTexture(m_pTexture[TEXTURE_KIND::TEX_BG]);
		m_pComboBG[i]->SetSize(COMBO_UI_BG_SIZE);
	}

	m_pTexNumber = new C2dPolygon();	// �����摜������

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
	SAFE_DELETE(m_pTexNumber);

	for (int i = 0; i < 2; ++i)
	{
		SAFE_DELETE(m_pTexture[i]);
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
	// �����R���{����
	for (int i = 0; i < MAX_COMBO_NUM; i++)
	{
		if (m_dComboInfo[i].dComboCnt == 0) continue;	// �R���{���������ĂȂ��ꍇ�̓X���[
		if (m_dComboInfo[i].bEndFlg)	continue;		// �R���{���I���ς݂̏ꍇ�̓X���[

		m_pTotalScore->SetAddScore(m_dComboInfo[i],i);	// ���Z�X�R�A�̒l���Z�b�g

		m_pComboBG[i]->Update();	// �R���{�w�i�̃A�j���[�V�����X�V

		// �R���{�������O�ƈ������
		if (m_dComboInfo[i].nOldComboCnt != m_dComboInfo[i].dComboCnt)	
		{
			m_pComboBG[i]->AnimReset();									// �A�j���[�V���������Z�b�g
			m_dComboInfo[i].nOldComboCnt = m_dComboInfo[i].dComboCnt;	// ���݂̃R���{�����i�[
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
	int lineCnt = 0;	// �\������R���{UI�̍s�ԍ�

	// �����R���{����
	for (int i = 0; i < MAX_COMBO_NUM; i++)
	{
		// 0�R���{�͕\�����Ȃ�
		if (m_dComboInfo[i].dComboCnt == 0) continue;

		DispComboBG(i, lineCnt);							// �R���{�w�i
		DisplayNumber(m_dComboInfo[i].dComboCnt, lineCnt);	// �����̕\��

		// �R���{���r�؂ꂽ�ꍇ
		if (m_dComboInfo[i].bEndFlg)
		{
			// �b���R���{����\������
			m_dComboInfo[i].dDispFrame++;

			// �w�莞�ԕ\��������R���{���̕\��������
			if (COMBO_END_DISP_DILAY_TIME <= m_dComboInfo[i].dDispFrame )
			{
				if (m_nMaxComboNum < m_dComboInfo[i].dComboCnt)
				{
					m_nMaxComboNum = m_dComboInfo[i].dComboCnt;	// �ő�R���{���X�V(���U���g�p)
				}

				m_dComboInfo[i].dComboCnt		= 0;
				m_dComboInfo[i].dDispFrame		= 0;
				m_dComboInfo[i].bEndFlg			= false;
				m_dComboInfo[i].dScore			= 0;	
				m_dComboInfo[i].nOldComboCnt	= 0;	// �R���{�������Z�b�g
				m_pComboBG[i]->AnimReset();
			}
		}

		lineCnt++;	// �����ɔ������Ă���R���{���𐔂���

	}
}

/* ========================================
	�R���{�w�i�摜�֐�
	----------------------------------------
	���e�F�R���{�w�i�摜��\������
	----------------------------------------
	����1�F�z��ԍ�
	����2�F���������̕\���ʒu�̒��ߒl
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CCombo::DispComboBG(int ArrayNum, int lineNum)
{

	float shiftPosX = lineNum * COMBO_UI_LINE_SPACE_X;	// ���̕\���ʒu�����l
	float shiftPosY = lineNum * COMBO_UI_LINE_SPACE_Y;	// �c�̕\���ʒu�����l

	TTriType<float> pos = {
			COMBO_UI_BG_POS.x + shiftPosX,
			COMBO_UI_BG_POS.y + shiftPosY,
			1.0f };

	m_pComboBG[ArrayNum]->SetPos(pos);

	if (m_pComboBG[ArrayNum]->GetAnimFlg())
	{
		m_pComboBG[ArrayNum]->Draw();
	}
	else
	{
		m_pComboBG[ArrayNum]->SetAnimNum(COMBO_UI_BG_MAX_NUM);
		m_pComboBG[ArrayNum]->C2dPolygon::Draw();
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
void CCombo::DisplayNumber(int cnt, int lineNum)
{
	int num[2];			// �e�������Z�b�g����
	num[0] = cnt % 10;	// �ꌅ��
	num[1] = cnt / 10;	// �\����

	float shiftPosX = lineNum * COMBO_UI_LINE_SPACE_X;	// ���̕\���ʒu�����l
	float shiftPosY = lineNum * COMBO_UI_LINE_SPACE_Y;	// �c�̕\���ʒu�����l

	// ��������
	for (int i = 0; i < 2; i++)
	{
		// �R���{����2���ȉ��ŁA��̌��ȊO�̏ꍇ�͕\�����Ȃ�(0���߂��Ȃ�)
		if (cnt < 10 && i != 0 ) continue;

		// �����ƂɈʒu�����炷
		float width = i * COMBO_UI_NUM_SPACE;

		TTriType<float> pos = {
			COMBO_NUM_POS.x - width + shiftPosX,
			COMBO_NUM_POS.y + shiftPosY,
			1.0f };

		int x = num[i] % 5;	// �����e�N�X�`���̉������ʒu
		int y = num[i] / 5;	// �����e�N�X�`���̏c�����ʒu

		m_pTexNumber->SetPos(pos);
		m_pTexNumber->SetSize(COMBO_NUM_SIZE);
		m_pTexNumber->SetUvOffset({ COMBO_NUM_UV_SCALE.x * x, COMBO_NUM_UV_SCALE.y * y });// �e�N�X�`��UV���W
		m_pTexNumber->SetUvScale(COMBO_NUM_UV_SCALE);
		m_pTexNumber->SetTexture(m_pTexture[0]);

		m_pTexNumber->Draw();

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
		if (m_dComboInfo[i].dComboCnt != 0) continue;

		m_dComboInfo[i].dComboCnt++;	// 1�R���{�ڂ��Z�b�g
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
	m_dComboInfo[num].dComboCnt++;

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
int CCombo::GetComboNum(int num)
{
	return m_dComboInfo[num].dComboCnt;
}

/* ========================================
	�R���{�I���t���O�擾�֐�
	----------------------------------------
	���e�F�Ή��Y�����̃R���{�I���t���O���擾����
	----------------------------------------
	�����F�z��̓Y����
	----------------------------------------
	�ߒl�F�R���{�I���t���O
======================================== */
int CCombo::GetComboEndFlg(int num)
{
	return m_dComboInfo[num].bEndFlg;
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
	m_dComboInfo[num].bEndFlg = true;					// �R���{�I���t���O���I��
	
	m_pTotalScore->ComboCheck(m_dComboInfo[num], num);	// �{�������߂�
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




