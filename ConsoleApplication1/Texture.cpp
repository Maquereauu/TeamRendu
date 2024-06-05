#include "Texture.h"
#include "Macros.h"
#include "DDSTextureLoader.h"
#include "Render.h"

GCTexture::GCTexture() 
{
    GCRender r;

    // 
    SrvHeapIndex = 0;
    //m_namePath = "";


    m_textureBuffer = nullptr;
    m_uploadTexture = nullptr;

    // Texture offset for GPU ? 

    //m_textureAdress = nullptr;
}

GCTexture::~GCTexture()
{
    // 
    m_textureBuffer.Reset();
    m_uploadTexture.Reset();

    //m_textureAdress = nullptr;


}


void GCTexture::Initialize(GCRender* pRender)
{
    HRESULT hr;

    SrvHeapIndex = 0;

    // Reset Alloc / List
    hr = pRender->GetCommandAllocator()->Reset();
    ASSERT_FAILED(hr);
    hr = pRender->GetCommandList()->Reset(pRender->GetCommandAllocator(), nullptr);
    ASSERT_FAILED(hr);

    std::wstring texturePath = L"Textures/texture.dds";

    // Create / Upload Ressource With Command List
    hr = DirectX::CreateDDSTextureFromFile12(pRender->Getmd3dDevice(),
        pRender->GetCommandList(),
        texturePath.c_str(),
        m_textureBuffer,
        m_uploadTexture,
        0,
        nullptr
    );
    ASSERT_FAILED(hr);

    // Create S R V
    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    srvDesc.Format = m_textureBuffer->GetDesc().Format;
    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = m_textureBuffer->GetDesc().MipLevels;

    CD3DX12_CPU_DESCRIPTOR_HANDLE srvHandle(pRender->GetCbvSrvUavSrvDescriptorHeap()->GetCPUDescriptorHandleForHeapStart());

    srvHandle.Offset(0, pRender->GetCbvSrvUavDescriptorSize());

    hr = pRender->GetCommandList()->Close();
    ASSERT_FAILED(hr);

    ID3D12CommandList* ppCommandLists[] = { pRender->GetCommandList() };
    pRender->GetCommandQueue()->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

    pRender->FlushCommandQueue();

    pRender->Getmd3dDevice()->CreateShaderResourceView(m_textureBuffer.Get(), &srvDesc, srvHandle);

    m_textureAdress = CD3DX12_GPU_DESCRIPTOR_HANDLE(pRender->GetCbvSrvUavSrvDescriptorHeap()->GetGPUDescriptorHandleForHeapStart());
    m_textureAdress.Offset(0, pRender->GetCbvSrvUavDescriptorSize());
}

void GCTexture::Render() {
    /*pRender->m_pCommandList->SetGraphicsRootDescriptorTable(0, m_textureAdress);*/



}