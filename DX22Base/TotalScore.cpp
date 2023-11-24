/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X�R�A�Ǘ��pcpp
	---------------------------------------
	TotalScore.cpp

	�쐬��	�R�{�M��

	�ύX����
	�E2023/11/22�@�쐬

========================================== */

// =============== �C���N���[�h ===================
#include "TotalScore.h"
#include "Sprite.h"

/* ========================================
	�֐��F�R���X�g���N�^
	-------------------------------------
	���e�F���s���ɍs������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CTotalScore::CTotalScore()
	: m_nTotalScore(0)
	, m_pToScoreTexture(nullptr)
	, TotalScoreArray{}
	, digitArray{}
	, nArraySize(0)
	, digits{}
{
	m_pToScoreTexture = new Texture();
	if (FAILED(m_pToScoreTexture->Create("Assets/Texture/numbers_v1/combo_numbers.png")))
	{
		MessageBox(NULL, "ToScore�����ǂݍ���", "Error", MB_OK);
	}
	for (int i = 0; i < TOTALSCORE_DIGIT; i++)//�g�[�^���X�R�A�̌������
	{
		TotalScoreArray.push_back(0);
	}
	for (int i = 0; i < MAX_COMBO_NUM; i++)
	{
		m_PlusScore[i].nAddScore = 0;
		m_PlusScore[i].fComboMagnification = 0;
		m_PlusScore[i].bEndComboFlg = false;
		m_PlusScore[i].bDispTotalScoreFlg = true;
		m_PlusScore[i].nDispFrame = 0;
	}
}
/* ========================================
	�֐��F�f�X�g���N�^
	-------------------------------------
	���e�F�j�����ɍs������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CTotalScore::~CTotalScore()
{
	SAFE_DELETE(m_pToScoreTexture);
	TotalScoreArray.clear();
}
void CTotalScore::Update()
{
	
}
/* ========================================
	�֐��F�`��֐�
	----------------------------------------
	���e�F�����}�l�[�W���[�̕`�揈��
	----------------------------------------
	�����F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CTotalScore::Draw()
{
	DirectX::XMFLOAT4X4 time[3];
	//�r���[�s���2D���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��i�P�ʍs��͌��
	DirectX::XMStoreFloat4x4(&time[1], DirectX::XMMatrixIdentity());

	//�v���W�F�N�V�����s��ɂ�2D�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	//���̍s���2D�̃X�N���[���̑����������܂�
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&time[2], DirectX::XMMatrixTranspose(proj));
	
	//�g�[�^���X�R�A�i��ԉE��j�̕`��ݒ�
	//�X�v���C�g�̐ݒ�
	Sprite::SetView(time[1]);
	Sprite::SetProjection(time[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(50.0f, -50.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(0.2f, 0.5f));
	Sprite::SetTexture(m_pToScoreTexture);

	for (int i = 0; i < TOTALSCORE_DIGIT; i++)
	{
		int width = 50 * i;
		//���[���h�s���X��Y�݂̂��l�����č쐬(Z��10���炢�ɔz�u
		DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(TOTALSCORE_POS.x - width, TOTALSCORE_POS.y, 0.0f);
		DirectX::XMStoreFloat4x4(&time[0], DirectX::XMMatrixTranspose(world));

		//�X�v���C�g�̐ݒ�
		Sprite::SetWorld(time[0]);
		
		int y = TotalScoreArray[i] % 5;	//�������O��W���܂�
		int x = TotalScoreArray[i] / 5;	//�z��ɓ����Ă鐔���̏ꏊ���v�Z���Ă܂�
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f*y, 0.5f*x));
		Sprite::Draw();
	}
	//���Z�\��̃X�R�A�i�g�[�^���̉��j�̕`��ݒ�T�C�Y�ȊO�͓����Ȃ̂ŏȗ�
	Sprite::SetSize(DirectX::XMFLOAT2(30.0f, -30.0f));

	for (int i = 0, lineNum=1; i < MAX_COMBO_NUM; i++)
	{
		if (m_PlusScore[i].nAddScore == 0)continue;//�����Ȃ���΃X���[

		if (m_PlusScore[i].bDispTotalScoreFlg == true) 
		{

 			digitArray = digitsToArray(m_PlusScore[i].nAddScore);	
			nArraySize = digitArray.size();				//�������m�F
			for (int i = 0; i < nArraySize; i++)
			{
				int width = 30 * i;
				int hight = 40 * lineNum;
				//���[���h�s���X��Y�݂̂��l�����č쐬(Z��10���炢�ɔz�u
				DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(TOTALSCORE_POS.x - width, TOTALSCORE_POS.y + hight, 0.0f);
				DirectX::XMStoreFloat4x4(&time[0], DirectX::XMMatrixTranspose(world));

				//�X�v���C�g�̐ݒ�
				Sprite::SetWorld(time[0]);

				int y = digitArray[i] % 5;	//�������O��W���܂�
				int x = digitArray[i] / 5;	//�z��ɓ����Ă鐔���̏ꏊ���v�Z���Ă܂�
				Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f*y, 0.5f*x));

				Sprite::Draw();
			}
			lineNum++;
		}
		else
		{
			AddTotalScore();
			m_PlusScore[i].bDispTotalScoreFlg = true;
			m_PlusScore[i].nAddScore = 0;
			m_PlusScore[i].bEndComboFlg = true;
			m_PlusScore[i].nDispFrame = 0;
		}
		//if (m_PlusScore[i].bEndComboFlg
		//	&&!m_PlusScore[i].bDispTotalScoreFlg)//�R���{�I����
		m_PlusScore[i].nDispFrame++;
		if (!m_PlusScore[i].bEndComboFlg)
		{
			// �b���R���{����\������
			
			if (m_PlusScore[i].nDispFrame >= 5 * 60)
			{
				m_PlusScore[i].bEndComboFlg = true;
			}
			digitArray = digitsToArray(m_PlusScore[i].fComboMagnification*10);
			nArraySize = digitArray.size();				//�������m�F
			for (int i = 0; i < nArraySize; i++)
			{
				int width = 30 * i;
				int hight = 40 * lineNum;
				//���[���h�s���X��Y�݂̂��l�����č쐬(Z��10���炢�ɔz�u
				DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(TOTALSCORE_POS.x - width, TOTALSCORE_POS.y + hight, 0.0f);
				DirectX::XMStoreFloat4x4(&time[0], DirectX::XMMatrixTranspose(world));

				//�X�v���C�g�̐ݒ�
				Sprite::SetWorld(time[0]);

				int y = digitArray[i] % 5;	//�������O��W���܂�
				int x = digitArray[i] / 5;	//�z��ɓ����Ă鐔���̏ꏊ���v�Z���Ă܂�
				Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f*y, 0.5f*x));

				Sprite::Draw();
			}
			lineNum++;

		}
		
		if (m_PlusScore[i].nDispFrame >= 8 * 60)
		{
			m_PlusScore[i].bDispTotalScoreFlg = false;
		}
	}

}
/* ========================================
	�v���X�X�R�A���Z�֐�
	----------------------------------------
	���e�F�v���X�X�R�A�̉��Z
	----------------------------------------
	����1�F�\����,�z��ԍ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CTotalScore::AddScore(CCombo::ComboInfo comboInfo,int num)
{

	m_PlusScore[num].nAddScore = comboInfo.dScore;

	//m_PlusScore[num].fComboMagnification= comboInfo.dCnt
	
}
/* ========================================
	�{���m��֐�
	----------------------------------------
	���e�F�R���{�I�����̔{�����m��
	----------------------------------------
	����1�F�\����,�z��ԍ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CTotalScore::ComboCheck(CCombo::ComboInfo comboInfo, int num)
{
	if (comboInfo.dCnt <= 5) m_PlusScore[num].fComboMagnification = 1.0f;
	else if (comboInfo.dCnt == 6)m_PlusScore[num].fComboMagnification = 1.1f;
	else if (comboInfo.dCnt == 7)m_PlusScore[num].fComboMagnification = 1.2f;
	else if (comboInfo.dCnt == 8)m_PlusScore[num].fComboMagnification = 1.3f;
	else if (comboInfo.dCnt == 9)m_PlusScore[num].fComboMagnification = 1.4f;
	else if (comboInfo.dCnt >= 10) m_PlusScore[num].fComboMagnification = 1.5f;

	m_PlusScore[num].bEndComboFlg = false;
	
}

/* ========================================
	�g�[�^���X�R�A���Z�֐�
	----------------------------------------
	���e�F�g�[�^���X�R�A�̉��Z
	----------------------------------------
	����1�F
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CTotalScore::AddTotalScore()
{

	m_nTotalScore += m_PlusScore->nAddScore;
	if (m_nTotalScore > MAX_TOTALSCORE)
	{
		m_nTotalScore = MAX_TOTALSCORE;
	}

	digitArray = digitsToArray(m_nTotalScore);
	nArraySize = digitArray.size();

	TotalScoreArray.clear();					//���Z�O�̃g�[�^���X�R�A�폜
	for (int i = 0; i < TOTALSCORE_DIGIT; i++)//�g�[�^���X�R�A�̌������
	{
		TotalScoreArray.push_back(0);
	}
	for (int i = 0; i < nArraySize; i++)	//���Z��̃g�[�^���X�R�A�쐬
	{
		TotalScoreArray[i] = digitArray[i];
	}
	digitArray.clear();
}
/* ========================================
	�g�[�^���X�R�A�擾�֐�
	----------------------------------------
	���e�F�g�[�^���X�R�A�̎擾
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�g�[�^���X�R�A�̐��l
======================================== */
int CTotalScore::GetTotalScore()
{
	return m_nTotalScore;
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
std::vector<int> CTotalScore::digitsToArray(int score)
{
	digits.clear();
	while (score > 0) {
		digits.push_back(score % 10);
		score /= 10;
	}
	// �P�̈ʂ�������Ă���̂Ŕ��]����
	//std::reverse(digits.begin(), digits.end());
	return digits;
}


