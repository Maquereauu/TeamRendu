 #include "Render.h"

#include "d3dUtil.h"

#include "ShaderTexture.h"
#include "ShaderColor.h"
#include "Shader.h"
#include "Material.h"
#include "Global.h"
#include "Window.h"

#include "Macros.h"

#include "Graphics.h"

#include "Mesh.h"




//#include "Mesh.h"
//bool GCRender::Initialize() {
//
//	InitDirect3D();
//	shad1 = new ShaderTexture();
//	shad2 = new ShaderColor();
//	mesh1 = new Mesh();
//
//	material1 = new GCMaterial();
//	material1->Initialize();
//	material1->AddTexture("texture", this);
#include "Graphics.h"
#include "Mesh.h"
#include "Texture.h"

bool GCRender::Initialize(GCGraphics* graphicsManager) {
	m_pGraphicsManager = graphicsManager;
	InitDirect3D();


	OnResize();

	
	




	

	


	return true;
}


void GCRender::ResetCommandList() {
	ThrowIfFailed(m_CommandList->Reset(m_DirectCmdListAlloc, nullptr));
}

void GCRender::ExecuteCommandList() {
	ID3D12CommandList* cmdsLists[] = { m_CommandList };
	m_CommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);
}

void GCRender::CloseCommandList() {
	ThrowIfFailed(m_CommandList->Close());
}



void GCRender::EnableDebugController() {
	#if defined(DEBUG) || defined(_DEBUG) 
		// Enable the D3D12 debug layer.
		{
			ID3D12Debug* debugController;
			ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)));
			debugController->EnableDebugLayer();
		}
	#endif
}


bool GCRender::InitDirect3D()
{

	EnableDebugController();

	ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&m_dxgiFactory)));

	// Try to create hardware device.
	HRESULT hardwareResult = D3D12CreateDevice(nullptr,             D3D_FEATURE_LEVEL_11_0,IID_PPV_ARGS(&m_d3dDevice));

	// Fallback to WARP device.
	if (FAILED(hardwareResult))
	{
		IDXGIAdapter* pWarpAdapter;
		ThrowIfFailed(m_dxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&pWarpAdapter)));

		ThrowIfFailed(D3D12CreateDevice(
			pWarpAdapter,
			D3D_FEATURE_LEVEL_11_0,
			IID_PPV_ARGS(&m_d3dDevice)));
	}

	ThrowIfFailed(m_d3dDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE,
		IID_PPV_ARGS(&m_Fence)));

	m_rtvDescriptorSize = m_d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	m_dsvDescriptorSize = m_d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	m_cbvSrvUavDescriptorSize = m_d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS msQualityLevels;
	msQualityLevels.Format = m_BackBufferFormat;
	msQualityLevels.SampleCount = 4;
	msQualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
	msQualityLevels.NumQualityLevels = 0;
	ThrowIfFailed(m_d3dDevice->CheckFeatureSupport(
		D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS,
		&msQualityLevels,
		sizeof(msQualityLevels)));

	m_4xMsaaQuality = msQualityLevels.NumQualityLevels;
	assert(m_4xMsaaQuality > 0 && "Unexpected MSAA quality level.");

	#ifdef _DEBUG
		LogAdapters();
	#endif

	CreateCommandObjects();
	CreateSwapChain();
	CreateRtvAndDsvDescriptorHeaps();
	CreateCbvSrvUavDescriptorHeaps();


	m_canResize = true;


	return true;
}


void GCRender::LogAdapters()
{
	UINT i = 0;
	IDXGIAdapter* adapter = nullptr;
	std::vector<IDXGIAdapter*> adapterList;
	while (m_dxgiFactory->EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_ADAPTER_DESC desc;
		adapter->GetDesc(&desc);

		std::wstring text = L"***Adapter: ";
		text += desc.Description;
		text += L"\n";

		OutputDebugString(text.c_str());

		adapterList.push_back(adapter);

		++i;
	}

	for (size_t i = 0; i < adapterList.size(); ++i)
	{
		LogAdapterOutputs(adapterList[i]);
		ReleaseCom(adapterList[i]);
	}
}

void GCRender::LogAdapterOutputs(IDXGIAdapter* adapter)
{
	UINT i = 0;
	IDXGIOutput* output = nullptr;
	while (adapter->EnumOutputs(i, &output) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_OUTPUT_DESC desc;
		output->GetDesc(&desc);

		std::wstring text = L"***Output: ";
		text += desc.DeviceName;
		text += L"\n";
		OutputDebugString(text.c_str());

		LogOutputDisplayModes(output, m_BackBufferFormat);

		ReleaseCom(output);

		++i;
	}

	m_canResize = true;

	//return true;
}

