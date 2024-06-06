#include "Mesh.h"
#include "Render.h"
#include "d3dUtil.h"



GCMesh::GCMesh() {
}

GCMesh::~GCMesh() {

}

void GCMesh::Initialize(GCRender* pRender) {
	m_pRender = pRender;
	CreateObjGeometryWithTextures();
}

void GCMesh::CreateBoxGeometry() 
{
	PrimitiveFactory* factory = new PrimitiveFactory();
	factory->Initialize(0, m_pRender);
	m_boxGeometry = factory->GetGeometry();
	m_boxGeometry->boxGeo->DrawArgs["box"] = m_boxGeometry->submesh;
}

void GCMesh::CreateObjGeometryWithTextures()
{
	ModelParserObj* objParser = new ModelParserObj();
	objParser->Initialize(m_pRender, "cube.obj");
	objParser->ParseObj();
	m_boxGeometryTex = objParser->BuildObjWithTextures();
	m_boxGeometryTex->boxGeo->DrawArgs["box"] = m_boxGeometryTex->submesh;
}

void GCMesh::CreateObjGeometry()
{
	ModelParserObj* objParser = new ModelParserObj();
	objParser->Initialize(m_pRender, "cubeNoUv.obj");
	objParser->ParseObj();
	m_boxGeometry = objParser->BuildObj();
	m_boxGeometry->boxGeo->DrawArgs["box"] = m_boxGeometry->submesh;
}

GCGEOMETRY* GCMesh::GetBoxGeometry()
{
	return m_boxGeometry;
}

GCGEOMETRYTEXTURE* GCMesh::GetGeometryTexture()
{
	return m_boxGeometryTex;
}




void GCMesh::Render() {




	m_pRender->GetCommandList()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView = m_boxGeometry->boxGeo->VertexBufferView();
	m_pRender->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView);
	D3D12_INDEX_BUFFER_VIEW indexBufferView = m_boxGeometry->boxGeo->IndexBufferView();
	m_pRender->GetCommandList()->IASetIndexBuffer(&indexBufferView);

	OutputDebugString(L"Set index buffer");

	DirectX::XMFLOAT3 pos1 = { 0.f, 0.f, 0.f };
	DirectX::XMVECTOR pos = DirectX::XMVectorSet(10, 10, 10, 1.0f);
	DirectX::XMVECTOR target = DirectX::XMVectorZero();
	DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(pos, target, up);
	DirectX::XMFLOAT4X4 MId = MathHelper::Identity4x4();
	DirectX::XMMATRIX world = DirectX::XMLoadFloat4x4(&MId);
	DirectX::XMMATRIX proj = DirectX::XMLoadFloat4x4(&mProj);
	DirectX::XMMATRIX worldViewProj = world * view * proj;

	m_Buffer = std::make_unique<UploadBuffer<ObjectConstants>>(m_pRender->Getmd3dDevice(), 1, true);
	ObjectConstants objConstants;
	XMStoreFloat4x4(&objConstants.WorldViewProj, XMMatrixTranspose(worldViewProj));
	m_Buffer->CopyData(0, objConstants);
	m_pRender->GetCommandList()->SetGraphicsRootConstantBufferView(0, m_Buffer->Resource()->GetGPUVirtualAddress());

	m_pRender->GetCommandList()->DrawIndexedInstanced(m_boxGeometry->boxGeo->DrawArgs["box"].IndexCount, 1, 0, 0, 0);



}


void GCMesh::CreateBoxGeometryTex()
{
	PrimitiveFactory* factory = new PrimitiveFactory();
	factory->Initialize(0,m_pRender);
	m_boxGeometryTex = factory->GetGeometryTexture();
	m_boxGeometryTex->boxGeo->DrawArgs["box"] = m_boxGeometryTex->submesh;


}

