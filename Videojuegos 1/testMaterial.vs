
cbuffer MatrixBuffer
{
	matrix projectionViewWorldMatrix;
};

cbuffer MaterialBuffer
{
	float4 materialColor;
};

struct VertexInputType
{
    float4 position : POSITION;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
	float4 materialColor : COLOR;
};

PixelInputType BasicVertexShader(VertexInputType input)
{
    PixelInputType output;

    input.position.w = 1.0f;
	output.position = mul(input.position, projectionViewWorldMatrix);
    output.materialColor = materialColor;

    return output;
}