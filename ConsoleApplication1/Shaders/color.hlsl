//cbuffer cbPerObject : register(b0)
//{
//    float4x4 gWorldViewProj;
//};

//struct VertexIn
//{
//    float3 PosL : POSITION;
//    float4 Color : COLOR;
//};

//struct VertexOut
//{
//    float4 PosH : SV_POSITION;
//    float4 Color : COLOR;
//};

//VertexOut VS(VertexIn vin)
//{
//    VertexOut vout;
	
//	// Transform to homogeneous clip space.
//    vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);
	
//	// Just pass vertex color into the pixel shader.
//    vout.Color = vin.Color;
    
//    return vout;
//}

//float4 PS(VertexOut pin) : SV_Target
//{
//    return pin.Color;
//}

cbuffer Data : register(b0)
{
    float4x4 model;
    float4x4 view;
    float4x4 projection;
};

Texture2D g_texture : register(t0); // Texture bound to t0, register space 0
SamplerState g_sampler : register(s0); // Sampler bound to s0, register space 0

struct VSInput
{
    float3 position : POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

struct VSOutput
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

VSOutput VSMain(VSInput input)
{
    VSOutput result;

    result.position = mul(float4(input.position, 1.0f), model);
    result.position = mul(result.position, view);
    result.position = mul(result.position, projection);

    result.color = input.color;
    result.uv = input.uv;

    return result;
}

float4 PSMain(VSOutput input) : SV_TARGET
{
    return g_texture.Sample(g_sampler, input.uv);
}