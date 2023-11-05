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


   ======================================== */

#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

   // =============== �C���N���[�h ===================
#include "Scene.h"	//�����o�̃w�b�_

   // =============== �N���X��` =====================
class CSceneManager	//�Ǘ�
{
public:
	// =============== �v���g�^�C�v�錾 ===============
	CSceneManager();		//�R���X�g���N�^
	~CSceneManager();		//�f�X�g���N�^
	void Update();			//�X�V
	void Draw() const;		//�`��
private:
	// =============== �����o�[�ϐ��錾 ===============
	CScene* m_pScene;	//�V�[��
};	//�V�[���Ǘ�

#endif	//!__SCENE_MANAGER_H__