void GCRender::CreateCommandObjects()
{
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	ThrowIfFailed(m_d3dDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_CommandQueue)));

	ThrowIfFailed(m_d3dDevice->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(&m_DirectCmdListAlloc)));

	ThrowIfFailed(m_d3dDevice->CreateCommandList(
		0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		m_DirectCmdListAlloc, // Associated command allocator
		nullptr,                   // Initial PipelineStateObject
		IID_PPV_ARGS(&m_CommandList)));

	// Start off in a closed state.  This is because the first time we refer 
	// to the command list we will Reset it, and it needs to be closed before
	// calling Reset.
	m_CommandList->Close();
}







void GCRender::CreateSwapChain()
{
	// Release the previous swapchain we will be recreating.
	if (m_SwapChain != nullptr) {
		m_SwapChain->Release();
	}

	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = GetWindow()->GetClientWidth();
	sd.BufferDesc.Height = GetWindow()->GetClientHeight();
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = m_BackBufferFormat;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SampleDesc.Count = m_4xMsaaState ? 4 : 1;
	sd.SampleDesc.Quality = m_4xMsaaState ? (m_4xMsaaQuality - 1) : 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = SwapChainBufferCount;
	sd.OutputWindow = GetWindow()->GetHMainWnd();
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// Note: Swap chain uses queue to perform flush.
	ThrowIfFailed(m_dxgiFactory->CreateSwapChain(
		m_CommandQueue,
		&sd,
		&m_SwapChain));
}



// CREATE HEAPS
void GCRender::CreateCbvSrvUavDescriptorHeaps() {
	// Create CBV / SRV / UAV descriptor heap
	D3D12_DESCRIPTOR_HEAP_DESC cbvHeapDesc = {};
	cbvHeapDesc.NumDescriptors = 100;
	cbvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	cbvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	cbvHeapDesc.NodeMask = 0;
	ThrowIfFailed(m_d3dDevice->CreateDescriptorHeap(&cbvHeapDesc, IID_PPV_ARGS(&m_cbvSrvUavDescriptorHeap)));

	//m_cbvSrvUavDescriptorSize = m_d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

void GCRender::CreateRtvAndDsvDescriptorHeaps()
{
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc;
	rtvHeapDesc.NumDescriptors = SwapChainBufferCount;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	rtvHeapDesc.NodeMask = 0;
	ThrowIfFailed(m_d3dDevice->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&m_rtvHeap)));


	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc;
	dsvHeapDesc.NumDescriptors = 1;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	dsvHeapDesc.NodeMask = 0;
	ThrowIfFailed(m_d3dDevice->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&m_dsvHeap)));
}
//


// RESIZE
void GCRender::OnResize() {
	// Vérification des conditions initiales.
	if (m_canResize == false) return;
	assert(m_d3dDevice);
	assert(m_SwapChain);
	assert(m_DirectCmdListAlloc);


	FlushCommandQueue();

	ResetCommandList();

	ReleasePreviousResources();
	ResizeSwapChain();
	CreateRenderTargetViews();
	CreateDepthStencilBufferAndView();

	CloseCommandList();
	ExecuteCommandList();
	FlushCommandQueue();

	UpdateViewport();
}


void GCRender::ReleasePreviousResources() {
	for (int i = 0; i < SwapChainBufferCount; ++i) {
		if (m_SwapChainBuffer[i] != nullptr) {
			m_SwapChainBuffer[i]->Release();
		}
	}
	if (m_DepthStencilBuffer != nullptr) {
		m_DepthStencilBuffer->Release();
	}
}


void GCRender::ResizeSwapChain() {
	ThrowIfFailed(m_SwapChain->ResizeBuffers(
		SwapChainBufferCount,
		GetWindow()->GetClientWidth(), GetWindow()->GetClientHeight(),
		m_BackBufferFormat,
		DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH));
	m_CurrBackBuffer = 0;
}


void GCRender::CreateRenderTargetViews() {
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart());
	for (UINT i = 0; i < SwapChainBufferCount; i++) {
		ThrowIfFailed(m_SwapChain->GetBuffer(i, IID_PPV_ARGS(&m_SwapChainBuffer[i])));
		m_d3dDevice->CreateRenderTargetView(m_SwapChainBuffer[i], nullptr, rtvHeapHandle);
		rtvHeapHandle.Offset(1, m_rtvDescriptorSize);
	}
}


