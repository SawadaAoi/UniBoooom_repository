/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�񕜃A�C�e���Ǘ��p�\�[�X
	------------------------------------
	HealItemManager.cpp
	------------------------------------
	�쐬��	yamashita

	�ύX����
	�E2023/11/27 cpp�쐬 yamashita
	�E2023/11/28 �����֐����쐬 yamashita
	�E2023/11/28 ���X�g�̃|�C���^�擾�֐����쐬 yamashita
	�E2024/01/21 �R�����g���C�EMessageBox���P takagi

========================================== */

// =============== �C���N���[�h ===================
#include "HealItemManager.h"

/* ========================================
   �R���X�g���N�^
   ----------------------------------------
   ���e�F�J�n����
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
CHealItemManager::CHealItemManager()
	:m_pModel(nullptr)
	,m_pVS(nullptr)
{
	//���_�V�F�[�_�ǂݍ���
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error�F";	//�G���[�ӏ�
		MessageBox(nullptr, (ErrorSpot + "VS_Model.cso�ǂݍ��ݎ��s").c_str(), "Error", MB_OK | MB_ICONERROR);								//�G���[�ʒm
#endif
	}
	//�񕜃A�C�e���̃��f���ǂݍ���
	m_pModel = new Model;
	if (!m_pModel->Load("Assets/Model/heart/heart_1.FBX", 1.0f, Model::None)) {		//�{���Ɣ��]�͏ȗ���
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error�F";	//�G���[�ӏ�
		MessageBox(nullptr, (ErrorSpot + "HealItem:Model�ǂݍ��ݎ��s").c_str(), "Error", MB_OK | MB_ICONERROR);								//�G���[�ʒm
#endif
	}
	m_pModel->SetVertexShader(m_pVS);
}

/* ========================================
   �f�X�g���N�^
   ----------------------------------------
   ���e�F�I������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
CHealItemManager::~CHealItemManager()
{
	SAFE_DELETE(m_pVS);
	SAFE_DELETE(m_pModel);

	for (auto i = m_pHealItemList.begin(); i != m_pHealItemList.end();)
	{
		delete (*i);
		i = m_pHealItemList.erase(i);
	}
}

/* ========================================
   �X�V����
   ----------------------------------------
   ���e�F���t���[���Ăяo������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
void CHealItemManager::Update()
{
	for (auto i = m_pHealItemList.begin(); i != m_pHealItemList.end();i++)
	{
		(*i)->Update();
	}
}

/* ========================================
   �`�揈��
   ----------------------------------------
   ���e�F���t���[���Ăяo������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
void CHealItemManager::Draw()
{
	if (m_pHealItemList.size() == 0) { return; }

	for (auto i = m_pHealItemList.begin(); i != m_pHealItemList.end(); i++)
	{
		(*i)->Draw();
	}
}

/* ========================================
   ��������
   ----------------------------------------
   ���e�F�񕜃A�C�e�����w�肵�����W�ɐ�������
   ----------------------------------------
   �����F���W
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
void CHealItemManager::Create(TPos3d<float> pos)
{
	m_pHealItemList.push_back(new CHealItem(pos, m_pModel, m_pVS));	//����
	m_pHealItemList.back()->SetCamera(m_pCamera);					//���������A�C�e���ɃJ�������Z�b�g
}

/* ========================================
   �񕜃A�C�e���R���e�i�擾�֐�
   ----------------------------------------
   ���e�F�񕜃A�C�e���̃R���e�i���擾����
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�񕜃A�C�e���̃R���e�i
======================================== */
std::vector<CHealItem*>* CHealItemManager::GetHealItemConPtr()
{
	return &m_pHealItemList;
}

/* ========================================
   �J�����擾�֐�
   ----------------------------------------
   ���e�F�J�����̃|�C���^���擾����
   ----------------------------------------
   �����F�J�����̃|�C���^
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
void CHealItemManager::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;
}