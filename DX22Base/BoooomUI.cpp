/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	BoooomUI�\��
	------------------------------------
	BoooomUI.cpp
	------------------------------------
	�쐬��
		�A�F��
	�ύX����
	�E2023/11/20 cpp,�쐬 Tei
	�E2023/11/20 �`��ŕK�v�Ȋ֐����쐬 Tei
	�E2023/12/07 �Q�[���p�����[�^����萔�ړ� takagi

========================================== */

// =============== �C���N���[�h ===================
#include "BoooomUI.h"

// =============== �萔��` ===================
const int MAX_ANIM(1);			//�A�j���[�V������
const TDiType<int> MAX_SEAT(1);	//1x1

const float BOOOOM_UI_SIZE_X = 1.0f;		//BoooomUI��X�̒����itexture�̔䗦�ƍ��킹��j
const float BOOOOM_UI_SIZE_Y = 0.565f;		//BoooomUI��Y�̒����itexture�̔䗦�ƍ��킹��j
const float BOOOOM_UI_SCALE_X = 6.0f;		//BoooomUI�T�C�Y�̃X�P�[��
const float BOOOOM_UI_SCALE_Y = 6.0f;		//BoooomUI�T�C�Y�̃X�P�[��

const float BOOOOM_UI_MAX_SCALE_X = BOOOOM_UI_SCALE_X * 2.5f;
const float BOOOOM_UI_MAX_SCALE_Y = BOOOOM_UI_SCALE_Y * 2.5f;

const float ANIM_TIME_RATE = 0.7f;	// ���������Ԃ̓��ABOOOOM�\�����s���͉̂�����(0.0f~1.0f)

/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CBoooomUI::CBoooomUI(TPos3d<float> pos, Texture* pTex, const CCamera* pCamera, float fTime /*,const int & nFrame*/)
	://m_pBoooomTex(pTex)
	//,m_pos(pos)
	//,m_scale{ BOOOOM_UI_SCALE_X, BOOOOM_UI_SCALE_Y, 0.0f}
	 m_fExplodeTime(fTime * ANIM_TIME_RATE)	//���������Ԃ��Z�b�g����
	, m_nDelFrame(0)
	, m_bDelFlg(false)
	, m_nAnimFrame(0)
	, m_fAnimRate(0.0f)
	, m_fAddScaleX(0.0f)
	, m_fAddScaleY(0.0f)
	, m_fScalingTime(fTime * ANIM_TIME_RATE)
	, CDrawAnim(MAX_ANIM, MAX_SEAT)	//�Ϗ�
	, m_pCnt(nullptr)				//�k���p�J�E���^
{

	SetCamera(pCamera);		//�J�����Z�b�g
	SetPos(pos);
	SetSize(TTriType<float>(BOOOOM_UI_SCALE_X, BOOOOM_UI_SCALE_Y, 0.0f));
	SetTexture(pTex);
	m_pCnt = new CFrameCnt((int)m_fScalingTime);	//�J�E���g�J�n

}
/* ========================================
	�f�X�g���N�^
	----------------------------------------
	���e�F�j�����ɍs������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CBoooomUI::~CBoooomUI()
{
	SAFE_DELETE(m_pCnt);

}

void CBoooomUI::Update()
{
	// =============== �X�V ===================
	CDrawAnim::Update();	//�e�̊֐��g�p
	

	DisplayTimeAdd();
	//TODO�����A������Ƃ��̃X�P�[�� ?

	m_nAnimFrame++;

	float fExpandTime = m_fScalingTime / 2.0f;
	if (m_nAnimFrame < (int)fExpandTime)
	{
		m_fAnimRate += 1.0f / fExpandTime ;	//�t���[�����Z
		
	}
	else if(m_nAnimFrame > 0)
	{
		m_fAnimRate -= 1.0f / (m_fScalingTime - fExpandTime);	//�t���[�����Z

		//-- ���X�ɏ����Ă�������
		if (m_pCnt)	//�k���`�F�b�N
		{
			--*m_pCnt;	//�J�E���g�_�E��
			if (m_pCnt->IsFin())
			{
				delete m_pCnt;		//���������
				m_pCnt = nullptr;	//��A�h���X���
			}
			else
			{
				SetAlpha(m_pCnt->GetRate());					//�����x�X�V
			}
		}
	}
	// 0�������Ȃ��悤��
	if (m_fAnimRate < 0) m_fAnimRate = 0;

	// ��Ԓl���g�p���ăX�P�[�����v�Z
	float scalingFactor = (sqrt(1 - pow(m_fAnimRate - 1, 2)));
	// �X�P�[���̐ݒ�
	SetSize(TTriType<float>(BOOOOM_UI_SCALE_X + ((BOOOOM_UI_MAX_SCALE_X - BOOOOM_UI_SCALE_X) * scalingFactor),
		BOOOOM_UI_SCALE_Y + ((BOOOOM_UI_MAX_SCALE_Y - BOOOOM_UI_SCALE_Y) * scalingFactor),0.0f));
	// uv�̃Y���𒲐�
	SetUvScale(TDiType<float>(1.0f, 1.565f));


}

/* ========================================
	�`��֐�
	----------------------------------------
	���e�FBoooom�̕`��
	----------------------------------------
	����1�F�`�惂�[�h
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CBoooomUI::Draw(const E_DRAW_MODE & eMode)
{
	if (m_pCnt)	//�k���`�F�b�N
	{
		// =============== �`�� ===================
		CDrawAnim::Draw();	//�e�̊֐��g�p
		if (!m_bAnim)	//�A�j���[�V���������̕`�悪�I����Ă���
		{
			C2dPolygon::Draw(E_DRAW_MODE_BILLBOARD);	//�Ō�̏�ʂ�`��������
		}
	}
}

/* ========================================
	boooomUI�\���J�E���g���Z�����֐�
	-------------------------------------
	���e�FboooomUI�\���J�E���g�����Z���Ĉ��b����������I���t���O���I���ɂ���
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CBoooomUI::DisplayTimeAdd()
{
	m_nDelFrame++;		// �t���[�����Z

	// ���b�����Ԃ��o������
	if (m_fExplodeTime <= m_nDelFrame)
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
bool CBoooomUI::GetDelFlg()
{
	return m_bDelFlg;
}


/* ========================================
	�I���m�F�֐�
	-------------------------------------
	���e�F�I���m�F
	-------------------------------------
	�����F�Ȃ�
	-------------------------------------
	�ߒl�F���̃I�u�W�F�N�g�̖�ڂ��I��������
=========================================== */
bool CBoooomUI::IsFin()
{
	if (m_pCnt)
	{
		// =============== �� ===================
		return false;	//�J�E���^�����݂���
	}
	else
	{
		// =============== �� ===================
		return true;	//�J�E���^�����݂��Ȃ�
	}
}