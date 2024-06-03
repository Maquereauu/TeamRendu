#pragma once
#include <vector>
class Texture2;
class Mesh;
class Shader;
class Graphics
{
private:
	std::vector<Mesh*> mMeshes;
public:
	Graphics();
	void CreateMesh(int type);
	void CreateShader();
	//void CreateTexture();
	//std::vector<Mesh*> GetMeshes();
public:
	std::vector<Texture2*> mTextures;
	std::vector<Shader*> mShaders;
};

