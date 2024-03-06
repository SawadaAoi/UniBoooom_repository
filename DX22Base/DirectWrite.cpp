#include "DirectWrite.h"
#include "DirectX.h"

FontData*				DirectWrite::m_pSetting = nullptr;
ID2D1Factory*			DirectWrite::pID2D1Factory = nullptr;
IDWriteFactory*			DirectWrite::pIDWriteFactory = nullptr;
IDWriteTextFormat*		DirectWrite::pTextFormat = nullptr;
IDWriteTextLayout*		DirectWrite::pTextLayout = nullptr;
ID2D1RenderTarget*		DirectWrite::pRT = nullptr;
ID2D1SolidColorBrush*	DirectWrite::pSolidBrush = nullptr;
IDXGISurface*			DirectWrite::pBackBuffer = nullptr;

/* ========================================
	�����t���R���X�g���N�^(�ȈՔ�)
	-------------------------------------
	�t�H���g�̐ݒ�
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F����
=========================================== */
DirectWrite::DirectWrite() 
{
	m_pSetting = new FontData();
	pTextLayout;
}

/* ========================================
	�����t���R���X�g���N�^(�S�������Őݒ�)
	-------------------------------------
	�t�H���g�̐ݒ�
	-------------------------------------
	����1�F����												Font�^
	����2�F�悭������񂯂�nullptr�ł���					
	����3�F�����̑���										IDWriteFontCollection�^
	����4�F���ʂɂ��邩�C�^���b�N�Ƃ��ɂ��邩				DWRITE_FONT_WEIGHT�^
	����5�F�c�����ύX										DWRITE_FONT_STYLE�^
	����6�F�����̑傫��										DWRITE_FONT_STRETCH�^
	����7�F�悭�킩���										FLOAT�^
	����8�F�\���ꏊ�ɑ΂��đO�l�߂����������l�ߕ\���� 	WCHAR const *�^
	����9�F�����̐F											DWRITE_TEXT_ALIGNMENT�^
	-------------------------------------					D2D1_COLOR_F�^
	�ߒl�F����
=========================================== */
DirectWrite::DirectWrite(Font font, IDWriteFontCollection * fontCollection, DWRITE_FONT_WEIGHT fontWeight, 
	DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, FLOAT fontSize, WCHAR const * localName, 
	DWRITE_TEXT_ALIGNMENT textAlignment, D2D1_COLOR_F Color)
{
	DirectWrite::m_pSetting->font = font;
	DirectWrite::m_pSetting->fontCollection = fontCollection;
	DirectWrite::m_pSetting->fontWeight = fontWeight;
	DirectWrite::m_pSetting->fontStretch = fontStretch;
	DirectWrite::m_pSetting->fontSize = fontSize;
	DirectWrite::m_pSetting->localName = localName;
	DirectWrite::m_pSetting->textAlignment = textAlignment;
	DirectWrite::m_pSetting->Color = Color;
}

/* ========================================
	�f�X�g���N�^
	-------------------------------------
	�I������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
DirectWrite::~DirectWrite()
{
	if (m_pSetting)
	{
		SAFE_DELETE(m_pSetting);
	}
}

/* ========================================
	�t�H���g�Z�b�g�֐�
	-------------------------------------
	�t�H���g�̐ݒ�
	-------------------------------------
	����1�F����
	����2�F�悭������񂯂�nullptr�ł���					Font�^
	����3�F�����̑���										IDWriteFontCollection�^
	����4�F���ʂɂ��邩�C�^���b�N�Ƃ��ɂ��邩				DWRITE_FONT_WEIGHT�^
	����5�F�c�����ύX										DWRITE_FONT_STYLE�^
	����6�F�����̑傫��										DWRITE_FONT_STRETCH�^
	����7�F�悭�킩���										FLOAT�^
	����8�F�\���ꏊ�ɑ΂��đO�l�߂����������l�ߕ\���� 	WCHAR const *�^
	����9�F�����̐F											DWRITE_TEXT_ALIGNMENT�^
	-------------------------------------					D2D1_COLOR_F�^
	�ߒl�F����
=========================================== */
void DirectWrite::SetFont(FontData * set)
{
	pIDWriteFactory->CreateTextFormat(FontList[(int)set->font], set->fontCollection,set->fontWeight,
		set->fontStyle,set->fontStretch,set->fontSize,set->localName,&pTextFormat);
	pTextFormat->SetTextAlignment(set->textAlignment);
	pRT->CreateSolidColorBrush(set->Color, &pSolidBrush);
}

