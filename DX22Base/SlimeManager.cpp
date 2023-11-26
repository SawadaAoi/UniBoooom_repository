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
	�E2023/11/15 �e���f���̓ǂݍ��݂�base����ړ� yamashita
	�E2023/11/15 �e���f���̓ǂݍ��݂��֐��� yamashita
	�E2023/11/21 BoooomUi�\������֐����Ăяo�� Tei
	�E2023/11/26 �X���C���Ɣ����̋����𒲂ד����邩���肷��֐����쐬 yamashita

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
	, m_pVS(nullptr)
	, m_pBlueModel(nullptr)
	, m_pGreenModel(nullptr)
	, m_pYellowModel(nullptr)
	, m_pRedModel(nullptr)
	, m_pFlameModel(nullptr)
	, m_pSEHitSlime(nullptr)
	, m_pSEUnion(nullptr)
	, m_pSEHitSlimeSpeaker(nullptr)
	, m_pSEUnionSpeaker(nullptr)
	, m_pExpMng(nullptr)
{
	//�X���C���̃��f���ƒ��_�V�F�[�_�[�̓ǂݍ���
	LoadModel();

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
	//�T�E���h�t�@�C���̓ǂݍ���
	m_pSEHitSlime = CSound::LoadSound("Assets/Sound/SE/SlimeHitSlime.mp3");		//�n���}�[��U��������SE�̓ǂݍ���
	m_pSEUnion = CSound::LoadSound("Assets/Sound/SE/Union.mp3");		//�X���C���������������̂�SE�̓ǂݍ���


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

	SAFE_DELETE(m_pVS);
	SAFE_DELETE(m_pFlameModel);
	SAFE_DELETE(m_pRedModel);
	SAFE_DELETE(m_pYellowModel);
	SAFE_DELETE(m_pGreenModel);
	SAFE_DELETE(m_pBlueModel);

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
	CheckEscape();	//Update�̑O�ɋ߂��ɔ��������邩�m�F����

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
			m_pSlime[i] = new CSlime_1(CreatePos,m_pVS,m_pBlueModel);	// ���I����
			break;
		case LEVEL_2:
			m_pSlime[i] = new CSlime_2(CreatePos, m_pVS, m_pGreenModel);	// ���I����
			break;
		case LEVEL_3:
			m_pSlime[i] = new CSlime_3(CreatePos, m_pVS, m_pYellowModel);	// ���I����
			break;
		case LEVEL_4:
			m_pSlime[i] = new CSlime_4(CreatePos, m_pVS, m_pRedModel);	// ���I����
			break;
		case LEVEL_FLAME:
			m_pSlime[i] = new CSlime_Flame(CreatePos,m_pVS,m_pFlameModel);	// ���I����
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
	tagTransform3d hitSlimeTransform, standSlimeTransform;		//���[���h���W�n
	float hitSlimeSpeed, standSlimeSpeed;						// �ړ��X�s�[�h
	float travelAngle, reflectionAngle;							// �ړ�����

	hitSlimeLevel = m_pSlime[HitSlimeNum]->GetSlimeLevel();		// �Փ˂���X���C���̃T�C�Y���擾
	hitSlimeTransform = m_pSlime[HitSlimeNum]->GetTransform();	// �Փ˂���X���C���̃��[���h���W�����擾
	hitSlimeSpeed = m_pSlime[HitSlimeNum]->GetSpeed();			// �Փ˂���X���C���̑��x���擾

	standSlimeLevel = m_pSlime[StandSlimeNum]->GetSlimeLevel();	// �Փ˂��ꂽ�X���C���̃T�C�Y���擾
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
		m_pSlime[HitSlimeNum]->HitMoveStart(hitSlimeSpeed * COL_SUB_HIT_TO_BIG, reflectionAngle);	// �Փ˂���X���C���ɐ�����шړ�����
		m_pSlime[StandSlimeNum]->HitMoveStart(hitSlimeSpeed * COL_SUB_STAND_TO_SMALL, travelAngle);	// �Փ˂��ꂽ�X���C���ɐ�����шړ�����
		m_pSEHitSlimeSpeaker = CSound::PlaySound(m_pSEHitSlime);									// SE�̍Đ�
	}
	
	// �Փ˂���X���C�����傫���ꍇ(�偨��)
	else if (hitSlimeLevel > standSlimeLevel)
	{
		m_pSlime[HitSlimeNum]->HitMoveStart(hitSlimeSpeed * COL_SUB_HIT_TO_SMALL, travelAngle);		// �Փ˂���X���C���ɐ�����шړ�����
		m_pSlime[StandSlimeNum]->HitMoveStart(hitSlimeSpeed * COL_SUB_STAND_TO_BIG, travelAngle);	// �Փ˂��ꂽ�X���C���ɐ�����шړ�����
		m_pSEHitSlimeSpeaker = CSound::PlaySound(m_pSEHitSlime);									// SE�̍Đ�
	}
	//�X���C���̃T�C�Y�������������ꍇ
	else
	{
		SAFE_DELETE(m_pSlime[HitSlimeNum]);								// �Փ˂���X���C�����폜
		SAFE_DELETE(m_pSlime[StandSlimeNum]);							// �Փ˂��ꂽ�X���C�����폜

		if (hitSlimeLevel == MAX_LEVEL)	//�X���C���̃T�C�Y���ő�̎�
		{
			//�X���C����������
			pExpMng->Create(pos, MAX_SIZE_EXPLODE * EXPLODE_BASE_RATIO, LEVEL_4_EXPLODE_TIME, E_SLIME_LEVEL::LEVEL_4x4);	//�Փ˂��ꂽ�X���C���̈ʒu�Ń��x���S����
			m_pScoreOHMng->DisplayOverheadScore(pos, LEVEL_4_SCORE * 2, LEVEL_4_HEIGHT);
			pExpMng->CreateUI(pos, LEVEL_4_EXPLODE_TIME);		//���x���S���������ʒuboooomUI�\��
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
	tagTransform3d hitSlimeTransform, standSlimeTransform;				//���[���h�s��Ɋւ����

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
		m_pSEHitSlimeSpeaker = CSound::PlaySound(m_pSEHitSlime);									//SE�̍Đ�

		return true;
	}
	// �t���C���@���@�m�[�}��
	else if (hitSlimeLevel == LEVEL_FLAME)
	{
		pExpMng->SwitchExplode(standSlimeLevel, standSlimeTransform.fPos,standSlimeSize);	//�X���C���̃��x���ɂ���Ĕ����̎��ԂƃT�C�Y�𕪊�
		m_pScoreOHMng->DisplayOverheadScore(standSlimeTransform.fPos, standSlimeLevel);
		SAFE_DELETE(m_pSlime[HitSlimeNum]);								// �Փ˂���X���C�����폜
		SAFE_DELETE(m_pSlime[StandSlimeNum]);							// �Փ˂��ꂽ�X���C�����폜

		return true;
	}
	// �m�[�}���@���@�t���C��
	else if (standSlimeLevel == LEVEL_FLAME)
	{
		pExpMng->SwitchExplode(hitSlimeLevel, hitSlimeTransform.fPos, hitSlimeSize);	//�X���C���̃��x���ɂ���Ĕ����̎��ԂƃT�C�Y�𕪊�
		m_pScoreOHMng->DisplayOverheadScore(hitSlimeTransform.fPos, hitSlimeLevel);

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
			m_pSlime[i] = new CSlime_2(pos, m_pVS, m_pGreenModel);
			break;
		case LEVEL_2:
			//�T�C�Y3�̃X���C���𐶐�
			m_pSlime[i] = new CSlime_3(pos, m_pVS, m_pYellowModel);
			break;
		case LEVEL_3:
			//�T�C�Y4�̃X���C���𐶐�
			m_pSlime[i] = new CSlime_4(pos, m_pVS, m_pRedModel);
			break;
		}

		m_pSlime[i]->SetCamera(m_pCamera);	//�J�������Z�b�g
		m_pSEUnionSpeaker = CSound::PlaySound(m_pSEUnion);	//SE�̍Đ�

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
void CSlimeManager::TouchExplosion(int DelSlime, CExplosionManager * pExpMng, int comboNum)
{
	TPos3d<float> pos(m_pSlime[DelSlime]->GetPos());			// �Փː�̃X���C���̈ʒu���m��
	E_SLIME_LEVEL level = m_pSlime[DelSlime]->GetSlimeLevel();	// �Փː�̃X���C���̃��x�����m��
	TTriType<float> size = m_pSlime[DelSlime]->GetScale();		// �Փː�̃X���C���T�C�Y���m��

	pExpMng->SwitchExplode(level, pos, size, comboNum);
	m_pScoreOHMng->DisplayOverheadScore(pos, level);
	//�g�[�^���X�R�A�ilevel,combo)
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
	tagSphereInfo::Sphere standSlimeSphere = pStandSlime->GetSphere();						//�Փ˂��ꂽ�X���C����Sphere���擾
	tagSphereInfo::Sphere moveSlimeSphere = pMoveSlime->GetSphere();						//�Փ˂����X���C����Sphere���擾
	float standSlimeToPlayerAngle = standSlimeSphere.Angle(m_pPlayer->GetPlayerSphere());	//�Փ˂��ꂽ�X���C������Player�ւ̊p�x���擾
	float standSlimeToMoveSlimeAngle = standSlimeSphere.Angle(moveSlimeSphere);				//�Փ˂��ꂽ�X���C������Փ˂����X���C���ւ̊p�x���擾
	float Distance = standSlimeSphere.Distance(pMoveSlime->GetSphere());					//�X���C�����m�̋������擾
	float posX, posY, posZ;																	//���W

	if (standSlimeToMoveSlimeAngle < 0) { standSlimeToMoveSlimeAngle = (2 * PI) + standSlimeToMoveSlimeAngle; }	//
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
	���f���ǂݍ��݊֐�
	----------------------------------------
	���e�F�X���C���̃��f���ƒ��_�V�F�[�_�[�̓ǂݍ���
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F
======================================== */
void CSlimeManager::LoadModel()
{
	//���_�V�F�[�_�ǂݍ���
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}
	//���x��1�X���C���̃��f���ǂݍ���
	m_pBlueModel = new Model;
	if (!m_pBlueModel->Load("Assets/Model/slime/slime_blue1.28.FBX", 0.15f, Model::XFlip)) {		//�{���Ɣ��]�͏ȗ���
		MessageBox(NULL, "slime_blue", "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
	}
	m_pBlueModel->SetVertexShader(m_pVS);
	//���x��2�X���C���̃��f���ǂݍ���
	m_pGreenModel = new Model;
	if (!m_pGreenModel->Load("Assets/Model/slime/slime_green1.28.FBX", 0.15f, Model::XFlip)) {		//�{���Ɣ��]�͏ȗ���
		MessageBox(NULL, "slime_green", "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
	}
	m_pGreenModel->SetVertexShader(m_pVS);
	//���x��3�X���C���̃��f���ǂݍ���
	m_pYellowModel = new Model;
	if (!m_pYellowModel->Load("Assets/Model/slime/slime_Yellow1.28.FBX", 0.15f, Model::XFlip)) {		//�{���Ɣ��]�͏ȗ���
		MessageBox(NULL, "slime_yellow", "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
	}
	m_pYellowModel->SetVertexShader(m_pVS);
	//���x��4�X���C���̃��f���ǂݍ���
	m_pRedModel = new Model;
	if (!m_pRedModel->Load("Assets/Model/slime/slime_red1.28.FBX", 0.18f, Model::XFlip)) {		//�{���Ɣ��]�͏ȗ���
		MessageBox(NULL, "slime_red", "Error", MB_OK);		//�����ŃG���[���b�Z�[�W�\��
	}
	m_pRedModel->SetVertexShader(m_pVS);
	//�t���C���X���C���̃��f���ǂݍ���
	m_pFlameModel = new Model;
	if (!m_pFlameModel->Load("Assets/Model/Golem/Golem.FBX", 0.015f, Model::XFlip)) {		//�{���Ɣ��]�͏ȗ���
		MessageBox(NULL, "Flame_Slime", "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
	}
	m_pFlameModel->SetVertexShader(m_pVS);
}


/* ========================================
	��������֐�
	----------------------------------------
	���e�F�X���C���Ɣ����̈ʒu�֌W���m�F���ē����邩�ǂ������肷��
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CSlimeManager::CheckEscape()
{
	for (int j = 0; j < MAX_SLIME_NUM; j++)
	{
		if (!m_pSlime[j]) { continue; }						//nullptr�Ȃ�X�L�b�v
		if (m_pSlime[j]->GetEscapeFlag()) { continue; }		//���łɓ����Ă���Ȃ�X�L�b�v

		TPos3d<float> slimePos = m_pSlime[j]->GetPos();	//�X���C���̍��W���Q�b�g
		float distance = ESCAPE_DISTANCE;				//�������ԂɂȂ�ő勗�����Z�b�g
		//�͈͓��ɔ���������Γ����邽�߂̃t���O�ƍ��W���Z�b�g
		for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
		{
			CExplosion* pExp = m_pExpMng->GetExplosionPtr(i);	//�����̃|�C���^���擾
			if (!pExp) { continue; }							//nullptr�Ȃ�X�L�b�v
			TPos3d<float> expPos = pExp->GetPos();				//�����̍��W���Q�b�g
			float slimeExpDistance = slimePos.Distance(expPos);
			if (distance > slimeExpDistance)	//���߂����������������ꍇ
			{
				distance = slimeExpDistance;
				m_pSlime[j]->SetExplosionPos(expPos);	//�����̍��W���X���C���ɃZ�b�g
				m_pSlime[j]->SetEscapeFlag(true);		//������t���O��ON�ɂ���
			}
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
void CSlimeManager::SetPlayerPos(TPos3d<float> pos)
{
	m_pPlayerPos = pos;
}

/* ========================================
	�����}�l�[�W���[�̃|�C���^�Z�b�g�֐�
	----------------------------------------
	���e�F�����}�l�[�W���[�̃|�C���^���Z�b�g����
	----------------------------------------
	����1�F�����}�l�[�W���[�̃|�C���^
	----------------------------------------
	�ߒl�F����
======================================== */
void CSlimeManager::SetExplosionMng(CExplosionManager* pExpMng)
{
	m_pExpMng = pExpMng;
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

/* ========================================
	�X�R�A���Z�b�g�֐�
	----------------------------------------
	���e�F�����������ɕK�v�ȃX�R�A���Z�b�g
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CSlimeManager::SetScoreOHMng(CScoreOHManager * pScoreMng)
{
	m_pScoreOHMng = pScoreMng;
}
