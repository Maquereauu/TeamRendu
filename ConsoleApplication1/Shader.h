#pragma once
#include "d3dUtil.h"
class Shader
{
public:
	Shader();
	~Shader();
	virtual void CompileShader();
	ID3DBlob* GetmvsByteCode();
	ID3DBlob* GetmpsByteCode();
	void RootSign();
	void Pso();

public:
	ID3D12RootSignature* m_RootSignature = nullptr;
	ID3D12PipelineState* m_PSO = nullptr;
	int m_Type;

protected:
	std::vector<D3D12_INPUT_ELEMENT_DESC> m_InputLayout;
	ID3DBlob* m_vsByteCode = nullptr;
	ID3DBlob* m_psByteCode = nullptr;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc;
	int m_count = 0;
};

