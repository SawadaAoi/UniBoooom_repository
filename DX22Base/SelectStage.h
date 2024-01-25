/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X�e�[�W�Z���N�g��`
	---------------------------------------
	SelectStage.h
	---------------------------------------
	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/11/16 ���� takagi
	�E2023/12/12 �X�e�[�W�Z���N�g�p�̍\���́A�z��A�֐��ǉ� yamamoto
	�E2024/01/20 ���t�@�N�^�����O takagi

========================================== */

#ifndef __SELECT_STAGE_H__	//SelectStage.h�C���N���[�h�K�[�h
#define __SELECT_STAGE_H__

// =============== �C���N���[�h ===================
#include "Scene.h"	//�e�̃w�b�_
#include "2dObject.h"
// =============== �萔��` =======================
const int SUTAGE_NUM = 3;						// �X�e�[�W�̐�

// =============== �N���X��` =====================
class CSelectStage :public CScene	//�V�[��
{
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
	void Update() override;				//�X�V	
	void Select();
	E_TYPE GetNext() const override;	//���̃V�[���Q�b�^
protected:
	StageSelect mStageNum[SUTAGE_NUM];
private:
	int Num;
	C2dObject* m_2dObj[5];
	StageSelect EscapeStageNum;
	Texture* m_pStageSelectBG;
	Texture* m_pStageSelectUI;

};	//�X�e�[�W�Z���N�g

#endif	//!__SELECT_STAGE_H__