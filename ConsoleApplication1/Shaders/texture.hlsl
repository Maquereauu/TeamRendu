Texture2D g_texture : register(t0); // Texture bound to t0, register space 0
SamplerState g_sampler : register(s0); // Sampler bound to s0, register space 0

cbuffer cbPerObject : register(b0)
{
    float4x4 gWorldViewProj;
};

struct VertexIn
{
    float3 PosL : POSITION;
    float2 UV : TEXCOORD;
};

struct VertexOut
{
    float4 PosH : SV_POSITION;
    float2 UV : TEXCOORD;
};

VertexOut VS(VertexIn vin)
{
    VertexOut vout;
    
    // Transform to homogeneous clip space.
    vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);
    
    // Pass vertex texture coordinates into the pixel shader.
    vout.UV = vin.UV;
    
    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    float4 texColor = g_texture.Sample(g_sampler, pin.UV);
    return texColor * texColor.a; // Apply transparency using alpha channel
}