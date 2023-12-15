/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X�e�[�W3����
	---------------------------------------
	Stage3.cpp

	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/11/16 ���� takagi
	�E2023/12/12 Stage1�̓��e���R�s�[ yamashita
	�E2023/12/14 BGM�̊Ǘ���SceneManager�Ɉړ� yamashita

========================================== */

// =============== �C���N���[�h ===================
#include "Stage3.h"	//���g�̃w�b�_
#include "CameraChase.h"
#include "HitStop.h"	//�q�b�g�X�g�b�v


/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CStage3::CStage3()
{
	m_pFloor->SetFloorModel(CFloor::StageKinds::Stage3);
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
CStage3::~CStage3()
{
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
void CStage3::Update()
{
	if (!m_bStart)	// �V�[���J�ڌ�Q�[�����J�n���邩����
	{
		// �^�C�g������J�ڌシ���Q�[���J�n�ɂȂ�Ȃ��悤�ɂ��鏈��
		m_nNum++;

		if (m_nNum > TIME_WAIT_START)	// �t�F�[�h�I���܂ő҂��č��}�Đ�
		{
			m_bStartSign = true;
		}

		if (m_bStartSign)	// �t�F�[�h���I��������A�j���[�V�����Đ��J�n
		{
			m_nCntSwitch++;
		}

		if (m_nCntSwitch > 1)	// ���̊Ԋu�Ő؂�ւ���
		{
			m_nCntSwitch = 0;		// �J�E���g��������

			m_fUVPos.x = (STARTSIGN_UV_POS_X)* m_nCntW;		// ��������UV���W�v�Z
			m_fUVPos.y = (STARTSIGN_UV_POS_Y)* m_nCntH;		// �c������UV���W�v�Z

			++m_nCntW;		// �������ɍ��W��1�i�߂�
			if (m_nCntW == STARTSIGN_UV_NUM_X)	// �e�N�X�`���̉E�[�܂ōs������ 
			{
				m_nCntW = 0;	// �J�E���g��������
				++m_nCntH;		// �c��1�i�߂�
			}

			if (m_nCntH == STARTSIGN_UV_NUM_Y)		// �e�N�X�`���̉��[�܂ōs������
			{
				m_nCntH = 0;	// �J�E���g��������
				m_nCntW = 0;
				m_bStart = true;	// �A�j���[�V�����Đ���OFF
			}
		}
	}
	else
	{
		// �J�����X�V
		m_pCamera->Update();

		//�|�[�Y�X�V
#if USE_PAUSE
		if (m_pPause)	//�k���`�F�b�N
		{
			m_pPause->Update();	//�|�[�Y�X�V
			if (m_pPause->IsPause())	//�|�[�Y��
			{
				return;	//�������f
			}
			m_bFinish = m_pPause->IsFin();	//�I������
		}
#endif

		// =============== �q�b�g�X�g�b�v���� ===================
		if (!CHitStop::IsStop())	//�q�b�g�X�g�b�v���������Ȃ�
		{
			// �v���C���[�X�V
			m_pPlayer->Update();	//���J�����X�V��

			// �X���C���}�l�[�W���[�X�V
			m_pSlimeMng->Update(m_pExplosionMng);
		}

		m_pFloor->Update();				// ���X�V
		m_pExplosionMng->Update();		// �����}�l�[�W���[�X�V
		m_pHealItemMng->Update();		// �񕜃A�C�e���X�V
		m_pUIStageManager->Update();	// UI�}�l�[�W���[�X�V
		PlayerHealItemCollision();		// �񕜃A�C�e����锻��
		Collision();					// �����蔻��X�V


	}

#if USE_FADE_GAME
	m_pFade->Update();
#endif

#if SCENE_TRANSITION
	if (m_pUIStageManager->GetStageFinish()->GetDispFlg())
	{
		if (IsKeyTrigger(VK_RETURN) || IsKeyTriggerController(BUTTON_A))
		{
			m_bFinish = true;	// �^�C�g���V�[���I���t���OON
		}
	}
#else
	if (m_pUIStageManager->GetStageFinish()->GetDeleteDispFlg())
	{
		// =============== �t���O�Ǘ� =====================
		m_bFinish = true;	// �^�C�g���V�[���I���t���OON

		// =============== �ޔ� =====================
		m_Data.nTotalScore = m_pUIStageManager->GetTotalScore();			//�X�R�A�ޔ�
		m_Data.nAliveTime = m_pUIStageManager->GetTimer()->GetErapsedTime();	//�o�ߎ��ԑޔ�
		if (m_pSlimeMng)	//�k���`�F�b�N
		{
			m_Data.nKill = m_pSlimeMng->GetKillCnt();						//�������ޔ�
		}
	}
#endif
}

/* ========================================
	�`��֐�
	----------------------------------------
	���e�F�`�揈��
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
//!memo(����������ā[)�Fconst���ז��ɂȂ�����O���Ă�(.h�̕���)
void CStage3::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
	DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
	SetRenderTargets(1, &pRTV, pDSV);		//DSV��null����2D�\���ɂȂ�

	// �X�^�[�g���}�`��
	if (!m_bStart)
	{
		DirectX::XMFLOAT4X4 mat[2];

		// ���[���h�s���X��Y�݂̂��l�����č쐬
		DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(START_POS_X, START_POS_Y, 0.0f);	// ���[���h�s��i�K�v�ɉ����ĕϐ��𑝂₵����A�����������L�q�����肷��j
		DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

		// �r���[�s���2D���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��
		DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());


		// �X�v���C�g�̐ݒ�
		Sprite::SetWorld(mat[0]);
		Sprite::SetView(mat[1]);
		if (m_pCamera)	//�k���`�F�b�N
		{
			Sprite::SetProjection(m_pCamera->GetProjectionMatrix(CCamera::E_DRAW_TYPE_2D));	// ���s���e�s���ݒ�
		}
		Sprite::SetSize(DirectX::XMFLOAT2(START_SCALE_X, START_SCALE_Y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(m_fUVPos.x, m_fUVPos.y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(STARTSIGN_UV_POS_X, STARTSIGN_UV_POS_Y));
		Sprite::SetTexture(m_pTexture);
		Sprite::Draw();
	}

	//���̕`��
	m_pFloor->Draw();

	// �X���C���}�l�[�W���[�`��
	m_pSlimeMng->Draw();

	// �v���C���[�`��
	m_pPlayer->Draw();

	LibEffekseer::Draw();

	//�����}�l�[�W���[�`��
	m_pExplosionMng->Draw();

	//�񕜃A�C�e���`��
	m_pHealItemMng->Draw();

	//2D�`��ϊ�
	SetRenderTargets(1, &pRTV, nullptr);

	//UI�}�l�[�W���[�`��
	m_pUIStageManager->Draw();

#if USE_FADE_GAME
	m_pFade->Draw();
#endif
#if USE_PAUSE
	if (m_pPause)
	{
		m_pPause->Draw();
	}
#endif
}

/* ========================================
	��ރQ�b�^
	----------------------------------------
	���e�F���g���X�e�[�W3�ł��邱�Ƃ�����
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F���g�̎��
=========================================== */
CStage3::E_TYPE CStage3::GetType() const
{
	// =============== �� ===================
	return CStage3::E_TYPE_STAGE3;	//���g�̎��
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
CStage3::E_TYPE CStage3::GetNext() const
{
	// =============== �� ===================
	return CStage3::E_TYPE_RESULT;	//�J�ڐ�V�[���̎��
}