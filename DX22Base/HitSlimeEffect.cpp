
/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
  �q�b�g�X���C���G�t�F�N�g����cpp
   ---------------------------------------
   HitSlimeEffect.h

   �쐬�� �A �F��

   �ύX����
	�E2024/01/25 HitSlimeEffect�N���X�쐬 Tei
	�E2024/02/01 �\���̕s����C�� sawada

========================================== */

// =============== �C���N���[�h ===================
#include "HitSlimeEffect.h"

// =============== �萔��` =======================
const float HIT_EFFECT_STANDARD_ONE_FRAME = 0.8f * 60.0f;
const float HIT_EFFECT_SIZE = 0.6f;

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�R���X�g���N�^
	-------------------------------------
	����1�F�������W(x,y,z)
	����2�F��������
	����3�F�q�b�g��Effekseer
	����4�F�J����
	-------------------------------------
	�ߒl�F����
=========================================== */
CHitSlimeEffect::CHitSlimeEffect(TPos3d<float> fPos, float fTime, Effekseer::EffectRef hitEffect, const CCamera * pCamera)
	: m_pCamera(nullptr)
	, m_bDelFlg(false)
	, m_fEffectTime(fTime)
	, m_nDelFrame(0)
{
	//�q�b�g�G�t�F�N�g������
	m_fEffectTime = fTime;		//�G�t�F�N�g�̑�����		
	m_Transform.fPos = fPos;	//�G�t�F�N�g�̈ʒu
	m_hitEffect = hitEffect;	//�G�t�F�N�g��Effekseer�t�@�C��
	m_efcHitHandle = LibEffekseer::GetManager()->Play(m_hitEffect, 	//�G�t�F�N�g�̊J�n
		m_Transform.fPos.x,
		m_Transform.fPos.y,
		m_Transform.fPos.z);
	LibEffekseer::GetManager()->SetScale(m_efcHitHandle, HIT_EFFECT_SIZE, HIT_EFFECT_SIZE, HIT_EFFECT_SIZE);	//�G�t�F�N�g�T�C�Y�ݒ�
	LibEffekseer::GetManager()->SetSpeed(m_efcHitHandle, m_fEffectTime / HIT_EFFECT_STANDARD_ONE_FRAME );		//�G�t�F�N�g�Đ����x�ݒ�
	m_pCamera = pCamera;

	//�G�t�F�N�g�̕`��(��x�J�����̕`������Ȃ��ƕ\�������������Ȃ��)
	TPos3d<float> cameraPos = m_pCamera->GetPos();							//�J�������W���擾
	DirectX::XMFLOAT3 fCameraPos(cameraPos.x, cameraPos.y, cameraPos.z);	//XMFLOAT3�ɕϊ�
	LibEffekseer::SetViewPosition(fCameraPos);								//�J�������W���Z�b�g
	LibEffekseer::SetCameraMatrix(m_pCamera->GetViewWithoutTranspose(), m_pCamera->GetProjectionWithoutTranspose());	//�]�u�O��view��projection���Z�b�g

}

/* ========================================
	�f�X�g���N�^�֐�
	-------------------------------------
	���e�F�f�X�g���N�^
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
CHitSlimeEffect::~CHitSlimeEffect()
{
	
}

/* ========================================
	�X�V�֐�
	-------------------------------------
	���e�F�q�b�g�G�t�F�N�g�̍X�V����
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CHitSlimeEffect::Update()
{
	DisplayTimeAdd();	//	�q�b�g�G�t�F�N�g�Đ����ԉ��Z
}

/* ========================================
	�`��֐�
	-------------------------------------
	���e�F�q�b�g�G�t�F�N�g�̕`�揈��
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CHitSlimeEffect::Draw()
{
	//�G�t�F�N�g�̕`��
	TPos3d<float> cameraPos = m_pCamera->GetPos();							//�J�������W���擾
	DirectX::XMFLOAT3 fCameraPos(cameraPos.x, cameraPos.y, cameraPos.z);	//XMFLOAT3�ɕϊ�
	LibEffekseer::SetViewPosition(fCameraPos);								//�J�������W���Z�b�g
	LibEffekseer::SetCameraMatrix(m_pCamera->GetViewWithoutTranspose(), m_pCamera->GetProjectionWithoutTranspose());	//�]�u�O��view��projection���Z�b�g
}

/* ========================================
	�q�b�g�G�t�F�N�g�\���J�E���g���Z�����֐�
	-------------------------------------
	���e�F�q�b�g�G�t�F�N�g�\���J�E���g�����Z���čĐ��b���o������I���t���O���I���ɂ���
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CHitSlimeEffect::DisplayTimeAdd()
{
	m_nDelFrame++;	// �t���[�����Z

	// �Đ��b���o������폜
	if (m_fEffectTime <= m_nDelFrame)
	{
		m_bDelFlg = true;	// �폜�t���O�𗧂Ă�
	}
}

/* ========================================
	�J�������Z�b�g�֐�
	----------------------------------------
	���e�F�`�揈���Ŏg�p����J�������Z�b�g
	----------------------------------------
	����1�F�J�����|�C���^
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CHitSlimeEffect::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;
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
bool CHitSlimeEffect::GetDelFlg()
{
	return m_bDelFlg;
}
