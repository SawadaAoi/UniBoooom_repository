/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	フェード用ピクセルシェーダー
	------------------------------------
	PsFade.hlsl
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/11/18 制作 takagi
	・2023/11/19 18の続き takagi
	・2023/11/20 整理 takagi

========================================== */

struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};
Texture2D tex : register(t0);
SamplerState samp : register(s2);

//SamplerState samp : register(s1)
//{
//	AddressU = WRAP;
//	AddressV = MIRROR;
//};
float4 main(PS_IN pin) : SV_TARGET{
	//return tex.Sample(samp, pin.uv) * pin.color;

	return float4(pin.color.x, pin.color.y, pin.color.z, (1.0f - tex.Sample(samp, pin.uv).w));
}