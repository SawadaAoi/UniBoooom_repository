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
	引数付きコンストラクタ(簡易版)
	-------------------------------------
	フォントの設定
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：無し
=========================================== */
DirectWrite::DirectWrite() 
{
	m_pSetting = new FontData();
	pTextLayout;
}

/* ========================================
	引数付きコンストラクタ(全部自分で設定)
	-------------------------------------
	フォントの設定
	-------------------------------------
	引数1：書体												Font型
	引数2：よく分からんけどnullptrでいい					
	引数3：文字の太さ										IDWriteFontCollection型
	引数4：普通にするかイタリックとかにするか				DWRITE_FONT_WEIGHT型
	引数5：縦横比を変更										DWRITE_FONT_STYLE型
	引数6：文字の大きさ										DWRITE_FONT_STRETCH型
	引数7：よくわからん										FLOAT型
	引数8：表示場所に対して前詰めか中央か後ろ詰め表示か 	WCHAR const *型
	引数9：文字の色											DWRITE_TEXT_ALIGNMENT型
	-------------------------------------					D2D1_COLOR_F型
	戻値：無し
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
	デストラクタ
	-------------------------------------
	終了処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
DirectWrite::~DirectWrite()
{
	if (m_pSetting)
	{
		SAFE_DELETE(m_pSetting);
	}
}

/* ========================================
	フォントセット関数
	-------------------------------------
	フォントの設定
	-------------------------------------
	引数1：書体
	引数2：よく分からんけどnullptrでいい					Font型
	引数3：文字の太さ										IDWriteFontCollection型
	引数4：普通にするかイタリックとかにするか				DWRITE_FONT_WEIGHT型
	引数5：縦横比を変更										DWRITE_FONT_STYLE型
	引数6：文字の大きさ										DWRITE_FONT_STRETCH型
	引数7：よくわからん										FLOAT型
	引数8：表示場所に対して前詰めか中央か後ろ詰め表示か 	WCHAR const *型
	引数9：文字の色											DWRITE_TEXT_ALIGNMENT型
	-------------------------------------					D2D1_COLOR_F型
	戻値：無し
=========================================== */
void DirectWrite::SetFont(FontData * set)
{
	pIDWriteFactory->CreateTextFormat(FontList[(int)set->font], set->fontCollection,set->fontWeight,
		set->fontStyle,set->fontStretch,set->fontSize,set->localName,&pTextFormat);
	pTextFormat->SetTextAlignment(set->textAlignment);
	pRT->CreateSolidColorBrush(set->Color, &pSolidBrush);
}

/* ========================================
	フォントセット関数
	-------------------------------------
	フォントの設定
	-------------------------------------
	引数1：書体
	引数2：よく分からんけどnullptrでいい					Font型
	引数3：文字の太さ										IDWriteFontCollection型
	引数4：普通にするかイタリックとかにするか				DWRITE_FONT_WEIGHT型
	引数5：縦横比を変更										DWRITE_FONT_STYLE型
	引数6：文字の大きさ										DWRITE_FONT_STRETCH型
	引数7：よくわからん										FLOAT型
	引数8：表示場所に対して前詰めか中央か後ろ詰め表示か 	WCHAR const *型
	引数9：文字の色											DWRITE_TEXT_ALIGNMENT型
	-------------------------------------					D2D1_COLOR_F型
	戻値：無し
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
	フォントセット関数
	-------------------------------------
	フォントの設定
	-------------------------------------
	引数1：表示したい文字
	引数2：表示したい場所をXY座標で((0,0)は左上)
	-------------------------------------
	戻値：無し
=========================================== */
void DirectWrite::DrawString(std::string str, DirectX::XMFLOAT2 pos)
{
	//文字列の変換
	std::wstring wstr = StringToWString(str.c_str());

	//ターゲットサイズの取得
	D2D1_SIZE_F TargetSize = pRT->GetSize();

	//テキストレイアウトを作成
	pIDWriteFactory->CreateTextLayout(wstr.c_str(), static_cast<unsigned int>(wstr.size()), pTextFormat, TargetSize.width, 
		TargetSize.height, &pTextLayout);

	//描画位置の確定
	D2D1_POINT_2F points;
	points.x = pos.x;
	points.y = pos.y;

	//描画の開始
	pRT->BeginDraw();

	//描画の処理
	pRT->DrawTextLayout(points, pTextLayout, pSolidBrush, D2D1_DRAW_TEXT_OPTIONS_NONE);

	//描画の終了
	pRT->EndDraw();
}

