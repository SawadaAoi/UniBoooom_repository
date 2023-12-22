/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	戦闘情報定義
	------------------------------------
	BattleData.h
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/12/07 制作 takagi
	・2023/12/11 分秒取得追加 takagi

========================================== */
//TODO:同じようにランキング用とかも作る

#ifndef __BATTLE_DATA_H__	//BattleData.hインクルードガード
#define __BATTLE_DATA_H__

// =============== インクルード ===================
#include <string>	//文字列操作
#include <fstream>	//ファイル専用ストリーム

// =============== 構造体定義 ===================
typedef struct tagBattleData	//ワールド行列に関わる情報
{
public:
	// ===メンバ変数宣言===
	int nAliveTime;		//生存時間[s]
	int nKill;			//倒した数
	int nTotalScore;	//スコア合計値
	int nStageNum;		//プレイしたステージ番号
	std::string	sName;	//プレイヤー名
	// ===プロトタイプ宣言===
	tagBattleData();																//コンストラクタ
	tagBattleData(const int& nAliveTime, const int& nKill, const int& nTotalScore, const int & nStageNum);	//引数付きコンストラクタ
	tagBattleData(const tagBattleData& Obj);										//コピーコンストラクタ
	~tagBattleData();																//デストラクタ
	void Load();																	//データ読み込み
	void Save();																	//データ保存
	int GetMinute();																//分ゲッタ
	int GetSecond();																//秒ゲッタ
	int GetCommaSecond();															//ミリ秒ゲッタ
}BattleData;	//試合データ

/* ========================================
	読み込み演算子
	------------------------------------ -
	内容：ファイルストリームからBattleData型のデータを読み込む
	------------------------------------ -
	引数1：std::basic_fstream<CharT, Traits>& FileStream：入力するファイルストリーム
	引数2：BattleData& Data：入力されるデータ
	------------------------------------ -
	戻値：引数の入力ストリームオブジェクト
=========================================== */
template<typename CharT, typename Traits>	//テンプレート関数実装
std::basic_fstream<CharT, Traits>& operator>>(std::basic_fstream<CharT, Traits>& FileStream, BattleData& Data)
{
	// =============== 読み込み ===================
	FileStream >> Data.nAliveTime >> Data.nKill >> Data.nTotalScore >> Data.nStageNum;	//宣言順に読み込み

	// =============== 提供 ===================
	return FileStream;	//入力元ストリーム
}

/* ========================================
	書き出し演算子
	------------------------------------ -
	内容：ファイルストリームにBattleData型のデータを書き出す
	------------------------------------ -
	引数1：std::basic_fstream<CharT, Traits>& FileStream：出力されるファイルストリーム
	引数2：const BattleData& Data：出力するデータ
	------------------------------------ -
	戻値：引数の出力ストリームオブジェクト
=========================================== */
template<typename CharT, typename Traits>	//テンプレート関数実装
std::basic_fstream<CharT, Traits>& operator<<(std::basic_fstream<CharT, Traits>& FileStream, const BattleData& Data)
{
	// =============== 書き出し ===================
	FileStream << Data.nAliveTime << ' ' << Data.nKill << ' ' << Data.nTotalScore << ' ' << Data.nStageNum << std::endl;	//宣言順に書き出し

	// =============== 提供 ===================
	return FileStream;	//出力先ストリーム
}

#endif //!__BATTLE_DATA_H__