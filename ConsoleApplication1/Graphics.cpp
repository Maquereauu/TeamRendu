#include "Graphics.h"
//#include "Global.h"
#include "Mesh.h"

//#include "Texture2.h"
#include "Render.h"


#include "Shader.h"
#include "ShaderColor.h"
#include "ShaderTexture.h"
#include "Material.h"

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
	m_vMesh.push_back(mesh);
	return mesh;
}


GCShader* GCGraphics::CreateShader(int type) {
	GCShader* shader;
	switch (type) {
	case 0:
	{
		shader = new GCShaderColor();
		shader->Initialize(m_pRender);
		m_vShader.push_back(shader);
		return shader;
		break;
	}
	case 1:
	{
		shader = new GCShaderTexture();
		shader->Initialize(m_pRender);
		m_vShader.push_back(shader);
		return shader;
		break;
	}
	}
	shader = new GCShader();
	m_vShader.push_back(shader);
	return shader;
}

GCMaterial* GCGraphics::CreateMaterial() {
	GCMaterial* material = new GCMaterial();
	m_vMaterial.push_back(material);
	return material;
}

std::vector<GCShader*> GCGraphics::GetShaders() {
	return m_vShader;
}

std::vector<GCMaterial*> GCGraphics::GetMaterials() {
	return m_vMaterial;
}

std::vector<GCMesh*> GCGraphics::GetMeshes() {
	return m_vMesh;
}


//void Graphics::CreateTexture() {
//	mTextures.push_back(new Texture2());
//}

//std::vector<Mesh*> Graphics::GetMeshes()
//{
//	return mMeshes;
//}