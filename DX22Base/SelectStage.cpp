/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X�e�[�W�Z���N�g����
	---------------------------------------
	SelectStage.cpp

	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/11/16 ���� takagi
	�E2023/12/12 �X�e�[�W�Z���N�g��ǉ��@yamamoto
	�E2024/01/26 �g�k���� takagi
	�E2024/01/26 �I���A����SE�ǉ� suzumura
	�E2024/01/28 �������� takagi

========================================== */

// =============== �C���N���[�h ===================
#include "SelectStage.h"	//���g�̃w�b�_
#include "Input.h"			//���͊Ǘ�
#define _USE_MATH_DEFINES	//math.h�̒�`�g�p
#include <math.h>			//M_PI�g�p
#include <algorithm>		//clamp�g�p
#include "Delete.h"			//�폜�}�N��

// =============== �萔��` =======================
const TDiType<int> HISCORE_NUM_SPLIT = { 5,2 };		// �n�C�X�R�A�����摜�̕�����
const TDiType<float> HISCORE_NUM_UVSCALE = { 1.0f / HISCORE_NUM_SPLIT.x ,1.0f / HISCORE_NUM_SPLIT.y };		// �n�C�X�R�A�����摜�̕�����

const TTriType<float> HISCORE_BASE_POS[3] = {	// �n�C�X�R�A�̃X�e�[�W�ʂ̈ʒu(�w�i�A�e�L�X�g�A�X�R�A���܂Ƃ߂�)
	{220.0f, 150.0f, 0.0f},
	{600.0f, 550.0f, 0.0f},
	{1000.0f, 150.0f, 0.0f},
};

/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CSelectStage::CSelectStage()
	: m_fSelectSize(INIT_SIZE_ARR_LET.x)	//�I�����Ă���I�u�W�F�N�g�̑傫��
	, m_bStickFlg(false)					//�X�e�B�b�N�̌X�|�L��
	, m_pFrameCntFall(nullptr)			//��z�������p�t���[���J�E���^
	, m_pFrameCntScale(nullptr)			//�g�k�p�t���[���J�E���^
	, m_bCntUpDwn(false)					//�J�E���g�A�b�v�E�_�E��
	, m_eNextType(CScene::E_TYPE_STAGE1)	//�����̎��̃V�[��
	, m_nButtonAlphaCnt(0)			//�g�k�p�t���[���J�E���^
	, m_pSE{ nullptr,nullptr }
	, m_pSESpeaker{ nullptr ,nullptr }
{
	// =============== ���I�m�� =====================
	for (int nIdx = 0; nIdx < static_cast<int>(E_2D_OBJECT_MAX); nIdx++)
	{
		if (m_p2dObject.find(static_cast<E_2D_OBJECT>(nIdx)) != m_p2dObject.end())	//�A�N�Z�X�E�k���`�F�b�N
		{
			// =============== ���f =====================
			continue;	//���̒l�̏�����
		}
		m_p2dObject.emplace(static_cast<E_2D_OBJECT>(nIdx), new C2dPolygon());
	}
	m_pFrameCntScale = new CFrameCnt(CHANGE_SCALE_HALF_TIME, m_bCntUpDwn);	//�t���[��������

	// =============== ������ =====================
	for (int nIdx = 0; nIdx < static_cast<int>(m_p2dObject.size()); nIdx++)
	{
		if (m_p2dObject.find(static_cast<E_2D_OBJECT>(nIdx)) != m_p2dObject.end() && m_p2dObject.at(static_cast<E_2D_OBJECT>(nIdx)))	//�A�N�Z�X�E�k���`�F�b�N
		{
			m_p2dObject.at(static_cast<E_2D_OBJECT>(nIdx))->SetPos(INIT_MAP_POS.at(static_cast<E_2D_OBJECT>(nIdx)));					//�ʒu�Z�b�g
			m_p2dObject.at(static_cast<E_2D_OBJECT>(nIdx))->SetRotate(INIT_MAP_ROTATE.at(static_cast<E_2D_OBJECT>(nIdx)));				//��]�Z�b�g
			m_p2dObject.at(static_cast<E_2D_OBJECT>(nIdx))->SetTexture(MAP_TEXTURE_FILE.at(static_cast<E_2D_OBJECT>(nIdx)).c_str());	//�e�N�X�`���Z�b�g
			m_p2dObject.at(static_cast<E_2D_OBJECT>(nIdx))->SetSize(INIT_MAP_SIZE.at(static_cast<E_2D_OBJECT>(nIdx)));					//�g�k�Z�b�g
		}
	}

	//=== �T�E���h�t�@�C���ǂݍ��� =====
	LoadSound();	

	// �f�[�^�󂯌p��
	m_Data.Load();	//�t�@�C���ɏオ���Ă������ǂݍ���

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
CSelectStage::~CSelectStage()
{
	// �j������
	SAFE_DELETE_POINTER_MAP(m_p2dObject);	//2d�I�u�W�F�N�g�폜
	SAFE_DELETE(m_pFrameCntScale);			//�J�E���^�폜
	SAFE_DELETE(m_pFrameCntFall);			//�J�E���^�폜
}

/* ========================================
	�X�V�֐�
	----------------------------------------
	���e�F�X�V����
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CSelectStage::Update()
{

	// =============== ���� =====================
	if (!m_pFrameCntFall)	//��z���������Ă��Ȃ�=�I��
	{
		Select();

		// =============== �g�k�X�V =====================
		if (m_pFrameCntScale)	//�k���`�F�b�N
		{
			m_pFrameCntScale->Count();	//�J�E���g�i�s
			m_fSelectSize = -(cosf(static_cast<float>(M_PI) * m_pFrameCntScale->GetRate()) - 1.0f) / 2.0f * (MAX_SIZE_ARR_LET - MIN_SIZE_ARR_LET) + MIN_SIZE_ARR_LET;	//�C�[�W���O���g�����傫���ύX
			if (m_pFrameCntScale->IsFin())	//�J�E���g����
			{
				m_bCntUpDwn ^= 1;													//�J�E���g�A�b�v�_�E���t�]
				SAFE_DELETE(m_pFrameCntScale);											//�J�E���^�폜
				m_pFrameCntScale = new CFrameCnt(CHANGE_SCALE_HALF_TIME, m_bCntUpDwn);	//�J�E���g�A�b�v�E�_�E��
			}
		}

		// =============== �g�k�ύX =====================
		switch (m_eNextType)	//�I������Ă�����̂�ύX
		{	//TODO:�A�N�Z�X�E�k���`�F�b�N
		case CScene::E_TYPE_STAGE1:	//�X�e�[�W1
			m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->SetSize({ m_fSelectSize * ASPECT_RATE_ARR_LET, m_fSelectSize, 1.0f });	//�X�e�[�W1�̎�z��
			m_p2dObject.at(E_2D_OBJECT_STAGE_1_REMINE)->SetSize({ m_fSelectSize * ASPECT_RATE_ARR_LET, m_fSelectSize, 1.0f });	//�X�e�[�W1�̎�z��
			break;	//���򏈗��I��
		case CScene::E_TYPE_STAGE2:	//�X�e�[�W2
			m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->SetSize({ m_fSelectSize * ASPECT_RATE_ARR_LET, m_fSelectSize, 1.0f });	//�X�e�[�W2�̎�z��
			m_p2dObject.at(E_2D_OBJECT_STAGE_2_REMINE)->SetSize({ m_fSelectSize * ASPECT_RATE_ARR_LET, m_fSelectSize, 1.0f });	//�X�e�[�W2�̎�z��
			break;	//���򏈗��I��
		case CScene::E_TYPE_STAGE3:	//�X�e�[�W3
			m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->SetSize({ m_fSelectSize * ASPECT_RATE_ARR_LET, m_fSelectSize, 1.0f });	//�X�e�[�W3�̎�z��
			m_p2dObject.at(E_2D_OBJECT_STAGE_3_REMINE)->SetSize({ m_fSelectSize * ASPECT_RATE_ARR_LET, m_fSelectSize, 1.0f });	//�X�e�[�W3�̎�z��
			break;	//���򏈗��I��			
		}
	}
	else
	{	//��z���������Ă���=�I������

		// =============== ���� =====================
		if (m_pFrameCntFall->IsFin())	//�J�E���g����
		{
			// =============== �t���O���� =====================
			m_bFinish = true;	//�V�[���I��

			// =============== �I�� =====================
			SAFE_DELETE(m_pFrameCntFall);	//�J�E���^�폜
			return;							//�������f
		}

		// =============== �J�E���g =====================
		m_pFrameCntFall->Count();	//�J�E���g�i�s

		// =============== �ϐ��錾 =====================
		TTriType<float> fPos = 0.0f;	//�ʒu
		auto EasingFunc = [this, &fPos](const TTriType<float>& fBasePos)->void {
			// =============== �ϐ��錾 =====================
			float fCompare = 7.5625;	//��r�Ώ�

			// =============== ������ =====================
			fPos = fBasePos;

			// =============== �X�V =====================
			fPos.y = (1.0f - powf(m_pFrameCntFall->GetRate(), 4.0f)) * (-m_fSelectSize / 2.0f - fBasePos.y) + fBasePos.y;	//y�l�X�V	GetRate()��1to0
		};	//�����ʒu�E�����T�C�Y�����Ƃ�fPos�ɗ�����ʒu���i�[

		// =============== ������ =====================
		switch (m_eNextType)	//�I������Ă�����̂�ύX
		{	//TODO:�A�N�Z�X�E�k���`�F�b�N
		case CScene::E_TYPE_STAGE1:	//�X�e�[�W1
			EasingFunc(INIT_MAP_POS.at(E_2D_OBJECT_STAGE_1_LEAVE));	//�X�e�[�W1�̎�z��			
			break;	//���򏈗��I��
		case CScene::E_TYPE_STAGE2:	//�X�e�[�W2
			EasingFunc(INIT_MAP_POS.at(E_2D_OBJECT_STAGE_2_LEAVE));	//�X�e�[�W2�̎�z��	
			break;	//���򏈗��I��
		case CScene::E_TYPE_STAGE3:	//�X�e�[�W3
			EasingFunc(INIT_MAP_POS.at(E_2D_OBJECT_STAGE_3_LEAVE));	//�X�e�[�W3�̎�z��	
			break;	//���򏈗��I��
		}

		// =============== �����ʒu�X�V =====================
		switch (m_eNextType)	//�I������Ă�����̂�ύX
		{	//TODO:�A�N�Z�X�E�k���`�F�b�N
		case CScene::E_TYPE_STAGE1:	//�X�e�[�W1
			m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->SetPos(fPos);	//�X�e�[�W1�̎�z��
			break;	//���򏈗��I��
		case CScene::E_TYPE_STAGE2:	//�X�e�[�W2
			m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->SetPos(fPos);	//�X�e�[�W2�̎�z��
			break;	//���򏈗��I��
		case CScene::E_TYPE_STAGE3:	//�X�e�[�W3
			m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->SetPos(fPos);	//�X�e�[�W3�̎�z��
			break;	//���򏈗��I��
		}
	}

	m_nButtonAlphaCnt++;	//�J�E���g�i�s

}

/* ========================================
	�`��֐�
	----------------------------------------
	���e�F�`�揈��
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
	======================================== */
void CSelectStage::Draw() //const
{
	// =============== �`�� =====================	//TODO:�A�N�Z�X�E�k���`�F�b�N


	m_p2dObject[E_2D_OBJECT_BACK_GROUND]->Draw();		//�w�i�`��

	HiscoreDraw();	// �n�C�X�R�A�֘A

	switch (m_eNextType)	//�I������Ă�����̂�ύX
	{	//TODO:�A�N�Z�X�E�k���`�F�b�N
	case CScene::E_TYPE_STAGE1:	//�X�e�[�W1
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->Draw();	//�X�e�[�W2�̎�z���`��
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_REMINE)->Draw();	//�X�e�[�W2�̎�z���`��
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->Draw();	//�X�e�[�W3�̎�z���`��
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_REMINE)->Draw();	//�X�e�[�W3�̎�z���`��
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->Draw();	//�X�e�[�W1�̎�z���`��
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_REMINE)->Draw();	//�X�e�[�W1�̎�z���`��
		break;	//���򏈗��I��
	case CScene::E_TYPE_STAGE2:	//�X�e�[�W2
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->Draw();	//�X�e�[�W1�̎�z���`��
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_REMINE)->Draw();	//�X�e�[�W1�̎�z���`��
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->Draw();	//�X�e�[�W3�̎�z���`��
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_REMINE)->Draw();	//�X�e�[�W3�̎�z���`��
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->Draw();	//�X�e�[�W2�̎�z���`��
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_REMINE)->Draw();	//�X�e�[�W2�̎�z���`��
		break;	//���򏈗��I��
	case CScene::E_TYPE_STAGE3:	//�X�e�[�W3
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->Draw();	//�X�e�[�W1�̎�z���`��
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_REMINE)->Draw();	//�X�e�[�W1�̎�z���`��
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->Draw();	//�X�e�[�W2�̎�z���`��
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_REMINE)->Draw();	//�X�e�[�W2�̎�z���`��
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->Draw();	//�X�e�[�W3�̎�z���`��
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_REMINE)->Draw();	//�X�e�[�W3�̎�z���`��
		break;	//���򏈗��I��
	}
	m_p2dObject[E_2D_OBJECT_BACK_SCENE_NAME]->Draw();	//�V�[�����`��

	// �u�^�C�g���֖߂�v�֘A
	m_p2dObject[E_2D_OBJECT_TO_TITLE_TEXT]->Draw();		// �^�C�g���փe�L�X�g

	m_p2dObject[E_2D_OBJECT_TO_TITLE_BUTTON]->SetAlpha(fabs(cosf(m_nButtonAlphaCnt * 0.03f)));

	m_p2dObject[E_2D_OBJECT_TO_TITLE_BUTTON]->Draw();	// A�{�^���e�L�X�g
}
/* ========================================
	�X�e�[�W��I������֐�
	----------------------------------------
	���e�F�X�e�[�W��I������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
	======================================== */
