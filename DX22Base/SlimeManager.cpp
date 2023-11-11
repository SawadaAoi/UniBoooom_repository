/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   �X���C���}�l�[�W���[ �N���X����
   ---------------------------------------
   SlimeManager.cpp

   �쐬�ҁF�鑺 ����

   �ύX����
	�E2023/11/05 �X���C���}�l�[�W���[�N���X�쐬 suzumura
	�E2023/11/08 �X���C�����m���ڐG�����ۂ̕��򏈗����쐬(���򂵂���ɍs�������͖������@��TODO�����Ă�����)�� yamashita
	�E2023/11/08 �����������쐬(������̐��������͖����� Slime_2�`Slime_4���܂���������) yamashita
	�E2023/11/09 ���������A�ϐ��̕ύX sawada
	�E2023/11/09 �R�����g�̒ǉ� sawada
	�E2023/11/11 parameter�p�w�b�_�ǉ� suzumura
	
=========================================== */

// =============== �C���N���[�h ===================
#include "SlimeManager.h"
#include "Slime_1.h"
#include "Slime_2.h"
#include "Slime_3.h"
#include "Slime_4.h"
#include <time.h>
#include "Input.h"		//��ŏ���

#include <stdlib.h>

// =============== �萔��` =======================
#if MODE_DEFINE
#else
const int ENEMY_GENERATE_INTERVAL	= 3 * 60;	// �����Ԋu
const int RANDOM_POS_MIN			= -15;		// �������W�͈͉���(x,z����)
const int RANDOM_POS_MAX			= 15;		// �������W�͈͏��(x,z����)
const int CREATE_DISTANCE			= 10;		// ���������ŏ��l
const int SLIME_LEVEL1_PER = 50;				// �X���C��_1�̐����m��
const int SLIME_LEVEL2_PER = 30;				// �X���C��_2�̐����m��
const int SLIME_LEVEL3_PER = 100 - SLIME_LEVEL1_PER - SLIME_LEVEL2_PER;	// �X���C��_3�̐����m��
const float MAX_SIZE_EXPLODE = 5.0f;	// �X���C��4���m�̔����̑傫��
const float EXPLODE_BASE_RATIO = 1.0f;	// �X���C���̔����ڐG�ł̔����̑傫���̃x�[�X
#endif

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�R���X�g���N�^
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
CSlimeManager::CSlimeManager()
	: m_CreateCnt(0)
{

	srand((unsigned int)time(NULL));	// �����p�^�[���ݒ�

	// �X���C��������
	for (int i = 0; i < MAX_SLIME; i++)
	{
		m_pSlime[i] = nullptr;
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
CSlimeManager::~CSlimeManager()
{
	// �X���C���폜
	for (int i = 0; i < MAX_SLIME; i++)
	{
		SAFE_DELETE(m_pSlime[i]);
	}
}

/* ========================================
	�X�V�����֐�
	-------------------------------------
	���e�F�X�V����
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSlimeManager::Update(CExplosionManager* pExpMng)
{
	
	// �X���C���X�V
	for (int i = 0; i < MAX_SLIME; i++)
	{
		if (m_pSlime[i] == nullptr) continue;
		m_pSlime[i]->Update(m_pPlayerPos);

	}

	m_CreateCnt++;
	if(ENEMY_GENERATE_INTERVAL<= m_CreateCnt)
	{
		// �G ����
		Create(GetRandomLevel());	//�X���C���̃��x���������_���ɑI��Ő�������
		m_CreateCnt = 0;				//�J�E���g�����Z�b�g
	}
}

/* ========================================
	�`�揈���֐�
	-------------------------------------
	���e�F�`�揈��
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSlimeManager::Draw()
{
	//"�X���C��1"�`��
	for (int i = 0; i < MAX_SLIME; i++)
	{
		if (m_pSlime[i] == nullptr) continue;
		m_pSlime[i]->Draw(m_pCamera);
	}
}


/* ========================================
	�X���C�������֐�
	-------------------------------------
	���e�F�X���C���̐���
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSlimeManager::Create(E_SLIME_LEVEL level)
{
	TPos3d<float> CreatePos;	// �X���C���̐����ʒu

	for (int i = 0; i < MAX_SLIME; i++)
	{
		// �X���C����use������
		if (m_pSlime[i] != nullptr) continue;

		// �K�؂ȍ��W���o��܂ŌJ��Ԃ�
		while (true)
		{
			// �������Z�b�g����
			CreatePos.x = GetRandom(RANDOM_POS_MIN, RANDOM_POS_MAX);	//�����擾
			CreatePos.z = GetRandom(RANDOM_POS_MIN, RANDOM_POS_MAX);
			CreatePos.y = 0;

			float Distance = CreatePos.Distance(m_pPlayerPos);	// �������W�̃v���C���[�Ƃ̋���

			if (Distance >= CREATE_DISTANCE) break;	// �v���C���[������̋�������Ă���Δ�����
		}
		
		switch (level)
		{
		case LEVEL_1:
			m_pSlime[i] = new CSlime_1(CreatePos);	// ���I����
			break;
		case LEVEL_2:
			m_pSlime[i] = new CSlime_2(CreatePos);	// ���I����
			break;
		case LEVEL_3:
			m_pSlime[i] = new CSlime_3(CreatePos);	// ���I����
			break;
		case LEVEL_4:
			m_pSlime[i] = new CSlime_4(CreatePos);	// ���I����
			break;
		}

		m_pSlime[i]->SetCamera(m_pCamera);	//�J�������Z�b�g
		break;						// ����������I��
		
	}
}

/* ========================================
	�X���C���ڐG����֐�
	----------------------------------------
	���e�F�X���C�����m���ڐG�����ۂɕ��򂵂Đ��������������s����
	----------------------------------------
	����1�F�Ԃ���ɂ����X���C���̔z��ԍ�
	����2�F�Ԃ���ꂽ�X���C���̔z��ԍ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CSlimeManager::HitBranch(int HitSlimeArrayNum, int standSlimeArrayNum, CExplosionManager* pExpMng)
{
	E_SLIME_LEVEL hitSlimeLevel, standSlimeLevel;
	hitSlimeLevel = m_pSlime[HitSlimeArrayNum]->GetSlimeLevel();		//�Ԃ���ɗ����X���C���̃T�C�Y���擾
	standSlimeLevel = m_pSlime[standSlimeArrayNum]->GetSlimeLevel();	//�Ԃ���ꂽ�X���C���̃T�C�Y���擾
	if (hitSlimeLevel > standSlimeLevel)								//�Ԃ���ɂ����X���C�����傫���ꍇ
	{
		float speed = m_pSlime[HitSlimeArrayNum]->GetSpeed();					//�Ԃ���ɗ����X���C���̑��x���擾
		CSphereInfo::Sphere sphere = m_pSlime[HitSlimeArrayNum]->GetSphere();		//�Ԃ���ꂽ�X���C����Sphere���擾
		float angle = sphere.Angle(m_pSlime[standSlimeArrayNum]->GetSphere());		//�Ԃ���ꂽ�X���C���̕���������o��
		m_pSlime[standSlimeArrayNum]->HitMoveStart(speed, angle);					//�Ԃ���ꂽ�X���C���ɐ�����шړ�����
		m_pSlime[HitSlimeArrayNum]->Reflect();										//�Ԃ���ɗ����X���C���̑��x�ɔ����̊�������Z����
	}
	else if(hitSlimeLevel < standSlimeLevel)	//�Ԃ���ɂ����X���C�����������ꍇ
	{
		float speed = m_pSlime[HitSlimeArrayNum]->GetSpeed();					//�Ԃ���ɗ����X���C���̑��x���擾
		CSphereInfo::Sphere sphere = m_pSlime[standSlimeArrayNum]->GetSphere();		//�Ԃ���ꂽ�X���C����Sphere���擾
		float angle = sphere.Angle(m_pSlime[HitSlimeArrayNum]->GetSphere());		//�Ԃ���ꂽ�X���C���̕���������o��
		m_pSlime[HitSlimeArrayNum]->HitMoveStart(speed, angle);						//�Ԃ���ꂽ�X���C���ɐ�����шړ�����
	}
	else	//�X���C���̃T�C�Y�������������ꍇ
	{
		TPos3d<float> pos(m_pSlime[standSlimeArrayNum]->GetPos());	//�Փː�̃X���C���̈ʒu���m��
		SAFE_DELETE(m_pSlime[HitSlimeArrayNum]);	//�Ԃ���ɗ����X���C�����폜
		SAFE_DELETE(m_pSlime[standSlimeArrayNum]);	//�Ԃ���ꂽ�X���C�����폜

		if (hitSlimeLevel == MAX_LEVEL)	//�X���C���̃T�C�Y���ő�̎�
		{
			//�����������s��<=TODO
			pExpMng->Create(pos, MAX_SIZE_EXPLODE);	//�Փː�̃X���C���̈ʒu�Ŕ���
		}
		else	//�ő�T�C�Y����Ȃ��ꍇ��1�i�K�傫���X���C���𐶐�����
		{
			UnionSlime(hitSlimeLevel,pos);	//�X���C���̌�������
		}
	}
}

/* ========================================
	�����֐�
	----------------------------------------
	���e�F1�i�K��̃X���C���𐶐�����֐�
	----------------------------------------
	����1�F�X���C���̃��x��
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CSlimeManager::UnionSlime(E_SLIME_LEVEL level ,TPos3d<float> pos)
{
	for (int i = 0; i < MAX_SLIME; i++)
	{
		if (m_pSlime[i] != nullptr) { continue; }

		switch (level)
		{
		case LEVEL_1:
			//�T�C�Y2�̃X���C���𐶐�
			m_pSlime[i] = new CSlime_2(pos);
			break;
		case LEVEL_2:
			//�T�C�Y3�̃X���C���𐶐�
			m_pSlime[i] = new CSlime_3(pos);
			break;
		case LEVEL_3:
			//�T�C�Y4�̃X���C���𐶐�
			m_pSlime[i] = new CSlime_4(pos);
			break;
		}

		m_pSlime[i]->SetCamera(m_pCamera);	//�J�������Z�b�g

		break;
	}
}

/* ========================================
	�����ڐG�֐�
	----------------------------------------
	���e�F��ʏ�̔����ɃX���C�����ڐG�������̏���
	----------------------------------------
	����1�F��������X���C���̔z��ԍ�
	����2�F�����}�l�[�W���[�̃|�C���^
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CSlimeManager::TouchExplosion(int DelSlime, CExplosionManager * pExpMng)
{
	TPos3d<float> pos(m_pSlime[DelSlime]->GetPos());	//�Փː�̃X���C���̈ʒu���m��

	float ExplosionSize;	// �����̑傫��
	switch (m_pSlime[DelSlime]->GetSlimeLevel())
	{
	case LEVEL_1:
		ExplosionSize = 1.0f * EXPLODE_BASE_RATIO;
		break;
	case LEVEL_2:
		ExplosionSize = 2.0f * EXPLODE_BASE_RATIO;
		break;
	case LEVEL_3:
		ExplosionSize = 3.0f * EXPLODE_BASE_RATIO;
		break;
	case LEVEL_4:
		ExplosionSize = 4.0f * EXPLODE_BASE_RATIO;
		break;
	
	}
	SAFE_DELETE(m_pSlime[DelSlime]);					//�Ԃ���ɗ����X���C�����폜
	pExpMng->Create(pos, ExplosionSize);				//�Փː�̃X���C���̈ʒu�Ŕ���
}

/* ========================================
	�X���C���z��擾�֐�
	----------------------------------------
	���e�F�X���C���z��̎擾
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�X���C���̔z��
======================================== */
E_SLIME_LEVEL CSlimeManager::GetRandomLevel()
{
	int random = abs(rand() % 100);	//�����_����0�`99�̐������쐬
	
	//�萔�Œ�`�����m����1�`3���x���̃X���C���𐶐�
	if (SLIME_LEVEL1_PER > random)	
	{
		return LEVEL_1;
	}
	else if ((SLIME_LEVEL1_PER + SLIME_LEVEL2_PER) > random)
	{
		return LEVEL_2;
	}
	else
	{
		return LEVEL_3;
	}
	
}

/* ========================================
	�X���C���z��擾�֐�
	----------------------------------------
	���e�F�X���C���z��̎擾
	----------------------------------------
	����1�F�Q�b�g�������X���C���̗v�f�ԍ�
	----------------------------------------
	�ߒl�F�X���C���̔z��
======================================== */
CSlimeBase* CSlimeManager::GetSlimePtr(int num)
{
	return m_pSlime[num];
}

/* ========================================
	�J�������Z�b�g�֐�
	----------------------------------------
	���e�F�`�揈���Ŏg�p����J�������Z�b�g
	----------------------------------------
	����1�F�J����
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CSlimeManager::SetCamera(CCamera * pCamera)
{
	m_pCamera = pCamera;
}

/* ========================================
	�v���C���[�̍��W�擾�֐�
	----------------------------------------
	���e�F���݂̃v���C���[�̍��W���擾����
	----------------------------------------
	����1�F�v���C���[�̍��W(���݂̓X�t�B�A�����A����ύX����)
	----------------------------------------
	�ߒl�F����
======================================== */
void CSlimeManager::SetPlayerPos(TPos3d<float> pos)
{
	m_pPlayerPos = pos;
}

/* ========================================
	�����֐�
	----------------------------------------
	���e�F����قȂ闐���֐�
	----------------------------------------
	����1�F�����̍ŏ��l�ƍő�l
	----------------------------------------
	�ߒl�F����int
======================================== */
int CSlimeManager::GetRandom(int min, int max)
{
	return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}