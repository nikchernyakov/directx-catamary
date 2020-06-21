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
};

struct PS_DATA
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
};

PS_DATA VSMain(VS_DATA input)
{
	PS_DATA output;
	output.pos = mul(float4(input.pos, 1.0f), World);
	output.pos = mul(output.pos, View);
	output.pos = mul(output.pos, Projection);
	output.color = input.color;
	return output;
}

float4 PSMain(PS_DATA input) : SV_Target
{
	return input.color;
}