void GCRender::CreateDepthStencilBufferAndView() {
	D3D12_RESOURCE_DESC depthStencilDesc = {};
	depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthStencilDesc.Alignment = 0;
	depthStencilDesc.Width = GetWindow()->GetClientWidth();
	depthStencilDesc.Height = GetWindow()->GetClientHeight();
	depthStencilDesc.DepthOrArraySize = 1;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
	depthStencilDesc.SampleDesc.Count = m_4xMsaaState ? 4 : 1;
	depthStencilDesc.SampleDesc.Quality = m_4xMsaaState ? (m_4xMsaaQuality - 1) : 0;
	depthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	depthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	D3D12_CLEAR_VALUE optClear = {};
	optClear.Format = m_DepthStencilFormat;
	optClear.DepthStencil.Depth = 1.0f;
	optClear.DepthStencil.Stencil = 0;

	CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_DEFAULT);
	ThrowIfFailed(m_d3dDevice->CreateCommittedResource(
		&heapProps,
		D3D12_HEAP_FLAG_NONE,
		&depthStencilDesc,
		D3D12_RESOURCE_STATE_COMMON,
		&optClear,
		IID_PPV_ARGS(&m_DepthStencilBuffer)));

	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Format = m_DepthStencilFormat;
	dsvDesc.Texture2D.MipSlice = 0;
	m_d3dDevice->CreateDepthStencilView(m_DepthStencilBuffer, &dsvDesc, GetDepthStencilView());

	CD3DX12_RESOURCE_BARRIER ResBar(CD3DX12_RESOURCE_BARRIER::Transition(m_DepthStencilBuffer,
		D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE));
	m_CommandList->ResourceBarrier(1, &ResBar);
}




void GCRender::UpdateViewport() {
	m_ScreenViewport.TopLeftX = 0;
	m_ScreenViewport.TopLeftY = 0;
	m_ScreenViewport.Width = static_cast<float>(GetWindow()->GetClientWidth());
	m_ScreenViewport.Height = static_cast<float>(GetWindow()->GetClientHeight());
	m_ScreenViewport.MinDepth = 0.0f;
	m_ScreenViewport.MaxDepth = 1.0f;

	m_ScissorRect = { 0, 0, GetWindow()->GetClientWidth(), GetWindow()->GetClientHeight() };


}
// RESIZE

void GCRender::Update(const Timer& gt) {

}


// DRAW

void GCRender::FlushCommandQueue()
{
	// Advance the fence value to mark commands up to this fence point.
	m_CurrentFence++;

	// Add an instruction to the command queue to set a new fence point.  Because we 
	// are on the GPU timeline, the new fence point won't be set until the GPU finishes
	// processing all the commands prior to this Signal().
	ThrowIfFailed(m_CommandQueue->Signal(m_Fence, m_CurrentFence));

	// Wait until the GPU has completed commands up to this fence point.
	if (m_Fence->GetCompletedValue() < m_CurrentFence)
	{
		HANDLE eventHandle = CreateEventEx(nullptr, NULL, false, EVENT_ALL_ACCESS);

		// Fire event when GPU hits current fence.  
		ThrowIfFailed(m_Fence->SetEventOnCompletion(m_CurrentFence, eventHandle));

		// Wait until the GPU hits current fence event is fired.
		WaitForSingleObject(eventHandle, INFINITE);
		CloseHandle(eventHandle);
	}
}
void GCRender::PrepareDraw() {
	ThrowIfFailed(m_DirectCmdListAlloc->Reset());
	ThrowIfFailed(m_CommandList->Reset(m_DirectCmdListAlloc, nullptr));

	m_CommandList->RSSetViewports(1, &m_ScreenViewport);
	m_CommandList->RSSetScissorRects(1, &m_ScissorRect);

	// Swap
	CD3DX12_RESOURCE_BARRIER ResBar(CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(),D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));
	m_CommandList->ResourceBarrier(1, &ResBar);

	// 
	m_CommandList->ClearRenderTargetView(CurrentBackBufferView(), DirectX::Colors::LightBlue, 0, nullptr);
	m_CommandList->ClearDepthStencilView(GetDepthStencilView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);

	// 
	D3D12_CPU_DESCRIPTOR_HANDLE dsv = GetDepthStencilView();
	D3D12_CPU_DESCRIPTOR_HANDLE cbbv = CurrentBackBufferView();
	m_CommandList->OMSetRenderTargets(1, &cbbv, true, &dsv);

	ID3D12DescriptorHeap* descriptorHeaps[] = { m_cbvSrvUavDescriptorHeap };
	m_CommandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);
	m_CommandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}









