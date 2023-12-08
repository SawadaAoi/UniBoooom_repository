/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�Q�[���^�C�}�[
	------------------------------------
	Timer.cpp
	------------------------------------
	�쐬��
		�A�F��
	�ύX����
	�E2023/11/14 cpp,�쐬 Tei
	�E2023/11/17 �J�n�����𕡐���ޒǉ��A�^�C�}�[�X�g�b�v���� Sawada
	�E2023/11/18 �^�C�}�[�`�揈���A���������̕`��֐��ǉ� Tei
	�E2023/11/22 �����_�̃^�C�}�[���擾�֐��ǉ� Tei
	�E2023/12/01 ���Ԍo�߂ŃX���C���̃p�����[�^��ύX���鏈�����C�� Sawada
	�E2023/12/07 �Q�[���p�����[�^����ꕔ�萔�ړ��E�Öق̌^�L���X�g���� takagi

========================================== */

// =============== �C���N���[�h ===================
#include "Timer.h"
#include "Sprite.h"
#include "GameParameter.h"

// =============== �萔��` =======================
const TPos2d<float> MINUTE_POS(565.0f, 45.0f);			//���̈ʒu�ݒ�
const TPos2d<float> SECOND_TENS_POS(640.0f, 45.0f);	//�\�̌��b�̈ʒu�ݒ�
const TPos2d<float> SECOND_ONE_POS(690.0f, 45.0f);		//��̌��b�̈ʒu�ݒ�
const TPos2d<float> TIME_BACKGROUND_POS(630.0f, 45.0f);	//�o�b�N�O���E���h�ʒu�ݒ�
const TPos2d<float> TIME_COLON_POS(602.5f, 45.0f);		//�R�����̈ʒu�ݒ�
const float TIME_BACK_GROUND_SIZE_X = 200.0f;			//�^�C�}�[�̃o�b�N�O�����h��X�̒����ݒ�
const float TIME_BACK_GROUND_SIZE_Y = -75.0f;			//�^�C�}�[�̃o�b�N�O�����h��Y�̒����ݒ�
const float TIME_COLON_SIZE_X = 35.0f;					//�^�C�}�[�̃R������X�̒����ݒ�
const float TIME_COLON_SIZE_Y = -35.0f;					//�^�C�}�[�̃R������Y�̒����ݒ�
#if MODE_GAME_PARAMETER
#else
const float SLM_PARAM_CHANGE_TIME[STATE_MAX] = { 60.0f, 120.0f, 180.0f };	// �o�ߎ��Ԃ̕b��
const int	SLM_CREATE_NUM[STATE_MAX] = { 20, 25, MAX_SLIME_NUM };	// �ő吶����
const int SLM_CREATE_INTERVAL_TIME[STATE_MAX] = { 1.0f, 1.5f, 1.5f };			// �����Ԋu
const float SLM_MOVE_ADD_SPEED[STATE_MAX] = { 1.0f, 1.1f, 1.2f };			// �ړ��X�s�[�h
#endif



/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CTimer::CTimer()
	: m_nTimeCnt(STAGE_TIME)
	, m_bStartFlg(false)
	, m_dWaitCnt(0)
	, m_bStopFlg(false)
	, m_pTextureBG(nullptr)
	, m_pTextureColon(nullptr)
	, m_pTextureNum(nullptr)
	, m_nMaxSlimeNum(SLM_CREATE_NUM[STATE_FIRST])
	, m_nSlimeCreateInterval(static_cast<int>(SLM_CREATE_INTERVAL_TIME[STATE_FIRST]))
	, m_fSlimeMoveSpeed(SLM_MOVE_ADD_SPEED[STATE_FIRST])
{
	//�����̃e�N�X�`���ǂލ���

	m_pTextureNum = new Texture();

	if (FAILED(m_pTextureNum->Create("Assets/Texture/numbers_v1/number.png")))
	{
		MessageBox(NULL, "number.png", "Error", MB_OK);
	}

	//�^�C�}�[�̗��e�N�X�`���ǂݍ���
	m_pTextureBG = new Texture;
	if (FAILED(m_pTextureBG->Create("Assets/Texture/timer_back_1.png")))
	{
		MessageBox(NULL, "timebackground.png", "Error", MB_OK);
	}

	m_pTextureColon = new Texture;
	if (FAILED(m_pTextureColon->Create("Assets/Texture/numbers_v1/colon.png")))
	{
		MessageBox(NULL, "colon.png", "Error", MB_OK);
	}
}
/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�j�����ɍs������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CTimer::~CTimer()
{

	SAFE_DELETE(m_pTextureColon);

	SAFE_DELETE(m_pTextureNum);

	SAFE_DELETE(m_pTextureBG);
}
/* ========================================
	�^�C�}�[�X�V�֐�
	----------------------------------------
	���e�F�^�C�}�[�̃J�E���g�_�E������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CTimer::Update()
{
	// �ҋ@���Ԃ̃`�F�b�N
	if (m_bStartFlg == false)
	{
		WaitTimeCheck();
		return;
	}

	// �^�C�}�[�X�g�b�v�̃`�F�b�N
	if (m_bStopFlg == true)
	{
		return;
	}
	// �^�C�}�[���Z
	m_nTimeCnt--;
	//���Ԃ�0�ɂȂ�����I��������
	if (m_nTimeCnt <= 0)
	{
		// TODO�Q�[���I������
	}

	ChangeSlimeParam();
}
/* ========================================
	�`��֐�
	----------------------------------------
	���e�F�^�C�}�[�̕`�揈��
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CTimer::Draw()
{
	//-----����UI�̕`��-----

	//�^�C�}�[��0�ɂȂ�����Areturn�i�\�����Ȃ��j
	if (m_nTimeCnt <= 0) return;
	//--���Ԃ̔w�i����(���f��)--
	DirectX::XMFLOAT4X4 timebackground[3];

	//���[���h�s���X��Y�݂̂��l�����č쐬(Z��10���炢�ɔz�u
	DirectX::XMMATRIX worldTimerBG = DirectX::XMMatrixTranslation(TIME_BACKGROUND_POS.x, TIME_BACKGROUND_POS.y, 0.0f);
	DirectX::XMStoreFloat4x4(&timebackground[0], DirectX::XMMatrixTranspose(worldTimerBG));
	//�r���[�s���2D���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��i�P�ʍs��͌��
	DirectX::XMStoreFloat4x4(&timebackground[1], DirectX::XMMatrixIdentity());

	//�v���W�F�N�V�����s��ɂ�2D�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	//���̍s���2D�̃X�N���[���̑����������܂�
	DirectX::XMMATRIX projTimerBG = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&timebackground[2], DirectX::XMMatrixTranspose(projTimerBG));

	//�X�v���C�g�̐ݒ�
	Sprite::SetWorld(timebackground[0]);
	Sprite::SetView(timebackground[1]);
	Sprite::SetProjection(timebackground[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(200.0f, -75.0f));
	Sprite::SetSize(DirectX::XMFLOAT2(TIME_BACK_GROUND_SIZE_X, TIME_BACK_GROUND_SIZE_Y));
	Sprite::SetTexture(m_pTextureBG);
	Sprite::Draw();

	//--�R�����̕`��--
	DirectX::XMFLOAT4X4 colon[3];
	//���[���h�s���X��Y�݂̂��l�����č쐬(Z��10���炢�ɔz�u
	DirectX::XMMATRIX worldColon = DirectX::XMMatrixTranslation(TIME_COLON_POS.x, TIME_COLON_POS.y, 0.0f);
	DirectX::XMStoreFloat4x4(&colon[0], DirectX::XMMatrixTranspose(worldColon));
	//�r���[�s���2D���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��i�P�ʍs��͌��
	DirectX::XMStoreFloat4x4(&colon[1], DirectX::XMMatrixIdentity());

	//�v���W�F�N�V�����s��ɂ�2D�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	//���̍s���2D�̃X�N���[���̑����������܂�
	DirectX::XMMATRIX projColon = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&colon[2], DirectX::XMMatrixTranspose(projColon));

	//�X�v���C�g�̐ݒ�
	Sprite::SetWorld(colon[0]);
	Sprite::SetView(colon[1]);
	Sprite::SetProjection(colon[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(25.0f, -25.0f));
	Sprite::SetSize(DirectX::XMFLOAT2(TIME_COLON_SIZE_X, TIME_COLON_SIZE_Y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pTextureColon);
	Sprite::Draw();
	//--���ԁi���������j�̕`��
	DrawNumber(MINUTE_POS, GetMinite());				//���̕b��
	DrawNumber(SECOND_TENS_POS, (GetSecond() / 10));	//�b�̏\�̌��̕`�� 
	DrawNumber(SECOND_ONE_POS, (GetSecond() % 10));		//�b�̈�̌��̕`��
}
/* ========================================
	�^�C�}�[�擾�֐�
	----------------------------------------
	���e�F�^�C�}�[�̕��v�Z
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F���Ԃ̕�
=========================================== */
int CTimer::GetMinite()
{
	int	minute = m_nTimeCnt / 3600;			//�� = ���^�C������i60�b * 60�t���[���j
	return minute;
}
/* ========================================
	�^�C�}�[�擾�֐�
	----------------------------------------
	���e�F�^�C�}�[�̕b���v�Z
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F���Ԃ̕b
=========================================== */
int CTimer::GetSecond()
{
	int second = (m_nTimeCnt / 60) % 60;	//�b = ���̕����𔲂��̎c��
	return second;
}



/* ========================================
	�^�C�}�[�J�n�֐�
	----------------------------------------
	���e�F�^�C�}�[���J�n����
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CTimer::TimeStart()
{
	m_nTimeCnt = STAGE_TIME;	// �f�t�H���g�̐������Ԃ��Z�b�g
	m_bStartFlg = true;			// �҂����ԂȂ�
}
/* ========================================
	�^�C�}�[�J�n�֐�
	----------------------------------------
	���e�F�^�C�}�[���J�n����
	----------------------------------------
	����1�F��������(�b)
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CTimer::TimeStart(float maxTime)
{
	m_nTimeCnt = int(maxTime * 60);	// �������Ԃ��Z�b�g
	m_bStartFlg = true;			// �҂����ԂȂ�
}
/* ========================================
	�^�C�}�[�J�n�֐�
	----------------------------------------
	���e�F�^�C�}�[���J�n����
	----------------------------------------
	����1�F��������(�b)
	����2�F�J�n�ҋ@����(�b)
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CTimer::TimeStart(float maxTime, float waitTime)
{
	m_dWaitCnt = int(waitTime * 60);	// �҂�����
	m_nTimeCnt = int(maxTime * 60);	// ��������
	m_bStartFlg = false;		// �҂����Ԃ���
}
/* ========================================
	�^�C�}�[��~�֐�
	----------------------------------------
	���e�F�^�C�}�[���X�g�b�v����
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CTimer::TimeStop()
{
	m_bStopFlg = true;
}
/* ========================================
	�^�C�}�[�ĊJ�֐�
	----------------------------------------
	���e�F�X�g�b�v�����^�C�}�[���Ăѓ�����
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CTimer::TimeRestart()
{
	m_bStopFlg = false;
}
/* ========================================
	�^�C�}�[���������`��֐�
	----------------------------------------
	���e�F�^�C�}�[�̕`�敔���`�悷��
	----------------------------------------
	����1�F�ʒu
	����2�F�`�悷�鐔��
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CTimer::DrawNumber(TPos2d<float> pos, int number)
{
	DirectX::XMFLOAT4X4 time[3];
	//���[���h�s���X��Y�݂̂��l�����č쐬(Z��10���炢�ɔz�u
	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(pos.x, pos.y, 0.0f);
	DirectX::XMStoreFloat4x4(&time[0], DirectX::XMMatrixTranspose(world));
	//�r���[�s���2D���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��i�P�ʍs��͌��
	DirectX::XMStoreFloat4x4(&time[1], DirectX::XMMatrixIdentity());

	//�v���W�F�N�V�����s��ɂ�2D�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	//���̍s���2D�̃X�N���[���̑����������܂�
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&time[2], DirectX::XMMatrixTranspose(proj));

	//�X�v���C�g�̐ݒ�
	Sprite::SetWorld(time[0]);
	Sprite::SetView(time[1]);
	Sprite::SetProjection(time[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(50.0f, -50.0f));

	//sprite�V�[�g�̏㕔���\���i0~4�j
	if ((number % 10) < 5)
	{
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f * number, 0.0f));
	}
	//sprite�V�[�g�̉������\���i5~9�j
	else
	{
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f * number, 0.5f));
	}
	Sprite::SetUVScale(DirectX::XMFLOAT2(0.2f, 0.5f));
	Sprite::SetTexture(m_pTextureNum);
	Sprite::Draw();
}

/* ========================================
	�^�C�}�[�ҋ@���ԃ`�F�b�N�֐�
	----------------------------------------
	���e�F�ݒ肵���ҋ@���Ԃ��o�߂��Ă��邩�m�F����
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CTimer::WaitTimeCheck()
{
	m_dWaitCnt--;	// �҂����Ԃ����Z
	// 0�ɂȂ�����^�C���J�E���g�J�n
	if (m_dWaitCnt <= 0)
	{
		m_bStartFlg = true;
	}

}


/* ========================================
	�X���C���p�����[�^�ύX�֐�
	----------------------------------------
	���e�F�o�ߎ��Ԃɂ���ăX���C���̃p�����[�^��ύX����
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CTimer::ChangeSlimeParam()
{
	int elapsedTimeFrame = STAGE_TIME - m_nTimeCnt;

	// ���i�K
	if (elapsedTimeFrame < SLM_PARAM_CHANGE_TIME[STATE_FIRST] * 60)
	{
		m_nMaxSlimeNum			= SLM_CREATE_NUM[STATE_FIRST];
		m_nSlimeCreateInterval	= static_cast<int>(SLM_CREATE_INTERVAL_TIME[STATE_FIRST] * 60);
		m_fSlimeMoveSpeed		= SLM_MOVE_ADD_SPEED[STATE_FIRST];

	}
	// ���i�K
	else if (elapsedTimeFrame < SLM_PARAM_CHANGE_TIME[STATE_SECOND] * 60)
	{
		m_nMaxSlimeNum			= SLM_CREATE_NUM[STATE_SECOND];
		m_nSlimeCreateInterval	= static_cast<int>(SLM_CREATE_INTERVAL_TIME[STATE_SECOND] * 60);
		m_fSlimeMoveSpeed = SLM_MOVE_ADD_SPEED[STATE_SECOND];


	}
	// ��O�i�K
	else
	{
		m_nMaxSlimeNum			= SLM_CREATE_NUM[STATE_THIRD];
		m_nSlimeCreateInterval	= static_cast<int>(SLM_CREATE_INTERVAL_TIME[STATE_THIRD] * 60);
		m_fSlimeMoveSpeed		= SLM_MOVE_ADD_SPEED[STATE_THIRD];


	}
}


/* ========================================
   �������Ԏ擾�֐�
   ----------------------------------------
   ���e�F�������Ԃ̃|�C���^���擾
   ----------------------------------------
   �����F����
   ----------------------------------------
   �ߒl�F�������Ԃ̃����o�ϐ��̃|�C���^
======================================== */
int * CTimer::GetTimePtr()
{
	return &m_nTimeCnt;
}

/* ========================================
	�o�ߎ��Ԏ擾�֐�
	----------------------------------------
	���e�F���݂̃^�C�}�[�̌o�ߎ��Ԃ��擾
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�Fint�@�o�ߎ���
=========================================== */
int CTimer::GetElapsedFrame()
{
	return STAGE_TIME - m_nTimeCnt;
}

/* ========================================
	�X���C���ύX�ő吶�����擾�֐�
	----------------------------------------
	���e�F�X���C���ő吶�����擾
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�Fint �X���C���ő吶����
=========================================== */
int CTimer::GetMaxSlimeNum()
{
	
	return m_nMaxSlimeNum;
}

/* ========================================
	�X���C���ύX�����Ԋu�擾�֐�
	----------------------------------------
	���e�F�X���C���̐����Ԋu���擾
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�Fint �����Ԋu�̕b��
=========================================== */
int CTimer::GetSlimeCreateInterval()
{
	return m_nSlimeCreateInterval;
}

/* ========================================
	�X���C���ύX�X�s�[�h�擾�֐�
	----------------------------------------
	���e�F�X���C���̃X�s�[�h���擾
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�Ffloat �X���C���̃X�s�[�h
=========================================== */
float CTimer::GetSlimeMoveSpeed()
{
	return m_fSlimeMoveSpeed;
}
