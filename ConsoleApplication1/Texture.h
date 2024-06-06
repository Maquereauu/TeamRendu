#pragma once

#include "d3dUtil.h"

class GCRender;

class GCTexture
{
public:
	GCTexture();
	~GCTexture();

	void Initialize(GCRender* pRender, std::string fileName);

	void Render();
	CD3DX12_GPU_DESCRIPTOR_HANDLE m_HDescriptorGPU;
private:

	std::string m_namePath;
	// 
	int SrvHeapIndex;



	Microsoft::WRL::ComPtr<ID3D12Resource> m_textureBuffer;
	Microsoft::WRL::ComPtr<ID3D12Resource> m_uploadTexture;
	Microsoft::WRL::ComPtr <ID3D12Resource> m_resource = nullptr;
	Microsoft::WRL::ComPtr <ID3D12Resource> m_uploadHeap = nullptr;
	UINT m_haepDescSize;
	UINT m_CbvSrvUavDescriptorSize;
	// Texture offset for GPU ? 

	CD3DX12_GPU_DESCRIPTOR_HANDLE m_textureAdress;
};