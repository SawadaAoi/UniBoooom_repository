/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	���[�h�C���W�P�[�^��`
	---------------------------------------
	LoadIndicator.h

	�쐬��	takagi

	�ύX����
	�E2024/03/06 ����J�n takagi

========================================== */

#ifndef __LOAD_INDICATOR_H__	//LoadIndicator.h�C���N���[�h�K�[�h
#define __LOAD_INDICATOR_H__

// =============== �C���N���[�h =====================
#include <thread>			//�X���b�h
#include "DrawAnimation.h"	//2d�A�j��
#include <memory>			//ptr�Ǘ�

// =============== �N���X��` =====================
class CLoadIndicator
{
public:
	// ===�v���g�^�C�v�錾===
	static CLoadIndicator& GetThis();	//���g�̃Q�b�^
	virtual void BeginDraw() final;
	virtual void EndDraw() final;
private:
	// ===�ϐ��錾===========
	std::jthread m_DrawThread;				//�X���b�h
	std::shared_ptr<CDrawAnim> m_p2d;		//�A�j���摜
	// ===�v���g�^�C�v�錾===
	CLoadIndicator();										//�R���X�g���N�^
	CLoadIndicator(const CLoadIndicator& Obj);				//�R�s�[�R���X�g���N�^
	CLoadIndicator& operator=(const CLoadIndicator& Obj);	//������Z�q
	~CLoadIndicator();										//�f�X�g���N�^
};	//���[�h�C���W�P�[�^

#endif	//!__LOAD_INDICATOR_H__