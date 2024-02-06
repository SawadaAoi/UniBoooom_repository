/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	タイトル用アニメ背景実装(草パターン)
	---------------------------------------
	TitleBgCloud.cpp

	作成者	takagi

	変更履歴
	・2024/01/29 制作 takagi
	・2024/02/06 制作進行 takagi

========================================== */

// =============== インクルード ===================
#include "TitleBgCloud.h"	//自身のヘッダ
#include "Defines.h"		//画面情報用

// =============== 定数定義 ===================
const std::string TEXTURE_FILE = "Assets/Texture/Title/Cloud.png";	//テクスチャファイル名
const int MAX_ANIM(100);											//アニメーション数
const TDiType<int> MAX_SEAT(5, 20);									//5x20
const /*TODO:unsigned*/ int ANIMATION_INTERVAL = 1;					//アニメーションフレーム間隔

/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CTitleBgCloud::CTitleBgCloud()
	:CTitleBgAnimeScaling(MAX_ANIM, MAX_SEAT, ANIMATION_INTERVAL)	//委譲
{
	// =============== 初期化 ===================
	SetTexture(TEXTURE_FILE.c_str());	//テクスチャ登録
	SetLoopFlg(true);					//ループさせる
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
CTitleBgCloud::~CTitleBgCloud()
{
}