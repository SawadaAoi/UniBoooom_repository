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
	・2023/12/11 成績仮表示 takagi

========================================== */

// =============== インクルード ===================
#include "Result.h"	//自身のヘッダ
#include "DirectXTex/TextureLoad.h"	
#include "Pos3d.h"
#include "Sprite.h"
#include "GameParameter.h"
#include "Input.h"
#include <array>					//配列
#include <map>						//連想型コンテナ
#include "Defines.h"				//画面サイズ情報


// =============== 定数定義 ===================
const std::map<int, std::string> MAP_TEX_PATH = {
	{CResult::BG_SCREEN,	"Assets/Texture/Result/ResultBG.png"},			//
	{CResult::BG_TEXT,		"Assets/Texture/Result/result_waku.png"},		//
	{CResult::TEXT_RESULT,	"Assets/Texture/Result/result.png"},			//
	{CResult::TEXT_SVL_TIME, "Assets/Texture/Result/SurvivalTime.png"},		//
	{CResult::TEXT_HUNT_NUM, "Assets/Texture/Result/TotalHunt.png"},			//
	{CResult::TEXT_SCORE,	"Assets/Texture/Result/SCORE.png"},				//
	{CResult::TEXT_NUM,		"Assets/Texture/Result/ResultSpliteSheet.png"},	//
	{CResult::TEXT_COLON,	"Assets/Texture/Result/Colon.png"},				//
	{CResult::STAGE,	"Assets/Texture/Result/Lv1.png"},				//
	{CResult::STAGE_1,	"Assets/Texture/Result/Lv1.png"},				//
	{CResult::STAGE_2,	"Assets/Texture/Result/Lv2.png"},				//
	{CResult::STAGE_3,	"Assets/Texture/Result/Lv3.png"},				//
	{CResult::STAMP,	"Assets/Texture/Result/stamp.png"},				//
};	

const std::map<int, DirectX::XMFLOAT2> MAP_SIZE = {
	{CResult::BG_SCREEN,	{SCREEN_WIDTH, SCREEN_HEIGHT}},
	{CResult::BG_TEXT,		{750.0f, 140.0f}},
	{CResult::TEXT_RESULT,	{320.0f, 85.0f}},
	{CResult::TEXT_SVL_TIME, {300.0f, 100.0f}},
	{CResult::TEXT_HUNT_NUM, {300.0f, 100.0f}},
	{CResult::TEXT_SCORE,	{300.0f, 100.0f}},
	{CResult::TEXT_NUM,		{75.0f, 75.0f}},
	{CResult::TEXT_COLON,	{80.0f, 80.0f}},
	{CResult::STAGE,		{480.0f, 600.0f}},
	{CResult::STAMP,		{400.0f, 400.0f}},
};



const std::map<int, DirectX::XMFLOAT2> MAP_POS = {
	{CResult::BG_SCREEN,	{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}},
	{CResult::TEXT_RESULT,	{970.0f, 120.0f}},
	{CResult::TEXT_SVL_TIME, {850.0f, 240.0f}},
	{CResult::TEXT_HUNT_NUM, {800.0f, 400.0f}},
	{CResult::TEXT_SCORE,	{750.0f, 560.0f}},
	{CResult::STAGE,	{300.0f, 360.0f}},
	{CResult::STAMP,	{300.0f, 360.0f}},
};

const std::map<int, DirectX::XMFLOAT2> MAP_POS_BG_TEXT = {
	{CResult::TEXT_SVL_TIME,	{1030.0f, 280.0f}},
	{CResult::TEXT_HUNT_NUM,	{980.0f, 440.0f}},
	{CResult::TEXT_SCORE, {930.0f, 600.0f}},
};

