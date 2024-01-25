/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ステージ3定義
	---------------------------------------
	Stage3.h
	---------------------------------------
	作成者
			takagi
			nieda

	変更履歴
	・2023/11/16 制作 takagi
	・2023/12/12 LoadSEをオーバーライド yamashita
	・2023/12/14 BGMの管理をSceneManagerに移動 yamashita
	・2024/01/15 GameFinish()関数の引数修正・RecordData()関数追加 takagi
	・2024/01/20 リファクタリング takagi

========================================== */

#ifndef __STAGE3_H__	//Stage3.hインクルードガード
#define __STAGE3_H__

// =============== インクルード ===================
#include "Stage.h"	//親のヘッダ

// =============== クラス定義 =====================
class CStage3 :public CStage	//ステージ
{
//protected:
//	enum E_3D	//更新順
//	{
//		E_3D_FLOOR = CStage::E_3D_MAX,	//床
//		E_3D_MAX,						//要素数
//	};	//3Dのオブジェクト
public:
	// ===プロトタイプ宣言===
	CStage3();							//コンストラクタ
	~CStage3();							//デストラクタ
	void Update();						//更新
	void Draw();					//描画
	E_TYPE GetNext() const override;	//次のシーンゲッタ
private:
	// ===プロトタイプ宣言===
	virtual void RecordData();			//データ記録
};	//ステージ3

#endif	//!__STAGE3_H__