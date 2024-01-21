/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ゲームスタート描画
	---------------------------------------
	GameOverText.h
	---------------------------------------
	作成者
			nieda

	変更履歴
	・2023/12/17 新規作成 nieda
	・2024/01/21 コメント改修 takagi

========================================== */

// =============== インクルード ===================
#include "GameOverText.h"	// 自身のヘッダ
#include "Defines.h"
#include "GameParameter.h"

// =============== 定数定義 ===================
const int OVER_SPLIT_NUM_MAX = 54;				// スタートのUIアニメーションの分割数の最大数
const TDiType<int> OVER_SPLIT_NUM = { 6, 9 };	// スタートのUIアニメーションの縦横分割数の最大数
const TPos2d<float> OVER_POS = { SCREEN_WIDTH_ / 2.0f, SCREEN_HEIGHT_ / 2.0f };		// 描画位置
const TDiType<float> OVER_SCALE = { (float)SCREEN_WIDTH_, (float)SCREEN_HEIGHT_ };		// 描画サイズ
const int OVER_SWITCH_CNT = 1;


/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：カメラクラスのポインタ
	----------------------------------------
	戻値：なし
=========================================== */
COverText::COverText(CCamera* pCamera)
	: CDrawAnim(OVER_SPLIT_NUM_MAX, OVER_SPLIT_NUM, OVER_SWITCH_CNT)
{
	SetTexture("Assets/Texture/StageFinish/GameOver.png");
	SetCamera(pCamera);
	SetPos({ OVER_POS.x, OVER_POS.y, 0.0f });
	SetSize({ OVER_SCALE.x, OVER_SCALE.y, 0.0f });
}
