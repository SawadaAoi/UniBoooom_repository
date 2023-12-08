/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	リザルトシーン実装
	---------------------------------------
	Result.cpp

	作成者
			takagi
			nieda

	変更履歴
	・2023/11/16 制作 takagi
	・2023/11/20 仮テクスチャ表示、画面遷移 nieda
	・2023/11/23 コントローラーに対応 nieda
	・2023/11/24 コメント、定数定義、列挙追加 nieda
	・2023/12/08 シーン遷移用に変数追加 takagi

========================================== */

// =============== インクルード ===================
#include "Result.h"	//自身のヘッダ
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
CResult::CResult()
{
	// リザルト画像読込
	m_pTexture[E_RESULT_RESULT] = new Texture();
	if (FAILED(m_pTexture[E_RESULT_RESULT]->Create("Assets/Texture/gamestart.png")))
	{
		MessageBox(NULL, "Result gamestart.png", "Error", MB_OK);
	}

	// リザルト画面押下ボタン指示画像読込
	m_pTexture[E_RESULT_BUTTON] = new Texture();
	if (FAILED(m_pTexture[E_RESULT_BUTTON]->Create("Assets/Texture/pre_result.png")))
	{
		MessageBox(NULL, "Result pre_result.png", "Error", MB_OK);
	}

	// データ受け継ぎ
	m_Data.Load();	//ファイルに上がっている情報を読み込む
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
CResult::~CResult()
{
	// 破棄処理
	for (int i = 0; i >= E_RESULT_MAX; ++i)
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
void CResult::Update()
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
void CResult::Draw()
{
	// タイトル画像表示
	Draw2d(TEXTURE_TITLE_TITLE_POSX
		, TEXTURE_TITLE_TITLE_POSY
		, TEXTURE_TITLE_TITLE_WIDTH
		, TEXTURE_TITLE_TITLE_HEIGHT
		, m_pTexture[E_RESULT_RESULT]);

	// タイトル画面押下ボタン指示画像表示
	Draw2d(TEXTURE_TITLE_BUTTON_POSX
		, TEXTURE_TITLE_BUTTON_POSY
		, TEXTURE_TITLE_BUTTON_WIDTH
		, TEXTURE_TITLE_BUTTON_HEIGHT
		, m_pTexture[E_RESULT_BUTTON]);
}

/* ========================================
	種類ゲッタ
	----------------------------------------
	内容：自身がリザルトシーンであることを示す
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：自身の種類
=========================================== */
CResult::E_TYPE CResult::GetType() const
{
	// =============== 提供 ===================
	return CResult::E_TYPE_RESULT;	//自身の種類
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
CResult::E_TYPE CResult::GetNext() const
{
	// =============== 提供 ===================
	return CResult::E_TYPE_TITLE;	//遷移先シーンの種類
}
