/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�V�[���p���ۃN���X����
	---------------------------------------
	Scene.cpp
	---------------------------------------
	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/10/24 ������ takagi
	�E2023/11/05 ���i�K�̃R�[�f�B���O�K��K�p takagi
	�E2023/11/07 �R�����g�C�� takagi
	�E2023/11/16 �񋓒ǉ��E�I���t���O������� takagi
	�E2023/11/22 2D�`��֐���ǉ� nieda
	�E2023/11/23 �T�E���h�t�@�C���ǂݍ��݊֐��ǉ� nieda
	�E2023/11/27 �J���������� takagi
	�E2023/12/07 �r���[�s��擾�ɃJ�����g�p takagi
	�E2023/12/08 �J�������Ȃ�����UI���\���ł��Ȃ������C��
	�E2023/12/14 BGM�̊Ǘ���SceneManager�Ɉړ� yamashita
	�E2024/01/19 GetType()�֐��폜�E���̑����t�@�N�^�����O takagi
	�E2024/01/20 �ׂ��ȏC�� takagi
	�E2024/01/21 �R�����g���C takagi
	�E2024/01/23 Z�\�[�g��������const�� takagi

========================================== */

// =============== �C���N���[�h ===================
#include "Scene.h"		//���g�̃w�b�_
#include "Delete.h"		//�폜�}�N��
#include <vector>		//�z��R���e�i
#include <algorithm>	//�\�[�g�p
#include "ObjectDrawer.h"	//�I�u�W�F�N�g�`��@�\

/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CScene::CScene()
	:m_pCamera(nullptr)	//�J����
	,m_bFinish(false)	//�V�[���J�n
{
}

/* ========================================
	�f�X�g���N�^
	----------------------------------------
	���e�F�j�����ɍs������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CScene::~CScene()
{
	// =============== �I�� =====================
	SAFE_DELETE_POINTER_MAP(m_p2dObjectOnScreen);	//�I�u�W�F�N�g�폜
	SAFE_DELETE_POINTER_MAP(m_pObjectManager);		//�I�u�W�F�N�g�폜
	SAFE_DELETE_POINTER_MAP(m_p2dObjectOnWorld);	//�I�u�W�F�N�g�폜
	SAFE_DELETE_POINTER_MAP(m_p3dObject);			//�I�u�W�F�N�g�폜
	SAFE_DELETE(m_pCamera);							//�J�����폜
}

/* ========================================
	�X�V�֐�
	----------------------------------------
	���e�F�X�V����
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CScene::Update()
{
	// =============== �X�V =====================
	if (m_pCamera)	//�k���`�F�b�N
	{
		m_pCamera->Update();	//�J�����X�V
	}
	for_each(m_p3dObject.begin(), m_p3dObject.end(), [](std::pair<int, CObject*> pObject)->void {
		if (pObject.second)	//�k���`�F�b�N
		{
			pObject.second->Update();	//�I�u�W�F�N�g�X�V
		}
	});	//3D�I�u�W�F�N�g�X�V
	for_each(m_p2dObjectOnWorld.begin(), m_p2dObjectOnWorld.end(), [](std::pair<int, CObject*> pObject)->void {
		if (pObject.second)	//�k���`�F�b�N
		{
			pObject.second->Update();	//�I�u�W�F�N�g�X�V
		}
	});	//3D�\��2D�I�u�W�F�N�g�X�V
	for_each(m_pObjectManager.begin(), m_pObjectManager.end(), [](std::pair<int, CObjectManager*> pObjectManager)->void {
		if (pObjectManager.second)	//�k���`�F�b�N
		{
			pObjectManager.second->Update();	//�}�l�[�W���X�V
		}
	});	//�}�l�[�W���X�V
	for_each(m_p2dObjectOnScreen.begin(), m_p2dObjectOnScreen.end(), [](std::pair<int, CObject*> pObject)->void {
		if (pObject.second)	//�k���`�F�b�N
		{
			pObject.second->Update();	//�I�u�W�F�N�g�X�V
		}
	});	//2D�\��2D�I�u�W�F�N�g�X�V
}

/* ========================================
	�`��֐�
	----------------------------------------
	���e�F�`�揈��
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CScene::Draw() const
{
	//// =============== �ϐ��錾 =====================
	//std::vector<const CObject*> Subject;	//��ʑ�

	//// =============== ������ =====================
	//for_each(m_p3dObject.begin(), m_p3dObject.end(), [&Subject](std::pair<int, CObject*> pObject)->void {
	//	if (pObject.second)	//�k���`�F�b�N
	//	{
	//		Subject.emplace_back(pObject.second);	//�I�u�W�F�N�g�ǉ�
	//	}
	//});	//��ʑ�3D�I�u�W�F�N�g�A�h���X�R�s�[
	//for_each(m_p2dObjectOnWorld.begin(), m_p2dObjectOnWorld.end(), [&Subject](std::pair<int, CObject*> pObject)->void {
	//	if (pObject.second)	//�k���`�F�b�N
	//	{
	//		Subject.emplace_back(pObject.second);	//�I�u�W�F�N�g�ǉ�
	//	}
	//});	//��ʑ�2D�I�u�W�F�N�g�A�h���X�R�s�[
	//for_each(m_pObjectManager.begin(), m_pObjectManager.end(), [&Subject](std::pair<int, CObjectManager*> pObjectManager)->void {
	//	if (pObjectManager.second)	//�k���`�F�b�N
	//	{
	//		pObjectManager.second->GetObjects(Subject);	//�I�u�W�F�N�g�ǉ�
	//	}
	//});	//�Ǘ�����Ă���I�u�W�F�N�g�A�h���X�R�s�[

	//// =============== Z�\�[�g =====================
	//std::sort(Subject.begin(), Subject.end(), [](const CObject* pFirst, const CObject* pSecond)->bool {
	//	return pFirst && pSecond					//�k���`�F�b�N
	//		? pFirst->GetPosZ() > pFirst->GetPosZ()	//���̂��̂���`��(�����̏ꍇ�͓���ւ��Ȃ�)
	//		: false;								//�Е���null�Ȃ̂Ŕ�r����K�v���Ȃ�
	//});	//�I�u�W�F�N�g�̃\�[�g

	//// =============== 3D��ԕ`�� =====================
	//for_each(Subject.begin(), Subject.end(), [](const CObject* pObject)->void {
	//	if (pObject)	//�k���`�F�b�N
	//	{
	//		pObject->Draw();	//�`��
	//	}
	//});	//�\�[�g���ɕ`��

	//// =============== 2D��ԕ`�� =====================
	//for_each(m_p2dObjectOnScreen.begin(), m_p2dObjectOnScreen.end(), [](std::pair<int, const CObject*> pObject)->void {
	//	if (pObject.second)	//�k���`�F�b�N
	//	{
	//		pObject.second->Draw();	//�I�u�W�F�N�g�`��
	//	}
	//});	//�L�[���ɕ`��

	CObjectDrawer::Draw();
}

/* ========================================
	�I���m�F�֐�
	----------------------------------------
	���e�F�V�[������߂邩�ǂ����̃t���O��Ԃ�
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�Ftrue:�V�[������߂��� / false:�V�[���𑱂�����
=========================================== */
bool CScene::IsFin() const
{
	// =============== �� =====================
	return m_bFinish;	//�I���v���t���O
}

/* ========================================
   �J�����|�C���^�擾�֐�
   -------------------------------------
   ���e�F�J�����N���X�̃|�C���^�擾
   -------------------------------------
   ����1�F����
   -------------------------------------
   �ߒl�F����
=========================================== */
CCamera* CScene::GetCamera() const
{
	// =============== �� =====================
	return m_pCamera;	//�J������
}