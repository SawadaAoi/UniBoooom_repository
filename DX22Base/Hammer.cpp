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
	�E2023/11/08 �R�����g�ǉ� yamashita
	�E2023/11/08 �ł������̕ϐ��̓����o�C�j�V�����C�U�ŏ����� yamashita
	�E2023/11/08 �萔HALF_PI�AANGULAR_ANGLE�AROTATE_RADIUS���` yamashita
	�E2023/11/08 Update�ɏ�����Ă���������Swing�֐��ɕ������@yamashita
	�E2023/11/08 ���I�m�ۂ����|�C���^��delete����SAFE_DELETE�ɕύX�@yamashita
	�E2023/11/09 �����蔻��p��Sphere�̃Q�b�g�֐���ǉ� yamashita
	�E2023/11/11 parameter�p�w�b�_�ǉ� suzumura
	�E2023/11/14 �S�̓I�ɏ����̗��ꂪ������Â炩�����̂ŏC�� Sawada

========================================== */

// =============== �C���N���[�h ===================
#include "hammer.h"				// ���g�̃w�b�_
#include "Sphere.h"				// ���̂̏��p�w�b�_
#include "GameParameter.h"		// �萔��`�p�w�b�_�[

// =============== �萔��` =======================
const float ADJUST_DIRECTX_TO_COSINE = DirectX::XMConvertToRadians(90.0f);	// �O�p�֐���DirectX�p�x�̍���(DirectX�̊p�x�́���0�x�A�O�p�֐��́���0�x)
const float ONE_FRAME_ADD_ANGLE = SWING_ANGLE / SWING_TIME_FRAME;			// 1�t���[���ňړ�����p�x��


#if MODE_GAME_PARAMETER
#else
const float SWING_ANGLE			= DirectX::XMConvertToRadians(90.0f);	// �n���}�[��U��͈�(��`�̊p�x�̑傫��)
const float SWING_TIME_FRAME	= 0.15f * 60;							// �n���}�[��U�鎞��(�t���[���P��)
const float ROTATE_RADIUS		= 1.0f;									// �n���}�[����]����v���C���[����̋���
const float HAMMER_COL_SIZE		= 0.75f;								// �n���}�[�̓����蔻��̑傫��
const float HAMMER_SIZE			= 1.5f;									// �n���}�[�̑傫��
#endif

/* ========================================
   �R���X�g���N�^�֐�
   ----------------------------------------
   ���e�F�������ɍs������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
CHammer::CHammer()
	: m_pos{ 0.0f,0.0f,0.0f }
	, m_scale{ HAMMER_SIZE,HAMMER_SIZE,HAMMER_SIZE }
	, m_pHammerGeo(nullptr)
	, m_tPlayerPos(0.0f,0.0f,0.0f)
	, m_fAngleNow(0)
	, m_dAddAngleCnt(0)

{
	m_pHammerGeo = new CSphere();							//�n���}�[�����\������W�I���g���[
	m_sphere.pos = {0.0f, 0.0f, 0.0f};
	m_sphere.radius = HAMMER_COL_SIZE;


}

/* ========================================
   �f�X�g���N�^�֐�
   ----------------------------------------
   ���e�F�j�����ɍs������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
CHammer::~CHammer()
{
	SAFE_DELETE(m_pHammerGeo);
}

/* ========================================
   �X�V�֐�
   ----------------------------------------
   ���e�F�X�V���s��
   ----------------------------------------
   ����1�F�Ȃ�
   ----------------------------------------
   �ߒl�F�n���}�[�̗L������
   ======================================== */
bool CHammer::Update()
{
	Swing();	//��]�ɂ��ړ��֐�

	// �ݒ�l�܂ňړ�����������
	if (m_dAddAngleCnt >= SWING_TIME_FRAME)
	{
		m_dAddAngleCnt = 0;		// �p�x�ύX�t���[���J�E���g���Z�b�g
		
		return false;
	}
	// �ړ�����true��Ԃ�
	else
	{
		return true;
	}
}

/* ========================================
   �`��֐�
   ----------------------------------------
   ���e�F�`����s��
   ----------------------------------------
   �����FCamera�N���X�̃|�C���^
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CHammer::Draw(const CCamera* pCamera)
{
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);	// �n���}�[�̍��W���ړ��̍s��Ɋi�[
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);// �g��k���s��

	DirectX::XMMATRIX mat = S * T;			//�ړ��̍s����i�[
	mat = DirectX::XMMatrixTranspose(mat);	//�]�u
	DirectX::XMFLOAT4X4 fMat;				//�s��̊i�[��
	DirectX::XMStoreFloat4x4(&fMat, mat);	//XMFLOAT4X4�ɕϊ�
	m_pHammerGeo->SetWorld(fMat);			//���[���h���W�ɃZ�b�g
	m_pHammerGeo->SetView(pCamera->GetViewMatrix());
	m_pHammerGeo->SetProjection(pCamera->GetProjectionMatrix());

	m_pHammerGeo->Draw();
}



/* ========================================
   �n���}�[��]�֐�
   ----------------------------------------
   ���e�F�n���}�[�̉�]�ɂ��ړ��̏���
   ----------------------------------------
   ����1�F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CHammer::Swing()
{
	m_fAngleNow -= ONE_FRAME_ADD_ANGLE;	// �n���}�[�����蔻��p�x�ړ�		

	// �p�x������W���擾(�v���C���[�̈ʒu�{�����{�v���C���[�̎���̉~��̈ʒu)
	m_pos.x = m_tPlayerPos.x + ROTATE_RADIUS * -cosf(m_fAngleNow);	// �O�p�֐�(�����v���)��DirectX(���v���)�̊p�x�̌������t�Ȃ̂Ŕ��]����
	m_pos.z = m_tPlayerPos.z + ROTATE_RADIUS * sinf(m_fAngleNow);

	m_sphere.pos = m_pos;		//�����蔻��p�̋��̂ɍ��W���R�s�[

	m_dAddAngleCnt++;	// �p�x�ύX�t���[���J�E���g���Z

}

/* ========================================
   �n���}�[�U���J�n�֐�
   ----------------------------------------
   ���e�F�U���������J�n����
   ----------------------------------------
   ����1�F�v���C���[���W
   ����2�F�v���C���[�̌���
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CHammer::AttackStart(TPos3d<float>pPos, float angle)
{
	float StartAngle =
		  angle						// �v���C���[�̌���
		+ ADJUST_DIRECTX_TO_COSINE	// �{�O�p�֐���DirectX�p�x�̍���
		+ (SWING_ANGLE / 2);		// �{�n���}�[��U��p�x�̔���(��`�̉E�[����X�^�[�g�����)

	m_fAngleNow = StartAngle;	// �J�n�p�x���Z�b�g

	m_tPlayerPos = pPos;		// �v���C���[���W���Z�b�g

	// �p�x������W���擾(�v���C���[�̈ʒu�{�����{�v���C���[�̎���̉~��̈ʒu)
	m_pos.x = m_tPlayerPos.x + ROTATE_RADIUS * -cosf(m_fAngleNow);
	m_pos.z = m_tPlayerPos.z + ROTATE_RADIUS * sinf(m_fAngleNow);

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
