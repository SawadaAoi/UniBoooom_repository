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

========================================== */

// =============== �C���N���[�h ===================
#include "UnionSmokeEffectManager.h"

// =============== �萔��` ===================
const std::map<int, std::string> MAP_TEX_PATH = {
	{CUnionSmokeEffectManager::GREEN_SMOKE,		"Assets/Effect/Union/green_v1.png"},		// �������̉摜�i�΁j
	{CUnionSmokeEffectManager::YELLOW_SMOKE,	"Assets/Effect/Union/yellow_v1.png"},		// �������̉摜�i���j
	{CUnionSmokeEffectManager::RED_SMOKE,		"Assets/Effect/Union/red_v1.png"},			// �������̉摜�i�ԁj
	
};
const int	EFFECT_SPEED = 0.02 * 60;		// �G�t�F�N�g�Đ��X�s�[�h

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
	����2�F�����T�C�Y(x,y,z)
	����3�F�X���C���̃��x��(�΁A���A��)
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CUnionSmokeEffectManager::Create(TPos3d<float> fpos, TPos3d<float> fsize, int slimelevel)
{
	// �����G�t�F�N�g������
	for (int i = 0; i < MAX_UNION_SMOKE_NUM; i++)
	{
		// �g�p�ς݂̌����G�t�F�N�g�̓X���[
		if (m_pUnionSmokeEffect[i] != nullptr) continue;

		// ���W�A�傫���A�g�p�̃e�N�X�`���A�J�������w�肵�Đ���
		m_pUnionSmokeEffect[i] = new CUnionSmokeEffect(fpos, fsize, m_pTexture[slimelevel - 1], m_pCamera);

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

		delete m_pUnionSmokeEffect[i]; m_pUnionSmokeEffect[i] = nullptr;	// �����G�t�F�N�g���폜����

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
