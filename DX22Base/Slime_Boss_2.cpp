/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�{�X�X���C��2.cpp
	------------------------------------
	Slime_Boss_2.cpp
	------------------------------------
	�쐬��	�V�c����

	�ύX����
	�E2023/12/12 �N���X�쐬 Sawada
	�E2023/12/14 �U�������ǉ� Sawada
	�E2024/01/23 ���n���̍����ړ��o�O���C�� Sawada
	�E2023/02/02 �A�j���[�V�����̒ǉ� yamashita
	�E2024/02/09 UsingCamera�g�p takagi
	�E2024/02/13 �J�����폜 takagi

========================================== */


// =============== �C���N���[�h ===================
#include "Slime_Boss_2.h"
#include "Sprite.h"
#include "UsingCamera.h"	//�J�����g�p

// =============== �萔��` =======================
const float BOSS_2_SCALE = 6.0f;					// �{�X2�̑傫��
const float BOSS_2_SPEED = ENEMY_MOVE_SPEED * 1.5f;	// �{�X2�̃X�s�[�h
const int	BOSS_2_MAX_HP = 10;						// �{�X2�̍ő�HP
const float BOSS_2_SHADOW_SCALE = 12.0f;			// �{�X2�̉e�̑傫��

const float STATE_CHANGE_ATTACK_INTERVAL	= 10.0f;	// �ʏ큨�U���̐؂�ւ��Ԋu
const float JUMP_CHAEGE_TIME				= 1.0f;		// �W�����v�O���߂̎���
const float JUMP_CHAEGE_SCALE_TIME			= 0.2f;		// �W�����v�O���߂̑傫���ύX����
const float JUMP_CHAEGE_SCALE_ADJUST		= 0.02f;	// �W�����v�O���߂̑傫���ύX�l
const float JUMP_TIME						= 1.5f;		// �W�����v��������
const float JUMP_SPEED						= 1.0f;		// �W�����v�X�s�[�h
const float JUMP_SHADOW_SIZE_MUL			= 0.9f;		// �W�����v���̉e�̕ύX��
const float TARGET_SHADOW_TIME				= 2.5f;		// �e���Ƃ����̎���
const float TARGET_SHADOW_PLYR_MOVE_TIME	= 3.0f;		// �e���Ƃ����̃v���C���[�Ǐ]����
const float DROP_SPEED						= 5.0f;		// ���������X�s�[�h
const float DROP_RIGID_TIME					= 3.0f;		// ������d������
const float DROP_RIGID_SCALE_TIME			= 0.2f;		// ������d���̑傫���ύX����
const float DROP_RIGID_SCALE_ADJUST			= 0.01f;	// ������d���̑傫���ύX�l




/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�R���X�g���N�^
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
CSlime_Boss_2::CSlime_Boss_2()
{
	m_nMoveState = MOVE_STATE::NORMAL;
	m_Transform.fScale = { BOSS_2_SCALE,BOSS_2_SCALE ,BOSS_2_SCALE };
	m_Sphere.fRadius *= BOSS_2_SCALE;
	m_eSlimeSize = E_SLIME_LEVEL::LEVEL_BOSS;
	SetNormalSpeed();
	SetMaxHp();
	m_nHp = m_nMaxHp;
	m_nAttack = BOSS_1_ATTACK;
	m_pShadow->SetScale(BOSS_2_SHADOW_SCALE);	// �e�̑傫����ݒ�

	for (int i = 0; i < MOVE_STATE::MOVE_MAX; i++)m_nMoveCnt[i] = 0;
}

/* ========================================
	�R���X�g���N�^�֐�(���W�w��)
	-------------------------------------
	���e�F�R���X�g���N�^
	-------------------------------------
	����1�F����������W
	����2�F���_�V�F�[�_
	����3�F�������郂�f��
	����4�F�������郂�f��
	-------------------------------------
	�ߒl�F����
=========================================== */
CSlime_Boss_2::CSlime_Boss_2(TPos3d<float> pos, AnimeModel * pModel)
	: CSlime_Boss_2()
{
	m_Transform.fPos = pos;			// �������W���w��

	m_pModel = pModel;
	m_pShadow->SetPos(TPos3d<float>(m_Transform.fPos.x, 0.0f, m_Transform.fPos.z));	// �e�̍��W���ړ�

	m_eCurAnime = DEVIL_SLIME_MOVE;
	m_pModel->Play(m_eCurAnime,true);
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
CSlime_Boss_2::~CSlime_Boss_2()
{
}


/* ========================================
	�X�V�֐�
	-------------------------------------
	���e�F���t���[���Ă΂��X�V
	-------------------------------------
	����1�F�v���C���[��transform(���W�A�傫���A�p�x)
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSlime_Boss_2::Update(tagTransform3d playerTransform)
{
	m_PlayerParam = playerTransform;	// �v���C���[�̍ŐVtransform�������o�ϐ��ɃZ�b�g
	// �ʏ�s���̎��̂݃A�j���[�V������i�s
	if (m_nMoveState == NORMAL)
	{
		m_fAnimeTime += ADD_ANIME;
	}

	// �ʏ�̈ړ���Ԃ̎�
	if (!m_bHitMove)	
	{
		MoveSwitch();	// �ʏ�ړ��؂�ւ�
	}
	// �n���}�[�ŉ���ꂽ��
	else
	{
		// �ˌ���Ԃ�"�������"���l�����Ȃ�
		if (m_nMoveState != MOVE_STATE::NORMAL)
		{
			m_bHitMove = false;
		}
		else
		{
			HitMove();							// �G�̐�����шړ�
			m_pShadow->SetPos(TPos3d<float>(m_Transform.fPos.x, 1.0f, m_Transform.fPos.z));	// �e�̍��W���ړ�	

			// �A�j���[�V�������_���ɕύX
			if (m_eCurAnime != DEVIL_SLIME_HIT)
			{	
				// �A�j���[�V������ύX����O�Ɍ��݂̃A�j����������
				m_pModel->SetAnimationTime(m_eCurAnime, 0.0f);
				m_pModel->Step(0.0f);

				m_eCurAnime = DEVIL_SLIME_HIT;	// �A�j���[�V�������_���ɕύX
				m_fAnimeTime = 0.0f;			// �A�j���[�V�����^�C�������Z�b�g
			}
		}
	}

	// -- ���W�X�V
	m_Transform.fPos.x += m_move.x;
	m_Transform.fPos.y += m_move.y;
	m_Transform.fPos.z += m_move.z;

// �_���[�W����------------

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
void CSlime_Boss_2::Draw()
{
	// DrawFlg��true�Ȃ�`�揈�����s��
	if (m_bDrawFlg == false) return;

	//-- �e�̕`��
	//m_pShadow->Draw();

	//�s���Ԃ��擾���ăZ�b�g
	DirectX::XMFLOAT4X4 worldMat;
	DirectX::XMStoreFloat4x4(&worldMat, XMMatrixTranspose(
		DirectX::XMMatrixScaling(m_Transform.fScale.x, m_Transform.fScale.y, m_Transform.fScale.z) *
		DirectX::XMMatrixRotationY(m_Transform.fRadian.y) *
		DirectX::XMMatrixTranslation(m_Transform.fPos.x, m_Transform.fPos.y, m_Transform.fPos.z)));

	DirectX::XMFLOAT4X4 mat[3] = {
	worldMat,
	CUsingCamera::GetThis().GetCamera()->GetViewMatrix(),
	CUsingCamera::GetThis().GetCamera()->GetProjectionMatrix()
	};

	//-- ���f���\��
	if (m_pModel) {

		ShaderList::SetWVP(mat);

		// �����̂����ʂ̃��f���ň����Ă��邽�ߕ`��̃^�C�~���O�Ń��[�V�����̎�ނƎ��Ԃ��Z�b�g����
		m_pModel->Play(m_eCurAnime, true);
		m_pModel->SetAnimationTime(m_eCurAnime, m_fAnimeTime);	// �A�j���[�V�����^�C�����Z�b�g
		// �A�j���[�V�����^�C�����Z�b�g���Ă��瓮�����Ȃ��Ɣ��f����Ȃ����ߏ��������i�߂�
		m_pModel->Step(0.0f);

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



	//HP�\��
	RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
	DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
	SetRenderTargets(1, &pRTV, nullptr);		//DSV��null����2D�\���ɂȂ�

	mat[1] = CUsingCamera::GetThis().GetCamera()->GetViewMatrix();
	mat[2] = CUsingCamera::GetThis().GetCamera()->GetProjectionMatrix();
	DirectX::XMFLOAT4X4 inv;//�t�s��̊i�[��
	inv = CUsingCamera::GetThis().GetCamera()->GetViewMatrix();

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
	�ʏ�ړ��؂�ւ��֐�
	-------------------------------------
	���e�F�ړ���؂�ւ���
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSlime_Boss_2::MoveSwitch()
{
	switch (m_nMoveState)
	{
	// �ړ�����
	case MOVE_STATE::NORMAL:
		SetNormalSpeed();	// �ړ��X�s�[�h�����Z�b�g(���O�̐�����ё��x�𖳂�����)
		MoveNormal();

		// �A�j���[�V�������ړ��ɕύX
		if (m_eCurAnime != DEVIL_SLIME_MOVE)
		{
			m_eCurAnime = DEVIL_SLIME_MOVE;	// �A�j���[�V�������_���ɕύX
			m_fAnimeTime = 0.0f;			// �A�j���[�V�����^�C�������Z�b�g
		}

		break;
	// �W�����v�\�����쏈��
	case MOVE_STATE::JUMP_CHARGE:
		MoveJumpCharge();

		break;

	// �W�����v����
	case MOVE_STATE::JUMP:
		MoveJump();

		break;

	// �����ʒu���菈��
	case MOVE_STATE::TARGET_SHADOW:
		MoveTargetShadow();

		break;

	// ��������
	case MOVE_STATE::DROP:
		MoveDrop();

		break;
	
	// �����d������
	case MOVE_STATE::DROP_RIGID:
		MoveDropRigid();

		break;
	}

}


/* ========================================
	�ʏ�ړ��֐�
	-------------------------------------
	���e�F�����_���ړ��ƃv���C���[�ǐՈړ����s��
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSlime_Boss_2::MoveNormal()
{
	TPos3d<float> playerPos = m_PlayerParam.fPos;					// �v���C���[�̍��W���擾
	float distancePlayer	= m_Transform.fPos.Distance(playerPos);	// �G����G�l�~�[�̋����A�p�x���v�Z

	// �v���C���[�Ƌ��������ȓ���������
	if (distancePlayer < MOVE_DISTANCE_PLAYER + 50.0f)	//�{�X�͏�Ƀv���C���[��ǂ������ė~����
	{
		TPos3d<float> movePos;
		movePos = playerPos - m_Transform.fPos;	// �v���C���[�ւ̃x�N�g�����v�Z
		if (distancePlayer != 0)	//0���Z���
		{
			m_move.x = movePos.x / distancePlayer * m_fSpeed;
			m_move.z = movePos.z / distancePlayer * m_fSpeed;
		}
		// �G����v���C���[�ւ̃x�N�g��
		DirectX::XMFLOAT3 directionVector;
		directionVector.x = m_Transform.fPos.x - playerPos.x;
		directionVector.y = m_Transform.fPos.y - playerPos.y;
		directionVector.z = m_Transform.fPos.z - playerPos.z;

		// �x�N�g���𐳋K�����ĕ����x�N�g���𓾂�
		DirectX::XMVECTOR direction = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&directionVector));
		// �����x�N�g�������]�s����v�Z
		m_Transform.fRadian.y = atan2(directionVector.x, directionVector.z);

		// �U�������ɐ؂�ւ�
		m_nMoveCnt[MOVE_STATE::NORMAL]++;
		// �U���������W�����v�@�؂�ւ�����
		if ((STATE_CHANGE_ATTACK_INTERVAL * 60) <= m_nMoveCnt[MOVE_STATE::NORMAL])
		{
			m_nMoveState = MOVE_STATE::JUMP_CHARGE;	// ��Ԃ�؂�ւ�
			m_nMoveCnt[MOVE_STATE::NORMAL] = 0;		// ���Z�����Z�b�g
		}

	}
	else
	{
		RandomMove();	// �����_���ړ�
		m_nMoveCnt[MOVE_STATE::NORMAL] = 0;	
	}

	m_pShadow->SetPos(TPos3d<float>(m_Transform.fPos.x,0.0f, m_Transform.fPos.z));	// �e�̍��W���ړ�	

}


/* ========================================
	�W�����v�\������֐�
	-------------------------------------
	���e�F�W�����v�O�̗��ߓ��쏈��
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSlime_Boss_2::MoveJumpCharge()
{
	m_nMoveCnt[MOVE_STATE::JUMP_CHARGE]++;

	// �W�����v�O�Ƀ{�X�̌����ڂ������ׂ��
	if (m_nMoveCnt[MOVE_STATE::JUMP_CHARGE] <= (JUMP_CHAEGE_SCALE_TIME * 60))
	{
		m_Transform.fScale.x *= 1.0f + JUMP_CHAEGE_SCALE_ADJUST;
		m_Transform.fScale.z *= 1.0f + JUMP_CHAEGE_SCALE_ADJUST;
		m_Transform.fScale.y *= 1.0f - JUMP_CHAEGE_SCALE_ADJUST;
	}

	// �W�����v�������ʒu�^�[�Q�b�g�@�؂�ւ�����
	if ((JUMP_CHAEGE_TIME * 60) <= m_nMoveCnt[MOVE_STATE::JUMP_CHARGE])
	{
		m_nMoveState = MOVE_STATE::JUMP;			// ��Ԃ�؂�ւ�
		m_nMoveCnt[MOVE_STATE::JUMP_CHARGE] = 0;	// ���Z�����Z�b�g

		this->SetScale({ BOSS_2_SCALE, BOSS_2_SCALE, BOSS_2_SCALE });	// �傫����߂��Ă���
	}

	m_pShadow->SetPos(TPos3d<float>(m_Transform.fPos.x, 0.0f, m_Transform.fPos.z));	// �e�̍��W���ړ�	

}

/* ========================================
	�W�����v�֐�
	-------------------------------------
	���e�F�����ɃW�����v���s��
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSlime_Boss_2::MoveJump()
{
	// �ړ��ʂ��Z�b�g����
	m_move.x = 0.0f;
	m_move.y = JUMP_SPEED;		// �^��Ɉړ�
	m_move.z = 0.0f;

	// �㏸�ɍ��킹�ĉe������������
	m_fScaleShadow *= JUMP_SHADOW_SIZE_MUL;
	m_pShadow->SetScale({ m_fScaleShadow ,m_fScaleShadow ,m_fScaleShadow });
	m_pShadow->SetPos({ m_Transform.fPos.x,	m_pShadow->GetPos().y,m_Transform.fPos.z });	// �{�X�ɍ��킹�ď�ɍs���Ȃ��l��Y���W�̈ʒu�͂��̂܂�

	m_nMoveCnt[MOVE_STATE::JUMP]++;
	// �W�����v�������ʒu�^�[�Q�b�g�@�؂�ւ�����
	if ((JUMP_TIME * 60) <= m_nMoveCnt[MOVE_STATE::JUMP])
	{
		m_nMoveState = MOVE_STATE::TARGET_SHADOW;	// ��Ԃ�؂�ւ�
		m_nMoveCnt[MOVE_STATE::JUMP] = 0;		 	// ���Z�����Z�b�g
		m_pShadow->SetScale(BOSS_2_SHADOW_SCALE);	// �e�̑傫���͖߂��Ă���
	}

}

/* ========================================
	�����ʒu�^�[�Q�b�g�����֐�
	-------------------------------------
	���e�F���b�ԃv���C���[�ʒu�ɗ����ʒu��_����߂�
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSlime_Boss_2::MoveTargetShadow()
{
	m_nMoveCnt[MOVE_STATE::TARGET_SHADOW]++;

	// ���b�Ԃ̊Ԃ����v���C���[�̍��W��Ǐ]���đ_�����߂�
	if (m_nMoveCnt[MOVE_STATE::TARGET_SHADOW] <= (TARGET_SHADOW_PLYR_MOVE_TIME * 60))
	{
		this->SetPos({ m_PlayerParam.fPos.x, this->GetPos().y, m_PlayerParam.fPos.z });			// �{�X�ړ�
		m_pShadow->SetPos({ m_Transform.fPos.x,	m_pShadow->GetPos().y,m_Transform.fPos.z });	// �e�ړ�
	}
	// �����ʒu�^�[�Q�b�g �� ���� �؂�ւ�
	else if ((TARGET_SHADOW_TIME * 60) <= m_nMoveCnt[MOVE_STATE::TARGET_SHADOW])
	{
		m_nMoveState = MOVE_STATE::DROP;				// ��Ԃ�؂�ւ�
		m_nMoveCnt[MOVE_STATE::TARGET_SHADOW] = 0;		// ���Z�����Z�b�g
	}
}

/* ========================================
	���������֐�
	-------------------------------------
	���e�F�e�̈ʒu�ɂ߂����ė�������
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSlime_Boss_2::MoveDrop()
{
	m_move.x = 0.0f;
	m_move.y = -DROP_SPEED;
	m_move.z = 0.0f;

	// �n�ʂɒ��n�����ꍇ
	if ( m_Transform.fPos.y < 0.0f)
	{
		// �ړ��ʂ�0�ɂ���
		m_move.x = 0.0f;
		m_move.y = 0.0f;
		m_move.z = 0.0f;

		// y���W��n�ʂɐݒu������ԂŌŒ�
		this->SetPos({ m_Transform.fPos.x,	0.0f, m_Transform.fPos.z });

		m_nMoveState = MOVE_STATE::DROP_RIGID;	// ��Ԃ�؂�ւ�
		m_nMoveCnt[MOVE_STATE::DROP] = 0; 	// ���Z�����Z�b�g

	}
}

/* ========================================
	�����d�������֐�
	-------------------------------------
	���e�F������Ɏb���d������
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSlime_Boss_2::MoveDropRigid()
{
	m_nMoveCnt[MOVE_STATE::DROP_RIGID]++;

	// ���n��Ƀ{�X�̌����ڂ������ׂ��
	if (m_nMoveCnt[MOVE_STATE::DROP_RIGID] <= (DROP_RIGID_SCALE_TIME * 60))
	{
		m_Transform.fScale.x *= 1.0f + DROP_RIGID_SCALE_ADJUST;
		m_Transform.fScale.z *= 1.0f + DROP_RIGID_SCALE_ADJUST;
		m_Transform.fScale.y *= 1.0f - DROP_RIGID_SCALE_ADJUST;
	}
	else
	{
		this->SetScale({ BOSS_2_SCALE, BOSS_2_SCALE, BOSS_2_SCALE });	// �傫����߂��Ă���
	}


	// �����ړ� �� �ʏ�ړ��؂�ւ�
	if ((DROP_RIGID_TIME * 60) <= m_nMoveCnt[MOVE_STATE::DROP_RIGID])
	{
		m_nMoveState = MOVE_STATE::NORMAL;	// ��Ԃ�؂�ւ�
		m_nMoveCnt[MOVE_STATE::DROP_RIGID] = 0; 	// ���Z�����Z�b�g

		// �A�j���[�V�������ړ��ɕύX
		if (m_eCurAnime != DEVIL_SLIME_MOVE)
		{
			m_eCurAnime = DEVIL_SLIME_MOVE;	// �A�j���[�V�������_���ɕύX
			m_fAnimeTime = 0.0f;			// �A�j���[�V�����^�C�������Z�b�g
		}
	}
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
void CSlime_Boss_2::SetNormalSpeed()
{
	m_fSpeed = BOSS_2_SPEED;	//�ړ����x�ɒ萔���Z�b�g
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
void CSlime_Boss_2::SetMaxHp()
{
	m_nMaxHp = BOSS_2_MAX_HP;
}


