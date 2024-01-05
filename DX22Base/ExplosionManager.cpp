/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�����Ǘ��pcpp
	---------------------------------------
	ExplosionManager.cpp
	
	�쐬��	�A �F��
	
	�ύX����
	�E2023/11/06 �����}�l�[�W���[�N���X�쐬 Tei
	�E2023/11/06 ���������A�폜�֐��쐬 Tei
	�E2023/11/07 ���������֐����̕ύX�ADeleteExplosin()�̏C�� Tei
	�E2023/11/09 �����z���Ԃ������̒ǉ� Sawada
	�E2023/11/10 ���̃I�u�W�F�N�g�Ɠ���̃J�������Z�b�g����悤�ɂ��� Yamashita
	�E2023/11/13 Create�֐��̈�����time��ǉ� Suzumura
	�E2023/11/18 ��������SE���Đ�����悤�ɕύX Yamahsita
	�E2023/11/19 Create�֐��̈�����damage��ǉ� Suzumura
	�E2023/11/20 �R���{���@�\�ǉ� Sawada
	�E2023/11/21 �R���{���@�\�̈ꕔ���R���{�N���X�Ɉړ� Sawada
	�E2023/11/21 ��������BoooomUI�̕\����ǉ� Tei
	�E2023/12/07 Effekseer.h�̃C���N���[�h�ǉ� Takagi

========================================== */

// =============== �C���N���[�h ===================
#include "ExplosionManager.h"	//���g�̃w�b�_�[
#include "Explosion.h"			//���������w�b�_�[
#include "Sphere.h"				//����`�w�b�_�[
#include "DirectWrite.h"
#include "Input.h"
#include "LibEffekseer.h"

// =============== �萔��` =======================
const float EXPLODE_VOLUME = 0.5f;

/* ========================================
	�֐��F�R���X�g���N�^
	-------------------------------------
	���e�F���s���ɍs������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CExplosionManager::CExplosionManager()
	:m_pSEExplode(nullptr)
	, m_pSEExplodeSpeaker(nullptr)
	, m_pTexUI(nullptr)
{
	// �����z��̏�����
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		m_pExplosion[i] = nullptr;
	}

	m_pTexUI = new Texture();
	// boooomUI�z��̏�����
	for (int i = 0; i < MAX_BOOOOM_NUM; i++)
	{
		m_pBoooomUI[i] = nullptr;
	}
	if (FAILED(m_pTexUI->Create("Assets/Texture/boooom.png")))
	{
		MessageBox(NULL, "boooom.png", "Error", MB_OK);
	}
	//�T�E���h�t�@�C���̓ǂݍ���
	m_pSEExplode = CSound::LoadSound("Assets/Sound/SE/Explode.mp3");

	//�G�t�F�N�g������
	m_explodeEffect = LibEffekseer::Create("Assets/Effect/mega/mega_reverse (2).efkefc");
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
CExplosionManager::~CExplosionManager()
{
	// �������폜
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		SAFE_DELETE(m_pExplosion[i]);
	}
	for (int i = 0; i < MAX_BOOOOM_NUM; i++)
	{
		SAFE_DELETE(m_pBoooomUI[i]);
	}
	SAFE_DELETE(m_pTexUI);
}


/* ========================================
	�X�V�����֐�
	-------------------------------------
	���e�F�����}�l�[�W���[�̍X�V����
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CExplosionManager::Update()
{
	// ����������
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		// ���g�p�̔����̓X���[
		if (m_pExplosion[i] == nullptr)
		{
			continue;

		}

		m_pExplosion[i]->Update();

		if (m_pExplosion[i]->GetSeFlg() == true)
		{
			m_pSEExplodeSpeaker = CSound::PlaySound(m_pSEExplode);	//�����̍Đ�
			m_pSEExplodeSpeaker->SetVolume(EXPLODE_VOLUME);			//���ʒ���
			m_pExplosion[i]->SetSeFlg(false);
		}
		
	}
	for (int i = 0; i < MAX_BOOOOM_NUM; i++)
	{
		//���g�p��BoooomUI�̓X���[
		if (m_pBoooomUI[i] == nullptr) continue;

		m_pBoooomUI[i]->Update();
	}
	DeleteCheck();	// �폜�`�F�b�N
	ComboEndCheck();	// �R���{�̍폜
}

/* ========================================
	�֐��F�`��֐�
	----------------------------------------
	���e�F�����}�l�[�W���[�̕`�揈��
	----------------------------------------
	�����F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CExplosionManager::Draw()
{
	// �����̌���
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		// ���g�p�̔����̓X���[
		if (m_pExplosion[i] == nullptr) continue;

		m_pExplosion[i]->Draw(); // �����̕`��
	}
	// boooomUI�̌���
	for (int i = 0; i < MAX_BOOOOM_NUM; i++)
	{
		//���g�p��BoooomUI�̓X���[
		if (m_pBoooomUI[i] == nullptr) continue;

		m_pBoooomUI[i]->Draw();	// boooomUI�̕`��
	}
}

/* ========================================
	���������֐�
	-------------------------------------
	���e�F�����̐���
	-------------------------------------
	����1�F�������W(x,y,z)
	����2�F�����̑傫��
	����3�F����������
	����4�F�����̃_���[�W
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CExplosionManager::Create(TTriType<float> pos,float size, float time, int damage, E_SLIME_LEVEL level)
{
	int comboNum = m_pCombo->FirstComboSet();		// �R���{�z��̓Y�������擾
	m_pCombo->AddScore(level, comboNum);

	// ����������
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		// �g�p�ς݂̔����̓X���[
		if (m_pExplosion[i] != nullptr) continue;

		m_pExplosion[i] = new CExplosion(pos, size, time, comboNum, true, damage,m_explodeEffect,m_pCamera);	// ���W���w�肵�Đ���
		m_pExplosion[i]->SetCamera(m_pCamera);

		break;

	}	
}

/* ========================================
	���������֐�
	-------------------------------------
	���e�F�����̐���
	-------------------------------------
	����1�F�������W(x,y,z)
	����2�F�����̑傫��
	����3�F����������
	����4�F�R���{�z��Y����
	����5�F�����̃_���[�W
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CExplosionManager::Create(TTriType<float> pos, float size, float time, int comboNum, int damage, E_SLIME_LEVEL level)
{
	m_pCombo->AddCombo(comboNum);	// �Ή�����R���{�z��̒l�����Z����
	m_pCombo->AddScore(level, comboNum);

	// ����������
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		// �g�p�ς݂̔����̓X���[
		if (m_pExplosion[i] != nullptr) continue;

		m_pExplosion[i] = new CExplosion(pos, size, time, comboNum, true, damage, m_explodeEffect, m_pCamera);	// ���W���w�肵�Đ���
		m_pExplosion[i]->SetCamera(m_pCamera);

		return;
	}
}



/* ========================================
	�����폜�֐�
	----------------------------------------
	���e�F��������������`�F�b�N���Ă���폜
	----------------------------------------
	�����F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CExplosionManager::DeleteCheck()
{
	// ����������
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		// ���g�p�̔����̓X���[
		if (m_pExplosion[i] == nullptr) continue;
		// �폜�t���O�������ĂȂ������̓X���[
		if (m_pExplosion[i]->GetDelFlg() == false) continue;

		delete m_pExplosion[i]; m_pExplosion[i] = nullptr;	// �������폜����

	}

	//BoooomUI������
	for (int i = 0; i < MAX_BOOOOM_NUM; i++)
	{
		//���g�p��BoooomUI�̓X���[
		if (m_pBoooomUI[i] == nullptr) continue;
		//�폜�t���O�������ĂȂ�BoooomUI�̓X���[
		if (m_pBoooomUI[i]->GetDelFlg() == false) continue;

		delete m_pBoooomUI[i]; m_pBoooomUI[i] = nullptr;
	}
}

/* ========================================
	UI���������֐�
	-------------------------------------
	���e�FBoooomUI�̐���
	-------------------------------------
	����1�F�������W(x,y,z)
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CExplosionManager::CreateUI(TPos3d<float> pos, float fTime)
{
	for (int i = 0; i < MAX_BOOOOM_NUM; i++)
	{
		// �g�p�ς݂�BoooomUi�̓X���[
		if (m_pBoooomUI[i] != nullptr) continue;

		m_pBoooomUI[i] = new CBoooomUI(pos, m_pTexUI, m_pCamera, fTime);	// ���W���w�肵�Đ���
		m_pBoooomUI[i]->SetCamera(m_pCamera);

		return;
	}
}



/* ========================================
	�����R���{���Z�b�g�֐�
	----------------------------------------
	���e�F�������A�����Ă��邩�`�F�b�N���ă��Z�b�g
	----------------------------------------
	�����F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CExplosionManager::ComboEndCheck()
{
	// �R���{�����m�F
	for (int i = 0; i < MAX_COMBO_NUM; i++)
	{
		// �R���{���������ĂȂ����̓X���[
		if (m_pCombo->GetCombo(i) == 0) continue;
		bool bComboFlg = false;	// �����A���L���t���O

		// ���������`�F�b�N
		for (int j = 0; j < MAX_EXPLOSION_NUM; j++)
		{
			// ���g�p�̔����̓X���[
			if (m_pExplosion[j] == nullptr) continue;

			// �R���{���L�����ǂ���(�Ή��Y�����̔�������ʏ�Ɏc���Ă��邩)
			if (m_pExplosion[j]->GetComboNum() == i)
			{
				bComboFlg = true;
				break;
			}
		}
		// ��ʊO�ɑΉ��Y�����̔������S�ĂȂ��Ȃ�����
		if (bComboFlg == false)
		{
			m_pCombo->EndCombo(i); 	// �R���{�����Z�b�g
		}
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
void CExplosionManager::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;
}

/* ========================================
	�R���{���Z�b�g�֐�
	----------------------------------------
	���e�F�R���{���|�C���^�Z�b�g
	----------------------------------------
	����1�F�R���{���|�C���^
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CExplosionManager::SetCombo(CCombo * pCombo)
{
	m_pCombo = pCombo;
}

/* ========================================
	�����z��擾�֐�
	----------------------------------------
	���e�F�����z��̎擾
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�����̔z��
======================================== */
CExplosion* CExplosionManager::GetExplosionPtr(int num)
{
	if (!m_pExplosion[num]) { return nullptr; }
	return m_pExplosion[num];
}


/* ========================================
	�֐��F��������֐�
	----------------------------------------
	���e�F�X���C���̃��x���ɉ����Ĕ����̎��ԂƑ傫����ύX
	----------------------------------------
	����1�F�X���C���̃��x��
	����2�F�����ꏊ
	����3�F�X���C���̑傫��
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CExplosionManager::SwitchExplode(E_SLIME_LEVEL slimeLevel, TPos3d<float> pos, TTriType<float> slimeSize)
{
	float ExplosionSize = slimeSize.x * EXPLODE_BASE_RATIO;
	float ExplodeTime;
	int ExplodeDamage;

	// �Ԃ���ꂽ�X���C���̃��x���ɂ���ĕ���
	switch (slimeLevel) {
	case LEVEL_1:		ExplodeTime = LEVEL_1_EXPLODE_TIME;		ExplodeDamage = LEVEL_1_EXPLODE_DAMAGE; break;
	case LEVEL_2:		ExplodeTime = LEVEL_2_EXPLODE_TIME;		ExplodeDamage = LEVEL_2_EXPLODE_DAMAGE; break;
	case LEVEL_3:		ExplodeTime = LEVEL_3_EXPLODE_TIME;		ExplodeDamage = LEVEL_3_EXPLODE_DAMAGE; break;
	case LEVEL_4:		ExplodeTime = LEVEL_4_EXPLODE_TIME;		ExplodeDamage = LEVEL_4_EXPLODE_DAMAGE; break;
	case LEVEL_FLAME:	ExplodeTime = LEVEL_1_EXPLODE_TIME;		ExplodeDamage = LEVEL_1_EXPLODE_DAMAGE; break;	// ���X���C���Ɣ������ڐG�����ۂ͈�ԏ���������
	case LEVEL_HEAL:	ExplodeTime = LEVEL_1_EXPLODE_TIME;		ExplodeDamage = LEVEL_1_EXPLODE_DAMAGE; break;	// �񕜃X���C���Ɣ������ڐG�����ۂ͈�ԏ���������
	case LEVEL_BOSS:	ExplodeTime = LEVEL_BOSS_EXPLODE_TIME;	ExplodeDamage = LEVEL_4_EXPLODE_DAMAGE; break;
	}

	Create(pos, ExplosionSize, ExplodeTime, ExplodeDamage, slimeLevel);	// ��������

}
/* ========================================
	�֐��F��������֐�
	----------------------------------------
	���e�F�X���C���̃��x���ɉ����Ĕ����̎��ԂƑ傫����ύX
	----------------------------------------
	����1�F�X���C���̃��x��
	����2�F�����ꏊ
	����3�F�X���C���̑傫��
	����4�F�R���{�z��̓Y����
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CExplosionManager::SwitchExplode(E_SLIME_LEVEL slimeLevel, TPos3d<float> pos, TTriType<float> slimeSize, int comboNum)
{
	float ExplosionSize = slimeSize.x * EXPLODE_BASE_RATIO;
	float ExplodeTime;
	int ExplodeDamage;

	// �Ԃ���ꂽ�X���C���̃��x���ɂ���ĕ���
	switch (slimeLevel) {
	case LEVEL_1:		ExplodeTime = LEVEL_1_EXPLODE_TIME;		ExplodeDamage = LEVEL_1_EXPLODE_DAMAGE; break;
	case LEVEL_2:		ExplodeTime = LEVEL_2_EXPLODE_TIME;		ExplodeDamage = LEVEL_2_EXPLODE_DAMAGE; break;
	case LEVEL_3:		ExplodeTime = LEVEL_3_EXPLODE_TIME;		ExplodeDamage = LEVEL_3_EXPLODE_DAMAGE; break;
	case LEVEL_4:		ExplodeTime = LEVEL_4_EXPLODE_TIME;		ExplodeDamage = LEVEL_4_EXPLODE_DAMAGE; break;
	case LEVEL_FLAME:	ExplodeTime = LEVEL_1_EXPLODE_TIME;		ExplodeDamage = LEVEL_1_EXPLODE_DAMAGE; break;	// ���X���C���Ɣ������ڐG�����ۂ͈�ԏ���������
	case LEVEL_HEAL:	ExplodeTime = LEVEL_1_EXPLODE_TIME;		ExplodeDamage = LEVEL_1_EXPLODE_DAMAGE; break;	// �񕜃X���C���Ɣ������ڐG�����ۂ͈�ԏ���������
	case LEVEL_BOSS:	ExplodeTime = LEVEL_BOSS_EXPLODE_TIME;	ExplodeDamage = LEVEL_4_EXPLODE_DAMAGE; break;

	}

	Create(pos, ExplosionSize, ExplodeTime, comboNum, ExplodeDamage, slimeLevel);	// ��������
//	m_pCombo->AddScore(slimeLevel, comboNum);

}


