/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   トータルスコアヘッダー
   ---------------------------------------
   TotalScore.h

   作成者 山本凱翔

   変更履歴
	・2023/11/22　作成 yamamoto
	・2023/11/23　score構造体、comboの構造体の情報取得処理追加 yamamoto
	・2023/12/07 ゲームパラメータに依存していたので修正 takagi

========================================== */
#ifndef __TOTALSCORE_H__
#define __TOTALSCORE_H__

// =============== インクルード ===================
#include <Texture.h>
#include"Combo.h"
#include <vector>
// =============== クラス定義 =====================
class CTotalScore
{
public:
	// ===構造体定義=========
	typedef struct
	{
		int   nAddScore;				// スコア
		float fComboMagnification;	//コンボ倍率
		bool  bEndComboFlg;			// コンボ表示終了フラグ
		bool  bDispTotalScoreFlg;	// スコア表示終了フラグ
		int   nDispFrame;				// 残描画用加算値
		bool  bDispFlg;				
	}PlusScore;	// スコア処理情報まとめ
public:
	CTotalScore();
	~CTotalScore();

	void Update();		 		//更新関数
	void Draw();		 		//描画関数
	void AddScore(CCombo::ComboInfo comboInfo,int num);
	void ComboCheck(CCombo::ComboInfo comboInfo, int num);
	void AddTotalScore();
	int GetTotalScore();
	std::vector<int> digitsToArray(int score);	//引数の数字を各桁1ずつ配列に入れる
private:
	int m_nTotalScore;
	
	PlusScore m_PlusScore[MAX_COMBO_NUM];
	CCombo::ComboInfo* m_pComboInfo;
	Texture* m_pToScoreTexture;
	Texture* m_pPlusScoreTexture;
	CCombo* m_pCombo;
	int nArraySize;
	std::vector<int> TotalScoreArray;	//各桁1ずつ入れるための配列
	std::vector<int> digitArray;//digitsをここに入れる
	std::vector<int> digits;//digitsをここに入れる
	

};




#endif // !__TOTALSCORE_H__

