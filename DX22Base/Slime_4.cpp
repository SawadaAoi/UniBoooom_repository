/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�X���C���T�C�Y4�pcpp
	------------------------------------
	Slime_4.cpp
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
	�E2024/01/31 �A�j���[�V�����̒ǉ� yamashita
	�E2024/02/09 UsingCamera�g�p takagi
	�E2024/02/13 �J�����폜 takagi

========================================== */

// =============== �C���N���[�h ===================
#include "Slime_4.h"
#include "GameParameter.h"	//�萔��`�p�w�b�_�[
#include "UsingCamera.h"	//�J�����g�p

// =============== �萔��` =======================
#if MODE_GAME_PARAMETER
#else
const float LEVEL4_SCALE = 4.0f;
const float LEVEL4_SPEED = ENEMY_MOVE_SPEED * 0.85;
const int	LEVEL4_ATTACK = 2;	// �U����
#endif
const float LEVEL_4_SHADOW_SCALE = 11.0f;	// �X���C���Q���x���S�̉e�̑傫��

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�R���X�g���N�^
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
CSlime_4::CSlime_4()
{
	m_Transform.fScale = { LEVEL4_SCALE,LEVEL4_SCALE ,LEVEL4_SCALE };
	m_Sphere.fRadius *= LEVEL4_SCALE;
	m_eSlimeSize = E_SLIME_LEVEL::LEVEL_4;
	SetNormalSpeed();
	m_nAttack = LEVEL4_ATTACK;
	m_fScaleShadow = LEVEL_4_SHADOW_SCALE;	// �e�̑傫����ݒ�
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
CSlime_4::CSlime_4(TPos3d<float> pos, AnimeModel* pModel)
	: CSlime_4()
{
	m_Transform.fPos = pos;			// �������W���w��
	m_pModel = pModel;
	// �A�j���[�V�����̃Z�b�g
	m_eCurAnime = (int)MOTION_LEVEL3_MOVE;	// ���݂̃A�j���[�V�������Z�b�g
	m_pModel->Play(m_eCurAnime, true);
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
CSlime_4::~CSlime_4()
{
}

void CSlime_4::Update(tagTransform3d playerTransform, float fSlimeMoveSpeed)
{
	m_PlayerTran = playerTransform;
	m_fAnimeTime += ADD_ANIME;	//�A�j���[�V�����̐i�s

	if (!m_bHitMove)	//�G���ʏ�̈ړ���Ԃ̎�
	{
		// �ړ��̃A�j���ɑJ��
		if (m_eCurAnime != MOTION_LEVEL4_MOVE)
		{
			m_eCurAnime = MOTION_LEVEL4_MOVE;
			m_fAnimeTime = 0.0f;
		}

		if (!m_bMvStpFlg  && m_nMvStpCnt == 0)	//������t���O��off�Ȃ�
		{
			NormalMove();	//�ʏ�ٓ�
		}
		else
		{
			MoveStop();	//�������瓦����
		}
	}
	else
	{
		//�G�̐�����шړ�
		HitMove();

		// ������я�Ԃ̃A�j���ɑJ��
		if (m_eCurAnime != MOTION_LEVEL4_HIT)
		{
			m_eCurAnime = MOTION_LEVEL4_HIT;
			m_fAnimeTime = 0.0f;
		}
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
void CSlime_4::Draw()
{

	//-- �e�̕`��
	m_pShadow->Draw(m_Transform, m_fScaleShadow);

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

void CSlime_4::NormalMove()
{
	TPos3d<float> playerPos = m_PlayerTran.fPos;

	// �G����G�l�~�[�̋����A�p�x���v�Z
	float distancePlayer = m_Transform.fPos.Distance(playerPos);

	// �v���C���[�Ƌ��������ȓ���������
	if (distancePlayer < 5)
	{
		// �v���C���[�ւ̊p�x���擾
		float rad = atan2f(playerPos.x - m_Transform.fPos.x, playerPos.z - m_Transform.fPos.z);
		// �v���C���[�Ɣ��Ε����Ɉړ�
		m_move.x = -(sinf(rad)) * m_fSpeed;
		m_move.z = -(cosf(rad)) * m_fSpeed;
		m_Transform.fRadian.y = atan2f(m_move.x, m_move.z);
	}
	else
	{
		RandomMove();	// �����_���ړ�

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
void CSlime_4::SetNormalSpeed()
{
	m_fSpeed = LEVEL4_SPEED;	//�ړ����x�ɒ萔���Z�b�g
}



