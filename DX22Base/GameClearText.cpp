/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ゲームスタート描画
	---------------------------------------
	GameClearText.h

	作成者
			nieda

	変更履歴
	・2023/12/17 新規作成 nieda

========================================== */

// =============== インクルード ===================
#include "GameClearText.h"	// 自身のヘッダ
#include "Defines.h"
#include "GameParameter.h"

// =============== 定数定義 ===================
const int CLEAR_SPLIT_NUM_MAX = 45;				// スタートのUIアニメーションの分割数の最大数
const TDiType<int> CLEAR_SPLIT_NUM = { 5, 9 };	// スタートのUIアニメーションの縦横分割数の最大数
const TPos2d<float> CLEAR_POS = { SCREEN_WIDTH_ / 2.0f, SCREEN_HEIGHT_ / 2.0f };		// 描画位置
const TDiType<float> CLEAR_SCALE = { (float)SCREEN_WIDTH_, (float)SCREEN_HEIGHT_ };		// 描画サイズ
const int CLEAR_SWITCH_CNT = 1;					// アニメーション切り替え間隔


/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：カメラクラスのポインタ
	----------------------------------------
	戻値：なし
=========================================== */
CClearText::CClearText(CCamera* pCamera)
	: CDrawAnim(CLEAR_SPLIT_NUM_MAX, CLEAR_SPLIT_NUM, CLEAR_SWITCH_CNT)
{
	//ゲームクリアの描画準備
	SetTexture("Assets/Texture/StageFinish/finish.png");
	SetCamera(pCamera);
	SetPos({ CLEAR_POS.x, CLEAR_POS.y, 0.0f });
	SetSize({ CLEAR_SCALE.x, CLEAR_SCALE.y, 0.0f });
}