const float NUM_SPACE = 55.0f;
const TDiType<int> NUM_SPLIT = { 5, 2 };
const TDiType<float> NUM_UVSCALE = { (1.0f / 5) ,(1.0f / 2) };

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

	for (int i = 0; i < E_TEXTURE::TEXTURE_MAX; i++)
	{
		// リザルト画像読込
		m_pTexture[i] = new Texture();
		if (FAILED(m_pTexture[i]->Create(MAP_TEX_PATH.at(i).c_str())))
		{
			MessageBox(NULL, "Result Texture", "Error", MB_OK);
		}
	}
	

	

	// データ受け継ぎ
	m_Data.Load();	//ファイルに上がっている情報を読み込む

	// =============== フォントデータ作成 ===================
	m_Font.SetFontResult();	//専用初期化
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
	for (int i = 0; i < E_TEXTURE::TEXTURE_MAX; i++)
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

	Draw2d(
		MAP_POS.at(E_TEXTURE::BG_SCREEN).x,
		MAP_POS.at(E_TEXTURE::BG_SCREEN).y,
		MAP_SIZE.at(E_TEXTURE::BG_SCREEN).x,
		MAP_SIZE.at(E_TEXTURE::BG_SCREEN).y,
		m_pTexture[E_TEXTURE::BG_SCREEN]);

	Draw2d(
		MAP_POS.at(E_TEXTURE::STAGE).x,
		MAP_POS.at(E_TEXTURE::STAGE).y,
		MAP_SIZE.at(E_TEXTURE::STAGE).x,
		MAP_SIZE.at(E_TEXTURE::STAGE).y,
		m_pTexture[E_TEXTURE::STAGE + m_Data.nStageNum]);


	if (m_Data.GetMinute() >= 3)
	{
		Draw2d(
			MAP_POS.at(E_TEXTURE::STAMP).x,
			MAP_POS.at(E_TEXTURE::STAMP).y,
			MAP_SIZE.at(E_TEXTURE::STAMP).x,
			MAP_SIZE.at(E_TEXTURE::STAMP).y,
			m_pTexture[E_TEXTURE::STAMP]);
	}


	for (int i = CResult::TEXT_SVL_TIME; i <= CResult::TEXT_SCORE; i++)
	{

		// タイトル画面押下ボタン指示画像表示
		Draw2d(
			MAP_POS_BG_TEXT.at(i).x,
			MAP_POS_BG_TEXT.at(i).y,
			MAP_SIZE.at(E_TEXTURE::BG_TEXT).x,
			MAP_SIZE.at(E_TEXTURE::BG_TEXT).y,
			m_pTexture[E_TEXTURE::BG_TEXT]);
	}


	for (int i = TEXT_RESULT; i < E_TEXTURE::TEXT_SCORE + 1; i++)
	{

		// タイトル画面押下ボタン指示画像表示
		Draw2d(
			MAP_POS.at(i).x, 
			MAP_POS.at(i).y, 
			MAP_SIZE.at(i).x,
			MAP_SIZE.at(i).y, 
			m_pTexture[i]);
	}


	
	DispTime(m_Data.GetSecond(), m_Data.GetMinute(), TDiType<float>(1200, 300));


	DispNum(m_Data.nKill, TDiType < float>(1200, 470));

	DispNum(m_Data.nTotalScore, TDiType < float>( 1200,630 ));


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

