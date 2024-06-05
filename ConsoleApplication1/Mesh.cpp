#include "Mesh.h"
#include "Render.h"
#include "d3dUtil.h"

#include "Macros.h"

GCMesh::GCMesh() {
}

GCMesh::~GCMesh() {

}

void GCMesh::Initialize(GCRender* pRender) {
	m_pRender = pRender;
	CreateGeometry();

    // Allocation de mémoire pour les données des constantes de l'objet
    m_pWorldViewProjData = new GCOBJECTCONSTANTS();

    DirectX::XMFLOAT4X4 mWorld = MathHelper::Identity4x4();
    DirectX::XMFLOAT4X4 mView = MathHelper::Identity4x4();
    DirectX::XMFLOAT4X4 mProj = MathHelper::Identity4x4();

    DirectX::XMFLOAT3 pos1 = { 0.f, 0.f, 0.f };
    DirectX::XMVECTOR pos = DirectX::XMVectorSet(10, 10, 10, 1.0f);
    DirectX::XMVECTOR target = DirectX::XMVectorZero();
    DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

    DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(pos, target, up);
    DirectX::XMFLOAT4X4 MId = MathHelper::Identity4x4();
    DirectX::XMMATRIX world = DirectX::XMLoadFloat4x4(&MId);
    DirectX::XMMATRIX proj = DirectX::XMLoadFloat4x4(&mProj);
    DirectX::XMMATRIX worldViewProj = world * view * proj;

    XMStoreFloat4x4(&m_pWorldViewProjData->WorldViewProj, XMMatrixTranspose(worldViewProj));


    /// Upload CBV DATA

    HRESULT hr;
    CD3DX12_HEAP_PROPERTIES cbHeapProps(D3D12_HEAP_TYPE_UPLOAD);
    CD3DX12_RESOURCE_DESC cbDesc = CD3DX12_RESOURCE_DESC::Buffer((sizeof(GCOBJECTCONSTANTS) + 255) & ~255);

    hr = m_pRender->Getmd3dDevice()->CreateCommittedResource(
        &cbHeapProps,
        D3D12_HEAP_FLAG_NONE,
        &cbDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&m_pConstantBuffer)
    );
    ASSERT_FAILED(hr);

    hr = m_pConstantBuffer->Map(0, nullptr, reinterpret_cast<void**>(&m_pMappedConstantBuffer));
    ASSERT_FAILED(hr);


    memcpy(m_pMappedConstantBuffer, reinterpret_cast<const void*>(&m_pWorldViewProjData->WorldViewProj), sizeof(GCOBJECTCONSTANTS));
    m_pConstantBuffer->Unmap(0, nullptr);
}

void CreateIndexBuffer(const std::vector<UINT>& indices, ID3D12Resource* buffer, D3D12_INDEX_BUFFER_VIEW& bufferView, GCRender* pRender) {
    const UINT size = static_cast<UINT>(indices.size() * sizeof(UINT));

    CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);
    CD3DX12_RESOURCE_DESC bufferDesc = CD3DX12_RESOURCE_DESC::Buffer(size);

    HRESULT hr = pRender->Getmd3dDevice()->CreateCommittedResource(
        &heapProps,
        D3D12_HEAP_FLAG_NONE,
        &bufferDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&buffer)
    );
    ASSERT_FAILED(hr);

    UINT8* pIndexDataBegin;
    CD3DX12_RANGE readRange(0, 0);

    hr = buffer->Map(0, &readRange, reinterpret_cast<void**>(&pIndexDataBegin));
    ASSERT_FAILED(hr);
    memcpy(pIndexDataBegin, indices.data(), size);
    buffer->Unmap(0, nullptr);

    bufferView.BufferLocation = buffer->GetGPUVirtualAddress();
    bufferView.Format = DXGI_FORMAT_R32_UINT;
    bufferView.SizeInBytes = size;
}


