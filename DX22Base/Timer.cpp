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
const int STAGE_TIME = 180 * 60;	//�X�e�[�W�������ԁi�b*�t���[���j
const float MINUTEPOS_X = 565.0f;	//���̈ʒu.X
const float MINUTEPOS_Y = 25.0f;	//���̈ʒu.Y
const float MINUTEPOS_Z = 10.0f;	//���̈ʒu.Z
const float SECOND_TENS_DIGIT_X = 640.0f;	//�\�̌��b�̈ʒu.X
const float SECOND_TENS_DIGIT_Y = 25.0f;	//�\�̌��b�̈ʒu.Y
const float SECOND_TENS_DIGIT_Z = 10.0f;	//�\�̌��b�̈ʒu.Z
const float SECOND_UNITS_DIGIT_X = 690.0f;	//��̌��b�̈ʒu.X
const float SECOND_UNITS_DIGIT_Y = 25.0f;	//��̌��b�̈ʒu.Y
const float SECOND_UNITS_DIGIT_Z = 10.0f;	//��̌��b�̈ʒu.Z

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
{
	//�����̃e�N�X�`���ǂލ���
	for (int i = 0; i < NUM_OF_NUMBER; i++)
	{
		m_pShowTimer[i] = new Texture();
	}
	if (FAILED(m_pShowTimer[0]->Create("Assets/Texture/numbers_v1/num0_v1.png")))
	{
		MessageBox(NULL, "0�ǂލ���", "Error", MB_OK);
	}
	else if (FAILED(m_pShowTimer[1]->Create("Assets/Texture/numbers_v1/num1_v1.png")))
	{
		MessageBox(NULL, "1�ǂލ���", "Error", MB_OK);
	}
	else if (FAILED(m_pShowTimer[2]->Create("Assets/Texture/numbers_v1/num2_v1.png")))
	{
		MessageBox(NULL, "2�ǂލ���", "Error", MB_OK);
	}
	else if (FAILED(m_pShowTimer[3]->Create("Assets/Texture/numbers_v1/num3_v1.png")))
	{
		MessageBox(NULL, "3�ǂލ���", "Error", MB_OK);
	}
	else if (FAILED(m_pShowTimer[4]->Create("Assets/Texture/numbers_v1/num4_v1.png")))
	{
		MessageBox(NULL, "4�ǂލ���", "Error", MB_OK);
	}
	else if (FAILED(m_pShowTimer[5]->Create("Assets/Texture/numbers_v1/num5_v1.png")))
	{
		MessageBox(NULL, "5�ǂލ���", "Error", MB_OK);
	}
	else if (FAILED(m_pShowTimer[6]->Create("Assets/Texture/numbers_v1/num6_v1.png")))
	{
		MessageBox(NULL, "6�ǂލ���", "Error", MB_OK);
	}
	else if (FAILED(m_pShowTimer[7]->Create("Assets/Texture/numbers_v1/num7_v1.png")))
	{
		MessageBox(NULL, "7�ǂލ���", "Error", MB_OK);
	}
	else if (FAILED(m_pShowTimer[8]->Create("Assets/Texture/numbers_v1/num8_v1.png")))
	{
		MessageBox(NULL, "8�ǂލ���", "Error", MB_OK);
	}
	else if (FAILED(m_pShowTimer[9]->Create("Assets/Texture/numbers_v1/num9_v1.png")))
	{
		MessageBox(NULL, "9�ǂލ���", "Error", MB_OK);
	}
	else
	{
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
	for (int i = 0; i < NUM_OF_NUMBER; i++)
	{
		if(m_pShowTimer[i])
		SAFE_DELETE(m_pShowTimer[i]);
	}
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
	Sprite::SetTexture(m_pShowTimer[GetMinite()]);
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
	Sprite::SetTexture(m_pShowTimer[GetSecond()/10]);
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
	Sprite::SetTexture(m_pShowTimer[(GetSecond()%10)]);
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
