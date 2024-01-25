/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X�e�[�W1��`
	---------------------------------------
	Stage1.h
	---------------------------------------
	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/11/05 ���� takagi
	�E2023/11/07 �R�����g�C�� takagi
	�E2023/11/16 Prot.h��Stage1.h takagi
	�E2023/12/14 BGM�̊Ǘ���SceneManager�Ɉړ� yamashita
	�E2024/01/15 GameFinish()�֐��̈����C���ERecordData()�֐��ǉ� takagi
	�E2024/01/20 ���t�@�N�^�����O takagi

========================================== */

#ifndef __STAGE1_H__	//Stage1.h�C���N���[�h�K�[�h
#define __STAGE1_H__

// =============== �C���N���[�h ===================
#include "Stage.h"	//�e�̃w�b�_

// =============== �N���X��` =====================
class CStage1 :public CStage	//�X�e�[�W
{
//protected:
//	enum E_3D	//�X�V��
//	{
//		E_3D_FLOOR = CStage::E_3D_MAX,	//��
//		E_3D_MAX,						//�v�f��
//	};	//3D�̃I�u�W�F�N�g
public:
	// ===�v���g�^�C�v�錾===
	CStage1();							//�R���X�g���N�^
	~CStage1();							//�f�X�g���N�^
	void Update();						//�X�V
	void Draw();						//�`��
	E_TYPE GetNext() const override;	//���̃V�[���Q�b�^
private:
	// ===�v���g�^�C�v�錾===
	virtual void RecordData();			//�f�[�^�L�^
};	//�X�e�[�W1

#endif	//!__STAGE1_H__