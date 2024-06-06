#include "Mesh.h"
#include "Render.h"
#include "d3dUtil.h"



GCMesh::GCMesh() {
}

GCMesh::~GCMesh() {

}

void GCMesh::Initialize(GCRender* pRender) {
	m_pRender = pRender;
	//CreateBoxGeometryColor();
    CreateBoxGeometryTexture();
    //CreateObjGeometryTexture();
    //CreateObjGeometryColor();
}

void GCMesh::UploadGeometryDataColor() {
    GCGeometryColor* boxGeometryColor = dynamic_cast<GCGeometryColor*>(m_pGeometry);
    if (!boxGeometryColor) {
        return;
    }

    const auto& vertices = boxGeometryColor->vertices;

    const UINT vbByteSize = static_cast<UINT>(vertices.size() * sizeof(GCVERTEX));
    const UINT ibByteSize = static_cast<UINT>(m_pGeometry->indices.size() * sizeof(std::uint16_t));

    boxGeometryColor->boxGeo = std::make_unique<MeshGeometry>();
    boxGeometryColor->boxGeo->Name = "boxGeo";

    ThrowIfFailed(D3DCreateBlob(vbByteSize, &boxGeometryColor->boxGeo->VertexBufferCPU));

    CopyMemory(boxGeometryColor->boxGeo->VertexBufferCPU->GetBufferPointer(), vertices.data(), vbByteSize);

    ThrowIfFailed(D3DCreateBlob(ibByteSize, &boxGeometryColor->boxGeo->IndexBufferCPU));

    CopyMemory(boxGeometryColor->boxGeo->IndexBufferCPU->GetBufferPointer(), m_pGeometry->indices.data(), ibByteSize);


    boxGeometryColor->boxGeo->VertexBufferGPU = d3dUtil::CreateDefaultBuffer(m_pRender->Getmd3dDevice(),
        m_pRender->GetCommandList(), vertices.data(), vbByteSize, boxGeometryColor->boxGeo->VertexBufferUploader);
    boxGeometryColor->boxGeo->IndexBufferGPU = d3dUtil::CreateDefaultBuffer(m_pRender->Getmd3dDevice(),
        m_pRender->GetCommandList(), m_pGeometry->indices.data(), ibByteSize, boxGeometryColor->boxGeo->IndexBufferUploader);

    boxGeometryColor->boxGeo->VertexByteStride = sizeof(GCVERTEX);
    boxGeometryColor->boxGeo->VertexBufferByteSize = vbByteSize;
    boxGeometryColor->boxGeo->IndexFormat = DXGI_FORMAT_R16_UINT;
    boxGeometryColor->boxGeo->IndexBufferByteSize = ibByteSize;

    // Initialize submesh
    SubmeshGeometry submesh;
    submesh.IndexCount = static_cast<UINT>(m_pGeometry->indices.size());
    submesh.StartIndexLocation = 0;
    submesh.BaseVertexLocation = 0;

    // Assign submesh to box geometry
    boxGeometryColor->submesh = submesh;

}


void GCMesh::UploadGeometryDataTexture() {
    GCGeometryTexture* boxGeometryColor = dynamic_cast<GCGeometryTexture*>(m_pGeometry);
    if (!boxGeometryColor) {
        return;
    }

    const auto& vertices = boxGeometryColor->vertices;

    const UINT vbByteSize = static_cast<UINT>(vertices.size() * sizeof(GCVERTEXTEXTURE));
    const UINT ibByteSize = static_cast<UINT>(m_pGeometry->indices.size() * sizeof(std::uint16_t));

    boxGeometryColor->boxGeo = std::make_unique<MeshGeometry>();
    boxGeometryColor->boxGeo->Name = "boxGeo";

    ThrowIfFailed(D3DCreateBlob(vbByteSize, &boxGeometryColor->boxGeo->VertexBufferCPU));

    CopyMemory(boxGeometryColor->boxGeo->VertexBufferCPU->GetBufferPointer(), vertices.data(), vbByteSize);

    ThrowIfFailed(D3DCreateBlob(ibByteSize, &boxGeometryColor->boxGeo->IndexBufferCPU));

    CopyMemory(boxGeometryColor->boxGeo->IndexBufferCPU->GetBufferPointer(), m_pGeometry->indices.data(), ibByteSize);


    boxGeometryColor->boxGeo->VertexBufferGPU = d3dUtil::CreateDefaultBuffer(m_pRender->Getmd3dDevice(),
        m_pRender->GetCommandList(), vertices.data(), vbByteSize, boxGeometryColor->boxGeo->VertexBufferUploader);
    boxGeometryColor->boxGeo->IndexBufferGPU = d3dUtil::CreateDefaultBuffer(m_pRender->Getmd3dDevice(),
        m_pRender->GetCommandList(), m_pGeometry->indices.data(), ibByteSize, boxGeometryColor->boxGeo->IndexBufferUploader);

    boxGeometryColor->boxGeo->VertexByteStride = sizeof(GCVERTEXTEXTURE);
    boxGeometryColor->boxGeo->VertexBufferByteSize = vbByteSize;
    boxGeometryColor->boxGeo->IndexFormat = DXGI_FORMAT_R16_UINT;
    boxGeometryColor->boxGeo->IndexBufferByteSize = ibByteSize;

    // Initialize submesh
    SubmeshGeometry submesh;
    submesh.IndexCount = static_cast<UINT>(m_pGeometry->indices.size());
    submesh.StartIndexLocation = 0;
    submesh.BaseVertexLocation = 0;

    // Assign submesh to box geometry
    boxGeometryColor->submesh = submesh;
}


