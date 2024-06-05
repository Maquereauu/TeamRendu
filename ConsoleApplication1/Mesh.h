#pragma once


#include "PrimitiveFactory.h"
#include "ModelParserObj.h"

class PrimitiveFactory;

class ModelParserObj;

class GCMesh;

#include "Render.h"

struct GCOBJECTCONSTANTS {
	DirectX::XMFLOAT4X4 WorldViewProj;
};

struct GCMESHDATA {

	// Vertex buffer
	ID3D12Resource* m_vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;

	// Index buffer
	ID3D12Resource* m_indexBuffer;
	D3D12_INDEX_BUFFER_VIEW m_indexBufferView;
};

class GCMesh
{
public: 
	GCMesh();
	~GCMesh();

	void Initialize(GCRender* pRender);
	void Render();

	void UploadWorldViewProjData();

	GCOBJECTCONSTANTS* m_pWorldViewProjData;


	void CreateGeometry();
	//void CreateObjGeometry();
	//GCGEOMETRY* GetBoxGeometry();
	//GCGEOMETRYTEXTURE* GetGeometryTexture();

	GCGEOMETRY* GetGeometry() const { return m_pGeometry; }
	GCMESHDATA* GetMeshData() const { return m_pMeshData; }

	// Constant buffer
	ID3D12Resource* m_pConstantBuffer; 
	UINT8* m_pMappedConstantBuffer;

private:

	//GCGEOMETRYTEXTURE* m_GeoTextures;
	GCGEOMETRY* m_pGeometry;
	GCMESHDATA* m_pMeshData;

	GCRender* m_pRender;


};

