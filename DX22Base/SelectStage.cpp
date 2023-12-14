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
========================================== */

// =============== �C���N���[�h ===================
#include "SelectStage.h"	//���g�̃w�b�_
#include "Input.h"
#include "GameParameter.h"
// =============== �萔��` =======================
const float TEXTURE_SELECT_STAGE_POSX = 900.0f;
const float TEXTURE_SELECT_STAGE_POSY = 400.0f;
const float TEXTURE_SELECT_STAGE_WIDTH = 900.0f;
const float TEXTURE_SELECT_STAGE_HEIGHT = 700.0f;

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
{
	mStageNum[0].Type = E_TYPE_STAGE1;
	mStageNum[0].m_pTexture= new Texture();
	if (FAILED(mStageNum[0].m_pTexture->Create("Assets/Texture/tehaisyo1.png")))
	{
		MessageBox(NULL, "Title gamstart.png", "Error", MB_OK);
	}

	mStageNum[1].Type = E_TYPE_STAGE2;
	mStageNum[1].m_pTexture = new Texture();
	if (FAILED(mStageNum[1].m_pTexture->Create("Assets/Texture/tehaisyo2.png")))
	{
		MessageBox(NULL, "Title gamstart.png", "Error", MB_OK);
	}
	mStageNum[2].Type = E_TYPE_STAGE3;
	mStageNum[2].m_pTexture = new Texture();
	if (FAILED(mStageNum[2].m_pTexture->Create("Assets/Texture/tehaisyo3.png")))
	{
		MessageBox(NULL, "Title gamstart.png", "Error", MB_OK);
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
CSelectStage::~CSelectStage()
{
	// �j������
	for (int i = 0; i >= SUTAGE_NUM; ++i)
	{
		SAFE_DELETE(mStageNum[i].m_pTexture);
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
	for (int i = SUTAGE_NUM-1; i > 0-1; i--)
	{
		Draw2d(TEXTURE_SELECT_STAGE_POSX+i*100
			, TEXTURE_SELECT_STAGE_POSY + i * 70
			, TEXTURE_SELECT_STAGE_WIDTH
			, TEXTURE_SELECT_STAGE_HEIGHT
			, mStageNum[i].m_pTexture);
	}
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
	if (IsKeyTrigger('A'))
	{
		EscapeStageNum = mStageNum[2];
		mStageNum[2] = mStageNum[1];
		mStageNum[1] = mStageNum[0];
		mStageNum[0] = EscapeStageNum;
	}
	if (IsKeyTrigger('D'))
	{
		EscapeStageNum = mStageNum[0];
		mStageNum[0] = mStageNum[1];
		mStageNum[1] = mStageNum[2];
		mStageNum[2] = EscapeStageNum;
	}
	TPos3d<float> fMoveInput;	// �X�e�B�b�N�̓��͒l������ϐ�

	if (GetUseVController())
	{// �R���g���[���[�̍��X�e�B�b�N�̌X�����擾
		fMoveInput.x = IsStickLeft().x;
		//fMoveInput.z = IsStickLeft().y * -1;	// �㉺�t(�����|1)
		if (fMoveInput.x < 0.0f)
		{
			EscapeStageNum = mStageNum[2];
			mStageNum[2] = mStageNum[1];
			mStageNum[1] = mStageNum[0];
			mStageNum[0] = EscapeStageNum;
		}
		if (fMoveInput.x > 0.0f)
		{
			EscapeStageNum = mStageNum[0];
			mStageNum[0] = mStageNum[1];
			mStageNum[1] = mStageNum[2];
			mStageNum[2] = EscapeStageNum;
		}
	}
	if (IsKeyTrigger(VK_SPACE) || IsKeyTriggerController(BUTTON_B))
	{
		m_bFinish = true;	// �^�C�g���V�[���I���t���OON
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
	return mStageNum[0].Type;	//�J�ڐ�V�[���̎��
}