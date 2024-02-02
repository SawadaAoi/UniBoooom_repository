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
	・2024/01/26 処理を見やすく修正&&トータルスコア加算アニメ処理追加 sawada
	・2024/02/02 ゲーム終了間際の加算スコアがトータルスコアに反映されるように suzumura

========================================== */
#ifndef __TOTALSCORE_H__
#define __TOTALSCORE_H__

// =============== インクルード ===================
#include <Texture.h>
#include"Combo.h"
#include <vector>
#include "Defines.h"
#include "DiType.h"
#include "Timer.h"
#include "Player.h"
// =============== クラス定義 =====================
class CTotalScore
{
public:
	// ===構造体定義=========
	typedef struct
	{
		int   nAddScore;				// スコア
		float fCombScoreMult;			// コンボスコア倍率
		bool  bEndComboFlg;				// コンボ表示終了フラグ(true:コンボ終了)
		int   nDispFrame;				// 残描画用加算値
		bool  bDispEndFlg;				// スコア加算値表示終了フラグ
		int	  nDispComMultFrame;		// コンボ倍率表示用加算値
		bool  bDispComMultEndFlg;		// スコア加算値表示終了フラグ
		bool  bDispGameEndFlg;				// スコア加算におけるプレイ終了時フラグ

	}PlusScore;	// スコア処理情報まとめ

	// 数字表示用
	typedef struct
	{
		TDiType<float> fSize;
		TDiType<float> fPos; 
		TDiType<float> fUVSize; 
		float spaceW; 
		Texture* pTexture; 
		int digits;

	}NumbersParam;

	// 画像種類
	enum TextureType
	{
		NUM_TOTAL_SCORE,
		NUM_ADD_SCORE,
		BG_TOTAL_SCORE,
		BG_ADD_SCORE,

		TEXTURE_MAX,
	};

public:
	CTotalScore(CPlayer* player, CTimer* timer);
	~CTotalScore();

	void Update();		 		//更新関数
	void Draw();		 		//描画関数
	void SetAddScore(CCombo::ComboInfo comboInfo,int num);
	void ComboCheck(CCombo::ComboInfo comboInfo, int num);
	void AddTotalScore(int addScore);

	int GetTotalScore();
	std::vector<int> digitsToArray(int score, int digits);	//引数の数字を各桁1ずつ配列に入れる
private:
	void TotalScoreMove();

	void DrawBGTotalScore();			// トータルスコアの背景描画
	void DrawTotalScore();
	void DrawAddScore(int nNum, int lineNum);
	void DrawBGAddScore(int lineNum);		// 加算スコアの背景描画
	void DrawScoreComboMulti(int nNum, int lineNum);

	void DrawTexture(TDiType<float> fSize, TDiType<float> fPos, TDiType<float> fUVSize, TDiType<float> fUVPos, Texture * pTexture);
	void DrawNumber(int dispNum, TDiType<float> fSize, TDiType<float> fPos, TDiType<float> fUVSize, float spaceW, float spaceH, Texture* pTexture, int digits);

	CTotalScore::PlusScore ResetPlusScore();

	int m_nTotalScoreDisp;
	int m_nTotalScore;
	int m_nToScoreAddCnt;
	int m_nToScoAddPoint;
	
	PlusScore m_AddScore[MAX_COMBO_NUM];
	CCombo::ComboInfo* m_pComboInfo;

	Texture* m_pTexture[TEXTURE_MAX];

	CCombo* m_pCombo;
	int nArraySize;
	std::vector<int> TotalScoreArray;	//各桁1ずつ入れるための配列

	CPlayer* m_pPlayer;
	CTimer* m_pTimer;
	

};




#endif // !__TOTALSCORE_H__

