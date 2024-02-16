/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�X���C���T�C�Y2�pcpp
	------------------------------------
	Slime_2.cpp
	------------------------------------
	�쐬��	�R�����C

	�ύX����
	�E2023/11/08 �쐬 yamashita
	�E2023/11/08 �傫���̒萔���`	yamashita
	�E2023/11/08 �X���C���̈ړ����x��傫�����ƂɕύX����֐����쐬	yamashita
	�E2023/11/08 �X���C���̈ړ����x��傫�����ƂɕύX����֐����쐬	yamashita
	�E2023/11/08 �R���X�g���N�^�Ń��x�����Ƃ̃p�����[�^���Z�b�g	yamashita
	�E2023/11/11 parameter�p�w�b�_�ǉ� suzumura
	�E2023/11/14 Base���烂�f���A�V�F�[�_�̓ǂݍ��݂��ړ� Suzumura
	�E2023/11/14 SphereInfo�̕ύX�ɑΉ� takagi
	�E2023/11/15 �X���C���̃��f���ƒ��_�V�F�[�_�[��manager����󂯎��悤�ɕύX yamashita
	�E2023/11/28 �e�̑傫����ݒ肷��ϐ��ǉ� nieda
	�E2023/12/01 �^�b�N���̋�����ǉ� yamashita
	�E2023/12/07 �Q�[���p�����[�^����ꕔ�萔�ړ� takagi
	�E2024/1/26  �A�j���[�V�����̎��� Yamashita
	�E2024/1/26  �^�b�N�����ɒ@���ƃ^�b�N�����܂��ĊJ�����s����C�� Yamashita
	�E2024/01/29 �A�j���[�V�����̒ǉ� yamashita
	�E2024/02/09 UsingCamera�g�p takagi
	�E2024/02/13 �J�����폜 takagi

========================================== */

// =============== �C���N���[�h ===================
#include "Slime_2.h"
#include "GameParameter.h"	//�萔��`�p�w�b�_�[
#include "UsingCamera.h"	//�J�����g�p

// =============== �萔��` =======================
const int	LEVEL2_ATTACK = 1;						// �U����
#if MODE_GAME_PARAMETER
#else
const float LEVEL2_SCALE = 2.0f;
const float LEVEL2_SPEED = ENEMY_MOVE_SPEED * 0.95;
#endif
const float LEVEL_2_SHADOW_SCALE = 2.5f;	// �X���C���Q���x���Q�̉e�̑傫��

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�R���X�g���N�^
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
CSlime_2::CSlime_2()
	: m_AtcMoveType(ATTACK_NONE)
	, m_nChargeCnt(0)
	, m_nTackleCnt(0)
	, m_nAtkInterval(0)
	, tackleDirection{0.0f,0.0f,0.0f,0.0f}
{
	m_Transform.fScale = { LEVEL2_SCALE,LEVEL2_SCALE ,LEVEL2_SCALE };
	m_Sphere.fRadius *= LEVEL2_SCALE;
	m_eSlimeSize = E_SLIME_LEVEL::LEVEL_2;
	SetNormalSpeed();
	m_nAttack = LEVEL2_ATTACK;
	m_fScaleShadow = LEVEL_2_SHADOW_SCALE;	// �e�̑傫����ݒ�
}

/* ========================================
	�R���X�g���N�^�֐�(���W�w��)
	-------------------------------------
	���e�F�R���X�g���N�^
	-------------------------------------
	����1�F����������W
	����2�F���_�V�F�[�_�[�̃|�C���^
	����3�F���f���̃|�C���^
	-------------------------------------
	�ߒl�F����
=========================================== */
CSlime_2::CSlime_2(TPos3d<float> pos, AnimeModel* pModel)
	: CSlime_2()
{
	m_Transform.fPos = pos;			// �������W���w��
	m_pModel = pModel;
	m_eCurAnime = MOTION_LEVEL2_MOVE;
	m_pModel->Play(m_eCurAnime,true);
}

/* ========================================
	�f�X�g���N�^�֐�
	-------------------------------------
	���e�F�f�X�g���N�^
	-------------------------------------
	����1�F
	-------------------------------------
	�ߒl�F
=========================================== */
CSlime_2::~CSlime_2()
{
}

/* ========================================
	�X�V�����֐�
	-------------------------------------
	���e�F�X�V����
	-------------------------------------
	����1�F�v���C���[��transform
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSlime_2::Update(tagTransform3d playerTransform, float fSlimeMoveSpeed)
{
	m_PlayerTran = playerTransform;
	m_fAnimeTime += ADD_ANIME * 0.6f;		// �A�j���[�V������i�s

	if (!m_bHitMove)	//�G���ʏ�̈ړ���Ԃ̎�
	{
		if (!m_bMvStpFlg  && m_nMvStpCnt == 0)	//������t���O��off�Ȃ�
		{
			NormalMove();	//�ʏ�ړ�
		}
		else
		{
			MoveStop();	//�������瓦����
		}
	}
	else
	{
		// ������уA�j���[�V�����Đ�
		if (m_eCurAnime != (int)MOTION_LEVEL2_HIT)
		{
			m_eCurAnime = (int)MOTION_LEVEL2_HIT;
			m_fAnimeTime = 0.0f;	// �A�j���[�V�����^�C���̃��Z�b�g
		}

		//�G�̐�����шړ�
		HitMove();

		// �^�b�N���𒆎~���ĕϐ���������
		m_AtcMoveType = ATTACK_NONE;
		m_nChargeCnt = 0;
		m_nTackleCnt = 0;
	}

	// -- ���W�X�V
	m_Transform.fPos.x += m_move.x * fSlimeMoveSpeed;
	m_Transform.fPos.z += m_move.z * fSlimeMoveSpeed;
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
void CSlime_2::Draw()
{
	//�s���Ԃ��擾���ăZ�b�g
	DirectX::XMFLOAT4X4 world;
	DirectX::XMStoreFloat4x4(&world, XMMatrixTranspose(
		DirectX::XMMatrixScaling(m_Transform.fScale.x, m_Transform.fScale.y, m_Transform.fScale.z) *
		DirectX::XMMatrixRotationY(m_Transform.fRadian.y + DirectX::g_XMPi[0]) *
		//DirectX::XMMatrixRotationY(m_Transform.fRadian.x + DirectX::XMConvertToRadians(20.0f)) *
		DirectX::XMMatrixTranslation(m_Transform.fPos.x, m_Transform.fPos.y, m_Transform.fPos.z)));


	DirectX::XMFLOAT4X4 mat[3] = {
	world,
	CUsingCamera::GetThis().GetCamera()->GetViewMatrix(),
	CUsingCamera::GetThis().GetCamera()->GetProjectionMatrix()
	};
	ShaderList::SetWVP(mat);

	// �����̂����ʂ̃��f���ň����Ă��邽�ߕ`��̃^�C�~���O�Ń��[�V�����̎�ނƎ��Ԃ��Z�b�g����
	m_pModel->Play(m_eCurAnime, true);
	m_pModel->SetAnimationTime(m_eCurAnime, m_fAnimeTime);	// �A�j���[�V�����^�C�����Z�b�g
	// �A�j���[�V�����^�C�����Z�b�g���Ă��瓮�����Ȃ��Ɣ��f����Ȃ����ߏ��������i�߂�
	m_pModel->Step(0.00000001f);

	// �����_�[�^�[�Q�b�g�A�[�x�o�b�t�@�̐ݒ�
	RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
	DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
	SetRenderTargets(1, &pRTV, pDSV);		//DSV��null����2D�\���ɂȂ�

	//-- ���f���\��
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

	//-- �e�̕`��
	m_pShadow->Draw(m_Transform, m_fScaleShadow);
}

/* ========================================
	�ʏ�ړ��֐�
	----------------------------------------
	���e�F�v���C���[��ǐՂ���ړ����s��
	----------------------------------------
	����1�F�v���C���[�����蔻��(Sphere)
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CSlime_2::NormalMove()
{

	TPos3d<float> playerPos = m_PlayerTran.fPos;

	// �G����G�l�~�[�̋����A�p�x���v�Z
	float distancePlayer = m_Transform.fPos.Distance(playerPos);

	// �v���C���[�Ƌ��������ȓ���������
	if (distancePlayer < MOVE_DISTANCE_PLAYER)
	{
		if (m_nAtkInterval > LEVEL2_ATTACK_INTERVAL && m_AtcMoveType == ATTACK_NONE)
		{
			m_AtcMoveType = ATTACK_CHARGE;
			m_nAtkInterval = 0;

			// �A�j���[�V�������u�U���v�ɕύX
			if (m_eCurAnime != (int)MOTION_LEVEL2_ATTACK)
			{
				m_eCurAnime = (int)MOTION_LEVEL2_ATTACK;
				m_fAnimeTime = 0.0f;	//�A�j���[�V�����^�C���̃��Z�b�g
			}

			return;
		}
	}

	//��Ԃɂ�镪�򏈗�
	switch (m_AtcMoveType)
	{
	case(ATTACK_NONE):	//�ʏ��Ԃ̎�
		m_nAtkInterval++;
		CSlimeBase::NormalMove();

		// ���݂̃A�j���[�V�������u�ړ��v�ȊO��������ړ����[�V�����ɕύX
		if (m_eCurAnime != (int)MOTION_LEVEL2_MOVE)
		{
			m_eCurAnime = (int)MOTION_LEVEL2_MOVE;
			m_fAnimeTime = 0.0f;	//�A�j���[�V�����^�C���̃��Z�b�g
		}

		return;
	case (ATTACK_CHARGE):
		if (m_nChargeCnt > LEVEL2_ATTACK_CHARGE_CNT)
		{	//�`���[�W�̎��Ԃ𒴂��Ă�����^�b�N����ԂɈڍs����
			m_AtcMoveType = ATTACK_TACKLE;
			m_nChargeCnt = 0;

		}
		else 
		{ //�܂���������J�E���g�𗭂߂�
			m_nChargeCnt++; 
			CSlimeBase::NormalMove();
		}	

		//�^�b�N���̊p�x���m��
		// �G����v���C���[�ւ̃x�N�g��
		DirectX::XMFLOAT3 directionVector;
		directionVector.x = m_Transform.fPos.x - playerPos.x;
		directionVector.y = m_Transform.fPos.y - playerPos.y;
		directionVector.z = m_Transform.fPos.z - playerPos.z;
		
		// �x�N�g���𐳋K�����ĕ����x�N�g���𓾂�
		tackleDirection = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&directionVector));
		// �����x�N�g�������]�s����v�Z
		m_Transform.fRadian.y = (atan2(-tackleDirection.m128_f32[0], -tackleDirection.m128_f32[2]));

		//�ړ���0��
		m_move = TTriType<float>(0.0f, 0.0f, 0.0f);

		return;
	case (ATTACK_TACKLE):
		if (m_nTackleCnt < LEVEL2_ATTACK_TACKLE_CNT)
		{	//�^�b�N�����Ԃɖ����Ȃ��Ȃ�^�b�N���p��
			m_nTackleCnt++;
			m_move.x = (sin(m_Transform.fRadian.y)) * LEVEL2_TACKLE_SPEED;
			m_move.z = (cos(m_Transform.fRadian.y)) * LEVEL2_TACKLE_SPEED;

			return;
		}
		else //�^�b�N�����Ԃ𒴂��Ă���΃^�b�N���I��
		{
			m_AtcMoveType = ATTACK_NONE;
			m_nTackleCnt = 0;
			CSlimeBase::NormalMove();

			// �ړ��A�j���[�V�����ɕύX
			m_eCurAnime = (int)MOTION_LEVEL2_MOVE;
			m_fAnimeTime = 0.0f;	//�A�j���[�V�����^�C���̃��Z�b�g

		}
		break;
	}

	//��L�̂ǂ�if�ɂ����Ă͂܂�Ȃ��ꍇ�����_���ړ�
	RandomMove();

	// ���݂̃A�j���[�V�������u�ړ��v�ȊO��������ړ����[�V�����ɕύX
	if (m_eCurAnime != (int)MOTION_LEVEL2_MOVE)
	{
		m_eCurAnime = (int)MOTION_LEVEL2_MOVE;
		m_fAnimeTime = 0.0f;	//�A�j���[�V�����^�C���̃��Z�b�g
	}
}

/* ========================================
	�X�s�[�h����֐�
	-------------------------------------
	���e�F�X���C���̈ړ����x��ݒ�
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CSlime_2::SetNormalSpeed()
{
	m_fSpeed = LEVEL2_SPEED;	//�ړ����x�ɒ萔���Z�b�g
}



