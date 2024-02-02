/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
  �v���C���[�ړ��G�t�F�N�g����cpp
   ---------------------------------------
   WalkEffect.cpp

   �쐬�� �A �F��

   �ύX����
	�E2024/01/30 WalkEffect�N���X�쐬 Tei

========================================== */

// =============== �萔��` =======================
const float WALK_EFFECT_STANDARD_ONE_FRAME = 0.1f * 60.0f;
const float WALK_EFFECT_SIZE = 0.9f;

// =============== �C���N���[�h ===================
#include "WalkEffect.h"
#include <time.h>

/* ========================================
	�֐��F�R���X�g���N�^
	-------------------------------------
	���e�F���s���ɍs������
	-------------------------------------
	����1�F�v���C�C���[�̈ʒu
	����2�F�v���C���[17�t���[���O�̈ʒu
	����3�F�v���C���[25�t���\���O�̈ʒu
	����4�F�v���C���[�̊p�x
	����5�F�G�t�F�N�g�̑�����
	����6�F�ʒu�ƃT�C�Y�����p����
	����7�F�G�t�F�N�g��effekseer�t�@�C��
	����8�F�J�����|�C���^
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CWalkEffect::CWalkEffect(TPos3d<float> fPos, TPos3d<float> fOldPos15, TPos3d<float> fOldPos30, TPos3d<float> fRadian, float fTime, float fNum, Effekseer::EffectRef walkEffect, const CCamera * pCamera)
	: m_bDelFlg(false)
	, m_nDelFrame(0)
	, m_pCamera(nullptr)
	, m_fEffectTime(fTime)
	, m_fRandNum(fNum)
{
	//�v���C���[�ړ��G�t�F�N�g������
	m_fEffectTime = fTime;			//�G�t�F�N�g�̑�����		
	m_OldTransform17f.fPos = fOldPos15;	//�v���C���[15�t���[���O�̈ʒu
	m_OldTransform25f.fPos = fOldPos30; //�v���C���[30�t���[���O�̈ʒu
	m_Transform.fPos = fPos;		//�v���C���[�̈ʒu
	m_Transform.fRadian = fRadian;	//�G�t�F�N�g�̊p�x
	m_walkEffect = walkEffect;		//�G�t�F�N�g��Effekseer�t�@�C��
	
	m_pCamera = pCamera;
	//�ړ��G�t�F�N�g�̉���Z�����邽�߂ɁA�����Ƃ����3�񐶐�����
	for (int i = 0; i < 3; i++)
	{
		LibEffekseer::GetManager()->Play(m_walkEffect, m_OldTransform17f.fPos.x+ m_fRandNum, m_OldTransform17f.fPos.y + 0.2f, m_OldTransform17f.fPos.z + m_fRandNum);
		LibEffekseer::GetManager()->Play(m_walkEffect, m_OldTransform25f.fPos.x, m_OldTransform25f.fPos.y + 0.15f, m_OldTransform25f.fPos.z);
		LibEffekseer::GetManager()->SetScale(m_efcWalkHandle, WALK_EFFECT_SIZE + m_fRandNum, WALK_EFFECT_SIZE + m_fRandNum, WALK_EFFECT_SIZE + m_fRandNum);	//�G�t�F�N�g�T�C�Y�ݒ�
	}
	LibEffekseer::GetManager()->SetSpeed(m_efcWalkHandle, WALK_EFFECT_STANDARD_ONE_FRAME / m_fEffectTime);			//�G�t�F�N�g�Đ����x�ݒ�
	LibEffekseer::GetManager()->SetRotation(m_efcWalkHandle, m_Transform.fRadian.x, m_Transform.fRadian.y, m_Transform.fRadian.z);	//�G�t�F�N�g�̉�]��ݒ�

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
CWalkEffect::~CWalkEffect()
{
}

/* ========================================
	�X�V�֐�
	-------------------------------------
	���e�F�ړ��G�t�F�N�g�̍X�V����
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CWalkEffect::Update()
{
	DisplayTimeAdd();	// �ړ��G�t�F�N�g�Đ����ԉ��Z
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
void CWalkEffect::Draw()
{
	//�G�t�F�N�g�̕`��
	TPos3d<float> cameraPos = m_pCamera->GetPos();							//�J�������W���擾
	DirectX::XMFLOAT3 fCameraPos(cameraPos.x, cameraPos.y, cameraPos.z);	//XMFLOAT3�ɕϊ�
	LibEffekseer::SetViewPosition(fCameraPos);								//�J�������W���Z�b�g
	LibEffekseer::SetCameraMatrix(m_pCamera->GetViewWithoutTranspose(), m_pCamera->GetProjectionWithoutTranspose());	//�]�u�O��view��projection���Z�b�g
}

/* ========================================
	�ړ��G�t�F�N�g�\���J�E���g���Z�����֐�
	-------------------------------------
	���e�F�ړ��G�t�F�N�g�\���J�E���g�����Z���čĐ��b���o������I���t���O���I���ɂ���
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CWalkEffect::DisplayTimeAdd()
{
	m_nDelFrame++;	// �t���[�����Z

// �Đ��b���o������폜
	if (m_fEffectTime  <= m_nDelFrame)
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
void CWalkEffect::SetCamera(const CCamera * pCamera)
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
bool CWalkEffect::GetDelFlg()
{
	return m_bDelFlg;
}
