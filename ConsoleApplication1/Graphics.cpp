#include "Graphics.h"
//#include "Global.h"
#include "Mesh.h"
#include "Shader.h"
#include "ShaderColor.h"
#include "ShaderTexture.h"
#include "Texture.h"
#include "Material.h"
//#include "Texture2.h"




Graphics::Graphics() {
	/*m_pRender = nullptr;*/
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

Mesh* Graphics::CreateMesh() {
	Mesh* mesh = new Mesh();
	m_vMesh.push_back(mesh);
	return mesh;
}

GCTexture* Graphics::CreateTexture() {
	GCTexture* texture = new GCTexture();
	m_vTexture.push_back(texture);
	return texture;
}


Shader* Graphics::CreateShader(int type) {
	Shader* shader;
	switch (type) {
	case 0:
	{
		shader = new ShaderColor();
		m_vShader.push_back(shader);
		return shader;
		break;
	}
	case 1:
	{
		shader = new ShaderTexture();
		m_vShader.push_back(shader);
		return shader;
		break;
	}
	}
	shader = new Shader();
	m_vShader.push_back(shader);
	return shader;
}

GCMaterial* Graphics::CreateMaterial() {
	GCMaterial* material = new GCMaterial();
	m_vMaterial.push_back(material);
	return material;
}

std::vector<Shader*> Graphics::GetShaders() {
	return m_vShader;
}

std::vector<GCMaterial*> Graphics::GetMaterials() {
	return m_vMaterial;
}

std::vector<Mesh*> Graphics::GetMeshes() {
	return m_vMesh;
}

std::vector<GCTexture*> Graphics::GetTextures() {
	return m_vTexture;
}


//void Graphics::CreateTexture() {
//	mTextures.push_back(new Texture2());
//}

//std::vector<Mesh*> Graphics::GetMeshes()
//{
//	return mMeshes;
//}