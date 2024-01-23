/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   �X�R�A�Ǘ��w�b�_�[
   ---------------------------------------
   ScoreOHManager.h
   ---------------------------------------
   �쐬��	yamamoto

   �ύX����
	�E2023/11/17�@�쐬 yamamoto
	�E2023/11/25�@�g���Ă��Ȃ��֐����폜 yamamoto
	�E2023/12/07 �Q�[���p�����[�^�Ɉˑ����Ă����̂ŏC���E�s�v�ӏ��폜�E�萔��` takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __SCORE_OH_MANAGER_H__	//ScoreOHManager.h�C���N���[�h�K�[�h
#define __SCORE_OH_MANAGER_H__

// =============== �C���N���[�h ===================
#include "ObjectManager.h"	//�e�̃w�b�_
#include "ScoreOverHead.h"
#include "ExplosionManager.h"	//�ő唚������`
#include "SlimeBase.h"

// =============== �萔���` ===================
const float SLIME_SCORE_HEIGHT = 4.0f;	//����������X�R�A�̕\���ʒu

// =============== �N���X��` =====================
class CScoreOHManager :public CObjectManager	//�I�u�W�F�N�g�Ǘ�
{
public:
	// ===�����o�֐��錾===
	CScoreOHManager();		//�R���X�g���N�^
	~CScoreOHManager();		//�f�X�g���N�^
	void Update();		 		//�X�V�֐�
	void Draw();		 		//�`��֐�
	void DisplayOverheadScore(TTriType<float> pos,int score, float height);			// �X�R�A�̐���
	void DisplayOverheadScore(TTriType<float> pos, E_SLIME_LEVEL level);			// �X�R�A�̐���
	void DeleteCheck();
protected:
	// ===�����o�ϐ��錾===
	CScoreOverHead* m_pScore[MAX_EXPLOSION_NUM];	//�X�R�A�̔z��
	static int m_nTotalScore[5];	//�g�[�^���X�R�A//�����ӏ��Ή�	//�{��������O
};	//�X�R�A�Ǘ�

#endif	//!__SCORE_OH_MANAGER_H__
