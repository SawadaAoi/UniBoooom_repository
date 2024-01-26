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

========================================== */

// =============== �C���N���[�h ===================
#include "SelectStage.h"	//���g�̃w�b�_
#include "Input.h"
#include "GameParameter.h"
#define _USE_MATH_DEFINES	//math.h�̒�`�g�p
#include <math.h>			//M_PI�g�p
#include <algorithm>		//clamp�g�p
#include "Delete.h"			//�폜�}�N��

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
	:m_bStickFlg(false)					//�X�e�B�b�N�̌X�|�L��
	,m_pFrameCnt(nullptr)				//�t���[���J�E���^
	,m_bCntUpDwn(false)					//�J�E���g�A�b�v�E�_�E��
	,m_eNextType(CScene::E_TYPE_STAGE1)	//�����̎��̃V�[��
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
	m_pFrameCnt = new CFrameCnt(CHANGE_SCALE_HALF_TIME, m_bCntUpDwn);	//�t���[��������

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
	Select();

	// =============== �ϐ��錾 =====================
	float fSize = INIT_SIZE_ARR_LET.x;	//�傫��

	// =============== �g�k�X�V =====================
	if (m_pFrameCnt)	//�k���`�F�b�N
	{
		m_pFrameCnt->Count();	//�J�E���g�i�s
		fSize = -(cosf(static_cast<float>(M_PI) * m_pFrameCnt->GetRate()) - 1.0f) / 2.0f * (MAX_SIZE_ARR_LET - MIN_SIZE_ARR_LET) + MIN_SIZE_ARR_LET;	//�C�[�W���O���g�����傫���ύX
		if (m_pFrameCnt->IsFin())	//�J�E���g����
		{
			m_bCntUpDwn ^= 1;													//�J�E���g�A�b�v�_�E���t�]
			SAFE_DELETE(m_pFrameCnt);											//�J�E���^�폜
			m_pFrameCnt = new CFrameCnt(CHANGE_SCALE_HALF_TIME, m_bCntUpDwn);	//�J�E���g�A�b�v�E�_�E��
		}
	}

	// =============== �g�k�ύX =====================
	switch (m_eNextType)	//�I������Ă�����̂�ύX
	{	//TODO:�A�N�Z�X�E�k���`�F�b�N
	case CScene::E_TYPE_STAGE1:	//�X�e�[�W1
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->SetSize({ fSize * ASPECT_RATE_ARR_LET, fSize, 1.0f });	//�X�e�[�W1�̎�z��
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_REMINE)->SetSize({ fSize * ASPECT_RATE_ARR_LET, fSize, 1.0f });	//�X�e�[�W1�̎�z��
		break;	//���򏈗��I��
	case CScene::E_TYPE_STAGE2:	//�X�e�[�W2
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->SetSize({ fSize * ASPECT_RATE_ARR_LET, fSize, 1.0f });	//�X�e�[�W2�̎�z��
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_REMINE)->SetSize({ fSize * ASPECT_RATE_ARR_LET, fSize, 1.0f });	//�X�e�[�W2�̎�z��
		break;	//���򏈗��I��
	case CScene::E_TYPE_STAGE3:	//�X�e�[�W3
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->SetSize({ fSize * ASPECT_RATE_ARR_LET, fSize, 1.0f });	//�X�e�[�W3�̎�z��
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_REMINE)->SetSize({ fSize * ASPECT_RATE_ARR_LET, fSize, 1.0f });	//�X�e�[�W3�̎�z��
		break;	//���򏈗��I��
	}
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
	//!memo(����������ā[)�Fconst���ז��ɂȂ�����O���Ă�(.h�̕���)
void CSelectStage::Draw() //const
{
	// =============== �`�� =====================	//TODO:�A�N�Z�X�E�k���`�F�b�N
	m_p2dObject[E_2D_OBJECT_BACK_GROUND]->Draw();		//�w�i�`��
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

	//for (auto Iterator = m_p2dObject.begin(); Iterator != m_p2dObject.end(); Iterator++)
	//{
	//	if (Iterator->second)	//�k���`�F�b�N
	//	{
	//		Iterator->second->Draw();	//�`��	//���Ԃ̓s���ŕs�̗p
	//	}
	//}
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
				}
				m_bStickFlg = true;	//�X�e�B�b�N�X�|��
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
				}
				m_bStickFlg = true;	//�X�e�B�b�N�X�|��
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
		}
	}

	if (IsKeyTrigger(VK_SPACE) || IsKeyTriggerController(BUTTON_B))
	{
		m_bFinish = true;	// �^�C�g���V�[���I���t���OON
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