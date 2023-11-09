/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	Hammer�pcpp
	------------------------------------
	Hammer.cpp
	------------------------------------
	�쐬��
		�R�{�M��
	�ύX����
	�E2023/11/08 �R�����g�ǉ� /�R�����C
	�E2023/11/08 �ł������̕ϐ��̓����o�C�j�V�����C�U�ŏ����� /�R�����C
	�E2023/11/08 �萔HALF_PI�AANGULAR_ANGLE�AROTATE_RADIUS���` /�R�����C
	�E2023/11/08 Update�ɏ�����Ă���������Swing�֐��ɕ������@/�R�����C
	�E2023/11/08 ���I�m�ۂ����|�C���^��delete����SAFE_DELETE�ɕύX�@/�R�����C
	�E�����蔻��p��Sphere�̃Q�b�g�֐���ǉ� /�R�����C

========================================== */

// =============== �萔��` =======================
const float HALF_PI = 3.141592f / 2;	//�n���}�[�̊J�n�n�_�̃��W�A���p(�v�C��)
const float ANGULAR_ANGLE = 0.1f;		//���t���[���ړ�����p�x��
const float ROTATE_RADIUS = 1.0f;		//�n���}�[����]����v���C���[����̋���
const float HAMMER_SIZE = 0.8f;			//�n���}�[�̓����蔻��̑傫��

#include "hammer.h"
#include "Sphere.h"

/* ========================================
   �R���X�g���N�^
   ----------------------------------------
   ���e�F��������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
CHammer::CHammer()
	:m_pos{ 0.0f,0.0f,0.0f }
	,m_stateangle(0.0f)
	, m_nowangle(HALF_PI)
	, m_bHammer(false)
	, m_pHammerGeo(nullptr)
{
	m_T = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);	//�ړ��̕ϊ��s��̏�����
	m_S = DirectX::XMMatrixScaling(0.0f, 0.0f, 0.0f);		//�g�k�̕ϊ��s��̏�����
	m_S = DirectX::XMMatrixRotationY(0.0f);					//Y���̉�]�̕ϊ��s��̏�����
	m_pHammerGeo = new CSphere();							//�n���}�[�����\������W�I���g���[
	m_sphere.pos = {0.0f, 0.0f, 0.0f};
	m_sphere.radius = 0.5f;
}

/* ========================================
   �f�X�g���N�^
   ----------------------------------------
   ���e�F��������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
CHammer::~CHammer()
{
	SAFE_DELETE(m_pHammerGeo);
}


void CHammer::Update(TPos3d<float> pPos, float angle)
{
	Swing(pPos,angle);	//��]�ɂ��ړ��֐�

	//���݊p�x��0�ɂȂ����瓮��I��
	if (m_nowangle <= 0.0f)
	{
		m_bHammer = false;		//�n���}�[�̎g�p�t���O��OFF
		m_nowangle = HALF_PI;	//�n���}�[�̌��݊p�x�������l�ɖ߂�
	}
}

/* ========================================
   �`��֐�
   ----------------------------------------
   ���e�F�`����s��
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CHammer::Draw(const CCamera* pCamera)
{
	m_T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);	//�n���}�[�̍��W���ړ��̍s��Ɋi�[
	DirectX::XMMATRIX mat = m_T;			//�ړ��̍s����i�[
	mat = DirectX::XMMatrixTranspose(mat);	//�]�u
	DirectX::XMFLOAT4X4 fMat;				//�s��̊i�[��
	DirectX::XMStoreFloat4x4(&fMat, mat);	//XMFLOAT4X4�ɕϊ�
	m_pHammerGeo->SetWorld(fMat);			//���[���h���W�ɃZ�b�g
	m_pHammerGeo->SetView(pCamera->GetViewMatrix());
	m_pHammerGeo->SetProjection(pCamera->GetProjectionMatrix());

	m_pHammerGeo->Draw();
}

/* ========================================
   �t���O�̃Q�b�g�֐�
   ----------------------------------------
   ���e�F�n���}�[��U���Ă����Ԃ��擾����
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�Fbool
   ======================================== */
bool CHammer::Gethammer()
{
	return m_bHammer;
}

/* ========================================
   �n���}�[�̉�]�֐�
   ----------------------------------------
   ���e�F�n���}�[�̉�]�ɂ��ړ��̏���
   ----------------------------------------
   ����1�F�v���C���[�̃|�W�V����
   ����2�F�v���C���[�̌����Ă�p�x
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CHammer::Swing(TPos3d<float> pPos, float angle)
{
	m_bHammer = true;		//�n���}�[�̎g�p�t���O��ON
	m_stateangle = angle;	//-2.5f ;	//�U��n�߂̊p�x	

	m_nowangle -= ANGULAR_ANGLE;				//���݂̊p�x�ʂ���ړ�����p�x�̕��ړ�
	float azimuth = m_stateangle + m_nowangle; // ���ʊp�i�p�x�j
	float inclination = 1.0f; // �p
	azimuth -= inclination;
	// ���ʍ��W���璼�����W�n�ւ̕ϊ�
	m_pos.x = pPos.x + ROTATE_RADIUS * sin(azimuth);

	//m_pos.y = pPos.y + ROTATE_RADIUS * cos(inclination);	//���Ԃ�^���ɐU��̂�Y���W�͓������Ȃ��̂ŃR�����g�A�E�g /�R�����C
	m_pos.z = pPos.z + ROTATE_RADIUS * cos(azimuth);

	m_sphere.pos = m_pos;		//�����蔻��p�̋��̂ɍ��W���R�s�[
}

/* ========================================
   Sphere�̃Q�b�g�֐�
   ----------------------------------------
   ���e�FSphere��Ԃ�����
   ----------------------------------------
   ����1�F�Ȃ�
   ----------------------------------------
   �ߒl�F�����蔻��̋���
   ======================================== */
CSphereInfo::Sphere CHammer::GetSphere()
{
	return m_sphere;
}
