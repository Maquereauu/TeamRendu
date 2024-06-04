#pragma once

#include "d3dUtil.h"

class Render;


class GCTexture
{
public:
	GCTexture();
	~GCTexture();
	void Initialize();
	void Render();

private:

	// 
	int m_offset;
	std::string m_namePath;


	Microsoft::WRL::ComPtr<ID3D12Resource> m_textureBuffer;
	Microsoft::WRL::ComPtr<ID3D12Resource> m_uploadTexture;

	// Texture offset for GPU ? 

	CD3DX12_GPU_DESCRIPTOR_HANDLE* m_textureAdress;
};