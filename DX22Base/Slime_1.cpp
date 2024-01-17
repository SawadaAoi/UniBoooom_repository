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
CSlime_1::CSlime_1(TPos3d<float> pos,VertexShader* pVS, AnimeModel* pModel, vector<AnimeModel::AnimeNo> anime)
	: CSlime_1()
{
	m_Transform.fPos = pos;			// �������W���w��
	m_pVS = pVS;
	m_pModel = pModel;
	pModel->SetVertexShader(ShaderList::GetVS(ShaderList::VS_ANIME));
	// �A�j���[�V�����̎󂯓n��
	m_Anime = anime;
	m_pModel->Play(m_Anime[MOTION_LEVEL1_MOVE],true);
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
	// m_pModel->Step(ADD_ANIME);
	m_fAnimeTime += ADD_ANIME;		// �A�j���[�V������i�s


	if (!m_bHitMove)	//�G���ʏ�̈ړ���Ԃ̎�
	{
		if (!m_bEscape  && m_nEscapeCnt == 0)	// ������t���O��off�Ȃ�
		{
			NormalMove();	//�ʏ�ړ�
		}
		else
		{
			Escape();	//�������瓦����
			//m_pModel->Step(-ADD_ANIME);	// �߂��ɔ���������ꍇ�A�j����߂��ĐÎ~������
		}
	}
	else
	{
		// ������уA�j���[�V�����Đ�
		if (m_pModel->GetPlayNo() == m_Anime[MOTION_LEVEL1_MOVE])
		{
			//m_pModel->Play(m_Anime[MOTION_LEVEL1_HIT],false);
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
	����1�F�J����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSlime_1::Draw(const CCamera * pCamera)
{

	DirectX::XMFLOAT4X4 mat[3];

	mat[0] = m_Transform.GetWorldMatrixSRT();
	mat[1] = pCamera->GetViewMatrix();
	mat[2] = pCamera->GetProjectionMatrix();

	//-- �s����V�F�[�_�[�֐ݒ�
	m_pVS->WriteBuffer(0, mat);

	ShaderList::SetWVP(mat);

	// �A�j���[�V�����̌��ݎ��Ԃ��Z�b�g
	m_pModel->SetAnimationTime(m_pModel->GetPlayNo(), m_fAnimeTime);

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
	}

	//-- �e�̕`��
	m_pShadow->Draw(m_Transform, m_fScaleShadow, pCamera);
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