#include "Material.h"
#include "Texture.h"

GCMaterial::GCMaterial() {
	m_pTexture = nullptr;
	m_color = DirectX::XMFLOAT4(0, 0, 0, 1);
}

GCMaterial::~GCMaterial() {
	delete(m_pTexture);
}

void GCMaterial::Initialize() {

}
	


void GCMaterial::SetColor(DirectX::XMFLOAT4 color) {
	m_color = color;
}


void GCMaterial::AddTexture(std::string name, GCRender* pRender) {
	m_pTexture = new GCTexture();
	m_pTexture->Initialize(pRender,name);
}






