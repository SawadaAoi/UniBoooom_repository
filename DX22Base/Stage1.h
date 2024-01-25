/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ステージ1定義
	---------------------------------------
	Stage1.h
	---------------------------------------
	作成者
			takagi
			nieda

	変更履歴
	・2023/11/05 制作 takagi
	・2023/11/07 コメント修正 takagi
	・2023/11/16 Prot.h→Stage1.h takagi
	・2023/12/14 BGMの管理をSceneManagerに移動 yamashita
	・2024/01/15 GameFinish()関数の引数修正・RecordData()関数追加 takagi
	・2024/01/20 リファクタリング takagi

========================================== */

#ifndef __STAGE1_H__	//Stage1.hインクルードガード
#define __STAGE1_H__

// =============== インクルード ===================
#include "Stage.h"	//親のヘッダ

// =============== クラス定義 =====================
class CStage1 :public CStage	//ステージ
{
//protected:
//	enum E_3D	//更新順
//	{
//		E_3D_FLOOR = CStage::E_3D_MAX,	//床
//		E_3D_MAX,						//要素数
//	};	//3Dのオブジェクト
public:
	// ===プロトタイプ宣言===
	CStage1();							//コンストラクタ
	~CStage1();							//デストラクタ
	void Update();						//更新
	void Draw();						//描画
	E_TYPE GetNext() const override;	//次のシーンゲッタ
private:
	// ===プロトタイプ宣言===
	virtual void RecordData();			//データ記録
};	//ステージ1

#endif	//!__STAGE1_H__