/* ========================================
	フォントセット関数
	-------------------------------------
	フォントの設定
	-------------------------------------
	引数1：表示したい文字
	引数2：表示したい場所を左上右下の順番で設定((0,0)は左上)
	-------------------------------------
	戻値：無し
=========================================== */
void DirectWrite::DrawString(std::string str, D2D1_RECT_F rect)
{
	//文字列の変換
	std::wstring wstr = StringToWString(str.c_str());

	//描画の開始
	pRT->BeginDraw();

	//描画処理
	pRT->DrawTextA(wstr.c_str(), static_cast<unsigned int>(wstr.size()), pTextFormat, rect, pSolidBrush, D2D1_DRAW_TEXT_OPTIONS_NONE);

	//描画の終了
	pRT->EndDraw();
}

/* ========================================
	このクラスの初期化(DirectX.cppで呼んでるから他の所では書かない)
	-------------------------------------
	マジで何やってるか分からん	参考サイト"https://islingtonsystem.hatenablog.jp/entry/2022/06/18/222040"
	-------------------------------------
	引数1：
	戻値：無し
=========================================== */
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

	pIDWriteFactory->CreateTextFormat(FontList[(int)m_pSetting->font], m_pSetting->fontCollection, 
		m_pSetting->fontWeight, m_pSetting->fontStyle, m_pSetting->fontStretch, 
		m_pSetting->fontSize, m_pSetting->localName, &pTextFormat);

	pRT->CreateSolidColorBrush(m_pSetting->Color, &pSolidBrush);

	pTextLayout;
}

/* ========================================
	このクラスの終了処理(DirectX.cppで呼んでるから他の所では書かない)
	-------------------------------------
	色んなものをリリース
	-------------------------------------
	引数1：
	戻値：無し
=========================================== */
void DirectWrite::Release()
{
	SAFE_DELETE(m_pSetting);
	//文字描画関連のアンロード
	if (pBackBuffer)pBackBuffer->Release();
	if (pSolidBrush)pSolidBrush->Release();
	if (pRT)pRT->Release();
	if (pTextFormat)pTextFormat->Release();
	if (pIDWriteFactory)pIDWriteFactory->Release();
	if (pID2D1Factory)pID2D1Factory->Release();
	if (pTextLayout)pTextLayout->Release();
}

/* ========================================
	SJIS変換関数
	-------------------------------------
	なんかSJISも使えるようになるらしい
	-------------------------------------
	引数1：文字列
	戻値：無し
=========================================== */
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

/* ========================================
	フォント用コンストラクタ
	-------------------------------------
	フォント初期化
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：無し
=========================================== */
FontData::FontData()
{
	// =============== 初期化 ===================
	font = Font::Arial;														//書体：Arial
	fontCollection = nullptr;												//?
	fontWeight = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_NORMAL;				//文字の太さ
	fontStyle = DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL;				//斜体無し
	fontStretch = DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_NORMAL;			//?
	fontSize = 20;															//文字の大きさ
	localName = L"ja-jp";													//?
	textAlignment = DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_LEADING;	//左端基準
	Color = D2D1::ColorF(D2D1::ColorF::Black);								//文字色：黒
}

/* ========================================
	リザルト用フォント情報登録関数
	-------------------------------------
	リザルト用にフォント変更
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：無し
=========================================== */
void FontData::SetFontResult()
{
	// =============== 初期化 ===================
	font = Font::Arial;														//書体：Arial
	fontCollection = nullptr;												//?
	fontWeight = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_SEMI_BOLD;			//文字の太さ
	fontStyle = DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_ITALIC;				//イタリック体
	fontStretch = DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_NORMAL;			//?
	fontSize = 45;															//文字の大きさ
	localName = L"ja-jp";													//?
	textAlignment = DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_LEADING;	//左端基準
	Color = D2D1::ColorF(D2D1::ColorF::Black);								//文字色：黒

}