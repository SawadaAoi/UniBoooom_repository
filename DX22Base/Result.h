/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	���U���g�V�[����`
	---------------------------------------
	Result.h

	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/11/16 ���� takagi
	�E2023/12/08 �V�[���J�ڗp�ɕϐ��ǉ� takagi
	�E2023/12/11 ���щ��\�� takagi

========================================== */

#ifndef __RESULT_H__	//Result.h�C���N���[�h�K�[�h
#define __RESULT_H__

// =============== �C���N���[�h ===================
#include "Scene.h"		//�e�̃w�b�_
#include "Texture.h"
#include "BattleData.h"	//�����o�̃w�b�_
#include <vector>		//�z��^�R���e�i
#include "DirectWrite.h"			//�o�͗p

// =============== �N���X��` =====================
class CResult :public CScene	//�V�[��
{
public:
	// ===�񋓒�`===========
	//enum E_RESULT
	//{
	//	E_RESULT_RESULT,		//���U���g�摜
	//	E_RESULT_BUTTON,		//�{�^�������w��
	//	E_RESULT_MAX,			//�v�f��
	//};	//�^�C�g���V�[���̃e�N�X�`���̎��



	enum E_TEXTURE
	{
		BG_SCREEN,
		BG_TEXT,
		TEXT_RESULT,
		TEXT_SVL_TIME,
		TEXT_HUNT_NUM,
		TEXT_SCORE,
		TEXT_NUM,
		TEXT_COLON,

		STAGE,
		STAGE_1,
		STAGE_2,
		STAGE_3,
		STAMP,

		TEXTURE_MAX,

	};
public:
	// =============== �v���g�^�C�v�錾 ===============
	CResult();							//�R���X�g���N�^
	~CResult();							//�f�X�g���N�^
	void Update();						//�X�V
	void Draw();					//�`��	
	E_TYPE GetType() const override;	//���g�̎�ރQ�b�^
	E_TYPE GetNext() const override;	//���̃V�[���Q�b�^
private:


	// =============== �����o�ϐ���` ===============
	Texture* m_pTexture[TEXTURE_MAX];
	BattleData m_Data;					//�퓬����
	FontData m_Font;					//�t�H���g�f�[�^
	FontData m_FontDef;					//�f�t�H���g�t�H���g
};	//���U���g

#endif	//!__RESULT_H__