/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ビット式フラグ定義(char型)
	------------------------------------
	UcFlag.h
	------------------------------------
	作成者	takagi

	変更履歴
	・2024/01/18 作成 takagi
	・2024/01/20 コンストラクタ引数追加 takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __UC_FLAG_H__	//UcFlag.hインクルードガード
#define __UC_FLAG_H__

// =============== クラス定義 =====================
class CUcFlag
{
public:
	// ===プロトタイプ宣言===
	CUcFlag(const unsigned char& ucFlag = 0x00);	//コンストラクタ
	CUcFlag(const CUcFlag& Obj);					//コピーコンストラクタ
	~CUcFlag();										//デストラクタ
	void Up(const unsigned char& ucFlag);			//フラグオン
	void Down(const unsigned char& ucFlag);			//フラグオフ
	bool Check(const unsigned char& ucFlag) const;	//フラグチェック
	const unsigned char& GetFlag() const;			//フラグゲッタ
private:
	// ===メンバ変数宣言=====
	unsigned char m_ucFlag;	//フラグ本体
};	//char型のフラグ

#endif	//!__UC_FLAG_H__