void CreateVertexBuffer(const std::vector<GCVERTEX>& vertices, ID3D12Resource* buffer, D3D12_VERTEX_BUFFER_VIEW& bufferView, GCRender* pRender) {
    const UINT size = static_cast<UINT>(vertices.size() * sizeof(GCVERTEX));

    CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);
    CD3DX12_RESOURCE_DESC bufferDesc = CD3DX12_RESOURCE_DESC::Buffer(size);

    HRESULT hr = pRender->Getmd3dDevice()->CreateCommittedResource(
        &heapProps,
        D3D12_HEAP_FLAG_NONE,
        &bufferDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&buffer)
    );
    ASSERT_FAILED(hr);

    UINT8* pVertexDataBegin;
    CD3DX12_RANGE readRange(0, 0);

    hr = buffer->Map(0, &readRange, reinterpret_cast<void**>(&pVertexDataBegin));
    ASSERT_FAILED(hr);
    memcpy(pVertexDataBegin, vertices.data(), size);

    buffer->Unmap(0, nullptr);

    bufferView.BufferLocation = buffer->GetGPUVirtualAddress();
    bufferView.StrideInBytes = sizeof(GCVERTEX);
    bufferView.SizeInBytes = size;
}

void GCMesh::CreateGeometry() 
{
	PrimitiveFactory* factory = new PrimitiveFactory();
	factory->Initialize(0, m_pRender);

    m_pGeometry = factory->BuildBoxGeometry();

    m_pMeshData = new GCMESHDATA();

    const UINT vertexBufferSize = sizeof(DirectX::XMFLOAT3) * m_pGeometry->vertexNumber;
    const UINT indexBufferSize = sizeof(UINT) * m_pGeometry->indiceNumber;
    const UINT stride = sizeof(DirectX::XMFLOAT3);

    CreateVertexBuffer(m_pGeometry->vertices, m_pMeshData->m_vertexBuffer, m_pMeshData->m_vertexBufferView, m_pRender);

    CreateIndexBuffer(m_pGeometry->indices, m_pMeshData->m_indexBuffer, m_pMeshData->m_indexBufferView, m_pRender);


	//m_boxGeometry = factory->GetGeometry();
	//m_boxGeometry->boxGeo->DrawArgs["box"] = m_boxGeometry->submesh;


}

//void GCMesh::CreateObjGeometry()
//{
//	ModelParserObj* objParser = new ModelParserObj();
//	objParser->ParseObj();
//	m_GeoTextures = objParser->BuildObj();
//	m_GeoTextures->boxGeo->DrawArgs["box"] = m_GeoTextures->submesh;
//}
//
//GCGEOMETRY* GCMesh::GetBoxGeometry()
//{
//	return m_boxGeometry;
//}
//
//GCGEOMETRYTEXTURE* GCMesh::GetGeometryTexture()
//{
//	return m_GeoTextures;
//}




void GCMesh::Render() {

    // Upload
    HRESULT hr;
    hr = m_pConstantBuffer->Map(0, nullptr, reinterpret_cast<void**>(&m_pMappedConstantBuffer));
    ASSERT_FAILED(hr);

    // Copie des données des constantes
    memcpy(m_pMappedConstantBuffer, m_pWorldViewProjData, sizeof(GCOBJECTCONSTANTS));

    m_pConstantBuffer->Unmap(0, nullptr);



	OutputDebugString(L"Set index buffer");







	m_pRender->GetCommandList()->SetGraphicsRootConstantBufferView(0, m_pConstantBuffer->GetGPUVirtualAddress());


    m_pRender->GetCommandList()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    D3D12_VERTEX_BUFFER_VIEW vertexBufferView = m_pMeshData->m_vertexBufferView;
    m_pRender->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView);
    D3D12_INDEX_BUFFER_VIEW indexBufferView = m_pMeshData->m_indexBufferView;
    m_pRender->GetCommandList()->IASetIndexBuffer(&indexBufferView);

	m_pRender->GetCommandList()->DrawIndexedInstanced(m_pGeometry->vertexNumber, 1, 0, 0, 0);



}


