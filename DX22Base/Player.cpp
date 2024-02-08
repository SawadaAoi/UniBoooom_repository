/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   Player�pcpp
   ---------------------------------------
   Player.cpp

   �쐬��
	�R�{�M��
   �ύX����
	�E2023/11/03 �ړ��쐬 yamamoto
	�E2023/11/06 �����ǉ��A�_���[�W����A�U���J�n�쐬 yamamoto
	�E2023/11/08 �v���C���[�̓����蔻��̑傫���̒萔��ǉ� yamashita
	�E2023/11/08 �U�����͈ړ��ł��Ȃ��悤�ɕύX yamashita
	�E2023/11/09 �J�����Ή� takagi
	�E2023/11/09 GameOver�̕\�� yamashita
	�E2023/11/09 �R���g���[���ړ��̒ǉ� sawada
	�E2023/11/11 parameter�p�w�b�_�ǉ� suzumura
	�E2023/11/11 �v���C���[�̓_�ŏ����ǉ� Tei
	�E2023/11/14 SphereInfo�̕ύX�ɑΉ� Takagi
	�E2023/11/14 �L�[�{�[�h�̓��͈ړ��������e��K�؂Ȍ`�ɕύX Sawada
	�E2023/11/15 Object�N���X���p�������̂ŏC���@yamamoto
	�E2023/11/19 �ړ���SE���Đ� yamashita
	�E2023/11/19 ��_���[�W���ƃn���}�[��U��SE���Đ� yamashita
	�E2023/11/19 �T�E�h�t�@�C���ǂݍ��݊֐����쐬 yamashita
	�E2023/11/23 �W�I���g���[���烂�f���ɍ����ւ� yamashita
	�E2023/11/27 �e�̕`���ǉ� nieda
	�E2023/11/27 Update���n���}�[�U��Ԋu�����ǉ� Tei
	�E2023/11/27 Update���n���}�[�U��Ԋu�����ǉ� Tei
	�E2023/11/28 �_���[�W�����Ɏ󂯂�_���[�W�ʂ�ǉ� Sawada
	�E2023/11/28 �񕜏�����ǉ� yamashita
	�E2023/11/28 �_���[�W�����Ɏ󂯂�_���[�W�ʂ�ǉ� Sawada
	�E2023/11/28 �񕜏�����ǉ� yamashita
	�E2023/11/29 �n���}�[�̃C���^�[�o���ǉ� yamamoto
	�E2023/12/03 �J�����̍X�V��S�����߁A�|�C���^��const���d���Ȃ����� takagi
	�E2023/12/07 �Q�[���p�����[�^����ꕔ�萔�ړ� takagi
	�E2023/12/14 �v���C���[�̃A�j���[�V�������� yamashita
	�E2023/12/14 SE�̕ϐ��𐮗� yamashita
	�E2023/12/15 SE���O����Đ��ł���悤�ɕύX yamashita
	�E2023/01/25 �ҋ@���[�V������ύX takagi
	�E2024/01/26 �x��SE�ǉ� suzumura
	�E2024/01/28 ���S���[�V�����ǉ� Sawada
	�E2024/01/28 �v���C���[���X���ăJ��������悭������悤�ɕύX Yamashita
	�E2024/01/30 �v���C���[�ړ��G�t�F�N�g�p�����ǉ� Tei
	�E2024/02/02 ���G�t�F�N�g�����ǉ� Tei
	�E2024/02/08 ���G�t�F�N�g�����C��&&�n���}�[�̐U�鑬�x�����łɏC�� sawada

======================================== */

// =============== �C���N���[�h ===================
#include "Player.h"
#include "Input.h"
#include "Sphere.h"
#include "GameParameter.h"		//�萔��`�p�w�b�_�[
#include "ShaderList.h"

// =============== �萔��` =======================
const float KEYBOARD_INPUT_SIZE = 1.0f;						// �L�[�{�[�h�̓��͒l�̑傫��
#if MODE_GAME_PARAMETER
#else
const float PLAYER_MOVE_SPEED = 0.1f;			//�v���C���[�̈ړ���
const int	PLAYER_HP = 5;
const float PLAYER_RADIUS = 0.3f;			// �v���C���[�̓����蔻��̑傫��
const float PLAYER_SIZE = 1.0f;			// �v���C���[�̑傫��
const int	NO_DAMAGE_TIME = 3 * 60;		//�v���C���[�̖��G����
const int	DAMAGE_FLASH_FRAME = 0.1f * 60;	// �v���C���[�̃_���[�W�_�ł̐؂�ւ��Ԋu
const float PLAYER_ROTATE_X_NORMAL = DirectX::XMConvertToRadians(30.0f);	// �v���C���[�̌X��
#endif
const int	HEAL_NUM = 2;									// �v���C���[�̉񕜗�
const float HAMMER_INTERVAL_TIME = 0.0f * 60;				// �n���}�[�U��Ԋu
const float PLAYER_SHADOW_SCALE = 2.5f;						// �v���C���[�̉e�̑傫��
const int	SE_RUN_INTERVAL = static_cast<int>(0.4f * 60);	// �v���C���[�̈ړ��ɂ��SE�����̊Ԋu
const float	SE_RUN_VOLUME = 0.3f;							// �ړ��ɂ��SE�̉���
const float PLAYER_MOVE_ANIME_SPEED = 1.2f;					// �v���C���[�̈ړ��A�j���[�V�����Đ����x
const float PLAYER_SWING_ANIME_SPEED = 5.0f;				// �v���C���[�̈ړ��A�j���[�V�����Đ����x
const float	ADD_ANIM_FRAME = 1.0f / 60.0f;
const int   PLAYER_WARNING_HP = 1;							//�m���̌x�����s���v���C���[�c��HP

const int	SWING_FAST_INTERVAL = 0.1f * 60;				// �n���}�[��U�鑬�x�𑁂�����Ԋu

const int	WALK_EFFECT_INTERVAL = 0.2f * 60;				// �����G�t�F�N�g�̏o���Ԋu
const int	SWEAT_EFFECT_INTERVAL = 0.5f * 60;				// ���G�t�F�N�g�̏o���Ԋu
const float	SWEAT_EFFECT_DISP_SPEED = 0.5f;					// ���G�t�F�N�g�̕\������n���}�[�̃X�s�[�h(����ȉ��̏ꍇ�ɕ\��)
const int	DIE_AFTER_INTERVAL = int(2.0f * 60);			// ���S���Ă���GameOver�e�L�X�g���o��܂ł̗P�\����



/* ========================================
   �֐��F�R���X�g���N�^
   ----------------------------------------
   ���e�F�������ɍs������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
CPlayer::CPlayer()
	: m_pHammer(nullptr)
	, m_bAttackFlg(false)
	, m_nHp(PLAYER_HP)		// �v���C���[��HP������
	, m_bDieFlg(false)
	, m_pCamera(nullptr)
	, m_nSafeTimeCnt(0)
	, m_bSafeTimeFlg(false)
	, m_DrawFlg(true)
	, m_FlashCnt(0)
	, m_pSE{ nullptr,nullptr ,nullptr }
	, m_pSESpeaker{ nullptr ,nullptr, nullptr }
	, m_nWalkSECnt(0)
	, m_bHumInvFlg(false)
	, m_fHumInvCnt(0.0f)
	, m_pWaitFrameCnt(nullptr)
	, m_bDieInvFlg(false)
	, m_fDieInvCnt(0.0f)
	, m_pWalkEffectMng(nullptr)
	, m_nWalkEffeCnt(0)
	, m_nSweatEffeCnt(0)
	, m_nSwingFastCnt(0)
	, m_fRotate_x(PLAYER_ROTATE_X_NORMAL)
{
	m_pHammer = new CHammer();								// Hammer�N���X���C���X�^���X

	m_Sphere.fRadius = PLAYER_RADIUS;						// �����蔻��p�̋��̂̔��a
	m_Transform.fScale = PLAYER_SIZE;
	LoadSound();							//�T�E���h�t�@�C���ǂݍ���

	//�v���C���[�̃��f���ǂݍ���
	m_pModel = new AnimeModel();
	if (!m_pModel->Load("Assets/Model/player/POW.fbx", 1.0f, AnimeModel::Flip::XFlip)) {		//�{���Ɣ��]�͏ȗ���
		MessageBox(NULL, "player", "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
	}
	m_pModel->SetVertexShader(ShaderList::GetVS(ShaderList::VS_ANIME));		//���_�V�F�[�_�[���Z�b�g
	//m_pModel->SetPixelShader(ShaderList::GetPS(ShaderList::PS_LAMBERT));	//�s�N�Z���V�F�[�_�[���Z�b�g

	LoadAnime();	//�A�j���[�V�����̓ǂݍ���
	m_pShadow = new CShadow();

	m_pWalkEffectMng = new CWalkEffectManager();
	m_pSweatEffectMng = new CSweatEffectManager();

}
/* ========================================
   �֐��F�f�X�g���N�^
   ----------------------------------------
   ���e�F�j�����ɍs������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
CPlayer::~CPlayer()
{
	SAFE_DELETE(m_pWalkEffectMng);
	SAFE_DELETE(m_pShadow);
	SAFE_DELETE(m_pModel);
	SAFE_DELETE(m_pHammer);
}

/* ========================================
   �X�V�����֐��֐�
   ----------------------------------------
   ���e�F�X�V����
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
void CPlayer::Update()
{
	// ���S�����ꍇ
	if (m_bDieInvFlg)
	{
		m_bAttackFlg	= false;				// �U�����t���O���I�t�ɂ���
		m_DrawFlg		= true;					// �_�ł�����
		m_bSafeTimeFlg	= false;				// ���G������

		m_fDieInvCnt++;
		// ���S�P�\���Ԃ��o�߂��Ă��邩
		if (DIE_AFTER_INTERVAL <= m_fDieInvCnt)
		{
			m_bDieFlg = true;	// ���S������I��
		}

	}
	// �n���}�[�U����
	else if (m_bAttackFlg)
	{
		// �n���}�[�̍U�����I��������
		if (m_pHammer->Update() == false)
		{
			m_pHammer->SwingSpeedSlow();	// �n���}�[�̃X�C���O�X�s�[�h��x������
			m_pModel->SetAnimationSpeed(m_Anime[MOTION_SWING], m_pHammer->GetSwingSpeed() * SWING_ANIM_ADJUST);	// �A�j���̑�����ݒ�
			m_bAttackFlg = false;			// �U�����t���O���I�t�ɂ���
			m_bHumInvFlg = true;			// �n���}�[�U��Ԋu�t���O�I��
		}

	}
	// �n���}�[�U���ȊO
	else
	{
		// �n���}�[�Ԋu���ԃt���O���I���̎�
		if (m_bHumInvFlg)
		{
			m_fHumInvCnt++;				// �n���}�[�Ԋu���ԃJ�E���g���Z
			if (m_fHumInvCnt >= HAMMER_INTERVAL_TIME)
			{
				m_bHumInvFlg = false;		// �n���}�[�Ԋu���ԃt���O�I��
				m_fHumInvCnt = 0.0f;		// �n���}�[�Ԋu���ԃ��Z�b�g
			}
		}

		// �R���g���[�����ڑ�����ĂȂ��ꍇ
		if (GetUseVController() == false)
		{
			MoveKeyboard();
		}
		// �R���g���[�����ڑ�����Ă���ꍇ
		else
		{
			MoveController();
		}

		// �J�����X�V
		m_pCamera->Update();	//�ʒu�X�V��A����𑦍��ɃJ�����ɔ��f������


		// �X�y�[�X�L�[�����������A�܂��̓R���g���[����B�{�^������������ && �n���}�[�Ԋu���Ԍo�ߍς�
		if ((IsKeyTrigger(VK_SPACE) || IsKeyTriggerController(BUTTON_B)) && !m_bHumInvFlg)
		{
			SAFE_DELETE(m_pWaitFrameCnt);	//�J�E���^�폜

 			m_pModel->Play(m_Anime[MOTION_SWING], false, m_pHammer->GetSwingSpeed() * SWING_ANIM_ADJUST);	//�A�j���[�V�����̍Đ�
			m_pModel->SetAnimationTime(m_Anime[MOTION_SWING], 0.0f);		//�A�j���[�V�����^�C�����X�^�[�g�ʒu�ɃZ�b�g

			m_pHammer->AttackStart(m_Transform.fPos, m_Transform.fRadian.y);	// �n���}�[�U���J�n
			m_bAttackFlg = true;	// �U���t���O��L���ɂ���

			//SE�̍Đ�
			PlaySE(SE_SWING);

		}
		else
		{
			m_nSwingFastCnt++;
			if (SWING_FAST_INTERVAL < m_nSwingFastCnt)
			{
				// �U���{�^���������ĂȂ����̓n���}�[�̃X�C���O�X�s�[�h��ʏ�ɖ߂��Ă���
				m_pHammer->SwingSpeedFast();
				m_pModel->SetAnimationSpeed(
					m_Anime[MOTION_SWING],
					m_pHammer->GetSwingSpeed() * SWING_ANIM_ADJUST);	// �A�j���̑�����ݒ�
				m_nSwingFastCnt = 0;
			}
			
		}

	}


	// ���G��ԂɂȂ��Ă���ꍇ
	if (m_bSafeTimeFlg)
	{
		m_nSafeTimeCnt++;					// ���t���[���ŃJ�E���g��ǉ�
		DamageAnimation();					// �v���C���[�_�Ŋ֐��Ăяo��

		// �J�E���g����莞�Ԃ𒴂�����
		if (m_nSafeTimeCnt >= NO_DAMAGE_TIME)
		{
			m_DrawFlg = true;				// �_�ł�����
			m_bSafeTimeFlg = false;				// ���G������
		}

	}

	//�ړ��ɂ��SE�ƃA�j���[�V�����̏���
	MoveCheck();

	//�A�j���[�V�����̍X�V
	if (!m_pWaitFrameCnt)	//�ҋ@���Ԓ��͎~�߂�
	{
		m_pModel->Step(ADD_ANIM_FRAME);
	}
	
	DisplaySweatEffect();			// ���G�t�F�N�g�쐬
		
	m_pWalkEffectMng->Update();
	m_pSweatEffectMng->Update(m_Transform.fPos);

	
}

/* ========================================
   �`�揈���֐�
   ----------------------------------------
   ���e�F�`�揈��
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
void CPlayer::Draw()
{
	// �`�悵�Ȃ�(�_�ŏ�����)
	if (m_DrawFlg == true)
	{
		//-- ���f���\��
		if (m_pModel) {
			// �����_�[�^�[�Q�b�g�A�[�x�o�b�t�@�̐ݒ�
			RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
			DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
			SetRenderTargets(1, &pRTV, pDSV);		//DSV��null����2D�\���ɂȂ�

			//m_pModel->Draw();
		}

		DirectX::XMFLOAT4X4 mat[3];

		//�g�k�A��]�A�ړ�(Y����]���ɂ����������̂�SRT�͎g��Ȃ�)
		DirectX::XMStoreFloat4x4(&mat[0], 
			DirectX::XMMatrixTranspose(
				DirectX::XMMatrixScaling(m_Transform.fScale.x, m_Transform.fScale.y, m_Transform.fScale.z)		// �傫��
				* DirectX::XMMatrixRotationY(m_Transform.fRadian.y)	// Y�p�x
				* DirectX::XMMatrixRotationX(m_fRotate_x)			// X�p�x
				* DirectX::XMMatrixRotationZ(m_Transform.fRadian.z)	// Z�p�x
				* DirectX::XMMatrixTranslation(m_Transform.fPos.x, m_Transform.fPos.y, m_Transform.fPos.z)));	// ���W
		mat[1] = m_pCamera->GetViewMatrix();
		mat[2] = m_pCamera->GetProjectionMatrix();


		ShaderList::SetWVP(mat);

		//�A�j���[�V�����Ή������v���C���[�̕`��
		m_pModel->Draw(nullptr, [this](int index)
		{
			const AnimeModel::Mesh* pMesh = m_pModel->GetMesh(index);
			const AnimeModel::Material* pMaterial = m_pModel->GetMaterial(pMesh->materialID);
			ShaderList::SetMaterial(*pMaterial);

			DirectX::XMFLOAT4X4 bones[200];
			for (int i = 0; i < pMesh->bones.size() && i < 200; ++i)
			{
				// ���̌v�Z�̓Q�[������[�u�X�L�����b�V���̎d�g�݁v���Q�l�ɂȂ�
				DirectX::XMStoreFloat4x4(&bones[i], DirectX::XMMatrixTranspose(
					pMesh->bones[i].invOffset *
					m_pModel->GetBone(pMesh->bones[i].index)
				));
			}
			ShaderList::SetBones(bones);
		});
#ifdef _DEBUG
		//�A�j���[�V�����̓������m�F�ł���{�[���̕`��(���S���瓮���Ȃ�)
		//m_pModel->DrawBone();	
#endif
	}

	//=====�A�j���[�V�����̒����p�Ɉꉞ�c���Ă���=====
	if (m_bAttackFlg)
	{
		//m_pHammer->Draw();		// �n���}�[�̕`��
	}

	m_pShadow->Draw(m_Transform, PLAYER_SHADOW_SCALE, m_pCamera);	// �e�̕`��

	m_nWalkEffeCnt++;
	m_pWalkEffectMng->Draw();
	m_pSweatEffectMng->Draw();
}

/* ========================================
   �_���[�W�֐�
   ----------------------------------------
   ���e�F�v���C���[���_���[�W���󂯂�
   ----------------------------------------
   �����F�U����
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
void CPlayer::Damage(int DmgNum)
{
	if (m_bDieInvFlg) return;	// ���S�������Ƃ͏������Ȃ�

	m_nHp -= DmgNum;
	m_bSafeTimeFlg = true;	//�v���C���[����莞�ԁA���G�ɂ���
	m_nSafeTimeCnt = 0;	//�v���C���[���G���Ԃ̃J�E���g��0�ɖ߂�
	//=== SE�̍Đ� =====
	PlaySE(SE_DAMAGED);

	// �v���C���[���m���ɂȂ�����x�����𗬂�
	if(m_nHp == PLAYER_WARNING_HP) PlaySE(SE_WARNING);

	if (m_nHp <= 0)
	{
		m_bDieInvFlg = true;
		m_fRotate_x = PLAYER_ROTATE_X_DIE;			// �v���C���[�̌X�����Z�b�g(�n�ʂɖ��܂�Ȃ��悤��)
		m_pModel->Play(m_Anime[MOTION_DIE],false);	// �A�j���[�V�����̍Đ�

	}
}

/* ========================================
   �L�[�{�[�h�p���͈ړ��֐�
   ----------------------------------------
   ���e�F�L�[�{�[�h���͂̈ړ�����
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
void CPlayer::MoveKeyboard()
{
	TPos3d<float> fMoveInput;	// �L�[�{�[�h�̓��͒l������ϐ�

	// �L�[����
	// �㉺
	if (IsKeyPress('W')) { fMoveInput.z = KEYBOARD_INPUT_SIZE; }		// ��	
	else if (IsKeyPress('S')) { fMoveInput.z = -KEYBOARD_INPUT_SIZE; }	// ��
	else { fMoveInput.z = 0.0f; }										// ���͖���

	// ���E
	if (IsKeyPress('D')) { fMoveInput.x = KEYBOARD_INPUT_SIZE; }		// ��	
	else if (IsKeyPress('A')) { fMoveInput.x = -KEYBOARD_INPUT_SIZE; }	// ��
	else { fMoveInput.x = 0.0f; }										// ���͖���

	MoveSizeInputSet(fMoveInput);	// ���͒l����ړ��ʂƌ������Z�b�g

	// ���W���ړ�
	m_Transform.fPos.x += m_fMove.x;
	m_Transform.fPos.z += m_fMove.z;
	
}

/* ========================================
   �R���g���[���p���͈ړ��֐�
   ----------------------------------------
   ���e�F�R���g���[�����͂̈ړ�����
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
void CPlayer::MoveController()
{

	TPos3d<float> fMoveInput;	// �X�e�B�b�N�̓��͒l������ϐ�

	// �R���g���[���[�̍��X�e�B�b�N�̌X�����擾
	fMoveInput.x = IsStickLeft().x;
	fMoveInput.z = IsStickLeft().y * -1;	// �㉺�t(�����|1)

	MoveSizeInputSet(fMoveInput);	// ���͒l����ړ��ʂƌ������Z�b�g

	// ���W���ړ�
	m_Transform.fPos.x += m_fMove.x;
	m_Transform.fPos.z += m_fMove.z;

}

/* ========================================
   �ړ��ʃC���v�b�g�Z�b�g�֐�
   ----------------------------------------
   ���e�F���͒l����ړ��ʂƌ������Z�b�g����
   ----------------------------------------
   ����1�F���͒l(x��z���g�p����)
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
void CPlayer::MoveSizeInputSet(TPos3d<float> fInput)
{
	// �L�[���͂�����ꍇ
	if (fInput.z != 0 || fInput.x != 0)
	{
		float moveRad = atan2(fInput.z, fInput.x);	// �ړ����͂��������̊p�x�����߂�

		// �p�x�����Ɉړ�����ړ��ʂ��Z�b�g
		m_fMove.x = cosf(moveRad) * PLAYER_MOVE_SPEED;
		m_fMove.z = sinf(moveRad) * PLAYER_MOVE_SPEED;

		// �����Z�b�g
		m_Transform.fRadian.y =
			(atan2(fInput.z * -1, fInput.x)			// DirectX�ƎO�p�֐��ŉ�]�������t�Ȃ̂Œ���
				- DirectX::XMConvertToRadians(90.0f));	// DirectX�ƎO�p�֐���0�x�̈ʒu��90�x����Ă���(����0)�̂Œ���
		
		// �v���C���[�ړ����G�t�F�N�g�\��
		if (WALK_EFFECT_INTERVAL <= m_nWalkEffeCnt)
		{
			m_pWalkEffectMng->Create(m_Transform);	// �v���C���[�ړ��G�t�F�N�g�쐬
			m_nWalkEffeCnt = 0;
		}
	}
	// �L�[���͂��Ȃ��ꍇ
	else
	{
		// �ړ����Ȃ�
		m_fMove.z = 0.0f;
		m_fMove.x = 0.0f;
	}
}

/* ========================================
   ���G�t�F�N�g�o���֐�
   ----------------------------------------
   ���e�F�n���}�[�̑��x�ɂ���Ċ��G�t�F�N�g��\��������
   ----------------------------------------
   ����1�F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
void CPlayer::DisplaySweatEffect()
{
	// �U�鑬�x�����ȉ��ɂȂ�����
	if (m_pHammer->GetSwingSpeed() < SWEAT_EFFECT_DISP_SPEED)
	{
		m_nSweatEffeCnt++;

		// �\���Ԋu���o�߂�����(GetSwingSpeed���|���邱�ƂŊԊu�����X�ɒZ���Ȃ�悤��)
		if (SWEAT_EFFECT_INTERVAL * m_pHammer->GetSwingSpeed() <= m_nSweatEffeCnt)
		{
			m_pSweatEffectMng->Create(m_Transform.fPos, m_Transform.fRadian);	// ���G�t�F�N�g�쐬
			m_nSweatEffeCnt = 0;
		}
	}
	else
	{
		m_nSweatEffeCnt = 0;	// �U�鑬�x���񕜂����烊�Z�b�g
	}
}


/* ========================================
   �n���}�[�����蔻��擾�֐�
   ----------------------------------------
   ���e�F�n���}�[�̓����蔻��p�̋��̂��擾����֐�
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�����蔻��(Sphere)
======================================== */
tagSphereInfo CPlayer::GetHammerSphere()
{
	return m_pHammer->GetSphere();
}

/* ========================================
   �v���C���[���W�|�C���^�擾�֐�
   ----------------------------------------
   ���e�F�v���C���[�̍��W�̃|�C���^�̎擾����֐�(�J�����Ɏg�p����)
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F���W�|�C���^�A�h���X
======================================== */
TPos3d<float>* CPlayer::GetPosAddress()
{
	return &m_Transform.fPos;
}

/* ========================================
   �n���}�[�|�C���^�擾�֐�
   ----------------------------------------
   ���e�F�v���C���[�̃n���}�[�|�C���^���擾����֐�
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�n���}�[�|�C���^
======================================== */
CHammer* CPlayer::GetHammerPtr()
{
	return m_pHammer;
}

/* ========================================
   ���G���ԃt���O�擾�֐�
   ----------------------------------------
   ���e�F�v���C���[�����G��Ԃ��̊m�F
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�Fbool(true=���G���) 
======================================== */
bool CPlayer::GetSafeTime()
{
	return m_bSafeTimeFlg;
}

/* ========================================
   �v���C���[HP�擾�֐�
   ----------------------------------------
   ���e�F�v���C���[��HP���擾
   ----------------------------------------
   �����F����
   ----------------------------------------
   �ߒl�F����
======================================== */
int* CPlayer::GetHpPtr()
{
	return &m_nHp;
}

/* ========================================
   �v���C���[���S�t���O�擾�֐�
   ----------------------------------------
   ���e�F�v���C���[���S�t���O���擾
   ----------------------------------------
   �����F����
   ----------------------------------------
   �ߒl�Ftrue = ���S / false = ����
======================================== */
bool CPlayer::GetDieFlg() const
{
	return m_bDieFlg;
}


/* ========================================
   �J�����̃Z�b�g�֐�
   ----------------------------------------
   ���e�F�v���C���[�Ǐ]�J�������Z�b�g����
   ----------------------------------------
   �����F�J����
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
void CPlayer::SetCamera(CCamera * pCamera)
{
	m_pCamera = pCamera;	//���g�͕ς����Ȃ����ǃ|�C���^�͂������̂Ń��V�I
	m_pHammer->SetCamera(m_pCamera);
	m_pWalkEffectMng->SetCamera(m_pCamera);
	m_pSweatEffectMng->SetCamera(m_pCamera);

}

/* ========================================
   �n���}�[�U���t���O�擾�֐�
   ----------------------------------------
   ���e�F�n���}�[�U���t���O�擾����
   ----------------------------------------
   �����F����
   ----------------------------------------
   �ߒl�F�n���}�[�U���t���O
======================================== */
bool CPlayer::GetAttackFlg()
{
	return m_bAttackFlg;
}

void CPlayer::SetSweatEffectMng(CSweatEffectManager* pSweatefcMng)
{
	m_pSweatEffectMng = pSweatefcMng;
}

/* ========================================
   �A�j���[�V�����ǂݍ��݊֐�
   ----------------------------------------
   ���e�F�A�j���[�V������ǂݍ���
   ----------------------------------------
   �����F����
   ----------------------------------------
   �ߒl�F����
======================================== */
void CPlayer::LoadAnime()
{
	for (int i = 0; i < MOTION_MAX; i++)
	{
		//�e�A�j���[�V�����̓ǂݍ���
		m_Anime[i] = m_pModel->AddAnimation(m_sAnimeFile[i].c_str());
		//�ǂݍ��݂Ɏ��s������G���[���b�Z�[�W
		if (!m_pModel->GetAnimation(m_Anime[i]))
		{
			MessageBox(NULL, m_sAnimeFile[i].c_str(), "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
		}
	}
}

/* ========================================
   �v���C���[�_�Ŋ֐�
   ----------------------------------------
   ���e�F�v���C���[���_���[�W���󂯂���_�ł���
   ----------------------------------------
   �����F����
   ----------------------------------------
   �ߒl�F����
======================================== */
void CPlayer::DamageAnimation()
{

	m_FlashCnt++;						//���t���[���ŃJ�E���g��ǉ�
	if (m_FlashCnt >= DAMAGE_FLASH_FRAME)
	{
		// �`�悷�邩���Ȃ��؂�ւ�
		if (m_DrawFlg)
		{
			m_DrawFlg = false;
		}
		else
		{
			m_DrawFlg = true;
		}

		m_FlashCnt = 0;
	}

}

/* ========================================
   �v���C���[���ړ��m�F�֐�
   ----------------------------------------
   ���e�F�v���C���[���ړ����Ă��邩�m�F���āA����ɉ������������s��
   ----------------------------------------
   �����F����
   ----------------------------------------
   �ߒl�F����
======================================== */
void CPlayer::MoveCheck()
{
	if (m_bDieInvFlg) return;	// ���S�������Ƃ͏������Ȃ�

	//�ړ��ʂ��c���ǂ����0�̎��̓J�E���g�����Z�b�g(�ړ����Ă��Ȃ���)
	if (m_fMove.x == 0.0f && m_fMove.z == 0.0f)
	{
		// �ҋ@���̃A�j���[�V�������Đ����ĂȂ��A�Ȃ����U��������Ȃ��ꍇ
		if (m_pModel->GetPlayNo() != m_Anime[MOTION_STOP] 
			&& !m_bAttackFlg && !m_pModel->IsPlay(m_Anime[MOTION_SWING]))	
		{
			// �J�E���g�_�E���J�n�O�̏ꍇ
			if (!m_pWaitFrameCnt)	// �l��nullptr
			{
				m_pWaitFrameCnt = new CFrameCnt(CNT_START_WAIT);	//�J�E���g�_�E���J�n
			}
			// �J�E���g�_�E���J�n�ς݂̏ꍇ
			else
			{	
				m_pWaitFrameCnt->Count();	//�J�E���g�_�E����

			}
			// �J�E���g�_�E������
			if (m_pWaitFrameCnt->IsFin())
			{
				SAFE_DELETE(m_pWaitFrameCnt);					// �J�E���^�폜
				m_pModel->Play(m_Anime[MOTION_STOP], false);	// �ҋ@���[�V�����J�n
			}
		}
	}
	// �ړ����̏ꍇ(�ҋ@���[�V�����J�ڑO�Ɉړ����n�߂�)
	else
	{
		if (m_pWaitFrameCnt)
		{
			SAFE_DELETE(m_pWaitFrameCnt);	//�J�E���^�폜
		}

		m_nWalkSECnt++;	//�J�E���g�𑝂₷

		//�@�J�E���g�����ȏ�ɂȂ��SE�𔭐����ăJ�E���g�����Z�b�g
		if (SE_RUN_INTERVAL <= m_nWalkSECnt)
		{
			//SE�̍Đ�
			PlaySE(SE_RUN, SE_RUN_VOLUME);
			m_nWalkSECnt = 0;	//�J�E���g�����Z�b�g
		}

		// �ړ����̃A�j���[�V�������Đ����ĂȂ��ꍇ�A�Ȃ����U��������Ȃ��ꍇ
		if (m_pModel->GetPlayNo() != m_Anime[MOTION_MOVE] && !m_pModel->IsPlay(m_Anime[MOTION_SWING]))
		{	
			m_pModel->Play(m_Anime[MOTION_MOVE], true, PLAYER_MOVE_ANIME_SPEED);	// �A�j���[�V�������Đ�

		}

	}
	
}

/* ========================================
   �v���C���[�pSE�ǂݍ��݊֐�
   ----------------------------------------
   ���e�F�v���C���[�p��SE�̃t�@�C����ǂݍ���
   ----------------------------------------
   �����F����
   ----------------------------------------
   �ߒl�F����
======================================== */
void CPlayer::LoadSound()
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
	SE�̓ǂݍ��݊֐�
	----------------------------------------
	���e�FSE�̓ǂݍ���
	----------------------------------------
	����1�FSE�̎��(enum)
	����2�F����
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CPlayer::PlaySE(SE se, float volume)
{
	m_pSESpeaker[se] = CSound::PlaySound(m_pSE[se]);	//SE�Đ�
	m_pSESpeaker[se]->SetVolume(volume);				//���ʂ̐ݒ�
}



/* ========================================
   �v���C���[�񕜊֐�
   ----------------------------------------
   ���e�F�v���C���[��HP���񕜂���
   ----------------------------------------
   �����F����
   ----------------------------------------
   �ߒl�F����
======================================== */
void CPlayer::Healing()
{
	m_nHp += HEAL_NUM;
	if (m_nHp >= PLAYER_HP) { m_nHp = PLAYER_HP; }
	PlaySE(SE_HEAL);
}


