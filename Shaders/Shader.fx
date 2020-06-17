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
};

VS_DATA VSMain(float3 pos : POSITION, float4 color : COLOR)
{
	VS_DATA vso;
	vso.pos = mul(float4(pos, 1.0f), World);
	vso.pos = mul(vso.pos, View);
	vso.pos = mul(vso.pos, Projection);
	vso.color = color;
	return vso;
}

float4 PSMain(VS_DATA input) : SV_Target
{
	return input.color;
}