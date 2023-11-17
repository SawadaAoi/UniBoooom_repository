#ifndef __DIRECTWRITE_H__
#define __DIRECTWRITE_H__

#include <dwrite.h>
#include <d2d1.h>
#include <string>
#include <DirectXMath.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")



//＝＝＝＝＝フォントリスト＝＝＝＝＝
enum class Font
{
	Meiryo,
	Arial,
	MairyouUI
};

//＝＝＝＝＝フォント名＝＝＝＝＝
namespace
{
	const WCHAR* FontList[]
	{
		L"メイリオ",
		L"Arial",
		L"Meiryo UI"
	};
}

//＝＝＝＝＝フォント設定＝＝＝＝＝
struct FontData
{
	Font font;								//フォント名
	IDWriteFontCollection* fontCollection;	//フォントコレクション
	DWRITE_FONT_WEIGHT fontWeight;			//フォントの太さ
	DWRITE_FONT_STYLE fontStyle;			//フォントスタイル
	DWRITE_FONT_STRETCH fontStretch;		//フォントの幅
	FLOAT fontSize;							//フォントサイズ
	WCHAR const* localName;					//ローカル名
	DWRITE_TEXT_ALIGNMENT textAlignment;	//テキストの配置
	D2D1_COLOR_F Color;						//フォントの色

	//デフォルトの設定
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

//＝＝＝＝＝DirectWrite設定＝＝＝＝＝
class DirectWrite
{
public:
	DirectWrite();																	//引数付きコンストラクタ1
	DirectWrite(Font font,IDWriteFontCollection* fontCollection,DWRITE_FONT_WEIGHT fontWeight,	//引数付きコンストラクタ2
		DWRITE_FONT_STYLE fontStyle,DWRITE_FONT_STRETCH fontStretch,FLOAT fontSize,
		WCHAR const* localName,DWRITE_TEXT_ALIGNMENT textAlignment,D2D1_COLOR_F Color);
	static void SetFont(FontData* set);																//フォント設定1
	static void SetFont(Font font,IDWriteFontCollection* fontCollection,DWRITE_FONT_WEIGHT fontWeight,	//フォント設定2
		DWRITE_FONT_STYLE fontStyle,DWRITE_FONT_STRETCH fontStretch,FLOAT fontSize,
		WCHAR const* localName,DWRITE_TEXT_ALIGNMENT textAlignment,D2D1_COLOR_F Color);

	static void DrawString(std::string str, DirectX::XMFLOAT2 pos);	//文字表示(書きはじめを指定)
	static void DrawString(std::string str,D2D1_RECT_F rect);			//文字表示(表示場所を四角形で範囲指定)
	static void Init();
	static void Release();

private:
	//すまん、メンバ変数はよくわからん
	static ID2D1Factory*			pID2D1Factory;
	static IDWriteFactory*			pIDWriteFactory;
	static IDWriteTextFormat*		pTextFormat;
	static IDWriteTextLayout*		pTextLayout;
	static ID2D1RenderTarget*		pRT;
	static ID2D1SolidColorBrush*	pSolidBrush;
	static IDXGISurface*			pBackBuffer;

	//フォントデータ
	static FontData* m_pSetting;

	//string型をwstring型に変換
	static std::wstring StringToWString(std::string oString);
};


#endif // !__DIRECTWRITE_H__

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝使い方＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//std::string str = "ABCDEFG";		//表示したい文字列を定義
//DirectX::XMFLOAT2 pos(0.0f, 0.0f);	//画面内の表示したい場所を設定(0.0f,0.0fは左上端)
//
//引数は｢文字列｣｢表示場所｣｢よくわかんないから同じやつで｣
//m_pDirectWrite->DrawString(str, pos, D2D1_DRAW_TEXT_OPTIONS_NONE);	