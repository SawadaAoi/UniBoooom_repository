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
const float WALK_EFFECT_STANDARD_ONE_FRAME = 0.4f * 60.0f;
const float WALK_EFFECT_SIZE = 0.8f;

// =============== �C���N���[�h ===================
#include "WalkEffect.h"
#include <time.h>

CWalkEffect::CWalkEffect(TPos3d<float> fPos, TPos3d<float> fRadian, float fTime, float fSize, Effekseer::EffectRef walkEffect, const CCamera * pCamera)
	: m_bDelFlg(false)
	, m_nDelFrame(0)
	, m_pCamera(nullptr)
	, m_fEffectTime(fTime)
	, m_fRandSize(0.0f)
{
	//�v���C���[�ړ��G�t�F�N�g������
	m_fEffectTime = fTime;		//�G�t�F�N�g�̑�����		
	m_Transform.fPos = fPos;	//�G�t�F�N�g�̈ʒu
	m_walkEffect = walkEffect;	//�G�t�F�N�g��Effekseer�t�@�C��
	m_fRandSize = fSize;
	m_Transform.fRadian = fRadian;

	m_pCamera = pCamera;
	for (int i = 0; i < 5; i++)
	{
		LibEffekseer::GetManager()->Play(m_walkEffect, m_Transform.fPos.x+ m_fRandSize, m_Transform.fPos.y + 0.2f, m_Transform.fPos.z + m_fRandSize);
		LibEffekseer::GetManager()->SetRotation(m_efcWalkHandle, m_Transform.fRadian.x, m_Transform.fRadian.y, m_Transform.fRadian.z);
		LibEffekseer::GetManager()->SetSpeed(m_efcWalkHandle, WALK_EFFECT_STANDARD_ONE_FRAME / m_fEffectTime);			//�G�t�F�N�g�Đ����x�ݒ�
		LibEffekseer::GetManager()->SetScale(m_efcWalkHandle, WALK_EFFECT_SIZE + m_fRandSize, WALK_EFFECT_SIZE + m_fRandSize, WALK_EFFECT_SIZE + m_fRandSize);	//�G�t�F�N�g�T�C�Y�ݒ�

	}
	
}

CWalkEffect::~CWalkEffect()
{
}

void CWalkEffect::Update()
{
	DisplayTimeAdd();
}

void CWalkEffect::Draw()
{
	//�G�t�F�N�g�̕`��
	TPos3d<float> cameraPos = m_pCamera->GetPos();							//�J�������W���擾
	DirectX::XMFLOAT3 fCameraPos(cameraPos.x, cameraPos.y, cameraPos.z);	//XMFLOAT3�ɕϊ�
	LibEffekseer::SetViewPosition(fCameraPos);								//�J�������W���Z�b�g
	LibEffekseer::SetCameraMatrix(m_pCamera->GetViewWithoutTranspose(), m_pCamera->GetProjectionWithoutTranspose());	//�]�u�O��view��projection���Z�b�g
}

void CWalkEffect::DisplayTimeAdd()
{
	m_nDelFrame++;	// �t���[�����Z

// �Đ��b���o������폜
	if (m_fEffectTime * 0.75f <= m_nDelFrame)
	{
		m_bDelFlg = true;	// �폜�t���O�𗧂Ă�
	}

}


void CWalkEffect::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;
}

bool CWalkEffect::GetDelFlg()
{
	return m_bDelFlg;
}
