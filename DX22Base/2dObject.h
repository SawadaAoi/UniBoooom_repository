/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	2Dオブジェクト定義
	------------------------------------
	2dObject.h
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/11/21 作成 takagi
	・2023/11/28 TextureSet関数にポインタ指定できる物を追加 takagi
	・2023/12/01 テクスチャの扱い方を安全化 takagi
	・2023/12/05 描画のモード追加 takagi
	・2023/12/06 Draw()関数のデフォルト引数変更 takagi
	・2023/12/10 静的変数の名前を修正・デフォルトのカメラも静的関数化。 takagi
	・2023/12/15 空の更新関数追加 takagi
	・2023/12/17 引数参照化 takagi
	・2023/12/20 継承先がやりにくかったのでワールド変数をprotected化 takagi
	・2024/01/16 統一のため、インクルードガードの___を__に変更	takagi
	・2024/01/16 リネーム・継承・不要箇所削除 takagi
	・2024/01/18 リファクタリング及びコメント追加 takagi
	・2024/01/20 GetPos()関数追加 takagi
	・2024/01/21 コメント改修・定数修正・汎化作業 takagi
	・2024/01/22 Draw()関数const化 takagi

========================================== */

#ifndef __2D_OBJECT_H__	//2dObject.hインクルードガード
#define __2D_OBJECT_H__

// =============== インクルード ===================
#include "Object.h"		//親のヘッダ
#include "Texture.h"	//メンバのヘッダ

// =============== クラス定義 =====================
class C2dObject	:public CObject	//オブジェクト継承
{
public:
	// ===列挙定義===========
	enum E_DRAW_MODE
	{
		E_DRAW_MODE_NORMAL,		//通常の描画
		E_DRAW_MODE_BILLBOARD,	//ビルボードとして描画
	};	//描画方法
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
	// ===定数定義===========
	static const E_DRAW_MODE DEFAULT_DRAW_MODE = E_DRAW_MODE_NORMAL;	//描画方法の規定値
	const int FRAME_MIN = 0;											//フェード時間の最小
	const int FRAME_TURNING_1 = 50;										//拡縮反転１反転
	const int FRAME_TURNING_2 = 100;									//拡縮反転２反転
	const int FRAME_MAX = 150;											//フェード時間の最大
	const float SCALE_MIN = 0.0f;										//最小サイズ
	const float SCALE_TURNINIG_2 = 30.0f;								//サイズ反転２反転
	const float SCALE_TURNINIG_1 = 100.0f;								//サイズ反転１反転
	const float SCALE_MAX = 1000.0f;									//最大サイズ
	const float ROTATE_ACCEL_RATE = 4.0f;								//角速度増加割合
	const TPos3d<float> INIT_POS = { 640.0f, 360.0f, 0.0f };			//初期位置
	const TTriType<float> INIT_SCALE = { 1.0f, 1.0f, 0.0f };			//初期拡縮
public:
	// ===プロトタイプ宣言===
	C2dObject();																	//コンストラクタ
	C2dObject(const C2dObject& Obj);												//コピーコンストラクタ
	virtual ~C2dObject();															//デストラクタ
	virtual void Update();															//更新
	virtual void Draw() const override;												//描画
	virtual void SetDrawMode(const E_DRAW_MODE& eMode = DEFAULT_DRAW_MODE) final;	//描画法セッタ
	virtual void SetUvOffset(const TDiType<float>& fUvOffset) final;				//UVずれセッタ
	virtual void SetUvScale(const TDiType<float>& fUvScale) final;					//UV拡縮セッタ
	virtual void SetColor(const TTriType<float>& fRGB, const float& fAlpha) final;	//色セッタRGBA
	virtual void SetColor(const TTriType<float>& fRGB) final;						//色セッタRGB
	virtual void SetColor(const float& fColor) final;								//色セッタ(同一値)
	virtual void SetAlpha(const float& fAlpha) final;								//透明度セッタ
	virtual void SetTexture(const char* pcTexPass) final;							//テクスチャ登録
	virtual void SetTexture(Texture* pTexture) final;								//テクスチャ登録
	virtual void SetVertexShader(VertexShader* pVs) final;							//頂点シェーダセッタ
	virtual void SetPixelShader(PixelShader* pPs) final;							//ピクセルシェーダセッタ
private:
	// ===メンバ変数宣言=====
	Param m_Param;									//シェーダーに書き込む情報
	static VertexShader* ms_pDefVs;					//デフォルト頂点シェーダー
	static PixelShader* ms_pDefPs;					//デフォルトピクセルシェーダー
	VertexShader* m_pVs;							//頂点シェーダー
	PixelShader* m_pPs;								//ピクセルシェーダー
	Texture* m_pTexture;							//テクスチャ情報
	Texture* m_pTextureLoad;						//テクスチャ情報	deleteしない、ポインタは受け取るだけ
	E_DRAW_MODE m_eMode;							//描画方法
	static int ms_nCnt2dObject;						//自身の生成数
	static const void* ms_pVtx;						//頂点情報
	static unsigned int ms_unVtxSize;				//頂点サイズ
	static unsigned int ms_unVtxCount;				//頂点数
	static const void* ms_pIdx;						//頂点インデックス
	static unsigned int ms_unIdxSize;				//インデックスサイズ
	static unsigned int ms_unIdxCount;				//インデックス数
	static ID3D11Buffer* ms_pVtxBuffer;				//頂点バッファ
	static ID3D11Buffer* ms_pIdxBuffer;				//インデックスバッファ
	// ===プロトタイプ宣言===
	void MakeVertexShader();		//頂点シェーダ作成
	void MakePixelShader();			//ピクセルシェーダー
	static void Make();				//形作成
	static void CreateVtxBuffer();	//頂点バッファ作成
	static void CreateIdxBuffer();	//インデックスバッファ作成
};	//2Dオブジェクト

#endif	//!__2D_OBJECT_H__