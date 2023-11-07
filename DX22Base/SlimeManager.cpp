/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   �X���C���}�l�[�W���[ �N���X����
   ---------------------------------------
   SlimeManager.cpp

   �쐬�ҁF�鑺 ����

   �ύX����
   �E2023/11/05 �X���C���}�l�[�W���[�N���X�쐬 /�鑺 ����

   ======================================== */
#include "SlimeManager.h"
#include "Slime_1.h"

#include <stdlib.h>


// =============== �R���X�g���N�^ =============
CSlimeManager::CSlimeManager()
	:m_nRandNum(0)
{
	//"�X���C��1"����
	for (int i = 0; i < MAX_SLIME_1; i++)
	{
		m_pSlime[i] = new CSlime_1;
	}
	/*
	//"�X���C��2"����
	for (int i = 0; i < MAX_SLIME_2; i++)
	{
		m_pSlime[i] = new CSlime_2;
	}
	//"�X���C��3"����
	for (int i = 0; i < MAX_SLIME_2; i++)
	{
		m_pSlime[i] = new CSlime_3;
	}
	//"�X���C��4"����
	for (int i = 0; i < MAX_SLIME_2; i++)
	{
		m_pSlime[i] = new CSlime_4;
	}
	*/
}

// =============== �f�X�g���N�^ =============
CSlimeManager::~CSlimeManager()
{
	//"�X���C��1"�폜
	for (int i = 0; i < MAX_SLIME_1; i++)
	{
		if (m_pSlime[i] != nullptr)
		{
			delete m_pSlime[i];
			m_pSlime[i] = nullptr;
		}
	}
}

/*
 ========================================
   �֐� Update()
 ----------------------------------------
   ���e�F�X�V����
 ======================================== */
void CSlimeManager::Update()
{

	//"�X���C��1"�X�V
	for (int i = 0; i < MAX_SLIME_1; i++)
	{
		float m_posX, m_posZ;
		int _RandNum = 0;
		// �^������
		m_nRandNum = rand();	//�^�������擾
		_RandNum = m_nRandNum;	//�ޔ�

		//�����_��X����
		m_nRandNum %= 10;	//(0~10)
		if (m_nRandNum < 5)  m_posX = (float)-m_nRandNum;
		else m_posX = (float)m_nRandNum - 5.0f;

		//�����_��Z����
		_RandNum -= 999;
		_RandNum %= 10;	//(0~10)
		if (_RandNum < 5)  m_posZ = (float)-_RandNum;
		else m_posZ = (float)_RandNum - 5.0f;

		// �G ����
		Generate(TTriType<float>(m_posX, 0.0f, m_posZ));
		m_pSlime[i]->Update();
	}
}
/*
 ========================================
   �֐� Draw()
 ----------------------------------------
   ���e�F�`�揈��
 ======================================== */
void CSlimeManager::Draw()
{
	//"�X���C��1"�`��
	for (int i = 0; i < MAX_SLIME_1; i++)
	{
		m_pSlime[i]->Draw();
	}
}

void CSlimeManager::Generate(TTriType<float> pos)
{
	CSphereInfo::Sphere sphere;
	sphere.radius = 0.0f;
	sphere.pos = pos;

	for (int i = 0; i < MAX_SLIME_1; i++)
	{
		// �X���C����use������
		if (m_pSlime[i]->GetUse() == false)
		{
			m_pSlime[i]->SetUse(true);	//use��true��
			m_pSlime[i]->SetPos(sphere);	//pos��ݒ�
			break;						//��������break
		}
	}
	
}

/* ========================================
	
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
		float speed = m_pSlime[HitSlimeArrayNum]->GetSlimeSpeed();					//�Ԃ���ɗ����X���C���̑��x���擾
		CSphereInfo::Sphere sphere = m_pSlime[HitSlimeArrayNum]->GetSphere();		//�Ԃ���ꂽ�X���C����Sphere���擾
		float angle = sphere.Angle(m_pSlime[standSlimeArrayNum]->GetSphere());		//�Ԃ���ꂽ�X���C���̕���������o��
		m_pSlime[standSlimeArrayNum]->HitMoveStart(speed, angle);					//�Ԃ���ꂽ�X���C���ɐ�����шړ�����
		//�Ԃ���ɗ����X���C���ɔ�������  <=TODO
	}
	else if(hitSlimeLevel < standSlimeLevel)	//�Ԃ���ɂ����X���C�����������ꍇ
	{
		float speed = m_pSlime[HitSlimeArrayNum]->GetSlimeSpeed();					//�Ԃ���ɗ����X���C���̑��x���擾
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
