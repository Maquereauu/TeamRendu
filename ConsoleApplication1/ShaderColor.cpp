#include "ShaderColor.h"

void GCShaderColor::CompileShader(std::wstring hlsl) {
	m_vsByteCode = d3dUtil::CompileShader(L"Shaders\\"+ hlsl + L".hlsl", nullptr, "VS", "vs_5_0");
	m_psByteCode = d3dUtil::CompileShader(L"Shaders\\" + hlsl + L".hlsl", nullptr, "PS", "ps_5_0");
	m_InputLayout =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};
	m_count = 1;
}

void GCShaderColor::Initialize(GCRender* pRender, std::wstring hlslName) {

	m_pRender = pRender;


	CompileShader(hlslName);
	RootSign();
	Pso();
}

