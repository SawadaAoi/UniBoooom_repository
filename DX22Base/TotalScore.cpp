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
	�E2023/11/26�@�R���{�{���̕\���̕ύX yamamoto
	�E2023/12/07 �Q�[���p�����[�^����ꕔ�萔�ړ��E�C���N���[�h�ǉ� takagi
	�E2024/01/26 ���������₷���C��&&�g�[�^���X�R�A���Z�A�j�������ǉ� sawada
	�E2024/02/02 �Q�[���I���ԍۂ̉��Z�X�R�A���g�[�^���X�R�A�ɔ��f�����悤�� suzumura
	�E2024/02/05 �Q�[���I���ԍۂ̉��Z�X�R�A���g�[�^���X�R�A�ɔ��f�����悤��(��) sawada

========================================== */

// =============== �C���N���[�h ===================
#include "TotalScore.h"
#include "Sprite.h"
#include "Pos2d.h"	//�񎟌����W
#include "UIStageManager.h"

// =============== �萔��` ===================
const std::string TEXTURE_PATH[CTotalScore::TEXTURE_MAX][2] =
{
	{"�g�[�^���X�R�A����","Assets/Texture/Score/score_numbers.png"},
	{"���Z�X�R�A����","Assets/Texture/Score/plus_score_numbers.png"},
	{"�g�[�^���X�R�A�w�i","Assets/Texture/Score/total_score_back_1.png"},
	{"���Z�X�R�A�w�i","Assets/Texture/Score/plus_score_back_1.png"},
};

const int ADD_SCORE_DISP_FRAME = 1.5f * 60;		// ���Z�X�R�A�\������
const int COMBO_MULT_DISP_FRAME = 1.0f * 60;	// �R���{�{���\������
const int TOTAL_SCORE_MOVE_FRAME = 0.05f * 60;	// �g�[�^���X�R�A���Z�A�j�������؂�ւ�����
const int TOTAL_SCORE_MOVE_ADD_POINT = 100;		// �g�[�^���X�R�A���Z�A�j���������Z�l


const int COMBO_MULTI_DISPLAY_NUM	= 6;					// �{���\���ŏ��R���{��
const int COMBO_MULTI_MAX_NUM		= 10;					// �{���ω��ő�R���{��

const float COMBO_MULTI_NUM[COMBO_MULTI_MAX_NUM + 1] = {	// �R���{���ɂ����Z�X�R�A�̔{��
	1.0f,	// 0
	1.0f,	// 1
	1.0f,	// 2
	1.0f,	// 3
	1.0f,	// 4
	1.0f,	// 5
	1.1f,	// 6
	1.2f,	// 7
	1.3f,	// 8
	1.4f,	// 9
	1.5f,	// 10
};


const int TOTAL_SCORE_DIGIT = 5;						//�g�[�^���X�R�A�̌���
const int MAX_TOTALSCORE = 99999;						//���ꏏ�ɕς��Ă��������i������9��ǉ��j//�ő�g�[�^�A���X�R�A

const TDiType<float> TOTAL_SCORE_POS(1230.0f, 50.0f);	// �g�[�^���X�R�A�̈ʒu�ݒ�
const TDiType<float> TOTAL_SCORE_SIZE(50.0f, -75.0f);	// �g�[�^���X�R�A�̕\���̑傫��
const TDiType<float> TOTAL_SCORE_UVSIZE(0.2f, 0.5f);	// �g�[�^���X�R�A��UV�̑傫��
const float TOTAL_SCORE_WIDTH = 50.0f;					   
														   
const TDiType<float> ADD_SCORE_POS(1230.0f, 50.0f);		// ���Z�X�R�A�̈ʒu�ݒ�
const TDiType<float> ADD_SCORE_SIZE(30.0f, -40.0f);		// ���Z�X�R�A�̕\���̑傫��
const TDiType<float> ADD_SCORE_UVSIZE(0.2f, 0.333f);	// ���Z�X�R�A��UV�̑傫��
const float ADD_SCORE_WIDTH = 30.0f;					   
const float ADD_SCORE_HIGHT = 60.0f;		

const TDiType<float> PLUS_SYMBOL_SIZE(30.0f, -40.0f);	// +�̕\���̑傫��
const TDiType<float> PLUS_SYMBOL_UVPOS(0.0f, 0.666f);	// +�̕\����UV���W
													   
const float CONBO_MULTI_WIDTH = 40.0f;

const TDiType<float> DECIMAL_POINT_POS(CONBO_MULTI_WIDTH / 2, -0.0f);	// �����_�̈ʒu�ݒ�
const TDiType<float> DECIMAL_POINT_SIZE(30.0f, -30.0f);	// �����_�̕\���̑傫��
const TDiType<float> DECIMAL_POINT_UVPOS(0.4f, 0.666f); // �����_��UV���W

const TDiType<float> CROSS_SYMBOL_SIZE(40.0f, -65.0f);	// �~�̕\���̑傫��
const TDiType<float> CROSS_SYMBOL_UVPOS(0.2f, 0.666f);	// �~�̕\����UV���W


const TPos2d<float> TOTAL_SCORE_BG_POS(1130.0f, 55.0f);		// �g�[�^���X�R�A�̔w�i�ʒu�ݒ�
const DirectX::XMFLOAT2 TOTAL_SCORE_BG_SIZE(320.0f, -110.0f);	// �g�[�^���X�R�A�̔w�i�̕\���̑傫��

const TPos2d<float> PLUS_SCORE_BG_POS(1175.0f, 60.0f);		// �g�[�^���X�R�A�̔w�i�ʒu�ݒ�
const DirectX::XMFLOAT2 PLUS_SCORE_BG_SIZE(200.0f, -50.0f);	// �g�[�^���X�R�A�̔w�i�̕\���̑傫��


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
	: m_nTotalScoreDisp(0)
	, m_nTotalScore(0)
	, m_nToScoreAddCnt(0)

{
	for (int i = 0; i < TextureType::TEXTURE_MAX; i++)
	{
		m_pTexture[i] = new Texture();
		if (FAILED(m_pTexture[i]->Create(TEXTURE_PATH[i][1].c_str())))
		{
			MessageBox(NULL, TEXTURE_PATH[i][0].c_str(), "Error", MB_OK);
		}
	}

	for (int i = 0; i < MAX_COMBO_NUM; i++)
	{
		// �X�R�A���Z�l�z�񃊃Z�b�g
		m_AddScore[i] = ResetAddScore();

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
	for (int i = 0; i < TextureType::TEXTURE_MAX; i++)
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
void CTotalScore::Update()
{
	TotalScoreMove();	// �g�[�^���X�R�A

	// ���Z�X�R�A
	for (int i = 0, lineNum = 1; i < MAX_COMBO_NUM; i++)
	{
		if (m_AddScore[i].nAddScore == 0)	continue;	// �l�̂Ȃ����̓X���[

		if (!m_AddScore[i].bEndComboFlg)	continue;	// �R���{�p�����̏ꍇ�͌㑱�̏����͍s��Ȃ�

		// �R���{�I����------------------------------

		// �R���{�{���\�����I�����Ă��Ȃ��ꍇ
		if (!m_AddScore[i].bDispCombMultEndFlg)
		{
			// �R���{����1�`5�̏ꍇ
			if (m_AddScore[i].nComboCnt < COMBO_MULTI_DISPLAY_NUM)
			{
				m_AddScore[i].bDispCombMultEndFlg = true; // �R���{�{���͕\�����Ȃ��ׁA�\���I��
			}
			// �R���{�{����6�ȏ�̏ꍇ
			else
			{
				m_AddScore[i].nDispCombMultCnt++;	// �R���{�{���\���J�E���g���Z

				// ���b���R���{�{����\��������
				if (m_AddScore[i].nDispCombMultCnt >= COMBO_MULT_DISP_FRAME)
				{
					m_AddScore[i].nAddScore = static_cast<int>
						( m_AddScore[i].nAddScore * m_AddScore[i].fCombScoreMult );	// �R���{�{�������Z�X�R�A�Ɋ|����
					m_AddScore[i].bDispCombMultEndFlg = true;						// �R���{�{���\���I��
				}
			}
			
			continue;	// �����ŏ����͏I��
		}
		
		// �R���{�{���\���I���� ----------------------------------

		// ���Z�X�R�A�\�����̏ꍇ
		if (!m_AddScore[i].bDispAddScoreEndFlg)
		{
			m_AddScore[i].nDispAddScoreCnt++;	// ���Z�X�R�A�\���J�E���g���Z

			// ��莞�ԉ��Z�X�R�A��\��������
			if (ADD_SCORE_DISP_FRAME <= m_AddScore[i].nDispAddScoreCnt)
			{
				AddTotalScore(m_AddScore[i].nAddScore);		// �g�[�^���X�R�A�ɉ��Z
				m_AddScore[i].bDispAddScoreEndFlg = true;	// ���Z�X�R�A�`������߂�
				m_pUIMng->PlaySE(CUIStageManager::SE_ADD_SCORE);
			}
		}
		// ���Z�X�R�A�\���I����̏ꍇ
		else
		{
			m_AddScore[i] = ResetAddScore();		// ���Z�X�R�A�z��l���Z�b�g

		}

	}
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
	RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
	DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
	SetRenderTargets(1, &pRTV, nullptr);		//DSV��null����2D�\���ɂȂ�

	DrawBGTotalScore();		// �g�[�^���X�R�A�w�i�`��
	DrawTotalScore();		// �g�[�^���X�R�A�`��

	// ���Z�X�R�A�\��	-----------
	// �����R���{���������s�ŕ\������
	for (int i = 0, lineNum = 1; i < MAX_COMBO_NUM; i++)
	{
		if (m_AddScore[i].nAddScore == 0)continue; // �����Ȃ���΃X���[

		DrawBGAddScore(lineNum);	// ���Z�X�R�A�̔w�i�`��
		DrawAddScore(i, lineNum);	// ���Z�X�R�A�`��
		lineNum++;					// �i���؂�ւ�

		if (!m_AddScore[i].bEndComboFlg) continue;	// �R���{�p�����̏ꍇ�͌㑱�̏����͍s��Ȃ�

		// �R���{�{���\���t���O���L���̏ꍇ(�R���{����6�����̏ꍇ�͍s��Ȃ�)
		if (!m_AddScore[i].bDispCombMultEndFlg)
		{
			DrawBGAddScore(lineNum);			// �w�i�`��(���Z�X�R�A�Ɠ��l�̂���)
			DrawScoreComboMulti(i, lineNum);	// �{���`��(��:1.2)
			lineNum++;							// �i���؂�ւ�

		}

	}
}

/* ========================================
	�g�[�^���X�R�A�`��֐�
	----------------------------------------
	���e�F�g�[�^���X�R�A�`�揈��
	----------------------------------------
	�����F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CTotalScore::DrawTotalScore()
{
	DrawNumber(
		m_nTotalScoreDisp, 
		TOTAL_SCORE_SIZE, 
		TOTAL_SCORE_POS, 
		TOTAL_SCORE_UVSIZE, 
		TOTAL_SCORE_WIDTH, 
		0.0f, 
		m_pTexture[TextureType::NUM_TOTAL_SCORE],
		TOTAL_SCORE_DIGIT);
}

/* ========================================
	���Z�X�R�A�`��֐�
	----------------------------------------
	���e�F���Z�X�R�A�`�揈��
	----------------------------------------
	�����F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CTotalScore::DrawAddScore(int nNum, int lineNum)
{
	DrawNumber(
		m_AddScore[nNum].nAddScore,
		ADD_SCORE_SIZE,
		ADD_SCORE_POS,
		ADD_SCORE_UVSIZE,
		ADD_SCORE_WIDTH,
		ADD_SCORE_HIGHT * lineNum,
		m_pTexture[TextureType::NUM_ADD_SCORE],
		0);


	//+�̕\��
	int AdScoDigi = digitsToArray(m_AddScore[nNum].nAddScore, 0).size();

	TDiType<float> fSetPos = { 
		ADD_SCORE_POS.x - (ADD_SCORE_SIZE.x * AdScoDigi), 
		ADD_SCORE_POS.y + (ADD_SCORE_HIGHT * lineNum) 
	};

	DrawTexture(
		PLUS_SYMBOL_SIZE, 
		fSetPos, 
		ADD_SCORE_UVSIZE, 
		PLUS_SYMBOL_UVPOS,
		m_pTexture[TextureType::NUM_ADD_SCORE]);

}

/* ========================================
	�g�[�^���X�R�A�w�i�`��֐�
	-------------------------------------
	���e�F�g�[�^���X�R�A�̔w�i��`�悷��
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CTotalScore::DrawBGTotalScore()
{
	//�{�X�Q�[�W�e�N�X�`���i��j
	DirectX::XMFLOAT4X4 TScoreBG[3];

	//���[���h�s���X��Y�݂̂��l�����č쐬
	DirectX::XMMATRIX worldTscorebg = DirectX::XMMatrixTranslation(TOTAL_SCORE_BG_POS.x, TOTAL_SCORE_BG_POS.y, 0.0f);

	DirectX::XMStoreFloat4x4(&TScoreBG[0], DirectX::XMMatrixTranspose(worldTscorebg));

	//�r���[�s���2D���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��i�P�ʍs��͌��
	DirectX::XMStoreFloat4x4(&TScoreBG[1], DirectX::XMMatrixIdentity());

	//�v���W�F�N�V�����s��ɂ�2D�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	//���̍s���2D�̃X�N���[���̑����������܂�
	DirectX::XMMATRIX projTscorebg = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.1f, 0.0f);
	DirectX::XMStoreFloat4x4(&TScoreBG[2], DirectX::XMMatrixTranspose(projTscorebg));

	//�X�v���C�g�̐ݒ�
	Sprite::SetWorld(TScoreBG[0]);
	Sprite::SetView(TScoreBG[1]);
	Sprite::SetProjection(TScoreBG[2]);
	Sprite::SetSize(TOTAL_SCORE_BG_SIZE);
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[TextureType::BG_TOTAL_SCORE] );
	Sprite::Draw();
}

/* ========================================
	���Z�X�R�A�w�i�`��֐�
	-------------------------------------
	���e�F���Z�X�R�A�̔w�i��`�悷��
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CTotalScore::DrawBGAddScore(int lineNum)
{
	//�{�X�Q�[�W�e�N�X�`���i��j
	DirectX::XMFLOAT4X4 PScoreBG[3];
	int hight = int(ADD_SCORE_HIGHT * lineNum);
	//���[���h�s���X��Y�݂̂��l�����č쐬
	DirectX::XMMATRIX worldPscorebg = DirectX::XMMatrixTranslation(PLUS_SCORE_BG_POS.x, PLUS_SCORE_BG_POS.y + hight, 0.0f);
	DirectX::XMStoreFloat4x4(&PScoreBG[0], DirectX::XMMatrixTranspose(worldPscorebg));

	//�r���[�s���2D���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��i�P�ʍs��͌��
	DirectX::XMStoreFloat4x4(&PScoreBG[1], DirectX::XMMatrixIdentity());

	//�v���W�F�N�V�����s��ɂ�2D�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	//���̍s���2D�̃X�N���[���̑����������܂�
	DirectX::XMMATRIX projPscorebg = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.1f, 0.0f);
	DirectX::XMStoreFloat4x4(&PScoreBG[2], DirectX::XMMatrixTranspose(projPscorebg));

	//�X�v���C�g�̐ݒ�
	Sprite::SetWorld(PScoreBG[0]);
	Sprite::SetView(PScoreBG[1]);
	Sprite::SetProjection(PScoreBG[2]);
	Sprite::SetSize(PLUS_SCORE_BG_SIZE);
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[TextureType::BG_ADD_SCORE]);
	Sprite::Draw();
}


/* ========================================
	�X�R�A�R���{�{���`��֐�
	----------------------------------------
	���e�F�X�R�A�R���{�{���`�揈��
	----------------------------------------
	�����F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CTotalScore::DrawScoreComboMulti(int nNum, int lineNum)
{
	DrawNumber(
		m_AddScore[nNum].fCombScoreMult * 10,
		ADD_SCORE_SIZE,
		ADD_SCORE_POS,
		ADD_SCORE_UVSIZE,
		CONBO_MULTI_WIDTH,
		ADD_SCORE_HIGHT * lineNum,
		m_pTexture[TextureType::NUM_ADD_SCORE],
		0);


	//�����_�\��
	int AdScoDigi = digitsToArray(m_AddScore[nNum].nAddScore, 0).size();

	TDiType<float> fSetPos = { 
		ADD_SCORE_POS.x - DECIMAL_POINT_POS.x ,
		ADD_SCORE_POS.y + (ADD_SCORE_HIGHT* lineNum)+ DECIMAL_POINT_POS.y 
	};
	DrawTexture(
		DECIMAL_POINT_SIZE,
		fSetPos,
		ADD_SCORE_UVSIZE,
		DECIMAL_POINT_UVPOS,
		m_pTexture[TextureType::NUM_ADD_SCORE]);

	//�~�\��
	fSetPos = {
		ADD_SCORE_POS.x - (ADD_SCORE_SIZE.x * 2 + DECIMAL_POINT_SIZE.x),
		ADD_SCORE_POS.y + (ADD_SCORE_HIGHT* lineNum)
	};
	DrawTexture(
		CROSS_SYMBOL_SIZE,
		fSetPos,
		ADD_SCORE_UVSIZE,
		CROSS_SYMBOL_UVPOS,
		m_pTexture[TextureType::NUM_ADD_SCORE]);


}


/* ========================================
	�摜�`��֐�
	----------------------------------------
	���e�F�摜��\������
	----------------------------------------
	����1�F�傫��
	����2�F�\���ʒu
	����3�FUV�T�C�Y
	����4�FUV���W
	����5�F�摜�|�C���^
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CTotalScore::DrawTexture(TDiType<float> fSize, TDiType<float> fPos, TDiType<float> fUVSize, TDiType<float> fUVPos, Texture * pTexture)
{
	// �s��̃Z�b�g
	DirectX::XMFLOAT4X4 Mat[3];
	DirectX::XMStoreFloat4x4(&Mat[1], DirectX::XMMatrixIdentity());
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&Mat[2], DirectX::XMMatrixTranspose(proj));

	// �s��
	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(fPos.x, fPos.y, 0.0f);	// ���W�ړ�
	DirectX::XMStoreFloat4x4(&Mat[0], DirectX::XMMatrixTranspose(world));

	Sprite::SetWorld(Mat[0]);
	Sprite::SetView(Mat[1]);		// �r���[�s��
	Sprite::SetProjection(Mat[2]);	// �v���W�F�N�V�����s��

	Sprite::SetSize(DirectX::XMFLOAT2(fSize.x, fSize.y));			// �摜�T�C�Y
	Sprite::SetUVScale(DirectX::XMFLOAT2(fUVSize.x, fUVSize.y));	// UV�T�C�Y
	Sprite::SetUVPos(DirectX::XMFLOAT2(fUVPos.x, fUVPos.y));		// UV���W

	Sprite::SetTexture(pTexture);									// �摜�|�C���^

	Sprite::Draw();
}

/* ========================================
	�����`��֐�
	----------------------------------------
	���e�F�����̕��т�\������
	----------------------------------------
	����1�F�`�搔��
	����2�F�傫��
	����3�F�\���ʒu
	����4�FUV�T�C�Y
	����5�F�����Ԃ̋󔒑傫��
	����6�F�������c�ɂ��炷�ʒu
	����7�F�摜�|�C���^
	����8�F����
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CTotalScore::DrawNumber(int dispNum, TDiType<float> fSize, TDiType<float> fPos, 
	TDiType<float> fUVSize, float spaceW, float spaceH, Texture* pTexture, int digits)
{
	std::vector<int> digitArray = digitsToArray(dispNum, digits);

	// �s��̃Z�b�g
	DirectX::XMFLOAT4X4 Mat[3];
	DirectX::XMStoreFloat4x4(&Mat[1], DirectX::XMMatrixIdentity());
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&Mat[2], DirectX::XMMatrixTranspose(proj));

	//�g�[�^���X�R�A�i��ԉE��j�̕`��ݒ�
	//�X�v���C�g�̐ݒ�
	Sprite::SetView(Mat[1]);		// �r���[�s��
	Sprite::SetProjection(Mat[2]);	// �v���W�F�N�V�����s��

	Sprite::SetSize(DirectX::XMFLOAT2(fSize.x, fSize.y));
	Sprite::SetUVScale(DirectX::XMFLOAT2(fUVSize.x, fUVSize.y));
	Sprite::SetTexture(pTexture);

	// �������`��
	for (int i = 0; i < digitArray.size(); i++)
	{
		float width = spaceW * i;

		DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(fPos.x - width, fPos.y + spaceH, 0.0f);
		DirectX::XMStoreFloat4x4(&Mat[0], DirectX::XMMatrixTranspose(world));

		//�X�v���C�g�̐ݒ�
		Sprite::SetWorld(Mat[0]);

		int nUv_x = digitArray[i] % 5;	
		int nUv_y = digitArray[i] / 5;

		Sprite::SetUVPos(DirectX::XMFLOAT2(fUVSize.x * nUv_x, fUVSize.y * nUv_y));
		Sprite::Draw();
	}
}


/* ========================================
	���Z�X�R�A���Z�b�g�֐�
	----------------------------------------
	���e�F���Z�X�R�A�����Z�b�g����
	----------------------------------------
	����1�F����
	----------------------------------------
	�ߒl�F���Z�X�R�A�\����
======================================== */
CTotalScore::PlusScore CTotalScore::ResetAddScore()
{
	PlusScore reAddScore;	// �Ԃ��l
		
	reAddScore.nAddScore			= 0;
	reAddScore.nComboCnt			= 0;
	reAddScore.fCombScoreMult		= 0.0f;	// �R���{�X�R�A�{��
	reAddScore.bEndComboFlg			= false;
	reAddScore.nDispAddScoreCnt		= 0;
	reAddScore.bDispAddScoreEndFlg	= false;
	reAddScore.nDispCombMultCnt		= 0;
	reAddScore.bDispCombMultEndFlg	= false;

	return reAddScore;
}

/* ========================================
	���Z�X�R�A�Z�b�g�֐�
	----------------------------------------
	���e�F���Z�X�R�A���Z�b�g����
	----------------------------------------
	����1�F�R���{���\����
	����2�F�z��ԍ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CTotalScore::SetAddScore(CCombo::ComboInfo comboInfo, int num)
{
	m_AddScore[num].nAddScore = comboInfo.dScore;	// �R���{�̃X�R�A���X�V����
	m_AddScore[num].nComboCnt = comboInfo.dComboCnt;		// �R���{���X�V����
	
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
	SetCombScoreMult(num);						// �R���{�X�R�A�{���Z�b�g
	m_AddScore[num].bEndComboFlg = true;		// �R���{�I���t���O
	
}

/* ========================================
	�g�[�^���X�R�A���Z�֐�
	----------------------------------------
	���e�F�g�[�^���X�R�A�̉��Z
	----------------------------------------
	����1�F���Z����X�R�A�l
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CTotalScore::AddTotalScore(int addScore)
{
	m_nTotalScore += addScore;	// �g�[�^���X�R�A�ɉ��Z�X�R�A�𑫂�

	// �ő�l�������Ȃ��悤�ɂ���
	if ( MAX_TOTALSCORE < m_nTotalScore)
	{
		m_nTotalScore = MAX_TOTALSCORE;
	}


}

/* ========================================
	�Q�[���I���g�[�^���X�R�A���Z�֐�
	----------------------------------------
	���e�F�Q�[���I�����ɓr���̃g�[�^���X�R�A�̉��Z
	----------------------------------------
	����1�F���Z����X�R�A�l
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CTotalScore::GameEndAddTotal()
{
	for (int i = 0; i < MAX_COMBO_NUM; i++)
	{
		if (m_AddScore[i].nAddScore == 0)	continue;		// �l�̂Ȃ����̓X���[
		if (m_AddScore[i].bDispAddScoreEndFlg)	continue;	// �g�[�^���X�R�A�ɉ��Z�ς݂̂��̂̓X���[

		if (!m_AddScore[i].bDispCombMultEndFlg						// �R���{�{���`�悪���I��
			&& COMBO_MULTI_DISPLAY_NUM <= m_AddScore[i].nComboCnt )	// �R���{����6�ȏ�̏ꍇ
		{
			// �R���{�{�������߂�
			SetCombScoreMult(i);
			// �R���{�{�������Z�X�R�A�Ɋ|����
			m_AddScore[i].nAddScore = static_cast<int>(m_AddScore[i].nAddScore * m_AddScore[i].fCombScoreMult);	
		}

		AddTotalScore(m_AddScore[i].nAddScore);	// �g�[�^���X�R�A�ɉ��Z

	}
}

/* ========================================
	UI�}�l�[�W���[�|�C���^�Z�b�^�[�֐�
	----------------------------------------
	���e�FUI�}�l�[�W���[�|�C���^���Z�b�g����
	----------------------------------------
	����1�FUI�}�l�[�W���[�|�C���^
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CTotalScore::SetUIStageManagerPtr(CUIStageManager * pUIMng)
{
	m_pUIMng = pUIMng;
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
	����2�F�\�����錅��(0���߂���)
	-------------------------------------
	�ߒl�F���[�����z��
=========================================== */
std::vector<int> CTotalScore::digitsToArray(int score, int digits)
{
	std::vector<int> digitsArray;
	digitsArray.clear();

	// �w�萔����z��Ɋi�[����
	while (score > 0) {
		digitsArray.push_back(score % 10);
		score /= 10;
	}


	// �w�茅���܂�0���߂���
	while (digitsArray.size() < digits)
	{
		digitsArray.push_back(0);
	}

	return digitsArray;
}


/* ========================================
	�g�[�^���X�R�A���Z����֐�
	-------------------------------------
	���e�F�g�[�^���X�R�A�ɉ��Z�X�R�A�𑫂����l�܂Ő������A�j���[�V��������
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CTotalScore::TotalScoreMove()
{
	// �\���p�g�[�^���X�R�A�����Z��g�[�^���X�R�A���قȂ�
	if (m_nTotalScoreDisp != m_nTotalScore)
	{
		m_nToScoreAddCnt++;	// �\���p�g�[�^���X�R�A�̐����؂�ւ��J�E���g���Z


		// �؂�ւ����Ԃ��߂��Ă��邩
		if (TOTAL_SCORE_MOVE_FRAME <= m_nToScoreAddCnt)
		{
			m_nTotalScoreDisp += TOTAL_SCORE_MOVE_ADD_POINT;	// �\���p�X�R�A�����Z����


			// �\���p�g�[�^���X�R�A�ɒl�𑫂��������ꍇ
			if (m_nTotalScore <= m_nTotalScoreDisp)
			{
				m_nTotalScoreDisp = m_nTotalScore;	// �l�����킹��
				m_pUIMng->StopSE(CUIStageManager::SE_ADD_SCORE);
			}
			m_nToScoreAddCnt = 0;
			
		}
	}
}


/* ========================================
	�R���{���{���Z�b�g�֐�
	-------------------------------------
	���e�F�R���{���ɉ����Ĕ{�����Z�b�g����
	-------------------------------------
	����1�F�X�R�A���Z�z��̓Y����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CTotalScore::SetCombScoreMult(int num)
{
	int comboCnt	= m_AddScore[num].nComboCnt;	// �R���{�����Z�b�g(���₷���d��)
	float fMult		= 1.0f;							// ���Z�X�R�A�l�Ɋ|����{��(�f�t�H���g��1.0f)

	// �R���{����1�`9
	if (comboCnt < COMBO_MULTI_MAX_NUM)
	{
		fMult = COMBO_MULTI_NUM[comboCnt];				// �ݒ肵���R���{���ɂ��{�����Z�b�g����
	}
	// �R���{����10�ȏ�̏ꍇ
	else
	{
		fMult = COMBO_MULTI_NUM[COMBO_MULTI_MAX_NUM];	// �{���͌Œ�
	}

	m_AddScore[num].fCombScoreMult = fMult;	// �R���{���Z�X�R�A�{���Z�b�g
}