/* ========================================
	�t�H���g�Z�b�g�֐�
	-------------------------------------
	�t�H���g�̐ݒ�
	-------------------------------------
	����1�F����
	����2�F�悭������񂯂�nullptr�ł���					Font�^
	����3�F�����̑���										IDWriteFontCollection�^
	����4�F���ʂɂ��邩�C�^���b�N�Ƃ��ɂ��邩				DWRITE_FONT_WEIGHT�^
	����5�F�c�����ύX										DWRITE_FONT_STYLE�^
	����6�F�����̑傫��										DWRITE_FONT_STRETCH�^
	����7�F�悭�킩���										FLOAT�^
	����8�F�\���ꏊ�ɑ΂��đO�l�߂����������l�ߕ\���� 	WCHAR const *�^
	����9�F�����̐F											DWRITE_TEXT_ALIGNMENT�^
	-------------------------------------					D2D1_COLOR_F�^
	�ߒl�F����
=========================================== */
void DirectWrite::SetFont(Font font, IDWriteFontCollection * fontCollection, DWRITE_FONT_WEIGHT fontWeight, 
	DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, FLOAT fontSize, WCHAR const * localName, 
	DWRITE_TEXT_ALIGNMENT textAlignment, D2D1_COLOR_F Color)
{
	pIDWriteFactory->CreateTextFormat(FontList[(int)font], fontCollection, fontWeight,
		fontStyle, fontStretch, fontSize, localName, &pTextFormat);
	pTextFormat->SetTextAlignment(textAlignment);
	pRT->CreateSolidColorBrush(Color, &pSolidBrush);
}

/* ========================================
	�t�H���g�Z�b�g�֐�
	-------------------------------------
	�t�H���g�̐ݒ�
	-------------------------------------
	����1�F�\������������
	����2�F�\���������ꏊ��XY���W��((0,0)�͍���)
	-------------------------------------
	�ߒl�F����
=========================================== */
void DirectWrite::DrawString(std::string str, DirectX::XMFLOAT2 pos)
{
	//������̕ϊ�
	std::wstring wstr = StringToWString(str.c_str());

	//�^�[�Q�b�g�T�C�Y�̎擾
	D2D1_SIZE_F TargetSize = pRT->GetSize();

	//�e�L�X�g���C�A�E�g���쐬
	pIDWriteFactory->CreateTextLayout(wstr.c_str(), static_cast<unsigned int>(wstr.size()), pTextFormat, TargetSize.width, 
		TargetSize.height, &pTextLayout);

	//�`��ʒu�̊m��
	D2D1_POINT_2F points;
	points.x = pos.x;
	points.y = pos.y;

	//�`��̊J�n
	pRT->BeginDraw();

	//�`��̏���
	pRT->DrawTextLayout(points, pTextLayout, pSolidBrush, D2D1_DRAW_TEXT_OPTIONS_NONE);

	//�`��̏I��
	pRT->EndDraw();
}

/* ========================================
	�t�H���g�Z�b�g�֐�
	-------------------------------------
	�t�H���g�̐ݒ�
	-------------------------------------
	����1�F�\������������
	����2�F�\���������ꏊ������E���̏��ԂŐݒ�((0,0)�͍���)
	-------------------------------------
	�ߒl�F����
=========================================== */
void DirectWrite::DrawString(std::string str, D2D1_RECT_F rect)
{
	//������̕ϊ�
	std::wstring wstr = StringToWString(str.c_str());

	//�`��̊J�n
	pRT->BeginDraw();

	//�`�揈��
	pRT->DrawTextA(wstr.c_str(), static_cast<unsigned int>(wstr.size()), pTextFormat, rect, pSolidBrush, D2D1_DRAW_TEXT_OPTIONS_NONE);

	//�`��̏I��
	pRT->EndDraw();
}

