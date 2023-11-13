#include "DirectWrite.h"
#include "DirectX.h"

//フォント設定
DirectWrite::DirectWrite(FontData* set) 
	:Setting(set) 
	, pID2D1Factory(nullptr)
	, pIDWriteFactory(nullptr)
	, pTextFormat(nullptr)
	, pTextLayout(nullptr)
	, pRT(nullptr)
	, pSolidBrush(nullptr)
	, pBackBuffer()
{
	Setting = new FontData();
	pTextLayout;
}

//フォント設定
DirectWrite::DirectWrite(Font font, IDWriteFontCollection * fontCollection, DWRITE_FONT_WEIGHT fontWeight, 
	DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, FLOAT fontSize, WCHAR const * localName, 
	DWRITE_TEXT_ALIGNMENT textAlignment, D2D1_COLOR_F Color)
{
	DirectWrite::Setting->font = font;
	DirectWrite::Setting->fontCollection = fontCollection;
	DirectWrite::Setting->fontWeight = fontWeight;
	DirectWrite::Setting->fontStretch = fontStretch;
	DirectWrite::Setting->fontSize = fontSize;
	DirectWrite::Setting->localName = localName;
	DirectWrite::Setting->textAlignment = textAlignment;
	DirectWrite::Setting->Color = Color;
}

void DirectWrite::SetFont(FontData * set)
{
	pIDWriteFactory->CreateTextFormat(FontList[(int)set->font], set->fontCollection,set->fontWeight,
		set->fontStyle,set->fontStretch,set->fontSize,set->localName,&pTextFormat);
	pTextFormat->SetTextAlignment(set->textAlignment);
	pRT->CreateSolidColorBrush(set->Color, &pSolidBrush);
}

void DirectWrite::SetFont(Font font, IDWriteFontCollection * fontCollection, DWRITE_FONT_WEIGHT fontWeight, 
	DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, FLOAT fontSize, WCHAR const * localName, 
	DWRITE_TEXT_ALIGNMENT textAlignment, D2D1_COLOR_F Color)
{
	pIDWriteFactory->CreateTextFormat(FontList[(int)font], fontCollection, fontWeight,
		fontStyle, fontStretch, fontSize, localName, &pTextFormat);
	pTextFormat->SetTextAlignment(textAlignment);
	pRT->CreateSolidColorBrush(Color, &pSolidBrush);
}

//文字描画
void DirectWrite::DrawString(std::string str, DirectX::XMFLOAT2 pos, D2D1_DRAW_TEXT_OPTIONS options)
{
	//文字列の変換
	std::wstring wstr = StringToWString(str.c_str());

	//ターゲットサイズの取得
	D2D1_SIZE_F TargetSize = pRT->GetSize();

	//テキストレイアウトを作成
	pIDWriteFactory->CreateTextLayout(wstr.c_str(), wstr.size(), pTextFormat, TargetSize.width, 
		TargetSize.height, &pTextLayout);

	//描画位置の確定
	D2D1_POINT_2F points;
	points.x = pos.x;
	points.y = pos.y;

	//描画の開始
	pRT->BeginDraw();

	//描画の処理
	pRT->DrawTextLayout(points, pTextLayout, pSolidBrush, options);

	//描画の終了
	pRT->EndDraw();
}

//文字描画
void DirectWrite::DrawString(std::string str, D2D1_RECT_F rect, D2D1_DRAW_TEXT_OPTIONS options)
{
	//文字列の変換
	std::wstring wstr = StringToWString(str.c_str());

	//描画の開始
	pRT->BeginDraw();

	//描画処理
	pRT->DrawTextA(wstr.c_str(), wstr.size(), pTextFormat, rect, pSolidBrush, options);

	//描画の終了
	pRT->EndDraw();
}

//初期化
void DirectWrite::Init()
{
	//Direct2D,DirectWriteの初期化
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pID2D1Factory);

	//バックバッファの取得	型:IDXGISwapChain
	GetSwapChain()->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));

	//dpiの設定
	FLOAT dpiX,dpiY;
	pID2D1Factory->GetDesktopDpi(&dpiX, &dpiY);

	//レンダーターゲットの作成
	D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties
	(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, 
		D2D1_ALPHA_MODE_PREMULTIPLIED), dpiX, dpiY);

	//サーフェスに描画するレンダーターゲットを作成
	pID2D1Factory->CreateDxgiSurfaceRenderTarget(pBackBuffer, &props, &pRT);

	//アンチエイリアシングモード
	pRT->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);

	//IDWRITEFactoryの作成
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), 
		reinterpret_cast<IUnknown**>(&pIDWriteFactory));

	pIDWriteFactory->CreateTextFormat(FontList[(int)Setting->font], Setting->fontCollection, 
		Setting->fontWeight, Setting->fontStyle, Setting->fontStretch, 
		Setting->fontSize, Setting->localName, &pTextFormat);

	pRT->CreateSolidColorBrush(Setting->Color, &pSolidBrush);

	pTextLayout;
}

//終了処理
void DirectWrite::Release()
{
	SAFE_DELETE(Setting);
	//文字描画関連のアンロード
	if (pBackBuffer)pBackBuffer->Release();
	if (pSolidBrush)pSolidBrush->Release();
	if (pRT)pRT->Release();
	if (pTextFormat)pTextFormat->Release();
	if (pIDWriteFactory)pIDWriteFactory->Release();
	if (pID2D1Factory)pID2D1Factory->Release();
	if (pTextLayout)pTextLayout->Release();
}

std::wstring DirectWrite::StringToWString(std::string oString)
{
	//SJIS->wstring
	int iBufferSize = MultiByteToWideChar(CP_ACP, 0, oString.c_str(), -1, (wchar_t*)NULL, 0);

	//バッファの取得
	wchar_t* cpUCS2 = new wchar_t[iBufferSize];

	//SJIS->wstring
	MultiByteToWideChar(CP_ACP, 0, oString.c_str(), -1, cpUCS2, iBufferSize);

	//stringの生成
	std::wstring oRet(cpUCS2, cpUCS2 + iBufferSize - 1);

	//バッファーの破棄
	delete[] cpUCS2;

	//変換結果を返す
	return(oRet);

	return std::wstring();
}
