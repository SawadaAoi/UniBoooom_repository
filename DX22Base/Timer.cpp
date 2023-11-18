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

========================================== */

// =============== �C���N���[�h ===================
#include "Timer.h"
#include "Sprite.h"

// =============== �萔��` =======================



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
	: m_nTimeCnt(0)
	, m_bStartFlg(false)
	, m_dWaitCnt(0)
	, m_bStopFlg(false)
	, m_pTimeBackground(nullptr)
	, m_pShowColon(nullptr)
	, m_pShowTimer(nullptr)
{
	//�����̃e�N�X�`���ǂލ���
	
	m_pShowTimer = new Texture();
	
	if (FAILED(m_pShowTimer->Create("Assets/Texture/numbers_v1/number.png")))
	{
		MessageBox(NULL, "�����ǂލ���", "Error", MB_OK);
	}
	

	//�^�C�}�[�̗��e�N�X�`���ǂݍ���
	m_pTimeBackground = new Texture;
	if (FAILED(m_pTimeBackground->Create("Assets/Texture/time_background.png")))
	{
		MessageBox(NULL, "BG�ǂލ���", "Error", MB_OK);
	}
	
	m_pShowColon = new Texture;
	if (FAILED(m_pShowColon->Create("Assets/Texture/colon.png")))
	{
		MessageBox(NULL, "colon�ǂލ���", "Error", MB_OK);
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
	
	SAFE_DELETE(m_pShowTimer);
	
	SAFE_DELETE(m_pTimeBackground);
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
	//---����UI�̕`��---
	//���Ԃ̗�����(���f��)
	DirectX::XMFLOAT4X4 timebackground[3];

	//���[���h�s���X��Y�݂̂��l�����č쐬(Z��10���炢�ɔz�u
	DirectX::XMMATRIX worldTimerBG = DirectX::XMMatrixTranslation(TIME_BACKGROUND_X, TIME_BACKGROUND_Y, TIME_BACKGROUND_Z);
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
	Sprite::SetTexture(m_pTimeBackground);
	Sprite::Draw();

	//�R�����̕`��
	DirectX::XMFLOAT4X4 colon[3];

	//���[���h�s���X��Y�݂̂��l�����č쐬(Z��10���炢�ɔz�u
	DirectX::XMMATRIX worldColon = DirectX::XMMatrixTranslation(TIME_COLON_X, TIME_COLON_Y, TIME_COLON_Z);
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
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pShowColon);
	Sprite::Draw();
	//���̕b��
	DirectX::XMFLOAT4X4 minute[3];
	
	//���[���h�s���X��Y�݂̂��l�����č쐬(Z��10���炢�ɔz�u
	DirectX::XMMATRIX worldMinute = DirectX::XMMatrixTranslation(MINUTEPOS_X, MINUTEPOS_Y, MINUTEPOS_Z);
	DirectX::XMStoreFloat4x4(&minute[0], DirectX::XMMatrixTranspose(worldMinute));
	
	//�r���[�s���2D���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��i�P�ʍs��͌��
	DirectX::XMStoreFloat4x4(&minute[1], DirectX::XMMatrixIdentity());
	
	//�v���W�F�N�V�����s��ɂ�2D�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	//���̍s���2D�̃X�N���[���̑����������܂�
	DirectX::XMMATRIX projMinute = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&minute[2], DirectX::XMMatrixTranspose(projMinute));
	
	//�X�v���C�g�̐ݒ�
	Sprite::SetWorld(minute[0]);
	Sprite::SetView(minute[1]);
	Sprite::SetProjection(minute[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(50.0f, -50.0f));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f*GetMinite(), 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(0.2f, 0.5f));
	Sprite::SetTexture(m_pShowTimer);
	Sprite::Draw();

	//�\�̌��b�̕`��
	DirectX::XMFLOAT4X4 secondTen[3];

	//���[���h�s���X��Y�݂̂��l�����č쐬(Z��10���炢�ɔz�u
	DirectX::XMMATRIX worldSecondTen = DirectX::XMMatrixTranslation(SECOND_TENS_DIGIT_X, SECOND_TENS_DIGIT_Y, SECOND_TENS_DIGIT_Z);
	DirectX::XMStoreFloat4x4(&secondTen[0], DirectX::XMMatrixTranspose(worldSecondTen));

	//�r���[�s���2D���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��i�P�ʍs��͌��
	DirectX::XMStoreFloat4x4(&secondTen[1], DirectX::XMMatrixIdentity());

	//�v���W�F�N�V�����s��ɂ�2D�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	//���̍s���2D�̃X�N���[���̑����������܂�
	DirectX::XMMATRIX projSecondTen = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&secondTen[2], DirectX::XMMatrixTranspose(projSecondTen));

	//�X�v���C�g�̐ݒ�
	Sprite::SetWorld(secondTen[0]);
	Sprite::SetView(secondTen[1]);
	Sprite::SetProjection(secondTen[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(50.0f, -50.0f));
	if (GetSecond() / 10 == 5)
	{
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f*(GetSecond() / 10), 0.5f));
	}
	else
	{
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f*(GetSecond() / 10), 0.0f));

	}
	Sprite::SetUVScale(DirectX::XMFLOAT2(0.2f, 0.5f));
	Sprite::SetTexture(m_pShowTimer);
	Sprite::Draw();

	//��̌��b�̕`��
	DirectX::XMFLOAT4X4 second[3];

	//���[���h�s���X��Y�݂̂��l�����č쐬(Z��10���炢�ɔz�u
	DirectX::XMMATRIX worldSecond = DirectX::XMMatrixTranslation(SECOND_UNITS_DIGIT_X, SECOND_UNITS_DIGIT_Y, SECOND_UNITS_DIGIT_Z);
	DirectX::XMStoreFloat4x4(&second[0], DirectX::XMMatrixTranspose(worldSecond));

	//�r���[�s���2D���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��i�P�ʍs��͌��
	DirectX::XMStoreFloat4x4(&second[1], DirectX::XMMatrixIdentity());

	//�v���W�F�N�V�����s��ɂ�2D�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	//���̍s���2D�̃X�N���[���̑����������܂�
	DirectX::XMMATRIX projSecond = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&second[2], DirectX::XMMatrixTranspose(projSecond));

	//�X�v���C�g�̐ݒ�
	Sprite::SetWorld(second[0]);
	Sprite::SetView(second[1]);
	Sprite::SetProjection(second[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(50.0f, -50.0f));
	if (GetSecond()-(GetSecond()/10*10) >= 5)
	{
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f*(GetSecond() % 5), 0.5f));
	}
	else
	{
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f*(GetSecond() % 5), 0.0f));
	}
	Sprite::SetUVScale(DirectX::XMFLOAT2(0.2f, 0.5f));
	Sprite::SetTexture(m_pShowTimer);
	Sprite::Draw();
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
	int second = ( m_nTimeCnt / 60 ) % 60;	//�b = ���̕����𔲂��̎c��

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
	m_nTimeCnt = maxTime * 60;	// �������Ԃ��Z�b�g
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
	m_dWaitCnt = waitTime * 60;	// �҂�����
	m_nTimeCnt = maxTime * 60;	// ��������
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
