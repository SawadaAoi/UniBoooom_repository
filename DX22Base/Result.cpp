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

========================================== */

// =============== �C���N���[�h ===================
#include "Result.h"	//���g�̃w�b�_
#include "DirectXTex/TextureLoad.h"
#include "Pos3d.h"
#include "Sprite.h"
#include "GameParameter.h"
#include "Input.h"


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
