/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	タイトル用開始コマンド定義
	---------------------------------------
	TitleCommandStart.h

	作成者	takagi

	変更履歴
	・2024/02/02 制作 takagi
	・2024/02/05 制作進行 takagi

========================================== */

#ifndef __TITLE_COMMAND_START_H__	//TitleCommandStart.hインクルードガード
#define __TITLE_COMMAND_START_H__

// =============== インクルード =====================
#include "TitleCommand.h"	//親のヘッダ

// =============== クラス定義 =====================
class CTitleCommandStart :public CTitleCommand	//タイトル用コマンド
{
public:
	// ===プロトタイプ宣言===
	CTitleCommandStart();			//コンストラクタ
	virtual ~CTitleCommandStart();	//デストラクタ
};	//開始コマンド

#endif	//!__TITLE_COMMAND_START_H__