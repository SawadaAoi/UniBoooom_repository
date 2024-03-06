/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�^�C�g���J�n���Y�[���A�E�g�p�J�E���^��`
	---------------------------------------
	TitleInitCounter.h

	�쐬��	takagi

	�ύX����
	�E2024/02/02 ���� takagi
	�E2024/02/05 �뎚�C���E�ꕔ�������� takagi
	�E2024/02/08 �w�b�_���C�� takagi

========================================== */

#ifndef __TITLE_INIT_COUNTER_H__	//TitleInitCounter.h�C���N���[�h�K�[�h
#define __TITLE_INIT_COUNTER_H__

// =============== �C���N���[�h =====================
#include "TitleObj.h"	//�e�̃w�b�_
#include <memory>		//ptr�Ǘ�
#include "FrameCnt.h"	//�J�E���^

// =============== �N���X��` =====================
class CTitleInitCounter
{
public:
	// ===�v���g�^�C�v�錾===
	virtual void Update() final;											//�X�V
	virtual void StartCount() final;										//�J�E���^�n��
	static CTitleInitCounter& GetThis();									//���g�̃Q�b�^
	virtual const std::weak_ptr<const CFrameCnt> GetCounter() const final;	//�J�E���^�Q�b�^	���킴�Ɩ߂�l�͎Q�ƂłȂ�
private:
	// ===�ϐ��錾===========
	static std::shared_ptr<CFrameCnt> ms_pCounter;	//�k���J�E���^
	static bool ms_bCountStarted;					//�J�E���g���J�n�������Ƃ����邩(true�F����)
	// ===�v���g�^�C�v�錾===
	CTitleInitCounter();										//�R���X�g���N�^
	CTitleInitCounter(const CTitleInitCounter& Obj);			//�R�s�[�R���X�g���N�^
	CTitleInitCounter& operator=(const CTitleInitCounter& Obj);	//������Z�q
	~CTitleInitCounter();										//�f�X�g���N�^	��shared_ptr���A�N�Z�X����p
};	//�^�C�g���J�n���Y�[���A�E�g�Ɏg�p����J�E���^

#endif	//!__TITLE_INIT_COUNTER_H__