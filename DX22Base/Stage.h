/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X�e�[�W�p���ۃN���X��`
	---------------------------------------
	Stage.h

	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/11/16 ���� takagi

	!memo(����������ā[)�FCollision�֌W�̃R�����g��낵��
========================================== */

#ifndef __STAGE_H__	//Stage.h�C���N���[�h�K�[�h
#define __STAGE_H__

// =============== �C���N���[�h ===================
#include "Scene.h"			//�e�̃w�b�_

// =============== �N���X��` =====================
class CStage :public CScene	//�V�[��
{
public:
	// =============== �v���g�^�C�v�錾 ===============
	//CStage();							//�R���X�g���N�^
	//virtual ~CStage();					//�f�X�g���N�^
	//virtual void Update();				//�X�V
	//virtual void Draw() const;			//�`��	
	//virtual E_TYPE GetType() const = 0;	//���g�̎�ރQ�b�^
private:
	void Collision();
	void PlayerSlimeCollision();
	void HammerSlimeCollision();
	void SlimeSlimeCollision();
	void ExplosionSlimeCollision();
	void SlimeSlimeNormalMoveCollision();
};	//�X�e�[�W

#endif	//!__STAGE_H__