// Tessellation domain shader
// After tessellation the domain shader processes the all the vertices

cbuffer MatrixBuffer : register(b0)
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

cbuffer TimeBuffer : register(b1)
{
	// x = height, y = frequency, z = speed, w = time
	float4 timebufferData;
};

struct ConstantOutputType
{
    float edges[4] : SV_TessFactor;
    float inside[2] : SV_InsideTessFactor;
};

struct InputType
{
    float3 position : POSITION;
    float4 colour : COLOR;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

struct OutputType
{
    float4 position : SV_POSITION;
    float4 colour : COLOR;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 worldPosition : TEXCOORD1;
};

[domain("quad")]
OutputType main(ConstantOutputType input, float2 uvCoord : SV_DomainLocation, const OutputPatch<InputType, 4> patch)
{
    float3 vertexPosition;
    OutputType output;
 
    // Determine the position of the new vertex.
	// Invert the y and Z components of uvwCoord as these coords are generated in UV space and therefore y is positive downward.
	// Alternatively you can set the output topology of the hull shader to cw instead of ccw (or vice versa).
	float3 v1 = lerp(patch[0].position, patch[1].position, uvCoord.y);
	float3 v2 = lerp(patch[3].position, patch[2].position, uvCoord.y);
	vertexPosition = lerp(v1, v2, uvCoord.x);
	
	output.worldPosition = mul(patch[0].position, worldMatrix).xyz;

	vertexPosition.z += timebufferData.x * sin((vertexPosition.xy * timebufferData.y) + timebufferData.w);
	//vertexPosition += 2 * sin((vertexPosition.x * 3) + 3);

    // Calculate the position of the new vertex against the world, view, and projection matrices.
    output.position = mul(float4(vertexPosition, 1.0f), worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);

	// Store the texture coordinates for the pixel shader.
	//animated texture moving along x axis with time
	 output.tex = patch[0].tex;
	//output.tex.x += time;
	 output.normal = patch[0].normal;
	// Calculate the normal vector against the world matrix only and normalise.
	output.normal = mul(output.normal, (float3x3)worldMatrix);
	output.normal = normalize(output.normal);
	
    // Send the input color into the pixel shader.
    output.colour = patch[0].colour;

    return output;
}

