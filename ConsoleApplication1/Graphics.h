#pragma once

#include <vector>
#include <string>

class Window;
class GCRender;
//class Texture2;
//class Material;
class GCTexture;

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
	GCShader* CreateShader(int type, std::wstring hlsl);
	GCMaterial* CreateMaterial();
	GCMesh* CreateMesh();
	GCTexture* CreateTexture(std::string fileName);
	// Resources Manager
	std::vector<GCShader*> GetShaders();
	std::vector<GCMaterial*> GetMaterials();
	std::vector<GCMesh*> GetMeshes();
	std::vector<GCTexture*> GetTextures();
	void AddTex(GCTexture* tex);
	// *
	
	// Render instance contain Window
	GCRender* m_pRender;

	//void CreateTexture();
	//std::vector<Mesh*> GetMeshes();

private:

	std::vector<GCTexture*> m_vTexture;
	std::vector<GCShader*> m_vShader;
	std::vector<GCMaterial*> m_vMaterial;
	std::vector<GCMesh*> m_vMesh;


};

