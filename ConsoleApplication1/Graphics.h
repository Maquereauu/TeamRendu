#pragma once

//#include "d3dUtil.h"
#include <vector>

//class Texture2;
class GCMesh;
class Shader;
class ShaderColor;
class ShaderTexture;
class Material;
class Window;
class GCRender;


class GCGraphics
{
public:
	GCGraphics();

	void Initialize();

	// Soon Mesh

	// Principal Object Creation
	Shader* CreateShader(int type);
	Material* CreateMaterial();
	GCMesh* CreateMesh();

	// Resources Manager
	std::vector<Shader*> GetShaders();
	std::vector<Material*> GetMaterials();
	std::vector<GCMesh*> GetMeshes();
	// *
	
	// Render instance contain Window
	GCRender* m_pRender;

	//void CreateTexture();
	//std::vector<Mesh*> GetMeshes();
private:
	std::vector<Shader*> m_vShader;
	std::vector<Material*> m_vMaterial;
	std::vector<GCMesh*> m_vMesh;


};

