/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ヒットストップ定義
	------------------------------------
	HitStop.h
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/11/17 作成 takagi
	・2023/11/21 静的に変更・コメント追加 takagi
	・2024/01/16 統一のため、インクルードガードの___を__に変更	takagi

========================================== */

#ifndef __HIT_STOP_H__	//HitStop.hインクルードガード
#define __HIT_STOP_H__

// =============== クラス定義 =====================
class CHitStop	//システム
{
public:
	// ===列挙定義===========
	enum HIT_STOP
	{
		E_BIT_FLAG_STOP_SOFT = 0x01,	//ストップ：軽
		E_BIT_FLAG_STOP_NORMAL = 0x02,	//ストップ：中
		E_BIT_FLAG_STOP_HEAVY = 0x04,	//ストップ：重
		E_BIT_FLAG_STOP_DEATH = 0x08,	//ストップ：死　※こんなの使うな
		E_BIT_FLAG_5 = 0x10,			//
		E_BIT_FLAG_6 = 0x20,			//
		E_BIT_FLAG_7 = 0x40,			//
		E_BIT_FLAG_8 = 0x80,			//

		E_BIT_FLAG_HIT_STOP = 0x0F,		//ヒットストップ中はオン、それ以外はオフ
		E_BIT_FLAG_MAX = 4,				//要素数(※直打ち！)
	};	//フラグ(優先度順)
public:
	// ===プロトタイプ宣言===
	CHitStop();												//コンストラクタ
	~CHitStop();											//デストラクタ
	static void Update();									//更新
	static void UpFlag(const unsigned char& ucBitFlag);		//フラグオン
	static void DownFlag(const unsigned char& ucBitFlag);	//フラグオフ
	static void SetFlag(const unsigned char& ucBitFlag);	//フラグ反転
	static bool IsStop();									//ヒットストップ中か
private:
	// ===メンバ変数宣言=====
	static unsigned char ms_ucFlag;	//フラグ	char:1バイト(8ビット)
	static int ms_nFrame;			//フレーム数カウンタ
	// ===プロトタイプ宣言===
	static void CallHitStop(int(*CallBack)(const int&));	//ヒットストップ判定
};	//ヒットストップ

#endif // !__HIT_STOP_H__