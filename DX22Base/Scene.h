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
	�E2023/10/24	������ takagi
	�E2023/10/26	GetType()�֐��̖߂�l���C�� takagi
	�E2023/11/04	�񋓒��g�ǉ� takagi
	�E2023/11/05 ���i�K�̃R�[�f�B���O�K��K�p takagi
	�E2023/11/07 �R�����g�C�� takagi

========================================== */

#ifndef __SCENE_H__
#define __SCENE_H__

// =============== �N���X��` =====================
class CScene	//�V�[��
{
public:
	// =============== �񋓒�` =======================
	enum E_TYPE
	{
		E_TYPE_TITLE,	//�^�C�g���V�[��
		E_TYPE_PROT,	//�v���g�^�C�v
	};	//�V�[���̎��
public:
	// =============== �v���g�^�C�v�錾 ===============
	CScene();							//�R���X�g���N�^
	virtual ~CScene();					//�f�X�g���N�^
	virtual void Update();				//�X�V
	virtual void Draw() const;			//�`��	
	virtual E_TYPE GetType() const = 0;	//���g�̎�ރQ�b�^
};	//�V�[��

#endif	//!__SCENE_H__