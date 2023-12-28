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
		int dCnt;		// コンボ数
		int dDispFrame;	// 残描画用加算値
		bool bEndFlg;	// コンボ終了フラグ
		int dScore;		// スコア（連鎖のたびに加算される）
	}ComboInfo;	// コンボ処理情報まとめ

public:
	// ===プロトタイプ宣言===
	CCombo();
	~CCombo();
	void Update();
	void Draw();

	int FirstComboSet();
	void AddCombo(int num);
	void AddScore(int num,int combo);
	int GetCombo(int num);
	void EndCombo(int num);
	void DisplayNumber(int cnt, float shiftPosY);
	void DrawTexture(float posX, float posY, float h, float w, Texture* pTexture);
	void SetTotalScore(CTotalScore* pTotalScore);

	int GetMaxCombo();
private:
	// ===メンバ変数宣言===
	Texture* m_pTextureNum[3];		// 数字画像
	ComboInfo m_dComboInfo[MAX_COMBO_NUM];	// コンボ用情報まとめ
	CTotalScore* m_pTotalScore;	

	int m_nMaxComboNum;

	float m_fSizeX;		// 横UV座標格納用
	float m_fSizeY;		// 縦UV座標格納用
	int m_nCntWidth;	// テクスチャの横分割数カウント用
	int m_nCntHeight;	// テクスチャの縦分割数カウント用
	int m_nCntOldCombo[MAX_COMBO_NUM];	// コンボ数増加確認用
	int m_nCnt;			// アニメーション切り替えカウント用
};


#endif // __COMBO_H__