/* ========================================
	���̃N���X�̏�����(DirectX.cpp�ŌĂ�ł邩�瑼�̏��ł͏����Ȃ�)
	-------------------------------------
	�}�W�ŉ�����Ă邩�������	�Q�l�T�C�g"https://islingtonsystem.hatenablog.jp/entry/2022/06/18/222040"
	-------------------------------------
	����1�F
	�ߒl�F����
=========================================== */
void DirectWrite::Init()
{
	//Direct2D,DirectWrite�̏�����
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pID2D1Factory);

	//�o�b�N�o�b�t�@�̎擾	�^:IDXGISwapChain
	GetSwapChain()->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));

	//dpi�̐ݒ�
	FLOAT dpiX,dpiY;
	pID2D1Factory->GetDesktopDpi(&dpiX, &dpiY);

	//�����_�[�^�[�Q�b�g�̍쐬
	D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties
	(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, 
		D2D1_ALPHA_MODE_PREMULTIPLIED), dpiX, dpiY);

	//�T�[�t�F�X�ɕ`�悷�郌���_�[�^�[�Q�b�g���쐬
	pID2D1Factory->CreateDxgiSurfaceRenderTarget(pBackBuffer, &props, &pRT);

	//�A���`�G�C���A�V���O���[�h
	pRT->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);

	//IDWRITEFactory�̍쐬
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), 
		reinterpret_cast<IUnknown**>(&pIDWriteFactory));

	pIDWriteFactory->CreateTextFormat(FontList[(int)m_pSetting->font], m_pSetting->fontCollection, 
		m_pSetting->fontWeight, m_pSetting->fontStyle, m_pSetting->fontStretch, 
		m_pSetting->fontSize, m_pSetting->localName, &pTextFormat);

	pRT->CreateSolidColorBrush(m_pSetting->Color, &pSolidBrush);

	pTextLayout;
}

/* ========================================
	���̃N���X�̏I������(DirectX.cpp�ŌĂ�ł邩�瑼�̏��ł͏����Ȃ�)
	-------------------------------------
	�F��Ȃ��̂������[�X
	-------------------------------------
	����1�F
	�ߒl�F����
=========================================== */
void DirectWrite::Release()
{
	SAFE_DELETE(m_pSetting);
	//�����`��֘A�̃A�����[�h
	if (pBackBuffer)pBackBuffer->Release();
	if (pSolidBrush)pSolidBrush->Release();
	if (pRT)pRT->Release();
	if (pTextFormat)pTextFormat->Release();
	if (pIDWriteFactory)pIDWriteFactory->Release();
	if (pID2D1Factory)pID2D1Factory->Release();
	if (pTextLayout)pTextLayout->Release();
}

/* ========================================
	SJIS�ϊ��֐�
	-------------------------------------
	�Ȃ�SJIS���g����悤�ɂȂ�炵��
	-------------------------------------
	����1�F������
	�ߒl�F����
=========================================== */
std::wstring DirectWrite::StringToWString(std::string oString)
{
	//SJIS->wstring
	int iBufferSize = MultiByteToWideChar(CP_ACP, 0, oString.c_str(), -1, (wchar_t*)NULL, 0);

	//�o�b�t�@�̎擾
	wchar_t* cpUCS2 = new wchar_t[iBufferSize];

	//SJIS->wstring
	MultiByteToWideChar(CP_ACP, 0, oString.c_str(), -1, cpUCS2, iBufferSize);

	//string�̐���
	std::wstring oRet(cpUCS2, cpUCS2 + iBufferSize - 1);

	//�o�b�t�@�[�̔j��
	delete[] cpUCS2;

	//�ϊ����ʂ�Ԃ�
	return(oRet);

	return std::wstring();
}

/* ========================================
	�t�H���g�p�R���X�g���N�^
	-------------------------------------
	�t�H���g������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F����
=========================================== */
FontData::FontData()
{
	// =============== ������ ===================
	font = Font::Arial;														//���́FArial
	fontCollection = nullptr;												//?
	fontWeight = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_NORMAL;				//�����̑���
	fontStyle = DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL;				//�Α̖���
	fontStretch = DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_NORMAL;			//?
	fontSize = 20;															//�����̑傫��
	localName = L"ja-jp";													//?
	textAlignment = DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_LEADING;	//���[�
	Color = D2D1::ColorF(D2D1::ColorF::Black);								//�����F�F��
}

/* ========================================
	���U���g�p�t�H���g���o�^�֐�
	-------------------------------------
	���U���g�p�Ƀt�H���g�ύX
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F����
=========================================== */
void FontData::SetFontResult()
{
	// =============== ������ ===================
	font = Font::Arial;														//���́FArial
	fontCollection = nullptr;												//?
	fontWeight = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_SEMI_BOLD;			//�����̑���
	fontStyle = DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_ITALIC;				//�C�^���b�N��
	fontStretch = DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_NORMAL;			//?
	fontSize = 45;															//�����̑傫��
	localName = L"ja-jp";													//?
	textAlignment = DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_LEADING;	//���[�
	Color = D2D1::ColorF(D2D1::ColorF::Black);								//�����F�F��

}