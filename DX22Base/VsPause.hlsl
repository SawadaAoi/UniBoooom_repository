/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ポーズ用頂点シェーダー
	------------------------------------
	VsPause.hlsl
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/11/18 制作 takagi
	・2023/11/19 18の続き takagi
	・2023/11/20 整理 takagi
	・2023/12/01 2dPolygonに適する形に変更 takagi
	・2023/12/06 pose→pause修正、ポーズ文字表示 takagi

========================================== */

// =============== 構造体定義 =====================
struct VS_IN
{
	float3 fPos : POSITION0;	//位置情報
	float2 fUv : TEXCOORD0;		//テクスチャ情報
};	//受け取る情報
struct VS_OUT
{
	float4 fPos : SV_POSITION;	//位置情報
	float2 fUv : TEXCOORD0;		//テクスチャ情報
	float4 fColor : COLOR0;		//色情報
};	//渡す情報


// =============== 定数バッファ =====================
cbuffer Matrix : register(b0)
{
	float4x4 fWorld;	//ワールド行列
	float4x4 fView;		//ビュー行列
	float4x4 fProj;		//プロジェクション行列
};	//行列
cbuffer Uv : register(b1)
{
	float2 fUvScale;	//UV拡縮
	float2 fUvOffset;	//UV移動
	float4 fColor;		//色
};	//UV調整

/* ========================================
	メイン関数
	-------------------------------------
	内容：頂点ごとに情報を設定する
	-------------------------------------
	引数1：VS_IN VsIn：DirectXから受け取る情報
	-------------------------------------
	戻値：そのピクセルに表示する色情報(rgba)
=========================================== */
VS_OUT main(VS_IN VsIn)
{
	// =============== 変数宣言 =====================
	VS_OUT VsOut;	//出力用

	// =============== 更新 =====================
	VsOut.fPos = float4(VsIn.fPos, 1.0f);	//位置情報格納
	VsOut.fPos = mul(VsOut.fPos, fWorld);	//ワールド行列適用
	VsOut.fPos = mul(VsOut.fPos, fView);	//ビュー行列適用
	VsOut.fPos = mul(VsOut.fPos, fProj);	//プロジェクション行列適用
	VsOut.fUv = VsIn.fUv;					//テクスチャ情報格納
	VsOut.fUv + 0.5f;						//UV座標系の原点を中央に移動
	VsOut.fColor = fColor;					//色設定

	// =============== 提供 =====================
	return VsOut;	//出力
}