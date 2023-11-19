struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};
Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samp : register(s2);

//SamplerState samp : register(s1)
//{
//	AddressU = WRAP;
//	AddressV = MIRROR;
//};
float4 main(PS_IN pin) : SV_TARGET{
	//return tex.Sample(samp, pin.uv) * pin.color;

	return float4(pin.color.x, pin.color.y, pin.color.z, (1.0f - tex2.Sample(samp, pin.uv).w) * (1.0f - tex.Sample(samp, pin.uv).w));
}