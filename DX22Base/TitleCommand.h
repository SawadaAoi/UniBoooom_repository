/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	タイトル用コマンド定義
	---------------------------------------
	TitleCommand.h

	作成者	takagi

	変更履歴
	・2023/12/16 制作 takagi
	・2024/02/05 リファクタリング takagi
	・2024/02/15 拡縮変化時間変更 takagi

========================================== */

#ifndef __TITLE_COMMAND_H__	//TitleCommand.hインクルードガード
#define __TITLE_COMMAND_H__

// =============== インクルード =====================
#include "TitleObj.h"	//親のヘッダ
#include <memory.h>		//ptr管理
#include "FrameCnt.h"	//カウンタ
#include <map>			//連想コンテナ

// =============== クラス定義 =====================
class CTitleCommand :public CTitleObj	//開始時ズームアウトするタイトル用平面オブジェ
{
public:
	// ===列挙定義==========
	enum E_STATE
	{
		E_STATE_UNSELECTED,			//非選択状態
		E_STATE_SELECTED,			//選択状態
		E_STATE_DECIDE,				//決定状態
		E_STATE_MAX,				//要素数
	};	//状態(テクスチャに影響)
private:
	// ===定数定義==========
	const std::map<E_STATE, unsigned int> MAP_MAX_ANIMATION_NUM =
	{
		{E_STATE_UNSELECTED, 1},	//非選択時のアニメーションコマ数
		{E_STATE_SELECTED, 1},		//選択時のアニメーションコマ数
		{E_STATE_DECIDE, 1},		//決定時のアニメーションコマ数
	};	//アニメーション番号の最大値
	const std::map<E_STATE, unsigned int> MAP_ANIMATION_INTERVAL =
	{
		{E_STATE_UNSELECTED, 1},	//非選択時のアニメーション間隔
		{E_STATE_SELECTED, 1},		//選択時のアニメーション間隔
		{E_STATE_DECIDE, 1},		//決定時のアニメーション間隔
	};	//アニメーション間隔
	const std::map<E_STATE, unsigned  int> MAP_ANIMATION_FRAME =
	{
		{E_STATE_UNSELECTED, 30},	//非選択時のアニメーション時間
		{E_STATE_SELECTED, 30},	//選択時のアニメーション時間
		{E_STATE_DECIDE, 30},		//決定時のアニメーション時間
	};	//アニメーション時間
protected:
	// ===定数定義==========
	const std::map<E_STATE, const TTriType<float>> MAP_SCALE =
	{
		{E_STATE_UNSELECTED, {120.0f * 3.5f, 26.0f * 3.5f, 0.0f}},				//非選択時の拡縮率
		{E_STATE_SELECTED, {120.0f * 3.5f * 1.1f, 26.0f * 3.5f * 1.1f, 0.0f}},	//選択時の拡縮率
		{E_STATE_DECIDE, {120.0f * 3.5f * 1.2f, 26.0f * 3.5f * 1.2f, 0.0f}},	//決定時の拡大率
	};	//状態による拡縮率
public:
	// ===プロトタイプ宣言===
	virtual ~CTitleCommand();								//デストラクタ
	virtual void Update() override;							//更新
	virtual void ChangeState(const E_STATE& eState) final;	//状態変更
	virtual bool DesideAnimeFin() final;					//決定アニメ再生完了
protected:
	// ===プロトタイプ宣言===
	CTitleCommand(const E_STATE& eInitState);	//コンストラクタ
private:
	// ===変数宣言===
	E_STATE m_eTexNo;											//状態列挙(テクスチャ横)
	unsigned int m_unAnimeNo;									//アニメーションコマ番号(テクスチャ縦)
	TTriType<float> m_fScale;									//大きさ管理
	std::shared_ptr<TTriType<float>> m_pfReScalingStartSize;	//拡縮変化開始時の大きさ
	std::shared_ptr<CFrameCnt> m_pFrameCnt;						//拡縮変化用カウンタ
	std::shared_ptr<CFrameCnt> m_pAnimeInterval;				//アニメーション間隔
	static bool m_bCntUpDwn;									//カウントアップ・ダウン切換フラグ
	static std::shared_ptr<CFrameCnt> m_pAlphaCnt;				//透明度変化用カウンタ
};	//タイトル用コマンド

#endif	//!__TITLE_COMMAND_H__