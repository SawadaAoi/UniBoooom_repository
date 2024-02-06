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
	・2024/01/16 統一のため、インクルードガードの___を__に変更	takagi
	・2024/02/02 一部関数const化、ついでに継承しても触れないようにfinal関数化 takagi

========================================== */

#ifndef __FRAME_CNT_H__	//FrameCnt.hインクルードガード
#define __FRAME_CNT_H__

// =============== クラス定義 =====================
class CFrameCnt	//システム
{
public:
	// ===プロトタイプ宣言===
	CFrameCnt(const unsigned int& nEndFrame, const bool& bCntDown = true);	//コンストラクタ
	virtual ~CFrameCnt();													//デストラクタ
	virtual CFrameCnt& operator++() final;									//'++'演算子のオーバーロード(カウントアップ用)
	virtual CFrameCnt& operator--() final;									//'--'演算子のオーバーロード
	virtual void Count() final;												//カウント進行
	virtual bool IsFin() const final;										//カウントの終了確認
	virtual float GetRate() const final;									//進行率獲得
	virtual int GetCnt() const final;										//現在フレーム数取得
private:
	// ===メンバ変数宣言=====
	unsigned int m_nEndFrame;	//最終フレーム数
	unsigned int m_nFrame;		//現在フレーム数
	bool m_bCntDown;	//true:カウントダウン	false:カウントアップ
};	//カウンタ

#endif // !__FRAME_CNT_H__