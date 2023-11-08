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
   �E2023/11/09 �J�����Ή� ���؏x��


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
const int HP = 5;
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
	:m_playerPosition{ 0.0f,0.0f,0.0f }
	,m_playerForward{ 0.0f,0.0f,1.0f }
	, m_playerRotation(0.0f)
	, m_pHammer(nullptr)
	, m_pPlayer(nullptr)
	, m_bHammer(false)
	,m_nHp(0)
	,m_pCamera(nullptr)
{
	m_T = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	m_S = DirectX::XMMatrixScaling(2.0f, 2.0f, 2.0f);
	m_Ry = DirectX::XMMatrixRotationY(0.0f);
	m_pHammer = new CHammer();
	m_pPlayer = new CSphere();
	m_nHp = HP;

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
	if (m_pHammer != nullptr)
	{
		delete m_pHammer;
		m_pHammer = nullptr;
	}
}

void CPlayer::Update()
{
	
	Move();

	if (IsKeyTrigger(VK_SPACE) || m_pHammer->Gethammer())	//�n���}�[��U��
	{
		m_pHammer->Update(m_playerPosition, m_playerRotation);
	}
}

void CPlayer::Draw()
{
	if (!m_pCamera)
	{
		return;
	}

	m_pPlayer->SetView(m_pCamera->GetViewMatrix());
	m_pPlayer->SetProjection(m_pCamera->GetProjectionMatrix());
	m_pPlayer->Draw();
	if (m_pHammer->Gethammer())
	{
		m_pHammer->Draw();
	}
}

void CPlayer::Damege()
{
	m_nHp -= 1;
}

void CPlayer::Move()
{//������player�̈ʒu�ƐM�������X�V������
	if (IsKeyPress('W'))
	{		//�O
		m_playerPosition.z += PLAYERMOVE;			//player��+Z�����Ɉړ�
		m_playerForward.z = FORWARD_YES;			//�����Ă������
		m_playerForward.x = FORWARD_NO;
		if (IsKeyPress('A'))
		{//���O
			m_playerPosition.x -= PLAYERMOVE;
			m_playerForward.x = -FORWARD_YES;
		}
		else if (IsKeyPress('D'))
		{//�E�O
			m_playerPosition.x += PLAYERMOVE;
			m_playerForward.x = FORWARD_YES;
		}
	}
	else if (IsKeyPress('S'))
	{//���
		m_playerPosition.z -= PLAYERMOVE;
		m_playerForward.z = -FORWARD_YES;
		m_playerForward.x = FORWARD_NO;
		if (IsKeyPress('A'))
		{//�����
			m_playerPosition.x -= PLAYERMOVE;
			m_playerForward.x = -FORWARD_YES;
		}
		else if (IsKeyPress('D'))
		{//�E���
			m_playerPosition.x += PLAYERMOVE;
			m_playerForward.x = FORWARD_YES;
		}
	}
	else if (IsKeyPress('D'))
	{//�E
		m_playerPosition.x += PLAYERMOVE;
		m_playerForward.x = FORWARD_YES;
		m_playerForward.z = FORWARD_NO;
	}
	else if (IsKeyPress('A'))
	{//��
		m_playerPosition.x -= PLAYERMOVE;
		m_playerForward.x = -FORWARD_YES;
		m_playerForward.z = FORWARD_NO;
	}

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
	m_T = DirectX::XMMatrixTranslation(m_playerPosition.x, m_playerPosition.y, m_playerPosition.z);
	DirectX::XMMATRIX Ry = DirectX::XMMatrixRotationY(m_playerRotation);
	DirectX::XMMATRIX mat = Ry * m_T;
	mat = DirectX::XMMatrixTranspose(mat);
	DirectX::XMFLOAT4X4 fMat;	//�s��̊i�[��
	DirectX::XMStoreFloat4x4(&fMat, mat);
	m_pPlayer->SetWorld(fMat);
}

//�R�����g�߂�ǂ�tkg
void CPlayer::GetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;	//���g�͕ς����Ȃ����ǃ|�C���^�͂������̂Ń��V�I
}