void CSelectStage::Select()
{
	// �Q�[���R���g���[���[
	if (GetUseVController())
	{
		TPos3d<float> fMoveInput;	// �X�e�B�b�N�̓��͒l������ϐ�
		fMoveInput.x = IsStickLeft().x;// �R���g���[���[�̍��X�e�B�b�N�̌X�����擾

		// ���X�e�B�b�N��|���Ă���
		if (!m_bStickFlg)
		{
			// �X�e�B�b�N��
			if (fMoveInput.x < 0.0f)
			{
				if (m_eNextType != CScene::E_TYPE_STAGE1)	//���̍Œ�l�łȂ��Ƃ�
				{	//TODO:�A�N�Z�X�E�k���`�F�b�N
					//TODO:�i�����炷
					switch (m_eNextType)	//�V�����I�����ꂽ���̂�ύX
					{
						case CScene::E_TYPE_STAGE1:	//�X�e�[�W1
							m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_1_LEAVE));	//�X�e�[�W1�̎�z��
							m_p2dObject.at(E_2D_OBJECT_STAGE_1_REMINE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_1_REMINE));	//�X�e�[�W1�̎�z��
							break;	//���򏈗��I��
						case CScene::E_TYPE_STAGE2:	//�X�e�[�W1
							m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_2_LEAVE));	//�X�e�[�W2�̎�z��
							m_p2dObject.at(E_2D_OBJECT_STAGE_2_REMINE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_2_REMINE));	//�X�e�[�W2�̎�z��
							break;	//���򏈗��I��
						case CScene::E_TYPE_STAGE3:	//�X�e�[�W1
							m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_3_LEAVE));	//�X�e�[�W3�̎�z��
							m_p2dObject.at(E_2D_OBJECT_STAGE_3_REMINE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_3_REMINE));	//�X�e�[�W3�̎�z��
							break;	//���򏈗��I��
					}
					m_eNextType = static_cast<CScene::E_TYPE>(m_eNextType - 1);	//���̃V�[���ԍ���I��

				//===== SE�̍Đ� =======
					PlaySE(SE_CHOOSE);
				}

			}
			// �X�e�B�b�N�E
			else if ( 0.0f < fMoveInput.x )
			{
				if (m_eNextType != CScene::E_TYPE_STAGE3)	//���̍ő�l�łȂ��Ƃ�
				{	//TODO:�A�N�Z�X�E�k���`�F�b�N
					//TODO:�i�����炷
					switch (m_eNextType)	//�V�����I�����ꂽ���̂�ύX
					{
					case CScene::E_TYPE_STAGE1:	//�X�e�[�W1
						m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_1_LEAVE));	//�X�e�[�W1�̎�z��
						m_p2dObject.at(E_2D_OBJECT_STAGE_1_REMINE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_1_REMINE));	//�X�e�[�W1�̎�z��
						break;	//���򏈗��I��
					case CScene::E_TYPE_STAGE2:	//�X�e�[�W1
						m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_2_LEAVE));	//�X�e�[�W2�̎�z��
						m_p2dObject.at(E_2D_OBJECT_STAGE_2_REMINE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_2_REMINE));	//�X�e�[�W2�̎�z��
						break;	//���򏈗��I��
					case CScene::E_TYPE_STAGE3:	//�X�e�[�W1
						m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_3_LEAVE));	//�X�e�[�W3�̎�z��
						m_p2dObject.at(E_2D_OBJECT_STAGE_3_REMINE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_3_REMINE));	//�X�e�[�W3�̎�z��
						break;	//���򏈗��I��
					}
					m_eNextType = static_cast<CScene::E_TYPE>(m_eNextType + 1);	//���̃V�[���ԍ���I��

				//===== SE�̍Đ� =======
					PlaySE(SE_CHOOSE);
				}

			}
		}
		// ���X�e�B�b�N���j���[�g����
		else
		{
			if (fabs(fMoveInput.x) <= 0.5f )
			{
				m_bStickFlg = false;
			}
		}
	}
	else
	{
		//�L�[�{�[�h����
		if (IsKeyTrigger('A'))
		{
			if (m_eNextType != CScene::E_TYPE_STAGE1)	//���̍Œ�l�łȂ��Ƃ�
			{	//TODO:�A�N�Z�X�E�k���`�F�b�N
				//TODO:�i�����炷
				switch (m_eNextType)	//�V�����I�����ꂽ���̂�ύX
				{
				case CScene::E_TYPE_STAGE1:	//�X�e�[�W1
					m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_1_LEAVE));	//�X�e�[�W1�̎�z��
					m_p2dObject.at(E_2D_OBJECT_STAGE_1_REMINE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_1_REMINE));	//�X�e�[�W1�̎�z��
					break;	//���򏈗��I��
				case CScene::E_TYPE_STAGE2:	//�X�e�[�W1
					m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_2_LEAVE));	//�X�e�[�W2�̎�z��
					m_p2dObject.at(E_2D_OBJECT_STAGE_2_REMINE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_2_REMINE));	//�X�e�[�W2�̎�z��
					break;	//���򏈗��I��
				case CScene::E_TYPE_STAGE3:	//�X�e�[�W1
					m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_3_LEAVE));	//�X�e�[�W3�̎�z��
					m_p2dObject.at(E_2D_OBJECT_STAGE_3_REMINE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_3_REMINE));	//�X�e�[�W3�̎�z��
					break;	//���򏈗��I��
				}
				m_eNextType = static_cast<CScene::E_TYPE>(m_eNextType - 1);	//���̃V�[���ԍ���I��
			}
			m_bStickFlg = true;	//�X�e�B�b�N�X�|��

				//===== SE�̍Đ� =======
			PlaySE(SE_CHOOSE);
		}
		if (IsKeyTrigger('D'))
		{
			if (m_eNextType != CScene::E_TYPE_STAGE3)	//���̍ő�l�łȂ��Ƃ�
			{	//TODO:�A�N�Z�X�E�k���`�F�b�N
				//TODO:�i�����炷
				switch (m_eNextType)	//�V�����I�����ꂽ���̂�ύX
				{
				case CScene::E_TYPE_STAGE1:	//�X�e�[�W1
					m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_1_LEAVE));	//�X�e�[�W1�̎�z��
					m_p2dObject.at(E_2D_OBJECT_STAGE_1_REMINE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_1_REMINE));	//�X�e�[�W1�̎�z��
					break;	//���򏈗��I��
				case CScene::E_TYPE_STAGE2:	//�X�e�[�W1
					m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_2_LEAVE));	//�X�e�[�W2�̎�z��
					m_p2dObject.at(E_2D_OBJECT_STAGE_2_REMINE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_2_REMINE));	//�X�e�[�W2�̎�z��
					break;	//���򏈗��I��
				case CScene::E_TYPE_STAGE3:	//�X�e�[�W1
					m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_3_LEAVE));	//�X�e�[�W3�̎�z��
					m_p2dObject.at(E_2D_OBJECT_STAGE_3_REMINE)->SetSize(INIT_MAP_SIZE.at(E_2D_OBJECT_STAGE_3_REMINE));	//�X�e�[�W3�̎�z��
					break;	//���򏈗��I��
				}
				m_eNextType = static_cast<CScene::E_TYPE>(m_eNextType + 1);	//���̃V�[���ԍ���I��
			}
			m_bStickFlg = true;	//�X�e�B�b�N�X�|��

			//===== SE�̍Đ� =======
			PlaySE(SE_CHOOSE);
		}
	}

	if (IsKeyTrigger(VK_SPACE) || IsKeyTriggerController(BUTTON_B) && m_pFrameCntFall)
	{
		m_pFrameCntFall = new CFrameCnt(FALL_TIME_ARR_LET);	//�J�E���^�쐬
		//===== SE�̍Đ� =======
		PlaySE(SE_DECISION);
	}

	if (IsKeyTrigger('B') || IsKeyTriggerController(BUTTON_A) && m_pFrameCntFall)
	{
		m_eNextType = E_TYPE::E_TYPE_TITLE;
		m_bFinish = true;
	}
}

