#include "Graphics.h"
#include "Global.h"
#include "Render.h"
#include "Mesh.h"
#include "Shader.h"

//#include "Texture2.h"




Graphics::Graphics() {
	m_pRender = nullptr;



}

void Graphics::Initialize() {
	// Init Debug Console
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONIN$", "r", stdin);
	std::cout << "Console initialized!" << std::endl;

	// Init render



}

void Graphics::CreateMesh(int type) {
	//Mesh* mesh = new Mesh();
	//mesh->Initialize(type);
	//mMeshes.push_back(mesh);
}


//Shader* Graphics::CreateShader() {
//	/*mShaders.push_back(new Shader());*/
//}

//void Graphics::CreateTexture() {
//	mTextures.push_back(new Texture2());
//}

//std::vector<Mesh*> Graphics::GetMeshes()
//{
//	return mMeshes;
//}