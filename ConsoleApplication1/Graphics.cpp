#include "Graphics.h"
//#include "Global.h"
#include "Mesh.h"
#include "Shader.h"
#include "ShaderColor.h"
#include "ShaderTexture.h"
//#include "Texture2.h"
#include "Render.h"




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
	m_vMesh.push_back(mesh);
	return mesh;
}


Shader* GCGraphics::CreateShader(int type) {
	Shader* shader;
	switch (type) {
	case 0:
	{
		shader = new ShaderColor();
		shader->Initialize(m_pRender);
		m_vShader.push_back(shader);
		return shader;
		break;
	}
	case 1:
	{
		shader = new ShaderTexture();
		shader->Initialize(m_pRender);
		m_vShader.push_back(shader);
		return shader;
		break;
	}
	}
	shader = new Shader();
	m_vShader.push_back(shader);
	return shader;
}

Material* GCGraphics::CreateMaterial() {
	Material* material = new Material();
	m_vMaterial.push_back(material);
	return material;
}

std::vector<Shader*> GCGraphics::GetShaders() {
	return m_vShader;
}

std::vector<Material*> GCGraphics::GetMaterials() {
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