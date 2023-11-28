/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	boooom表示用ヘッダ
	------------------------------------
	BoooomUI.h
	------------------------------------
	作成者
		鄭宇恩
	変更履歴
	・2023/11/20 h,作成 Tei
	・2023/11/21 表示で必要なメンバ変数、関数作成 Tei

========================================== */
#ifndef __BOOOOM_UI_H__
#define __BOOOOM_UI_H__

// =============== インクルード ===================
#include "Sprite.h"
#include <Texture.h>
#include "Pos3d.h"
#include "Camera.h"


// =============== クラス定義 =====================
class CBoooomUI
{
public:
	// ===プロトタイプ宣言===
	CBoooomUI(TPos3d<float> pos, Texture* pTex, const CCamera* pCamera, float fTime);
	~CBoooomUI();
	void Update();
	void Draw();

	void DisplayTimeAdd();		//boooomUI表示カウント加算処理関数
	bool GetDelFlg();			//削除フラグ取得処理関数
	void SetCamera(const CCamera * pCamera);

protected:
	const CCamera* m_pCamera;
private:
	// ===メンバ変数宣言===
	Texture* m_pBoooomTex;
	TPos3d<float> m_pos;			//描画の位置
	TPos3d<float> m_scale;			//描画のスケールサイズ

	int			m_nDelFrame;		// BoooomUI表示カウント
	bool		m_bDelFlg;			// 表示終了フラグ
	float		m_fExplodeTime;		// 爆発総時間
};


#endif // __BOOOOM_UI_H__