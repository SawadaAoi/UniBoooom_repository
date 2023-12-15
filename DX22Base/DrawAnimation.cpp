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
	�E2023/12/15 �f�t�H���g���ƃT�C�Y�������������̂ŕύX�ł���悤�C�� nieda

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
	����4�F�`��T�C�Y
	����5�F�c���̕������̍ő吔
	����6�F�A�j���[�V�����̐؂�ւ��Ԋu
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CDrawAnim::CDrawAnim(const char* textureFile, CCamera* pCamera, int nSplitMax, TDiType<float> fSize, TDiType<int> nSplit, int nCnt)
	: m_nNumAnim(0)
	, m_nNumAnimMax(0)
	, m_nSplitNum(0, 0)
	, m_fSize(0.0f, 0.0f, 0.0f)
	, m_fUvPos(0.0f, 0.0f)
	, m_fUvScale(0.0f, 0.0f)
	, m_nFrameCnt(0)
	, m_nSwitchCnt(0)
	, m_bLoop(false)
	, m_bAnim(true)
{
	SetTexture(textureFile);	// �e�N�X�`�����Z�b�g
	SetCamera(pCamera);			// �J�������Z�b�g
	m_fSize = { fSize.x, fSize.y, 0.0f };	// �`��T�C�Y�ݒ�
	m_nNumAnimMax = nSplitMax;	// �������̍ő�l���i�[
	m_nSplitNum = nSplit;		// �c���̕��������i�[
	m_fUvScale = { 1.0f / m_nSplitNum.x, 1.0f / m_nSplitNum.y };	// UV�����T�C�Y���i�[
	m_nSwitchCnt = nCnt;		// �A�j���[�V�����̐؂�ւ��Ԋu���i�[
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
	if (m_bAnim)
	{
		m_nFrameCnt++;	// �`��؂�ւ��p�J�E���g��1�i�߂�

		if (m_nFrameCnt > m_nSwitchCnt)		// ��莞�Ԍo�߂�����`����X�V����
		{
			m_nFrameCnt = 0;	// �J�E���g�����Z�b�g
			m_fUvPos.x = (m_fUvScale.x) * (m_nNumAnim % m_nSplitNum.x);	// �`�悷��UV���W���v�Z
			m_fUvPos.y = (m_fUvScale.y) * (m_nNumAnim / m_nSplitNum.x);	// �`�悷��UV���W���v�Z

			m_nNumAnim++;			// �`�悷��A�j���[�V�����ԍ����X�V
			SetSize(m_fSize);		// �`��T�C�Y���Z�b�g
			SetUvOffset(m_fUvPos);	// UV���W���Z�b�g
			SetUvScale(m_fUvScale);	// UV�����T�C�Y���Z�b�g
		}

		if (m_nNumAnim == m_nNumAnimMax)		// �ŉ��i�̕`�悪�I�������
		{
			m_nNumAnim = 0;		// �J�E���g�����Z�b�g

			if (!m_bLoop)	// ���[�v�Đ��t���O��OFF�Ȃ�
			{
				m_bAnim = false;		// �\���t���O��OFF
			}
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
	if (m_bAnim)	// �`��t���O��ON�̊Ԃ͕`�悷��
	{
		C2dPolygon::Draw();		// �`��
	}
}

/* ========================================
	���[�v�Đ��t���O�Z�b�g�֐�
	-------------------------------------
	���e�F���[�v�Đ��t���O���Z�b�g
	-------------------------------------
	�����F���[�v�Đ�����t���O�itrue�Ȃ烋�[�v����j
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CDrawAnim::SetLoopFlg(bool bLoop)
{
	m_bLoop = bLoop;	// �t���O���Z�b�g
}

/* ========================================
	�A�j���Đ��t���O�Q�b�g�֐�
	-------------------------------------
	���e�F���[�v�Đ��t���O���Z�b�g
	-------------------------------------
	�����F���[�v�Đ�����t���O�itrue�Ȃ烋�[�v����j
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
bool CDrawAnim::GetAnimFlg()
{
	return m_bAnim;
}