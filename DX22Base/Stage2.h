/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X�e�[�W2��`
	---------------------------------------
	Stage2.h

	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/11/16 ���� takagi
	�E2023/12/12 LoadSE���I�[�o�[���C�h yamashita
	�E2023/12/14 BGM�̊Ǘ���SceneManager�Ɉړ� yamashita
	�E2024/01/15 GameFinish()�֐��̈����C���ERecordData()�֐��ǉ� takagi
	�E2024/02/09 GetType()�֐��폜 takagi

========================================== */

#ifndef __STAGE2_H__	//Stage2.h�C���N���[�h�K�[�h
#define __STAGE2_H__

// =============== �C���N���[�h ===================
#include "Stage.h"	//�e�̃w�b�_

// =============== �N���X��` =====================
class CStage2 :public CStage	//�X�e�[�W
{
public:
	// ===�v���g�^�C�v�錾===
	CStage2();							//�R���X�g���N�^
	~CStage2();							//�f�X�g���N�^
	void Update();						//�X�V
	void Draw();						//�`��
	E_TYPE GetNext() const override;	//���̃V�[���Q�b�^
private:
	// ===�v���g�^�C�v�錾===
	virtual void RecordData();			//�f�[�^�L�^
};	//�X�e�[�W2

#endif	//!__STAGE2_H__