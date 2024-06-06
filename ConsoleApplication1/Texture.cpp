#include "Texture.h"
#include "Macros.h"
#include "DDSTextureLoader.h"
#include "Render.h"
#include "Graphics.h"
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


void GCTexture::Initialize(GCRender* pRender, std::string fileName)
{
	//GetEngine()->mCommandList->Reset(GetEngine()->mDirectCmdListAlloc, GetEngine()->graphicManager->mShaders[1]->mPSO);
		//to do for gianni mcommandelist
	m_haepDescSize = pRender->Getmd3dDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	m_CbvSrvUavDescriptorSize = pRender->Getmd3dDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	// Texture resource
	std::string Name = "ahah";
	std::wstring wideFileName(fileName.begin(), fileName.end());

	// Create the final filename
	std::wstringstream ss;
	ss << L"Textures/" << wideFileName << L".dds";
	std::wstring Filename = ss.str();

	DirectX::CreateDDSTextureFromFile12(pRender->Getmd3dDevice(), pRender->GetCommandList(), Filename.c_str(), m_resource, m_uploadHeap);
	//if (Resource == nullptr)
	//	return false;

	// Heap
	CD3DX12_CPU_DESCRIPTOR_HANDLE hDescriptor(pRender->GetCbvSrvUavSrvDescriptorHeap()->GetCPUDescriptorHandleForHeapStart());
	hDescriptor.Offset(pRender->m_pGraphicsManager->GetTextures().size(), m_haepDescSize);

	// Desc texture
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Format = m_resource->GetDesc().Format;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = m_resource->GetDesc().MipLevels;
	srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;
	pRender->Getmd3dDevice()->CreateShaderResourceView(m_resource.Get(), &srvDesc, hDescriptor);
	//getGPU pour les dessiner	
	// Manager

	m_HDescriptorGPU = CD3DX12_GPU_DESCRIPTOR_HANDLE(pRender->GetCbvSrvUavSrvDescriptorHeap()->GetGPUDescriptorHandleForHeapStart());
	m_HDescriptorGPU.Offset(pRender->m_pGraphicsManager->GetTextures().size(), m_haepDescSize);

	pRender->m_pGraphicsManager->AddTex(this);
}

void GCTexture::Render() {
    /*pRender->m_pCommandList->SetGraphicsRootDescriptorTable(0, m_textureAdress);*/



}