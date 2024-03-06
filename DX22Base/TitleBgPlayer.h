/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	タイトル用アニメ背景定義(プレイヤーパターン)
	---------------------------------------
	TitleBgPlayer.h

	作成者	takagi

	変更履歴
	・2024/01/29 制作 takagi
	・2024/02/06 制作進行 takagi
	・2024/02/12 テクスチャdelete系変更 takagi

========================================== */

#ifndef __TITLE_BG_PLAYER_H__	//TitleBgPlayer.hインクルードガード
#define __TITLE_BG_PLAYER_H__

// =============== インクルード =====================
#include "DrawAnimation.h"	//親のヘッダ
#include <list>				//双方向非アクセス式配列コンテナ
#include <Texture.h>		//テクスチャ管理

// =============== クラス定義 =====================
class CTitleBgPlayer :public CDrawAnim	//背景アニメーション
{
private:
	// ===定数定義===========
	const std::list<std::string> LIST_ANIMATION_DUSH = {
		"Assets/Texture/Title/PlayerToRight.png",	//左から右へ
		"Assets/Texture/Title/PlayerToLeft.png"		//右から左へ
	};	//走るアニメーションのファイル名
public:
	// ===プロトタイプ宣言===
	CTitleBgPlayer();													//コンストラクタ
	virtual ~CTitleBgPlayer();											//デストラクタ
	virtual void Update() final;										//更新
	virtual void Draw(const E_DRAW_MODE& = E_DRAW_MODE_NORMAL) final;	//描画
private:
	// ===変数宣言===========
	std::shared_ptr<CFrameCnt> m_pCounter;						//カウンタ
	std::list<Texture*> m_pDushAnimeTexture;					//走るアニメーション用テクスチャ管理	TODO:shared_ptrにする
	std::list<Texture*>::const_iterator m_DushAnimeIterator;	//走るアニメーション用イテレータ
};	//タイトル開始映像

#endif	//!__TITLE_BG_PLAYER_H__