/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	フェード定義
	------------------------------------
	Fade.h
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/11/18 制作 takagi

========================================== */

#ifndef ___FADE_H___	//Fade.hインクルードガード
#define ___FADE_H___

// =============== インクルード ===================
#include "Sprite.h"
#include "Camera.h"		//カメラ

// =============== クラス定義 =====================
class CFade : public Sprite
{
};	//フェード

#endif // !___FADE_H___


















//
///* ========================================
//	HEW/UniBoooom!!
//	------------------------------------
//	フェード定義
//	------------------------------------
//	Fade.h
//	------------------------------------
//	作成者	takagi
//
//	変更履歴
//	・2023/11/18 制作 takagi
//
//========================================== */
//
//#ifndef ___FADE_H___	//Fade.hインクルードガード
//#define ___FADE_H___
//
//// =============== インクルード ===================
//#include "Shader.h"		//シェーダー
//#include "Texture.h"	//テクスチャ
//#include "Camera.h"		//カメラ
//
//// =============== クラス定義 =====================
//class CFade
//{
//private:
//	// ===構造体定義=========
//	struct Vertex
//	{
//		float pos[3];
//		float uv[2];
//	};
//public:
//	// ===プロトタイプ宣言===
//	CFade(const CCamera*);					//コンストラクタ
//	CFade(const CFade& Obj);	//コピーコンストラクタ
//	~CFade();					//デストラクタ
//	void Update();				//更新
//	void Draw();				//描画
//	void SetTexture(const std::string sTexPass);	//テクスチャ登録
//private:
//	// ===メンバ変数宣言=====
//	Texture* m_pTexture;			//テクスチャ情報
//	static int ms_nCntFade;			//自身の生成数
//	static VertexShader* ms_pVs;	//頂点シェーダー
//	static PixelShader* ms_pPs;		//ピクセルシェーダー
//
//	static const void* ms_pVtx;
//	static unsigned int ms_unVtxSize;
//	static unsigned int ms_unVtxCount;
//	//static bool isWrite;
//	static const void* ms_pIdx;
//	static unsigned int ms_unIdxSize;
//	static unsigned int ms_unIdxCount;
//	static ID3D11Buffer* ms_pVtxBuffer;
//	static ID3D11Buffer* ms_pIdxBuffer;
//	DirectX::XMFLOAT4X4 matrix[3];
//	const CCamera* m_pCamera;
//
//	// ===プロトタイプ宣言===
//	static void MakeShader();						//シェーダー作成
//	static void Make();								//形作成
//	static void CreateVtxBuffer();
//	static void CreateIdxBuffer();
//};	//フェード
//
//#endif // !___FADE_H___