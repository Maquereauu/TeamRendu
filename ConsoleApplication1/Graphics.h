#pragma once

//#include "d3dUtil.h"
#include <vector>

//class Texture2;
class Mesh;
class Shader;
class ShaderColor;
class ShaderTexture;
class Material;


class Graphics
{
public:
	Graphics();

	/*void Initialize();*/

	// Soon Mesh

	// Principal Object Creation
	Shader* CreateShader(int type);
	Material* CreateMaterial();
	Mesh* CreateMesh();

	// Resources Manager
	std::vector<Shader*> GetShaders();
	std::vector<Material*> GetMaterials();
	std::vector<Mesh*> GetMeshes();
	// *
	
	// Render instance contain Window
	/*Render* m_pRender;*/

	//void CreateTexture();
	//std::vector<Mesh*> GetMeshes();
private:
	std::vector<Shader*> m_vShader;
	std::vector<Material*> m_vMaterial;
	std::vector<Mesh*> m_vMesh;
};

