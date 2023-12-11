/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�|�[�Y��ʒ�`
	---------------------------------------
	Pause.h

	�쐬��	takagi

	�ύX����
	�E2023/12/01 ���� takagi
	�E2023/12/04 ���� takagi
	�E2023/12/06 pose��pause�C���A�|�[�Y�����\�� takagi
	�E2023/12/08 �A�N�Z�X�w��q�Ԉړ� takagi
	�E2023/12/09 �I�u�W�F�N�g���� takagi
	�E2023/12/10 ����i�s takagi

========================================== */

#ifndef __PAUSE_H__	//Pause.h�C���N���[�h�K�[�h
#define __PAUSE_H__

// =============== �C���N���[�h =====================
#include "Sound.h"		//��
#include "Camera.h"		//�J����
#include "PauseObj.h"	//�����o�̃w�b�_
#include <vector>		//�z��R���e�i

// =============== �N���X��` =====================
class CPause
{
private:
	// ===�񋓒�`==========
	enum E_FLAG
	{
		E_FLAG_PAUSEMODE = 0x01,		//�|�[�Y���[�h
		E_FLAG_COMMAND_CONTINUE = 0x02,	//�p���R�}���h
		E_FLAG_COMMAND_FINISH = 0x04,	//�I���R�}���h
		E_FLAG_DECIDE_COMMAND = 0x08,	//�R�}���h������
		E_FLAG_CALL_FINISH = 0x10,		//�I���\��
	};	//�t���O
public:
	// ===�v���g�^�C�v�錾===
	CPause(const CCamera* pCamera);						//�R���X�g���N�^
	~CPause();											//�f�X�g���N�^
	void Update();										//�X�V
	void Draw();										//�`��
	bool IsFin() const;									//�I���m�F
	void SetCamera(const CCamera* pCamera = nullptr);	//�J�����Z�b�^
	bool IsPause() const;								//�|�[�Y����
private:
	// ===�����o�ϐ��錾=====
	unsigned char m_ucFlag;							//�t���O
	std::vector<CPauseObj*> m_p2dObj;				//���ʃ|���S��
	const CCamera* m_pCamera;						//�J����	���Q�Ƃ݂̂Ɏg�p�A�폜���Ȃ�
	// ===�v���g�^�C�v�錾===
	void Boot();									//�|�[�Y���[�h�N��
	void InitObjects();								//�������E���I�m��
	void Destroy();									//�|�[�Y�I��
	void UpFlag(const unsigned char& ucBitFlag);	//�t���O�N����
	void DownFlag(const unsigned char& ucBitFlag);	//�t���O�~�낵
	void SetFlag(const unsigned char& ucBitFlag);	//�t���O���]
};	//���U���g

#endif	//!__PAUSE_H__