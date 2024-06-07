#include "Material.h"
#include "Texture.h"
#include "Graphics.h"

GCMaterial::GCMaterial() {
	m_pTexture = nullptr;
	m_color = DirectX::XMFLOAT4(0, 0, 0, 1);
}

GCMaterial::~GCMaterial() {
	delete(m_pTexture);
}

void GCMaterial::Initialize() {

}
	

void GCMaterial::AddTexture(std::string name, GCGraphics* pGraphics) {
	m_pTexture = new GCTexture();
	m_pTexture->Initialize(name, pGraphics);
	pGraphics->m_vTextures.push_back(m_pTexture);
	pGraphics->m_textureId++;
}