void GCRender::DrawOneObject(GCMesh* pMesh, DirectX::XMMATRIX worldViewProj, GCShader* pShader) {
    // Configuration du pipeline de rendu
    m_CommandList->SetPipelineState(pShader->GetPso()); // Configuration de l'état du pipeline
    m_CommandList->SetGraphicsRootSignature(pShader->GetRootSign()); // Configuration de la signature racine

    // Configuration du type de primitive
    m_CommandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Configuration des tampons de vertex et d'index
    D3D12_VERTEX_BUFFER_VIEW vertexBufferView = pMesh->GetBoxGeometry()->boxGeo->VertexBufferView();
    m_CommandList->IASetVertexBuffers(0, 1, &vertexBufferView);
    D3D12_INDEX_BUFFER_VIEW indexBufferView = pMesh->GetBoxGeometry()->boxGeo->IndexBufferView();
    m_CommandList->IASetIndexBuffer(&indexBufferView);

    // Configuration de la texture si le shader est de type texture
    if (pShader->m_Type == STEnum::texture) {
        m_CommandList->SetGraphicsRootDescriptorTable(0, m_pGraphicsManager->GetMaterials()[0]->GetTexture()->GetHandleDescriptorGPU());
    }

    

    // Configuration des constantes de l'objet à envoyer au GPU
    m_Buffer = std::make_unique<UploadBuffer<ObjectConstants>>(Getmd3dDevice(), 1, true);
    ObjectConstants objConstants;
    XMStoreFloat4x4(&objConstants.WorldViewProj, XMMatrixTranspose(worldViewProj)); // Transposition de la matrice
    m_Buffer->CopyData(0, objConstants); // Copie des données dans le tampon de chargement
    m_CommandList->SetGraphicsRootConstantBufferView(pShader->m_Type == STEnum::texture ? 1 : 0, m_Buffer->Resource()->GetGPUVirtualAddress());

    // Dessin de l'objet indexé
    m_CommandList->DrawIndexedInstanced(pMesh->GetBoxGeometry()->boxGeo->DrawArgs["box"].IndexCount, 1, 0, 0, 0);
}

void GCRender::PostDraw() {
	CD3DX12_RESOURCE_BARRIER ResBar2(CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

	m_CommandList->ResourceBarrier(1, &ResBar2);
	ThrowIfFailed(m_CommandList->Close());


	ID3D12CommandList* cmdsLists[] = { m_CommandList };
	m_CommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);


	ThrowIfFailed(m_SwapChain->Present(0, 0));
	m_CurrBackBuffer = (m_CurrBackBuffer + 1) % SwapChainBufferCount;


	FlushCommandQueue();
}
// DRAW





// LOG 

//void GCRender::LogAdapters()
//{
//	UINT i = 0;
//	IDXGIAdapter* adapter = nullptr;
//	std::vector<IDXGIAdapter*> adapterList;
//	while (m_dxgiFactory->EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND)
//	{
//		DXGI_ADAPTER_DESC desc;
//		adapter->GetDesc(&desc);
//
//		std::wstring text = L"***Adapter: ";
//		text += desc.Description;
//		text += L"\n";
//
//		OutputDebugString(text.c_str());
//
//		adapterList.push_back(adapter);
//
//		++i;
//	}
//
//	for (size_t i = 0; i < adapterList.size(); ++i)
//	{
//		LogAdapterOutputs(adapterList[i]);
//		ReleaseCom(adapterList[i]);
//	}
//}
//
//void GCRender::LogAdapterOutputs(IDXGIAdapter* adapter)
//{
//	UINT i = 0;
//	IDXGIOutput* output = nullptr;
//	while (adapter->EnumOutputs(i, &output) != DXGI_ERROR_NOT_FOUND)
//	{
//		DXGI_OUTPUT_DESC desc;
//		output->GetDesc(&desc);
//
//		std::wstring text = L"***Output: ";
//		text += desc.DeviceName;
//		text += L"\n";
//		OutputDebugString(text.c_str());
//
//		LogOutputDisplayModes(output, m_BackBufferFormat);
//
//		ReleaseCom(output);
//
//		++i;
//	}
//}

void GCRender::LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format)
{
	UINT count = 0;
	UINT flags = 0;

	// Call with nullptr to get list count.
	output->GetDisplayModeList(format, flags, &count, nullptr);

	std::vector<DXGI_MODE_DESC> modeList(count);
	output->GetDisplayModeList(format, flags, &count, &modeList[0]);

	for (auto& x : modeList)
	{
		UINT n = x.RefreshRate.Numerator;
		UINT d = x.RefreshRate.Denominator;
		std::wstring text =
			L"Width = " + std::to_wstring(x.Width) + L" " +
			L"Height = " + std::to_wstring(x.Height) + L" " +
			L"Refresh = " + std::to_wstring(n) + L"/" + std::to_wstring(d) +
			L"\n";

		::OutputDebugString(text.c_str());
	}
}
// LOG