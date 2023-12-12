/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	���U���g�V�[������
	---------------------------------------
	Result.cpp

	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/11/16 ���� takagi
	�E2023/11/20 ���e�N�X�`���\���A��ʑJ�� nieda
	�E2023/11/23 �R���g���[���[�ɑΉ� nieda
	�E2023/11/24 �R�����g�A�萔��`�A�񋓒ǉ� nieda
	�E2023/12/08 �V�[���J�ڗp�ɕϐ��ǉ� takagi
	�E2023/12/11 ���щ��\�� takagi

========================================== */

// =============== �C���N���[�h ===================
#include "Result.h"	//���g�̃w�b�_
#include "DirectXTex/TextureLoad.h"	
#include "Pos3d.h"
#include "Sprite.h"
#include "GameParameter.h"
#include "Input.h"
#include <array>					//�z��
#include <map>						//�A�z�^�R���e�i
#include "Defines.h"				//��ʃT�C�Y���

// =============== �񋓒�` ===================
enum E_CORD
{
	//E_CORD_RESULT,	//���U���g
	E_CORD_ALIVE,	//��������
	E_CORD_KILL,	//������
	E_CORD_SCORE,	//�X�R�A
};	//�R�[�h

// =============== �萔��` ===================
const std::map<E_CORD, std::string> MAP_STRING = {
	//{E_CORD_RESULT,	"���U���g"},			//���U���g
	{E_CORD_ALIVE, "�������ԁF"},			//��������
	{E_CORD_KILL, "�X���C�����������F"},	//������
	{E_CORD_SCORE, "TOTAL SCORE�F"},		//�X�R�A
};	//�����̘A�z�R���e�i
const std::map<E_CORD, DirectX::XMFLOAT2> MAP_POS = {
	//{E_CORD_RESULT,	{static_cast<float>SCREEN_WIDTH / 2.0f - MAP_STRING.at(E_CORD_RESULT).length(), 10.0f}},	//���U���g
	{E_CORD_ALIVE, {0.0f, 360.0f}},		//��������
	{E_CORD_KILL, {0.0f, 410.0f}},		//������
	{E_CORD_SCORE, {0.0f, 460.0f}},		//�X�R�A
};	//�ʒu�̘A�z�R���e�i

/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CResult::CResult()
{
	// ���U���g�摜�Ǎ�
	m_pTexture[E_RESULT_RESULT] = new Texture();
	if (FAILED(m_pTexture[E_RESULT_RESULT]->Create("Assets/Texture/gamestart.png")))
	{
		MessageBox(NULL, "Result gamestart.png", "Error", MB_OK);
	}

	// ���U���g��ʉ����{�^���w���摜�Ǎ�
	m_pTexture[E_RESULT_BUTTON] = new Texture();
	if (FAILED(m_pTexture[E_RESULT_BUTTON]->Create("Assets/Texture/pre_result.png")))
	{
		MessageBox(NULL, "Result pre_result.png", "Error", MB_OK);
	}

	// �f�[�^�󂯌p��
	m_Data.Load();	//�t�@�C���ɏオ���Ă������ǂݍ���

	// =============== �t�H���g�f�[�^�쐬 ===================
	m_Font.SetFontResult();	//��p������
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
CResult::~CResult()
{
	// �j������
	for (int i = 0; i >= E_RESULT_MAX; ++i)
	{
		SAFE_DELETE(m_pTexture[i]);
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
void CResult::Update()
{
	// �X�y�[�X�L�[�����������A�܂��̓R���g���[����B�{�^������������ 
	if (IsKeyTrigger(VK_SPACE) || IsKeyTriggerController(BUTTON_B))
	{
		m_bFinish = true;	// �^�C�g���V�[���I���t���OON
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
void CResult::Draw()
{
	// �^�C�g���摜�\��
	Draw2d(TEXTURE_TITLE_TITLE_POSX
		, TEXTURE_TITLE_TITLE_POSY
		, TEXTURE_TITLE_TITLE_WIDTH
		, TEXTURE_TITLE_TITLE_HEIGHT
		, m_pTexture[E_RESULT_RESULT]);

	// �^�C�g����ʉ����{�^���w���摜�\��
	Draw2d(TEXTURE_TITLE_BUTTON_POSX
		, TEXTURE_TITLE_BUTTON_POSY
		, TEXTURE_TITLE_BUTTON_WIDTH
		, TEXTURE_TITLE_BUTTON_HEIGHT
		, m_pTexture[E_RESULT_BUTTON]);

	// =============== �t�H���g�Z�b�g ===================
	DirectWrite::SetFont(&m_Font);	//��p�t�H���g���Z�b�g

	// =============== �`��n ===============
	//DirectWrite::DrawString(MAP_STRING.at(E_CORD_RESULT), MAP_POS.at(E_CORD_RESULT));										//���U���g
	DirectWrite::DrawString(MAP_STRING.at(E_CORD_ALIVE) + std::to_string(m_Data.GetMinute()) + "�F" + std::to_string(m_Data.GetSecond()) + "�F"
		+ std::to_string(m_Data.GetCommaSecond()), MAP_POS.at(E_CORD_ALIVE));												//��������
	DirectWrite::DrawString(MAP_STRING.at(E_CORD_KILL) + std::to_string(m_Data.nKill), MAP_POS.at(E_CORD_KILL));			//������
	DirectWrite::DrawString(MAP_STRING.at(E_CORD_SCORE) + std::to_string(m_Data.nTotalScore), MAP_POS.at(E_CORD_SCORE));	//�X�R�A

	// =============== �I�� ===================
	DirectWrite::SetFont(&m_FontDef);	//�f�t�H���g�t�H���g�Ƀ��Z�b�g
}

/* ========================================
	��ރQ�b�^
	----------------------------------------
	���e�F���g�����U���g�V�[���ł��邱�Ƃ�����
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F���g�̎��
=========================================== */
CResult::E_TYPE CResult::GetType() const
{
	// =============== �� ===================
	return CResult::E_TYPE_RESULT;	//���g�̎��
}

/* ========================================
	���V�[���Q�b�^
	----------------------------------------
	���e�F�J�ڂ������V�[��������������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�J�ڐ�V�[���̎��
=========================================== */
CResult::E_TYPE CResult::GetNext() const
{
	// =============== �� ===================
	return CResult::E_TYPE_TITLE;	//�J�ڐ�V�[���̎��
}