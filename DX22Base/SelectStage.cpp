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
	{ 220.0f, 150.0f, 0.0f},		// �X�e�[�W1
	{ 600.0f, 550.0f, 0.0f},		// �X�e�[�W2
	{ 1000.0f, 150.0f, 0.0f},	// �X�e�[�W3
};

const float FLASH_BUTTON_TEXT_ADJUST = 0.02f;	//�u�߂�v�u����v�e�L�X�g�̓_�ŊԊu����

// ��z���̗h��֌W
const float STAGE_TEX_ANIM_ANGLE = 10.0f;			// �X�e�[�W��z���摜�̗h��̊p�x���E�l
const int	CHANGE_ROTATE_HALF_TIME = 1.5f * 60;	// �h�ꔼ��������ɂ����鎞��

// �X�e�[�W�Z���N�g�����֌W
const int SELECT_MOVE_RIGHT = 1;	// �E�ɑI���ړ�
const int SELECT_MOVE_LEFT = -1;	// ���ɑI���ړ�
const int SELECT_MOVE_NOT = 0;		// ���͂��ĂȂ�

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
	: m_fChangeRotate(0.0f)					// �X�e�[�W��z���摜�̌X���ϓ��l
	, m_bStickFlg(true)						// �X�e�B�b�N�̌X�|�L��
	, m_pFrameCntFall(nullptr)				// ��z�������p�t���[���J�E���^
	, m_pFrameCntRotate(nullptr)				// �g�k�p�t���[���J�E���^
	, m_bCntUpDwn(false)					// �J�E���g�A�b�v�E�_�E��
	, m_eNextType(CScene::E_TYPE_STAGE1)	// �����̎��̃V�[��
	, m_nButtonAlphaCnt(0)					// �g�k�p�t���[���J�E���^
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
	m_pFrameCntRotate = new CFrameCnt(CHANGE_ROTATE_HALF_TIME, m_bCntUpDwn);	//�t���[��������

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

	// ��z���摜�̒��S�l����ɂ��炷(�h��̃A�j���[�V�����̈�)
	m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->SetOffSet(STAGE_TEXTURE_OFFSET);
	m_p2dObject.at(E_2D_OBJECT_STAGE_1_REMINE)->SetOffSet(STAGE_TEXTURE_OFFSET);
	m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->SetOffSet(STAGE_TEXTURE_OFFSET);
	m_p2dObject.at(E_2D_OBJECT_STAGE_2_REMINE)->SetOffSet(STAGE_TEXTURE_OFFSET);
	m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->SetOffSet(STAGE_TEXTURE_OFFSET);
	m_p2dObject.at(E_2D_OBJECT_STAGE_3_REMINE)->SetOffSet(STAGE_TEXTURE_OFFSET);

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
	SAFE_DELETE(m_pFrameCntRotate);			//�J�E���^�폜
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

	// ��z���摜�����������J�n���Ă���ꍇ(�X�e�[�W����ς�) 
	if (m_pFrameCntFall)
	{
		FallAnimationStageTexture();	// ��z���摜��j��A�j���[�V����
		
	}
	else
	{	
		StageSelect();								// �X�e�[�W�I������
		SelectStageTextureAnimation(m_eNextType);	// �I����z���A�j���[�V����
	}

	m_nButtonAlphaCnt++;	//�u�߂�v�u����v�e�L�X�g�_��

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
void CSelectStage::Draw()
{
	// =============== �`�� =====================	//TODO:�A�N�Z�X�E�k���`�F�b�N
	m_p2dObject[E_2D_OBJECT_BACK_GROUND]->Draw();		//�w�i�`��
	m_p2dObject[E_2D_OBJECT_BACK_SCENE_NAME]->Draw();	//�V�[����(��ʏ㕔�̘g)�`��

	DrawHiscore();		// �n�C�X�R�A�֘A�`��
	DrawStageTexture();	// �X�e�[�W��z���摜�`��


	m_p2dObject[E_2D_OBJECT_BUTTON_EXPLANATION]->SetAlpha(
		fabs(cosf(m_nButtonAlphaCnt * FLASH_BUTTON_TEXT_ADJUST)));	// �u�߂�v�u����v�e�L�X�g�_��
	m_p2dObject[E_2D_OBJECT_BUTTON_EXPLANATION]->Draw();			// �u�߂�v�u����v�e�L�X�g�`��
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
void CSelectStage::StageSelect()
{
	// �Q�[���R���g���[���[�g�p��
	if (GetUseVController())
	{
		TPos3d<float> fMoveInput;	// �X�e�B�b�N�̓��͒l������ϐ�
		fMoveInput.x = IsStickLeft().x;// �R���g���[���[�̍��X�e�B�b�N�̌X�����擾

		if (m_bStickFlg)
		{
			// �X�e�B�b�N�E
			if ( 0.0f < fMoveInput.x )
			{
				SelectStageChange(SELECT_MOVE_RIGHT);	// �J�ڃX�e�[�W�l��ύX
				m_bStickFlg = false;					// �X�e�B�b�N�X�|�t���O�I��

			}
			// �X�e�B�b�N��
			else if (fMoveInput.x < 0.0f)
			{
				SelectStageChange(SELECT_MOVE_LEFT);	// �J�ڃX�e�[�W�l��ύX
				m_bStickFlg = false;					// �X�e�B�b�N�X�|�t���O�I��

			}
		}
		else
		{
			// �X�e�B�b�N�̌X�������l�ȉ��̏ꍇ
			if (fabs(fMoveInput.x) <= 0.5f )	
			{
				m_bStickFlg = true;	// �X�e�B�b�N���j���[�g�����ɖ߂�����ړ��\�ɂ���
			}
		}
	}
	// �L�[�{�[�h�g�p��
	else
	{
		// �E
		if (IsKeyTrigger('D'))	SelectStageChange(SELECT_MOVE_RIGHT);	// �J�ڃX�e�[�W�l��ύX
		// ��
		if (IsKeyTrigger('A'))	SelectStageChange(SELECT_MOVE_LEFT);	// �J�ڃX�e�[�W�l��ύX
	}

	// ����
	if ( (IsKeyTrigger(VK_SPACE) || IsKeyTrigger(VK_RETURN) || IsKeyTriggerController(BUTTON_B)) && !m_pFrameCntFall)
	{
		m_pFrameCntFall = new CFrameCnt(FALL_TIME_ARR_LET);	//�J�E���^�쐬
		PlaySE(SE_DECISION);	// SE�̍Đ� 

	}

	// �^�C�g����ʂɖ߂�
	if ((IsKeyTrigger('B') || IsKeyTriggerController(BUTTON_A) )&& !m_pFrameCntFall)
	{
		m_eNextType = E_TYPE::E_TYPE_TITLE;
		m_bFinish = true;
	}
}



/* ========================================
	�I���X�e�[�W�l�ύX�֐�
	----------------------------------------
	���e�F�v���C����X�e�[�W��ύX����
	----------------------------------------
	����1�F�ύX�l( �萔�� SELECT_MOVE_NOT / SELECT_MOVE_RIGHT / SELECT_MOVE_LEFT )
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CSelectStage::SelectStageChange(int select)
{
	// �h��̉��Z�l�����Z�b�g����
	SAFE_DELETE(m_pFrameCntRotate);												// �J�E���^�폜
	m_pFrameCntRotate = new CFrameCnt(CHANGE_ROTATE_HALF_TIME, m_bCntUpDwn);	// �J�E���g�A�b�v�E�_�E��

	ResetStageTexture(m_eNextType);	// �I�����Ă����X�e�[�W�̉摜�`��������Z�b�g
	PlaySE(SE_CHOOSE);				// SE�̍Đ�

	// �J�[�\�����E�[�ŉE�Ɉړ�����ꍇ
	if (select == SELECT_MOVE_RIGHT && m_eNextType == CScene::E_TYPE_STAGE3)
	{
		m_eNextType = E_TYPE_STAGE1;	// ���[�Ƀ��[�v�ړ�
		return;
	}
	// �J�[�\�������[�ō��Ɉړ�����ꍇ
	if (select == SELECT_MOVE_LEFT && m_eNextType == CScene::E_TYPE_STAGE1)
	{
		m_eNextType = E_TYPE_STAGE3;	// �E�[�Ƀ��[�v�ړ�
		return;
	}

	// �I���X�e�[�W��ύX
	m_eNextType = static_cast<CScene::E_TYPE>(m_eNextType + select);	

}

/* ========================================
	�I���X�e�[�W��z���摜�A�j���[�V�����֐�
	----------------------------------------
	���e�F�I�������X�e�[�W�̎�z���摜���A�j���[�V���������鏈��
	----------------------------------------
	����1�F�X�e�[�W�ԍ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CSelectStage::SelectStageTextureAnimation(CScene::E_TYPE stage)
{

	// �h��̃A�j���[�V�����Ɏg�p����l���X�V
	if (m_pFrameCntRotate)	//�k���`�F�b�N
	{
		m_pFrameCntRotate->Count();	//�J�E���g�i�s

		m_fChangeRotate =	// STAGE_TEX_ANIM_ANGLE �` -STAGE_TEX_ANIM_ANGLE�̊p�x���Z�b�g
			(m_pFrameCntRotate->GetRate() * STAGE_TEX_ANIM_ANGLE * 2) - STAGE_TEX_ANIM_ANGLE;

		if (m_pFrameCntRotate->IsFin())	//�J�E���g����
		{
			m_bCntUpDwn ^= 1;															// �J�E���g�A�b�v�_�E���t�]
			SAFE_DELETE(m_pFrameCntRotate);												// �J�E���^�폜
			m_pFrameCntRotate = new CFrameCnt(CHANGE_ROTATE_HALF_TIME, m_bCntUpDwn);	// �J�E���g�A�b�v�E�_�E��
		}
	}

	switch (stage)	// �I�����Ă���X�e�[�W��z���摜��h�炷
	{	
	case CScene::E_TYPE_STAGE1:	//�X�e�[�W1

		m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->SetRotate({ 0.0f, 0.0f, DirectX::XMConvertToRadians(m_fChangeRotate) });
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_REMINE)->SetRotate({ 0.0f, 0.0f, DirectX::XMConvertToRadians(m_fChangeRotate) });
		break;

	case CScene::E_TYPE_STAGE2:	//�X�e�[�W2

		m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->SetRotate({ 0.0f, 0.0f, DirectX::XMConvertToRadians(m_fChangeRotate) });
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_REMINE)->SetRotate({ 0.0f, 0.0f, DirectX::XMConvertToRadians(m_fChangeRotate) });
		break;

	case CScene::E_TYPE_STAGE3:	//�X�e�[�W3

		m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->SetRotate({ 0.0f, 0.0f, DirectX::XMConvertToRadians(m_fChangeRotate) });
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_REMINE)->SetRotate({ 0.0f, 0.0f, DirectX::XMConvertToRadians(m_fChangeRotate) });
		break;			
	}
}

/* ========================================
	�X�e�[�W�摜�T�C�Y�����A�j���[�V�����`��֐�
	----------------------------------------
	���e�F�X�e�[�W�̉摜�̕`����������l�ɖ߂�
	----------------------------------------
	����1�F�X�e�[�W�ԍ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CSelectStage::FallAnimationStageTexture()
{

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
		fPos.y = fBasePos.y * m_pFrameCntFall->GetRate();	// �������W����ʊO�܂ł̋�������
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

/* ========================================
	�X�e�[�W�摜��񃊃Z�b�g�`��֐�
	----------------------------------------
	���e�F�X�e�[�W�̉摜�̕`����������l�ɖ߂�
	----------------------------------------
	����1�F�X�e�[�W�ԍ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CSelectStage::ResetStageTexture(CScene::E_TYPE stage)
{
	switch (stage)	// �X���������l�ɖ߂�
	{
	case CScene::E_TYPE_STAGE1:
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->SetRotate(INIT_MAP_ROTATE.at(E_2D_OBJECT_STAGE_1_LEAVE));	
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_REMINE)->SetRotate(INIT_MAP_ROTATE.at(E_2D_OBJECT_STAGE_1_REMINE));	
		break;
	case CScene::E_TYPE_STAGE2:

		m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->SetRotate(INIT_MAP_ROTATE.at(E_2D_OBJECT_STAGE_2_LEAVE));
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_REMINE)->SetRotate(INIT_MAP_ROTATE.at(E_2D_OBJECT_STAGE_2_REMINE));
		break;
	case CScene::E_TYPE_STAGE3:	
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->SetRotate(INIT_MAP_ROTATE.at(E_2D_OBJECT_STAGE_3_LEAVE));
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_REMINE)->SetRotate(INIT_MAP_ROTATE.at(E_2D_OBJECT_STAGE_3_REMINE));
		break;
	}
}

/* ========================================
	�X�e�[�W��z���`��֐�
	----------------------------------------
	���e�F�X�e�[�W��z����`�悷��
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CSelectStage::DrawStageTexture()
{
	// �I�����Ă���X�e�[�W�̎�z������Ԏ�O�ɕ`�悷��
	switch (m_eNextType)
	{	//TODO:�A�N�Z�X�E�k���`�F�b�N
	case CScene::E_TYPE_STAGE1:	//�X�e�[�W1
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->Draw();	//�X�e�[�W2�̎�z���`��
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_REMINE)->Draw();	//�X�e�[�W2�̎�z���`��
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->Draw();	//�X�e�[�W3�̎�z���`��
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_REMINE)->Draw();	//�X�e�[�W3�̎�z���`��
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->Draw();	//�X�e�[�W1�̎�z���`��
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_REMINE)->Draw();	//�X�e�[�W1�̎�z���`��
		break;
	case CScene::E_TYPE_STAGE2:	//�X�e�[�W2
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->Draw();	//�X�e�[�W1�̎�z���`��
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_REMINE)->Draw();	//�X�e�[�W1�̎�z���`��
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->Draw();	//�X�e�[�W3�̎�z���`��
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_REMINE)->Draw();	//�X�e�[�W3�̎�z���`��
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->Draw();	//�X�e�[�W2�̎�z���`��
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_REMINE)->Draw();	//�X�e�[�W2�̎�z���`��
		break;
	case CScene::E_TYPE_STAGE3:	//�X�e�[�W3
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_LEAVE)->Draw();	//�X�e�[�W1�̎�z���`��
		m_p2dObject.at(E_2D_OBJECT_STAGE_1_REMINE)->Draw();	//�X�e�[�W1�̎�z���`��
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_LEAVE)->Draw();	//�X�e�[�W2�̎�z���`��
		m_p2dObject.at(E_2D_OBJECT_STAGE_2_REMINE)->Draw();	//�X�e�[�W2�̎�z���`��
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_LEAVE)->Draw();	//�X�e�[�W3�̎�z���`��
		m_p2dObject.at(E_2D_OBJECT_STAGE_3_REMINE)->Draw();	//�X�e�[�W3�̎�z���`��
		break;
	}
}

/* ========================================
	�n�C�X�R�A�`��֐�
	----------------------------------------
	���e�F�n�C�X�R�A��`�悷��
	----------------------------------------
	����1�F����
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CSelectStage::DrawHiscore()
{
	TTriType<float> NumBasePos;	// �n�C�X�R�A�������W�ϐ�

	for (int i = 0; i < 3; i++)
	{
		// �n�C�X�R�A�w�i���W�Z�b�g
		m_p2dObject.at(E_2D_OBJECT_HISCORE_BG)->SetPos({
			INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_BG).x + HISCORE_BASE_POS[i].x,
			INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_BG).y + HISCORE_BASE_POS[i].y,
			INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_BG).z ,
			});

		// �n�C�X�R�A�e�L�X�g���W�Z�b�g
		m_p2dObject.at(E_2D_OBJECT_HISCORE_TEXT)->SetPos({
			INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_TEXT).x + HISCORE_BASE_POS[i].x,
			INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_TEXT).y + HISCORE_BASE_POS[i].y,
			INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_TEXT).z ,
			});

		// �n�C�X�R�A�������W�ϐ��Z�b�g
		NumBasePos = {
			INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_NUM).x + HISCORE_BASE_POS[i].x,
			INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_NUM).y + HISCORE_BASE_POS[i].y,
			INIT_MAP_POS.at(E_2D_OBJECT_HISCORE_NUM).z ,
		};


		m_p2dObject.at(E_2D_OBJECT_HISCORE_BG)->Draw();		// �n�C�X�R�A�w�i�`��
		m_p2dObject.at(E_2D_OBJECT_HISCORE_TEXT)->Draw();	// �n�C�X�R�A�e�L�X�g�`��
		DispNum(m_Data.nHighScore[i], 5, NumBasePos);		// �n�C�X�R�A�����`��
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

	NumStorage(&digitArray, dispNum, nDigits);	// �z��ɐ���������

	// �������`��
	for (int i = 0; i < digitArray.size(); i++)
	{
		float width = (INIT_MAP_SIZE.at(E_2D_OBJECT_HISCORE_NUM).x * 0.8f) * i;
		
		int x = digitArray[i] % HISCORE_NUM_SPLIT.x;	// �����e�N�X�`���̉������ʒu
		int y = digitArray[i] / HISCORE_NUM_SPLIT.x;	// �����e�N�X�`���̏c�����ʒu

		m_p2dObject.at(E_2D_OBJECT_HISCORE_NUM)->SetUvScale(HISCORE_NUM_UVSCALE);	// �e�N�X�`��UV������
		m_p2dObject.at(E_2D_OBJECT_HISCORE_NUM)->SetUvOffset({						// �e�N�X�`��UV���W
			HISCORE_NUM_UVSCALE.x * x, 
			HISCORE_NUM_UVSCALE.y * y });

		m_p2dObject.at(E_2D_OBJECT_HISCORE_NUM)->SetPos({ pos.x - width , pos.y, pos.z });	// �e�N�X�`�����W
		m_p2dObject.at(E_2D_OBJECT_HISCORE_NUM)->Draw();									// �`��
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