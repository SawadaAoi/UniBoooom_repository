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
	�E2023/11/11 �X���C�����m���d�Ȃ�Ȃ��֐���ǉ� yamashita
	�E2023/11/13 �X���C�����x�����Ƃɔ������Ԃ�ݒ�ł���悤�ɕύX Suzumura
	�E2023/11/14 ���X���C���̏��������� Suzumura
	�E2023/11/14 SphereInfo�̕ύX�ɑΉ� Takagi

=========================================== */

// =============== �C���N���[�h ===================
#include "SlimeManager.h"
#include "Slime_1.h"
#include "Slime_2.h"
#include "Slime_3.h"
#include "Slime_4.h"
#include "Slime_Flame.h"
#include "Input.h"		//��ŏ���
#include "GameParameter.h"		//�萔��`�p�w�b�_�[

#include <stdlib.h>

// =============== �萔��` =======================
#if MODE_GAME_PARAMETER
#else
const int ENEMY_CREATE_INTERVAL	= 3 * 60;		// �����Ԋu
const int RANDOM_POS			= 15;			// �������W�͈�
const int CREATE_DISTANCE		= 10;			// ���������ŏ��l
const int SLIME_LEVEL1_PER		= 50;			// �X���C��_1�̐����m��
const int SLIME_LEVEL2_PER		= 35;			// �X���C��_2�̐����m��
const int SLIME_LEVEL3_PER		= 10;			// �X���C��_3�̐����m��
const int SLIME_LEVEL_FLAME_PER	= 100 - SLIME_LEVEL1_PER - SLIME_LEVEL2_PER - SLIME_LEVEL3_PER;	// �X���C��_�t���C���̐����m��

const int START_ENEMY_NUM		= 10;			// �Q�[���J�n���̓G�L�����̐�

