/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ポーズコマンド定義
	---------------------------------------
	CommandPause.h
	---------------------------------------
	作成者	takagi

	変更履歴
	・2023/12/10 制作 takagi
	・2023/12/16 コメント修正 takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __COMMAND_PAUSE_H__	//CommandPause.hインクルードガード
#define __COMMAND_PAUSE_H__

// =============== インクルード =====================
#include "PauseObj.h"	//親のヘッダ

// =============== クラス定義 =====================
class CCommandPause :public CPauseObj	//平面オブジェ
{
private:
	enum E_TEXTURE
	{
		E_TEXTURE_UNSELECTED,	//非選択状態
		E_TEXTURE_SELECTED,		//選択状態
		E_TEXTURE_DECIDE,		//決定状態
		E_TEXTURE_MAX,			//要素数
	};	//テクスチャ情報
public:
	// ===プロトタイプ宣言===
	CCommandPause(const int& nWaitTime);	//コンストラクタ
	~CCommandPause();						//デストラクタ
	void Update() override;					//更新
	void Selected();						//選択状態化
	void UnSelected();						//非選択状態化
	void Decide();							//決定
private:
	// ===変数宣言===
	E_TEXTURE m_eTexNo;			//テクスチャ列挙
	TDiType<float> m_fScale;	//拡縮率
	int* m_pnTimer;				//決定テクスチャ表示時間計測用
};	//ポーズ用コマンド

#endif	//!__COMMAND_PAUSE_H__