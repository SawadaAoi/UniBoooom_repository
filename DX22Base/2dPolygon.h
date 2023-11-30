/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	平面ポリゴン定義
	------------------------------------
	2dPolygon.h
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/11/21 作成 takagi
	・2023/11/28 TextureSet関数にポインタ指定できる物を追加

========================================== */

#ifndef ___2D_POLYGON_H___	//2dPolygon.hインクルードガード
#define ___2D_POLYGON_H___

// =============== インクルード ===================
#include "Shader.h"			//メンバのヘッダ
#include "Texture.h"		//メンバのヘッダ
#include "Camera.h"			//メンバのヘッダ
#include "Transform3d.h"	//メンバのヘッダ
#include "DiType.h"			//メンバのヘッダ
#include "TriType.h"		//メンバのヘッダ
#include "Transform3d.h"	//メンバのヘッダ

// =============== クラス定義 =====================
class C2dPolygon
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
		TDiType<float> fUvOffset;	//UV座標のズレ
		TDiType<float> fUvScale;	//UV拡縮
		TTriType<float> fColor;		//色
		float fAlpha;				//透明度
	}Param;	//シェーダーに送る情報
public:
	// ===プロトタイプ宣言===
	C2dPolygon();										//コンストラクタ
	C2dPolygon(const C2dPolygon& Obj);					//コピーコンストラクタ
	~C2dPolygon();										//デストラクタ
	void Draw();										//描画
	void SetCamera(const CCamera* pCamera);				//カメラセッタ
	void SetPos(TPos3d<float> fPos);					//位置セッタ
	void SetSize(TTriType<float> fScale);				//大きさセッタ
	void SetRotate(TTriType<float> fRotate);			//回転セッタ
	void SetTransform(tagTransform3d Transform);		//ワールド座標セッタ
	void SetUvOffset(TDiType<float> fUvOffset);			//UVずれセッタ
	void SetUvScale(TDiType<float> fUvScale);			//UV拡縮セッタ
	void SetColor(TTriType<float> fRGB, float fAlpha);	//色セッタRGBA
	void SetColor(TTriType<float> fRGB);				//色セッタRGB
	void SetColor(float fColor);						//色セッタ(同一値)
	void SetAlpha(float fAlpha);						//透明度セッタ
	void SetTexture(const char* pcTexPass);				//テクスチャ登録
	void SetTexture(Texture* pTexture);				//テクスチャ登録
	void SetVertexShader(VertexShader* pVs);			//頂点シェーダセッタ
	void SetPixelShader(PixelShader* pPs);				//ピクセルシェーダセッタ
private:
	// ===メンバ変数宣言=====
	tagTransform3d m_Transform;			//ワールド座標
	DirectX::XMFLOAT4X4 m_aMatrix[3];	//行列
	Param m_Param;						//シェーダーに書き込む情報
	static VertexShader* m_pDefVs;				//頂点シェーダー
	static PixelShader* m_pDefPs;					//ピクセルシェーダー
	VertexShader* m_pVs;				//頂点シェーダー
	PixelShader* m_pPs;					//ピクセルシェーダー
	Texture* m_pTexture;				//テクスチャ情報
	static int ms_nCnt2dPolygon;		//自身の生成数
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
	void MakeVertexShader();		//頂点シェーダ作成
	void MakePixelShader();			//ピクセルシェーダー
	static void Make();				//形作成
	static void CreateVtxBuffer();	//頂点バッファ作成
	static void CreateIdxBuffer();	//インデックスバッファ作成
};	//フェード

#endif // !___2D_POLYGON_H___