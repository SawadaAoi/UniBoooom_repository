/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ゲームスタート描画
	---------------------------------------
	DrawAnimation.h

	作成者
			nieda

	変更履歴
	・2023/12/12 新規作成 nieda
	・2023/12/15 ゲームスタートのテクスチャを新規のものに変更 nieda
	・2023/12/16 描画位置追加 nieda

========================================== */

// =============== インクルード ===================
#include "DrawGameStart.h"	// 自身のヘッダ
#include "GameParameter.h"

// =============== 定数定義 ===================
const int START_SPLIT_NUM_MAX = 60;				// スタートのUIアニメーションの分割数の最大数
const TDiType<int> START_SPLIT_NUM = {5, 12};	// スタートのUIアニメーションの縦横分割数の最大数
const TPos2d<float> START_POS = { SCREEN_WIDTH_ / 2.0f + 50.0f, SCREEN_HEIGHT_ / 2.0f + 150.0f };		// 描画位置
const TDiType<float> START_SCALE = { (float)SCREEN_WIDTH_, (float)SCREEN_HEIGHT_ };		// 描画サイズ
const int START_SWITCH_CNT = 1;					// アニメーション切り替え間隔


/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：カメラクラスのポインタ
	----------------------------------------
	戻値：なし
=========================================== */
CDrawStart::CDrawStart(CCamera* pCamera)
	: CDrawAnim("Assets/Texture/Start_sprit.png", pCamera, START_SPLIT_NUM_MAX, START_POS, START_SCALE, START_SPLIT_NUM, START_SWITCH_CNT)
{
}

