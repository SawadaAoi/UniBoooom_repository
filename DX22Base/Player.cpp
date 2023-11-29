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
	�E2023/11/23 �Q�[���I�[�o�[�̉��\�����폜 yamashita
	�E2023/11/27 Update���n���}�[�U��Ԋu�����ǉ� Tei
	�E2023/11/28 �_���[�W�����Ɏ󂯂�_���[�W�ʂ�ǉ� Sawada
	�E2023/11/28 �񕜏�����ǉ� yamashita

======================================== */

// =============== �C���N���[�h ===================
#include "Player.h"
#include "Input.h"
#include "Sphere.h"
#include "GameParameter.h"		//�萔��`�p�w�b�_�[
#define _USE_MATH_DEFINES		// �~����
#include <math.h>				// �~����

// =============== �萔��` =======================
const float KEYBOARD_INPUT_SIZE = 1.0f;	// �L�[�{�[�h�̓��͒l�̑傫��

#if MODE_GAME_PARAMETER
#else
const float PLAYER_MOVE_SPEED	= 0.1f;			//�v���C���[�̈ړ���
const int	PLAYER_HP			= 5;
const float PLAYER_RADIUS		= 0.3f;			// �v���C���[�̓����蔻��̑傫��
const float PLAYER_SIZE			= 1.0f;			// �v���C���[�̑傫��
const int	NO_DAMAGE_TIME		= 3 * 60;		//�v���C���[�̖��G����
const int	DAMAGE_FLASH_FRAME	= 0.1f * 60;	// �v���C���[�̃_���[�W�_�ł̐؂�ւ��Ԋu
const int	SE_RUN_INTERVAL		= 0.4f * 60;	//�v���C���[�̈ړ��ɂ��SE�����̊Ԋu
const int	HEAL_NUM			= 1;			//�v���C���[�̉񕜗�
const float	SE_RUN_VOLUME		= 0.3f;			//�ړ��ɂ��SE�̉���
const float HAMMER_INTERVAL_TIME	= 1.0f * 60;	// �n���}�[�U��Ԋu

#endif

// =============== �O���[�o���ϐ���` =============


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
	, m_nHp(0)
	, m_pCamera(nullptr)
	, m_nNoDamageCnt(0)
	, m_bCollide(false)
	, m_DrawFlg(true)
	, m_FlashCnt(0)
	, m_pSESwingHammer(nullptr)
	, m_pSESwingHamSpeaker(nullptr)
	, m_pSERun(nullptr)
	, m_pSERunSpeaker(nullptr)
	, m_pSEDamaged(nullptr)
	, m_pSEDamagedSpeaker(nullptr)
	, m_nMoveCnt(0)
	, m_bIntFlg(false)
	, m_fIntCnt(0.0f)
{
	m_pHammer = new CHammer();								// Hammer�N���X���C���X�^���X
	m_nHp = PLAYER_HP;										// �v���C���[��HP������
	m_Sphere.fRadius = PLAYER_RADIUS;						// �����蔻��p�̋��̂̔��a
	m_Transform.fScale = PLAYER_SIZE;
	LoadSound();	//�T�E���h�t�@�C���ǂݍ���

	//���_�V�F�[�_�ǂݍ���
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}
	//�v���C���[�̃��f���ǂݍ���
	m_pModel = new Model;
	if (!m_pModel->Load("Assets/Model/player/player.FBX", 1.0f, Model::None)) {		//�{���Ɣ��]�͏ȗ���
		MessageBox(NULL, "player", "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
	}
	m_pModel->SetVertexShader(m_pVS);
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
	SAFE_DELETE(m_pModel);
	SAFE_DELETE(m_pVS);
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
	// �n���}�[�U����
	if (m_bAttackFlg == true)
	{
		// �n���}�[�̍U�����I��������
		if (m_pHammer->Update() == false)
		{
			m_bAttackFlg = false;	// �U�����t���O���I�t�ɂ���
			m_bIntFlg = true;		// �n���}�[�U��Ԋu�t���O�I��
		}

	}
	else
	{
		// �n���}�[�Ԋu���ԃt���O���I���̎�
		if (m_bIntFlg)
		{
			m_fIntCnt++;				// �n���}�[�Ԋu���ԃJ�E���g���Z
			if (m_fIntCnt >= HAMMER_INTERVAL_TIME)
			{
				m_bIntFlg = false;		// �n���}�[�Ԋu���ԃt���O�I��
				m_fIntCnt = 0.0f;		//�n���}�[�Ԋu���ԃ��Z�b�g
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


		// �X�y�[�X�L�[�����������A�܂��̓R���g���[����B�{�^������������ && �n���}�[�Ԋu���Ԍo�ߍς�
		if ((IsKeyTrigger(VK_SPACE) || IsKeyTriggerController(BUTTON_B)) && !m_bIntFlg)
		{
			m_pHammer->AttackStart(m_Transform.fPos, m_Transform.fRadian.y);	// �n���}�[�U���J�n
			m_bAttackFlg = true;	// �U���t���O��L���ɂ���
			m_pSESwingHamSpeaker = CSound::PlaySound(m_pSESwingHammer);	//�n���}�[��U��SE�̍Đ�
		}

	}
	
	// ���G��ԂɂȂ��Ă���ꍇ
	if (m_bCollide)							
	{
		m_nNoDamageCnt++;					// ���t���[���ŃJ�E���g��ǉ�
		DamageAnimation();					// �v���C���[�_�Ŋ֐��Ăяo��

		// �J�E���g����莞�Ԃ𒴂�����
		if (m_nNoDamageCnt >= NO_DAMAGE_TIME)	
		{
			m_DrawFlg = true;				// �_�ł�����
			m_bCollide = false;				// ���G������
		}
		
	}

	SE_Move();	//�ړ��ɂ��SE�̏���
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
		DirectX::XMFLOAT4X4 mat[3];

		mat[0] = m_Transform.GetWorldMatrixSRT();
		mat[1] = m_pCamera->GetViewMatrix();
		mat[2] = m_pCamera->GetProjectionMatrix();

		//-- �s����V�F�[�_�[�֐ݒ�
		m_pVS->WriteBuffer(0, mat);

		//-- ���f���\��
		if (m_pModel) {
			// �����_�[�^�[�Q�b�g�A�[�x�o�b�t�@�̐ݒ�
			RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
			DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
			SetRenderTargets(1, &pRTV, pDSV);		//DSV��null����2D�\���ɂȂ�

			m_pModel->Draw();
		}
	}
	
	if (m_bAttackFlg)
	{
		m_pHammer->Draw();		//�n���}�[�̕`��
	}

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
	m_nHp -= DmgNum;
	m_bCollide = true;	//�v���C���[����莞�ԁA���G�ɂ���
	m_nNoDamageCnt = 0;	//�v���C���[���G���Ԃ̃J�E���g��0�ɖ߂�
	m_pSEDamagedSpeaker = CSound::PlaySound(m_pSEDamaged);	//��_���[�W����SE�Đ�

	if (m_nHp <= 0)
	{
		//�Q�[���I�[�o�[���� <= TODO
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
	if		(IsKeyPress('W'))	{ fMoveInput.z =  KEYBOARD_INPUT_SIZE; }	// ��
	else if (IsKeyPress('S'))	{ fMoveInput.z = -KEYBOARD_INPUT_SIZE; }	// ��
	else						{ fMoveInput.z =  0.0f; }					// ���͖���
	// ���E
	if		(IsKeyPress('D'))	{ fMoveInput.x =  KEYBOARD_INPUT_SIZE; }	// ��
	else if (IsKeyPress('A'))	{ fMoveInput.x = -KEYBOARD_INPUT_SIZE; }	// ��
	else						{ fMoveInput.x =  0.0f; }					// ���͖���


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
			atan2(fInput.z * -1, fInput.x)			// DirectX�ƎO�p�֐��ŉ�]�������t�Ȃ̂Œ���
			+ DirectX::XMConvertToRadians(90.0f);	// DirectX�ƎO�p�֐���0�x�̈ʒu��90�x����Ă���(����0)�̂Œ���
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
   Collision�m�F�֐�
   ----------------------------------------
   ���e�F�v���C���[�����G��Ԃ��̊m�F
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�Fbool
======================================== */
bool CPlayer::GetCollide()
{
	return m_bCollide;
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
   �J�����̃Z�b�g�֐�
   ----------------------------------------
   ���e�F�v���C���[�Ǐ]�J�������Z�b�g����
   ----------------------------------------
   �����F�J����
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
void CPlayer::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;	//���g�͕ς����Ȃ����ǃ|�C���^�͂������̂Ń��V�I
	m_pHammer->SetCamera(m_pCamera);
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
   �v���C���[�_�Ŋ֐�
   ----------------------------------------
   ���e�F�v���C���[���_���[�W���󂯂���_�ł���
   ----------------------------------------
   �����F����
   ----------------------------------------
   �ߒl�F����
======================================== */
void CPlayer::SE_Move()
{
	m_nMoveCnt++;	//�J�E���g�𑝂₷

	//�ړ��ʂ��c���ǂ����0�̎��̓J�E���g�����Z�b�g
	if (m_fMove.x == 0.0f && m_fMove.z == 0.0f)	
	{
		m_nMoveCnt = 0;
	}

	//�J�E���g�����ȏ�ɂȂ��SE�𔭐����ăJ�E���g�����Z�b�g
	if (SE_RUN_INTERVAL <= m_nMoveCnt)	
	{
		m_pSERunSpeaker = CSound::PlaySound(m_pSERun);
		m_pSERunSpeaker->SetVolume(SE_RUN_VOLUME);
		m_nMoveCnt = 0;
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
	m_pSEDamaged = CSound::LoadSound("Assets/Sound/SE/PlayerDamage.mp3");	//SE�̓ǂݍ���
	m_pSESwingHammer = CSound::LoadSound("Assets/Sound/SE/Swing.mp3");		//SE�̓ǂݍ���
	m_pSERun = CSound::LoadSound("Assets/Sound/SE/Run.mp3");				//SE�̓ǂݍ���
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
	if (m_nHp == PLAYER_HP) { return; }
	m_nHp += HEAL_NUM;
}
