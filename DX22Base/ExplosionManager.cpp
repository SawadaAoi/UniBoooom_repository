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

========================================== */

// =============== �C���N���[�h ===================
#include "ExplosionManager.h"	//���g�̃w�b�_�[
#include "Explosion.h"			//���������w�b�_�[
#include "Sphere.h"				//����`�w�b�_�[

// =============== �萔��` =======================


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
{
	// �����z��̏�����
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		m_pExplosion[i] = nullptr;
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
CExplosionManager::~CExplosionManager()
{
	// �������폜
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		SAFE_DELETE(m_pExplosion[i]);
	}
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
	}

	DeleteCheck();	// �폜�`�F�b�N
}



/* ========================================
	���������֐�
	-------------------------------------
	���e�F�����̐���
	-------------------------------------
	����1�F�������W(x,y,z)
	-------------------------------------
	����2�F�����̑傫��
	-------------------------------------
	����3�F����������
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CExplosionManager::Create(TTriType<float> pos,float size, float time,int score)
{
	// ����������
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		// �g�p�ς݂̔����̓X���[
		if (m_pExplosion[i] != nullptr) continue;

		m_pExplosion[i] = new CExplosion(pos,size,time);	// ���W���w�肵�Đ���
		m_pExplosion[i]->SetCamera(m_pCamera);
		m_pScoreMng->CreateScore(pos, time, score);


		break;

	}
}

/* ========================================
	�֐��F�����폜�֐�
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
	�X�R�A���Z�b�g�֐�
	----------------------------------------
	���e�F�����������ɕK�v�ȃX�R�A���Z�b�g
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CExplosionManager::SetScoreMng(CScoreManager * pScoreMng)
{
	m_pScoreMng = pScoreMng;
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
	return m_pExplosion[num];;
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

	// �Ԃ���ꂽ�X���C���̃��x���ɂ���ĕ���
	switch (slimeLevel) {
	case LEVEL_1:
		//�X���C����������
		Create(pos, ExplosionSize, LEVEL_1_EXPLODE_TIME, LEVEL_1_SCORE);	//�Փ˂��ꂽ�X���C���̈ʒu�Ń��x���P����
		break;
	case LEVEL_2:
		//�X���C����������
		Create(pos, ExplosionSize, LEVEL_2_EXPLODE_TIME, LEVEL_2_SCORE);	//�Փ˂��ꂽ�X���C���̈ʒu�Ń��x���Q����
		break;
	case LEVEL_3:
		//�X���C����������
		Create(pos, ExplosionSize, LEVEL_3_EXPLODE_TIME, LEVEL_3_SCORE);	//�Փ˂��ꂽ�X���C���̈ʒu�Ń��x���R����
		break;
	case LEVEL_4:
		//�X���C����������
		Create(pos, ExplosionSize, LEVEL_4_EXPLODE_TIME, LEVEL_4_SCORE);	//�Փ˂��ꂽ�X���C���̈ʒu�Ń��x���S����
		break;
	case LEVEL_FLAME:
		Create(pos, ExplosionSize, LEVEL_1_EXPLODE_TIME, LEVEL_1_SCORE);	//�Փ˂��ꂽ�X���C���̈ʒu�Ń��x���P����

		break;
	}
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
}
