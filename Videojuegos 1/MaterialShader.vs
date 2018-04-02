cbuffer MatrixBuffer
{
	matrix projectionViewWorldMatrix;
	matrix tex;
};

struct VertexInputType
{
    float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

PixelInputType MaterialVertexShader(VertexInputType input)
{
    PixelInputType output;
    
	// Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;

	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = mul(input.position, projectionViewWorldMatrix);

	//Store the texture coordinates for the pixel shader
	output.tex = input.tex;

	//Calculate the normal vector against the world matrix only
	output.normal =  mul(input.normal,(float3x3)projectionViewWorldMatrix);

	//Normalize the normal vector
	output.normal = normalize(output.normal);

    return output;
}