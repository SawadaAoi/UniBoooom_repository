/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�{�X�X���C���\�[�X
	------------------------------------
	Slime_BossBase.cpp
	------------------------------------
	�쐬��	suzumura

	�ύX����
	�E2023/11/17 �N���X�쐬 suzumura
	�E2023/11/23 Damage,IsDead�֐���ǉ� suzumura
	�E2023/11/27 HP�\���ǉ� yamamoto
	�E2023/11/28 �e�̕`���ǉ� nieda
	�E2023/11/30 ���������[�N���� takagi
	�E2024/01/20 ���t�@�N�^�����O takagi
	�E2024/01/21 �R�����g���C�EMessageBox���P takagi

========================================== */

// =============== �C���N���[�h ===================
#include "Slime_BossBase.h"
#include "Sprite.h"
// =============== �萔��` =======================
#if MODE_GAME_PARAMETER
#else
const float SLIME_HP_HEIGHT = 5.0f;		//�{�X�̗͕̑\���ʒu�iY�j
const float BOSS_HP_SIZEX = 0.3f;		//�̗͂P���̑傫���iX�j
const float BOSS_HP_SIZEY = 0.5f;		//�̗͂P���̑傫���iY�j
const float BOSS_HPFRAME_SIZEX = 0.2f;	//�̗̓Q�[�W���ǂꂾ���傫�����iX�j
const float BOSS_HPFRAME_SIZEY = 0.2f;	//�̗̓Q�[�W���ǂꂾ���傫�����iY�j
const float BOSS_HP_POSX = 8.6f;		//�̗̓Q�[�W�i������j�̈ʒu

const int BOSS_DAMAGE_FLASH_FRAME = 0.1 * 60;					// �_���[�W�󂯂��ۂ̓_�Ńt���[��(���G�ł͂Ȃ�)
const int BOSS_DAMAGE_FLASH_TOTAL_FRAME = 0.5 * 60;					// �_���[�W���󂯂��ۂ̓_�ł����t���[���s����


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
CSlime_BossBase::CSlime_BossBase()
	: m_nHp(0)
	, m_nMaxHp(0)
	, m_bDead(false)
	, m_nInvFrame(0)
	, m_bDrawFlg(true)
	, m_bFlash(false)
	, m_pBossHpTexture(nullptr)
	, m_pHpFrameTexture(nullptr)
	, m_nMoveState(0)	// 0��Normal
	, m_pHpFrame(nullptr)
	,m_pBossHp(nullptr)
{

	m_pBossHpTexture = new Texture();
	if (FAILED(m_pBossHpTexture->Create("Assets/Texture/Boss_Hp.png")))
	{
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error�F";	//�G���[�ӏ�
		MessageBox(nullptr, (ErrorSpot + "HP�Q�[�W�ǂݍ��ݎ��s").c_str(), "Error", MB_OK | MB_ICONERROR);									//�G���[�ʒm
#endif
	}
	m_pBossHp = new C2dObject;
	m_pBossHp->SetTexture(m_pBossHpTexture);
	m_pHpFrameTexture = new Texture();
	if (FAILED(m_pHpFrameTexture->Create("Assets/Texture/Boss_HpFrame.png")))
	{
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error�F";	//�G���[�ӏ�
		MessageBox(nullptr, (ErrorSpot + "HP�t���[���ǂݍ��ݎ��s").c_str(), "Error", MB_OK | MB_ICONERROR);									//�G���[�ʒm
#endif
	}
	m_pHpFrame = new C2dObject;
	m_pHpFrame->SetTexture(m_pHpFrameTexture);
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
CSlime_BossBase::~CSlime_BossBase()
{
	// =============== �I�� ===================
	delete m_pBossHpTexture;		//���������
	m_pBossHpTexture = nullptr;		//��A�h���X���
	delete m_pHpFrameTexture;		//���������
	m_pHpFrameTexture = nullptr;	//��A�h���X���
}

void CSlime_BossBase::Update()
{
	if (m_pBossHp)
	{
		m_pBossHp->SetTransform(m_Transform);
		m_pBossHp->Update();
	}
	if (m_pHpFrame)
	{
		m_pHpFrame->SetTransform(m_Transform);
		m_pHpFrame->Update();
	}
}

/* ========================================
	�`�揈���֐�
	-------------------------------------
	���e�F�`�揈��
	-------------------------------------
	����1�F�J����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSlime_BossBase::Draw() const
{
	// DrawFlg��true�Ȃ�`�揈�����s��
	if (m_bDrawFlg == false) return;

	//-- �e�̕`��
	m_pShadow->Draw();
	
	C3dObject::Draw();

	if (m_pBossHp)
	{
		m_pBossHp->Draw();
	}
	if (m_pHpFrame)
	{
		m_pHpFrame->Draw();
	}

}


/* ========================================
	���[�v�֐�
	-------------------------------------
	���e�F�{�X�����ꂷ������߂��Ƀ��[�v
	-------------------------------------
	����1�F�v���C���[���W(TPos3d)
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CSlime_BossBase::Warp(TPos3d<float> playerPos)
{

}

/* ========================================
	�_���[�W�֐�
	-------------------------------------
	���e�F�{�X�Ƀ_���[�W��^����֐�
	-------------------------------------
	����1�F�_���[�W��
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CSlime_BossBase::Damage(int num)
{
	m_nHp -= num;		// HP����
	m_bFlash = true;	// �_��ON

	if (m_nHp <= 0) m_bDead = true;	// HP���O�ȉ��Ȃ玀�S
}

/* ========================================
	�����m�F�֐�
	-------------------------------------
	���e�F�{�X������ł��邩�ǂ�����Ԃ�
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����ł��邩�ǂ���(bool)
=========================================== */
bool CSlime_BossBase::IsDead()
{
	return m_bDead;
}


/* ========================================
	�ړ���ގ擾�֐�
	-------------------------------------
	���e�F�{�X�̌��݂̈ړ��̎�ނ�Ԃ�
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F�ړ����
=========================================== */
int CSlime_BossBase::GetMoveState()
{
	return m_nMoveState;
}



