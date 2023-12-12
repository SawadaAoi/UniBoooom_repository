/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	UI�A�j���[�V�����`��pcpp
	---------------------------------------
	DrawAnimation.h

	�쐬��
			nieda

	�ύX����
	�E2023/12/08 �V�K�쐬 nieda
	�E2023/12/09 ���� nieda
	�E2023/12/11 ���� nieda
	�E2023/12/12 tkg�搶�̎w���ɂ��2dpolygon�ɑΉ� nieda

========================================== */

// =============== �C���N���[�h ===================
#include "DrawAnimation.h"	// ���g�̃w�b�_


/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�F�ǂݍ��ރt�@�C���̃p�X
	����2�F�J�����N���X�̃|�C���^
	����3�F�������̍ő吔
	����4�F�c���̕������̍ő吔
	����5�F�A�j���[�V�����̐؂�ւ��Ԋu
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CDrawAnim::CDrawAnim(const char* textureFile, CCamera* pCamera, int nMax, TDiType<int> nCut, int nCntSwitch)
	: m_nNumAnim(0)
	, m_nNumAnimMax(0)
	, m_NumCut(0, 0)
	, m_fUvpos(0.0f, 0.0f)
	, m_fUvscale(0.0f, 0.0f)
	, m_nCntSwitch(0)
	, m_nCntFrame(0)
	, bRoop(true)
{
	SetTexture(textureFile);	// �e�N�X�`�����Z�b�g
	SetCamera(pCamera);			// �J�������Z�b�g
	m_fUvscale = { 1.0f / m_NumCut.x, 1.0f / m_NumCut.y };	// UV�����T�C�Y���i�[
	m_nNumAnimMax = nMax;		// �������̍ő�l���i�[
	m_NumCut = nCut;			// �c���̕��������i�[
	m_nCntSwitch = nCntSwitch;	// �A�j���[�V�����̐؂�ւ��Ԋu���i�[
}

/* ========================================
	2D�A�j���[�V�����X�V�֐�
	-------------------------------------
	���e�F2D�A�j���[�V�����̍X�V����
	-------------------------------------
	�����F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CDrawAnim::Update()
{
	if (bRoop)
	{
		m_nCntFrame++;	// �`��؂�ւ��p�J�E���g��1�i�߂�

		if (m_nCntFrame > m_nCntSwitch)		// ��莞�Ԍo�߂�����`����X�V����
		{
			m_nCntSwitch = 0;	// �J�E���g�����Z�b�g
			m_fUvpos.x = (m_fUvscale.x) * (m_nNumAnim % m_NumCut.x);	// �`�悷��UV���W���v�Z
			m_fUvpos.y = (m_fUvscale.y) * (m_nNumAnim / m_NumCut.x);	// �`�悷��UV���W���v�Z

			m_nNumAnim++;			// �`�悷��A�j���[�V�����ԍ����X�V
			SetUvOffset(m_fUvpos);	// UV���W���Z�b�g
			SetUvScale(m_fUvscale);	// UV�����T�C�Y���Z�b�g
		}

		if (m_nNumAnim == m_nNumAnimMax)		// �ŉ��i�̕`�悪�I�������
		{
			m_nNumAnim = 0;		// �J�E���g�����Z�b�g
			bRoop = false;		// �\���t���O��OFF
		}
	}
}

/* ========================================
	2D�A�j���[�V�����`��֐�
	-------------------------------------
	���e�F2D�A�j���[�V�����̕`�揈��
	-------------------------------------
	�����F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CDrawAnim::Draw()
{
	if (bRoop)	// �`��t���O��ON�̊Ԃ͕`�悷��
	{
		C2dPolygon::Draw();		// �`��
	}
}
