/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	タイトル用2Dオブジェ定義
	---------------------------------------
	TitleObj.h
	---------------------------------------
	作成者	takagi

	変更履歴
	・2023/12/16 制作 takagi
	・2023/12/17 ChackPutOut()関数追加・引数参照化 takagi
	・2024/01/20 リファクタリング takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __TITLE_OBJ_H__	//TitleObj.hインクルードガード
#define __TITLE_OBJ_H__

// =============== インクルード =====================
#include "2dObject.h"	//親のヘッダ

// =============== クラス定義 =====================
class CTitleObj :public C2dObject	//平面オブジェ
{
public:
	// ===プロトタイプ宣言===
	CTitleObj(const int& nWaitTime = 0);	//コンストラクタ
	~CTitleObj();							//デストラクタ
	void Update() override;					//更新
	void Draw() override;					//描画
	bool ChackDraw();						//表示しているか
private:
	// ===メンバ変数宣言=====
	int* m_pnWaitTime;	//初動待機時間計測
};	//タイトル用オブジェ

#endif	//!__TITLE_OBJ_H__