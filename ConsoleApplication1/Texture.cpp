
#include "Macros.h"
#include "DDSTextureLoader.h"

#include "Render.h"
#include "Graphics.h"
#include "Texture.h"

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


void GCTexture::Initialize(std::string fileName, GCGraphics* pGraphics)
{
	//GetEngine()->mCommandList->Reset(GetEngine()->mDirectCmdListAlloc, GetEngine()->graphicManager->mShaders[1]->mPSO);
		//to do for gianni mcommandelist
	m_haepDescSize = pGraphics->m_pRender->Getmd3dDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	m_CbvSrvUavDescriptorSize = pGraphics->m_pRender->Getmd3dDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	// Texture resource
	std::string Name = "ahah";
	std::wstring wideFileName(fileName.begin(), fileName.end());

	// Create the final filename
	std::wstringstream ss;
	ss << L"Textures/" << wideFileName << L".dds";
	std::wstring Filename = ss.str();

	DirectX::CreateDDSTextureFromFile12(pGraphics->m_pRender->Getmd3dDevice(), pGraphics->m_pRender->GetCommandList(), Filename.c_str(), m_resource, m_uploadHeap);
	//if (Resource == nullptr)
	//	return false;

	// Heap
	CD3DX12_CPU_DESCRIPTOR_HANDLE hDescriptor(pGraphics->m_pRender->GetCbvSrvUavSrvDescriptorHeap()->GetCPUDescriptorHandleForHeapStart());
	hDescriptor.Offset(pGraphics->m_pRender->m_pGraphicsManager->m_textureId, m_haepDescSize);

	// Desc texture
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Format = m_resource->GetDesc().Format;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = m_resource->GetDesc().MipLevels;
	srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;
	pGraphics->m_pRender->Getmd3dDevice()->CreateShaderResourceView(m_resource.Get(), &srvDesc, hDescriptor);
	//getGPU pour les dessiner	
	// Manager

	m_HDescriptorGPU = CD3DX12_GPU_DESCRIPTOR_HANDLE(pGraphics->m_pRender->GetCbvSrvUavSrvDescriptorHeap()->GetGPUDescriptorHandleForHeapStart());
	m_HDescriptorGPU.Offset(pGraphics->m_pRender->m_pGraphicsManager->m_textureId, m_haepDescSize);

}

void GCTexture::Render() {



}