/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	UNION�Ǘ���`
	------------------------------------
	UnionManager.h
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/12/19 ���� takagi

========================================== */

#ifndef ___UNION_MANAGER_H___	//UnionManager.h�C���N���[�h�K�[�h
#define ___UNION_MANAGER_H___

// =============== �C���N���[�h ===================
#include "Shader.h"			//�����o�̃w�b�_
#include "Texture.h"		//�����o�̃w�b�_
#include "Camera.h"			//�����o�̃w�b�_
#include "Transform3d.h"	//�����o�̃w�b�_
#include "DiType.h"			//�����o�̃w�b�_
#include "TriType.h"		//�����o�̃w�b�_
#include <map>				//�A�z�R���e�i
#include <vector>			//�z��R���e�i
#include <typeinfo>			//�����o�̃w�b�_
#include "2dPolygon.h"		//�����o�̃w�b�_
#include "Union.h"			//�����o�̃w�b�_

// =============== �N���X��` =====================
class CUnionManager
{
public:
	// ===�v���g�^�C�v�錾===
	CUnionManager();									//�R���X�g���N�^
	//CUnionManager(const CUnionManager& Obj);			//�R�s�[�R���X�g���N�^
	~CUnionManager();									//�f�X�g���N�^
	void Update();										//�X�V
	void Draw();										//�`��
	void SetCamera(CCamera* pCamera);					//�J�����Z�b�^
	void MakeUnion(const size_t& HashTypeId, const TPos3d<float>& fPos);
private:
	// ===�����o�ϐ��錾=====
	unsigned char m_ucFlag;							//�t���O
	static int ms_nCntUnionManager;					//���g�̐�����
	static std::map<size_t, Texture*> ms_pTexture;	//�e�N�X�`�����
	std::vector<CUnion*> m_pUnion;					//UNION
	const CCamera* m_pCamera;						//�J����(�Ⴂ��)
};	//�t�F�[�h

#endif // !___UNION_MANAGER_H___