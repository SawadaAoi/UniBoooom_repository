/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	フェード用頂点シェーダー
	------------------------------------
	VsFade.hlsl
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/11/18 制作 takagi
	・2023/11/19 18の続き takagi
	・2023/11/20 整理 takagi
	・2023/11/24 テクスチャが見えないときをつくるため定数バッファにUvOffset追加 takagi

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

	VsOut.fPos = float4(VsIn.fPos, 1.0f);										//位置情報格納
	VsOut.fPos = mul(VsOut.fPos, fWorld);										//ワールド行列適用
	VsOut.fPos = mul(VsOut.fPos, fView);										//ビュー行列適用
	VsOut.fPos = mul(VsOut.fPos, fProj);										//プロジェクション行列適用
	VsOut.fUv = VsIn.fUv;														//テクスチャ情報格納
	VsOut.fUv + 0.5f;															//UV座標系の原点を中央に移動
	VsOut.fUv *= fUvScale;														//指定された倍率で拡縮する
	VsOut.fUv += float2(0.5f - fUvScale.x / 2.0f, 0.5f - fUvScale.y / 2.0f);	//拡縮で右に延びた分、位置を補正する
	VsOut.fUv += fUvOffset;														//移動値がある場合はその分UV座標をずらす
	VsOut.fColor = float4(0.0f, 0.0f, 0.0f, 1.0f);								//色設定

	// =============== 提供 =====================
	return VsOut;	//出力
}