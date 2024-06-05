#pragma once


#include "PrimitiveFactory.h"

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
	GCGEOMETRY* m_boxGeometry;

private:
	GCRender* m_pRender;
};

