/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	タイトル用コマンド定義
	---------------------------------------
	CommandTitle.h
	---------------------------------------
	作成者	takagi

	変更履歴
	・2023/12/16 制作 takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __COMMAND_TITLE_H__	//CommandTitle.hインクルードガード
#define __COMMAND_TITLE_H__

// =============== インクルード =====================
#include "TitleObj.h"	//親のヘッダ

// =============== クラス定義 =====================
class CCommandTitle :public CTitleObj	//平面オブジェ
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
	CCommandTitle(const int& nWaitTime);	//コンストラクタ
	~CCommandTitle();						//デストラクタ
	void Update() override;					//更新
	void Selected();						//選択状態化
	void UnSelected();						//非選択状態化
	void Decide();							//決定
private:
	// ===変数宣言===
	E_TEXTURE m_eTexNo;			//テクスチャ列挙
	TDiType<float> m_fScale;	//拡縮率
	int* m_pnTimer;				//決定テクスチャ表示時間計測用
};	//タイトル用コマンド

#endif	//!__COMMAND_TITLE_H__