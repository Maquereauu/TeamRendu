#pragma once

#include "d3dUtil.h"

class GCTexture;
class GCRender;

class GCMaterial
{
public:
	GCMaterial();
	~GCMaterial();
	void Initialize();

	void SetColor(DirectX::XMFLOAT4 color);
	void AddTexture(std::string name, GCRender* pRender);





	GCTexture* m_pTexture;
	DirectX::XMFLOAT4 m_color;

};

