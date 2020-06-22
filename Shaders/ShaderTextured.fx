Texture2D shaderTexture : register(t0);        // Буфер текстуры
SamplerState SampleTypeWrap : register(s0);     // Буфер образца

Texture2D depthMapTexture : register(t1);
SamplerState SampleTypeClamp  : register(s1);


cbuffer CBuf : register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;
	matrix lightView;
	matrix lightProjection;
};

cbuffer LightBuffer : register(b1)
{
	float4 ambientColor;
	float4 diffuseColor;
	float3 lightPosition;
	float3 lightDirection;
	float specularPower;
	float4 specularColor;
	float lightPadding;
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
	float2 tex : TEXCOORD;
};

struct PS_DATA
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float3 normal : NORMAL;
	float2 tex : TEXCOORD0;
	float3 viewDirection : TEXCOORD1;
	float4 lightViewPosition : TEXCOORD2;
	float3 lightPos : TEXCOORD3;
};

PS_DATA VSMain(VS_DATA input)
{
	PS_DATA output;
	
	output.pos = mul(float4(input.pos, 1.0f), World);
	output.pos = mul(output.pos, View);
	output.pos = mul(output.pos, Projection);
	
	// Calculate the position of the vertice as viewed by the light source.
	output.lightViewPosition = mul(float4(input.pos, 1.0f), World);
	output.lightViewPosition = mul(output.lightViewPosition, lightView);
	output.lightViewPosition = mul(output.lightViewPosition, lightProjection);

	output.color = input.color;
	output.tex = input.tex;

	// Calculate the normal vector against the world matrix only.
	output.normal = mul(float4(input.normal, 0.0f), World);
	output.normal = normalize(output.normal);

	// Calculate the position of the vertex in the world.
	float4 worldPosition = mul(float4(input.pos, 1.0f), World);

	// Determine the viewing direction based on the position of the camera and the position of the vertex in the world.
	output.viewDirection = cameraPosition.xyz - worldPosition.xyz;
	output.viewDirection = normalize(output.viewDirection);

	// Determine the light position based on the position of the light and the position of the vertex in the world.
	output.lightPos = lightPosition.xyz - worldPosition.xyz;
	output.lightPos = normalize(output.lightPos);

	return output;
}

float4 PSMain(PS_DATA input) : SV_Target
{
	// Set the bias value for fixing the floating point precision issues.
	float bias = 0.001f;

	// Calculate the projected texture coordinates.
	float2 projectTexCoord;
	projectTexCoord.x = input.lightViewPosition.x / input.lightViewPosition.w / 2.0f + 0.5f;
	projectTexCoord.y = -input.lightViewPosition.y / input.lightViewPosition.w / 2.0f + 0.5f;
	return float4(projectTexCoord, 0.0f, 1.0f);

	// Set the default output color to the ambient light value for all pixels.
	float4 finalColor = ambientColor;

	// Initialize the specular color.
	float4 specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// Determine if the projected coordinates are in the 0 to 1 range.  If so then this pixel is in the view of the light.
	if ((saturate(projectTexCoord.x) == projectTexCoord.x)
		&& (saturate(projectTexCoord.y) == projectTexCoord.y))
	{
		// Invert the light direction for calculations.
		float3 lightDir = -lightDirection;

		// Sample the shadow map depth value from the depth texture using the sampler at the projected texture coordinate location.
		float depthValue = depthMapTexture.Sample(SampleTypeClamp, projectTexCoord).r;

		// Calculate the depth of the light.
		float lightDepthValue = input.lightViewPosition.z / input.lightViewPosition.w;

		// Subtract the bias from the lightDepthValue.
		lightDepthValue = lightDepthValue - bias;

		// Compare the depth of the shadow map value and the depth of the light to determine whether to shadow or to light this pixel.
		// If the light is in front of the object then light the pixel, if not then shadow this pixel since an object (occluder) is casting a shadow on it.
		if (lightDepthValue < depthValue)
		{
			return float4(1.0f, 0.0f, 0.0f, 1.0f);
			// Calculate the amount of light on this pixel.
			//float lightIntensity = saturate(dot(input.normal, lightDir));
			float lightIntensity = saturate(dot(input.normal, input.lightPos));
			if (lightIntensity > 0.0f)
			{
				// Determine the final diffuse color based on the diffuse color and the amount of light intensity.
				finalColor += (diffuseColor * lightIntensity);
				// Saturate the ambient and diffuse color.
				finalColor = saturate(finalColor);

				/*// Calculate the reflection vector based on the light intensity, normal vector, and light direction.
				float3 reflection = normalize(2 * lightIntensity * input.normal - lightDir);
				// Determine the amount of specular light based on the reflection vector, viewing direction, and specular power.
				specular = pow(saturate(dot(reflection, input.viewDirection)), specularPower);
				// Add the specular component last to the output color.
				finalColor = saturate(finalColor + specular);*/
			}
		}
	}

	// Multiply the texture pixel and the final diffuse color to get the final pixel color result.
	float4 textureColor = shaderTexture.Sample(SampleTypeWrap, input.tex);
	finalColor = finalColor * textureColor;

	return finalColor;
}