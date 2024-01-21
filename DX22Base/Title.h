/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�^�C�g���V�[����`
	---------------------------------------
	Title.h
	------------------------------------
	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/10/26 ������ takagi
	�E2023/11/05 ���i�K�̃R�[�f�B���O�K��K�p takagi
	�E2023/11/07 �R�����g�C�� takagi
	�E2023/11/16 �I�[�o�[���C�h�֐��ǉ� takagi
	�E2023/12/16 �`�敨���P takagi
	�E2024/01/18 �p�������l�[���Ή� takagi
	�E2024/01/20 GetType()�֐��폜�E���t�@�N�^�����O takagi

========================================== */

#ifndef __TITLE_H__	//Title.h�C���N���[�h�K�[�h
#define __TITLE_H__

// =============== �C���N���[�h ===================
#include "Scene.h"		//�e�̃w�b�_
#include "2dObject.h"	//�����o�̃w�b�_
#include "UcFlag.h"		//�����o�̃w�b�_
#include <map>			//�A�z�R���e�i

// =============== �N���X��` =====================
class CTitle :public CScene	//�V�[��
{
private:
	// ===�񋓒�`==========
	enum E_FLAG
	{
		//E_FLAG_PAUSEMODE = 0x01,		//�|�[�Y���[�h
		E_FLAG_COMMAND_CONTINUE = 0x02,	//�p���R�}���h
		E_FLAG_COMMAND_FINISH = 0x04,	//�I���R�}���h
		E_FLAG_DECIDE_COMMAND = 0x08,	//�R�}���h������
		E_FLAG_TIDYING_UP = 0x10,		//�Еt����
		//E_FLAG_CALL_FINISH = 0x20,		//�I���\��
	};	//�t���O
	enum E_2D	//�X�V��
	{
		E_2D_BACK,		//�w�i
		E_2D_START,		//�J�n�R�}���h
		E_2D_FINISH,	//�I���R�}���h
		E_2D_LOGO,		//�^�C�g�����S
		E_2D_OPENING,	//�J�n�f��
		E_2D_MAX,		//�v�f��
	};	//2D�̃I�u�W�F�N�g
	// ===�萔��`===========
	const float START_RADIUS_CAMERA = 0.5f;		//�����J��������
	const float END_RADIUS_CAMERA = 15.0f;		//�ŏI�J��������
	const int ZOOMOUT_FRAME = 90;				//�Y�[���A�E�g�ɂ�����t���[����
	const float COMMAND_SPACE = 120.0f;			//�R�}���h���m�̏c�̊�
	const float COMMAND_DOWN = 160.0f;			//�R�}���h�𒆐S����ǂꂾ�������邩
	const std::map<int, int> MAP_WAIT_START = {
		{E_2D_BACK, 0},	//�w�i
		{E_2D_START, ZOOMOUT_FRAME},	//�J�n�R�}���h
		{E_2D_FINISH, ZOOMOUT_FRAME},	//�I���R�}���h
		{E_2D_LOGO, 0},		//�^�C�g�����S
		{E_2D_OPENING, 0},	//�J�n�f��
	};	//�|���S���ƕ\���J�n�ҋ@���Ԃ̑Ή��\
	const std::map<int, int> MAP_WAIT_FIN = {
		{E_2D_BACK, 30},	//�w�i
		{E_2D_START, 15},	//�J�n�R�}���h
		{E_2D_FINISH, 30},	//�I���R�}���h
		{E_2D_LOGO, 15},	//�^�C�g�����S
	};	//�|���S���ƕ\���I���ҋ@���Ԃ̑Ή��\
	const std::map<int, std::string> MAP_TEXTURE = {
		{E_2D_BACK, "Assets/Texture//Title/TitleBg.png"},				//�w�i
		{E_2D_START, "Assets/Texture/Title/Title_Start.png"},			//�J�n�R�}���h
		{E_2D_FINISH, "Assets/Texture/Pause/Pause_Finish.png"},			//�I���R�}���h
		{E_2D_LOGO, "Assets/Texture/Title/TitleLogo.png"},				//�^�C�g�����S
		{E_2D_OPENING, "Assets/Texture/Title/titleopening_kari.png"},	//�J�n�f��
	};	//�|���S���ƃe�N�X�`���̑Ή��\
	const std::map<int, TPos3d<float>> MAP_POS = {
		{E_2D_BACK, {static_cast<float>(SCREEN_WIDTH) / 2.0f, static_cast<float>(SCREEN_HEIGHT) / 2.0f, 0.0f}},		//�w�i
		{E_2D_START, {static_cast<float>(SCREEN_WIDTH) / 2.0f, 260.0f, 0.0f}},										//�J�n�R�}���h
		{E_2D_FINISH, {static_cast<float>(SCREEN_WIDTH) / 2.0f, 260.0f - COMMAND_SPACE, 0.0f}},						//�I���R�}���h
		//{E_2D_LOGO, {static_cast<float>(SCREEN_WIDTH) / 2.0f, 450.0f, 0.0f}},										//�^�C�g�����S
		{E_2D_OPENING, {static_cast<float>(SCREEN_WIDTH) / 2.0f, static_cast<float>(SCREEN_HEIGHT) / 2.0f, 0.0f}},	//�I�[�v�j���O
	};	//�|���S���Ə������W�̑Ή��\
public:
	// ===�v���g�^�C�v�錾===
	CTitle();							//�R���X�g���N�^
	~CTitle();							//�f�X�g���N�^
	void Update() override;				//�X�V
	void Draw() override;				//�`��
	E_TYPE GetNext() const override;	//���̃V�[���Q�b�^
private:
	// ===�����o�ϐ��錾=====
	CUcFlag m_ucFlag;		//�t���O
	E_TYPE m_eNextScene;	//�V�[���J�ڐ�
};	//�^�C�g��

#endif	//!__TITLE_H__