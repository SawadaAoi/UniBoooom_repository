/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	タイトルシーン定義
	---------------------------------------
	Title.h
	------------------------------------
	作成者
			takagi
			nieda

	変更履歴
	・2023/10/26 仮制作 takagi
	・2023/11/05 現段階のコーディング規約適用 takagi
	・2023/11/07 コメント修正 takagi
	・2023/11/16 オーバーライド関数追加 takagi
	・2023/12/16 描画物改善 takagi
	・2024/01/18 継承元リネーム対応 takagi
	・2024/01/20 GetType()関数削除・リファクタリング takagi

========================================== */

#ifndef __TITLE_H__	//Title.hインクルードガード
#define __TITLE_H__

// =============== インクルード ===================
#include "Scene.h"		//親のヘッダ
#include "2dObject.h"	//メンバのヘッダ
#include "UcFlag.h"		//メンバのヘッダ
#include <map>			//連想コンテナ

// =============== クラス定義 =====================
class CTitle :public CScene	//シーン
{
private:
	// ===列挙定義==========
	enum E_FLAG
	{
		//E_FLAG_PAUSEMODE = 0x01,		//ポーズモード
		E_FLAG_COMMAND_CONTINUE = 0x02,	//継続コマンド
		E_FLAG_COMMAND_FINISH = 0x04,	//終了コマンド
		E_FLAG_DECIDE_COMMAND = 0x08,	//コマンド決定状態
		E_FLAG_TIDYING_UP = 0x10,		//片付け中
		//E_FLAG_CALL_FINISH = 0x20,		//終了予約
	};	//フラグ
	enum E_2D	//更新順
	{
		E_2D_BACK,		//背景
		E_2D_START,		//開始コマンド
		E_2D_FINISH,	//終了コマンド
		E_2D_LOGO,		//タイトルロゴ
		E_2D_OPENING,	//開始映像
		E_2D_MAX,		//要素数
	};	//2Dのオブジェクト
	// ===定数定義===========
	const float START_RADIUS_CAMERA = 0.5f;		//初期カメラ距離
	const float END_RADIUS_CAMERA = 15.0f;		//最終カメラ距離
	const int ZOOMOUT_FRAME = 90;				//ズームアウトにかけるフレーム数
	const float COMMAND_SPACE = 120.0f;			//コマンド同士の縦の間
	const float COMMAND_DOWN = 160.0f;			//コマンドを中心からどれだけ下げるか
	const std::map<int, int> MAP_WAIT_START = {
		{E_2D_BACK, 0},	//背景
		{E_2D_START, ZOOMOUT_FRAME},	//開始コマンド
		{E_2D_FINISH, ZOOMOUT_FRAME},	//終了コマンド
		{E_2D_LOGO, 0},		//タイトルロゴ
		{E_2D_OPENING, 0},	//開始映像
	};	//ポリゴンと表示開始待機時間の対応表
	const std::map<int, int> MAP_WAIT_FIN = {
		{E_2D_BACK, 30},	//背景
		{E_2D_START, 15},	//開始コマンド
		{E_2D_FINISH, 30},	//終了コマンド
		{E_2D_LOGO, 15},	//タイトルロゴ
	};	//ポリゴンと表示終了待機時間の対応表
	const std::map<int, std::string> MAP_TEXTURE = {
		{E_2D_BACK, "Assets/Texture//Title/TitleBg.png"},				//背景
		{E_2D_START, "Assets/Texture/Title/Title_Start.png"},			//開始コマンド
		{E_2D_FINISH, "Assets/Texture/Pause/Pause_Finish.png"},			//終了コマンド
		{E_2D_LOGO, "Assets/Texture/Title/TitleLogo.png"},				//タイトルロゴ
		{E_2D_OPENING, "Assets/Texture/Title/titleopening_kari.png"},	//開始映像
	};	//ポリゴンとテクスチャの対応表
	const std::map<int, TPos3d<float>> MAP_POS = {
		{E_2D_BACK, {static_cast<float>(SCREEN_WIDTH) / 2.0f, static_cast<float>(SCREEN_HEIGHT) / 2.0f, 0.0f}},		//背景
		{E_2D_START, {static_cast<float>(SCREEN_WIDTH) / 2.0f, 260.0f, 0.0f}},										//開始コマンド
		{E_2D_FINISH, {static_cast<float>(SCREEN_WIDTH) / 2.0f, 260.0f - COMMAND_SPACE, 0.0f}},						//終了コマンド
		//{E_2D_LOGO, {static_cast<float>(SCREEN_WIDTH) / 2.0f, 450.0f, 0.0f}},										//タイトルロゴ
		{E_2D_OPENING, {static_cast<float>(SCREEN_WIDTH) / 2.0f, static_cast<float>(SCREEN_HEIGHT) / 2.0f, 0.0f}},	//オープニング
	};	//ポリゴンと初期座標の対応表
public:
	// ===プロトタイプ宣言===
	CTitle();							//コンストラクタ
	~CTitle();							//デストラクタ
	void Update() override;				//更新
	void Draw() override;				//描画
	E_TYPE GetNext() const override;	//次のシーンゲッタ
private:
	// ===メンバ変数宣言=====
	CUcFlag m_ucFlag;		//フラグ
	E_TYPE m_eNextScene;	//シーン遷移先
};	//タイトル

#endif	//!__TITLE_H__