// ��1.0f�ł��̂܂�
const float COL_SUB_HIT_TO_BIG = 0.7f;				// �X���C���Փ�(������)�̏Փˑ��̌��Z�l(���˂���ړ�)
const float COL_SUB_STAND_TO_SMALL = 0.3f;			// �X���C���Փ�(������)�̏Փ˂���鑤�̌��Z�l(�Փ˂��ꂽ����)
const float COL_SUB_HIT_TO_SMALL = 0.3f;			// �X���C���Փ�(�偨��)�̏Փˑ��̌��Z�l(�ړ�����)
const float COL_SUB_STAND_TO_BIG = 1.2f;			// �X���C���Փ�(�偨��)�̏Փ˂���鑤�̌��Z�l(�Փ˂��ꂽ����)
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


	// �X���C��������
	for (int i = 0; i < MAX_SLIME_NUM; i++)
	{
		m_pSlime[i] = nullptr;
	}

	// �Q�[���J�n���ɓG�L�����𐶐�����
	for (int i = 0; i < START_ENEMY_NUM; i++)
	{
		int ranLv = rand() % 3 + 1;		// ��������X���C���̃��x���𗐐��Ŏw��
		Create((E_SLIME_LEVEL)ranLv);	// ��������
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
	for (int i = 0; i < MAX_SLIME_NUM; i++)
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
	for (int i = 0; i < MAX_SLIME_NUM; i++)
	{
		if (m_pSlime[i] == nullptr) continue;
		m_pSlime[i]->Update(m_pPlayerPos);

	}

	m_CreateCnt++;
	if(ENEMY_CREATE_INTERVAL<= m_CreateCnt)
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
	for (int i = 0; i < MAX_SLIME_NUM; i++)
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

	for (int i = 0; i < MAX_SLIME_NUM; i++)
	{
		// �X���C����use������
		if (m_pSlime[i] != nullptr) continue;

		// �K�؂ȍ��W���o��܂ŌJ��Ԃ�
		while (true)
		{
			// �������Z�b�g����
			CreatePos.x = GetRandom(-RANDOM_POS, RANDOM_POS);	//�����擾
			CreatePos.z = GetRandom(-RANDOM_POS, RANDOM_POS);
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
		case LEVEL_FLAME:
			m_pSlime[i] = new CSlime_Flame(CreatePos);	// ���I����
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
	����1�F�Փ˂���X���C���̔z��ԍ�
	����2�F�Փ˂��ꂽ�X���C���̔z��ԍ�
	����3�F�����}�l�[�W���[
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CSlimeManager::HitBranch(int HitSlimeNum, int StandSlimeNum, CExplosionManager* pExpMng)
{
	E_SLIME_LEVEL hitSlimeLevel, standSlimeLevel;				// ���x��
	tagSphereInfo hitSlimeSphere, standSlimeSphere;				// �����蔻��
	tagTransform3d hitSlimeTransform, standSlimeTransform;		//���[���h���W�n
	float hitSlimeSpeed, standSlimeSpeed;						// �ړ��X�s�[�h
	float travelAngle, reflectionAngle;							// �ړ�����

	hitSlimeLevel = m_pSlime[HitSlimeNum]->GetSlimeLevel();		// �Փ˂���X���C���̃T�C�Y���擾
	hitSlimeSphere = m_pSlime[HitSlimeNum]->GetSphere();		// �Փ˂���X���C���̓����蔻����擾
	hitSlimeTransform = m_pSlime[HitSlimeNum]->GetTransform();	// �Փ˂���X���C���̃��[���h���W�����擾
	hitSlimeSpeed = m_pSlime[HitSlimeNum]->GetSpeed();			// �Փ˂���X���C���̑��x���擾

	standSlimeLevel = m_pSlime[StandSlimeNum]->GetSlimeLevel();	// �Փ˂��ꂽ�X���C���̃T�C�Y���擾
	standSlimeSphere = m_pSlime[StandSlimeNum]->GetSphere();	// �Փ˂��ꂽ�X���C���̓����蔻����擾
	standSlimeTransform = m_pSlime[StandSlimeNum]->GetTransform();	// �Փ˂���X���C���̃��[���h���W�����擾

	travelAngle = hitSlimeTransform.Angle(standSlimeTransform);		// �Փ˂��鑤�̐i�s����
	reflectionAngle = standSlimeTransform.Angle(hitSlimeTransform);	// �Փ˂��鑤�̋t����(����)
	TPos3d<float> pos = m_pSlime[StandSlimeNum]->GetPos();        // �Փ˂��ꂽ�X���C���̈ʒu���m��
	
	//-- �t���C���X���C���q�b�g���� �Ăяo��
	if (HitFlameBranch(HitSlimeNum, StandSlimeNum, pExpMng)) 
	{
		return; //�t���C���X���C���ڐG���s��ꂽ�Ȃ珈�����d�Ȃ�Ȃ��悤��return����
	}
	
	//-- �m�[�}���X���C���q�b�g����
	// �Փ˂���X���C�����������ꍇ(������)
	if (hitSlimeLevel < standSlimeLevel)
	{
		m_pSlime[HitSlimeNum]->HitMoveStart(hitSlimeSpeed * COL_SUB_HIT_TO_BIG, reflectionAngle);			// �Փ˂���X���C���ɐ�����шړ�����
		m_pSlime[StandSlimeNum]->HitMoveStart(hitSlimeSpeed * COL_SUB_STAND_TO_SMALL, travelAngle);			// �Փ˂��ꂽ�X���C���ɐ�����шړ�����

	}
	
	// �Փ˂���X���C�����傫���ꍇ(�偨��)
	else if (hitSlimeLevel > standSlimeLevel)
	{
		m_pSlime[HitSlimeNum]->HitMoveStart(hitSlimeSpeed * COL_SUB_HIT_TO_SMALL, travelAngle);	// �Փ˂���X���C���ɐ�����шړ�����
		m_pSlime[StandSlimeNum]->HitMoveStart(hitSlimeSpeed * COL_SUB_STAND_TO_BIG, travelAngle);			// �Փ˂��ꂽ�X���C���ɐ�����шړ�����

	}
	//�X���C���̃T�C�Y�������������ꍇ
	else
	{
		SAFE_DELETE(m_pSlime[HitSlimeNum]);								// �Փ˂���X���C�����폜
		SAFE_DELETE(m_pSlime[StandSlimeNum]);							// �Փ˂��ꂽ�X���C�����폜

		if (hitSlimeLevel == MAX_LEVEL)	//�X���C���̃T�C�Y���ő�̎�
		{
			//�X���C����������
			pExpMng->Create(pos, MAX_SIZE_EXPLODE * EXPLODE_BASE_RATIO, LEVEL_4_EXPLODE_TIME);	//�Փ˂��ꂽ�X���C���̈ʒu�Ń��x���S����

		}
		else	//�ő�T�C�Y����Ȃ��ꍇ��1�i�K�傫���X���C���𐶐�����
		{
			UnionSlime(hitSlimeLevel,pos);	//�X���C���̌�������
		}
	}
}

/* ========================================
	�t���C���X���C���ڐG����֐�
	----------------------------------------
	���e�F�t���C���X���C�����ڐG�����ہA���������������s����
	----------------------------------------
	����1�F�Փ˂���X���C���̔z��ԍ�
	����2�F�Փ˂��ꂽ�X���C���̔z��ԍ�
	����3�F�����}�l�[�W���[
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
bool CSlimeManager::HitFlameBranch(int HitSlimeNum, int StandSlimeNum, CExplosionManager* pExpMng)
{
	E_SLIME_LEVEL hitSlimeLevel, standSlimeLevel;						// ���x��
	float hitSlimeSpeed;												// �ړ��X�s�[�h
	float travelAngle;													// �ړ�����
	float ExplosionSize;												// �����̑傫��
	tagTransform3d hitSlimeTransform, standSlimeTransform;				//���[���h�s��Ɋւ����

	TPos3d<float> pos = m_pSlime[StandSlimeNum]->GetPos();					// �Փ˂��ꂽ�X���C���̈ʒu���m��
	TTriType<float> hitSlimeSize = m_pSlime[HitSlimeNum]->GetScale();		// �Փː�̃X���C���̃T�C�Y���m��
	TTriType<float> standSlimeSize = m_pSlime[StandSlimeNum]->GetScale();	// �������ł����X���C���̃T�C�Y���m��

	hitSlimeTransform = m_pSlime[HitSlimeNum]->GetTransform();				// �Փ˂���̃��[���h�s��Ɋւ����
	standSlimeTransform = m_pSlime[StandSlimeNum]->GetTransform();			// �Փ˂��ꂽ���[���h�s��Ɋւ����
	hitSlimeLevel = m_pSlime[HitSlimeNum]->GetSlimeLevel();					// �Փ˂���X���C���̃T�C�Y���擾
	hitSlimeSpeed = m_pSlime[HitSlimeNum]->GetSpeed();						// �Փ˂���X���C���̑��x���擾
	travelAngle = hitSlimeTransform.Angle(standSlimeTransform);				// �Փ˂��鑤�̐i�s����
	standSlimeLevel = m_pSlime[StandSlimeNum]->GetSlimeLevel();				// �Փ˂��ꂽ�X���C���̃T�C�Y���擾

	//-- �t���C���X���C���q�b�g����
	// �t���C���@���@�t���C��
	if (hitSlimeLevel == LEVEL_FLAME && standSlimeLevel == LEVEL_FLAME)
	{
		// �w�Փ˂���X���C�����傫���ꍇ(�偨��)�x�Ɠ���������������
		m_pSlime[HitSlimeNum]->HitMoveStart(hitSlimeSpeed * COL_SUB_HIT_TO_SMALL, travelAngle);		// �Փ˂���X���C���ɐ�����шړ�����
		m_pSlime[StandSlimeNum]->HitMoveStart(hitSlimeSpeed * COL_SUB_STAND_TO_BIG, travelAngle);	// �Փ˂��ꂽ�X���C���ɐ�����шړ�����

		return true;
	}
	// �t���C���@���@�m�[�}��
	else if (hitSlimeLevel == LEVEL_FLAME)
	{
		pExpMng->SwitchExplode(standSlimeLevel,hitSlimeTransform.fPos,standSlimeSize);	//�X���C���̃��x���ɂ���Ĕ����̎��ԂƃT�C�Y�𕪊�

		SAFE_DELETE(m_pSlime[HitSlimeNum]);								// �Փ˂���X���C�����폜
		SAFE_DELETE(m_pSlime[StandSlimeNum]);							// �Փ˂��ꂽ�X���C�����폜

		return true;
	}
	// �m�[�}���@���@�t���C��
	else if (standSlimeLevel == LEVEL_FLAME)
	{
		pExpMng->SwitchExplode(hitSlimeLevel, hitSlimeTransform.fPos, hitSlimeSize);	//�X���C���̃��x���ɂ���Ĕ����̎��ԂƃT�C�Y�𕪊�

		SAFE_DELETE(m_pSlime[HitSlimeNum]);								// �Փ˂���X���C�����폜
		SAFE_DELETE(m_pSlime[StandSlimeNum]);							// �Փ˂��ꂽ�X���C�����폜

		return true;

	}
	return false;
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
	for (int i = 0; i < MAX_SLIME_NUM; i++)
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
	TPos3d<float> pos(m_pSlime[DelSlime]->GetPos());			// �Փː�̃X���C���̈ʒu���m��
	E_SLIME_LEVEL level = m_pSlime[DelSlime]->GetSlimeLevel();	// �Փː�̃X���C���̃��x�����m��
	TTriType<float> size = m_pSlime[DelSlime]->GetScale();		// �Փː�̃X���C���T�C�Y���m��

	pExpMng->SwitchExplode(level,pos,size);

	SAFE_DELETE(m_pSlime[DelSlime]);					//�Ԃ���ɗ����X���C�����폜

	//pExpMng->Create(pos, ExplosionSize);				//�Փː�̃X���C���̈ʒu�Ŕ���
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
	else if ((SLIME_LEVEL1_PER + SLIME_LEVEL2_PER + SLIME_LEVEL3_PER) > random)
	{
		return LEVEL_3;
	}
	else
	{
		return LEVEL_FLAME;
	}
	
}

/* ========================================
	�d�Ȃ�Ȃ��֐�
	----------------------------------------
	���e�F�Ԃ������X���C�������������߂����֐�
	----------------------------------------
	����1�F�Փ˂����X���C���̃|�C���^
	����2�F�Փ˂��ꂽ�X���C���̃|�C���^
	----------------------------------------
	�ߒl�F
======================================== */
void CSlimeManager::PreventOverlap(CSlimeBase * pMoveSlime, CSlimeBase * pStandSlime)
{
	//���̃R�����g�A�E�g�͗��z�I�ȏ����̂�肩��
	/*
	tagSphereInfo::Sphere standSlimeSphere = pStandSlime->GetSphere();
	tagSphereInfo::Sphere moveSlimeSphere = pMoveSlime->GetSphere();
	float standSlimeToPlayerAngle = standSlimeSphere.Angle(m_pPlayer->GetPlayerSphere());
	float standSlimeToMoveSlimeAngle = standSlimeSphere.Angle(moveSlimeSphere);
	float Distance = standSlimeSphere.Distance(pMoveSlime->GetSphere());
	float posX, posY, posZ;

	if (standSlimeToMoveSlimeAngle < 0) { standSlimeToMoveSlimeAngle = (2 * PI) + standSlimeToMoveSlimeAngle; }
	if (standSlimeToPlayerAngle < 0) { standSlimeToPlayerAngle = (2 * PI) + standSlimeToPlayerAngle; }
	standSlimeToMoveSlimeAngle -= standSlimeToPlayerAngle;

	if (PI < standSlimeToMoveSlimeAngle)
	{
		standSlimeToMoveSlimeAngle -= DirectX::XMConvertToRadians(5.0f);
	}
	else
	{
		standSlimeToMoveSlimeAngle += DirectX::XMConvertToRadians(5.0f);
	}
	TPos3d<float> pos = pStandSlime->GetPos();
	pos.x +=  cosf(standSlimeToMoveSlimeAngle) * (standSlimeSphere.radius + moveSlimeSphere.radius + 0.05);
	pos.z += sinf(standSlimeToMoveSlimeAngle) * (standSlimeSphere.radius + moveSlimeSphere.radius + 0.05);

	pMoveSlime->SetPos(pos);

	pMoveSlime->ReversePos();
	*/

	float angle = pStandSlime->GetTransform().Angle(pMoveSlime->GetTransform());				//�Փ˂��Ă����p�x
	float distance = pStandSlime->GetSphere().fRadius + pMoveSlime->GetSphere().fRadius;	//���݂��̃X���C���̔��a�𑫂�����

	TPos3d<float> pos = pStandSlime->GetPos();		//�����߂���̍��W
	pos.x += cosf(angle) * (distance + 0.001f);		//�Ԃ���Ȃ��M���M���̋�����ݒ�
	pos.z += sinf(angle) * (distance + 0.001f);		//�Ԃ���Ȃ��M���M���̋�����ݒ�

	pMoveSlime->SetPos(pos);						//�Ԃ���Ȃ��M���M���̋����Ɉړ�
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