void GCMesh::CreateBoxGeometryColor()
{
    PrimitiveFactory* factory = new PrimitiveFactory();
    factory->Initialize(0, m_pRender);
    m_pGeometry = factory->BuildBoxGeometryColor();

    UploadGeometryDataColor();

    m_pGeometry->boxGeo->DrawArgs["box"] = m_pGeometry->submesh;
}

void GCMesh::CreateBoxGeometryTexture()
{
	PrimitiveFactory* factory = new PrimitiveFactory();
	factory->Initialize(0, m_pRender);

	m_pGeometry = factory->BuildBoxGeometryTexture();

    UploadGeometryDataTexture();

	m_pGeometry->boxGeo->DrawArgs["box"] = m_pGeometry->submesh;


}
//
void GCMesh::CreateObjGeometryColor()
{
	ModelParserObj* objParser = new ModelParserObj();
	objParser->Initialize(m_pRender, "cubeNoUv.obj");
	objParser->ParseObj();
	m_pGeometry = objParser->BuildObjColor();

    UploadGeometryDataColor();

    m_pGeometry->boxGeo->DrawArgs["box"] = m_pGeometry->submesh;


}

void GCMesh::CreateObjGeometryTexture()
{
	ModelParserObj* objParser = new ModelParserObj();
	objParser->Initialize(m_pRender, "cube.obj");
	objParser->ParseObj();
    m_pGeometry = objParser->BuildObjTexture();

    UploadGeometryDataTexture();

    m_pGeometry->boxGeo->DrawArgs["box"] = m_pGeometry->submesh;
}



GCGeometry* GCMesh::GetBoxGeometry()
{
	return m_pGeometry;
}

//GCGEOMETRYTEXTURE* GCMesh::GetGeometryTexture()
//{
//	return m_boxGeometryTexture;
//}




void GCMesh::Render() {




	//m_pRender->GetCommandList()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//D3D12_VERTEX_BUFFER_VIEW vertexBufferView = m_boxGeometry->boxGeo->VertexBufferView();
	//m_pRender->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView);
	//D3D12_INDEX_BUFFER_VIEW indexBufferView = m_boxGeometry->boxGeo->IndexBufferView();
	//m_pRender->GetCommandList()->IASetIndexBuffer(&indexBufferView);

	//OutputDebugString(L"Set index buffer");

	//DirectX::XMFLOAT3 pos1 = { 0.f, 0.f, 0.f };
	//DirectX::XMVECTOR pos = DirectX::XMVectorSet(10, 10, 10, 1.0f);
	//DirectX::XMVECTOR target = DirectX::XMVectorZero();
	//DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	//DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(pos, target, up);
	//DirectX::XMFLOAT4X4 MId = MathHelper::Identity4x4();
	//DirectX::XMMATRIX world = DirectX::XMLoadFloat4x4(&MId);
	//DirectX::XMMATRIX proj = DirectX::XMLoadFloat4x4(&mProj);
	//DirectX::XMMATRIX worldViewProj = world * view * proj;

	//m_Buffer = std::make_unique<UploadBuffer<ObjectConstants>>(m_pRender->Getmd3dDevice(), 1, true);
	//ObjectConstants objConstants;
	//XMStoreFloat4x4(&objConstants.WorldViewProj, XMMatrixTranspose(worldViewProj));
	//m_Buffer->CopyData(0, objConstants);
	//m_pRender->GetCommandList()->SetGraphicsRootConstantBufferView(0, m_Buffer->Resource()->GetGPUVirtualAddress());

	//m_pRender->GetCommandList()->DrawIndexedInstanced(m_boxGeometry->boxGeo->DrawArgs["box"].IndexCount, 1, 0, 0, 0);



}




