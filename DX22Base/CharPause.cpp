/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ポーズ文字実装
	---------------------------------------
	CharPause.cpp

	作成者	takagi

	変更履歴
	・2023/12/09 制作 takagi
	・2023/12/10 制作進行 takagi

========================================== */

// =============== インクルード ===================
#include "CharPause.h"	//自身のヘッダ
#include "GameParameter.h"

// =============== 定数定義 ===================
const float AMPITUDE(25.0f);											//振幅
const float ANGLE_SPEED(DirectX::XMConvertToRadians(1.5f));				//単振動の角速度
#if !MODE_GAME_PARAMETER
const float CHARA_WIDTH = 100.0f;										//ポーズ表記横幅
const float CHARA_HEIGHT = 100.0f;										//ポーズ表記縦幅
#endif // !MODE_GAME_PARAMETER
const TPos3d<float> SCALE(CHARA_WIDTH, CHARA_HEIGHT, 0.0f);	//大きさ


/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：const int& nWaitTime：待機時間
	----------------------------------------
	戻値：なし
=========================================== */
CCharPause::CCharPause(const int& nWaitTime)
	:m_fMoveAngle(0.0f)		//移動角
	,CPauseObj(nWaitTime)	//委譲
{
	// =============== 初期化 ===================
	SetSize(SCALE);	//大きさ初期化
}

/* ========================================
	位置算出関数
	----------------------------------------
	内容：第一引数で受け取った位置を表す変数にズレを直接反映する。
	----------------------------------------
	引数1：TPos3d<float>& fPos：結果が格納される、最終目標位置の情報が入った変数
	----------------------------------------
	戻値：なし
=========================================== */
void CCharPause::CulculatePos(TPos3d<float>& fPos)
{
	// =============== 算出 ===================
	CPauseObj::CulculatePos(fPos);							//親の関数使用
	fPos.y = m_fReach.y + AMPITUDE * sinf(m_fMoveAngle);	//補完

	// =============== 更新 ===================
	m_fMoveAngle += ANGLE_SPEED;	//角更新
}