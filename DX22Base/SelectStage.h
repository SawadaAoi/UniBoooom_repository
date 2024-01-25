/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X�e�[�W�Z���N�g��`
	---------------------------------------
	SelectStage.h

	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/11/16 ���� takagi
	�E2023/12/12 �X�e�[�W�Z���N�g�p�̍\���́A�z��A�֐��ǉ� yamamoto
	�E2024/01/26 �g�k���� takagi

========================================== */

#ifndef __SELECT_STAGE_H__	//SelectStage.h�C���N���[�h�K�[�h
#define __SELECT_STAGE_H__

// =============== �C���N���[�h ===================
#include "Scene.h"	//�e�̃w�b�_
#include "2dPolygon.h"
#include "FrameCnt.h"	//�������o�p
// =============== �萔��` =======================
const int SUTAGE_NUM = 3;						// �X�e�[�W�̐�

// =============== �N���X��` =====================
class CSelectStage :public CScene	//�V�[��
{
	// ===�萔��`===========
	const float MIN_SIZE_ARR_LET = 450.0f;	//��z���ŏ��T�C�Y
	const float MAX_SIZE_ARR_LET = 550.0f;	//��z���ő�T�C�Y
	const int CHANGE_SCALE_HALF_TIME = 120;	//�g�k����������ɂ����鎞��
public:
	// ===�\���̒�`=========
	typedef struct
	{
		E_TYPE Type;
		Texture* m_pTexture;
	}StageSelect;

public:
	// =============== �v���g�^�C�v�錾 ===============
	CSelectStage();						//�R���X�g���N�^
	~CSelectStage();					//�f�X�g���N�^
	void Update();						//�X�V
	void Draw();// const;					//�`��	
	void Select();
	E_TYPE GetType() const override;	//���g�̎�ރQ�b�^
	E_TYPE GetNext() const override;	//���̃V�[���Q�b�^
protected:
	StageSelect mStageNum[SUTAGE_NUM];
private:
	int m_nSelectNum;			// �I�𒆂̃X�e�[�W�ԍ�
	C2dPolygon* m_2dObj[5];
	StageSelect EscapeStageNum;
	Texture* m_pStageSelectBG;
	Texture* m_pStageSelectUI;
	bool m_bStickFlg;			// �R���g���[���[�̃X�e�B�b�N���������Ă��邩
	CFrameCnt* m_pFrameCnt;		//�C�[�W���O�p�^�C�}�[
	bool m_bCntUpDwn;			//�J�E���g�A�b�v�E�_�E��

};	//�X�e�[�W�Z���N�g

#endif	//!__SELECT_STAGE_H__