/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�|�[�Y��ʎ���
	---------------------------------------
	Pause.cpp

	�쐬��	takagi

	�ύX����
	�E2023/12/01 ���� takagi
	�E2023/12/04 ���� takagi
	�E2023/12/05 ���� takagi
	�E2023/12/06 pose��pause�C���A�|�[�Y�����\�� takagi

========================================== */

// =============== �C���N���[�h ===================
#include "Pause.h"		//���g�̃w�b�_
#include <map>			//�֌W���R���e�i
#include <array>		//�z��
#include "CameraDef.h"	//�^���J����
#include "Input.h"		//�L�[����

// =============== �񋓌^��` ===================
enum E_2D
{
	E_2D_BACK,		//�w�i
	E_2D_PA,		//�|�[�Y�́h�|�h
	E_2D_U,			//�|�[�Y�́h�[�h
	E_2D_SE,		//�|�[�Y�́h�Y�h
	E_2D_CONTINUE,	//�p���R�}���h
	E_2D_FINISH,	//�I���R�}���h
	E_2D_MAX,		//�v�f��
};	//2D�̃I�u�W�F�N�g
enum E_COMMAND
{
	E_COMMAND_CONTINUE,	//�Q�[���𑱂���
	E_COMMAND_FINISH,	//�Q�[������߂�
	E_COMMAND_MAX,		//�v�f��
};	//�R�}���h����
enum E_SHADER_TYPE
{
	E_SHADER_TYPE_VERTEX,	//���_�V�F�[�_�[
	E_SHADER_TYPE_PIXEL,	//�s�N�Z���V�F�[�_�[
	E_SHADER_TYPE_MAX,		//�v�f��
};	//�V�F�[�_�[�̎��

// =============== �萔��` ===================
///<summary>�Q�[���p�����[�^�p
///<para>�萔�̈ꕔ���������悤�ɐ؂�o��������</para>
///</summary>
#include "GameParameter.h"
#if GAME_PARAMETER
const float COMMAND_SPACE_HALF = 85.0f;	//�R�}���h���m�̏c�̊�
const float PAUSE_Y = 520.0f;			//�|�[�Y�\�������Sy�ʒu
const float PAUSE_SPACE = 85.0f;		//�|�[�Y�\�L�̉��̊�
const float COMMAND_WIDTH = 320.0f;		//�R�}���h�c��
const float COMMAND_HEIGHT = 70.0f;		//�R�}���h����
#endif // !GAME_PARAMETER


const std::string BGM_FILE_PASS("Assets/Sound/BGM/BGM_maou.mp3");
const std::string SE_FILE_PASS("Assets/Sound/SE/Smash.mp3");
const std::map<int, std::string> MAP_TEXTURE = {
	{E_2D_BACK, "Assets/Texture/Pause/PauseBg.png"},			//�w�i
	{E_2D_PA, "Assets/Texture/Pause/Pause_po.png"},													//�|�[�Y�́h�|�h
	{E_2D_U, "Assets/Texture/Pause/Pause_-.png"},													//�|�[�Y�́h�[�h
	{E_2D_SE, "Assets/Texture/Pause/Pause_zu.png"},													//�|�[�Y�́h�Y
	{E_2D_CONTINUE, "Assets/Texture/Pause/Pause_Continue.png"},	//�p���R�}���h
	{E_2D_FINISH, "Assets/Texture/Pause/Pause_Finish.png"},	//�R�}���hB
};	//�|���S���ƃe�N�X�`���̑Ή��\
const std::map<int, TPos3d<float>> MAP_POS = {	//�X�V��
	{E_2D_BACK, {static_cast<float>(SCREEN_WIDTH) / 2.0f, static_cast<float>(SCREEN_HEIGHT) / 2.0f, 0.0f}},					//�w�i
	{E_2D_PA, {static_cast<float>(SCREEN_WIDTH) / 2.0f - CHARA_SPACE, CHARA_Y, 0.0f}},										//�|�[�Y�́h�|�h
	{E_2D_U, {static_cast<float>(SCREEN_WIDTH) / 2.0f, CHARA_Y, 0.0f}},														//�|�[�Y�́h�[�h
	{E_2D_SE, {static_cast<float>(SCREEN_WIDTH) / 2.0f + CHARA_SPACE, CHARA_Y, 0.0f}},										//�|�[�Y�́h�Y�h
	{E_2D_CONTINUE, {static_cast<float>(SCREEN_WIDTH) / 2.0f, static_cast<float>(SCREEN_HEIGHT) / 2.0f + COMMAND_SPACE_HALF, 0.0f}},	//�p���R�}���h
	{E_2D_FINISH, {static_cast<float>(SCREEN_WIDTH) / 2.0f, static_cast<float>(SCREEN_HEIGHT) / 2.0f - COMMAND_SPACE_HALF, 0.0f}},	//�I���R�}���h
};	//�|���S���Ə������W�̑Ή��\
const std::map<int, TPos3d<float>> MAP_SIZE = {	//�X�V��
	{E_2D_BACK, {static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT), 0.0f}},	//�w�i
	{E_2D_PA, {CHARA_WIDTH, CHARA_HEIGHT, 0.0f}},												//�|�[�Y�́h�|�h
	{E_2D_U, {CHARA_WIDTH, CHARA_HEIGHT, 0.0f}},												//�|�[�Y�́h�[�h
	{E_2D_SE, {CHARA_WIDTH, CHARA_HEIGHT, 0.0f}},												//�|�[�Y�́h�Y�h
	{E_2D_CONTINUE, {COMMAND_WIDTH, COMMAND_HEIGHT, 0.0f}},										//�p���R�}���h
	{E_2D_FINISH, {COMMAND_WIDTH, COMMAND_HEIGHT, 0.0f}},										//�I���R�}���h
};	//�|���S���Ə����T�C�Y�̑Ή��\
const std::map<int, std::array<std::string, E_SHADER_TYPE_MAX>> MAP_SHADER = {
	{E_2D_BACK, {"Assets/Shader/VsPause.cso", "Assets/Shader/PsPause.cso"}},	//�w�i
	//TODO:���̐�I�u�W�F�N�g��ǉ������Ƃ��ɓǂݍ��ރV�F�[�_�[�����ꂽ�肷�鋰�ꂪ����̂Œʏ펞�p�̃V�F�[�_�[������ēǂݍ��܂���
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
CPause::CPause(const CCamera* pCamera)
	:m_ucFlag(0x00)			//�t���O
	,m_pBgPs(nullptr)		//�w�i�p�s�N�Z���V�F�[�_
	,m_pBgVs(nullptr)		//�w�i�p���_�V�F�[�_
	//,m_pCamera(nullptr)		//�J�����Ǘ�
	,m_pCameraDef(nullptr)	//�^���J����
{
	// =============== �ϐ��錾 ===================
	int nCnt = 0;	//���[�v�J�E���g�p

	// =============== ���I�m�� ===================
	m_2dObj = {	//�X�V��
		new C2dPolygon(),				//�w�i�p
		new C2dPolygon(),				//�w�i�p
		new C2dPolygon(),				//�|�̎��p
		new C2dPolygon(),				//�[�̎��p
		new C2dPolygon(),				//�Y�̎��p
		new C2dPolygon(),				//�I���R�}���h�p
	};	//���ʃ|���S��
	m_pBgVs = new VertexShader;			//���_�V�F�[�_�[
	m_pBgPs = new PixelShader;			//�s�N�Z���V�F�[�_�[
	m_pCameraDef = new CCameraDef();	//�^���J����
	
	// =============== ������ ===================
	SetCamera(pCamera);	//�J����������
	for (std::vector<C2dPolygon*>::iterator Iterator = m_2dObj.begin(); Iterator != m_2dObj.end(); Iterator++)
	{
		if (MAP_POS.size() > nCnt)	//map�̔z�񂪑��݂���Y����
		{
			(*Iterator)->SetPos({ MAP_POS.at(nCnt) });	//�ʒu������
		}
		if (MAP_SIZE.size() > nCnt)	//map�̔z�񂪑��݂���Y����
		{
			(*Iterator)->SetSize({ MAP_SIZE.at(nCnt) });	//�T�C�Y������
		}
		if (MAP_TEXTURE.size() > nCnt)	//map�̔z�񂪑��݂���Y����
		{
			(*Iterator)->SetTexture(MAP_TEXTURE.at(nCnt).c_str());	//�e�N�X�`���o�^
		}

		// =============== �J�E���^ ===================
		nCnt++;	//�J�E���g�i�s
	}

	// =============== �t�@�C���ǂݍ��� ===================
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
CPause::~CPause()
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
void CPause::Update()
{
	// =============== �L�[���� ===================
	// =============== ���� ===================
	// =============== �J�[�\���ړ� ===================

	// =============== �I���m�� ===================
	if (m_ucFlag & E_FLAG_DECIDE_COMMAND)	//�R�}���h���莞
	{
		// =============== �I����Ԕ��� ===================
		if (m_ucFlag & E_FLAG_COMMAND_CONTINUE)	//�p��
		{
			// =============== �t���O���� ===================
			DownFlag(E_FLAG_PAUSEMODE | E_FLAG_COMMAND_CONTINUE);	//�|�[�Y�𒆒f���A�Q�[�����ĊJ����
		}
		if (m_ucFlag & E_FLAG_COMMAND_FINISH)	//�p��
		{
			// =============== �t���O���� ===================
			DownFlag(E_FLAG_PAUSEMODE | E_FLAG_COMMAND_FINISH);	//�|�[�Y�𒆒f����
			UpFlag(E_FLAG_CALL_FINISH);							//�Q�[���̏I���\��
		}
	}
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
void CPause::Draw()
{
	// =============== ���[�h���� ===================
	if (!(m_ucFlag & E_FLAG_PAUSEMODE))	//�|�[�Y���[�h�̃t���O�������Ă��Ȃ�
	{
		// =============== �I�� ==================
		return;	//�������f
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
bool CPause::IsFin() const
{
	// =============== �� ===================
	return (m_ucFlag & E_FLAG_CALL_FINISH);	//�I���t���O
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
void CPause::SetCamera(const CCamera * pCamera)
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
bool CPause::IsPause() const
{
	// =============== �� ===================
	return (m_ucFlag & E_FLAG_PAUSEMODE);	//�|�[�Y���[�h�t���O�������Ă��邩
}

/* ========================================
	�N���֐�
	----------------------------------------
	���e�F�|�[�Y���[�h���N������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
	======================================== */
void CPause::Boot()
{
	// =============== �t���O���� ===================
	UpFlag(E_FLAG_PAUSEMODE);	//�|�[�Y�J�n
}

/* ========================================
	�t���O�I���֐�
	-------------------------------------
	���e�F�����ɑΉ������t���O���N����
	-------------------------------------
	����1�Fconst unsigned char & ucBitFlag�F�Ώۃt���O
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CPause::UpFlag(const unsigned char & ucBitFlag)
{
	// =============== ��� ===================
	m_ucFlag |= ucBitFlag;	//�t���O����
}

/* ========================================
	�t���O�I�t�֐�
	-------------------------------------
	���e�F�����ɑΉ������t���O���~�낷
	-------------------------------------
	����1�Fconst unsigned char & ucBitFlag�F�Ώۃt���O
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CPause::DownFlag(const unsigned char & ucBitFlag)
{
	// =============== ��� ===================
	m_ucFlag &= (ucBitFlag ^ 0xFF);	//�t���O����
}

/* ========================================
	�t���O�X�C�b�`�֐�
	-------------------------------------
	���e�F�����ɑΉ������t���O�̔��]
	-------------------------------------
	����1�Fconst unsigned char & ucBitFlag�F�Ώۃt���O
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CPause::SetFlag(const unsigned char & ucBitFlag)
{
	// =============== ��� ===================
	m_ucFlag ^= ucBitFlag;	//�t���O����
}