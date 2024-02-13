/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
  ���G�t�F�N�g�N���X ����
   ---------------------------------------
   SweatEffect.cpp

   �쐬�� �A �F��

   �ύX����
	�E2024/02/02 HitSlimeEffect�N���X�쐬 Tei
	�E2024/02/13 UsingCamera�g�p takagi

========================================== */

// =============== �C���N���[�h ===================
#include "SweatEffect.h"
#include "UsingCamera.h"	//�J�����g�p

// =============== �萔��` =======================
const float SWEAT_EFFECT_STANDARD_ONE_FRAME = 0.467f * 60.0f;	
const float SWEAT_EFFECT_SIZE = 0.5f;			// �G�t�F�N�g�T�C�Y
const float SWEAT_EFFECT_SPEED = 1.3f;


/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�F���W
	����2�F�p�x
	����3�F�G�t�F�N�g������
	����4�F�G�t�F�N�g�t�@�C��
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CSweatEffect::CSweatEffect(TPos3d<float> fPos, TPos3d<float> fRadian, float fTime, Effekseer::EffectRef sweatEffect)
	: m_fEffectTime(fTime)
	, m_bDelFlg(false)
	, m_nDelFrame(0)
{
	// �G�t�F�N�g������
	m_Transform.fPos = fPos;
	m_Transform.fRadian = fRadian;
	m_SweatEffect = sweatEffect;
	m_efcSweatHnadle = LibEffekseer::GetManager()->Play(m_SweatEffect, m_Transform.fPos.x, m_Transform.fPos.y + 6.5f, m_Transform.fPos.z);	// �G�t�F�N�g�̊J�n
	LibEffekseer::GetManager()->SetScale(m_efcSweatHnadle, SWEAT_EFFECT_SIZE, SWEAT_EFFECT_SIZE , SWEAT_EFFECT_SIZE);	// �G�t�F�N�g�̃T�C�Y��ݒ�
 	LibEffekseer::GetManager()->SetRotation(m_efcSweatHnadle, m_Transform.fRadian.x ,90.0f, m_Transform.fRadian.z);		// Y��90�x�ŌŒ肷��
	LibEffekseer::GetManager()->SetSpeed(m_efcSweatHnadle, SWEAT_EFFECT_SPEED);
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
CSweatEffect::~CSweatEffect()
{
	LibEffekseer::GetManager()->StopEffect(m_efcSweatHnadle);
}

/* ========================================
	�X�V�֐�
	----------------------------------------
	���e�F�X�V����
	----------------------------------------
	����1�F���W
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CSweatEffect::Update(TPos3d<float> fPos)
{
	m_Transform.fPos = fPos;
	LibEffekseer::GetManager()->SetLocation(m_efcSweatHnadle, m_Transform.fPos.x, m_Transform.fPos.y + 6.5f, m_Transform.fPos.z);
	DisplayTimeAdd();
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
void CSweatEffect::Draw()
{
	//�G�t�F�N�g�̕`��
	TPos3d<float> cameraPos = CUsingCamera::GetThis().GetCamera()->GetPos();							//�J�������W���擾
	DirectX::XMFLOAT3 fCameraPos(cameraPos.x, cameraPos.y, cameraPos.z);	//XMFLOAT3�ɕϊ�
	LibEffekseer::SetViewPosition(fCameraPos);								//�J�������W���Z�b�g
	LibEffekseer::SetCameraMatrix(CUsingCamera::GetThis().GetCamera()->GetViewWithoutTranspose(), CUsingCamera::GetThis().GetCamera()->GetProjectionWithoutTranspose());	//�]�u�O��view��projection���Z�b�g
}

/* ========================================
	���G�t�F�N�g�\���J�E���g���Z�����֐�
	-------------------------------------
	���e�F���G�t�F�N�g�\���J�E���g�����Z���čĐ��b���o������I���t���O���I���ɂ���
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSweatEffect::DisplayTimeAdd()
{
	m_nDelFrame++;	// �t���[�����Z

	// �Đ��b���o������폜
	if (m_fEffectTime <= m_nDelFrame)
	{
		m_bDelFlg = true;	// �폜�t���O�𗧂Ă�
	}
}

/* ========================================
	�폜�t���O�擾�����֐�
	-------------------------------------
	���e�F�폜�t���O���擾����
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F�폜�t���O(bool)
=========================================== */
bool CSweatEffect::GetDelFlg()
{
	return m_bDelFlg;
}
