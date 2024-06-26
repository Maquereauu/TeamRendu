#include "Graphics.h"
//#include "Global.h"
#include "Mesh.h"

//#include "Texture2.h"
#include "Render.h"


#include "Shader.h"
#include "ShaderColor.h"
#include "ShaderTexture.h"
#include "Texture.h"
#include "Material.h"
//#include "Texture2.h"
GCGraphics::GCGraphics() {
	/*m_pRender = nullptr;*/
}

void GCGraphics::Initialize() {
	m_pRender = new GCRender();
	m_pRender->Initialize(this);
}

//void Graphics::Initialize() {
//	// Init Debug Console
//	//AllocConsole();
//	//FILE* fp;
//	//freopen_s(&fp, "CONOUT$", "w", stdout);
//	//freopen_s(&fp, "CONIN$", "r", stdin);
//	//std::cout << "Console initialized!" << std::endl;
//
//	// Init render
//
//
//
//}

GCMesh* GCGraphics::CreateMesh() {
	GCMesh* mesh = new GCMesh();
	mesh->Initialize(m_pRender);
	m_vMeshes.push_back(mesh);
	//m_meshId++;
	return mesh;
}

//GCTexture* GCGraphics::CreateTexture(std::string fileName) {
//	GCTexture* texture = new GCTexture();
//	texture->Initialize(fileName, m_pRender);
//	m_vTexture.push_back(texture);
//	return texture;
//}


GCShader* GCGraphics::CreateShader(int type, std::wstring hlsl) {
    GCShader* shader = nullptr; // Initialisation de la variable shader � nullptr

    switch (type) {
    case 0:
    {
        shader = new GCShaderColor();
        shader->m_Type = 0;
        shader->Initialize(m_pRender, hlsl);
        m_vShaders.push_back(shader);
        m_shaderId++;
        return shader;
        break;
    }
    case 1:
    {
        shader = new GCShaderTexture();
        shader->m_Type = 1;
        shader->Initialize(m_pRender, hlsl);
        m_vShaders.push_back(shader);
        m_shaderId++;
        return shader;
        break;
    }
    }

    GCShader* parentShader = dynamic_cast<GCShader*>(shader);
    if (parentShader != nullptr) {
        return parentShader;
    }
    else {
        return nullptr;
    }
}

GCMaterial* GCGraphics::CreateMaterial() {
	GCMaterial* material = new GCMaterial();
	material->Initialize();
	m_vMaterials.push_back(material);
	m_materialId++;
	return material;
}

std::vector<GCShader*> GCGraphics::GetShaders() {
	return m_vShaders;
}

std::vector<GCMaterial*> GCGraphics::GetMaterials() {
	return m_vMaterials;
}

std::vector<GCMesh*> GCGraphics::GetMeshes() {
	return m_vMeshes;
}

std::vector<GCTexture*> GCGraphics::GetTextures() {
	return m_vTextures;
}


//void GCGraphics::AddTex(GCTexture* tex) {
//	m_vTexture.push_back(tex);
//}
//

//void Graphics::CreateTexture() {
//	mTextures.push_back(new Texture2());
//}

//std::vector<Mesh*> Graphics::GetMeshes()
//{
//	return mMeshes;
//}