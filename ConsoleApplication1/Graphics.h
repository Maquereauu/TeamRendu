#pragma once

#include "d3dUtil.h"

class Texture2;
class Mesh;
class Shader;
class Render;



class Graphics
{
public:
	Graphics();

	void Initialize();

	// Soon Mesh
	void CreateMesh(int type);

	// Principal Object Creation
	Shader* CreateShader();
	Material* CreateMaterial();
	// Mesh* CreateMesh();

	// Resources Manager
	std::vector<Shader*> GetAllShader();
	std::vector<Material*> GetAllMaterial();
	// *

	// Render instance contain Window
	Render* m_pRender;

	//void CreateTexture();
	//std::vector<Mesh*> GetMeshes();
private:
	std::vector<Shader*> m_vShader;
	std::vector<Material*> m_vMaterial;
	//	std::vector<Mesh*> m_vMesh;
};

