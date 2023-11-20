/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�t�F�[�h�p���_�V�F�[�_�[
	------------------------------------
	VsFade.hlsl
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/11/18 ���� takagi
	�E2023/11/19 18�̑��� takagi
	�E2023/11/20 ���� takagi

========================================== */


// =============== �\���̒�` =====================
struct VS_IN {
	float3 pos : POSITION0;
	float2 uv : TEXCOORD0;
};
struct VS_OUT {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};
cbuffer Matrix : register(b0) {
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};
cbuffer Uv : register(b1) {
	//float2 size;
	float2 uvPos;
	float2 uvScale;
};
//cbuffer Param : register(b1) {
//	float2 offset;
//	float2 size;
//	float2 uvPos;
//	float2 uvScale;
//	float4 color;
//};
VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	//vout.pos.xy *= size;
	//vout.pos.xy += offset;
	vout.pos = mul(vout.pos, world);
	vout.pos = mul(vout.pos, view);
	vout.pos = mul(vout.pos, proj);
	vout.uv = vin.uv;
	vout.uv + 0.5f;
	//vout.uv = vin.uv * 1.2f;
	vout.uv *= uvScale;
	vout.uv += float2(0.5f - uvScale.x / 2.0f, 0.5f - uvScale.y / 2.0f);
	//vout.uv -= float2(-uvScale.x / 4.0f, -uvScale.y / 2.0f);
	//vout.uv = (vout.uv - 0.5f) * 2.0f;
	//vout.uv += uvPos;
	vout.color = float4(0.0f, 0.0f, 0.0f, 1.0f);
	return vout;
}