#include "ShaderTexture.h"

void GCShaderTexture::CompileShader() {
	m_vsByteCode = d3dUtil::CompileShader(L"Shaders\\texture.hlsl", nullptr, "VS", "vs_5_0");
	m_psByteCode = d3dUtil::CompileShader(L"Shaders\\texture.hlsl", nullptr, "PS", "ps_5_0");
	m_InputLayout =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};
	m_count = 2;
}

void GCShaderTexture::Initialize(GCRender* pRender) {

	m_pRender = pRender;


	CompileShader();
	RootSign();
	Pso();
}