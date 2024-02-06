/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�����G�t�F�N�g�`��
	---------------------------------------
	UnionEffectText.cpp

	�쐬��
			Tei

	�ύX����
	�E2024/02/06 �����G�t�F�N�g nieda

========================================== */

// =============== �C���N���[�h ===================
#include "UnionSmokeEffect.h"
#include "Defines.h"
#include "GameParameter.h"

// =============== �萔��` ===================
const int UNION_SMOKE_SPLIT_NUM_MAX = 55;				// �����̉��A�j���[�V�����̕������̍ő吔
const TDiType<int> UNION_SMOKE_SPLIT_NUM = { 5, 11 };	// �����̉��A�j���[�V�����̏c���������̍ő吔
const int UNION_SMOKE_SWITCH_CNT = 1;					// �A�j���[�V�����؂�ւ��Ԋu

/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�F�������W�ix,y,z�j
	����2�F�����T�C�Y�ix,y,z�j
	����3�F�ǂݍ��ނ̉摜
	����4�F�J�����N���X�̃|�C���^
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CUnionSmokeEffect::CUnionSmokeEffect(TPos3d<float> pos, TPos3d<float> size, Texture* pTex, const CCamera * pCamera)
	: CDrawAnim(UNION_SMOKE_SPLIT_NUM_MAX, UNION_SMOKE_SPLIT_NUM, UNION_SMOKE_SWITCH_CNT)
	, m_bDelFlg(false)
	, m_nDelFrame(0)
	, m_fEffectTime(UNION_SMOKE_SPLIT_NUM_MAX)
{
	m_pTexUnionSmoke = new CDrawAnim(UNION_SMOKE_SPLIT_NUM_MAX, UNION_SMOKE_SPLIT_NUM, UNION_SMOKE_SWITCH_CNT);
	m_pTexUnionSmoke->SetCamera(pCamera);
	m_pTexUnionSmoke->SetTexture(pTex);
	m_pTexUnionSmoke->SetPos(pos);
	m_pTexUnionSmoke->SetSize(size);
	m_pTexUnionSmoke->SetLoopFlg(false);
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
CUnionSmokeEffect::~CUnionSmokeEffect()
{
	SAFE_DELETE(m_pTexUnionSmoke);
}

/* ========================================
	�X�V�֐�
	-------------------------------------
	���e�F�����G�t�F�N�g�̍X�V����
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CUnionSmokeEffect::Update()
{
	// �A�j���V�����̑��x�������邽�߁A���s���i�͋Z�j
	m_pTexUnionSmoke->Update();
	m_pTexUnionSmoke->Update();
	DisplayTimeAdd();
}

/* ========================================
	�`��֐�
	-------------------------------------
	���e�F�����G�t�F�N�g�̕`�揈��
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CUnionSmokeEffect::Draw()
{
	m_pTexUnionSmoke->Draw(E_DRAW_MODE_BILLBOARD);
}

/* ========================================
	�����G�t�F�N�g�\���J�E���g���Z�����֐�
	-------------------------------------
	���e�F�����G�t�F�N�g�\���J�E���g�����Z���čĐ��b���o������I���t���O���I���ɂ���
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CUnionSmokeEffect::DisplayTimeAdd()
{
	m_nDelFrame++;	// �t���[�����Z

	// �Đ��b���o������폜
	if (m_fEffectTime <= m_nDelFrame)
	{
		m_bDelFlg = true;	// �폜�t���O�𗧂Ă�
	}
}

/* ========================================
	�폜�t���O�擾�����֐�
	-------------------------------------
	���e�F�폜�t���O���擾����
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F�폜�t���O(bool)
=========================================== */
bool CUnionSmokeEffect::GetDelFlg()
{
	return m_bDelFlg;
}
