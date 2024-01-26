/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X�e�[�W�Z���N�g����
	---------------------------------------
	SelectStage.cpp

	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/11/16 ���� takagi
	�E2023/12/12 �X�e�[�W�Z���N�g��ǉ��@yamamoto
	�E2024/01/26 �g�k���� takagi
	�E2024/01/26 �I���A����SE�ǉ� suzumura

========================================== */

// =============== �C���N���[�h ===================
#include "SelectStage.h"	//���g�̃w�b�_
#include "Input.h"
#include "GameParameter.h"
#define _USE_MATH_DEFINES	//math.h�̒�`�g�p
#include <math.h>			//M_PI�g�p
#include <algorithm>		//clamp�g�p
// =============== �萔��` =======================
const float TEXTURE_SELECT_STAGE_POSX = 900.0f;
const float TEXTURE_SELECT_STAGE_POSY = 300.0f;
const float TEXTURE_SELECT_STAGE_WIDTH = 400.0f;
const float TEXTURE_SELECT_STAGE_HEIGHT =500.0f;

/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CSelectStage::CSelectStage()
	: m_pStageSelectBG(nullptr)
	, m_pStageSelectUI(nullptr)
	, m_nSelectNum(0)
	, m_bStickFlg(false)
	, m_pFrameCnt(nullptr)	//�t���[���J�E���^
	,m_bCntUpDwn(false)	//�J�E���g�A�b�v�E�_�E��
	, m_pSE{ nullptr,nullptr }
	, m_pSESpeaker{ nullptr ,nullptr }
{
	mStageNum[0].Type = E_TYPE_STAGE1;
	mStageNum[0].m_pTexture= new Texture();
	if (FAILED(mStageNum[0].m_pTexture->Create("Assets/Texture/StageSelect/tehaisyo1.png")))
	{
		MessageBox(NULL, "Title gamstart.png", "Error", MB_OK);
	}

	mStageNum[1].Type = E_TYPE_STAGE2;
	mStageNum[1].m_pTexture = new Texture();
	if (FAILED(mStageNum[1].m_pTexture->Create("Assets/Texture/StageSelect/tehaisyo2.png")))
	{
		MessageBox(NULL, "Title gamstart.png", "Error", MB_OK);
	}
	mStageNum[2].Type = E_TYPE_STAGE3;
	mStageNum[2].m_pTexture = new Texture();
	if (FAILED(mStageNum[2].m_pTexture->Create("Assets/Texture/StageSelect/tehaisyo3.png")))
	{
		MessageBox(NULL, "Title gamstart.png", "Error", MB_OK);
	}

	for (int i = 0; i < 5; i++)
	{
		m_2dObj[i] = new C2dPolygon();
		m_2dObj[i]->SetCamera(m_pCamera);					//�J�����Z�b�^
	}
	m_pStageSelectBG= new Texture();
	if (FAILED(m_pStageSelectBG->Create("Assets/Texture/StageSelect/StageSelectBG.png")))
	{
		MessageBox(NULL, "Title gamstart.png", "Error", MB_OK);
	}
	m_pStageSelectUI = new Texture();
	if (FAILED(m_pStageSelectUI->Create("Assets/Texture/StageSelect/stselectUI.png")))
	{
		MessageBox(NULL, "Title gamstart.png", "Error", MB_OK);
	}

	m_2dObj[0]->SetPos({ 250.0f, 300.0f,1.0f });
	m_2dObj[0]->SetRotate({ 0.0f,0.0f,-0.25f });
	m_2dObj[1]->SetPos({ 600.0f, 300.0f,1.0f });
	m_2dObj[1]->SetRotate({ 0.0f,0.0f,0.05f });
	m_2dObj[2]->SetPos({ 950.0f, 300.0f,1.0f });
	m_2dObj[2]->SetRotate({ 0.0f,0.0f,0.1f });
	m_2dObj[0]->SetSize({ TEXTURE_SELECT_STAGE_WIDTH, TEXTURE_SELECT_STAGE_HEIGHT ,1.0f });
	m_2dObj[1]->SetSize({ TEXTURE_SELECT_STAGE_WIDTH, TEXTURE_SELECT_STAGE_HEIGHT ,1.0f });
	m_2dObj[2]->SetSize({ TEXTURE_SELECT_STAGE_WIDTH, TEXTURE_SELECT_STAGE_HEIGHT ,1.0f });

	// =============== ���I�m�� =====================
	m_pFrameCnt = new CFrameCnt(CHANGE_SCALE_HALF_TIME, m_bCntUpDwn);	//�t���[��������

	//=== �T�E���h�t�@�C���ǂݍ��� =====
	LoadSound();	

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
CSelectStage::~CSelectStage()
{
	// �j������
	for (int i = 0; i >= SUTAGE_NUM; ++i)
	{
		SAFE_DELETE(mStageNum[i].m_pTexture);
	}
	SAFE_DELETE(m_pStageSelectBG);
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
void CSelectStage::Update()
{
	Select();
}

/* ========================================
	�`��֐�
	----------------------------------------
	���e�F�`�揈��
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
	======================================== */
	//!memo(����������ā[)�Fconst���ז��ɂȂ�����O���Ă�(.h�̕���)
void CSelectStage::Draw() //const
{
	//�w�i
	m_2dObj[3]->SetTexture(m_pStageSelectBG);
	m_2dObj[3]->SetPos({ SCREEN_WIDTH/2, SCREEN_HEIGHT/2 ,1.0f });
	m_2dObj[3]->SetSize({ SCREEN_WIDTH, SCREEN_HEIGHT ,1.0f });
	m_2dObj[3]->Draw();
	


	if (!(0 == m_nSelectNum))
	{//�X�e�[�W1
		m_2dObj[0]->SetTexture(mStageNum[0].m_pTexture);
		m_2dObj[0]->SetPos({ 250.0f, 300.0f,1.0f });
		m_2dObj[0]->SetSize({ TEXTURE_SELECT_STAGE_WIDTH, TEXTURE_SELECT_STAGE_HEIGHT ,1.0f });
		m_2dObj[0]->SetRotate({ 0.0f,0.0f,-0.25f });
		m_2dObj[0]->SetColor(0.5f, 1.0f);
		m_2dObj[0]->Draw();
	}
	if (!(1 == m_nSelectNum))
	{
		//�X�e�[�W2
		m_2dObj[1]->SetTexture(mStageNum[1].m_pTexture);
		m_2dObj[1]->SetPos({ 600.0f, 300.0f,1.0f });
		m_2dObj[1]->SetSize({ TEXTURE_SELECT_STAGE_WIDTH , TEXTURE_SELECT_STAGE_HEIGHT   ,1.0f });
		m_2dObj[1]->SetRotate({ 0.0f,0.0f,0.05f });
		m_2dObj[1]->SetColor(0.5f, 1.0f);
		m_2dObj[1]->Draw();
	}
	if (!(2 == m_nSelectNum))
	{
		//�X�e�[�W3
		m_2dObj[2]->SetTexture(mStageNum[2].m_pTexture);
		m_2dObj[2]->SetPos({ 950.0f, 300.0f,1.0f });
		m_2dObj[2]->SetSize({ TEXTURE_SELECT_STAGE_WIDTH , TEXTURE_SELECT_STAGE_HEIGHT   ,1.0f });
		m_2dObj[2]->SetRotate({ 0.0f,0.0f,0.1f });
		m_2dObj[2]->SetColor(0.5f, 1.0f);
		m_2dObj[2]->Draw();
	}


	// =============== �ϐ��錾 =====================
	float fSize = MIN_SIZE_ARR_LET;	//�傫��

	if (m_pFrameCnt)	//�k���`�F�b�N
	{
		m_pFrameCnt->Count();	//�J�E���g�i�s
		fSize = -(cosf(static_cast<float>(M_PI) * m_pFrameCnt->GetRate()) - 1.0f) / 2.0f * (MAX_SIZE_ARR_LET - MIN_SIZE_ARR_LET) + MIN_SIZE_ARR_LET;	//�C�[�W���O���g�����傫���ύX
		if (m_pFrameCnt->IsFin())	//�J�E���g����
		{
			m_bCntUpDwn ^= 1;													//�J�E���g�A�b�v�_�E���t�]
			SAFE_DELETE(m_pFrameCnt);											//�J�E���^�폜
			m_pFrameCnt = new CFrameCnt(CHANGE_SCALE_HALF_TIME, m_bCntUpDwn);	//�J�E���g�A�b�v�E�_�E��
		}
	}

	m_2dObj[m_nSelectNum]->SetTexture(mStageNum[m_nSelectNum].m_pTexture);
	m_2dObj[m_nSelectNum]->SetColor(1.0f, 1.0f);
	m_2dObj[m_nSelectNum]->SetSize({ fSize * TEXTURE_SELECT_STAGE_WIDTH / TEXTURE_SELECT_STAGE_HEIGHT, fSize, 1.0f });	//�g�k
	m_2dObj[m_nSelectNum]->Draw();

	//for (int i = SUTAGE_NUM-1; i > 0-1; i--)
	//{
	//	if (i == m_nSelectNum) continue;
	//	m_2dObj[i]->SetTexture(mStageNum[i].m_pTexture);
	//	m_2dObj[i]->SetPos({ TEXTURE_SELECT_STAGE_POSX + i * 100,TEXTURE_SELECT_STAGE_POSY-i*70,1.0f });
	//	m_2dObj[i]->SetSize({ TEXTURE_SELECT_STAGE_WIDTH, TEXTURE_SELECT_STAGE_HEIGHT ,1.0f});
	//	m_2dObj[i]->SetRotate({ 0.0f,0.0f,-0.3f });
	//	m_2dObj[i]->Draw();
	//}
	//����
	m_2dObj[4]->SetTexture(m_pStageSelectUI);
	m_2dObj[4]->SetPos({ 640.0f, 660.0f  ,1.0f });
	m_2dObj[4]->SetSize({ SCREEN_WIDTH, 120.0f ,1.0f });
	m_2dObj[4]->Draw();
}
/* ========================================
	�X�e�[�W��I������֐�
	----------------------------------------
	���e�F�X�e�[�W��I������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
	======================================== */
void CSelectStage::Select()
{
	// �Q�[���R���g���[���[
	if (GetUseVController())
	{
		TPos3d<float> fMoveInput;	// �X�e�B�b�N�̓��͒l������ϐ�
		fMoveInput.x = IsStickLeft().x;// �R���g���[���[�̍��X�e�B�b�N�̌X�����擾

		// ���X�e�B�b�N��|���Ă���
		if (!m_bStickFlg)
		{
			// �X�e�B�b�N��
			if (fMoveInput.x < 0.0f)
			{
				m_nSelectNum -= 1;
				if (m_nSelectNum < 0) m_nSelectNum = 0;
				m_bStickFlg = true;

				//===== SE�̍Đ� =======
				PlaySE(SE_CHOOSE);
			}
			// �X�e�B�b�N�E
			else if ( 0.0f < fMoveInput.x )
			{
				m_nSelectNum += 1;
				if (m_nSelectNum > 2)m_nSelectNum = 2;
				m_bStickFlg = true;

				//===== SE�̍Đ� =======
				PlaySE(SE_CHOOSE);
			}
		}
		// ���X�e�B�b�N���j���[�g����
		else
		{
			if (fabs(fMoveInput.x) <= 0.5f )
			{
				m_bStickFlg = false;
			}
		}
	}
	//�L�[�{�[�h����
	if (IsKeyTrigger('A')) {
		m_nSelectNum -= 1;
		if (m_nSelectNum < 0) m_nSelectNum = 0;
		//===== SE�̍Đ� =======
		PlaySE(SE_CHOOSE);
	}
	if (IsKeyTrigger('D')) {
		m_nSelectNum += 1;
		if (m_nSelectNum > 2)m_nSelectNum = 2;
		//===== SE�̍Đ� =======
		PlaySE(SE_CHOOSE);
	}

	if (IsKeyTrigger(VK_SPACE) || IsKeyTriggerController(BUTTON_B))
	{
		m_bFinish = true;	// �^�C�g���V�[���I���t���OON
		//===== SE�̍Đ� =======
		PlaySE(SE_DECISION);
	}
}

/* ========================================
	��ރQ�b�^
	----------------------------------------
	���e�F���g���X�e�[�W�Z���N�g�ł��邱�Ƃ�����
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F���g�̎��
=========================================== */
CSelectStage::E_TYPE CSelectStage::GetType() const
{
	// =============== �� ===================
	return CSelectStage::E_TYPE_SELECT_STAGE;	//���g�̎��
}

/* ========================================
	���V�[���Q�b�^
	----------------------------------------
	���e�F�J�ڂ������V�[��������������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�J�ڐ�V�[���̎��
=========================================== */
CSelectStage::E_TYPE CSelectStage::GetNext() const
{
	// =============== �� ===================
	//return CSelectStage::E_TYPE_STAGE1;	//�J�ڐ�V�[���̎��
	return mStageNum[m_nSelectNum].Type;	//�J�ڐ�V�[���̎��
}

/* ========================================
   �Z���N�g�X�e�[�W�pSE�ǂݍ��݊֐�
   ----------------------------------------
   ���e�F�Z���N�g�X�e�[�W�p��SE�̃t�@�C����ǂݍ���
   ----------------------------------------
   �����F����
   ----------------------------------------
   �ߒl�F����
======================================== */
void CSelectStage::LoadSound()
{
	//SE�̓ǂݍ���
	for (int i = 0; i < SE_MAX; i++)
	{
		m_pSE[i] = CSound::LoadSound(m_sSEFile[i].c_str());
		if (!m_pSE[i])
		{
			MessageBox(NULL, m_sSEFile[i].c_str(), "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
		}
	}
}

/* ========================================
	SE�̍Đ��֐�
	----------------------------------------
	���e�FSE�̍Đ�
	----------------------------------------
	����1�FSE�̎��(enum)
	����2�F����
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CSelectStage::PlaySE(SE se, float volume)
{
	m_pSESpeaker[se] = CSound::PlaySound(m_pSE[se]);	//SE�Đ�
	m_pSESpeaker[se]->SetVolume(volume);				//���ʂ̐ݒ�
}