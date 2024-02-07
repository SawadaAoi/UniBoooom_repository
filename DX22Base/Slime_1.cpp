/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�X���C���T�C�Y1�pcpp
	------------------------------------
	Slime_1.cpp
	------------------------------------
	�쐬��	�V�c

	�ύX����
	�E2023/11/08 �쐬 sawada
	�E2023/11/08 �傫���̒萔���`	yamashita
	�E2023/11/08 �X���C���̈ړ����x��傫�����ƂɕύX����֐����쐬	yamashita
	�E2023/11/08 �X���C���̈ړ����x��傫�����ƂɕύX����֐����쐬	yamashita
	�E2023/11/08 �R���X�g���N�^�Ń��x�����Ƃ̃p�����[�^���Z�b�g	yamashita
	�E2023/11/11 define�p�w�b�_�ǉ� suzumura
	�E2023/11/14 Base���烂�f���A�V�F�[�_�̓ǂݍ��݂��ړ� Suzumura
	�E2023/11/14 SphereInfo�̕ύX�ɑΉ� takagi
	�E2023/11/15 �X���C���̃��f���ƒ��_�V�F�[�_�[��manager����󂯎��悤�ɕύX yamashita
	�E2023/11/28 �e�̑傫����ݒ肷��ϐ��ǉ� nieda
	�E2023/12/07 �Q�[���p�����[�^����ꕔ�萔�ړ� takagi
	�E2024/1/26  �A�j���[�V�����̎��� Yamashita

========================================== */

// =============== �C���N���[�h ===================
#include "Slime_1.h"
#include "GameParameter.h"		//�萔��`�p�w�b�_�[

// =============== �萔��` =======================
const int	LEVEL1_ATTACK = 1;						// �U����
#if MODE_GAME_PARAMETER
#else
const float LEVEL1_SCALE = 1.0f;
const float LEVEL1_SPEED = ENEMY_MOVE_SPEED;
#endif
const float LEVEL_1_SHADOW_SCALE = 1.0f;	// �X���C���Q���x���P�̉e�̑傫��

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�R���X�g���N�^
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
CSlime_1::CSlime_1()
{
	m_Transform.fScale = { LEVEL1_SCALE,LEVEL1_SCALE ,LEVEL1_SCALE };
	m_Sphere.fRadius *= LEVEL1_SCALE;
	m_eSlimeSize = E_SLIME_LEVEL::LEVEL_1;
	SetNormalSpeed();
	m_nAttack = LEVEL1_ATTACK;
	m_fScaleShadow = LEVEL_1_SHADOW_SCALE;	// �e�̑傫����ݒ�
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
CSlime_1::CSlime_1(TPos3d<float> pos, AnimeModel* pModel)
	: CSlime_1()
{
	m_Transform.fPos = pos;			// �������W���w��
	m_pModel = pModel;
	// �A�j���[�V�����̃Z�b�g
	m_eCurAnime = (int)MOTION_LEVEL1_MOVE;	// ���݂̃A�j���[�V�������Z�b�g
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
CSlime_1::~CSlime_1()
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
void CSlime_1::Update(tagTransform3d playerTransform, float fSlimeMoveSpeed)
{
	m_PlayerTran = playerTransform;	// �v���C���[�̍ŐV�p�����[�^���擾

	// �A�j���[�V�����̏�Ԃɂ���ăA�j���[�V�����̐i�s���x��ύX
	if (m_eCurAnime == (int)MOTION_LEVEL1_HIT)
	{
		m_fAnimeTime += (ADD_ANIME * 0.7f);		// �A�j���[�V������i�s
	}
	else if (m_eCurAnime == (int)MOTION_LEVEL1_MOVE)
	{
		m_fAnimeTime += ADD_ANIME;		// �A�j���[�V������i�s
	}

	if (!m_bHitMove)	//�G���ʏ�̈ړ���Ԃ̎�
	{
		// ���݂̃A�j���[�V�������u������сv��������ړ����[�V�����ɕύX
		if (m_eCurAnime == (int)MOTION_LEVEL1_HIT)
		{
			m_eCurAnime = (int)MOTION_LEVEL1_MOVE;
			m_fAnimeTime = 0.0f;	//�A�j���[�V�����^�C���̃��Z�b�g
		}

		if (!m_bMvStpFlg  && m_nMvStpCnt == 0)	//��~�t���O��off�Ȃ�
		{
			NormalMove();	//�ʏ�ړ�
		}
		else
		{
			MoveStop();	//�������瓦����

			// ��~���̓A�j���[�V��������~�����邽�߂ɃA�j���[�V�����^�C����߂�
			m_fAnimeTime -= ADD_ANIME;
		}
	}
	else
	{
		// ������уA�j���[�V�����Đ�
		if (m_eCurAnime == (int)MOTION_LEVEL1_MOVE)
		{
			m_eCurAnime = (int)MOTION_LEVEL1_HIT;
			m_fAnimeTime = 0.0f;	// �A�j���[�V�����^�C���̃��Z�b�g
		}

		//�G�̐�����шړ�
		HitMove();
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
void CSlime_1::Draw()
{
	if (!m_pCamera) { return; }	//�k���`�F�b�N

	//�s���Ԃ��擾���ăZ�b�g
	DirectX::XMFLOAT4X4 world;
	DirectX::XMStoreFloat4x4(&world, XMMatrixTranspose(
		DirectX::XMMatrixScaling(m_Transform.fScale.x, m_Transform.fScale.y, m_Transform.fScale.z) *
		DirectX::XMMatrixRotationY(m_Transform.fRadian.y) *
		DirectX::XMMatrixTranslation(m_Transform.fPos.x, m_Transform.fPos.y, m_Transform.fPos.z)));

	DirectX::XMFLOAT4X4 mat[3] = {
	world,
	m_pCamera->GetViewMatrix(),
	m_pCamera->GetProjectionMatrix()
	};
	ShaderList::SetWVP(mat);	

	// �����̂����ʂ̃��f���ň����Ă��邽�ߕ`��̃^�C�~���O�Ń��[�V�����̎�ނƎ��Ԃ��Z�b�g����
	m_pModel->Play(m_eCurAnime,true);
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

	//-- �e�̕`��
	m_pShadow->Draw(m_Transform, m_fScaleShadow, m_pCamera);
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
void CSlime_1::SetNormalSpeed()
{
	m_fSpeed = LEVEL1_SPEED;	//�ړ����x�ɒ萔���Z�b�g
}