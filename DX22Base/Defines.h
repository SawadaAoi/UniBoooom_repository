/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	Define用ヘッダ
	------------------------------------
	Defines.h
	------------------------------------
	作成者　佐々木先生
		
	変更履歴
	・2024/02/27 Release適合 takagi
	
========================================== */
#ifndef __DEFINES_H__	//Defines.hインクルードガード
#define __DEFINES_H__

#include <assert.h>
#include <Windows.h>
#include <stdarg.h>
#include <stdio.h>

// リソースパス
#define ASSET(path)	"Assets/"path

// タイトル
#define APP_TITLE "UniBoooom!!"

// 画面サイズ
#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (720)

// グリッドサイズ
#define DEBUG_GRID_NUM (10) // グリッド中心から端までの線の数
#define DEBUG_GRID_MARGIN (1.0f) // グリッド配置幅(メートル換算)


#endif // __DEFINES_H__