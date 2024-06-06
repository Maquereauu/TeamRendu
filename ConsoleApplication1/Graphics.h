#pragma once

//#include "d3dUtil.h"
#include <vector>

//class Texture2;
class Mesh;
class Shader;
class ShaderColor;
class ShaderTexture;
//class Material;
class GCTexture;
class GCMaterial;

class Graphics
{
public:
	Graphics();

	/*void Initialize();*/

	// Soon Mesh

	// Principal Object Creation
	Shader* CreateShader(int type);
	GCMaterial* CreateMaterial();
	Mesh* CreateMesh();
	GCTexture* CreateTexture();

	// Resources Manager
	std::vector<Shader*> GetShaders();
	std::vector<GCMaterial*> GetMaterials();
	std::vector<Mesh*> GetMeshes();
	std::vector<GCTexture*> GetTextures();
	// *
	
	// Render instance contain Window
	/*Render* m_pRender;*/

	//void CreateTexture();
	//std::vector<Mesh*> GetMeshes();
	std::vector<GCTexture*> m_vTexture;
private:
	std::vector<Shader*> m_vShader;
	std::vector<GCMaterial*> m_vMaterial;
	std::vector<Mesh*> m_vMesh;
};

