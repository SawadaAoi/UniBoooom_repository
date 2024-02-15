/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�{�X�X���C��1.cpp
	------------------------------------
	Slime_Boss_1.cpp
	------------------------------------
	�쐬��	�鑺����

	�ύX����
	�E2023/11/17 �N���X�쐬 Suzumura
	�E2023/11/23 �ˌ������̒ǉ� Suzumura
	�E2023/11/28 �e�̑傫����ݒ肷��ϐ��ǉ� nieda
	�E2023/12/07 �Q�[���p�����[�^����ꕔ�萔�ړ� takagi
	�E2023/02/02 �A�j���[�V�����̒ǉ� yamashita

========================================== */

// =============== �C���N���[�h ===================
#include "Slime_Boss_1.h"
#include "GameParameter.h"		//�萔��`�p�w�b�_�[
#include "Sprite.h"


// =============== �萔��` =======================
#if MODE_GAME_PARAMETER
#else
const float LEVEL_BOSS_1_SCALE = 6.0f;						// �{�X�P�̑傫��
const float LEVEL_BOSS_1_SPEED = ENEMY_MOVE_SPEED * 1.5f;	// �{�X�P�̃X�s�[�h
const int BOSS_1_MAX_HP = 100;								// �{�X�P�̍ő�HP

const float ASSAULT_DISTANCE = 0.2f;						// �ˌ���������
const int ASSAULT_COOL_TIME = 10 * 60;						// �ˌ��N���[�^�C��
const int ASSAULT_CHARGE_TIME = 2 * 60;						// �ˌ��`���[�W����
const int ASSAULT_TIME = 1.0f * 60;							// �ˌ�������
const float ASSAULT_SPEED = LEVEL_BOSS_1_SPEED * 15.0f;		// �ˌ����̃X�s�[�h
const int	BOSS_1_ATTACK = 2;	// �U����
#endif
const float BOSS_1_SHADOW_SCALE = 12.0f;		// �{�X�P�̉e�̑傫��

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�R���X�g���N�^
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
CSlime_Boss_1::CSlime_Boss_1()
	:m_nFrame(0)
	,m_assaultDistancePlayer(0.0f)
	,m_assaultMovePos{0.0f,0.0f,0.0f}
{
	m_Transform.fScale = { LEVEL_BOSS_1_SCALE,LEVEL_BOSS_1_SCALE ,LEVEL_BOSS_1_SCALE };
	m_Sphere.fRadius *= LEVEL_BOSS_1_SCALE;
	m_eSlimeSize = E_SLIME_LEVEL::LEVEL_BOSS;
	SetNormalSpeed();
	SetMaxHp();
	m_nHp = m_nMaxHp;
	m_nAttack = BOSS_1_ATTACK;
	m_pShadow->SetScale(BOSS_1_SHADOW_SCALE);
}

/* ========================================
	�R���X�g���N�^�֐�(���W�w��)
	-------------------------------------
	���e�F�R���X�g���N�^
	-------------------------------------
	����1�F����������W
	����2�F���_�V�F�[�_
	����3�F�������郂�f��
	-------------------------------------
	�ߒl�F����
=========================================== */
CSlime_Boss_1::CSlime_Boss_1(TPos3d<float> pos, AnimeModel* pModel)
	: CSlime_Boss_1()
{
	m_Transform.fPos = pos;			// �������W���w��
	m_pModel = pModel;
	m_eCurAnime = ROCK_SLIME_MOVE;		// �A�j���[�V�������ړ��ɃZ�b�g
	m_pModel->Play(m_eCurAnime,true);	// �A�j���[�V�������X�^�[�g

	m_pShadow->SetPos(m_Transform.fPos);	// �e�̍��W���Z�b�g

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
CSlime_Boss_1::~CSlime_Boss_1()
{
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
void CSlime_Boss_1::Update(tagTransform3d playerTransform)
{
	m_fAnimeTime += ADD_ANIME * 1.4f;

	m_PlayerTran = playerTransform;
	
	if (!m_bHitMove)	//�G���ʏ�̈ړ���Ԃ̎�
	{
		NormalMove();	// �ʏ�s������
	}
	else
	{
		// �`���[�W���ɂԂ���΂��ꂽ��N�[���^�C���������Z�b�g
		if (m_nMoveState == CHARGE)
		{
			HitMove();		// �G�̐�����шړ�
			ResetAssault();	// �ˌ����Z�b�g

			if (m_eCurAnime != ROCK_SLIME_HIT)
			{
				m_eCurAnime = ROCK_SLIME_HIT;	// �A�j���[�V�������ړ��ɕύX
				m_fAnimeTime = 0.0f;			// �A�j���[�V�����^�C���̃��Z�b�g
			}
		}

		// �ˌ���Ԃ�"�������"���l�����Ȃ�
		if (m_nMoveState == ASSAULT)
		{
			m_bHitMove = false;
		}
		else
		{
			HitMove(); //�G�̐�����шړ�

			if (m_eCurAnime != ROCK_SLIME_HIT)
			{
				m_eCurAnime = ROCK_SLIME_HIT;	// �A�j���[�V�������ړ��ɕύX
				m_fAnimeTime = 0.0f;			// �A�j���[�V�����^�C���̃��Z�b�g
			}
		}
	}

	// -- ���W�X�V
	m_Transform.fPos.x += m_move.x;
	m_Transform.fPos.z += m_move.z;

	m_pShadow->SetPos(m_Transform.fPos);

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
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSlime_Boss_1::Draw()
{
	// DrawFlg��true�Ȃ�`�揈�����s��
	if (m_bDrawFlg == false) return;

	//�s���Ԃ��擾���ăZ�b�g
	DirectX::XMFLOAT4X4 worldMat;
	DirectX::XMStoreFloat4x4(&worldMat, XMMatrixTranspose(
		DirectX::XMMatrixScaling(m_Transform.fScale.x, m_Transform.fScale.y, m_Transform.fScale.z) *
		DirectX::XMMatrixRotationY(m_Transform.fRadian.y) *
		DirectX::XMMatrixTranslation(m_Transform.fPos.x, m_Transform.fPos.y, m_Transform.fPos.z)));

	DirectX::XMFLOAT4X4 mat[3] = {
	worldMat,
	m_pCamera->GetViewMatrix(),
	m_pCamera->GetProjectionMatrix()
	};

	//-- ���f���\��
	if (m_pModel) {

		ShaderList::SetWVP(mat);

		// �����̂����ʂ̃��f���ň����Ă��邽�ߕ`��̃^�C�~���O�Ń��[�V�����̎�ނƎ��Ԃ��Z�b�g����
		m_pModel->Play(m_eCurAnime, true);
		m_pModel->SetAnimationTime(m_eCurAnime, m_fAnimeTime);	// �A�j���[�V�����^�C�����Z�b�g
		// �A�j���[�V�����^�C�����Z�b�g���Ă��瓮�����Ȃ��Ɣ��f����Ȃ����ߏ��������i�߂�
		m_pModel->Step(0.000001f);

		// �����_�[�^�[�Q�b�g�A�[�x�o�b�t�@�̐ݒ�
		RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
		DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
		SetRenderTargets(1, &pRTV, pDSV);		//DSV��null����2D�\���ɂȂ�

		//-- ���f���\��(�A�j���[�V�����Ή�ver)
		if (m_pModel) {
			//�A�j���[�V�����Ή������v���C���[�̕`��
			m_pModel->Draw(nullptr, [this](int index)
			{
				const AnimeModel::Mesh* pMesh = m_pModel->GetMesh(index);
				const AnimeModel::Material* pMaterial = m_pModel->GetMaterial(pMesh->materialID);
				ShaderList::SetMaterial(*pMaterial);

				DirectX::XMFLOAT4X4 bones[200];
				for (int i = 0; i < pMesh->bones.size() && i < 200; ++i)
				{
					// ���̌v�Z�̓Q�[������[�u�X�L�����b�V���̎d�g�݁v���Q�l�ɂȂ�
					DirectX::XMStoreFloat4x4(&bones[i], DirectX::XMMatrixTranspose(
						pMesh->bones[i].invOffset *
						m_pModel->GetBone(pMesh->bones[i].index)
					));
				}
				ShaderList::SetBones(bones);
			});
			//m_pModel->DrawBone();
		}
	}

	//-- �e�̕`��
	m_pShadow->Draw(m_pCamera);

	//HP�\��
	RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
	DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
	SetRenderTargets(1, &pRTV, nullptr);		//DSV��null����2D�\���ɂȂ�

	mat[1] = m_pCamera->GetViewMatrix();
	mat[2] = m_pCamera->GetProjectionMatrix();
	DirectX::XMFLOAT4X4 inv;//�t�s��̊i�[��
	inv = m_pCamera->GetViewMatrix();

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
	float width = (HPWidth / 2)*(m_nMaxHp - m_nHp);


	world = matInv * DirectX::XMMatrixTranslation(m_Transform.fPos.x - width, m_Transform.fPos.y + SLIME_HP_HEIGHT, m_Transform.fPos.z);
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));
	Sprite::SetSize(DirectX::XMFLOAT2(HPWidth * m_nHp, BOSS_HP_SIZEY));

	Sprite::SetUVPos(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));

	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetTexture(m_pBossHpTexture);
	Sprite::Draw();


}

/* ========================================
	�ʏ�s���֐�(�{�X)
	----------------------------------------
	���e�F�v���C���[��ǐՂ���ړ����s��(�{�X)
	----------------------------------------
	����1�F�v���C���[���W(TPos3d)
	----------------------------------------
	�ߒl�F����
======================================== */
void CSlime_Boss_1::NormalMove()
{
	TPos3d<float> movePos;
	TPos3d<float> playerPos = m_PlayerTran.fPos;

	// �t���[�����Z
	m_nFrame++;

	// ��Ԃɂ���ē��������
	switch (m_nMoveState)
	{
	//--�m�[�}�����
	case NORMAL:
		// �ϐ��錾
		float distancePlayer;
		DirectX::XMFLOAT3 directionVector;
		DirectX::XMVECTOR direction;

		// �A�j���[�V�������ړ��Ɉڍs
		if (m_eCurAnime != ROCK_SLIME_MOVE)
		{
			m_eCurAnime = ROCK_SLIME_MOVE;	// �A�j���[�V�������U���ɕύX
			m_fAnimeTime = 0.0f;				// �A�j���[�V�����^�C���̃��Z�b�g
		}


		// �G����G�l�~�[�̋����A�p�x���v�Z
		distancePlayer = m_Transform.fPos.Distance(playerPos);

		movePos = playerPos - m_Transform.fPos;	// �v���C���[�ւ̃x�N�g�����v�Z
		if (distancePlayer != 0)	//0���Z���
		{
			m_move.x = movePos.x / distancePlayer * m_fSpeed;
			m_move.z = movePos.z / distancePlayer * m_fSpeed;
		}
		// �G����v���C���[�ւ̃x�N�g��
		directionVector.x = m_Transform.fPos.x - playerPos.x;
		directionVector.y = m_Transform.fPos.y - playerPos.y;
		directionVector.z = m_Transform.fPos.z - playerPos.z;

		// �x�N�g���𐳋K�����ĕ����x�N�g���𓾂�
		direction = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&directionVector));
		// �����x�N�g�������]�s����v�Z
		m_Transform.fRadian.y = atan2(directionVector.x, directionVector.z);

		// �N�[���^�C�����I����ĂȂ��Ȃ�NORMAL�̂܂�
		if (m_nFrame <= ASSAULT_COOL_TIME)	break;

		// �v���C���[�Ƌ��������ȓ���������
		if (distancePlayer > ASSAULT_DISTANCE)
		{
			m_nMoveState = CHARGE;	// "�`���[�W"��ԂɑJ��
			m_nFrame = 0;		// �t���[�����Z�b�g

			// �A�j���[�V��������]�Ɉڍs
			if (m_eCurAnime != ROCK_SLIME_ROLLING)
			{
				m_eCurAnime = ROCK_SLIME_ROLLING;	// �A�j���[�V�������U���ɕύX
				m_fAnimeTime = 0.0f;				// �A�j���[�V�����^�C���̃��Z�b�g
			}
		}
		break;
		
		//-- �`���[�W���
	case CHARGE:
		Charge(playerPos, movePos);	// �`���[�W�Ăяo��
		break;

		//-- �ˌ����
	case ASSAULT:
		Assault();		// �ˌ��Ăяo��

		break;

	}
}

/* ========================================
	�`���[�W���s���֐�
	-------------------------------------
	���e�F�{�X���ˌ��̂��߂̃`���[�W���s������
	-------------------------------------
	����1�F�v���C���[���W(TPos3d)
	����2�F�v���C���[�̈ړ���(TPos3d)
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSlime_Boss_1::Charge(TPos3d<float> playerPos, TPos3d<float> movePos)
{
	// �ϐ��錾
	float distancePlayer;
	DirectX::XMFLOAT3 directionVector;
	DirectX::XMVECTOR direction;

	// �G����G�l�~�[�̋����A�p�x���v�Z
	distancePlayer = m_Transform.fPos.Distance(playerPos);
	movePos = playerPos - m_Transform.fPos;	// �v���C���[�ւ̃x�N�g�����v�Z

	if (distancePlayer != 0)	//0���Z���
	{
		// �`���[�W���͑��x�O
		m_fSpeed = 0;	
		m_move.x = movePos.x / distancePlayer * m_fSpeed;
		m_move.z = movePos.z / distancePlayer * m_fSpeed;
	}

	// �G����v���C���[�ւ̃x�N�g��
	directionVector.x = m_Transform.fPos.x - playerPos.x;
	directionVector.y = m_Transform.fPos.y - playerPos.y;
	directionVector.z = m_Transform.fPos.z - playerPos.z;

	// �x�N�g���𐳋K�����ĕ����x�N�g���𓾂�
	direction = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&directionVector));
	// �����x�N�g�������]�s����v�Z
	m_Transform.fRadian.y = atan2(directionVector.x, directionVector.z);

	// �`���[�W�^�C�����I�������"�ˌ�"
	if (m_nFrame >= ASSAULT_CHARGE_TIME)
	{
		m_assaultDistancePlayer = distancePlayer;	// ����̋�����ۑ�
		m_assaultMovePos = movePos;					// �ړ��ʂ�ۑ�
		m_nMoveState = ASSAULT;						// "�ˌ�"��Ԃ�
		m_nFrame = 0;								// �t���[�����Z�b�g
	}
}

/* ========================================
	�{�X��"�ˌ�"���s���֐�
	-------------------------------------
	���e�F�{�X���ˌ��U�����s������
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSlime_Boss_1::Assault()
{
	if (m_assaultDistancePlayer != 0)	//0���Z���
	{
		m_fSpeed = ASSAULT_SPEED;	// �ˌ����̃X�s�[�h�ɕύX
		m_move.x = m_assaultMovePos.x / m_assaultDistancePlayer * m_fSpeed;
		m_move.z = m_assaultMovePos.z / m_assaultDistancePlayer * m_fSpeed;
	}

	// �ˌ����Ԃ��I��
	if (m_nFrame >= ASSAULT_TIME)
	{
		ResetAssault();	// �ˌ����Z�b�g

		if (m_eCurAnime != ROCK_SLIME_MOVE)
		{
			m_pModel->SetAnimationTime(ROCK_SLIME_ROLLING, 0.0f);	//�A�j���[�V���������Z�b�g����
			m_pModel->Step(0.0f);	// �Z�b�g�����A�j���[�V�����^�C���𔽉f������

			m_eCurAnime = ROCK_SLIME_MOVE;	// �A�j���[�V�������ړ��ɕύX
			m_fAnimeTime = 0.0f;			// �A�j���[�V�����^�C���̃��Z�b�g
		}
	}
}

/* ========================================
	"�ˌ�"�̃��Z�b�g���s���֐�
	-------------------------------------
	���e�F�ˌ������Z�b�g�������Ƃ��Ɉꊇ�ŌĂ�
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSlime_Boss_1::ResetAssault()
{
	m_nMoveState = NORMAL;	// "�m�[�}��"��Ԃ�
	SetNormalSpeed();		// �X�s�[�h��ʏ��Ԃɖ߂�
	m_nFrame = 0;			//�t���[�����Z�b�g
}

/* ========================================
	�X�s�[�h����֐�
	-------------------------------------
	���e�F�X���C���̈ړ����x��ݒ�
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSlime_Boss_1::SetNormalSpeed()
{
	m_fSpeed = LEVEL_BOSS_1_SPEED;	//�ړ����x�ɒ萔���Z�b�g
}

/* ========================================
	�}�b�N�XHP����֐�
	-------------------------------------
	���e�F�X���C����MAXHP��ݒ�
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSlime_Boss_1::SetMaxHp()
{
	m_nMaxHp = BOSS_1_MAX_HP;
}