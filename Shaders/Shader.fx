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
	float specularPower;
	float4 specularColor;
};

cbuffer CameraBuffer : register(b2)
{
	float3 cameraPosition;
	float cameraPadding;
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
	float3 viewDirection : TEXCOORD1;
};

PS_DATA VSMain(VS_DATA input)
{
	PS_DATA output;

	output.pos = mul(float4(input.pos, 1.0f), World);
	output.pos = mul(output.pos, View);
	output.pos = mul(output.pos, Projection);

	output.color = input.color;

	// Calculate the normal vector against the world matrix only.
	output.normal = mul(float4(input.normal, 0.0f), World).xyz;
	output.normal = normalize(output.normal);

	// Calculate the position of the vertex in the world.
	float4 worldPosition = mul(float4(input.pos, 1.0f), World);

	// Determine the viewing direction based on the position of the camera and the position of the vertex in the world.
	output.viewDirection = cameraPosition.xyz - worldPosition.xyz;
	output.viewDirection = normalize(output.viewDirection);

	return output;
}

float4 PSMain(PS_DATA input) : SV_Target
{
	float4 textureColor = input.color;

	// Set the default output color to the ambient light value for all pixels.
	float4 finalColor = ambientColor;

	// Initialize the specular color.
	float4 specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// Invert the light direction for calculations.
	float3 lightDir = -lightDirection;

	// Calculate the amount of light on this pixel.
	float lightIntensity = saturate(dot(input.normal, lightDir));
	if (lightIntensity > 0.0f)
	{
		// Determine the final diffuse color based on the diffuse color and the amount of light intensity.
		finalColor += (diffuseColor * lightIntensity);
		// Saturate the ambient and diffuse color.
		finalColor = saturate(finalColor);
		// Calculate the reflection vector based on the light intensity, normal vector, and light direction.
		float3 reflection = normalize(2 * lightIntensity * input.normal - lightDir);
		// Determine the amount of specular light based on the reflection vector, viewing direction, and specular power.
		specular = pow(saturate(dot(reflection, input.viewDirection)), specularPower);
	}

	// Multiply the texture pixel and the final diffuse color to get the final pixel color result.
	finalColor = finalColor * textureColor;

	// Add the specular component last to the output color.
	finalColor = saturate(finalColor + specular);

	return finalColor;
}