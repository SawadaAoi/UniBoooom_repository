/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	フレームカウンタ定義
	------------------------------------
	FrameCnt.h
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/12/16 作成 takagi

========================================== */

#ifndef ___FRAME_CNT_H___	//FrameCnt.hインクルードガード
#define ___FRAME_CNT_H___

// =============== クラス定義 =====================
class CFrameCnt	//システム
{
public:
	// ===プロトタイプ宣言===
	CFrameCnt(const unsigned int& nEndFrame, const bool& bCntDown = true);	//コンストラクタ
	~CFrameCnt();															//デストラクタ
	CFrameCnt& operator++();												//'++'演算子のオーバーロード(カウントアップ用)
	CFrameCnt& operator--();												//'--'演算子のオーバーロード
	void Count();															//カウント進行
	bool IsFin();															//カウントの終了確認
	float GetRate();														//進行率獲得
	int GetCnt();															//現在フレーム数取得
private:
	// ===メンバ変数宣言=====
	unsigned int m_nEndFrame;	//最終フレーム数
	unsigned int m_nFrame;		//現在フレーム数
	bool m_bCntDown;	//true:カウントダウン	false:カウントアップ
};	//カウンタ

#endif // !___FRAME_CNT_H___