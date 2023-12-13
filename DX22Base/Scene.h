/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�V�[���p���ۃN���X��`
	---------------------------------------
	Scene.h

	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/10/24 ������ takagi
	�E2023/10/26 GetType()�֐��̖߂�l���C�� takagi
	�E2023/11/04 �񋓒��g�ǉ� takagi
	�E2023/11/05 ���i�K�̃R�[�f�B���O�K��K�p takagi
	�E2023/11/07 �R�����g�C�� takagi
	�E2023/11/16 �񋓒ǉ��EGetNext()�֐��ǉ��E�I���t���O��������E�R�����g�C�� takagi
	�E2023/11/17 �񋓒��g�ǉ� takagi
	�E2023/11/22 2D�`��֐��錾 nieda
	�E2023/11/23 �T�E���h�t�@�C���ǂݍ��݊֐��p�ϐ��ǉ� nieda

========================================== */

#ifndef __SCENE_H__	//Scene.h�C���N���[�h�K�[�h
#define __SCENE_H__

// =============== �C���N���[�h ===================
#include "Texture.h"
#include "Sound.h"
#include "Camera.h"
#include "Fade.h"

// =============== �N���X��` =====================
class CScene
{
public:
	// ===�񋓒�`===========
	enum E_TYPE
	{
		E_TYPE_TITLE,			//�^�C�g���V�[��
		//E_TYPE_PROT,			//�v���g�^�C�v
		E_TYPE_SELECT_STAGE,	//�X�e�[�W�Z���N�g
		E_TYPE_STAGE1,			//�X�e�[�W1
		E_TYPE_STAGE2,			//�X�e�[�W2
		E_TYPE_STAGE3,			//�X�e�[�W3
		E_TYPE_RESULT,			//���U���g�V�[��
		E_TYPE_MAX,				//�v�f��
		E_TYPE_NONE = -255,		//�Y���Ȃ�
		E_TYPE_PAST,			//�O�̃V�[��
	};	//�V�[���̎��
public:
	// ===�v���g�^�C�v�錾===
	CScene();							//�R���X�g���N�^
	virtual ~CScene();					//�f�X�g���N�^
	virtual void Update();				//�X�V
	virtual void Draw();				//�`��
	bool IsFin() const;					//�I���m�F
	virtual E_TYPE GetType() const = 0;	//���g�̎�ރQ�b�^
	virtual E_TYPE GetNext() const = 0;	//���̃V�[���Q�b�^
	void Draw2d(float, float, float, float, Texture*);	// �����Ȃ���2D�e�N�X�`���\��
	CCamera* GetCamera();
	virtual void SoundUpdate();
protected:
	// ===�����o�ϐ��錾=====
	bool m_bFinish;	//�I���\��p(true�ŏI��)
	CCamera* m_pCamera;
	CFade* m_pFade;
	XAUDIO2_BUFFER* m_pBGM;							//BGM�̉����f�[�^
	IXAudio2SourceVoice* m_pBGMSpeaker;				//BGM�𕷂���鑤
};	//�V�[��

#endif	//!__SCENE_H__