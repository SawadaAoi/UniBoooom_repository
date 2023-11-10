/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   Player�pcpp
   ---------------------------------------
   Player.cpp

   �쐬��
	�R�{�M��
   �ύX����
   �E2023/11/03 �ړ��쐬 �R�{�M��
   �E2023/11/06 �����ǉ��A�_���[�W����A�U���J�n�쐬 �R�{�M��
   �E2023/11/08 �v���C���[�̓����蔻��̑傫���̒萔��ǉ� /�R�����C
   �E2023/11/08 �U�����͈ړ��ł��Ȃ��悤�ɕύX /�R�����C
   �E2023/11/09 �J�����Ή� ���؏x��
   �E2023/11/09 GameOver�̕\���@�R�����C
   �E2023/11/09 �R���g���[���ړ��̒ǉ��@�V�c����

   ======================================== */

   // =============== �C���N���[�h ===================
#include"Player.h"
#include "Input.h"
#include "Sphere.h"
// =============== �萔��` =======================
#define PLAYERMOVE (0.1f)	//player�̈ړ���
#define XM_PI (3.141593f)	//�~����
#define FORWARD_YES	(1.0f)	//���̕�����������
#define FORWARD_NO (0.0f)	//���̕����������Ă��Ȃ�
const int PLAYER_HP = 5;
const float PLAYER_RADIUS = 0.5f;	//�v���C���[�̓����蔻��̑傫��
const int NO_DAMAGE_TIME = 3 * 60;	//�v���C���[�̖��G����
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
	:m_pos{ 0.0f,0.0f,0.0f }
	/*,m_playerPosition{ 0.0f,0.0f,0.0f }*/
	,m_playerForward{ 0.0f,0.0f,0.0f }
	,m_playerRotation(0.0f)
	,m_pHammer(nullptr)
	,m_pPlayerGeo(nullptr)
	,m_pGameOver(nullptr)
	,m_bHammer(false)
	,m_nHp(0)
	,m_pCamera(nullptr)
	,m_nNoDamageCnt(0)
	,m_bCollide(false)
{
	m_T = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);	//�ړ��̕ϊ��s���������
	m_S = DirectX::XMMatrixScaling(2.0f, 2.0f, 2.0f);		//�g�k�̕ϊ��s���������
	m_Ry = DirectX::XMMatrixRotationY(0.0f);				//Y����]�̕ϊ��s���������
	m_pHammer = new CHammer();								//Hammer�N���X���C���X�^���X
	m_pPlayerGeo = new CSphere();							//�v���C���[�Ƃ��ĉ��\�����鋅�̃I�u�W�F�N�g�̃C���X�^���X
	m_pGameOver = new CSphere();
	m_nHp = PLAYER_HP;												//�v���C���[��HP������
	m_sphere.pos = { 0.0f,0.0f,0.0f };	//�����蔻��p�̋��̂̍��W��������
	m_sphere.radius = PLAYER_RADIUS;	//�����蔻��p�̋��̂̔��a
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
	SAFE_DELETE(m_pGameOver);
	SAFE_DELETE(m_pPlayerGeo);
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
	if (!m_bHammer)	//�U�����͈ړ����Ȃ�
	{
		if (GetUseVController() == false)
		{
			Move();
		}
		else
		{
			ControllerMove();
		}
	}


	if ((IsKeyTrigger(VK_SPACE)|| IsKeyTriggerController(BUTTON_B)) || m_pHammer->Gethammer())	//�X�y�[�X�L�[�����������������̓n���}�[��U��t���O��ON�̎�
	{
		m_pHammer->Update(m_pos, m_playerRotation);			//�n���}�[��U��Update�������s��
	}
	
	m_bHammer = m_pHammer->Gethammer();	//�n���}�[���g�p�����m�F
	if (m_bCollide)							//���G��ԂɂȂ��Ă���ꍇ
	{
		m_nNoDamageCnt++;						//���t���[���ŃJ�E���g��ǉ�
		if (m_nNoDamageCnt >= NO_DAMAGE_TIME)	//�J�E���g����莞�Ԃ𒴂�����
			m_bCollide = false;				//���G������
	}
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
	if (!m_pCamera)
	{
		return;
	}

	m_pPlayerGeo->SetView(m_pCamera->GetViewMatrix());
	m_pPlayerGeo->SetProjection(m_pCamera->GetProjectionMatrix());
	m_pPlayerGeo->Draw();		//�v���C���[��`��
	if (m_pHammer->Gethammer())	//�n���}�[��U��t���O��ON�̎�
	{
		m_pHammer->Draw(m_pCamera);		//�n���}�[�̕`��
	}

	if (m_nHp <= 0)	//�Q�[���I�[�o�[��\���I�u�W�F�N�g�̕`��	<=TODO ��X�����܂�
	{
		m_pGameOver->SetView(m_pCamera->GetViewMatrix());										//�r���[�̃Z�b�g
		m_pGameOver->SetProjection(m_pCamera->GetProjectionMatrix());							//�v���W�F�N�V�����̃Z�b�g
		DirectX::XMMATRIX mat = DirectX::XMMatrixTranslation(0.0f, 2.0f, 0.0f);					//�ړ��̕ϊ��s��
		mat = DirectX::XMMatrixTranspose(mat);													//�]�u
		DirectX::XMFLOAT4X4 fmat;																//�Z�b�g���[���h�p�̕ϐ�
		DirectX::XMStoreFloat4x4(&fmat, mat);													//MATRIX�^����ϊ�
		m_pGameOver->SetWorld(fmat);															//���[���h�̃Z�b�g
		m_pGameOver->Draw();																	//GameOver�̕`��
	}
}

/* ========================================
   �_���[�W�֐�
   ----------------------------------------
   ���e�F�v���C���[���_���[�W���󂯂�
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CPlayer::Damage()
{
	m_nHp -= 1;
	m_bCollide = true;	//�v���C���[����莞�ԁA���G�ɂ���
	m_nNoDamageCnt = 0;	//�v���C���[���G���Ԃ̃J�E���g��0�ɖ߂�

	if (m_nHp <= 0)
	{
		//�Q�[���I�[�o�[���� <= TODO
	}
}

/* ========================================
   �v���C���[�̈ړ��֐�
   ----------------------------------------
   ���e�F�v���C���[���_���[�W���󂯂�
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CPlayer::Move()
{//������player�̈ʒu�Ɛi�s�������X�V������
	if (IsKeyPress('W'))
	{	//�O�Ɉړ�
		m_pos.z += PLAYERMOVE;					//player��+Z�����Ɉړ�
		m_playerForward.z = FORWARD_YES;		//�����Ă������
		m_playerForward.x = FORWARD_NO;
		if (IsKeyPress('A'))
		{//���O�Ɉړ�
			m_pos.x -= PLAYERMOVE;
			m_playerForward.x = -FORWARD_YES;
		}
		else if (IsKeyPress('D'))
		{//�E�O�Ɉړ�
			m_pos.x += PLAYERMOVE;
			m_playerForward.x = FORWARD_YES;
		}
	}
	else if (IsKeyPress('S'))
	{//���Ɉړ�
		m_pos.z -= PLAYERMOVE;
		m_playerForward.z = -FORWARD_YES;
		m_playerForward.x = FORWARD_NO;
		if (IsKeyPress('A'))
		{//�����Ɉړ�
			m_pos.x -= PLAYERMOVE;
			m_playerForward.x = -FORWARD_YES;
		}
		else if (IsKeyPress('D'))
		{//�E���Ɉړ�
			m_pos.x += PLAYERMOVE;
			m_playerForward.x = FORWARD_YES;
		}
	}
	else if (IsKeyPress('D'))
	{//�E�Ɉړ�
		m_pos.x += PLAYERMOVE;
		m_playerForward.x = FORWARD_YES;
		m_playerForward.z = FORWARD_NO;
	}
	else if (IsKeyPress('A'))
	{//���Ɉړ�
		m_pos.x -= PLAYERMOVE;
		m_playerForward.x = -FORWARD_YES;
		m_playerForward.z = FORWARD_NO;
	}

	m_sphere.pos = m_pos;	//�v���C���[�̍��W�𓖂��蔻��p�̋��̂ɃR�s�[

	//�i�s��������player�̌��������߂�
	if (m_playerForward.x == FORWARD_NO)	//x�����������ĂȂ�������Z���i�O��j�ɓ�������
	{
		if (m_playerForward.z > 0.0f) {//+Z�O�����ɂ���
			m_playerRotation = 0.0f; // �O����
		}
		else {
			m_playerRotation = XM_PI; // �����
		}
	}
	else {//Z�̕����ɂ������Ă�Ȃ�΂߁A�����ĂȂ��Ȃ牡�̕���������
		m_playerRotation = atan(m_playerForward.x / m_playerForward.z);	//�����Ŏ΂߂����f
		if (m_playerForward.z < 0.0f) {
			m_playerRotation += XM_PI; // ����-�Ȃ���Ȃ̂ő����Č�둤��
		}
	}

	//=====player�̍��W�A��]���Z�b�g=====
	m_T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);		//�ړ��̕ϊ��s��
	DirectX::XMMATRIX Ry = DirectX::XMMatrixRotationY(m_playerRotation);//Y���̉�]�s��
	DirectX::XMMATRIX mat = Ry * m_T;									//�ϊ��s�������
	mat = DirectX::XMMatrixTranspose(mat);								//�ϊ��s���]�u
	DirectX::XMFLOAT4X4 fMat;											//�s��̊i�[��
	DirectX::XMStoreFloat4x4(&fMat, mat);								//XMFLOAT4X4�ɕϊ����Ċi�[
	m_pPlayerGeo->SetWorld(fMat);										//���[���h���W�ɃZ�b�g
}

/* ========================================
   �R���g���[�����͊֐�
   ----------------------------------------
   ���e�F�R���g���[�����͂̈ړ�����
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CPlayer::ControllerMove()
{
	// �R���g���[���[�̍��X�e�B�b�N�̌X�����擾
	float stick_x = IsStickLeft().x;
	float stick_y = IsStickLeft().y;	

	// �X�e�B�b�N���^�񒆂̏ꍇ�ړ����Ȃ�
	if (stick_x != 0 || stick_y != 0)
	{
		float moveRad = atan2(stick_y * -1, stick_x);	// �X�e�B�b�N��|���������̊p�x�����߂�(y�����t�Ȃ̂Ł|1���|����)

		// �p�x�����Ɉړ����鏈��
		m_pos.x += cosf(moveRad) * PLAYERMOVE;
		m_pos.z += sinf(moveRad) * PLAYERMOVE;

		m_playerRotation = atan2(stick_y, stick_x) + (XM_PI/2);	// XMMatrixTranslation�����v���Ŋp�x��90�x����Ă���(����0)�̂Œ���
	}

	m_sphere.pos = m_pos;	//�v���C���[�̍��W�𓖂��蔻��p�̋��̂ɃR�s�[

	m_T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);		//�ړ��̕ϊ��s��
	DirectX::XMMATRIX Ry = DirectX::XMMatrixRotationY(m_playerRotation);//Y���̉�]�s��
	DirectX::XMMATRIX mat = Ry * m_T;									//�ϊ��s�������
	mat = DirectX::XMMatrixTranspose(mat);								//�ϊ��s���]�u
	DirectX::XMFLOAT4X4 fMat;											//�s��̊i�[��
	DirectX::XMStoreFloat4x4(&fMat, mat);								//XMFLOAT4X4�ɕϊ����Ċi�[
	m_pPlayerGeo->SetWorld(fMat);										//���[���h���W�ɃZ�b�g
}
	

/* ========================================
   �v���C���[�����蔻��擾�֐�
   ----------------------------------------
   ���e�F�v���C���[�̓����蔻��p�̋��̂��擾����֐�
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�����蔻��(Sphere)
   ======================================== */
CSphereInfo::Sphere CPlayer::GetPlayerSphere()
{
	return m_sphere;
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
CSphereInfo::Sphere CPlayer::GetHammerSphere()
{
	return m_pHammer->GetSphere();
}

/* ========================================
   �v���C���[���W�̎擾�֐�
   ----------------------------------------
   ���e�F�v���C���[�̍��W���擾����֐�
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F���W(x,y,z)
   ======================================== */
TPos3d<float> CPlayer::GetPos()
{
	return m_pos;
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
bool CPlayer::GetHammerFlg()
{
	return m_bHammer;
}
