#pragma once

#include <vector>


class Window;
class GCRender;

class GCMesh;
class GCShader;
class GCShaderColor;
class GCShaderTexture;
class GCMaterial;



class GCGraphics
{
public:
	GCGraphics();

	void Initialize();


	// Principal Object Creation
	GCShader* CreateShader(int type);
	GCMaterial* CreateMaterial();
	GCMesh* CreateMesh();

	// Resources Manager
	std::vector<GCShader*> GetShaders();
	std::vector<GCMaterial*> GetMaterials();
	std::vector<GCMesh*> GetMeshes();
	// *
	
	// Render instance contain Window
	GCRender* m_pRender;

	//void CreateTexture();
	//std::vector<Mesh*> GetMeshes();
private:
	std::vector<GCShader*> m_vShader;
	std::vector<GCMaterial*> m_vMaterial;
	std::vector<GCMesh*> m_vMesh;


};

