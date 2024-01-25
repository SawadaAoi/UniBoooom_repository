/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X�e�[�W�Z���N�g����
	---------------------------------------
	SelectStage.cpp
	---------------------------------------
	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/11/16 ���� takagi
	�E2023/12/12 �X�e�[�W�Z���N�g��ǉ��@yamamoto
	�E2024/01/20 ���t�@�N�^�����O takagi
	�E2024/01/21 �R�����g���C�EMessageBox���P takagi

========================================== */

// =============== �C���N���[�h ===================
#include "SelectStage.h"	//���g�̃w�b�_
#include "Input.h"
#include "GameParameter.h"
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
	,Num(0)
{
	mStageNum[0].Type = E_TYPE_STAGE1;
	mStageNum[0].m_pTexture= new Texture();
	if (FAILED(mStageNum[0].m_pTexture->Create("Assets/Texture/StageSelect/tehaisyo1.png")))
	{
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error�F";	//�G���[�ӏ�
		MessageBox(nullptr, (ErrorSpot + "tehaisyo1.png�ǂݍ��ݎ��s").c_str(), "Error", MB_OK | MB_ICONERROR);						//�G���[�ʒm
#endif
	}

	mStageNum[1].Type = E_TYPE_STAGE2;
	mStageNum[1].m_pTexture = new Texture();
	if (FAILED(mStageNum[1].m_pTexture->Create("Assets/Texture/StageSelect/tehaisyo2.png")))
	{
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error�F";	//�G���[�ӏ�
		MessageBox(nullptr, (ErrorSpot + "tehaisyo2.png�ǂݍ��ݎ��s").c_str(), "Error", MB_OK | MB_ICONERROR);						//�G���[�ʒm
#endif
	}
	mStageNum[2].Type = E_TYPE_STAGE3;
	mStageNum[2].m_pTexture = new Texture();
	if (FAILED(mStageNum[2].m_pTexture->Create("Assets/Texture/StageSelect/tehaisyo3.png")))
	{
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error�F";	//�G���[�ӏ�
		MessageBox(nullptr, (ErrorSpot + "tehaisyo3.png�ǂݍ��ݎ��s").c_str(), "Error", MB_OK | MB_ICONERROR);						//�G���[�ʒm
#endif
	}

	for (int i = 0; i < 5; i++)
	{
		m_2dObj[i] = new C2dObject();
		m_2dObj[i]->SetCamera(m_pCamera);					//�J�����Z�b�^
	}
	m_pStageSelectBG= new Texture();
	if (FAILED(m_pStageSelectBG->Create("Assets/Texture/StageSelect/StageSelectBG.png")))
	{
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error�F";	//�G���[�ӏ�
		MessageBox(nullptr, (ErrorSpot + "StageSelectBG.png�ǂݍ��ݎ��s").c_str(), "Error", MB_OK | MB_ICONERROR);						//�G���[�ʒm
#endif
	}
	m_pStageSelectUI = new Texture();
	if (FAILED(m_pStageSelectUI->Create("Assets/Texture/StageSelect/stselectUI.png")))
	{
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error�F";	//�G���[�ӏ�
		MessageBox(nullptr, (ErrorSpot + "stselectUI.png�ǂݍ��ݎ��s").c_str(), "Error", MB_OK | MB_ICONERROR);						//�G���[�ʒm
#endif
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
	// =============== ���͎�t ===================
	//if (!(m_ucFlag.Check(E_FLAG_TIDYING_UP)))	//�Еt�����łȂ�
	//{
		// =============== �R���g���[�� ==================
		if (GetUseVController())	// �R���g���[�����ڑ�����Ă���ꍇ
		{
			// =============== �J�[�\���ړ� ===================
			if (IsStickLeft().x < 0)		//�����͎�
			{
				Num += 1;
				if (Num > 2)Num = 2;
			}
			if (IsStickLeft().x > 0)	//�����͎�
			{
				Num -= 1;
				if (Num < 0) Num = 0;
			}

			// =============== ���� ===================
			if (IsKeyTriggerController(BUTTON_B))	//B�{�^�����͎�
			{
				// =============== �t���O���� ===================
				m_bFinish = true;	//�V�[���I��
			}
		}
		else
		{
			//// =============== �J�[�\���ړ� ===================
			//if (IsKeyTrigger(VK_UP) || IsKeyTrigger('W'))		//���EW���͎�
			//{
			//	// =============== ��ԑJ�� ===================
			//	if (m_p2dObject.find(E_2D_START) != m_p2dObject.end() && m_p2dObject.at(E_2D_START)
			//		&& typeid(CCommandTitle) == typeid(*m_p2dObject.at(E_2D_START)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
			//	{
			//		if (static_cast<CCommandTitle*>(m_p2dObject[E_2D_START])->ChackUpdate())	//�\����
			//		{
			//			static_cast<CCommandTitle*>(m_p2dObject[E_2D_START])->Selected();		//�I����ԑJ��
			//			m_ucFlag.Up(E_FLAG_COMMAND_CONTINUE);								//��̃R�}���h�̗p
			//		}
			//	}
			//	if (m_p2dObject.find(E_2D_FINISH) != m_p2dObject.end() && m_p2dObject.at(E_2D_FINISH)
			//		&& typeid(CCommandTitle) == typeid(*m_p2dObject.at(E_2D_FINISH)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
			//	{
			//		if (static_cast<CCommandTitle*>(m_p2dObject[E_2D_FINISH])->ChackUpdate())	//�\����
			//		{
			//			static_cast<CCommandTitle*>(m_p2dObject[E_2D_FINISH])->UnSelected();	//�I����ԑJ��
			//			m_ucFlag.Down(E_FLAG_COMMAND_FINISH);								//���̃R�}���h�s�̗p
			//		}
			//	}
			//}
			//if (IsKeyTrigger(VK_DOWN) || IsKeyTrigger('S'))	//���ES���͎�
			//{
			//	// =============== ��ԑJ�� ===================
			//	if (m_p2dObject.find(E_2D_FINISH) != m_p2dObject.end() && m_p2dObject.at(E_2D_FINISH)
			//		&& typeid(CCommandTitle) == typeid(*m_p2dObject.at(E_2D_FINISH)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
			//	{
			//		if (static_cast<CCommandTitle*>(m_p2dObject[E_2D_FINISH])->ChackUpdate())	//�\����
			//		{
			//			static_cast<CCommandTitle*>(m_p2dObject[E_2D_FINISH])->Selected();	//�I����ԑJ��
			//			m_ucFlag.Up(E_FLAG_COMMAND_FINISH);									//���̃R�}���h�̗p
			//		}
			//	}
			//	if (m_p2dObject.find(E_2D_START) != m_p2dObject.end() && m_p2dObject.at(E_2D_START)
			//		&& typeid(CCommandTitle) == typeid(*m_p2dObject.at(E_2D_START)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
			//	{
			//		if (static_cast<CCommandTitle*>(m_p2dObject[E_2D_START])->ChackUpdate())	//�\����
			//		{
			//			static_cast<CCommandTitle*>(m_p2dObject[E_2D_START])->UnSelected();	//�I����ԑJ��
			//			m_ucFlag.Down(E_FLAG_COMMAND_CONTINUE);								//��̃R�}���h�s�̗p
			//		}
			//	}
			//}

			// =============== ���� ===================
			if (IsKeyTrigger(VK_RETURN) || IsKeyTrigger(VK_SPACE))	//Enter�ESpace���͎�
			{
				// =============== �t���O���� ===================
				m_bFinish = true;	//�V�[���I��
			}		
		}
	//}


	//�w�i
		m_2dObj[3]->SetTexture(m_pStageSelectBG);
		m_2dObj[3]->SetPos({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 ,1.0f });
		m_2dObj[3]->SetSize({ SCREEN_WIDTH, SCREEN_HEIGHT ,1.0f });
		m_2dObj[3]->Update();



		if (!(0 == Num))
		{//�X�e�[�W1
			m_2dObj[0]->SetTexture(mStageNum[0].m_pTexture);
			m_2dObj[0]->SetPos({ 250.0f, 300.0f,1.0f });
			m_2dObj[0]->SetSize({ TEXTURE_SELECT_STAGE_WIDTH, TEXTURE_SELECT_STAGE_HEIGHT ,1.0f });
			m_2dObj[0]->SetRotate({ 0.0f,0.0f,-0.25f });
			m_2dObj[0]->SetColor(0.5f, 1.0f);
			m_2dObj[0]->Update();
		}
		if (!(1 == Num))
		{
			//�X�e�[�W2
			m_2dObj[1]->SetTexture(mStageNum[1].m_pTexture);
			m_2dObj[1]->SetPos({ 600.0f, 300.0f,1.0f });
			m_2dObj[1]->SetSize({ TEXTURE_SELECT_STAGE_WIDTH , TEXTURE_SELECT_STAGE_HEIGHT   ,1.0f });
			m_2dObj[1]->SetRotate({ 0.0f,0.0f,0.05f });
			m_2dObj[1]->SetColor(0.5f, 1.0f);
			m_2dObj[1]->Update();
		}
		if (!(2 == Num))
		{
			//�X�e�[�W3
			m_2dObj[2]->SetTexture(mStageNum[2].m_pTexture);
			m_2dObj[2]->SetPos({ 950.0f, 300.0f,1.0f });
			m_2dObj[2]->SetSize({ TEXTURE_SELECT_STAGE_WIDTH , TEXTURE_SELECT_STAGE_HEIGHT   ,1.0f });
			m_2dObj[2]->SetRotate({ 0.0f,0.0f,0.1f });
			m_2dObj[2]->SetColor(0.5f, 1.0f);
			m_2dObj[2]->Update();
		}

		m_2dObj[Num]->SetTexture(mStageNum[Num].m_pTexture);
		m_2dObj[Num]->SetColor(1.0f, 1.0f);
		m_2dObj[Num]->Update();

		//for (int i = SUTAGE_NUM-1; i > 0-1; i--)
		//{
		//	if (i == Num) continue;
		//	m_2dObj[i]->SetTexture(mStageNum[i].m_pTexture);
		//	m_2dObj[i]->SetPos({ TEXTURE_SELECT_STAGE_POSX + i * 100,TEXTURE_SELECT_STAGE_POSY-i*70,1.0f });
		//	m_2dObj[i]->SetSize({ TEXTURE_SELECT_STAGE_WIDTH, TEXTURE_SELECT_STAGE_HEIGHT ,1.0f});
		//	m_2dObj[i]->SetRotate({ 0.0f,0.0f,-0.3f });
		//	m_2dObj[i]->Update();
		//}
		//����
		m_2dObj[4]->SetTexture(m_pStageSelectUI);
		m_2dObj[4]->SetPos({ 640.0f, 660.0f  ,1.0f });
		m_2dObj[4]->SetSize({ SCREEN_WIDTH, 120.0f ,1.0f });
		m_2dObj[4]->Update();
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
		Num -= 1;
		if (Num < 0) Num = 0;
	//EscapeStageNum = mStageNum[2];
	//mStageNum[2] = mStageNum[1];
	//mStageNum[1] = mStageNum[0];
	//mStageNum[0] = EscapeStageNum;
	}
	if (IsKeyTrigger('D'))
	{
		Num += 1;
		if (Num > 2)Num = 2;
		//EscapeStageNum = mStageNum[0];
		//mStageNum[0] = mStageNum[1];
		//mStageNum[1] = mStageNum[2];
		//mStageNum[2] = EscapeStageNum;
	}
	TPos3d<float> fMoveInput;	// �X�e�B�b�N�̓��͒l������ϐ�

	//if (GetUseVController())
	//{// �R���g���[���[�̍��X�e�B�b�N�̌X�����擾
	//	fMoveInput.x = IsStickLeft().x;
	//	//fMoveInput.z = IsStickLeft().y * -1;	// �㉺�t(�����|1)
	//	if (fMoveInput.x < 0.0f)
	//	{
	//		EscapeStageNum = mStageNum[2];
	//		mStageNum[2] = mStageNum[1];
	//		mStageNum[1] = mStageNum[0];
	//		mStageNum[0] = EscapeStageNum;
	//	}
	//	if (fMoveInput.x > 0.0f)
	//	{
	//		EscapeStageNum = mStageNum[0];
	//		mStageNum[0] = mStageNum[1];
	//		mStageNum[1] = mStageNum[2];
	//		mStageNum[2] = EscapeStageNum;
	//	}
	//}
	if (IsKeyTrigger(VK_SPACE) || IsKeyTriggerController(BUTTON_B))
	{
		m_bFinish = true;	// �^�C�g���V�[���I���t���OON
	}
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
	return mStageNum[Num].Type;	//�J�ڐ�V�[���̎��
}