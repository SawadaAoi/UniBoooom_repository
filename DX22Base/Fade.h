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
	・2023/11/19 18の続き takagi
	・2023/11/20 整理 takagi
	・2023/11/23 IsFade()関数追加・細かい書き換え takagi
	・2023/11/24 定数定義修正・定数バッファにUvOffset追加 takagi

========================================== */

#ifndef ___FADE_H___	//Fade.hインクルードガード
#define ___FADE_H___

// =============== インクルード ===================
#include "Shader.h"			//メンバのヘッダ
#include "Texture.h"		//メンバのヘッダ
#include "Camera.h"			//メンバのヘッダ
#include "Transform3d.h"	//メンバのヘッダ
#include "DiType.h"			//メンバのヘッダ
#include "TriType.h"		//メンバのヘッダ

// =============== クラス定義 =====================
class CFade
{
private:
	// ===構造体定義=========
	typedef struct
	{
		float fPos[3];	//位置情報
		float fUv[2];	//UV情報
	}Vertex;	//頂点情報
	typedef struct
	{
		TDiType<float> fUvScale;	//UV拡縮
		TDiType<float> fUvOffset;	//UV移動
	}UvParam;	//シェーダーに送る情報
	// ===列挙定義===========
	enum E_BIT_FLAG
	{
		E_BIT_FLAG_FADE_OUT = 0x01,		//フェードアウトフラグ
		E_BIT_FLAG_FADE_STOP = 0x02,	//フェードストップフラグ
		E_BIT_FLAG_FADE_IN = 0x04,		//フェードインフラグ
		E_BIT_FLAG_4 = 0x08,			//
		E_BIT_FLAG_5 = 0x10,			//
		E_BIT_FLAG_6 = 0x20,			//
		E_BIT_FLAG_7 = 0x40,			//
		E_BIT_FLAG_8 = 0x80,			//
	};	//フェードの種類
// =============== 定数定義 =====================
	const int E_BIT_FLAG_MAX = 3;																			//要素数(※直打ち定数)
	const unsigned char FLAG_FADE_ALL = E_BIT_FLAG_FADE_OUT | E_BIT_FLAG_FADE_STOP | E_BIT_FLAG_FADE_IN;	//フェード系フラグ全て
public:
	// ===プロトタイプ宣言===
	CFade(const CCamera* pCamera);	//コンストラクタ
	CFade(const CFade& Obj);		//コピーコンストラクタ
	~CFade();						//デストラクタ
	void Update();					//更新
	void Draw();					//描画
	void Start();					//フェード開始
	bool IsFade();					//フェード中かどうかを返す
	bool IsFadeOut();				//フェードアウト中か
	bool IsFadeIn();				//フェードイン中か
	float GetFrameRate();			//フェードインの進行度ゲッタ
private:
	// ===メンバ変数宣言=====
	unsigned char m_ucFlag;				//フラグ
	tagTransform3d m_Transform;			//ワールド座標
	DirectX::XMFLOAT4X4 m_aMatrix[3];	//行列
	UvParam m_UvParam;					//UV情報
	int m_nFrame;
	static int ms_nCntFade;				//自身の生成数
	static VertexShader* ms_pVs;		//頂点シェーダー
	static PixelShader* ms_pPs;			//ピクセルシェーダー
	static Texture* ms_pTexture;		//テクスチャ情報
	static const void* ms_pVtx;			//頂点情報
	static unsigned int ms_unVtxSize;	//頂点サイズ
	static unsigned int ms_unVtxCount;	//頂点数
	static const void* ms_pIdx;			//頂点インデックス
	static unsigned int ms_unIdxSize;	//インデックスサイズ
	static unsigned int ms_unIdxCount;	//インデックス数
	static ID3D11Buffer* ms_pVtxBuffer;	//頂点バッファ
	static ID3D11Buffer* ms_pIdxBuffer;	//インデックスバッファ
	const CCamera* m_pCamera;			//カメラ追跡
	// ===プロトタイプ宣言===
	static void Make();								//形作成
	static void SetTexture();						//テクスチャ登録
	static void CreateVtxBuffer();					//頂点バッファ作成
	static void CreateIdxBuffer();					//インデックスバッファ作成
	void UpFlag(const unsigned char& ucBitFlag);	//フラグ起こし
	void DownFlag(const unsigned char& ucBitFlag);	//フラグ降ろし
	void SetFlag(const unsigned char& ucBitFlag);	//フラグ反転
	void FadeOut();									//フェードアウト更新
	void FadeStop();								//フェードストップ更新
	void FadeIn();									//フェードイン更新
};	//フェード

#endif // !___FADE_H___