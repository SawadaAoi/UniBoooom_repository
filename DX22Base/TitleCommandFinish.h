/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	タイトル用終了コマンド定義
	---------------------------------------
	TitleCommandFinish.h

	作成者	takagi

	変更履歴
	・2024/02/02 制作 takagi
	・2024/02/05 制作進行 takagi

========================================== */

#ifndef __TITLE_COMMAND_FINISH_H__	//TitleCommandFinish.hインクルードガード
#define __TITLE_COMMAND_FINISH_H__

// =============== インクルード =====================
#include "TitleCommand.h"	//親のヘッダ

// =============== クラス定義 =====================
class CTitleCommandFinish :public CTitleCommand	//タイトル用コマンド
{
public:
	// ===プロトタイプ宣言===
	CTitleCommandFinish();			//コンストラクタ
	virtual ~CTitleCommandFinish();	//デストラクタ
};	//終了コマンド

#endif	//!__TITLE_COMMAND_FINISH_H__