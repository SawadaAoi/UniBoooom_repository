/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	Define用ヘッダ
	------------------------------------
	Defines.h
	------------------------------------
	作成者　佐々木先生
		
	変更履歴
	・2024/01/20 コメント改修 takagi
	
========================================== */

#ifndef __DEFINES_H__	//Defines.hインクルードガード
#define __DEFINES_H__

// =============== インクルード ===================
#include <assert.h>		//プログラム異常終了用マクロ定義
#include <Windows.h>	//ウィンドウ操作用
#include <stdarg.h>		//可変長引数の関数作成用
#include <stdio.h>		//入出力用

// =============== 定数・マクロ定義 ===================
#define ASSET(path)	"Assets/"path	//リソースパス(引数の文字列結合)
#define APP_TITLE "UniBoooom!!"		//タイトル名
#define SCREEN_WIDTH (1280)			//画面サイズ(横)
#define SCREEN_HEIGHT (720)			//画面サイズ(縦)
#define DEBUG_GRID_NUM (10)			//グリッド中心から端までの線の数
#define DEBUG_GRID_MARGIN (1.0f)	//グリッド配置幅(メートル換算)

#endif //!__DEFINES_H__