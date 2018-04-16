cbuffer MatrixBuffer : register(b0)
{
	matrix projectionViewWorldMatrix;
};

struct VertexInputType
{
    float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
	float2 tex2 : TEXCOORD1;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
	float2 tex2 : TEXCOORD1;
};

PixelInputType VertexProgram(VertexInputType input)
{
    PixelInputType output;

    input.position.w = 1.0f;
	output.position = mul(input.position, projectionViewWorldMatrix);
	output.tex = input.tex;
	output.tex2 = input.tex2;
	output.normal = mul(input.normal,(float3x3)projectionViewWorldMatrix);
	output.normal = normalize(output.normal);

	output.tangent = mul(input.tangent,(float3x3)projectionViewWorldMatrix);
	output.tangent = normalize(output.tangent);

	output.binormal = mul(input.binormal,(float3x3)projectionViewWorldMatrix);
	output.binormal = normalize(output.binormal);

    return output;
}