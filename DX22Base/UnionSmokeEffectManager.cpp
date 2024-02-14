/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�����G�t�F�N�g�}�l�[�W���\
	---------------------------------------
	UnionSmokeEffectManager.cpp

	�쐬��
			Tei

	�ύX����
	�E2024/02/06 �N���X�쐬 Tei
	�E2024/02/08 �G�t�F�N�g�T�C�Y��萔�ɏC�� sawada

========================================== */

// =============== �C���N���[�h ===================
#include "UnionSmokeEffectManager.h"

// =============== �萔��` ===================
const std::map<int, std::string> MAP_TEX_PATH = {
	{CUnionSmokeEffectManager::GREEN_SMOKE,		"Assets/Effect/Union/greenW_v2.png"},		// �������̉摜�i�΁j
	{CUnionSmokeEffectManager::YELLOW_SMOKE,	"Assets/Effect/Union/yellowW_v2.png"},		// �������̉摜�i���j
	{CUnionSmokeEffectManager::RED_SMOKE,		"Assets/Effect/Union/RedW_v2.png"},			// �������̉摜�i�ԁj
};

// �G�t�F�N�g�̃T�C�Y
const TPos3d<float> UNION_SMOKE_EFFECT_SIZE[CUnionSmokeEffectManager::SMOKE_MAX] =
{
	{5.0f, 5.0f, 5.0f},			// �X���C�����m
	{7.0f, 7.0f, 7.0f,},		// �΃X���C�����m
	{10.0f, 10.0f, 10.0f},		// ���X���C�����m
};


/* ========================================
	�֐��F�R���X�g���N�^
	-------------------------------------
	���e�F���s���ɍs������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CUnionSmokeEffectManager::CUnionSmokeEffectManager()
{
	for (int i = 0; i < E_SMOKE::SMOKE_MAX; i++)
	{
		// ���U���g�摜�Ǎ�
		m_pTexture[i] = new Texture();
		if (FAILED(m_pTexture[i]->Create(MAP_TEX_PATH.at(i).c_str())))
		{
			MessageBox(NULL, "Union Smoke Texture", "Error", MB_OK);
		}
	}

	for (int i = 0; i < MAX_UNION_SMOKE_NUM; i++)
	{
		m_pUnionSmokeEffect[i] = nullptr;
	}
}

/* ========================================
	�֐��F�f�X�g���N�^
	-------------------------------------
	���e�F�j�����ɍs������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CUnionSmokeEffectManager::~CUnionSmokeEffectManager()
{
	// �������폜
	for (int i = 0; i < E_SMOKE::SMOKE_MAX; i++)
	{
		SAFE_DELETE(m_pTexture[i]);
	}

	// �������폜
	for (int i = 0; i < MAX_UNION_SMOKE_NUM; i++)
	{
		SAFE_DELETE(m_pUnionSmokeEffect[i]);
	}
}

/* ========================================
	���������֐�
	-------------------------------------
	���e�F�����G�t�F�N�g�̐���
	-------------------------------------
	����1�F�������W(x,y,z)
	����2�F�X���C���̃��x��(�΁A���A��)
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CUnionSmokeEffectManager::Create(TPos3d<float> fpos, int slimelevel)
{
	// �����G�t�F�N�g������
	for (int i = 0; i < MAX_UNION_SMOKE_NUM; i++)
	{
		// �g�p�ς݂̌����G�t�F�N�g�̓X���[
		if (m_pUnionSmokeEffect[i] != nullptr) continue;

		// ���W�A�傫���A�g�p�̃e�N�X�`���A�J�������w�肵�Đ���
		m_pUnionSmokeEffect[i] = new CUnionSmokeEffect(fpos, UNION_SMOKE_EFFECT_SIZE[slimelevel - 1], m_pTexture[slimelevel - 1], m_pCamera);

		return;
	}
}

/* ========================================
	�X�V�����֐�
	-------------------------------------
	���e�F�����G�t�F�N�g�}�l�[�W���[�̍X�V����
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CUnionSmokeEffectManager::Update()
{
	// �����G�t�F�N�g������
	for (int i = 0; i < MAX_UNION_SMOKE_NUM; i++)
	{
		// ���g�p�̌����G�t�F�N�g�̓X���[
		if (m_pUnionSmokeEffect[i] == nullptr) continue;
		m_pUnionSmokeEffect[i]->Update();
	}
	DeleteCheck();
}

/* ========================================
	�֐��F�`��֐�
	----------------------------------------
	���e�F�����G�t�F�N�g�}�l�[�W���[�̕`�揈��
	----------------------------------------
	�����F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CUnionSmokeEffectManager::Draw()
{
	// Union�G�t�F�N�g�̌���
	for (int i = 0; i < MAX_UNION_SMOKE_NUM; i++)
	{
		// ���g�p��Union�G�t�F�N�g�̓X���[
		if (m_pUnionSmokeEffect[i] == nullptr) continue;

		m_pUnionSmokeEffect[i]->Draw(); // Union�G�t�F�N�g�̕`��

	}
}

/* ========================================
	�����G�t�F�N�g�폜�֐�
	----------------------------------------
	���e�F�����G�t�F�N�g������������`�F�b�N���Ă���폜
	----------------------------------------
	�����F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CUnionSmokeEffectManager::DeleteCheck()
{
	// �����G�t�F�N�g������
	for (int i = 0; i < MAX_UNION_SMOKE_NUM; i++)
	{
		// ���g�p�̌����G�t�F�N�g�̓X���[
		if (m_pUnionSmokeEffect[i] == nullptr) continue;
		// �폜�t���O�������ĂȂ������G�t�F�N�g�̓X���[
		if (m_pUnionSmokeEffect[i]->GetDelFlg() == false) continue;

		SAFE_DELETE(m_pUnionSmokeEffect[i]);	// �����G�t�F�N�g���폜����

	}
}

/* ========================================
	�J�������Z�b�g�֐�
	----------------------------------------
	���e�F�`�揈���Ŏg�p����J�������Z�b�g
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CUnionSmokeEffectManager::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;
}
