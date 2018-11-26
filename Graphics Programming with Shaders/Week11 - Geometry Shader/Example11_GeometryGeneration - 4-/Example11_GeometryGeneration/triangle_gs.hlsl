
cbuffer MatrixBuffer : register(b0)
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

cbuffer quadPositionBuffer
{
	static float3 gPositions[4] =
	{
		float3 (-1,1,0),
		float3 (-1,-1,0),
		float3 (1,1,0),
		float3 (1,-1,0),
	};

	static float2 gTexCoords[4] =
	{
		float2 (0,0),
		float2 (0,1),
		float2 (1,0),
		float2 (1,1),
	};
};

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
};

[maxvertexcount(4)]
void main(point InputType input[1], inout TriangleStream<OutputType> triStream)
{
	OutputType output;

	//quads
	for (int i = 0; i < 4; i++)
	{
		float4 vposition = float4(gPositions[i], 1.0f) + input[0].position;
		output.position = mul(vposition, worldMatrix);
		output.position = mul(output.position, viewMatrix);
		output.position = mul(output.position, projectionMatrix);
		output.tex = gTexCoords[i];
		output.normal = input[0].normal;
		triStream.Append(output);
	}

	//// Move the vertex away from the point position
 //   output.position = input[0].position + float4(0.0, 2.0, 0.0, 0.0);
 //   output.position = mul(output.position, worldMatrix);
 //   output.position = mul(output.position, viewMatrix);
 //   output.position = mul(output.position, projectionMatrix);
 //   output.tex = input[0].tex + float4(0.0, 2.0, 0.0, 0.0);
 //   output.normal = mul(input[0].normal, (float3x3) worldMatrix);
 //   output.normal = normalize(output.normal);
 //   triStream.Append(output);

	//// Move the vertex away from the point position
 //   output.position = input[0].position + float4(-2.0, 0.0, 0.0, 0.0);
 //   output.position = mul(output.position, worldMatrix);
 //   output.position = mul(output.position, viewMatrix);
 //   output.position = mul(output.position, projectionMatrix);
	//output.tex = input[0].tex + float4(-2.0, 0.0, 0.0, 0.0);
 //   output.normal = mul(input[0].normal, (float3x3) worldMatrix);
 //   output.normal = normalize(output.normal);
 //   triStream.Append(output);

	//// Move the vertex away from the point position
 //   output.position = input[0].position + float4(2.0, 0.0, 0.0, 0.0);
 //   output.position = mul(output.position, worldMatrix);
 //   output.position = mul(output.position, viewMatrix);
 //   output.position = mul(output.position, projectionMatrix);
	//output.tex = input[0].tex + float4(2.0, 0.0, 0.0, 0.0);
 //   output.normal = mul(input[0].normal, (float3x3) worldMatrix);
 //   output.normal = normalize(output.normal);
 //   triStream.Append(output);

	triStream.RestartStrip();

	
}