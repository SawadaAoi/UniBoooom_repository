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
	�E2023/11/20 �{�X�p�̔z���ǉ�
	�E2023/11/21 �{�X�p�̓����蔻�莞�̏���(HitSlimeBossBranch...etc)��ǉ�
	�E2023/11/21 �{�X�p�̒ʏ펞�̏���(PreventSlimeBossOverlap...etc)��ǉ�
	�E2023/11/21 BoooomUi�\������֐����Ăяo�� Tei
	�E2023/11/23 �X���C���̐����ʒu���v���C���[���S�ɕύX yamashita
	�E2023/11/23 �X���C���̐����ʒu���O��̐����ʒu������ȏ㗣���悤�ɕύX	yamashita
	�E2023/11/23 �X���C�����v���C���[������ȏ㗣���ƑΊp����Ɉړ�����悤�ɕύX yamashita
	�E2023/11/26 �{�X�����p�֐��ǉ�	Sawada
	�E2023/11/26 �X���C���Ɣ����̋����𒲂ד����邩���肷��֐����쐬 yamashita
	�E2023/11/27 �ԐԂ̔����������Ƀq�b�g�X�g�b�v�Ɖ�ʗh�ꂷ��悤�ɏC��	Sawada
	�E2023/11/29 ��ʗh����������c���ɕύX takagi
	�E2023/11/29 �v���C���[�̃|�C���^���擾 yamashita
	�E2023/11/30 ���f���̓ǂݍ��݂�Maya��������DirectX�����ɕύX yamashita
	�E2023/11/30 �U������ӏ����݁E�q�b�g�X�g�b�v�����E�΃X���C���ƐԃX���C���Փˎ��ɐU������ takagi

=========================================== */

// =============== �C���N���[�h ===================
#include "SlimeManager.h"
#include "Slime_1.h"
#include "Slime_2.h"
#include "Slime_3.h"
#include "Slime_4.h"
#include "Slime_Flame.h"
#include "Slime_Boss_1.h"
#include "Input.h"		//��ŏ���
#include "GameParameter.h"		//�萔��`�p�w�b�_�[
#include "HitStop.h"

#include <stdlib.h>

// =============== �萔��` =======================
#if MODE_GAME_PARAMETER
#else
#define DEBUG_BOSS	(false)						// �f�o�b�O�p�ɃQ�[���J�n���{�X�𐶐����邩�ǂ���

const int ENEMY_CREATE_INTERVAL		= int(3.0f * 60);		// �����Ԋu
const int ENEMY_CREATE_INTERVAL_LV2 = int(2.0f * 60);		// �����Ԋu���炷
const int ENEMY_CREATE_INTERVAL_LV3 = int(1.0f * 60);		// �����Ԋu����Ɍ��炷
const int RANDOM_POS			= 15;			// �������W�͈�
const int CREATE_DISTANCE		= 10;			// ���������ŏ��l
const int SLIME_LEVEL1_PER		= 10;			// �X���C��_1�̐����m��
const int SLIME_LEVEL2_PER		= 15;			// �X���C��_2�̐����m��
const int SLIME_LEVEL3_PER		= 10;			// �X���C��_3�̐����m��
const int SLIME_LEVEL_FLAME_PER	= 100 - SLIME_LEVEL1_PER - SLIME_LEVEL2_PER - SLIME_LEVEL3_PER;	// �X���C��_�t���C���̐����m��

const int START_ENEMY_NUM		= 10;			// �Q�[���J�n���̓G�L�����̐�

// ��1.0f�ł��̂܂�
const float COL_SUB_HIT_TO_BIG = 0.7f;				// �X���C���Փ�(������)�̏Փˑ��̌��Z�l(���˂���ړ�)
const float COL_SUB_STAND_TO_SMALL = 0.3f;			// �X���C���Փ�(������)�̏Փ˂���鑤�̌��Z�l(�Փ˂��ꂽ����)
const float COL_SUB_HIT_TO_SMALL = 0.3f;			// �X���C���Փ�(�偨��)�̏Փˑ��̌��Z�l(�ړ�����)
const float COL_SUB_STAND_TO_BIG = 1.2f;			// �X���C���Փ�(�偨��)�̏Փ˂���鑤�̌��Z�l(�Փ˂��ꂽ����)
const float LEAVE_DISTANCE = 20.0f;					// ����ȏ㗣�ꂽ��Ίp����Ɉړ�����

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
CSlimeManager::CSlimeManager(CPlayer* pPlayer)
	: m_CreateCnt(0)
	, m_pVS(nullptr)
	, m_pBlueModel(nullptr)
	, m_pGreenModel(nullptr)
	, m_pYellowModel(nullptr)
	, m_pRedModel(nullptr)
	, m_pFlameModel(nullptr)
	, m_pBossModel{nullptr,nullptr}
	, m_pSEHitSlime(nullptr)
	, m_pSEUnion(nullptr)
	, m_pSEHitSlimeSpeaker(nullptr)
	, m_pSEUnionSpeaker(nullptr)
	, m_oldCreatePos{ 0.0f,0.0f,0.0f }
	, m_pPlayer(pPlayer)
	, m_pExpMng(nullptr)
	, m_pTimer(nullptr)
{
	//�X���C���̃��f���ƒ��_�V�F�[�_�[�̓ǂݍ���
	LoadModel();
	
	// �X���C��������
	for (int i = 0; i <MAX_SLIME_NUM; i++)
	{
		m_pSlime[i] = nullptr;
	}
	// �{�X�X���C��������
	for (int i = 0; i < MAX_BOSS_SLIME_NUM; i++)
	{
		m_pBoss[i] = nullptr;
	}

	
	// �Q�[���J�n���ɓG�L�����𐶐�����
	for (int i = 0; i < START_ENEMY_NUM; i++)
	{
		int ranLv = rand() % 3 + 1;		// ��������X���C���̃��x���𗐐��Ŏw��
		Create((E_SLIME_LEVEL)ranLv);	// ��������
	}

#if DEBUG_BOSS
	// �J�n���{�X����
	for (int i = 0; i < MAX_BOSS_SLIME_NUM; i++)
	{
		// �X���C����use������
		if (m_pBoss[i] != nullptr) continue;
		m_pBoss[i] = new CSlime_Boss_1(TPos3d<float>(5.0f,0.0f,3.0f), m_pVS, m_pBossModel);	//���I����

		break;
	}
#endif
	

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
	SAFE_DELETE(m_pBossModel[0]);
	SAFE_DELETE(m_pBossModel[1]);

	// �X���C���폜
	for (int i = 0; i <MAX_SLIME_NUM; i++)
	{
		SAFE_DELETE(m_pSlime[i]);
	}

	// �{�X�X���C���폜
	for (int i = 0; i < MAX_BOSS_SLIME_NUM; i++)
	{
		SAFE_DELETE(m_pBoss[i]);
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
	for (int i = 0; i <MAX_SLIME_NUM; i++)
	{
		if (m_pSlime[i] == nullptr) continue;
		m_pSlime[i]->Update(m_pPlayer->GetTransform(), m_pTimer->GetSlimeMoveSpeed());

	}

	OutOfRange();	//�X���C�����v���C���[�����苗�����ꂽ��Ίp���Ɉړ�

	// �{�X�X���C���X�V
	for (int i = 0; i < MAX_BOSS_SLIME_NUM; i++)
	{
		if (m_pBoss[i] == nullptr) continue;
		m_pBoss[i]->Update(m_pPlayer->GetTransform());

	}

	//---�G����---
	m_CreateCnt++;
	if (m_pTimer->GetSlimeCreateInterval() <= m_CreateCnt)
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
	//"�X���C��"�`��
	for (int i = 0; i <MAX_SLIME_NUM; i++)
	{
		if (m_pSlime[i] == nullptr) continue;
		m_pSlime[i]->Draw(m_pCamera);
	}
				
	// �{�X�X���C���X�V
	for (int i = 0; i < MAX_BOSS_SLIME_NUM; i++)
	{
		if (m_pBoss[i] == nullptr) continue;
		m_pBoss[i]->Draw(m_pCamera);

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

	int mMaxNum;
	if (m_pTimer == nullptr)
	{
		mMaxNum = SLM_CREATE_NUM[STATE_FIRST];
	}
	else
	{
		mMaxNum = m_pTimer->GetMaxSlimeNum();
	}

	for (int i = 0; i < mMaxNum; i++)
	{
		// �X���C����use������
		if (m_pSlime[i] != nullptr) continue;

		// �K�؂ȍ��W���o��܂ŌJ��Ԃ�
		while (true)
		{
			// �������Z�b�g����
			CreatePos.x = float(GetRandom(int(m_pPlayer->GetPos().x - RANDOM_POS), int(m_pPlayer->GetPos().x + RANDOM_POS)));	//�����擾
			CreatePos.z = float(GetRandom(int(m_pPlayer->GetPos().z - RANDOM_POS), int(m_pPlayer->GetPos().z + RANDOM_POS)));
			CreatePos.y = 0;

			float PlayerCreateDistance = CreatePos.Distance(m_pPlayer->GetPos());	// �������W�̃v���C���[�Ƃ̋���
			float oldCreateDistance = CreatePos.Distance(m_oldCreatePos);	// �������W�̃v���C���[�Ƃ̋���

			// �v���C���[������̋�������Ă���Δ�����
			if (PlayerCreateDistance >= CREATE_DISTANCE && oldCreateDistance >= CREATE_DISTANCE) break;	
		}

		m_oldCreatePos = CreatePos;	//�������W��ێ�
		
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
	�{�X�X���C�������֐�
	-------------------------------------
	���e�F�{�X�X���C���̐���
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSlimeManager::CreateBoss()
{
	for (int i = 0; i < MAX_BOSS_SLIME_NUM; i++)
	{
		// �X���C����use������
		if (m_pBoss[i] != nullptr) continue;
		m_pBoss[i] = new CSlime_Boss_1(TPos3d<float>(0.0f, 0.0f, 0.0f), m_pVS, m_pBossModel[0], m_pBossModel[1]);	//���I����(��荇�����ʒu�͉�)

		break;
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
	float hitSlimeSpeed;						// �ړ��X�s�[�h
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
			pExpMng->Create(pos, MAX_SIZE_EXPLODE * EXPLODE_BASE_RATIO, LEVEL_4_EXPLODE_TIME, LEVEL_4_EXPLODE_DAMAGE, E_SLIME_LEVEL::LEVEL_4x4);	//�Փ˂��ꂽ�X���C���̈ʒu�Ń��x���S����
			m_pScoreOHMng->DisplayOverheadScore(pos, LEVEL_4_SCORE * 2, SLIME_SCORE_HEIGHT);
			pExpMng->CreateUI(pos, LEVEL_4_EXPLODE_TIME);		//���x���S���������ʒuboooomUI�\��

			m_pCamera->UpFlag(CCamera::E_BIT_FLAG_VIBRATION_UP_DOWN_STRONG | CCamera::E_BIT_FLAG_VIBRATION_SIDE_STRONG);
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

		//�ԃX���C��(Stand)�ƌ��˂����Ƃ����������̐U����傫������
		if (typeid(CSlime_4) == typeid(*m_pSlime[HitSlimeNum]))
		{
			m_pCamera->UpFlag(CCamera::E_BIT_FLAG_VIBRATION_UP_DOWN_STRONG | CCamera::E_BIT_FLAG_VIBRATION_SIDE_STRONG);
		}
		else
		{
			m_pCamera->UpFlag(CCamera::E_BIT_FLAG_VIBRATION_UP_DOWN_STRONG | CCamera::E_BIT_FLAG_VIBRATION_SIDE_WEAK);
		}

		SAFE_DELETE(m_pSlime[HitSlimeNum]);								// �Փ˂���X���C�����폜
		SAFE_DELETE(m_pSlime[StandSlimeNum]);							// �Փ˂��ꂽ�X���C�����폜

		return true;
	}
	// �m�[�}���@���@�t���C��
	else if (standSlimeLevel == LEVEL_FLAME)
	{
		pExpMng->SwitchExplode(hitSlimeLevel, hitSlimeTransform.fPos, hitSlimeSize);	//�X���C���̃��x���ɂ���Ĕ����̎��ԂƃT�C�Y�𕪊�
		m_pScoreOHMng->DisplayOverheadScore(hitSlimeTransform.fPos, hitSlimeLevel);

		//�ԃX���C��(Hit)�ƌ��˂����Ƃ����������̐U����傫������
		if (typeid(CSlime_4) == typeid(*m_pSlime[HitSlimeNum]))
		{
			m_pCamera->UpFlag(CCamera::E_BIT_FLAG_VIBRATION_UP_DOWN_STRONG | CCamera::E_BIT_FLAG_VIBRATION_SIDE_STRONG);
		}
		else
		{
			m_pCamera->UpFlag(CCamera::E_BIT_FLAG_VIBRATION_UP_DOWN_STRONG | CCamera::E_BIT_FLAG_VIBRATION_SIDE_WEAK);
		}

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
	for (int i = 0; i <MAX_SLIME_NUM; i++)
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

}

/* ========================================
	�X���C�����{�X�ڐG����֐�
	----------------------------------------
	���e�F�X���C������{�X�Ƃ̐ڐG�𐳂��������ɕ��򂳂���
	----------------------------------------
	����1�F�Փ˂���X���C���̔z��ԍ�
	����2�F�Փ˂��ꂽ�X���C���̔z��ԍ�
	����3�F�����}�l�[�W���[
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CSlimeManager::HitSlimeBossBranch(int HitSlimeNum, int StandBossNum, CExplosionManager* pExpMng)
{
	E_SLIME_LEVEL hitSlimeLevel;								// ���x��
	E_SLIME_LEVEL standBossLevel;								// ���x��(�{�X)
	tagTransform3d hitSlimeTransform;							// ���[���h���W�n
	tagTransform3d standBossTransform;							// ���[���h���W�n(�{�X)
	TTriType<float> hitSlimeSize;								// �T�C�Y���m��						
	float hitSlimeSpeed;										// �ړ��X�s�[�h
	float travelAngle, reflectionAngle;							// �ړ�����

	// --�Q��
	// �m�[�}��
	hitSlimeLevel = m_pSlime[HitSlimeNum]->GetSlimeLevel();			// �Փ˂���X���C���̃T�C�Y���擾
	hitSlimeTransform = m_pSlime[HitSlimeNum]->GetTransform();		// �Փ˂���X���C���̃��[���h���W�����擾
	hitSlimeSpeed = m_pSlime[HitSlimeNum]->GetSpeed();				// �Փ˂���X���C���̑��x���擾
	hitSlimeSize = m_pSlime[HitSlimeNum]->GetScale();				// �Փː�̃X���C���̃T�C�Y���m��

	// �{�X
	standBossLevel = LEVEL_BOSS;									// �Փ˂���	�{�X�X���C���̃T�C�Y���擾
	standBossTransform = m_pBoss[StandBossNum]->GetTransform();		// �Փ˂���	�{�X�X���C���̃��[���h���W�����擾

	// ���̑�
	travelAngle = hitSlimeTransform.Angle(standBossTransform);		// �Փ˂��鑤�̐i�s����
	reflectionAngle = standBossTransform.Angle(hitSlimeTransform);	// �Փ˂��鑤�̋t����(����)

	//-- �t���C���X���C���q�b�g����
	// �t���C���@���@�{�X
	if (hitSlimeLevel == LEVEL_FLAME && standBossLevel == LEVEL_BOSS)
	{
		// �t���C�����������ă{�X�͎c��
		pExpMng->SwitchExplode(hitSlimeLevel, hitSlimeTransform.fPos, hitSlimeSize);	//�X���C���̃��x���ɂ���Ĕ����̎��ԂƃT�C�Y�𕪊�
		SAFE_DELETE(m_pSlime[HitSlimeNum]);												// �Փ˂���X���C�����폜
	}

	//-- �m�[�}���X���C���q�b�g����
	// �{�X���Փ˂����ꍇ(������)
	else if (hitSlimeLevel < standBossLevel)
	{
		m_pSlime[HitSlimeNum]->HitMoveStart(hitSlimeSpeed * COL_SUB_HIT_TO_BIG, reflectionAngle);			// �Փ˂���X���C���ɐ�����шړ�����
		m_pBoss[StandBossNum]->HitMoveStart(hitSlimeSpeed * COL_SUB_STAND_TO_SMALL, travelAngle);			// �Փ˂��ꂽ�X���C���ɐ�����шړ�����

	}

}

/* ========================================
	�{�X���X���C���ڐG����֐�
	----------------------------------------
	���e�F�{�X����X���C���Ƃ̐ڐG�𐳂��������ɕ��򂳂���
	----------------------------------------
	����1�F�Փ˂���X���C���̔z��ԍ�
	����2�F�Փ˂��ꂽ�X���C���̔z��ԍ�
	����3�F�����}�l�[�W���[
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CSlimeManager::HitBossSlimeBranch(int HitSlimeNum, int StandSlimeNum, CExplosionManager* pExpMng)
{
	E_SLIME_LEVEL standSlimeLevel;				// ���x��
	E_SLIME_LEVEL hitBossLevel;					// ���x��(�{�X)
	tagTransform3d standSlimeTransform;			// ���[���h���W�n
	tagTransform3d hitBossTransform;			// ���[���h���W�n(�{�X)
	TTriType<float> standSlimeSize;				// �T�C�Y���m��						
	float hitBossSpeed;							// �ړ��X�s�[�h(�{�X)
	float travelAngle, reflectionAngle;			// �ړ�����

	// --�Q��
	// // �m�[�}��
	standSlimeLevel = m_pSlime[StandSlimeNum]->GetSlimeLevel();		// �Փ˂���X���C���̃T�C�Y���擾
	standSlimeTransform = m_pSlime[StandSlimeNum]->GetTransform();	// �Փ˂���X���C���̃��[���h���W�����擾
	standSlimeSize = m_pSlime[StandSlimeNum]->GetScale();			// �X���C���̃T�C�Y���m��

	// �{�X
	hitBossLevel = LEVEL_BOSS;										// �Փ˂���	�{�X�X���C���̃T�C�Y���擾
	hitBossTransform = m_pBoss[HitSlimeNum]->GetTransform();		// �Փ˂���	�{�X�X���C���̃��[���h���W�����擾
	hitBossSpeed = m_pBoss[HitSlimeNum]->GetSpeed();				// �Փ˂���	�{�X�X���C���̑��x���擾	���{�X�͈��Ȃ͂�������ς�����
	
	// ���̑�
	travelAngle = hitBossTransform.Angle(standSlimeTransform);		// �Փ˂��鑤�̐i�s����
	reflectionAngle = standSlimeTransform.Angle(hitBossTransform);	// �Փ˂��鑤�̋t����(����)

	//-- �t���C���X���C���q�b�g����
	// �{�X�@���@�t���C��
	if (hitBossLevel == LEVEL_BOSS && standSlimeLevel == LEVEL_FLAME)
	{
		// �t���C�����������ă{�X�͎c��
		pExpMng->SwitchExplode(standSlimeLevel, standSlimeTransform.fPos, standSlimeSize);	//�X���C���̃��x���ɂ���Ĕ����̎��ԂƃT�C�Y�𕪊�
		SAFE_DELETE(m_pSlime[StandSlimeNum]);												// �Փ˂���X���C�����폜
	}

	//-- �m�[�}���X���C���q�b�g����
	// �{�X���Փ˂���ꍇ(�偨��) 
	else if (hitBossLevel > standSlimeLevel)
	{
		m_pBoss[HitSlimeNum]->HitMoveStart(hitBossSpeed * COL_SUB_HIT_TO_SMALL, travelAngle);				// �Փ˂���X���C���ɐ�����шړ�����
		m_pSlime[StandSlimeNum]->HitMoveStart(hitBossSpeed * COL_SUB_STAND_TO_BIG, travelAngle);			// �Փ˂��ꂽ�X���C���ɐ�����шړ�����

	}
}

/* ========================================
	�{�X���{�X�ڐG����֐�
	----------------------------------------
	���e�F�X���C������{�X�Ƃ̐ڐG�𐳂��������ɕ��򂳂���
	----------------------------------------
	����1�F�Փ˂���X���C���̔z��ԍ�
	����2�F�Փ˂��ꂽ�X���C���̔z��ԍ�
	����3�F�����}�l�[�W���[
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CSlimeManager::HitBossBossBranch(int HitBossNum, int StandBossNum, CExplosionManager* pExpMng)
{
	E_SLIME_LEVEL hitBossLevel, standBossLevel;					// ���x��(�{�X)
	tagTransform3d hitBossTransform, standBossTransform;		// ���[���h���W�n(�{�X)					
	float hitBossSpeed;											// �ړ��X�s�[�h(�{�X)
	float travelAngle, reflectionAngle;							// �ړ�����

	// --�Q��
	// �{�X
	hitBossLevel = LEVEL_BOSS;									// �Փ˂���	�{�X�X���C���̃T�C�Y���擾
	hitBossTransform = m_pBoss[HitBossNum]->GetTransform();		// �Փ˂���	�{�X�X���C���̃��[���h���W�����擾
	hitBossSpeed = m_pBoss[HitBossNum]->GetSpeed();				// �Փ˂���	�{�X�X���C���̑��x���擾	���{�X�͈��Ȃ͂�������ς�����
	standBossLevel = LEVEL_BOSS;								// �Փ˂���	�{�X�X���C���̃T�C�Y���擾
	standBossTransform = m_pBoss[StandBossNum]->GetTransform();	// �Փ˂���	�{�X�X���C���̃��[���h���W�����擾

	// ���̑�
	travelAngle = hitBossTransform.Angle(standBossTransform);		// �Փ˂��鑤�̐i�s����
	reflectionAngle = standBossTransform.Angle(hitBossTransform);	// �Փ˂��鑤�̋t����(����)

	// --�{�X���m�q�b�g����
	if (hitBossLevel == LEVEL_BOSS && standBossLevel == LEVEL_BOSS)
	{
		//(�偨��)�Ɠ����������s��
		m_pBoss[HitBossNum]->HitMoveStart(hitBossSpeed * COL_SUB_HIT_TO_SMALL, travelAngle);				// �Փ˂���X���C���ɐ�����шړ�����
		m_pBoss[StandBossNum]->HitMoveStart(hitBossSpeed * COL_SUB_STAND_TO_BIG, travelAngle);			// �Փ˂��ꂽ�X���C���ɐ�����шړ�����

	}
}

/* ========================================
	�����ڐG�֐�(�{�X)
	----------------------------------------
	���e�F��ʏ�̔����Ƀ{�X���ڐG�������̏���
	----------------------------------------
	����1�F�ڐG�����{�X�̔z��ԍ�(int)
	����2�F�����}�l�[�W���[�̃|�C���^
	����3�F�ڐG���������̔z��ԍ�(int)
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CSlimeManager::TouchBossExplosion(int BossNum, CExplosionManager* pExpMng, int ExpNum)
{
	CExplosion* touchExplosion = pExpMng->GetExplosionPtr(ExpNum);	// �ڐG�����������擾
	TPos3d<float> pos(m_pBoss[BossNum]->GetPos());					// �Փː�̃X���C���̈ʒu���m��
	E_SLIME_LEVEL level = m_pBoss[BossNum]->GetSlimeLevel();		// �Փː�̃X���C���̃��x�����m��
	TTriType<float> size = m_pBoss[BossNum]->GetScale();			// �Փː�̃X���C���T�C�Y���m��

	// ���ɐڐG�ς݂�����
	if (touchExplosion->GetBossTouched() == false)
	{
		// �����З͕��̃_���[�W���{�X�ɗ^����
		m_pBoss[BossNum]->Damage(pExpMng->GetExplosionPtr(ExpNum)->GetDamage());
		// ��x�_���[�W��^�����瓯�������ł̓_���[�W��^���Ȃ�
		touchExplosion->BossTouched();
	}
	// ���S����
	if (m_pBoss[BossNum]->IsDead() == true)
	{
		SAFE_DELETE(m_pBoss[BossNum]);	//�Ԃ���ɗ����X���C��(�{�X)���폜
		
		pExpMng->SwitchExplode(level, pos, size, pExpMng->GetExplosionPtr(ExpNum)->GetComboNum());	// ��������
		m_pScoreOHMng->DisplayOverheadScore(pos, LEVEL_Boss_SCORE, SLIME_SCORE_HEIGHT);
		m_pHealItemMng->Create(pos);

	}

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
	�X���C���ƃX���C�����d�Ȃ�Ȃ��֐�
	----------------------------------------
	���e�F�Ԃ������X���C�������������߂����֐�
	----------------------------------------
	����1�F�Փ˂����X���C���̃|�C���^
	����2�F�Փ˂��ꂽ�X���C���̃|�C���^
	----------------------------------------
	�ߒl�F����
======================================== */
void CSlimeManager::PreventSlimeSlimeOverlap(CSlimeBase * pMoveSlime, CSlimeBase * pStandSlime)
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
	�X���C�����{�X���d�Ȃ�Ȃ��֐�
	----------------------------------------
	���e�F�Ԃ������X���C�������������߂����֐�
	----------------------------------------
	����1�F�Փ˂����X���C���̃|�C���^
	����2�F�Փ˂��ꂽ�{�X�̃|�C���^
	----------------------------------------
	�ߒl�F����
======================================== */
void CSlimeManager::PreventSlimeBossOverlap(CSlimeBase* pMoveSlime, CSlime_BossBase* pStandBoss)
{

	float angle = pStandBoss->GetTransform().Angle(pMoveSlime->GetTransform());				//�Փ˂��Ă����p�x
	float distance = pStandBoss->GetSphere().fRadius + pMoveSlime->GetSphere().fRadius;	//���݂��̃X���C���̔��a�𑫂�����

	TPos3d<float> pos = pStandBoss->GetPos();		//�����߂���̍��W
	pos.x += cosf(angle) * (distance + 0.001f);		//�Ԃ���Ȃ��M���M���̋�����ݒ�
	pos.z += sinf(angle) * (distance + 0.001f);		//�Ԃ���Ȃ��M���M���̋�����ݒ�

	pMoveSlime->SetPos(pos);						//�Ԃ���Ȃ��M���M���̋����Ɉړ�
}

/* ========================================
	�{�X���X���C�����d�Ȃ�Ȃ��֐�
	----------------------------------------
	���e�F�Ԃ���ꂽ�X���C�������������߂����֐�
	----------------------------------------
	����1�F�Փ˂����X���C���̃|�C���^
	����2�F�Փ˂��ꂽ�X���C���̃|�C���^
	----------------------------------------
	�ߒl�F����
======================================== */
void CSlimeManager::PreventBossSlimeOverlap(CSlime_BossBase* pMoveBoss, CSlimeBase* pStandSlime)
{

	float angle = pStandSlime->GetTransform().Angle(pMoveBoss->GetTransform());				//�Փ˂��Ă����p�x
	float distance = pStandSlime->GetSphere().fRadius + pMoveBoss->GetSphere().fRadius;	//���݂��̃X���C���̔��a�𑫂�����

	TPos3d<float> pos = pStandSlime->GetPos();		//�����߂���̍��W
	pos.x += cosf(angle) * (distance + 0.001f);		//�Ԃ���Ȃ��M���M���̋�����ݒ�
	pos.z += sinf(angle) * (distance + 0.001f);		//�Ԃ���Ȃ��M���M���̋�����ݒ�

	pStandSlime->SetPos(pos);						//�Ԃ���Ȃ��M���M���̋����Ɉړ�
}

/* ========================================
	�{�X�ƃ{�X���d�Ȃ�Ȃ��֐�
	----------------------------------------
	���e�F�Ԃ������{�X�����������߂����֐�
	----------------------------------------
	����1�F�Փ˂����X���C���̃|�C���^
	����2�F�Փ˂��ꂽ�X���C���̃|�C���^
	----------------------------------------
	�ߒl�F����
======================================== */
void CSlimeManager::PreventBossBossOverlap(CSlime_BossBase* pMoveBoss, CSlime_BossBase* pStandBoss)
{

	float angle = pStandBoss->GetTransform().Angle(pMoveBoss->GetTransform());				//�Փ˂��Ă����p�x
	float distance = pStandBoss->GetSphere().fRadius + pMoveBoss->GetSphere().fRadius;	//���݂��̃X���C���̔��a�𑫂�����

	TPos3d<float> pos = pStandBoss->GetPos();		//�����߂���̍��W
	pos.x += cosf(angle) * (distance + 0.001f);		//�Ԃ���Ȃ��M���M���̋�����ݒ�
	pos.z += sinf(angle) * (distance + 0.001f);		//�Ԃ���Ȃ��M���M���̋�����ݒ�

	pMoveBoss->SetPos(pos);						//�Ԃ���Ȃ��M���M���̋����Ɉړ�
}

/* ========================================
	���f���ǂݍ��݊֐�
	----------------------------------------
	���e�F�X���C���̃��f���ƒ��_�V�F�[�_�[�̓ǂݍ���
	----------------------------------------
	����1�F����
	----------------------------------------
	�ߒl�F����
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
	if (!m_pBlueModel->Load("Assets/Model/slime/slime_blue1.28.FBX", 0.15f, Model::ZFlip)) {		//�{���Ɣ��]�͏ȗ���
		MessageBox(NULL, "slime_blue", "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
	}
	m_pBlueModel->SetVertexShader(m_pVS);
	//���x��2�X���C���̃��f���ǂݍ���
	m_pGreenModel = new Model;
	if (!m_pGreenModel->Load("Assets/Model/slime/slime_green1.28.FBX", 0.15f, Model::ZFlip)) {		//�{���Ɣ��]�͏ȗ���
		MessageBox(NULL, "slime_green", "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
	}
	m_pGreenModel->SetVertexShader(m_pVS);
	//���x��3�X���C���̃��f���ǂݍ���
	m_pYellowModel = new Model;
	if (!m_pYellowModel->Load("Assets/Model/slime/slime_Yellow1.28.FBX", 0.15f, Model::ZFlip)) {		//�{���Ɣ��]�͏ȗ���
		MessageBox(NULL, "slime_yellow", "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
	}
	m_pYellowModel->SetVertexShader(m_pVS);
	//���x��4�X���C���̃��f���ǂݍ���
	m_pRedModel = new Model;
	if (!m_pRedModel->Load("Assets/Model/slime/slime_red1.28.FBX", 0.18f, Model::ZFlip)) {		//�{���Ɣ��]�͏ȗ���
		MessageBox(NULL, "slime_red", "Error", MB_OK);		//�����ŃG���[���b�Z�[�W�\��
	}
	m_pRedModel->SetVertexShader(m_pVS);
	//�t���C���X���C���̃��f���ǂݍ���
	m_pFlameModel = new Model;
	if (!m_pFlameModel->Load("Assets/Model/Golem/Golem.FBX", 0.015f, Model::ZFlip)) {		//�{���Ɣ��]�͏ȗ���
		MessageBox(NULL, "Flame_Slime", "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
	}
	m_pFlameModel->SetVertexShader(m_pVS);
	//�{�X�X���C���̃��f���ǂݍ���
	m_pBossModel [0]= new Model;
	if (!m_pBossModel[0]->Load("Assets/Model/boss_slime_1/boss_slime_1.fbx", 0.23f, Model::ZFlip)) {		//�{���Ɣ��]�͏ȗ���
		MessageBox(NULL, "Boss_Slime", "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
	}

	m_pBossModel[0]->SetVertexShader(m_pVS);
	//�{�X�X���C���̃��f���ǂݍ���
	m_pBossModel[1] = new Model;
	if (!m_pBossModel[1]->Load("Assets/Model/boss_slime_1/boss_slime_rush_1.fbx", 0.23f, Model::ZFlip)) {		//�{���Ɣ��]�͏ȗ���
		MessageBox(NULL, "Boss_Slime", "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
	}

	m_pBossModel[1]->SetVertexShader(m_pVS);
}

/* ========================================
	�͈͊O�X���C���ړ��֐�
	----------------------------------------
	���e�F�v���C���[���痣�ꂷ�����X���C�����v���C���[���猩���Ίp���̈ʒu�Ɉړ�
	----------------------------------------
	�����F�Q�b�g�������X���C���̗v�f�ԍ�
	----------------------------------------
	�ߒl�F�X���C���̔z��
======================================== */
void CSlimeManager::OutOfRange()
{
	for (int i = 0; i <MAX_SLIME_NUM; i++)
	{
		if (!m_pSlime[i]) { continue; }	//null�Ȃ�X�L�b�v

		TPos3d<float> slimePos = m_pSlime[i]->GetPos();
		float distance = slimePos.Distance(m_pPlayer->GetPos());

		if (distance >= LEAVE_DISTANCE)	//���������ꂷ���Ă�����
		{
			//���΋������v�Z
			float disX = m_pPlayer->GetPos().x - slimePos.x;
			float disZ = m_pPlayer->GetPos().z - slimePos.z;

			//�����߂Â��Ă���Ίp���Ɉړ�������
			if (disX > 0.0f) { disX -= 1.0f; }
			else { disX += 1.0f; }
			if (disZ > 0.0f) { disZ -= 1.0f; }
			else { disZ += 1.0f; }
			//�Ίp���̍��W���Z�b�g
			TPos3d<float> setPos = { m_pPlayer->GetPos().x + disX,0.0f,m_pPlayer->GetPos().z + disZ};
			m_pSlime[i]->SetPos(setPos);
		}
	}
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
	for (int j = 0; j <MAX_SLIME_NUM; j++)
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
	�{�X�X���C���z��擾�֐�
	----------------------------------------
	���e�F�{�X�X���C���z��̎擾
	----------------------------------------
	����1�F�Q�b�g�������{�X�X���C���̗v�f�ԍ�
	----------------------------------------
	�ߒl�F�{�X�X���C���̔z��
======================================== */
CSlime_BossBase* CSlimeManager::GetBossSlimePtr(int num)
{
	return m_pBoss[num];
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
	�^�C�}�[�Z�b�g�֐�
	----------------------------------------
	���e�F�^�C�}�[�̃|�C���^���Z�b�g����
	----------------------------------------
	����1�F�^�C�}�[�̃|�C���^
	----------------------------------------
	�ߒl�F����
======================================== */
void CSlimeManager::SetTimer(CTimer * pTimer)
{
	m_pTimer = pTimer;
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
	����1�F�X�R�A�|�C���^
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CSlimeManager::SetScoreOHMng(CScoreOHManager* pScoreMng)
{
	m_pScoreOHMng = pScoreMng;
}

/* ========================================
	�񕜃A�C�e���Z�b�g�֐�
	----------------------------------------
	���e�F�񕜃A�C�e���̃}�l�[�W���[�̃|�C���^���Z�b�g
	----------------------------------------
	����1�F�񕜃A�C�e���}�l�[�W���[�̃|�C���^
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CSlimeManager::SetHealMng(CHealItemManager * pHealItemMng)
{
	m_pHealItemMng = pHealItemMng;
}
