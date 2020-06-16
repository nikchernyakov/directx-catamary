Texture2D txDiffuse : register(t0);        // Буфер текстуры
SamplerState samLinear : register(s0);     // Буфер образца

cbuffer CBuf : register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;
};

struct VS_DATA
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float2 tex : TEXCOORD;
};

VS_DATA VSMain(float3 pos : POSITION, float4 color : COLOR, float2 texCord : TEXCOORD0)
{
	VS_DATA vso;
	vso.pos = mul(float4(pos, 1.0f), World);
	vso.pos = mul(vso.pos, View);
	vso.pos = mul(vso.pos, Projection);
	vso.color = color;
	vso.tex = texCord;
	return vso;
}

float4 PSMain(VS_DATA input) : SV_Target
{
	float4 finalColor = txDiffuse.Sample(samLinear, input.tex);
	finalColor.a = 1;
	return finalColor;
}