/* ========================================
	��ރQ�b�^
	----------------------------------------
	���e�F���g���X�e�[�W�Z���N�g�ł��邱�Ƃ�����
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F���g�̎��
=========================================== */
CSelectStage::E_TYPE CSelectStage::GetType() const
{
	// =============== �� ===================
	return CSelectStage::E_TYPE_SELECT_STAGE;	//���g�̎��
}

/* ========================================
	���V�[���Q�b�^
	----------------------------------------
	���e�F�J�ڂ������V�[��������������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�J�ڐ�V�[���̎��
=========================================== */
CSelectStage::E_TYPE CSelectStage::GetNext() const
{
	// =============== �� ===================
	return m_eNextType;	//�J�ڐ�V�[���̎��
}

/* ========================================
   �Z���N�g�X�e�[�W�pSE�ǂݍ��݊֐�
   ----------------------------------------
   ���e�F�Z���N�g�X�e�[�W�p��SE�̃t�@�C����ǂݍ���
   ----------------------------------------
   �����F����
   ----------------------------------------
   �ߒl�F����
======================================== */
void CSelectStage::LoadSound()
{
	//SE�̓ǂݍ���
	for (int i = 0; i < SE_MAX; i++)
	{
		m_pSE[i] = CSound::LoadSound(m_sSEFile[i].c_str());
		if (!m_pSE[i])
		{
			MessageBox(NULL, m_sSEFile[i].c_str(), "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
		}
	}
}

/* ========================================
	SE�̍Đ��֐�
	----------------------------------------
	���e�FSE�̍Đ�
	----------------------------------------
	����1�FSE�̎��(enum)
	����2�F����
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CSelectStage::PlaySE(SE se, float volume)
{
	m_pSESpeaker[se] = CSound::PlaySound(m_pSE[se]);	//SE�Đ�
	m_pSESpeaker[se]->SetVolume(volume);				//���ʂ̐ݒ�
}

void CSelectStage::HiscoreParamSet()
{
}

void CSelectStage::HiscoreDraw()
{
	for (int i = 0; i < 3; i++)
	{
		m_p2dObject.at(E_2D_OBJECT_HISCORE_BG)->SetPos({
		INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_BG).x + HISCORE_BASE_POS[i].x,
		INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_BG).y + HISCORE_BASE_POS[i].y,
		INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_BG).z ,
			});
		m_p2dObject.at(E_2D_OBJECT_HISCORE_TEXT)->SetPos({
			INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_TEXT).x + HISCORE_BASE_POS[i].x,
			INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_TEXT).y + HISCORE_BASE_POS[i].y,
			INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_TEXT).z ,
			});

		m_p2dObject.at(E_2D_OBJECT_HISCORE_BG)->Draw();
		m_p2dObject.at(E_2D_OBJECT_HISCORE_TEXT)->Draw();

		TTriType<float> NumBasePos = {
			INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_NUM).x + HISCORE_BASE_POS[i].x,
			INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_NUM).y + HISCORE_BASE_POS[i].y,
			INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_NUM).z ,
		};

		DispNum(m_Data.nHighScore[i], 5, NumBasePos);
	}

	
}



/* ========================================
	�����`��֐�
	----------------------------------------
	���e�F������`�悷��
	----------------------------------------
	����1�F�`�悷�鐔��
	����2�F����
	����3�F�ʒu
	����4�F�傫��
	����5�F�����Ԃ̑傫��
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CSelectStage::DispNum(int dispNum, int nDigits, TTriType<float> pos)
{

	std::vector<int> digitArray;
	DirectX::XMFLOAT4X4 mat;
	int Num = dispNum;


	NumStorage(&digitArray, dispNum, nDigits);

	for (int i = 0; i < digitArray.size(); i++)
	{
		float width = (INIT_MAP_SIZE.at(E_2D_OBJECT_HISCORE_NUM).x * 0.8f) * i;
		
		int x = digitArray[i] % HISCORE_NUM_SPLIT.x;	//�������O��W���܂�
		int y = digitArray[i] / HISCORE_NUM_SPLIT.x;	//�z��ɓ����Ă鐔���̏ꏊ���v�Z���Ă܂�

		m_p2dObject.at(E_2D_OBJECT_HISCORE_NUM)->SetUvScale(HISCORE_NUM_UVSCALE);
		m_p2dObject.at(E_2D_OBJECT_HISCORE_NUM)->SetUvOffset({ HISCORE_NUM_UVSCALE.x * x, HISCORE_NUM_UVSCALE.y * y });

		m_p2dObject.at(E_2D_OBJECT_HISCORE_NUM)->SetPos({ pos.x - width , pos.y, pos.z });
		m_p2dObject.at(E_2D_OBJECT_HISCORE_NUM)->Draw();
	}
}


/* ========================================
	�������i�[����
	----------------------------------------
	���e�F�z��ɐ����������ƂɊi�[����
	----------------------------------------
	����1�F���i�[�z��
	����1�F�i�[���鐔��
	����1�F����
	----------------------------------------
	�ߒl�F����
=========================================== */
void CSelectStage::NumStorage(std::vector<int>* digitArray, int nNumber, int nDigits)
{
	// �������z������Z�b�g
	(*digitArray).clear();

	// �\�����鐔����0�ȏ�̏ꍇ
	if (0 < nNumber)
	{
		// nNumber��S�Ċi�[����܂ŌJ��Ԃ�
		while (0 != nNumber)
		{
			(*digitArray).push_back(nNumber % 10);	// nNumber�̉�1�����i�[����
			nNumber /= 10;							// nNumber��1���X���C�h������

		}

	}

	// �w�茅���܂�0���߂���
	while ((*digitArray).size() < nDigits)
	{
		(*digitArray).push_back(0);
	}
}