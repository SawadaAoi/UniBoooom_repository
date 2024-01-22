/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�V�[���p���ۃN���X��`
	---------------------------------------
	ObjectManager.h
	---------------------------------------
	�쐬��	takagi

	�ύX����
	�E2024/01/21 ���� takagi

========================================== */

#ifndef __OBJECT_MANAGER_H__	//ObjectManager.h�C���N���[�h�K�[�h
#define __OBJECT_MANAGER_H__

// =============== �C���N���[�h ===================
#include "Camera.h"		//�����o�̃w�b�_
#include <3dObject.h>	//�����o�̃w�b�_
#include <2dObject.h>	//�����o�̃w�b�_
//#include <ObjManager.h>	//�����o�̃w�b�_
#include <map>			//�A�z�^�z��

// =============== �N���X��` =====================
class CObjectManager
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
		E_TYPE_FINISH_ALL,		//�A�v�����̂��I����
	};	//�V�[���̎��
public:
	// ===�v���g�^�C�v�錾===
	CObjectManager();							//�R���X�g���N�^
	virtual ~CObjectManager();					//�f�X�g���N�^
	virtual void Update();				//�X�V
	virtual void Draw();				//�`��
	bool IsFin() const;					//�I���m�F
	virtual E_TYPE GetNext() const = 0;	//���̃V�[���Q�b�^
	CCamera* GetCamera() const;			//�J�����Q�b�^

protected:
	// ===�����o�ϐ��錾=====
	std::map<int, CObject*> m_p3dObject;	//�I�u�W�F�N�g(�e�V�[���ōX�V���ɒ�`�����񋓂��L�[�Ƃ���)
	CCamera* m_pCamera;						//�J����	delete���Ȃ��A�|�C���^�͎󂯎���p
};	//�V�[��

#endif	//!__OBJECT_MANAGER_H__