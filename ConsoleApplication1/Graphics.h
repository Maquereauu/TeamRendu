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

	
	// Render instance contain Window
	GCRender* m_pRender;


	int m_meshId = 0;
	int m_shaderId = 0;
	int m_materialId = 0;
	int m_textureId = 0;

	std::vector<GCTexture*> m_vTextures;
	std::vector<GCShader*> m_vShaders;
	std::vector<GCMaterial*> m_vMaterials;
	std::vector<GCMesh*> m_vMeshes;

private:






};

