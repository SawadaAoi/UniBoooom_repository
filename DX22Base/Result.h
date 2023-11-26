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

========================================== */

#ifndef __RESULT_H__	//Result.h�C���N���[�h�K�[�h
#define __RESULT_H__

// =============== �C���N���[�h ===================
#include "Scene.h"	//�e�̃w�b�_
#include "Texture.h"

// =============== �N���X��` =====================
class CResult :public CScene	//�V�[��
{
public:
	// ===�񋓒�`===========
	enum E_RESULT
	{
		E_RESULT_RESULT,		//���U���g�摜
		E_RESULT_BUTTON,		//�{�^�������w��
		E_RESULT_MAX,			//�v�f��
	};	//�^�C�g���V�[���̃e�N�X�`���̎��
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
	Texture* m_pTexture[E_RESULT_MAX];
};	//���U���g

#endif	//!__RESULT_H__