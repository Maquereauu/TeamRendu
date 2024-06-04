#include "Texture.h"
#include "Macros.h"
#include "DDSTextureLoader.h"
#include "Render.h"

GCTexture::GCTexture() 
{
    // 
    m_offset = 0;
    //m_namePath = "";


    m_textureBuffer = nullptr;
    m_uploadTexture = nullptr;

    // Texture offset for GPU ? 

    m_textureAdress = nullptr;
}

GCTexture::~GCTexture()
{
    // 
    m_textureBuffer.Reset();
    m_uploadTexture.Reset();

    //m_textureAdress = nullptr;


}

//void GCTexture::Initialize(Render* pRender)
//{
//    HRESULT hr;
//
//    //m_offset = offset - 1;
//
//
//
//
//    // Reset Alloc / List
//    hr = pRender->m_pCommandAllocator->Reset();
//    ASSERT_FAILED(hr);
//    hr = pRender->m_pCommandList->Reset(pRender->m_pCommandAllocator.Get(), nullptr);
//    ASSERT_FAILED(hr);
//
//
//    std::wstring texturePath = L"res/texture/" + L"test.dds";
//
//    // Create / Upload Ressource With Command List
//    hr = DirectX::CreateDDSTextureFromFile12(pRender->m_pDevice.Get(), 
//        pRender->m_pCommandList.Get(),
//        texturePath.c_str(),
//        m_textureBuffer,
//        m_uploadTexture,
//        0,
//        nullptr
//    );
//    ASSERT_FAILED(hr);
//
//
//
//    // Create S R V
//    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
//    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
//    srvDesc.Format = m_textureBuffer->GetDesc().Format;
//    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
//    srvDesc.Texture2D.MipLevels = m_textureBuffer->GetDesc().MipLevels;
//
//
//    CD3DX12_CPU_DESCRIPTOR_HANDLE srvHandle(pRender->m_pCbvSrvHeap->GetCPUDescriptorHandleForHeapStart());
//    srvHandle.Offset(m_offset, pRender->m_cbvSrvDescriptorSize);
//
//    hr = pRender->m_pCommandList->Close();
//    ASSERT_FAILED(hr);
//
//    ID3D12CommandList* ppCommandLists[] = { pRender->m_pCommandList.Get() };
//    pRender->m_pCommandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);
//
//    pRender->WaitForPreviousFrame();
//
//    pRender->m_pDevice->CreateShaderResourceView(m_textureBuffer.Get(), &srvDesc, srvHandle);
//
//
//
//    *m_textureAdress = CD3DX12_GPU_DESCRIPTOR_HANDLE(pRender->m_pCbvSrvHeap->GetGPUDescriptorHandleForHeapStart());
//    m_textureAdress->Offset(m_offset, pRender->m_cbvSrvDescriptorSize);
//
//}


void GCTexture::Render() {
    /*pRender->m_pCommandList->SetGraphicsRootDescriptorTable(0, m_textureAdress);*/



}