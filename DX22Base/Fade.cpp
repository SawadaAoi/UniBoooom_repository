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
	�E2023/11/21 �X�V�E�`�揈������ takagi
	�E2023/11/23 IsFade()�֐��ǉ��E�ׂ����������� takagi
	�E2023/11/24 �t�F�[�h�̎d�l�ύX�Ή� takagi
	�E2023/11/27 �^���J�������� takagi
	�E2023/12/01 �t�F�[�h�̎d�l�ύX takagi 
	�E2023/12/04 �J�����̃t�@�C�������K�p takagi
	�E2023/12/17 �t�F�[�h�������肪����A�ŏ��E�ő��ԂɂȂ�Ȃ����Ƃ���������C���E�u���b�N�A�E�g�Ή� takagi
	�E2024/01/16 �t�F�[�h�A�E�g�E�C���ɃC�[�W���O�K�p takagi

========================================== */

// =============== �C���N���[�h ===================
#include "Fade.h"		//���g�̃w�b�_
#include "CameraDef.h"	//�^���J����
#include <math.h>		//pow�g�p

#if _DEBUG
#include <Windows.h>	//���b�Z�[�W�{�b�N�X�p
#endif

// =============== �萔�E�}�N����` =====================
const std::string VS_PASS("Assets/Shader/VsFade.cso");		//�e�N�X�`���̃p�X��
const std::string PS_PASS("Assets/Shader/PsFade.cso");		//�e�N�X�`���̃p�X��
const std::string TEX_PASS("Assets/Texture/Fade.png");		//�e�N�X�`���̃p�X��
const TPos3d<float> INIT_POS(640.0f, 360.0f, 0.0f);			//�ʒu������
const TTriType<float> INIT_SCALE(4000.0f, 4000.0f, 0.0f);	//�����g�k
const TTriType<float> INIT_RADIAN(0.0f);					//������]
const TTriType<int> FRAME_FADE_MAX(100, 60, 70);			//�t�F�[�h�ɂ�����t���[����	x:�A�E�g, y:�X�g�b�v, z:�C��
const int FRAME_MIN(0);										//�t�F�[�h���Ԃ̍ŏ�
const int FRAME_OUT_PATTERN_1_FIN(50);						//�t�F�[�h�A�E�g�J�n����g�k�����܂�܂ł̃t���[����
const int FRAME_OUT_PATTERN_2_FIN(80);						//�t�F�[�h�A�E�g�J�n����g�k�����܂�I���܂ł̃t���[����
const float SCALE_OUT_MIN(500.0f);							//�t�F�[�h�A�E�g�ŏ��T�C�Y	uv�̓s����A�l���傫�����T�C�Y���������Ȃ�
const float SCALE_IN_MIN(600.0f);							//�t�F�[�h�C���ŏ��T�C�Y	uv�̓s����A�l���傫�����T�C�Y���������Ȃ�
const float SCALE_OUT_STAY(10.0f);							//�t�F�[�h�A�E�g�g�k���ꎞ���܂�Ƃ��̃T�C�Y
const float SCALE_OUT_MAX(0.0f);							//�t�F�[�h�ő�T�C�Y	uv�̓s����A�l�����������T�C�Y���傫���Ȃ�
const float SCALE_IN_MAX(0.0f);								//�t�F�[�h�ő�T�C�Y	uv�̓s����A�l�����������T�C�Y���傫���Ȃ�
const float ROTATE_ACCEL_RATE(0.00025f);					//�p���x��������
const double PI(3.14159265358979323846);					//�~����M_PI�̃R�s�[
#define ROTATE_EASE_IN_OUT(frame) (ROTATE_ACCEL_RATE * (0.5 ? 4 * pow((frame), 3.0)	\
	: 1 - pow(-2 * (frame) + 2, 3.0) / 2))					//�t�F�[�h�C���E�A�E�g��]�p�̃C�[�Y�v�Z

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
CCamera* CFade::ms_pDefCamera = nullptr;		//��p�\���J����

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
	,m_UvParam{ {SCALE_OUT_MIN}, {0.0f } }					//�V�F�[�_�[�pUV���W
	,m_nFrame(0)								
{
	// =============== �ÓI�쐬 ===================
	if (0 == ms_nCntFade)	//���݁A���ɂ��̃N���X���쐬����Ă��Ȃ���
	{
		// =============== �J�����쐬 ===================
		ms_pDefCamera = new CCameraDef();	//�\���J����

		// =============== �V�F�[�_�[�쐬 ===================
		ms_pVs = new VertexShader();	//���_�V�F�[�_�쐬
		ms_pVs->Load(VS_PASS.c_str());	//���_�V�F�[�_�ǂݍ���
		ms_pPs = new PixelShader();		//�s�N�Z���V�F�[�_�쐬
		ms_pPs->Load(PS_PASS.c_str());	//�s�N�Z���V�F�[�_�ǂݍ���

	// =============== �e�N�X�`���쐬 ===================
		SetTexture();	//�e�N�X�`���o�^

	// =============== �`��쐬 ===================
		Make();	//���ʃ|���S���쐬
	}

	// =============== ������ ===================
	if (pCamera)	//�k���`�F�b�N
	{
		m_pCamera = pCamera;	//�J����������
	}
	else
	{
		m_pCamera = ms_pDefCamera;	//�^���J����
	}

	// =============== �s��쐬 ===================
	m_aMatrix[0] = m_Transform.GetWorldMatrixSRT();							//���[���h�s��
	DirectX::XMStoreFloat4x4(&m_aMatrix[1], DirectX::XMMatrixIdentity());	//�r���[�s��F�P�ʍs��
	m_aMatrix[2] = m_pCamera->GetProjectionMatrix(CCamera::E_DRAW_TYPE_2D);	//�v���W�F�N�V�����s��

	// =============== �J�E���^ ===================
	ms_nCntFade++;	//���g�̐��J�E���g

	// =============== �t���[�����o�^ ===================
	m_nFrame = FRAME_FADE_MAX.z;	//�t�F�[�h�C���̃t���[�����o�^

	// =============== �t���O���� ===================
	UpFlag(E_BIT_FLAG_FADE_IN);	//�t�F�[�h�C���J�n
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
	if (ms_nCntFade == 0)
	{
		SAFE_DELETE(ms_pVs);		//���_�V�F�[�_�[���
		SAFE_DELETE(ms_pPs);		//�s�N�Z���V�F�[�_�[���
		SAFE_DELETE(ms_pTexture);	//�e�N�X�`�����
		SAFE_DELETE(ms_pDefCamera);	//�\���J�������
		//SAFE_DELETE(ms_pVtx);		//���_�����
		//SAFE_DELETE(ms_pIdx);		//���_�C���f�b�N�X���
		//SAFE_DELETE(ms_pVtxBuffer);	//���_�o�b�t�@���
		//SAFE_DELETE(ms_pIdxBuffer);	//�C���f�b�N�X�o�b�t�@���
	}
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
	// =============== ���� ===================
	if (!ms_pTexture || !(m_ucFlag & FLAG_FADE_ALL))	//�`��ł��Ȃ���
	{
		return;	//�������f
	}

	// =============== �ޔ� ===================
	unsigned char ucTemp = m_ucFlag;		//�ޔ�

	// =============== �t���O���� ===================
	for (int nIdx = 0; nIdx < E_BIT_FLAG_MAX; nIdx++)
	{
		if (ucTemp & 0x01)	//���ʃr�b�g����D�悵�ď�������
		{
			switch (0x01 << nIdx)	//�Y�������r�b�g��ɕϊ�
			{
				// =============== �t�F�[�h�A�E�g ===================
			case E_BIT_FLAG_FADE_OUT:	//�t�F�[�h�A�E�g
				FadeOut();	//�t�F�[�h�A�E�g����
				break;		//���򏈗��I��

				// =============== �t�F�[�h�X�g�b�v ===================
			case E_BIT_FLAG_FADE_STOP:	//�t�F�[�h�X�g�b�v
				FadeStop();	//�t�F�[�h�X�g�b�v����
				break;		//���򏈗��I��

				// =============== �t�F�[�h�C�� ===================
			case E_BIT_FLAG_FADE_IN:	//�t�F�[�h�C��
				FadeIn();	//�t�F�[�h�C������
				break;		//���򏈗��I��

				// =============== ���Ή� ===================
			default:					//���̑�
#if _DEBUG
				MessageBox(nullptr, "�z�肳��Ȃ��t�F�[�h�̎�ނł�", "Fade.cpp->Update->Error", MB_OK);	//�G���[�ʒm
#endif
				break;						//���򏈗��I��
			}
			break;	//���[�v�����I��
		}
		else
		{
			ucTemp >>= 1;	//���̃t���O����
		}
	}

	// =============== �s��X�V ===================
	m_aMatrix[0] = m_Transform.GetWorldMatrixSRT();							//���[���h�s��X�V
	m_aMatrix[2] = m_pCamera->GetProjectionMatrix(CCamera::E_DRAW_TYPE_2D);	//�v���W�F�N�V�����s��X�V
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
	// =============== ���� ===================
	if (!ms_pTexture || !(m_ucFlag & FLAG_FADE_ALL))	//�`��ł��Ȃ���
	{
		if (m_ucFlag & E_BIT_FLAG_BLACKOUT)
		{
			// =============== �����ύX ===================
			m_UvParam.fUvOffset = 1000.0f;	//�e�N�X�`���ʒu�����炵�t�F�[�h���B��
		}
		else
		{
			// =============== �I�� ===================
			return;	//�������f
		}
	}

	// =============== �ϐ��錾 ===================
	float Param[4] = { m_UvParam.fUvScale.x, m_UvParam.fUvScale.y, m_UvParam.fUvOffset.x, m_UvParam.fUvOffset.y };	//�萔�o�b�t�@�������ݗp

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
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CFade::Start()
{
	// =============== �t���[�����o�^ ===================
	m_nFrame = FRAME_FADE_MAX.x;	//�t�F�[�h�A�E�g�̃t���[�����o�^

	// =============== �t���O���� ===================
	UpFlag(E_BIT_FLAG_FADE_OUT);	//�t�F�[�h�A�E�g�J�n
}

/* ========================================
	�t�F�[�h�m�F�֐�
	-------------------------------------
	���e�F�t�F�[�h�����m�F����
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�t�F�[�h����true, ����ȊO��false
=========================================== */
bool CFade::IsFade()
{	
	// =============== �� ===================
	if (m_ucFlag & FLAG_FADE_ALL)	//�t�F�[�h��
	{
		return true;	//�t�F�[�h���Ă���
	}
	else
	{
		return false;	//�t�F�[�h���Ă��Ȃ�
	}
}

/* ========================================
	�t�F�[�h�A�E�g�m�F�֐�
	-------------------------------------
	���e�F�t�F�[�h�A�E�g�����m�F����
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�t�F�[�h�A�E�g����true, ����ȊO��false
=========================================== */
bool CFade::IsFadeOut()
{
	// =============== �ޔ� ===================
	unsigned char ucTemp = m_ucFlag;		//�ޔ�

	// =============== �t���O���� ===================
	for (int nIdx = 0; nIdx < E_BIT_FLAG_MAX; nIdx++)
	{
		if (ucTemp & 0x01)	//Update�֐��Ɠ����̗D��x�ŏ�������
		{
			// =============== �� ===================
			switch (0x01 << nIdx)	//�Y�������r�b�g��ɕϊ�
			{
				// =============== �t�F�[�h�A�E�g�� ===================
			case E_BIT_FLAG_FADE_OUT:	//�t�F�[�h�A�E�g
				return true;	//�t�F�[�h�A�E�g���Ă���
				break;			//���򏈗��I��
			}
			break;	//���[�v�����I��
		}
		else
		{
			ucTemp >>= 1;	//���̃t���O����
		}
	}
	return false;	//�t�F�[�h�A�E�g���Ă��Ȃ�
}

/* ========================================
	�t�F�[�h�C���m�F�֐�
	-------------------------------------
	���e�F�t�F�[�h�C�������m�F����
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�t�F�[�h�C������true, ����ȊO��false
=========================================== */
bool CFade::IsFadeIn()
{
	// =============== �ޔ� ===================
	unsigned char ucTemp = m_ucFlag;		//�ޔ�

	// =============== �t���O���� ===================
	for (int nIdx = 0; nIdx < E_BIT_FLAG_MAX; nIdx++)
	{
		if (ucTemp & 0x01)	//Update�֐��Ɠ����̗D��x�ŏ�������
		{
			// =============== �� ===================
			switch (0x01 << nIdx)	//�Y�������r�b�g��ɕϊ�
			{
				// =============== �t�F�[�h�C���� ===================
			case E_BIT_FLAG_FADE_IN:	//�t�F�[�h�C��
				return true;	//�t�F�[�h�C�����Ă���
				break;			//���򏈗��I��
			}
			break;	//���[�v�����I��
		}
		else
		{
			ucTemp >>= 1;	//���̃t���O����
		}
	}
	return false;	//�t�F�[�h�C�����Ă��Ȃ�
}

/* ========================================
	�t�F�[�h�i���Q�b�^�֐�
	-------------------------------------
	���e�F���݃t�F�[�h���[�h�̐i�s������񋟂���
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F���݃t�F�[�h���[�h�� �i������ / �ő厞�� �̌���	��t�F�[�h����0.0f
=========================================== */
float CFade::GetFrameRate()
{
	// =============== �ޔ� ===================
	unsigned char ucTemp = m_ucFlag;		//�ޔ�

	// =============== �t���O���� ===================
	for (int nIdx = 0; nIdx < E_BIT_FLAG_MAX; nIdx++)
	{
		if (ucTemp & 0x01)	//���ʃr�b�g����D�悵�ď�������
		{
			// =============== �� ===================
			switch (0x01 << nIdx)	//�Y�������r�b�g��ɕϊ�
			{
				// =============== �t�F�[�h�A�E�g ===================
			case E_BIT_FLAG_FADE_OUT:	//�t�F�[�h�A�E�g
#if _DEBUG
				if (0 == FRAME_FADE_MAX.x)
				{
					MessageBox(nullptr, "0���Z�̊댯��������܂�", "Fade.cpp->GetFrameRate->Error", MB_OK);	//�G���[�ʒm
					return 0.0f;	//�Վ��Ή�
				}
#endif
				return static_cast<float>(m_nFrame) / static_cast<float>(FRAME_FADE_MAX.x);	//�A�E�g�̐i�s����
				break;		//���򏈗��I��

				// =============== �t�F�[�h�X�g�b�v ===================
			case E_BIT_FLAG_FADE_STOP:	//�t�F�[�h�X�g�b�v
#if _DEBUG
				if (0 == FRAME_FADE_MAX.y)
				{
					MessageBox(nullptr, "0���Z�̊댯��������܂�", "Fade.cpp->GetFrameRate->Error", MB_OK);	//�G���[�ʒm
					return 0.0f;	//�Վ��Ή�
				}
#endif
				return static_cast<float>(m_nFrame) / static_cast<float>(FRAME_FADE_MAX.y);	//�X�g�b�v�̐i�s����
				break;		//���򏈗��I��

				// =============== �t�F�[�h�C�� ===================
			case E_BIT_FLAG_FADE_IN:	//�t�F�[�h�C��
#if _DEBUG
				if (0 == FRAME_FADE_MAX.z)
				{
					MessageBox(nullptr, "0���Z�̊댯��������܂�", "Fade.cpp->GetFrameRate->Error", MB_OK);	//�G���[�ʒm
					return 0.0f;	//��֒l�őΉ�
				}
#endif
				return static_cast<float>(m_nFrame) / static_cast<float>(FRAME_FADE_MAX.z);	//�C���̐i�s����
				break;		//���򏈗��I��
#if _DEBUG
				// =============== ���Ή� ===================
			default:					//���̑�
				MessageBox(nullptr, "�z�肳��Ȃ��t�F�[�h�̎�ނł�", "Fade.cpp->GetFrameRate->Error", MB_OK);	//�G���[�ʒm
				break;			//���򏈗��I��
#endif
			}
			break;	//���[�v�����I��
		}
		else
		{
			ucTemp >>= 1;	//���̃t���O����
		}
	}
		return 0.0f;	//�t�F�[�h���Ă��Ȃ�
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
		{{-0.5f, 0.5f, -0.0f}, {0.0f, 0.0f}},	//���ʃ|���S������
		{{ 0.5f, 0.5f, -0.0f}, {1.0f, 0.0f}},	//���ʃ|���S���E��
		{{-0.5f,-0.5f, -0.0f}, {0.0f, 1.0f}},	//���ʃ|���S������
		{{ 0.5f,-0.5f, -0.0f}, {1.0f, 1.0f}},	//���ʃ|���S���E��
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
		MessageBox(nullptr, "�^�̃T�C�Y��int�^�ƈ�v���܂���", "Fade.cpp->CreateIdxBuffer->Error", MB_OK);	//�G���[�ʒm
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
	�t���O�I�t�֐�
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
void CFade::SetFlag(const unsigned char & ucBitFlag)
{
	// =============== ��� ===================
	m_ucFlag ^= ucBitFlag;	//�t���O����
}

/* ========================================
	�t�F�[�h�A�E�g�X�V�֐�
	-------------------------------------
	���e�F�t�F�[�h�A�E�g����
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CFade::FadeOut()
{
#if _DEBUG
	// =============== ���� ===================
	if (!(m_ucFlag & E_BIT_FLAG_FADE_OUT))	//�A�E�g����
	{
		MessageBox(nullptr, "�t�F�[�h�A�E�g���łȂ����Ƀt�F�[�h�A�E�g���悤�Ƃ��Ă��܂�", "Fade.cpp->FadeOut->Error", MB_OK);	//�G���[�ʒm
		return;	//�������f
	}
#endif
		// =============== ��ԕ��� ===================
		if (m_nFrame < FRAME_MIN)	//�t�F�[�h�A�E�g�I��
		{
			DownFlag(E_BIT_FLAG_FADE_OUT);	//�t�F�[�h�A�E�g�I��
			//m_nFrame = FRAME_FADE_MAX.y;	//�t�F�[�h�X�g�b�v�̃t���[�����o�^
			//UpFlag(E_BIT_FLAG_FADE_STOP);	//�t�F�[�h�X�g�b�v�J�n
			UpFlag(E_BIT_FLAG_BLACKOUT);	//�t�F�[�h�X�g�b�v�J�n
		}
		else
		{
			// =============== �������q�t���ϐ��錾 ===================
			int nFrameTemp = FRAME_FADE_MAX.x - m_nFrame;	//�ޔ�
			
			// =============== �g�k�X�V ===================
			if (nFrameTemp <= FRAME_OUT_PATTERN_1_FIN)	//�t�F�[�h�A�E�g�p�^�[���P�F�t�F�[�h�A�E�g�J�n����g�k�����܂�܂�
			{
				m_UvParam.fUvScale.x = SCALE_OUT_MAX + (SCALE_OUT_STAY - SCALE_OUT_MAX) * (float)(nFrameTemp - FRAME_MIN) / (float)(FRAME_OUT_PATTERN_1_FIN);	//�g�k�Z�b�g
			}
			else
			{
				if (nFrameTemp <= FRAME_OUT_PATTERN_2_FIN)	//�t�F�[�h�A�E�g�p�^�[���Q�F�g�k�����܂�n�߂Ă��痯�܂�I���܂�
				{
					m_UvParam.fUvScale.x = SCALE_OUT_STAY;	//�g�k�Z�b�g
				}
				else
				{
					if (nFrameTemp <= FRAME_FADE_MAX.x)	//�t�F�[�h�A�E�g�p�^�[���R�F�g�k�ĊJ����t�F�[�h�A�E�g�I���܂�
					{
						m_UvParam.fUvScale.x = SCALE_OUT_STAY + (SCALE_OUT_MIN - SCALE_OUT_STAY) * (float)(nFrameTemp - FRAME_OUT_PATTERN_2_FIN) / (float)(FRAME_FADE_MAX.x - FRAME_OUT_PATTERN_2_FIN);	//�g�k�Z�b�g
					}
#if _DEBUG
					else
					{
						MessageBox(nullptr, "�t���[�������z��𒴉߂��܂���", "Fade.cpp->FadeOut->Error", MB_OK);	//�G���[�ʒm
					}
#endif
				}
			}
			m_UvParam.fUvScale.y = m_UvParam.fUvScale.x;	//x�l�̕ύX��y�l�ɔ��f����

			// =============== ��]�p�X�V ===================
			m_Transform.fRadian.z = DirectX::XMConvertToRadians(ROTATE_EASE_IN_OUT(nFrameTemp));	//�t���[�����Ŋp�X�V
		}

		// =============== �J�E���^ ===================
		m_nFrame--;	//�t���[���J�E���g
}

/* ========================================
	�t�F�[�h�X�g�b�v�X�V�֐�
	-------------------------------------
	���e�F�t�F�[�h�X�g�b�v����
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CFade::FadeStop()
{	
#if _DEBUG
	// =============== ���� ===================
	if (!(m_ucFlag & E_BIT_FLAG_FADE_STOP))	//�X�g�b�v����
	{
		MessageBox(nullptr, "�t�F�[�h�X�g�b�v���łȂ����Ƀt�F�[�h�X�g�b�v���悤�Ƃ��Ă��܂�", "Fade.cpp->FadeStop->Error", MB_OK);	//�G���[�ʒm
		return;	//�������f
	}
#endif
	// =============== �t�F�[�h�X�g�b�v ===================
		if (m_nFrame <= FRAME_MIN)	//�J�E���g�I��
		{
			m_UvParam.fUvOffset = 0.0f;		//�e�N�X�`���ʒu��߂��t�F�[�h��������
			DownFlag(E_BIT_FLAG_FADE_STOP);	//�X�g�b�v�I��
			//m_nFrame = FRAME_FADE_MAX.z;	//�t�F�[�h�C���̃t���[�����o�^
			//UpFlag(E_BIT_FLAG_FADE_IN);		//�t�F�[�h�C���J�n
		}

		// =============== �J�E���^ ===================
		m_nFrame--;	//�t���[���J�E���g
}

/* ========================================
	�t�F�[�h�C���X�V�֐�
	-------------------------------------
	���e�F�t�F�[�h�C������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CFade::FadeIn()
{
#if _DEBUG
	// =============== ���� ===================
	if (!(m_ucFlag & E_BIT_FLAG_FADE_IN))	//�C������
	{
		MessageBox(nullptr, "�t�F�[�h�C�����łȂ����Ƀt�F�[�h�C�����悤�Ƃ��Ă��܂�", "Fade.cpp->FadeIn->Error", MB_OK);	//�G���[�ʒm
		return;	//�������f
	}
#endif
	// =============== ��ԕ��� ===================
	if (m_nFrame < FRAME_MIN)	//�t�F�[�h�C���I��
	{
		DownFlag(E_BIT_FLAG_FADE_IN);	//�t�F�[�h�C���I��
	}
	else
	{
		// =============== �������q�t���ϐ��錾 ===================
		int nFrameTemp = FRAME_FADE_MAX.z - m_nFrame;	//�ޔ�

		// =============== �g�k�X�V ===================
#if _DEBUG
		if (m_nFrame <= FRAME_FADE_MAX.z)	//�t�F�[�h�C��
		{
#endif
			m_UvParam.fUvScale.x = SCALE_IN_MAX + (SCALE_IN_MIN - SCALE_IN_MAX) * (float)(m_nFrame - FRAME_MIN) / (float)(FRAME_FADE_MAX.z);	//�g�k�Z�b�g
#if _DEBUG
		}
		else
		{
			MessageBox(nullptr, "�t���[�������z��𒴉߂��܂���", "Fade.cpp->FadeIn->Error", MB_OK);	//�G���[�ʒm
		}
#endif
	}
	m_UvParam.fUvScale.y = m_UvParam.fUvScale.x;	//x�l�̕ύX��y�l�ɔ��f����

	// =============== ��]�p�X�V ===================
	m_Transform.fRadian.z = DirectX::XMConvertToRadians(ROTATE_EASE_IN_OUT(FRAME_FADE_MAX.x - m_nFrame));	//�t���[�����Ŋp�X�V
	//m_Transform.fRadian.z = DirectX::XMConvertToRadians(ROTATE_ACCEL_RATE * -cosf(3.14159265358979323846264338327950188419f * (float)(m_nFrame - FRAME_MIN) / (float)(FRAME_FADE_MAX.z) - 1) / 2);

	// =============== �J�E���^ ===================
	m_nFrame--;	//�t���[���J�E���g
}