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
	float3 pos : POSITION;
	float4 color : COLOR;
	float2 tex : TEXCOORD;
};

struct PS_DATA
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float2 tex : TEXCOORD;
};

PS_DATA VSMain(VS_DATA input)
{
	PS_DATA output;
	output.pos = mul(float4(input.pos, 1.0f), World);
	output.pos = mul(output.pos, View);
	output.pos = mul(output.pos, Projection);
	output.color = input.color;
	output.tex = input.tex;
	return output;
}

float4 PSMain(PS_DATA input) : SV_Target
{
	float4 finalColor = txDiffuse.Sample(samLinear, input.tex);
	finalColor.a = 1.0f;
	return finalColor;
}