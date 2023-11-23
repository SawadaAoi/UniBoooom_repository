/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	HealItem�p�w�b�_
	------------------------------------
	HealItem.h
	------------------------------------
	�쐬��
		yamashita
	�ύX����
	�E2023/11/23 h�쐬 yamashita
	�E2023/11/23 �\����HEAL_ITEM���쐬 yamashita
========================================== */


// =============== �C���N���[�h�� =====================
#include "Camera.h"
#include "Transform3d.h"
#include "Shader.h"
#include "Model.h"

#ifndef __HEART_ITEM_H__
#define __HEART_ITEM_H__

class CHealItem
{
public:
	CHealItem();
	~CHealItem();
	void Update();
	void Draw();

	void Create(TPos3d<float> pos);
	void SetCamera(const CCamera* pCamera);	//�J�����Z�b�g�֐�


private:
	struct HEAL_ITEM
	{
		tagTransform3d m_Transform;	//���[���h���W�n���
		int		m_Cnt;				//���������܂ł̎��Ԃ𑪂�
		bool	m_bUse;				//�܂����݂��Ă邩�̃`�F�b�N
	};

	// ===�����o�ϐ��錾=====
	std::vector<HEAL_ITEM> m_healItem;			//�\���̂̃R���e�i
	Model* m_pModel;							//3D���f��
	VertexShader* m_pVS;						//�o�[�e�b�N�X�V�F�[�_�[�̃|�C���^
	const CCamera* m_pCamera;					//�J�����̃|�C���^
};



#endif // !__HEART_ITEM_H__


