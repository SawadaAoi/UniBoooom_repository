/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	タイトルシーン実装
	---------------------------------------
	Title.cpp

	作成者
			takagi
			nieda

	変更履歴
	・2023/10/26 仮制作 takagi
	・2023/11/05 現段階のコーディング規約適用 takagi
	・2023/11/07 コメント修正 takagi
	・2023/11/16 オーバーライド関数追加 takagi
	・2023/11/22 仮テクスチャ表示、画面遷移 nieda
	・2023/11/23 コントローラーに対応 nieda
	・2023/11/24 コメント、定数定義、列挙追加 nieda

========================================== */

// =============== インクルード ===================
#include "Title.h"	//自身のヘッダ
#include "DirectXTex/TextureLoad.h"
#include "Pos3d.h"
#include "Sprite.h"
#include "GameParameter.h"
#include "Input.h"


/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CTitle::CTitle()
{
	// タイトル画像読込
	m_pTexture[E_TITLE_TITLE] = new Texture();
	if (FAILED(m_pTexture[E_TITLE_TITLE]->Create("Assets/Texture/gamestart.png")))
	{
		MessageBox(NULL, "Title gamstart.png", "Error", MB_OK);
	}

	// タイトル画面押下ボタン指示画像読込
	m_pTexture[E_TITLE_BUTTON] = new Texture();
	if (FAILED(m_pTexture[E_TITLE_BUTTON]->Create("Assets/Texture/pre_title.png")))
	{
		MessageBox(NULL, "Title pre_title.png", "Error", MB_OK);
	}
}

/* ========================================
	デストラクタ
	----------------------------------------
	内容：破棄時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CTitle::~CTitle()
{
	// 破棄処理
	for (int i = 0; i >= E_TITLE_MAX; ++i)
	{
		SAFE_DELETE(m_pTexture[i]);
	}
}

/* ========================================
	更新関数
	----------------------------------------
	内容：更新処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CTitle::Update()
{
	// スペースキーを押した時、またはコントローラのBボタンを押した時 
	if (IsKeyTrigger(VK_SPACE) || IsKeyTriggerController(BUTTON_B))
	{
		m_bFinish = true;	// タイトルシーン終了フラグON
	}
}

/* ========================================
	描画関数
	----------------------------------------
	内容：描画処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
	======================================== */
void CTitle::Draw()
{
	// タイトル画像表示
	Draw2d(TEXTURE_TITLE_TITLE_POSX
		, TEXTURE_TITLE_TITLE_POSY
		, TEXTURE_TITLE_TITLE_WIDTH
		, TEXTURE_TITLE_TITLE_HEIGHT
		, m_pTexture[E_TITLE_TITLE]);

	// タイトル画面押下ボタン指示画像表示
	Draw2d(TEXTURE_TITLE_BUTTON_POSX
		, TEXTURE_TITLE_BUTTON_POSY
		, TEXTURE_TITLE_BUTTON_WIDTH
		, TEXTURE_TITLE_BUTTON_HEIGHT
		, m_pTexture[E_TITLE_BUTTON]);
}

/* ========================================
	種類ゲッタ
	----------------------------------------
	内容：自身がタイトルシーンであることを示す
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：自身の種類
=========================================== */
CTitle::E_TYPE CTitle::GetType() const
{
	// =============== 提供 ===================
	return CTitle::E_TYPE_TITLE;	//自身の種類
}

/* ========================================
	次シーンゲッタ
	----------------------------------------
	内容：遷移したいシーンが何かを示す
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：遷移先シーンの種類
=========================================== */
CTitle::E_TYPE CTitle::GetNext() const
{
	// =============== 提供 ===================
	return CTitle::E_TYPE_STAGE1;	//遷移先シーンの種類
}
