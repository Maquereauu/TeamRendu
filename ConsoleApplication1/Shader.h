#pragma once
#include "d3dUtil.h"

class GCRender;

class GCShader
{
public:
	GCShader();
	~GCShader();

	virtual void CompileShader();

	ID3DBlob* GetmvsByteCode();
	ID3DBlob* GetmpsByteCode();

	void RootSign();
	void Pso();

	ID3D12RootSignature* GetRootSign();
	ID3D12PipelineState* GetPso();

	virtual void Initialize(GCRender* pRender);
	void Render();

	//void Render(Mesh* mesh, Material* material, matrix);

private:
	ID3D12RootSignature* m_RootSignature = nullptr;
	ID3D12PipelineState* m_PSO = nullptr;
public:
	int m_Type;

protected:
	std::vector<D3D12_INPUT_ELEMENT_DESC> m_InputLayout;
	ID3DBlob* m_vsByteCode = nullptr;
	ID3DBlob* m_psByteCode = nullptr;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc;
	int m_count = 0;

	// 
	GCRender* m_pRender;
};

