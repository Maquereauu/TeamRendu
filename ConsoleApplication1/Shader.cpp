#include "Shader.h"
#include "Global.h"
#include "Render.h"
#include "Mesh.h"




GCShader::GCShader() {

}


GCShader::~GCShader()
{

};



void GCShader::Render() {
	m_pRender->GetCommandList()->SetPipelineState(GetPso());
	m_pRender->GetCommandList()->SetGraphicsRootSignature(GetRootSign());
}

void GCShader::Initialize(GCRender* pRender) {

}

void GCShader::CompileShader() {

}

void GCShader::RootSign() {
	CD3DX12_ROOT_PARAMETER slotRootParameter[2];

	//int count = 0;
	// Create a single descriptor table of CBVs.
	switch (m_count) {
	case 1:
	{
		//CD3DX12_DESCRIPTOR_RANGE cbvTable; cbvTable.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);
		//slotRootParameter[1].InitAsDescriptorTable(1, &cbvTable);
		slotRootParameter[0].InitAsConstantBufferView(0);
		break;
	}
	case 2:
	{
		// Add descriptor range for shader resource views (SRVs)
		CD3DX12_DESCRIPTOR_RANGE srvTable;
		srvTable.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);
		slotRootParameter[0].InitAsDescriptorTable(1, &srvTable);

		// For the texture shader
   // For the texture shader
		slotRootParameter[1].InitAsConstantBufferView(0);

		// Add descriptor range for sampler
		//CD3DX12_DESCRIPTOR_RANGE samplerTable;
		//samplerTable.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER, 1, 0);
		//slotRootParameter[2].InitAsDescriptorTable(1, &samplerTable);
		break;

	}
	}
	CD3DX12_STATIC_SAMPLER_DESC staticSample = CD3DX12_STATIC_SAMPLER_DESC(
		0, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP, // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP, // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP, // addressW
		0.0f, // mipLODBias
		16, // maxAnisotropy
		D3D12_COMPARISON_FUNC_ALWAYS, // comparisonFunc
		D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK, // borderColor
		0.0f, // minLOD
		D3D12_FLOAT32_MAX // maxLOD
	);
	// A root signature is an array of root parameters.
	CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(m_count, slotRootParameter, 1, &staticSample, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
	// create a root signature with a single slot which points to a descriptor range consisting of a single constant buffer
	ID3DBlob* serializedRootSig = nullptr;
	ID3DBlob* errorBlob = nullptr;
	HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1,
		&serializedRootSig, &errorBlob);

	if (errorBlob != nullptr)
	{
		::OutputDebugStringA((char*)errorBlob->GetBufferPointer());
	}
	ThrowIfFailed(hr);
	ThrowIfFailed(m_pRender->Getmd3dDevice()->CreateRootSignature(
		0,
		serializedRootSig->GetBufferPointer(),
		serializedRootSig->GetBufferSize(),
		IID_PPV_ARGS(&m_RootSignature)));
}

void GCShader::Pso() {
	// Initialize the graphics pipeline state description
	ZeroMemory(&psoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	psoDesc.InputLayout = { m_InputLayout.data(), (UINT)m_InputLayout.size() };
	psoDesc.pRootSignature = m_RootSignature;
	psoDesc.VS =
	{
		reinterpret_cast<BYTE*>(m_vsByteCode->GetBufferPointer()),
		m_vsByteCode->GetBufferSize()
	};
	psoDesc.PS =
	{
		reinterpret_cast<BYTE*>(m_psByteCode->GetBufferPointer()),
		m_psByteCode->GetBufferSize()
	};
	psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);

	// Customize the blend state for transparency
	CD3DX12_BLEND_DESC blendDesc(D3D12_DEFAULT);
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	psoDesc.BlendState = blendDesc;

	// Use default depth stencil state
	psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);

	// Set other pipeline state settings
	//psoDesc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME; //permet de voir les bordure
	psoDesc.SampleMask = UINT_MAX;
	psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psoDesc.NumRenderTargets = 1;
	psoDesc.RTVFormats[0] = m_pRender->GetBackBufferFormat();
	psoDesc.SampleDesc.Count = m_pRender->Get4xMsaaState() ? 4 : 1;
	psoDesc.SampleDesc.Quality = m_pRender->Get4xMsaaState() ? (m_pRender->Get4xMsaaQuality() - 1) : 0;
	psoDesc.DSVFormat = m_pRender->GetDepthStencilFormat();

	// Create the graphics pipeline state
	ThrowIfFailed(m_pRender->Getmd3dDevice()->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&m_PSO)));
}



ID3D12RootSignature* GCShader::GetRootSign() {
	return m_RootSignature;
}

ID3D12PipelineState* GCShader::GetPso() {
	return m_PSO;
}


ID3DBlob* GCShader::GetmvsByteCode()
{
	return m_vsByteCode;
};

ID3DBlob* GCShader::GetmpsByteCode()
{
	return m_psByteCode;
};