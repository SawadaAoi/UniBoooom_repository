/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
  �v���C���[�ړ��G�t�F�N�g����cpp
   ---------------------------------------
   WalkEffect.cpp

   �쐬�� �A �F��

   �ύX����
	�E2024/01/30 WalkEffect�N���X�쐬 Tei
	�E2024/02/13 UsingCamera�g�p takagi

========================================== */

// =============== �萔��` =======================
const float WALK_EFFECT_STANDARD_ONE_FRAME = 0.1f * 60.0f;
const float WALK_EFFECT_SIZE = 0.9f;
const float WALK_EFFECT_HEIGHT = 0.5f;
const int	WALK_EFFECT_ALPHA = 3;	// �G�t�F�N�g�̔Z��(���X�������̂ŏd�˂ĕ\��)

// =============== �C���N���[�h ===================
#include "WalkEffect.h"
#include <time.h>
#include "UsingCamera.h"	//�J�����g�p

/* ========================================
	�֐��F�R���X�g���N�^
	-------------------------------------
	���e�F���s���ɍs������
	-------------------------------------
	����1�F�v���C���[��	�g�����X�t�H�[��
	����2�F�G�t�F�N�g�̑�����
	����3�F�ʒu�����p����
	����4�F�G�t�F�N�g��effekseer�t�@�C��
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CWalkEffect::CWalkEffect(tagTransform3d tTransForm, int nDelFrame, float fPosRan, Effekseer::EffectRef walkEffect)
	: m_bDelFlg(false)
	, m_nDelFrame(0)
	, m_fDispMaxFlame(nDelFrame)
{
	//�v���C���[�ړ��G�t�F�N�g������
	m_walkEffect = walkEffect;		//�G�t�F�N�g��Effekseer�t�@�C��
	
	//�ړ��G�t�F�N�g�̉���Z�����邽�߂ɁA�����Ƃ����3�񐶐�����
	for (int j = 0; j < WALK_EFFECT_ALPHA; j++)
	{
		m_efcWalkHandle = LibEffekseer::GetManager()->Play(
			m_walkEffect, tTransForm.fPos.x + fPosRan, tTransForm.fPos.y + WALK_EFFECT_HEIGHT, tTransForm.fPos.z + fPosRan);

		LibEffekseer::GetManager()->SetScale(m_efcWalkHandle,
			WALK_EFFECT_SIZE,
			WALK_EFFECT_SIZE,
			WALK_EFFECT_SIZE);	//�G�t�F�N�g�T�C�Y�ݒ�

		LibEffekseer::GetManager()->SetSpeed(m_efcWalkHandle, WALK_EFFECT_STANDARD_ONE_FRAME * 0.05f);			//�G�t�F�N�g�Đ����x�ݒ�
	}

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
	TPos3d<float> cameraPos = CUsingCamera::GetThis().GetCamera()->GetPos();							//�J�������W���擾
	DirectX::XMFLOAT3 fCameraPos(cameraPos.x, cameraPos.y, cameraPos.z);	//XMFLOAT3�ɕϊ�
	LibEffekseer::SetViewPosition(fCameraPos);								//�J�������W���Z�b�g
	LibEffekseer::SetCameraMatrix(CUsingCamera::GetThis().GetCamera()->GetViewWithoutTranspose(), CUsingCamera::GetThis().GetCamera()->GetProjectionWithoutTranspose());	//�]�u�O��view��projection���Z�b�g
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
	if (m_fDispMaxFlame  <= m_nDelFrame)
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
bool CWalkEffect::GetDelFlg()
{
	return m_bDelFlg;
}
