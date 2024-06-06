#pragma once


#include "PrimitiveFactory.h"
#include "ModelParserObj.h"

class PrimitiveFactory;

class ModelParserObj;

class GCMesh;

#include "Render.h"

struct GCVERTEX
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT4 Color;
};

struct GCVERTEXTEXTURE
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT2 TexC; // Normal
};

class GCGeometry {
public:
	virtual ~GCGeometry() {}


	std::vector<std::uint16_t> indices;
	std::size_t vertexNumber;
	std::size_t indiceNumber;

	SubmeshGeometry submesh;
	std::unique_ptr<MeshGeometry> boxGeo;
};

class GCGeometryColor : public GCGeometry {
public:

	std::vector<GCVERTEX> vertices;

};

class GCGeometryTexture : public GCGeometry {
public:
	std::vector<GCVERTEXTEXTURE> vertices;
};



class GCMesh
{
public: 
	GCMesh();
	~GCMesh();

	void Initialize(GCRender* pRender);
	void Render();

	//void UploadWorldViewProjData();

	void UploadGeometryDataColor();
	void UploadGeometryDataTexture();

	void CreatePrimitiveGeometry(int id);
	void CreateObjGeometry(std::wstring obj, bool isTextured = false);

	//DirectX::XMFLOAT4X4 mWorld = MathHelper::Identity4x4();
	//DirectX::XMFLOAT4X4 mView = MathHelper::Identity4x4();
	//DirectX::XMFLOAT4X4 mProj = MathHelper::Identity4x4();
	//std::unique_ptr<UploadBuffer<ObjectConstants>> m_Buffer;

	// Primitive
	void CreateBoxGeometryColor(int id);
	void CreateBoxGeometryTexture(int id);
	//// Parse
	void CreateObjGeometryColor(std::wstring obj);
	void CreateObjGeometryTexture(std::wstring obj);

	GCGeometry* GetBoxGeometry();
	//GCGeometry* GetGeometryTexture();



private:

	GCRender* m_pRender;

	GCGeometry* m_pGeometry;
};

