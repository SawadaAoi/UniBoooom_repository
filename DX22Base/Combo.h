/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	コンボUI用ヘッダ
	------------------------------------
	Combo.h
	------------------------------------
	作成者
		澤田蒼生
	変更履歴
	・2023/11/21 作成 Sawada
	・2023/11/23 構造体にスコアを追加　yamamoto
	・2023/11/30 アニメーション用変数追加　nieda
	・2023/12/07 ゲームパラメータから定数移動 takagi

========================================== */
#ifndef __COMBO_H__
#define __COMBO_H__

// =============== インクルード ===================
#include "Sprite.h"
#include <Texture.h>
#include "Object.h"
#include "DrawAnimation.h"
class CTotalScore;

// =============== 定数定義 =======================
const int	MAX_COMBO_NUM = 5;					// 最大同時コンボ数

// =============== クラス定義 =====================
class CCombo
{
public:
	// ===構造体定義=========
	typedef struct
	{
		int dComboCnt;		// コンボ数
		int nOldComboCnt;	// コンボ数（増加したかのチェックに使用）

		int dDispFrame;	// 残描画用加算値
		bool bEndFlg;	// コンボ終了フラグ
		int dScore;		// スコア（連鎖のたびに加算される）
	}ComboInfo;	// コンボ処理情報まとめ

	enum TEXTURE_KIND
	{
		TEX_NUM,
		TEX_BG,

		TEX_MAX,
	};

public:
	// ===プロトタイプ宣言===
	CCombo();
	~CCombo();
	void Update();
	void Draw();

	int FirstComboSet();
	void AddCombo(int num);
	void AddScore(int num,int combo);
	void EndCombo(int num);


	void SetTotalScore(CTotalScore* pTotalScore);


	int GetComboNum(int num);
	int GetComboEndFlg(int num);
	int GetMaxCombo();
private:
	void DisplayNumber(int cnt, int lineNum);
	void DispComboBG(int ArrayNum, int lineNum);

	// ===メンバ変数宣言===
	Texture* m_pTexture[TEX_MAX];		// 数字画像
	ComboInfo m_dComboInfo[MAX_COMBO_NUM];	// コンボ用情報まとめ
	CTotalScore* m_pTotalScore;	

	CDrawAnim* m_pComboBG[MAX_COMBO_NUM];		// コンボの背景アニメーション
	C2dPolygon* m_pTexNumber;

	int m_nMaxComboNum;
};


#endif // __COMBO_H__