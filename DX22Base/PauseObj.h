/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�|�[�Y�I�u�W�F��`
	---------------------------------------
	PauseObj.h

	�쐬��	takagi

	�ύX����
	�E2023/12/09 ���� takagi
	�E2023/12/10 ����i�s takagi

========================================== */

#ifndef __PAUSE_OBJ_H__	//PauseObj.h�C���N���[�h�K�[�h
#define __PAUSE_OBJ_H__

// =============== �C���N���[�h =====================
#include "2dPolygon.h"	//�e�̃w�b�_

// =============== �N���X��` =====================
class CPauseObj	:public C2dPolygon	//���ʃI�u�W�F
{
public:
	// ===�v���g�^�C�v�錾===
	CPauseObj(const int& nWaitTime = 0);								//�R���X�g���N�^
	virtual ~CPauseObj() ;												//�f�X�g���N�^
	virtual void Update();												//�X�V
	virtual void Draw(E_DRAW_MODE eMode = E_DRAW_MODE_NORMAL) override;	//�`��
	void SetReach(const TPos3d<float>& fReach);							//���B�n�_�Z�b�^
	void Destroy();														//�j��
	bool IsDestroyed();													//�j�������t���O�Q�b�^
protected:
	// ===�����o�ϐ��錾=====
	TPos3d<float> m_fReach;	//���B�n�_
	// ===�v���g�^�C�v�錾===
	virtual void CulculatePos(TPos3d<float>& fPos);	//�ʒu�Z�o
private:
	// ===�����o�ϐ��錾=====
	float m_fOffset;		//�ŏI�ʒu�Ƃ�x�Y��
	int* m_pnWaitTime;		//�����ҋ@���Ԍv��
	const int m_nLogWait;	//�ҋ@���ԑޔ�
	int* m_pnMoveTime;		//���ꂽ�ʒu����߂�̂ɂ����鎞��
	int* m_pnRemoveTime;	//���ꂽ�ʒu����߂�̂ɂ����鎞��
	bool m_bDestroyed;		//�j������������������
};	//�|�[�Y�p�I�u�W�F�N�g

#endif	//!__PAUSE_OBJ_H__