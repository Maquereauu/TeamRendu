#include "Graphics.h"
//#include "Global.h"
#include "Mesh.h"
#include "Shader.h"
#include "ShaderColor.h"
#include "ShaderTexture.h"
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

Material* Graphics::CreateMaterial() {
	Material* material = new Material();
	m_vMaterial.push_back(material);
	return material;
}

std::vector<Shader*> Graphics::GetShaders() {
	return m_vShader;
}

std::vector<Material*> Graphics::GetMaterials() {
	return m_vMaterial;
}

std::vector<Mesh*> Graphics::GetMeshes() {
	return m_vMesh;
}


//void Graphics::CreateTexture() {
//	mTextures.push_back(new Texture2());
//}

//std::vector<Mesh*> Graphics::GetMeshes()
//{
//	return mMeshes;
//}