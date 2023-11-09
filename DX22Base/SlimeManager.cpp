/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   �X���C���}�l�[�W���[ �N���X����
   ---------------------------------------
   SlimeManager.cpp

   �쐬�ҁF�鑺 ����

   �ύX����
	�E2023/11/05 �X���C���}�l�[�W���[�N���X�쐬 /�鑺 ����
	�E2023/11/08 �X���C�����m���ڐG�����ۂ̕��򏈗����쐬(���򂵂���ɍs�������͖������@��TODO�����Ă�����)�� /�R�����C
	�E2023/11/08 �����������쐬(������̐��������͖����� Slime_2�`Slime_4���܂���������) /�R�����C
	�E2023/11/09 ���������A�ϐ��̕ύX           /�V�c ����
	�E2023/11/09 �R�����g�̒ǉ�           /�V�c ����
	
=========================================== */

// =============== �C���N���[�h ===================
#include "SlimeManager.h"
#include "Slime_1.h"
#include <time.h>

#include <stdlib.h>


// =============== �萔��` =======================
const int ENEMY_GENERATE_INTERVAL	= 5 * 60;	// �����Ԋu
const int RANDOM_POS_MIN			= -30;		// �������W�͈͉���(x,z����)
const int RANDOM_POS_MAX			= 30;		// �������W�͈͏��(x,z����)
const int CREATE_DISTANCE			= 10;		// ���������ŏ��l


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
	: m_GeneCnt(0)
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
void CSlimeManager::Update()
{
	
	// �X���C���X�V
	for (int i = 0; i < MAX_SLIME; i++)
	{
		if (m_pSlime[i] == nullptr) continue;
		m_pSlime[i]->Update(m_pPlayerSphere);

	}

	m_GeneCnt++;
	if(ENEMY_GENERATE_INTERVAL<=m_GeneCnt)
	{
		// �G ����
		Create();
		m_GeneCnt = 0;
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
void CSlimeManager::Create()
{
	CSphereInfo::Sphere CreatePos;	// �X���C���̐����ʒu(TODO�F�^��ύX����)

	for (int i = 0; i < MAX_SLIME; i++)
	{
		// �X���C����use������
		if (m_pSlime[i] != nullptr) continue;

		// �K�؂ȍ��W���o��܂ŌJ��Ԃ�
		while (true)
		{
			// �������Z�b�g����
			CreatePos.pos.x = GetRandom(RANDOM_POS_MIN, RANDOM_POS_MAX);	//�����擾
			CreatePos.pos.z = GetRandom(RANDOM_POS_MIN, RANDOM_POS_MAX);
			CreatePos.pos.y = 0;

			//float Distance = sqrt(pow(Sphere.pos.x - pos.x, 2.0f) + pow(Sphere.pos.z - pos.z, 2.0f));
			float Distance = CreatePos.Distance(m_pPlayerSphere);

			if (Distance >= CREATE_DISTANCE) break;	// �v���C���[������̋�������Ă���Δ�����
		}
		
		m_pSlime[i] = new CSlime_1();	// ���I����
		m_pSlime[i]->SetPos(TPos3d<float>(
			CreatePos.pos.x, CreatePos.pos.y, CreatePos.pos.z));	//pos��ݒ�
		
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
void CSlimeManager::HitBranch(int HitSlimeArrayNum, int standSlimeArrayNum)
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
		SAFE_DELETE(m_pSlime[HitSlimeArrayNum]);	//�Ԃ���ɗ����X���C�����폜
		SAFE_DELETE(m_pSlime[standSlimeArrayNum]);	//�Ԃ���ꂽ�X���C�����폜

		if (hitSlimeLevel == MAX_LEVEL)	//�X���C���̃T�C�Y���ő�̎�
		{
			//�����������s��<=TODO
			//2023/11/09�F��������Ȃ���SceneGameCollision�ł��ׂ������H(�ނ�݂Ƀ|�C���^��n���̂͗ǂ��Ȃ��H)
		}
		else	//�ő�T�C�Y����Ȃ��ꍇ��1�i�K�傫���X���C���𐶐�����
		{
			UnionSlime(hitSlimeLevel);	//�X���C���̌�������
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
void CSlimeManager::UnionSlime(E_SLIME_LEVEL level)
{
	for (int i = 0; i < MAX_SLIME; i++)
	{
		if (m_pSlime[i] != nullptr) { continue; }

		switch (level)
		{
		case LEVEL_1:
			//�T�C�Y2�̃X���C���𐶐�<=TODO
			break;
		case LEVEL_2:
			//�T�C�Y3�̃X���C���𐶐�<=TODO
			break;
		case LEVEL_3:
			//�T�C�Y4�̃X���C���𐶐�<=TODO
			break;
		}
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
void CSlimeManager::SetPlayerSphere(CSphereInfo::Sphere pSphere)
{
	m_pPlayerSphere = pSphere;
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