void CResult::DispTime(int second, int minutes, TDiType<float> pos)
{
	std::vector<int> digitArray;
	DirectX::XMFLOAT4X4 mat;
	int Num = second;
	digitArray.clear();

	if (0 < Num)
	{
		while (Num > 0) {
			digitArray.push_back(Num % 10);
			Num /= 10;
		}

		if (digitArray.size() == 1)
		{
			digitArray.push_back(0);
		}
	}
	else
	{
		digitArray.push_back(0);
		digitArray.push_back(0);
	}




	for (int i = 0; i < digitArray.size(); i++)
	{

		int width = NUM_SPACE * i;
		//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
		DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(pos.x - width, pos.y, 0.0f);
		DirectX::XMStoreFloat4x4(&mat, DirectX::XMMatrixTranspose(world));

		//スプライトの設定
		Sprite::SetWorld(mat);

		int x = digitArray[i] % NUM_SPLIT.x;	//ここ名前募集します
		int y = digitArray[i] / NUM_SPLIT.x;	//配列に入ってる数字の場所を計算してます

		Sprite::SetSize(DirectX::XMFLOAT2(MAP_SIZE.at(E_TEXTURE::TEXT_NUM).x, -MAP_SIZE.at(E_TEXTURE::TEXT_NUM).y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(NUM_UVSCALE.x * x, NUM_UVSCALE.y * y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(NUM_UVSCALE.x, NUM_UVSCALE.y));
		Sprite::SetTexture(m_pTexture[E_TEXTURE::TEXT_NUM]);
		Sprite::Draw();
	}

	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(pos.x - (NUM_SPACE * 2), pos.y, 0.0f);
	DirectX::XMStoreFloat4x4(&mat, DirectX::XMMatrixTranspose(world));

	Sprite::SetWorld(mat);

	Sprite::SetSize(DirectX::XMFLOAT2(80.0f, -80.0f));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[E_TEXTURE::TEXT_COLON]);
	Sprite::Draw();


	Num = minutes;
	digitArray.clear();

	if (0 < Num)
	{
		while (Num > 0) {
			digitArray.push_back(Num % 10);
			Num /= 10;
		}

		if (digitArray.size() == 1)
		{
			digitArray.push_back(0);
		}
	}
	else
	{
		digitArray.push_back(0);
		digitArray.push_back(0);
	}

	for (int i = 0; i < digitArray.size(); i++)
	{

		int width = NUM_SPACE * i;
		//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
		DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(pos.x - (NUM_SPACE * 3) - width, pos.y, 0.0f);
		DirectX::XMStoreFloat4x4(&mat, DirectX::XMMatrixTranspose(world));

		//スプライトの設定
		Sprite::SetWorld(mat);

		int x = digitArray[i] % NUM_SPLIT.x;	//ここ名前募集します
		int y = digitArray[i] / NUM_SPLIT.x;	//配列に入ってる数字の場所を計算してます

		Sprite::SetSize(DirectX::XMFLOAT2(MAP_SIZE.at(E_TEXTURE::TEXT_NUM).x, -MAP_SIZE.at(E_TEXTURE::TEXT_NUM).y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(NUM_UVSCALE.x * x, NUM_UVSCALE.y * y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(NUM_UVSCALE.x, NUM_UVSCALE.y));
		Sprite::SetTexture(m_pTexture[E_TEXTURE::TEXT_NUM]);
		Sprite::Draw();
	}
}

void CResult::DispNum(int dispNum, TDiType<float> pos)
{

	std::vector<int> digitArray;
	DirectX::XMFLOAT4X4 mat;
	int Num = dispNum;


	digitArray.clear();

	if (0 < Num)
	{
		while (Num > 0) {
			digitArray.push_back(Num % 10);
			Num /= 10;
		}
	}
	else
	{
		digitArray.push_back(0);
	}


	

	for (int i = 0; i < digitArray.size(); i++)
	{

		int width = NUM_SPACE * i;
		//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
		DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(pos.x - width, pos.y, 0.0f);
		DirectX::XMStoreFloat4x4(&mat, DirectX::XMMatrixTranspose(world));

		//スプライトの設定
		Sprite::SetWorld(mat);

		int x = digitArray[i] % NUM_SPLIT.x;	//ここ名前募集します
		int y = digitArray[i] / NUM_SPLIT.x;	//配列に入ってる数字の場所を計算してます

		Sprite::SetSize(DirectX::XMFLOAT2(MAP_SIZE.at(E_TEXTURE::TEXT_NUM).x, -MAP_SIZE.at(E_TEXTURE::TEXT_NUM).y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(NUM_UVSCALE.x * x, NUM_UVSCALE.y * y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(NUM_UVSCALE.x, NUM_UVSCALE.y));
		Sprite::SetTexture(m_pTexture[E_TEXTURE::TEXT_NUM]);
		Sprite::Draw();
	}
}
