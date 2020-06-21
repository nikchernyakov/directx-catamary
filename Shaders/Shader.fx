cbuffer CBuf : register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;
};

cbuffer LightBuffer : register(b1)
{
	float4 ambientColor;
	float4 diffuseColor;
	float3 lightDirection;
	float padding;
};

struct VS_DATA
{
	float3 pos : POSITION;
	float4 color : COLOR;
	float3 normal : NORMAL;
};

struct PS_DATA
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float3 normal : NORMAL;
};

PS_DATA VSMain(VS_DATA input)
{
	PS_DATA output;

	output.pos = mul(float4(input.pos, 1.0f), World);
	output.pos = mul(output.pos, View);
	output.pos = mul(output.pos, Projection);

	output.color = input.color;

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

	textureColor = input.color;

	// Set the default output color to the ambient light value for all pixels.
	finalColor = ambientColor;

	// Invert the light direction for calculations.
	lightDir = -lightDirection;

	// Calculate the amount of light on this pixel.
	lightIntensity = saturate(dot(input.normal, lightDir));

	if (lightIntensity > 0.0f)
	{
		// Determine the final diffuse color based on the diffuse color and the amount of light intensity.
		finalColor += (diffuseColor * lightIntensity);
	}

	// Saturate the final light color.
	finalColor = saturate(finalColor);

	// Multiply the texture pixel and the final diffuse color to get the final pixel color result.
	finalColor = finalColor * textureColor;

	return finalColor;
}