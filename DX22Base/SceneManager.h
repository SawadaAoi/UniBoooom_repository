/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�V�[���Ǘ���`
	---------------------------------------
	SceneManager.h

	�쐬��	takagi

	�ύX����
	�E2023/10/24	������ takagi
	�E2023/11/05 ���i�K�̃R�[�f�B���O�K��K�p takagi
	�E2023/11/07 �R�����g�C�� takagi
	�E2023/11/16 �V�[���J�ڂ̗�������� takagi
	�E2023/11/17 �ߋ��V�[���ɖ߂鏈����ǉ� takagi
	�E2023/11/23 �t�F�[�h�@�\�ǉ� takagi
	�E2023/12/01 �t�F�[�h�̎d�l�ύX takagi 

========================================== */

#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

// =============== �C���N���[�h ===================
#include "Scene.h"	//�����o�̃w�b�_
#include "Fade.h"	//�����o�̃w�b�_

// =============== �N���X��` =====================
class CSceneManager	//�Ǘ�
{
public:
	// ===�v���g�^�C�v�錾===
	CSceneManager();		//�R���X�g���N�^
	~CSceneManager();		//�f�X�g���N�^
	void Update();			//�X�V
	void Draw();			//�`��
	bool IsFin() const;		//�I���m�F
private:
	// ===�����o�ϐ��錾=====
	CScene* m_pScene;				//�V�[��
	CScene::E_TYPE m_ePastScene;	//�O�̃V�[��
	CScene::E_TYPE m_eNextScene;	//�V�[���J�ڐ�
	bool m_bFinish;					//�I���\��p(true�ŏI��)
	bool m_bStartFadeOut;			//�t�F�[�h�A�E�g�J�n������
	bool m_bFinFadeOut;				//�t�F�[�h�A�E�g�I��������
	CFade* m_pFade;					//�t�F�[�h

	// ===�v���g�^�C�v�錾===
	void ChangeScene();		//�V�[���ύX
	void MakeNewScene();	//�V�V�[�����I�m��
};	//�V�[���Ǘ�

#endif	//!__SCENE_MANAGER_H__