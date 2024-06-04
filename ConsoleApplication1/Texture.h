#pragma once

#include "d3dUtil.h"

class GCRender;


class GCTexture
{
public:
	GCTexture();
	~GCTexture();

	void Initialize(GCRender* pRender);

	void Render();

private:

	std::string m_namePath;
	// 
	int SrvHeapIndex;



	Microsoft::WRL::ComPtr<ID3D12Resource> m_textureBuffer;
	Microsoft::WRL::ComPtr<ID3D12Resource> m_uploadTexture;

	// Texture offset for GPU ? 

	CD3DX12_GPU_DESCRIPTOR_HANDLE m_textureAdress;
};