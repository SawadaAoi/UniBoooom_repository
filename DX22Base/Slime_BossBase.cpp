/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�{�X�X���C��.cpp
	------------------------------------
	Slime_Boss.cpp
	------------------------------------
	�쐬��	�鑺����

	�ύX����
	�E2023/11/17 �N���X�쐬 Suzumura
	�E2023/11/23 Damage,IsDead�֐���ǉ� Suzumura
	�E2023/11/27 HP�\���ǉ� yamamoto
	�E2023/11/28 �e�̕`���ǉ� nieda
	�E2023/11/30 ���������[�N���� takagi

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
const float BOSS_HP_POSX = 17.0f;		//�̗̓Q�[�W�i������j�̈ʒu

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
{

	m_pBossHpTexture = new Texture();
	if (FAILED(m_pBossHpTexture->Create("Assets/Texture/Boss_Hp.png")))
	{
		MessageBox(NULL, "HP�Q�[�W�ǂݍ���", "Error", MB_OK);
	}
	m_pHpFrameTexture = new Texture();
	if (FAILED(m_pHpFrameTexture->Create("Assets/Texture/Boss_HpFrame.png")))
	{
		MessageBox(NULL, "HP�t���[���ǂݍ���", "Error", MB_OK);
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
CSlime_BossBase::~CSlime_BossBase()
{
	// =============== �I�� ===================
	delete m_pBossHpTexture;		//���������
	m_pBossHpTexture = nullptr;		//��A�h���X���
	delete m_pHpFrameTexture;		//���������
	m_pHpFrameTexture = nullptr;	//��A�h���X���
}

/* ========================================
	�X�V�����֐�
	-------------------------------------
	���e�F�X�V����
	-------------------------------------
	����1�F�v���C���[���W(TPos3d)
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSlime_BossBase::Update(tagTransform3d playerTransform)
{
	m_PlayerTran = playerTransform;

	if (!m_bHitMove)	//�G���ʏ�̈ړ���Ԃ̎�
	{
		NormalMove();
	}
	else
	{
		//�G�̐�����шړ�
		HitMove();
	}

	// -- ���W�X�V
	m_Transform.fPos.x += m_move.x;
	m_Transform.fPos.z += m_move.z;

	// �_���[�W����������Ȃ��Ȃ�_�ŏ������s��Ȃ�
	if (m_bFlash == false) return;
	// �_�ŏ���
	m_nInvFrame++;						//���t���[���ŃJ�E���g��ǉ�
	if (0 == m_nInvFrame % BOSS_DAMAGE_FLASH_FRAME)
	{
		// �`�悷�邩���Ȃ��؂�ւ�
		if (m_bDrawFlg)
		{
			m_bDrawFlg = false;	// true��false
		}
		else
		{
			m_bDrawFlg = true;	// false��true
		}

	}
	// ���_�Ŏ��Ԃ��߂�����I��
	if (m_nInvFrame >= BOSS_DAMAGE_FLASH_TOTAL_FRAME)
	{
		m_bFlash = false;
		m_nInvFrame = 0;
		m_bDrawFlg = true;
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
void CSlime_BossBase::Draw(const CCamera* pCamera)
{
	// DrawFlg��true�Ȃ�`�揈�����s��
	if (m_bDrawFlg == false) return;

	DirectX::XMFLOAT4X4 mat[3];

	mat[0] = m_Transform.GetWorldMatrixSRT();
	mat[1] = pCamera->GetViewMatrix();
	mat[2] = pCamera->GetProjectionMatrix();

	//-- �s����V�F�[�_�[�֐ݒ�
	m_pVS->WriteBuffer(0, mat);

	//-- ���f���\��
	if (m_pModel) {
		// �����_�[�^�[�Q�b�g�A�[�x�o�b�t�@�̐ݒ�
		RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
		DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
		SetRenderTargets(1, &pRTV, pDSV);		//DSV��null����2D�\���ɂȂ�
		m_pModel->Draw();
	}
	
	//-- �e�̕`��
	m_pShadow->Draw(pCamera);

	//HP�\��
	RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
	DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
	SetRenderTargets(1, &pRTV, nullptr);		//DSV��null����2D�\���ɂȂ�

	mat[1] = pCamera->GetViewMatrix();
	mat[2] = pCamera->GetProjectionMatrix();
	DirectX::XMFLOAT4X4 inv;//�t�s��̊i�[��
	inv = pCamera->GetViewMatrix();

	//�J�����̍s���GPU�ɓn���ۂɓ]�u����Ă��邽�߁A�t�s��̂��߂Ɉ�x���ɖ߂�
	DirectX::XMMATRIX matInv = DirectX::XMLoadFloat4x4(&inv);
	matInv = DirectX::XMMatrixTranspose(matInv);

	//�ړ������͋t�s��őł������K�v�������̂�0��ݒ肵�Ĉړ��𖳎�����
	DirectX::XMStoreFloat4x4(&inv, matInv);
	inv._41 = inv._42 = inv._43 = 0.0f;

	matInv = DirectX::XMLoadFloat4x4(&inv);
	matInv = DirectX::XMMatrixInverse(nullptr, matInv);



	//�t���[��
	DirectX::XMMATRIX world = matInv * DirectX::XMMatrixTranslation(m_Transform.fPos.x, m_Transform.fPos.y + SLIME_HP_HEIGHT, m_Transform.fPos.z);
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));
	Sprite::SetSize(DirectX::XMFLOAT2(3.2f, 0.7f));

	Sprite::SetUVPos(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));


	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetTexture(m_pHpFrameTexture);
	Sprite::Draw();


	HPWidth = 3.0f / m_nMaxHp;	
	float width = (HPWidth /2)*(m_nMaxHp - m_nHp);
	

	 world = matInv * DirectX::XMMatrixTranslation(m_Transform.fPos.x - width, m_Transform.fPos.y+ SLIME_HP_HEIGHT, m_Transform.fPos.z);
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));
	Sprite::SetSize(DirectX::XMFLOAT2(HPWidth*m_nHp, BOSS_HP_SIZEY));
	
	Sprite::SetUVPos(DirectX::XMFLOAT2(1.0f,1.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f,1.0f));

	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetTexture(m_pBossHpTexture);
	Sprite::Draw();

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



