// Light vertex shader
// Standard issue vertex shader, apply matrices, pass info to pixel shader
cbuffer MatrixBuffer : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

cbuffer TimeBuffer : register(b1)
{
	float time;
	float frequency;
	float height;
	float speed;
}

struct InputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

struct OutputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 worldPosition : TEXCOORD1;
};

OutputType main(InputType input)
{
	OutputType output;

	
	
	
    input.position.y += height * (sin(frequency * (time + input.position.x)));

	//modify normals
    input.normal.x = 1 - cos(frequency * (time + input.position.x));
    input.normal.y = abs(cos((frequency/2) * (time + input.position.x)));

    

	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	//moves the texture with the sin wave
    input.tex.x += time * 0.09f;

	// Store the texture coordinates for the pixel shader.
	output.tex = input.tex;

	
	
	// Calculate the normal vector against the world matrix only and normalise.
	output.normal = mul(input.normal, (float3x3)worldMatrix);
	output.normal = normalize(output.normal);
	output.worldPosition = mul(input.position, worldMatrix).xyz;

	//output.position.y += height * sin(time + input.position.x);

	return output;
}