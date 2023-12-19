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
	・2023/12/01 テクスチャの扱い方を安全化 takagi
	・2023/12/05 描画のモード追加 takagi
	・2023/12/06 Draw()関数のデフォルト引数変更 takagi
	・2023/12/10 静的変数の名前を修正・デフォルトのカメラも静的関数化。 takagi
	・2023/12/15 空の更新関数追加 takagi
	・2023/12/17 引数参照化 takagi
	・2023/12/20 継承先がやりにくかったのでワールド変数をprotected化 takagi

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
public:
	enum E_DRAW_MODE
	{
		E_DRAW_MODE_NORMAL,		//通常の描画
		E_DRAW_MODE_BILLBOARD,	//ビルボードとして描画
	};
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
	C2dPolygon();																//コンストラクタ
	C2dPolygon(const C2dPolygon& Obj);											//コピーコンストラクタ
	virtual ~C2dPolygon();														//デストラクタ
	virtual void Update();														//更新
	virtual void Draw(const E_DRAW_MODE& eMode = E_DRAW_MODE_NORMAL);			//描画
	virtual void SetCamera(const CCamera* pCamera);								//カメラセッタ
	virtual void SetPos(const TPos3d<float>& fPos);								//位置セッタ
	virtual void SetSize(const TTriType<float>& fScale);						//大きさセッタ
	virtual void SetRotate(const TTriType<float>& fRotate);						//回転セッタ
	virtual void SetTransform(const tagTransform3d& Transform);					//ワールド座標セッタ
	virtual void SetUvOffset(const TDiType<float>& fUvOffset);					//UVずれセッタ
	virtual void SetUvScale(const TDiType<float>& fUvScale);					//UV拡縮セッタ
	virtual void SetColor(const TTriType<float>& fRGB, const float& fAlpha);	//色セッタRGBA
	virtual void SetColor(const TTriType<float>& fRGB);							//色セッタRGB
	virtual void SetColor(const float& fColor);									//色セッタ(同一値)
	virtual void SetAlpha(const float& fAlpha);									//透明度セッタ
	virtual void SetTexture(const char* pcTexPass);								//テクスチャ登録
	virtual void SetTexture(Texture* pTexture);									//テクスチャ登録
	virtual void SetVertexShader(VertexShader* pVs);							//頂点シェーダセッタ
	virtual void SetPixelShader(PixelShader* pPs);								//ピクセルシェーダセッタ
protected:
	// ===メンバ変数宣言=====
	tagTransform3d m_Transform;	//ワールド座標
private:
	// ===メンバ変数宣言=====
	DirectX::XMFLOAT4X4 m_aMatrix[3];		//行列
	Param m_Param;							//シェーダーに書き込む情報
	static VertexShader* ms_pDefVs;			//頂点シェーダー
	static PixelShader* ms_pDefPs;			//ピクセルシェーダー
	VertexShader* m_pVs;					//頂点シェーダー
	PixelShader* m_pPs;						//ピクセルシェーダー
	Texture* m_pTexture;					//テクスチャ情報
	Texture* m_pTextureLoad;				//テクスチャ情報	deleteしない、ポインタは受け取るだけ
	static int ms_nCnt2dPolygon;			//自身の生成数
	static const void* ms_pVtx;				//頂点情報
	static unsigned int ms_unVtxSize;		//頂点サイズ
	static unsigned int ms_unVtxCount;		//頂点数
	static const void* ms_pIdx;				//頂点インデックス
	static unsigned int ms_unIdxSize;		//インデックスサイズ
	static unsigned int ms_unIdxCount;		//インデックス数
	static ID3D11Buffer* ms_pVtxBuffer;		//頂点バッファ
	static ID3D11Buffer* ms_pIdxBuffer;		//インデックスバッファ
	const CCamera* m_pCamera;				//カメラ追跡
	static const CCamera* ms_pCameraDef;	//疑似カメラ
	// ===プロトタイプ宣言===
	void MakeVertexShader();		//頂点シェーダ作成
	void MakePixelShader();			//ピクセルシェーダー
	static void Make();				//形作成
	static void CreateVtxBuffer();	//頂点バッファ作成
	static void CreateIdxBuffer();	//インデックスバッファ作成
};	//フェード

#endif // !___2D_POLYGON_H___