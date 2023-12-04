/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�|�[�Y��ʎ���
	---------------------------------------
	Pose.cpp

	�쐬��	takagi

	�ύX����
	�E2023/12/01 ���� takagi
	�E2023/12/04 ���� takagi

========================================== */

// =============== �C���N���[�h ===================
#include "Pose.h"		//���g�̃w�b�_
#include <map>			//�֌W���R���e�i
#include <array>		//�z��
#include "CameraDef.h"	//�^���J����

// =============== �񋓌^��` ===================
enum E_2D
{
	E_2D_BACK,		//�w�i
	E_2D_COMMAND_A,	//�R�}���hA�p
	E_2D_COMMAND_B,	//�R�}���hA�p
	E_2D_COMMAND_C,	//�R�}���hA�p
};	//2D�̃I�u�W�F�N�g
enum E_SHADER_TYPE
{
	E_SHADER_TYPE_VERTEX,	//���_�V�F�[�_�[
	E_SHADER_TYPE_PIXEL,	//�s�N�Z���V�F�[�_�[
	E_SHADER_TYPE_MAX,		//�v�f��
};

// =============== �萔��` ===================
const std::string BGM_FILE_PASS("Assets/Sound/BGM/BGM_maou.mp3");
const std::string SE_FILE_PASS("Assets/Sound/SE/Smash.mp3");
const std::map<int, std::string> MAP_TEXTURE = {
	{E_2D_BACK, "Assets/Texture/PoseBg.png"},	//�w�i
};	//�|���S���ƃe�N�X�`���̑Ή��\
const std::map<int, std::array<std::string, E_SHADER_TYPE_MAX>> MAP_SHADER = {
	{E_2D_BACK, {"VsPose.cso", "PsPose.cso"}},	//�w�i
};	//�|���S���ƃV�F�[�_�[[���_, �s�N�Z��]�̑Ή��\

/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�Fconst CCamera* pCamera�F�J�����̃|�C���^
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CPose::CPose(const CCamera* pCamera)
	:m_pBgPs(nullptr)		//�w�i�p�s�N�Z���V�F�[�_
	,m_pBgVs(nullptr)		//�w�i�p���_�V�F�[�_
	//,m_pCamera(nullptr)		//�J�����Ǘ�
	,m_pCameraDef(nullptr)	//�^���J����
{
	// =============== �ϐ��錾 ===================
	int nCnt = 0;	//���[�v�J�E���g�p

	// =============== ���I�m�� ===================
	m_2dObj = {	//�X�V��
		new C2dPolygon(),				//�w�i�p
		new C2dPolygon(),				//�R�}���hA�p
		new C2dPolygon(),				//�R�}���hB�p
		new C2dPolygon(),				//�R�}���hC�p
	};	//���ʃ|���S��
	m_pBgVs = new VertexShader;			//���_�V�F�[�_�[
	m_pBgPs = new PixelShader;			//�s�N�Z���V�F�[�_�[
	m_pCameraDef = new CCameraDef();	//�^���J����
	
	// =============== ������ ===================
	SetCamera(pCamera);	//�J����������

	// =============== �t�@�C���ǂݍ��� ===================
	for (std::vector<C2dPolygon*>::iterator Iterator = m_2dObj.begin(); Iterator < m_2dObj.end(); Iterator++)
	{
		if (MAP_TEXTURE.size() > nCnt)	//map�̔z�񂪑��݂���Y����
		{
			(*Iterator)->SetTexture(MAP_TEXTURE.at(nCnt).c_str());	//�e�N�X�`���o�^
		}

		// =============== �J�E���^ ===================
		nCnt++;	//�J�E���g�i�s
	}
	m_pBGM = CSound::LoadSound(BGM_FILE_PASS.c_str(), true);	//BGM�̓ǂݍ���
	m_pSEHitHammer = CSound::LoadSound(SE_FILE_PASS.c_str());	//SE�̓ǂݍ���
		

	// =============== �V�F�[�_�[�ݒ� ===================
	m_pBgVs->Load(MAP_SHADER.at(E_2D_BACK)[E_SHADER_TYPE_VERTEX].c_str());	//���_�V�F�[�_�[�쐬
	m_pBgPs->Load(MAP_SHADER.at(E_2D_BACK)[E_SHADER_TYPE_PIXEL].c_str());	//�s�N�Z���V�F�[�_�[�쐬
	
	// =============== �V�F�[�_�[�o�^ ===================
	m_2dObj[E_2D_BACK]->SetVertexShader(m_pBgVs);	//���_�V�F�[�_�[�o�^
	m_2dObj[E_2D_BACK]->SetPixelShader(m_pBgPs);	//�s�N�Z���V�F�[�_�[�o�^
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
	SAFE_DELETE(m_pCameraDef);				//�^���J�����폜
	SAFE_DELETE(m_pBgPs);					//�s�N�Z���V�F�[�_�[�폜
	SAFE_DELETE(m_pBgVs);					//���_�V�F�[�_�[�폜
	for (std::vector<C2dPolygon*>::iterator Iterator = m_2dObj.end(); Iterator != m_2dObj.begin();)
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
	// =============== ���[�h���� ===================
	if (m_ucFlag & (E_FLAG_POSEMODE ^ 0xFF))	//�|�[�Y���[�h�̃t���O�������Ă��Ȃ�
	{

	}

	// =============== �ϐ��錾 ===================
	int nCnt = 0;	//���[�v�J�E���g�p

	// =============== �`�� ===================
	for (std::vector<C2dPolygon*>::iterator Iterator = m_2dObj.begin(); Iterator != m_2dObj.end(); Iterator++)
	{
		if (MAP_TEXTURE.size() > nCnt)	//map�̔z�񂪑��݂���Y����
		{
			(*Iterator)->Draw();	//���ʕ`��
		}

		// =============== �J�E���^ ===================
		nCnt++;	//�J�E���g�i�s
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

/* ========================================
	�J�����o�^�֐�
	----------------------------------------
	���e�Fnullptr�łȂ��J�����̃A�h���X���󂯎��g�p����B
	----------------------------------------
	����1�Fconst CCamera * pCamera�F�J�����̃|�C���^
	----------------------------------------
	�ߒl�F�Ȃ�
	======================================== */
void CPose::SetCamera(const CCamera * pCamera)
{
	// =============== �ϐ��錾 ===================
	int nCnt = 0;				//���[�v�J�E���g�p
	const CCamera* pCameraUse;	//�J�����A�h���X�ޔ�p

	// =============== ������ ===================
	if (pCamera)	//�k���`�F�b�N
	{
		pCameraUse = pCamera;		//�V�K�J�����o�^
	}
	else
	{
		pCameraUse = m_pCameraDef;	//�J������p
	}
	
	// =============== �J�����o�^ ===================
	for (std::vector<C2dPolygon*>::iterator Iterator = m_2dObj.begin(); Iterator < m_2dObj.end(); Iterator++)
	{
		if (MAP_TEXTURE.size() > nCnt)	//map�̔z�񂪑��݂���Y����
		{
			(*Iterator)->SetCamera(pCameraUse);	//�J�����o�^
		}

		// =============== �J�E���^ ===================
		nCnt++;	//�J�E���g�i�s
	}
}

/* ========================================
	�|�[�Y����֐�
	----------------------------------------
	���e�F�|�[�Y�����ǂ�����Ԃ�
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
	======================================== */
bool CPose::IsPose() const
{
	// =============== �� ===================
	return (m_ucFlag & E_FLAG_POSEMODE);	//�|�[�Y���[�h�t���O�������Ă��邩
}