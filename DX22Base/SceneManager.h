/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�V�[���Ǘ���`
	---------------------------------------
	SceneManager.h
	---------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/10/24 ������ takagi
	�E2023/11/05 ���i�K�̃R�[�f�B���O�K��K�p takagi
	�E2023/11/07 �R�����g�C�� takagi
	�E2023/11/16 �V�[���J�ڂ̗�������� takagi
	�E2023/11/17 �ߋ��V�[���ɖ߂鏈����ǉ� takagi
	�E2023/11/23 �t�F�[�h�@�\�ǉ� takagi
	�E2023/12/01 �t�F�[�h�̎d�l�ύX takagi
	�E2024/01/18 CScene->GetType()�֐����g�p���Ȃ��`�ɕύX�Ȃǃ��t�@�N�^�����O takagi
	�E2024/01/20 ���֌W���t�@�N�^�����O takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __SCENE_MANAGER_H__	//SceeneManager.h�C���N���[�h�K�[�h
#define __SCENE_MANAGER_H__

// =============== �C���N���[�h ===================
#include "Scene.h"			//�����o�̃w�b�_
#include "Fade.h"			//�����o�̃w�b�_
#include "Sound.h"			//�����o�̃w�b�_
#include "UcFlag.h"			//�����o�̃w�b�_
#include "Title.h"			//�C���X�^���X���
#include "SelectStage.h"	//�C���X�^���X���
#include "Stage1.h"			//�C���X�^���X���
#include "Stage2.h"			//�C���X�^���X���
#include "Stage3.h"			//�C���X�^���X���
#include "Result.h"			//�C���X�^���X���
#include <map>				//�A�z�^�R���e�i

// =============== �N���X��` =====================
class CSceneManager
{
private:
	// ===�񋓒�`===========
	enum E_BIT_FLAG
	{
		E_BIT_FLAG_FINISH = 0x01,			//�V�[���I���\��p�t���O(�I���ŏI��)
		E_BIT_FLAG_START_FADE_OUT = 0x02,	//�t�F�[�h�A�E�g���J�n������
		E_BIT_FLAG_END_FADE_OUT = 0x04,		//�t�F�[�h�A�E�g���I��������
		E_BIT_FLAG_4 = 0x08,				//
		E_BIT_FLAG_5 = 0x10,				//
		E_BIT_FLAG_6 = 0x20,				//
		E_BIT_FLAG_7 = 0x40,				//
		E_BIT_FLAG_8 = 0x80,				//
	};	//�t���O�Ǘ�
	// ===�萔��`===========
	const std::map<size_t, CScene::E_TYPE> MAP_SCENE_TYPE = {
		{typeid(CTitle).hash_code(), CScene::E_TYPE_TITLE},					//�^�C�g��
		{typeid(CSelectStage).hash_code(), CScene::E_TYPE_SELECT_STAGE},	//�X�e�[�W�I��
		{typeid(CStage1).hash_code(), CScene::E_TYPE_STAGE1},				//�X�e�[�W1
		{typeid(CStage2).hash_code(), CScene::E_TYPE_STAGE2},				//�X�e�[�W2
		{typeid(CStage3).hash_code(), CScene::E_TYPE_STAGE3},				//�X�e�[�W3
		{typeid(CResult).hash_code(), CScene::E_TYPE_RESULT},				//���U���g
	};	//�V�[����
	const std::map<size_t, XAUDIO2_BUFFER*> MAP_BGM = {
		{typeid(CTitle).hash_code(), CSound::LoadSound("Assets/Sound/BGM/BGM_maou.mp3", true)},			//�^�C�g��
		{typeid(CSelectStage).hash_code(), CSound::LoadSound("Assets/Sound/BGM/BGM_maou.mp3", true)},	//�X�e�[�W�I��
		{typeid(CStage1).hash_code(), CSound::LoadSound("Assets/Sound/BGM/BGM_maou.mp3", true)},		//�X�e�[�W1
		{typeid(CStage2).hash_code(), CSound::LoadSound("Assets/Sound/BGM/BGM_maou.mp3", true)},		//�X�e�[�W2
		{typeid(CStage3).hash_code(), CSound::LoadSound("Assets/Sound/BGM/BGM_maou.mp3", true)},		//�X�e�[�W3
		{typeid(CResult).hash_code(), CSound::LoadSound("Assets/Sound/BGM/BGM_maou.mp3", true)},		//���U���g
	};	//BGM�f�[�^
public:
	// ===�v���g�^�C�v�錾===
	CSceneManager();	//�R���X�g���N�^
	~CSceneManager();	//�f�X�g���N�^
	void Update();		//�X�V
	void Draw();		//�`��
	bool IsFin() const;	//�I���m�F
private:
	// ===�����o�ϐ��錾=====
	CScene* m_pScene;					//�V�[��
	CScene::E_TYPE m_ePastScene;		//�O�̃V�[��
	CScene::E_TYPE m_eNextScene;		//�V�[���J�ڐ�
	CUcFlag m_UcFlag;					//�t���O
	CFade* m_pFade;						//�t�F�[�h
	IXAudio2SourceVoice* m_pBGMSpeaker;	//BGM�𕷂���鑤
	// ===�v���g�^�C�v�錾===
	void ChangeScene();		//�V�[���ύX
	void MakeNewScene();	//�V�V�[�����I�m��
	void SoundUpdate();		//BGM�̍X�V
	void SoundFade();		//BGM�̃t�F�[�h
	void PlayBGM();			//BGM�̍Đ�
};	//�V�[���Ǘ�

#endif	//!__SCENE_MANAGER_H__