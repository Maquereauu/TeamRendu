#pragma once


#include "PrimitiveFactory.h"
#include "ModelParserObj.h"

class PrimitiveFactory;

class ModelParserObj;

class GCMesh;

#include "Render.h"




class GCMesh
{
public: 
	GCMesh();
	~GCMesh();

	void Initialize(GCRender* pRender);
	void Render();

	void UploadWorldViewProjData();


	DirectX::XMFLOAT4X4 mWorld = MathHelper::Identity4x4();
	DirectX::XMFLOAT4X4 mView = MathHelper::Identity4x4();
	DirectX::XMFLOAT4X4 mProj = MathHelper::Identity4x4();
	std::unique_ptr<UploadBuffer<ObjectConstants>> m_Buffer;

	void CreateBoxGeometry();
	void CreateObjGeometry();
	void CreateObjGeometryWithTextures();
	GCGEOMETRY* GetBoxGeometry();
	GCGEOMETRYTEXTURE* GetGeometryTexture();
	void CreateBoxGeometryTex();
	GCGEOMETRYTEXTURE* m_boxGeometryTex;

private:

	GCRender* m_pRender;
	GCGEOMETRY* m_boxGeometry;
};

