/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X�R�A�Ǘ��pcpp
	---------------------------------------
	TotalScore.cpp

	�쐬��	�R�{�M��

	�ύX����
	�E2023/11/22�@�쐬 yamamoto
	�E2023/11/23�@�`�揈���ǉ� yamamoto
	�E2023/11/24�@�e�N�X�`���̒���,�R�����g���� yamamoto

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
	, m_pPlusScoreTexture(nullptr)
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
	m_pPlusScoreTexture = new Texture();
	if (FAILED(m_pPlusScoreTexture->Create("Assets/Texture/numbers_v1/plus_score_numbers.png")))
	{
		MessageBox(NULL, "PlusScore�����ǂݍ���", "Error", MB_OK);
	}
	
	for (int i = 0; i < TOTALSCORE_DIGIT; i++)//�g�[�^���X�R�A�̌������
	{
		TotalScoreArray.push_back(0);
	}
	for (int i = 0; i < MAX_COMBO_NUM; i++)
	{
		m_PlusScore[i].nAddScore = 0;
		m_PlusScore[i].fComboMagnification = 0;
		m_PlusScore[i].bEndComboFlg = true;
		m_PlusScore[i].bDispTotalScoreFlg = true;
		m_PlusScore[i].nDispFrame = 0;
		m_PlusScore[i].bDispFlg = false;
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
	SAFE_DELETE(m_pPlusScoreTexture);
	TotalScoreArray.clear();
}
void CTotalScore::Update()
{
	
}
/* ========================================
	�֐��F�`��֐�
	----------------------------------------
	���e�F�X�R�A�̕`�揈��
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
	Sprite::SetSize(DirectX::XMFLOAT2(TOTALSCORE_SIZE.x, TOTALSCORE_SIZE.y));
	Sprite::SetUVScale(DirectX::XMFLOAT2(0.2f, 0.5f));
	Sprite::SetTexture(m_pToScoreTexture);

	for (int i = 0; i < TOTALSCORE_DIGIT; i++)
	{
		int width = TOTALSCORE_SIZE.x * i;
		//���[���h�s���X��Y�݂̂��l�����č쐬(Z��10���炢�ɔz�u
		DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(TOTALSCORE_POS.x - width, TOTALSCORE_POS.y, 0.0f);
		DirectX::XMStoreFloat4x4(&time[0], DirectX::XMMatrixTranspose(world));

		//�X�v���C�g�̐ݒ�
		Sprite::SetWorld(time[0]);
		
		int x = TotalScoreArray[i] % 5;	//�������O��W���܂�
		int y = TotalScoreArray[i] / 5;	//�z��ɓ����Ă鐔���̏ꏊ���v�Z���Ă܂�
		
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f*x, 0.5f*y));
		Sprite::Draw();
	}
	//���Z�\��̃X�R�A�i�g�[�^���̉��j�̕`��ݒ�T�C�Y�ȊO�͓����Ȃ̂ŏȗ�
	Sprite::SetSize(DirectX::XMFLOAT2(PLUSSCORE_SIZE.x, PLUSSCORE_SIZE.y));
	Sprite::SetUVScale(DirectX::XMFLOAT2(0.2f, 0.333f));
	Sprite::SetTexture(m_pPlusScoreTexture);
	for (int i = 0, lineNum=1; i < MAX_COMBO_NUM; i++)
	{
		
		if (m_PlusScore[i].nAddScore == 0)continue;//�����Ȃ���΃X���[

		
		if (m_PlusScore[i].bDispTotalScoreFlg == true) 
		{
			
 			digitArray = digitsToArray(m_PlusScore[i].nAddScore);	
			nArraySize = digitArray.size();				//�������m�F
			for (int i = 0; i < nArraySize; i++)
			{
				int width = PLUSSCORE_SIZE.x * i;
				int hight = ROW_HIGHT * lineNum;
				//���[���h�s���X��Y�݂̂��l�����č쐬(Z��10���炢�ɔz�u
				DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(TOTALSCORE_POS.x - width, TOTALSCORE_POS.y + hight, 0.0f);
				DirectX::XMStoreFloat4x4(&time[0], DirectX::XMMatrixTranspose(world));

				//�X�v���C�g�̐ݒ�
				Sprite::SetWorld(time[0]);

				int y = digitArray[i] % 5;	//�������O��W���܂�
				int x = digitArray[i] / 5;	//�z��ɓ����Ă鐔���̏ꏊ���v�Z���Ă܂�
				Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f*y, 0.333f*x));

				Sprite::Draw();
			}
			//+�̕\��
			int width = PLUSSCORE_SIZE.x * nArraySize;
			int hight = ROW_HIGHT * lineNum;
			//���[���h�s���X��Y�݂̂��l�����č쐬(Z��10���炢�ɔz�u
			DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(TOTALSCORE_POS.x - width, TOTALSCORE_POS.y + hight, 0.0f);
			DirectX::XMStoreFloat4x4(&time[0], DirectX::XMMatrixTranspose(world));

			//�X�v���C�g�̐ݒ�
			Sprite::SetWorld(time[0]);
			Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.666f));

			Sprite::Draw();
			lineNum++;
		}
		else
		{
			AddTotalScore();
			m_PlusScore[i].bDispTotalScoreFlg = true;
			m_PlusScore[i].nAddScore = 0;
			m_PlusScore[i].bEndComboFlg = true;
			m_PlusScore[i].nDispFrame = 0;
			m_PlusScore[i].bDispFlg = false;
		}
	
		m_PlusScore[i].nDispFrame++;
		if (!m_PlusScore[i].bEndComboFlg)
		{
			// �b���R���{�{����\������
			
			if (m_PlusScore[i].nDispFrame >= 1 * 60)
			{
				m_PlusScore[i].bEndComboFlg = true;
				m_PlusScore[i].bDispFlg = true;
				m_PlusScore[i].nAddScore *= m_PlusScore[i].fComboMagnification;
				m_PlusScore[i].nDispFrame = 0;
			}
			digitArray = digitsToArray(m_PlusScore[i].fComboMagnification*10);
			nArraySize = digitArray.size();				//�������m�F
			for (int i = 0; i < nArraySize; i++)
			{
				int width = MAGNIFICATION * i;
				int hight = ROW_HIGHT * lineNum;
				//���[���h�s���X��Y�݂̂��l�����č쐬(Z��10���炢�ɔz�u
				DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(TOTALSCORE_POS.x - width, TOTALSCORE_POS.y + hight, 0.0f);
				DirectX::XMStoreFloat4x4(&time[0], DirectX::XMMatrixTranspose(world));

				//�X�v���C�g�̐ݒ�
				Sprite::SetWorld(time[0]);

				int y = digitArray[i] % 5;	//�������O��W���܂�
				int x = digitArray[i] / 5;	//�z��ɓ����Ă鐔���̏ꏊ���v�Z���Ă܂�
				Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f*y, 0.333f*x));

				Sprite::Draw();
			}
			//�~�\��
			int width = PLUSSCORE_SIZE.x*2+ SMALLDECIMAL_SIZE.x;
			int hight = ROW_HIGHT * lineNum;
			//���[���h�s���X��Y�݂̂��l�����č쐬(Z��10���炢�ɔz�u
			DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(TOTALSCORE_POS.x - width, TOTALSCORE_POS.y + hight, 0.0f);
			DirectX::XMStoreFloat4x4(&time[0], DirectX::XMMatrixTranspose(world));
			
			//�X�v���C�g�̐ݒ�
			Sprite::SetWorld(time[0]);
			Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f, 0.666f));
			
			Sprite::Draw();
			
			Sprite::SetSize(DirectX::XMFLOAT2(SMALLDECIMAL_SIZE.x, SMALLDECIMAL_SIZE.y));
			//�����_�\��
			width = PLUSSCORE_SIZE.x- SMALLDECIMAL_POS.x;
			hight -= SMALLDECIMAL_POS.y;
			//���[���h�s���X��Y�݂̂��l�����č쐬(Z��10���炢�ɔz�u
			 world = DirectX::XMMatrixTranslation(TOTALSCORE_POS.x - width, TOTALSCORE_POS.y + hight, 0.0f);
			DirectX::XMStoreFloat4x4(&time[0], DirectX::XMMatrixTranspose(world));
			
			//�X�v���C�g�̐ݒ�
			Sprite::SetWorld(time[0]);
			Sprite::SetUVPos(DirectX::XMFLOAT2(0.4f, 0.666f));
			
			Sprite::Draw();
			lineNum++;
		}
		if (m_PlusScore[i].nDispFrame >= 2 * 60&& m_PlusScore[i].bDispFlg)
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
	m_PlusScore[num].nDispFrame = 0;
	
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

