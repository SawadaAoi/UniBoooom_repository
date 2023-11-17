#ifndef __DIRECTWRITE_H__
#define __DIRECTWRITE_H__

#include <dwrite.h>
#include <d2d1.h>
#include <string>
#include <DirectXMath.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")



//�����������t�H���g���X�g����������
enum class Font
{
	Meiryo,
	Arial,
	MairyouUI
};

//�����������t�H���g������������
namespace
{
	const WCHAR* FontList[]
	{
		L"���C���I",
		L"Arial",
		L"Meiryo UI"
	};
}

//�����������t�H���g�ݒ聁��������
struct FontData
{
	Font font;								//�t�H���g��
	IDWriteFontCollection* fontCollection;	//�t�H���g�R���N�V����
	DWRITE_FONT_WEIGHT fontWeight;			//�t�H���g�̑���
	DWRITE_FONT_STYLE fontStyle;			//�t�H���g�X�^�C��
	DWRITE_FONT_STRETCH fontStretch;		//�t�H���g�̕�
	FLOAT fontSize;							//�t�H���g�T�C�Y
	WCHAR const* localName;					//���[�J����
	DWRITE_TEXT_ALIGNMENT textAlignment;	//�e�L�X�g�̔z�u
	D2D1_COLOR_F Color;						//�t�H���g�̐F

	//�f�t�H���g�̐ݒ�
	FontData()
	{
		font			= Font::Arial;
		fontCollection	= nullptr;
		fontWeight		= DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_NORMAL;
		fontStyle		= DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL;
		fontStretch		= DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_NORMAL;
		fontSize		= 20;
		localName		= L"ja-jp";
		textAlignment	= DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_LEADING;
		Color			= D2D1::ColorF(D2D1::ColorF::Black);
	}
};

//����������DirectWrite�ݒ聁��������
class DirectWrite
{
public:
	DirectWrite();																	//�����t���R���X�g���N�^1
	DirectWrite(Font font,IDWriteFontCollection* fontCollection,DWRITE_FONT_WEIGHT fontWeight,	//�����t���R���X�g���N�^2
		DWRITE_FONT_STYLE fontStyle,DWRITE_FONT_STRETCH fontStretch,FLOAT fontSize,
		WCHAR const* localName,DWRITE_TEXT_ALIGNMENT textAlignment,D2D1_COLOR_F Color);
	static void SetFont(FontData* set);																//�t�H���g�ݒ�1
	static void SetFont(Font font,IDWriteFontCollection* fontCollection,DWRITE_FONT_WEIGHT fontWeight,	//�t�H���g�ݒ�2
		DWRITE_FONT_STYLE fontStyle,DWRITE_FONT_STRETCH fontStretch,FLOAT fontSize,
		WCHAR const* localName,DWRITE_TEXT_ALIGNMENT textAlignment,D2D1_COLOR_F Color);

	static void DrawString(std::string str, DirectX::XMFLOAT2 pos);	//�����\��(�����͂��߂��w��)
	static void DrawString(std::string str,D2D1_RECT_F rect);			//�����\��(�\���ꏊ���l�p�`�Ŕ͈͎w��)
	static void Init();
	static void Release();

private:
	//���܂�A�����o�ϐ��͂悭�킩���
	static ID2D1Factory*			pID2D1Factory;
	static IDWriteFactory*			pIDWriteFactory;
	static IDWriteTextFormat*		pTextFormat;
	static IDWriteTextLayout*		pTextLayout;
	static ID2D1RenderTarget*		pRT;
	static ID2D1SolidColorBrush*	pSolidBrush;
	static IDXGISurface*			pBackBuffer;

	//�t�H���g�f�[�^
	static FontData* m_pSetting;

	//string�^��wstring�^�ɕϊ�
	static std::wstring StringToWString(std::string oString);
};


#endif // !__DIRECTWRITE_H__

//�����������������������������������������g��������������������������������������������
//std::string str = "ABCDEFG";		//�\����������������`
//DirectX::XMFLOAT2 pos(0.0f, 0.0f);	//��ʓ��̕\���������ꏊ��ݒ�(0.0f,0.0f�͍���[)
//
//�����͢�����񣢕\���ꏊ���悭�킩��Ȃ����瓯����ţ
//m_pDirectWrite->DrawString(str, pos, D2D1_DRAW_TEXT_OPTIONS_NONE);	