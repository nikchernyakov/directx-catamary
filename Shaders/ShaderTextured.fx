Texture2D txDiffuse : register(t0);        // Буфер текстуры
SamplerState samLinear : register(s0);     // Буфер образца

cbuffer CBuf : register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;
};

cbuffer LightBuffer : register(b1)
{
	float4 diffuseColor;
	float3 lightDirection;
	float padding;
};

struct VS_DATA
{
	float3 pos : POSITION;
	float4 color : COLOR;
	float3 normal : NORMAL;
	float2 tex : TEXCOORD;
};

struct PS_DATA
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float3 normal : NORMAL;
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

	// Calculate the normal vector against the world matrix only.
	output.normal = mul(input.normal, (float3x3)World);
	output.normal = normalize(output.normal);

	return output;
}

float4 PSMain(PS_DATA input) : SV_Target
{
	float4 textureColor;
	float3 lightDir;
	float lightIntensity;
	float4 finalColor;

	textureColor = txDiffuse.Sample(samLinear, input.tex);

	// Invert the light direction for calculations.
	lightDir = -lightDirection;

	// Calculate the amount of light on this pixel.
	lightIntensity = saturate(dot(input.normal, lightDir));

	// Determine the final amount of diffuse color based on the diffuse color combined with the light intensity.
	finalColor = saturate(diffuseColor * lightIntensity);

	// Multiply the texture pixel and the final diffuse color to get the final pixel color result.
	finalColor = finalColor * textureColor;

	return finalColor;
}