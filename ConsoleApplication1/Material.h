#pragma once

#include "d3dUtil.h"

class GCTexture;

class GCMaterial
{
public:
	GCMaterial();
	~GCMaterial();
	void Initialize(Texture* pTexture);

	void SetColor(DirectX::XMFLOAT4 color);

	void AddTexture(std::string name);





	GCTexture* m_pTexture;
	DirectX::XMFLOAT4 m_color;

};

