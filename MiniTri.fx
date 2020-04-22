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

struct PS_IN
{
	float4 pos : SV_POSITION;
	float4 col : COLOR;
};

/*VS_DATA VSMain(VS_DATA input)
{
	VS_DATA output = (VS_DATA)0;
	
	output.pos = mul(input.pos, MOVE);
	//output.pos = input.pos;
	output.col = input.col;
	
	return output;
}*/

VS_DATA VSMain(float4 pos : POSITION, float4 color : COLOR)
{
	VS_DATA vso;
	vso.pos = mul(pos, World);
	vso.pos = mul(vso.pos, View);
	vso.pos = mul(vso.pos, Projection);
	vso.color = color;
	return vso;
}

/*float4 PSMain( PS_IN input ) : SV_Target
{
	float4 col = input.col;
#ifdef TEST
	if (input.pos.x > 400) col = TCOLOR;
#endif

	return col;
}*/

float4 PSMain(VS_DATA input) : SV_Target
{
	return input.color;
}