/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�v���C���[�ړ��G�t�F�N�g�Ǘ��pcpp
	---------------------------------------
	WalkEffectManager.cpp

	�쐬��	�A �F��

	�ύX����
	�E2024/01/30 WalkEffectManager�N���X�쐬 Tei

========================================== */

// =============== �C���N���[�h ===================
#include "WalkEffectManager.h"

// =============== �萔��` =======================
const float TOTAL_WALK_EFFECT_TIME = 10.0f;

CWalkEffectManager::CWalkEffectManager()
{
	
	// �v���C���[�ړ��G�t�F�N�g�z��̏�����
	for (int i = 0; i < MAX_STEP_NUM; i++)
	{
		m_pwalkEffect[i] = nullptr;
	}

	//�G�t�F�N�g������
	m_walkEffect = LibEffekseer::Create("Assets/Effect/walk_effect/step_smoke.efkefc");
}

CWalkEffectManager::~CWalkEffectManager()
{
	// �������폜
	for (int i = 0; i < MAX_STEP_NUM; i++)
	{
		SAFE_DELETE(m_pwalkEffect[i]);
	}
}

void CWalkEffectManager::Draw()
{
	// �q�b�g�G�t�F�N�g�̌���
	for (int i = 0; i < MAX_STEP_NUM; i++)
	{
		// ���g�p�̃v���C���[�ړ��G�t�F�N�g�̓X���[
		if (m_pwalkEffect[i] == nullptr) continue;

		m_pwalkEffect[i]->Draw(); // �v���C���[�ړ��G�t�F�N�g�̕`��

		break;
	}
}

void CWalkEffectManager::Update()
{
	// �v���C���[�ړ��G�t�F�N�g������
	for (int i = 0; i < MAX_STEP_NUM; i++)
	{
		// ���g�p�̃v���C���[�ړ��G�t�F�N�g�̓X���[
		if (m_pwalkEffect[i] == nullptr) continue;
		m_pwalkEffect[i]->Update();
		
	}
	DeleteCheck();	// �폜�`�F�b�N
	
}

CWalkEffect * CWalkEffectManager::GetWalkPtr(int num)
{
	if (!m_pwalkEffect[num]) { return nullptr; }
	return m_pwalkEffect[num];
}

void CWalkEffectManager::Create(TTriType<float> pos)
{
	// �v���C���[�ړ��G�t�F�N�g������
	for (int i = 0; i < MAX_STEP_NUM; i++)
	{
		// �g�p�ς݂̃v���C���[�ړ��G�t�F�N�g�̓X���[
		if (m_pwalkEffect[i] != nullptr) continue;

		// ���W�A�G�t�F�N�g���ԁAEffekseer�t�@�C���A�J�������w�肵�Đ���
		m_pwalkEffect[i] = new CWalkEffect(pos, TOTAL_WALK_EFFECT_TIME, m_walkEffect, m_pCamera);
		m_pwalkEffect[i]->SetCamera(m_pCamera);		//�J�����Z�b�g
		break;
	}
}

void CWalkEffectManager::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;
}

void CWalkEffectManager::DeleteCheck()
{
	// �v���C���[�ړ��G�t�F�N�g������
	for (int i = 0; i < MAX_STEP_NUM; i++)
	{
		// ���g�p�̃v���C���[�ړ��G�t�F�N�g�̓X���[
		if (m_pwalkEffect[i] == nullptr) continue;
		// �폜�t���O�������ĂȂ��v���C���[�ړ��G�t�F�N�g�̓X���[
		if (m_pwalkEffect[i]->GetDelFlg() == false) continue;

		delete m_pwalkEffect[i]; m_pwalkEffect[i] = nullptr;	// �v���C���[�ړ��G�t�F�N�g���폜����

	}
}
