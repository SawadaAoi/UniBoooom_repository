/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�|�[�Y��ʎ���
	---------------------------------------
	Pose.cpp

	�쐬��	takagi

	�ύX����
	�E2023/12/01 ���� takagi

========================================== */

// =============== �C���N���[�h ===================
#include "Pose.h"	//���g�̃w�b�_
#include <map>		//�֌W���R���e�i
#include "DiType.h"	//�Q�̌^

// =============== �񋓌^��` ===================
enum E_2D
{
	E_2D_BACK,		//�w�i
	E_2D_COMMAND_A,	//�R�}���hA�p
	E_2D_COMMAND_B,	//�R�}���hA�p
	E_2D_COMMAND_C,	//�R�}���hA�p
};	//2D�̃I�u�W�F�N�g

// =============== �萔��` ===================
const std::string BGM_FILE_PASS("Assets/Sound/BGM/BGM_maou.mp3");
const std::string SE_FILE_PASS("Assets/Sound/SE/Smash.mp3");
const std::map<int, std::string> MAP_TEXTURE = {
	{E_2D_BACK, "Assets/Texture/PoseBg.png"},	//�w�i
};	//�|���S���ƃe�N�X�`���̑Ή��\
const std::map<int, TDiType<std::string>> MAP_SHADER = {
	{E_2D_BACK, {"VsPose.cso", "PsPose.cso"}},	//�w�i
};	//�|���S���ƃV�F�[�_�[[���_, �s�N�Z��]�̑Ή��\

/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�FCCamera* pCamera�F�J�����̃|�C���^
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CPose::CPose(CCamera* pCamera)
	:m_pBgPs(nullptr)	//�w�i�p�s�N�Z���V�F�[�_
	,m_pBgVs(nullptr)	//�w�i�p���_�V�F�[�_
{
	// =============== ������ ===================
	if (pCamera)	//�k���`�F�b�N
	{
		m_pCamera = pCamera;	//�J����
	}

	// =============== ���I�m�� ===================
	m_2dObj = {	//�X�V��
		new C2dPolygon(),	//�w�i�p
		new C2dPolygon(),	//�R�}���hA�p
		new C2dPolygon(),	//�R�}���hB�p
		new C2dPolygon(),	//�R�}���hC�p
	};	//���ʃ|���S��
	
	// =============== �t�@�C���ǂݍ��� ===================
	for (std::vector<C2dPolygon*>::iterator Iterator = m_2dObj.begin(), int nCnt = 0; Iterator < m_2dObj.end(); Iterator++, nCnt++)
	{
		if (MAP_TEXTURE.size() < nCnt)	//map�̔z�񂪑��݂���Y����
		{
			(*Iterator)->SetTexture(MAP_TEXTURE.at(nCnt).c_str());	//�e�N�X�`���o�^
		}
	}
	m_pBGM = CSound::LoadSound(BGM_FILE_PASS.c_str(), true);	//BGM�̓ǂݍ���
	m_pSEHitHammer = CSound::LoadSound(SE_FILE_PASS.c_str());	//SE�̓ǂݍ���
	
	// =============== �V�F�[�_�[�ݒ� ===================
	m_2dObj[E_2D_BACK]->SetVertexShader(MAP_SHADER.at(E_2D_BACK).x.c_str());
	m_2dObj[E_2D_BACK]->SetPixelShader(MAP_SHADER.at(E_2D_BACK).y.c_str());
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
CPose::~CPose()
{	
	// =============== �I�� ===================
	for (std::vector<C2dPolygon*>::iterator Iterator = m_2dObj.end(); Iterator < m_2dObj.begin();)
	{
		delete (*(--Iterator));				//���������
		Iterator = m_2dObj.erase(Iterator);	//�C�e���[�^�폜�E�ړ�
	}
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
void CPose::Update()
{
}

/* ========================================
	�`��֐�
	----------------------------------------
	���e�F�`�揈��
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
	======================================== */
void CPose::Draw()
{
	// =============== �`�� ===================
	for (std::vector<C2dPolygon*>::iterator Iterator = m_2dObj.begin(), int nCnt = 0; Iterator < m_2dObj.end(); Iterator++, nCnt++)
	{
		if (MAP_TEXTURE.size() < nCnt)	//map�̔z�񂪑��݂���Y����
		{
			(*Iterator)->Draw();	//���ʕ`��
		}
	}
}

/* ========================================
	�I�������֐�
	----------------------------------------
	���e�F�I���t���O�̒l��Ԃ�
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
	======================================== */
bool CPose::IsFin() const
{
	// =============== �� ===================
	return m_bFinish;	//�I���t���O
}