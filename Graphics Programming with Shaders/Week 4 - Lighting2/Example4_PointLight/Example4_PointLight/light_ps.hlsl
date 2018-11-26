// Light pixel shader
// Calculate diffuse lighting for a single directional light (also texturing)

Texture2D texture0 : register(t0);
SamplerState sampler0 : register(s0);

cbuffer LightBuffer : register(b0)
{
	float4 ambient[2];
	float4 diffuse[2];
	float4 position[2];
	
};

struct InputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 worldPosition : TEXCOORD1;
};

// Calculate lighting intensity based on direction and normal. Combine with light colour.
float4 calculateLighting(float3 lightDirection, float3 normal, float4 ldiffuse)
{
	float intensity = saturate(dot(normal, lightDirection));
	float4 colour = saturate(ldiffuse * intensity);
	return colour;
}

float4 main(InputType input) : SV_TARGET
{
	//attenuation values
	float constantFactor = 1.0f;
	float linearFactor = 0.125f;
	float quadratic = 0.0f;

	//distance between the light and the geometry
	float dist[2];
	float attenuation[2];
	float4 textureColour[2];
	float3 lightVector[2];
	float4 lightColour[2];

		dist[0] = length(position[0] - input.worldPosition);

		//calculate the attenuation
			attenuation[0] = 1 / (constantFactor + (linearFactor * dist[0]) + (quadratic * pow(dist[0], 2)));

			// Sample the texture. Calculate light intensity and colour, return light*texture for final pixel colour.
				textureColour[0] = texture0.Sample(sampler0, input.tex);

				lightVector[0] = normalize(position[0] - input.worldPosition);

				lightColour[0] = ambient[0] + calculateLighting(lightVector[0], input.normal, diffuse[0] * attenuation[0]);

			return lightColour[0] * textureColour[0];
}



