/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�t�F�[�h����
	------------------------------------
	Fade.cpp
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/11/18 ���� takagi
	�E2023/11/19 18�̑��� takagi
	�E2023/11/20 ���� takagi

========================================== */

// =============== �f�o�b�O���[�h ===================
#if _DEBUG
#define USE_FADE (true)	//�t�F�[�h���^�]
#endif

// =============== �C���N���[�h ===================
#include "Fade.h"	//���g�̃w�b�_

#if USE_FADE
#include "Input.h"	//�L�[���͗p
#endif

#if _DEBUG
#include <Windows.h>	//���b�Z�[�W�{�b�N�X�p
#endif

// =============== �萔��` =====================
const std::string VS_PASS("Assets/Shader/VsFade.cso");	//�e�N�X�`���̃p�X��
const std::string PS_PASS("Assets/Shader/PsFade.cso");	//�e�N�X�`���̃p�X��
const std::string TEX_PASS("Assets/Fade.png");			//�e�N�X�`���̃p�X��
const TPos3d<float> INIT_POS(640.0f, 360.0f, 0.0f);		//�ʒu������
const TTriType<float> INIT_SCALE(80.0f, 80.0f, 0.0f);	//�����g�k
const TTriType<float> INIT_RADIAN(0.0f);				//������]
const int FRAME_MIN(0);									//�t�F�[�h���Ԃ̍ŏ�
const int FRAME_TURNING_1(50);							//�g�k���]�P���]
const int FRAME_TURNING_2(100);							//�g�k���]�Q���]
const int FRAME_MAX(150);								//�t�F�[�h���Ԃ̍ő�
const float SCALE_MIN(0.0f);							//�ŏ��T�C�Y
const float SCALE_TURNINIG_2(15.0f);					//�T�C�Y���]�Q���]
const float SCALE_TURNINIG_1(100.0f);					//�T�C�Y���]�P���]
const float SCALE_MAX(1000.0f);							//�ő�T�C�Y
const float ROTATE_ACCEL_RATE(4.0f);					//�p���x��������

// =============== �O���[�o���ϐ��錾 =====================
int CFade::ms_nCntFade;							//���g�̐�����
VertexShader* CFade::ms_pVs = nullptr;			//���_�V�F�[�_�[
PixelShader* CFade::ms_pPs = nullptr;			//�s�N�Z���V�F�[�_�[
Texture* CFade::ms_pTexture = nullptr;			//�e�N�X�`�����
const void* CFade::ms_pVtx = nullptr;			//���_���
unsigned int CFade::ms_unVtxSize;				//���_�T�C�Y
unsigned int CFade::ms_unVtxCount;				//���_��
const void* CFade::ms_pIdx = nullptr;			//���_�̃C���f�b�N�X
unsigned int CFade::ms_unIdxSize;				//�C���f�b�N�X�T�C�Y
unsigned int CFade::ms_unIdxCount;				//�C���f�b�N�X��
ID3D11Buffer* CFade::ms_pVtxBuffer = nullptr;	//���_�o�b�t�@
ID3D11Buffer* CFade::ms_pIdxBuffer = nullptr;	//�C���f�b�N�X�o�b�t�@ 

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�������ɍs������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CFade::CFade(const CCamera* pCamera)
	:m_ucFlag(0x00)									//�t���O
	,m_pCamera(pCamera)								//�J����
	,m_Transform(INIT_POS, INIT_SCALE, INIT_RADIAN)	//���[���h���W
	,m_UvParam{{ 1.0f, 1.0f }, { 0.0f, 0.0f }}		//�V�F�[�_�[�pUV���W	//TODO:DiType�̏�񂪍X�V���ꂽ�甽�f����
	,m_nFrameOut(0)
	,m_nFrameStop(0)
	,m_nFrameIn(0)
{
	// =============== �ÓI�쐬 ===================
	if (0 == ms_nCntFade)	//���݁A���ɂ��̃N���X���쐬����Ă��Ȃ���
	{
		// =============== �V�F�[�_�[�쐬 ===================
		ms_pVs = new VertexShader();		//���_�V�F�[�_�쐬
		ms_pVs->Load("Assets/Shader/VsFade.cso");		//���_�V�F�[�_�ǂݍ���
		ms_pPs = new PixelShader();			//�s�N�Z���V�F�[�_�쐬
		ms_pPs->Load("Assets/Shader/PsFade.cso");		//�s�N�Z���V�F�[�_�ǂݍ���

	// =============== �e�N�X�`���쐬 ===================
		SetTexture();	//�e�N�X�`���o�^

	// =============== �`��쐬 ===================
		Make();	//���ʃ|���S���쐬
	}

	// =============== �s��쐬 ===================
	m_aMatrix[0] = m_Transform.GetWorldMatrixSRT();							//���[���h�s��
	DirectX::XMStoreFloat4x4(&m_aMatrix[1], DirectX::XMMatrixIdentity());	//�r���[�s��F�P�ʍs��
	m_aMatrix[2] = m_pCamera->GetProjectionMatrix(CCamera::E_DRAW_TYPE_2D);	//�v���W�F�N�V�����s��

	// =============== �J�E���^ ===================
	ms_nCntFade++;	//���g�̐��J�E���g
}

/* ========================================
	�R�s�[�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�R�s�[���ɍs������
	-------------------------------------
	����1�Fconst CFade & Obj�F�R�s�[���̎Q��
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CFade::CFade(const CFade & Obj)
{
}

/* ========================================
	�f�X�g���N�^�֐�
	-------------------------------------
	���e�F�j�����ɍs������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CFade::~CFade()
{
	// =============== ��� ===================
	ms_nCntFade--;				//���g�̐��J�E���g
	SAFE_DELETE(ms_pVs);		//���_�V�F�[�_�[���
	SAFE_DELETE(ms_pPs);		//�s�N�Z���V�F�[�_�[���
	SAFE_DELETE(ms_pTexture);	//�e�N�X�`�����
	//SAFE_DELETE(ms_pVtx);		//���_�����
	//SAFE_DELETE(ms_pIdx);		//���_�C���f�b�N�X���
	//SAFE_DELETE(ms_pVtxBuffer);	//���_�o�b�t�@���
	//SAFE_DELETE(ms_pIdxBuffer);	//�C���f�b�N�X�o�b�t�@���
}

/* ========================================
	�X�V�֐�
	-------------------------------------
	���e�F�X�V����
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CFade::Update()
{
}

/* ========================================
	�`��֐�
	-------------------------------------
	���e�F�`�揈��
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CFade::Draw()
{
#if USE_FADE
	if (IsKeyTrigger('7'))
	{
		Start();	//�t�F�[�h�J�n
	}
#endif

	// =============== ���� ===================
	if (!ms_pTexture || !(m_ucFlag & FLAG_FADE_ALL))	//�`��ł��Ȃ���
	{
		return;	//�������f
	}

	// =============== �t�F�[�h�X�g�b�v ===================
	if (m_ucFlag & E_BIT_FLAG_FADE_STOP)	//�X�g�b�v����
	{
		if (m_nFrameStop <= FRAME_MIN)	//�J�E���g�I��
		{
			DownFlag(E_BIT_FLAG_FADE_STOP);	//�X�g�b�v�I��
			UpFlag(E_BIT_FLAG_FADE_IN);		//�t�F�[�h�C���J�n
			m_nFrameOut = FRAME_MAX;		//�t�F�[�h���ԍēo�^
		}

		// =============== �J�E���^ ===================
		m_nFrameStop--;	//�t���[���J�E���g
	}
	else
	{
		// =============== �t�F�[�h ===================
#if _DEBUG
		if (m_ucFlag & (E_BIT_FLAG_FADE_IN | E_BIT_FLAG_FADE_OUT))
		{
#endif
			// =============== �ϐ��錾 ===================
			int nFrameTemp;	//�t���[���ޔ�p

			// =============== ���򏈗� ===================
			if (m_ucFlag & E_BIT_FLAG_FADE_OUT)	//�t�F�[�h�A�E�g��
			{
				// =============== ������ ===================
				nFrameTemp = FRAME_MAX - m_nFrameOut;	//�ޔ�

				// =============== �J�E���^ ===================
				m_nFrameOut--;	//�t���[���J�E���g
			}
			if (m_ucFlag & E_BIT_FLAG_FADE_IN)	//�t�F�[�h�C����
			{
				// =============== ������ ===================
				nFrameTemp = m_nFrameIn;	//�ޔ�

				// =============== �J�E���^ ===================
				m_nFrameIn--;	//�t���[���J�E���g
			}

			// =============== ��ԕ��� ===================
			if (m_nFrameIn <= FRAME_MIN && m_ucFlag & E_BIT_FLAG_FADE_IN || m_nFrameOut <= FRAME_MIN && m_ucFlag & E_BIT_FLAG_FADE_OUT)	//�t�F�[�h�A�E�g�E�C���I��
			{
				if (m_ucFlag & E_BIT_FLAG_FADE_OUT)	//�t�F�[�h�A�E�g��
				{
					DownFlag(E_BIT_FLAG_FADE_OUT);	//�t�F�[�h�A�E�g�I��
					UpFlag(E_BIT_FLAG_FADE_STOP);	//�t�F�[�h�X�g�b�v�J�n
				}
				if (m_ucFlag & E_BIT_FLAG_FADE_IN)	//�t�F�[�h�C����
				{
					DownFlag(E_BIT_FLAG_FADE_IN);	//�t�F�[�h�C���I��
				}
			}
			else
			{
				if (nFrameTemp <= FRAME_TURNING_1)	//�A�E�g���F��P�^�[�j���O�|�C���g����I���܂�
				{
					m_UvParam.fUvScale.x =(SCALE_TURNINIG_1 - SCALE_MIN) * (float)(nFrameTemp - FRAME_MIN) / (float)(FRAME_TURNING_1);	//�g�k�Z�b�g
				}
				else
				{
					if (nFrameTemp <= FRAME_TURNING_2)	//�A�E�g���F��Q�^�[�j���O�|�C���g�����P�^�[�j���O�|�C���g�܂�
					{
						m_UvParam.fUvScale.x = SCALE_TURNINIG_1 + (SCALE_TURNINIG_2 - SCALE_TURNINIG_1) * (float)(nFrameTemp - FRAME_TURNING_1) / (float)(FRAME_TURNING_2 - FRAME_TURNING_1);	//�g�k�Z�b�g
					}
					else
					{
						if (nFrameTemp <= FRAME_MAX)	//�A�E�g���F�J�n�����P�^�[�j���O�|�C���g�܂�
						{
							m_UvParam.fUvScale.x = SCALE_TURNINIG_2 + (SCALE_MAX - SCALE_TURNINIG_2) * (float)(nFrameTemp - FRAME_TURNING_2) / (float)(FRAME_MAX - FRAME_TURNING_2);	//�g�k�Z�b�g
						}
#if _DEBUG
						else
						{
							MessageBox(nullptr, "�t���[�������z��𒴉߂��܂���", "Fade.cpp->Error", MB_OK);	//�G���[�ʒm
						}
#endif
					}
				}
				m_UvParam.fUvScale.y = m_UvParam.fUvScale.x;	//�ύX�𑵂���
			}

			// =============== �p�X�V ===================
			m_Transform.fRadian.z = DirectX::XMConvertToRadians(nFrameTemp * ROTATE_ACCEL_RATE);	//�t���[�����Ŋp�X�V
#if _DEBUG
		}
		else
		{
			MessageBox(nullptr, "�z�肳��Ȃ��t�F�[�h�̎�ނł�", "Fade.cpp->Error", MB_OK);	//�G���[�ʒm
		}
#endif
	}

	// =============== �s��X�V ===================
	m_aMatrix[0] = m_Transform.GetWorldMatrixSRT();							//���[���h�s��X�V
	m_aMatrix[2] = m_pCamera->GetProjectionMatrix(CCamera::E_DRAW_TYPE_2D);	//�v���W�F�N�V�����s��X�V

	// =============== �ϐ��錾 ===================
	float Param[4] = { m_UvParam.fUvScale.x, m_UvParam.fUvScale.y, m_UvParam.fDummy.x, m_UvParam.fDummy.y };	//�萔�o�b�t�@�������ݗp

	// =============== �V�F�[�_�[�g�p ===================
	ms_pVs->WriteBuffer(0, m_aMatrix);	//�萔�o�b�t�@�ɍs���񏑂�����
	ms_pVs->WriteBuffer(1, &Param);	//�萔�o�b�t�@��UV��񏑂�����
	ms_pVs->Bind();						//���_�V�F�[�_�[�g�p
	ms_pPs->SetTexture(0, ms_pTexture);	//�e�N�X�`���o�^
	ms_pPs->Bind();						//�s�N�Z���V�F�[�_�[�g�p

	// =============== �ϐ��錾 ===================
	ID3D11DeviceContext* pContext = GetContext();	//�`�摮���̏��
	unsigned int unOffset = 0;						//���_�o�b�t�@�z����̃o�b�t�@��

	// =============== �g�|���W�[�ݒ� ===================
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);		//�O�p�|���S���̃g�|���W�[		TODO:���ʂ�����strip�ł��ǂ����������ǂǂ����̕����y�������ׂ�

	// =============== ���_�o�b�t�@�o�^ ===================
	pContext->IASetVertexBuffers(0, 1, &ms_pVtxBuffer, &ms_unVtxSize, &unOffset);	//���_�o�b�t�@�o�^

	// =============== �C���f�b�N�X�̗L�� ===================
	if (ms_unIdxCount > 0)	//�C���f�b�N�X�����鎞
	{
		// =============== �T�C�Y�Ⴂ ===================
		DXGI_FORMAT Format;	//���\�[�X�f�[�^�t�H�[�}�b�g
		switch (ms_unIdxSize)	//�C���f�b�N�X�T�C�Y
		{
		case 4: Format = DXGI_FORMAT_R32_UINT; break;	//1����32�r�b�g�����Ȃ�����(unsigned int (�V�������))
		case 2: Format = DXGI_FORMAT_R16_UINT; break;	//1����16�r�b�g�����Ȃ�����(unsigned int (�Â����))
		}

		// =============== �C���f�b�N�X�o�b�t�@�o�^ ===================
		pContext->IASetIndexBuffer(ms_pIdxBuffer, Format, 0);	//�C���f�b�N�X�o�b�t�@�o�^

		// =============== �`�� ===================
		pContext->DrawIndexed(ms_unIdxCount, 0, 0);	//���_�̃C���f�b�N�X���g���ĕ`��
	}
	else
	{
		// =============== �`�� ===================
		pContext->Draw(ms_unVtxCount, 0);	// ���_�o�b�t�@�݂̂ŕ`��
	}
}

/* ========================================
	�X�^�[�g�֐�
	-------------------------------------
	���e�F�`�󐶐��E���o�^
	-------------------------------------
	����1�FTTriType<int> nFrame�F�t���[����(x�F�t�F�[�h�A�E�g, y�F�t�F�[�h�X�g�b�v, z�F�t�F�[�h�C��)
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CFade::Start(TTriType<int> nFrame)
{
	// =============== �t���[�����o�^ ===================
	m_nFrameOut = nFrame.x;		//�t�F�[�h�A�E�g�̃t���[�����o�^
	m_nFrameStop = nFrame.y;	//�t�F�[�h�X�g�b�v�̃t���[�����o�^
	m_nFrameIn = nFrame.z;		//�t�F�[�h�C���̃t���[�����o�^

	// =============== �t���O���� ===================
	UpFlag(E_BIT_FLAG_FADE_OUT);	//�t�F�[�h�A�E�g�J�n
}


/* ========================================
	�`�󐶐��֐�
	-------------------------------------
	���e�F�`�󐶐��E���o�^
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CFade::Make()
{
	// =============== �ϐ��錾 ===================
	Vertex aVtx[] = {
		{{-10.5f, 10.5f, -0.0f}, {0.0f, 0.0f}},	//���ʃ|���S������
		{{ 10.5f, 10.5f, -0.0f}, {1.0f, 0.0f}},	//���ʃ|���S���E��
		{{-10.5f,-10.5f, -0.0f}, {0.0f, 1.0f}},	//���ʃ|���S������
		{{ 10.5f,-10.5f, -0.0f}, {1.0f, 1.0f}},	//���ʃ|���S���E��
	};	//���_���
	int aIdx[] = {
		0, 1, 2, 2, 1, 3	//���ʃ|���S��
	};	//���_�C���f�b�N�X

	// =============== ������ ===================
	ms_pVtx = aVtx;					//���_���
	ms_unVtxSize = sizeof(Vertex);	//���_�^�T�C�Y
	ms_unVtxCount = _countof(aVtx);	//���_��
	ms_pIdx = aIdx;					//���_�̃C���f�b�N�X
	ms_unIdxSize = sizeof(int);		//�C���f�b�N�X�T�C�Y
	ms_unIdxCount = _countof(aIdx);	//�C���f�b�N�X��

	// =============== ���� ===================
	CreateVtxBuffer();	//���_�o�b�t�@�쐬
	CreateIdxBuffer();	//�C���f�b�N�X�o�b�t�@
}

/* ========================================
	�e�N�X�`���Z�b�^�֐�
	-------------------------------------
	���e�F�e�N�X�`���[�쐬�E�o�^
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CFade::SetTexture()
{
	// =============== ��� ===================
	SAFE_DELETE(ms_pTexture);	//�e�N�X�`�����

	// =============== �쐬 ===================
	ms_pTexture = new Texture;				//���I�m��
	ms_pTexture->Create(TEX_PASS.c_str());	//�V�K�e�N�X�`���o�^
}

/* ========================================
	���_�o�b�t�@�쐬�֐�
	-------------------------------------
	���e�F�C���f�b�N�X��񂩂�f�[�^�쐬
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CFade::CreateVtxBuffer()
{
	// =============== �o�b�t�@���ݒ� ===================
	D3D11_BUFFER_DESC BufDesc;							//�o�b�t�@���
	ZeroMemory(&BufDesc, sizeof(BufDesc));				//���g��S��0�ŏ�����
	BufDesc.ByteWidth = ms_unVtxSize * ms_unVtxCount;	//�o�b�t�@�̑傫��
	BufDesc.Usage = D3D11_USAGE_DEFAULT;				//��������ł̊Ǘ����@
	BufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;		//GPU��ł̗��p���@

	//���o�b�t�@�����f�[�^�ݒ�
	D3D11_SUBRESOURCE_DATA SubResource;				//�T�u���\�[�X
	ZeroMemory(&SubResource, sizeof(SubResource));	//�f�[�^������
	SubResource.pSysMem = ms_pVtx;					//�o�b�t�@�ɓ��ꍞ�ރf�[�^

	// =============== �쐬 ===================
	HRESULT hr = GetDevice()->CreateBuffer(&BufDesc, &SubResource, &ms_pVtxBuffer);	//���_�o�b�t�@�쐬
	if (FAILED(hr))	//�G���[����
	{
		// =============== ��֏��� ===================
		ms_pVtxBuffer = nullptr;	//��A�h���X���
	}
}

/* ========================================
	�C���f�b�N�X�o�b�t�@�쐬�֐�
	-------------------------------------
	���e�F�C���f�b�N�X��񂩂�f�[�^�쐬
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CFade::CreateIdxBuffer()
{
	// =============== �C���f�b�N�X�T�C�Y�̊m�F ===================
	switch (ms_unIdxSize)
	{
		// =============== �T�C�Y�Ⴂ ===================
	default:	//���L�ȊO
#if _DEBUG
		MessageBox(nullptr, "�^�̃T�C�Y��int�^�ƈ�v���܂���", "Fade.cpp->Error", MB_OK);	//�G���[�ʒm
#endif
		return;	//�������f

		// =============== int�^�Ɠ��� ===================
	case 2:	//�Â�int�^�̃T�C�Y
	case 4:	//����int�^�̃T�C�Y
		break;	//���򏈗��I��
	}

	// =============== �o�b�t�@�̏���ݒ� ===================
	D3D11_BUFFER_DESC BufDesc;							//�o�b�t�@���
	ZeroMemory(&BufDesc, sizeof(BufDesc));				//���g��S��0�ŏ�����
	BufDesc.ByteWidth = ms_unIdxSize * ms_unIdxCount;	//�f�[�^�̃o�C�g��
	BufDesc.Usage = D3D11_USAGE_DEFAULT;				//��������ł̊Ǘ����@
	BufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;		//GPU��ł̗��p���@

	// =============== �o�b�t�@�̏����f�[�^ ===================
	D3D11_SUBRESOURCE_DATA SubResource = {};	//�T�u���\�[�X
	SubResource.pSysMem = ms_pIdx;				//�o�b�t�@�ɓ��ꍞ�ރf�[�^

	// =============== �쐬 ===================
	HRESULT hr = GetDevice()->CreateBuffer(&BufDesc, &SubResource, &ms_pIdxBuffer);	//�C���f�b�N�X�̃o�b�t�@�쐬
	if (FAILED(hr))	//�G���[����
	{
		// =============== ��֏��� ===================
		ms_pIdxBuffer = nullptr;	//��A�h���X���
	}
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
void CFade::UpFlag(const unsigned char & ucBitFlag)
{
	// =============== ��� ===================
	m_ucFlag |= ucBitFlag;	//�t���O����
}

/* ========================================
	�t���O�I���֐�
	-------------------------------------
	���e�F�����ɑΉ������t���O���~�낷
	-------------------------------------
	����1�Fconst unsigned char & ucBitFlag�F�Ώۃt���O
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CFade::DownFlag(const unsigned char & ucBitFlag)
{
	// =============== ��� ===================
	m_ucFlag &= !ucBitFlag;	//�t���O����
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
void CFade::SetFlag(const unsigned char & ucBitFlag)
{
	// =============== ��� ===================
	m_ucFlag ^= ucBitFlag;	//�t���O����
}