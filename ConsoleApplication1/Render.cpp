#include "Render.h"
#include "d3dUtil.h"
#include "ShaderTexture.h"
#include "ShaderColor.h"
#include "Shader.h"
#include "Global.h"
#include "Window.h"



#include "Mesh.h"
bool Render::Initialize() {
	InitDirect3D();
	shad1 = new ShaderTexture();
	shad2 = new ShaderColor();
	mesh1 = new Mesh();
	ThrowIfFailed(m_CommandList->Reset(m_DirectCmdListAlloc, nullptr));
	BuildDescriptorHeaps();
	//BuildConstantBuffers();
	BuildShadersAndInputLayout();
	BuildRootSignature();
	BuildBoxGeometry();
	//BuildTriangleGeometry();
	BuildPSO();
	//CreateSwapChain();
	// Execute the initialization commands.
	ThrowIfFailed(m_CommandList->Close());
	ID3D12CommandList* cmdsLists[] = { m_CommandList };
	m_CommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);
	/*ThrowIfFailed(m_CommandList->Reset(m_DirectCmdListAlloc, shad1->m_PSO));*/
	//texture1->TextureCreateFromFile12("Asteroid");
	//texture2->TextureCreateFromFile12("goku");
	//texture3->TextureCreateFromFile12("crosshair");
	//textureGameOver->TextureCreateFromFile12("Game_Over");
	//texture4->TextureCreateFromFile12("noeil");
	//texture5->TextureCreateFromFile12("Red_Hit3");
	//textureLifeBar5->TextureCreateFromFile12("HpBar5");
	//textureLifeBar4->TextureCreateFromFile12("HpBar4");
	//textureLifeBar3->TextureCreateFromFile12("HpBar3");
	//textureLifeBar2->TextureCreateFromFile12("HpBar2");
	//textureLifeBar1->TextureCreateFromFile12("HpBar1");
	//textureLifeBar0->TextureCreateFromFile12("HpBar0");
	//texture6->TextureCreateFromFile12("skybox");
	//ThrowIfFailed(mCommandList->Close());
	//ID3D12CommandList* cmdsLists2[] = { mCommandList };
	//mCommandQueue->ExecuteCommandLists(_countof(cmdsLists2), cmdsLists2);
	OnResize();
	//Wait until initialization is complete.
	FlushCommandQueue();
	return true;
}


bool Render::InitDirect3D()
{
#if defined(DEBUG) || defined(_DEBUG) 
		// Enable the D3D12 debug layer.
		{
			ID3D12Debug* debugController;
			ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)));
			debugController->EnableDebugLayer();
		}
#endif

	ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&m_dxgiFactory)));

	// Try to create hardware device.
	HRESULT hardwareResult = D3D12CreateDevice(
		nullptr,             // default adapter
		D3D_FEATURE_LEVEL_11_0,
		IID_PPV_ARGS(&m_d3dDevice));

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

	m_RtvDescriptorSize = m_d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	m_DsvDescriptorSize = m_d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	m_CbvSrvUavDescriptorSize = m_d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	// Check 4X MSAA quality suppo
	// vices support 4X MSAA for all render 
	// target formats, so we only need to check quality support.

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
	canResize = true;
	return true;
}
void Render::LogAdapters()
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

void Render::LogAdapterOutputs(IDXGIAdapter* adapter)
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
}

void Render::LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format)
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

void Render::CreateCommandObjects()
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

void Render::BuildDescriptorHeaps()
{
	D3D12_DESCRIPTOR_HEAP_DESC cbvHeapDesc;
	cbvHeapDesc.NumDescriptors = 100;
	cbvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	cbvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	cbvHeapDesc.NodeMask = 0;
	ThrowIfFailed(m_d3dDevice->CreateDescriptorHeap(&cbvHeapDesc, IID_PPV_ARGS(&m_CbvHeap)));
}


void Render::BuildRootSignature()
{
	// Root parameter can be a table, root descriptor or root constants.
	//for (int i = 0; i < graphicManager->mShaders.size(); i++)
	//	graphicManager->mShaders[i]->RootSign();
	shad1->RootSign();
	shad2->RootSign();
}

void Render::BuildShadersAndInputLayout()
{
	HRESULT hr = S_OK;
	//for (int i = 0; i < graphicManager->mShaders.size(); i++)
	//{
	//	graphicManager->mShaders[i]->CompileShader(i);
	//}
	shad1->CompileShader();
	shad2->CompileShader();
	//mvsByteCode = d3dUtil::CompileShader(L"Shaders\\color.hlsl", nullptr, "VS", "vs_5_0");
	//mpsByteCode = d3dUtil::CompileShader(L"Shaders\\color.hlsl", nullptr, "PS", "ps_5_0");

}

void Render::BuildPSO()
{
	//for (int i = 0; i < graphicManager->mShaders.size(); i++)
	//	graphicManager->mShaders[i]->Pso();
	shad1->Pso();
	shad2->Pso();
}

void Render::BuildBoxGeometry()
{
	//for (int i = 0; i < graphicManager->GetMeshes().size(); i++)
	//	graphicManager->GetMeshes()[i]->BuildGeo();
	mesh1->CreateObjGeometry();
}


void Render::CreateSwapChain()
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

void Render::FlushCommandQueue()
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

void Render::CreateRtvAndDsvDescriptorHeaps()
{
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc;
	rtvHeapDesc.NumDescriptors = SwapChainBufferCount;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	rtvHeapDesc.NodeMask = 0;
	ThrowIfFailed(m_d3dDevice->CreateDescriptorHeap(
		&rtvHeapDesc, IID_PPV_ARGS(&m_RtvHeap)));


	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc;
	dsvHeapDesc.NumDescriptors = 1;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	dsvHeapDesc.NodeMask = 0;
	ThrowIfFailed(m_d3dDevice->CreateDescriptorHeap(
		&dsvHeapDesc, IID_PPV_ARGS(&m_DsvHeap)));
}

ID3D12Device* Render::Getmd3dDevice()
{
	return m_d3dDevice;
}

void Render::OnResize()
{
	if (canResize == false)
		return;
	assert(m_d3dDevice);
	assert(m_SwapChain);
	assert(m_DirectCmdListAlloc);

	// Flush before changing any resources.
	FlushCommandQueue();

	ThrowIfFailed(m_CommandList->Reset(m_DirectCmdListAlloc, nullptr));

	// Release the previous resources we will be recreating.
	for (int i = 0; i < SwapChainBufferCount; ++i) {
		if (m_SwapChainBuffer[i] != nullptr) {
			m_SwapChainBuffer[i]->Release();
		}

	}
	if (m_DepthStencilBuffer != nullptr) {
		m_DepthStencilBuffer->Release();
	}

	// Resize the swap chain.
	ThrowIfFailed(m_SwapChain->ResizeBuffers(
		SwapChainBufferCount,
		GetWindow()->GetClientWidth(), GetWindow()->GetClientHeight(),
		m_BackBufferFormat,
		DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH));

	m_CurrBackBuffer = 0;

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle(m_RtvHeap->GetCPUDescriptorHandleForHeapStart());
	for (UINT i = 0; i < SwapChainBufferCount; i++)
	{
		ThrowIfFailed(m_SwapChain->GetBuffer(i, IID_PPV_ARGS(&m_SwapChainBuffer[i])));
		m_d3dDevice->CreateRenderTargetView(m_SwapChainBuffer[i], nullptr, rtvHeapHandle);
		rtvHeapHandle.Offset(1, m_RtvDescriptorSize);
	}

	// Create the depth/stencil buffer and view.
	D3D12_RESOURCE_DESC depthStencilDesc;
	depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthStencilDesc.Alignment = 0;
	depthStencilDesc.Width = GetWindow()->GetClientWidth();
	depthStencilDesc.Height = GetWindow()->GetClientHeight();
	depthStencilDesc.DepthOrArraySize = 1;
	depthStencilDesc.MipLevels = 1;

	// Correction 11/12/2016: SSAO chapter requires an SRV to the depth buffer to read from 
	// the depth buffer.  Therefore, because we need to create two views to the same resource:
	//   1. SRV format: DXGI_FORMAT_R24_UNORM_X8_TYPELESS
	//   2. DSV Format: DXGI_FORMAT_D24_UNORM_S8_UINT
	// we need to create the depth buffer resource with a typeless format.  
	depthStencilDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;

	depthStencilDesc.SampleDesc.Count = m_4xMsaaState ? 4 : 1;
	depthStencilDesc.SampleDesc.Quality = m_4xMsaaState ? (m_4xMsaaQuality - 1) : 0;
	depthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	depthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	D3D12_CLEAR_VALUE optClear;
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

	// Create descriptor to mip level 0 of entire resource using the format of the resource.
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Format = m_DepthStencilFormat;
	dsvDesc.Texture2D.MipSlice = 0;
	m_d3dDevice->CreateDepthStencilView(m_DepthStencilBuffer, &dsvDesc, DepthStencilView());

	CD3DX12_RESOURCE_BARRIER ResBar(CD3DX12_RESOURCE_BARRIER::Transition(m_DepthStencilBuffer,
		D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE));
	// Transition the resource from its initial state to be used as a depth buffer.
	m_CommandList->ResourceBarrier(1, &ResBar);

	// Execute the resize commands.
	ThrowIfFailed(m_CommandList->Close());
	ID3D12CommandList* cmdsLists[] = { m_CommandList };
	m_CommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	// Wait until resize is complete.
	FlushCommandQueue();

	// Update the viewport transform to cover the client area.
	m_ScreenViewport.TopLeftX = 0;
	m_ScreenViewport.TopLeftY = 0;
	m_ScreenViewport.Width = static_cast<float>(GetWindow()->GetClientWidth());
	m_ScreenViewport.Height = static_cast<float>(GetWindow()->GetClientHeight());
	m_ScreenViewport.MinDepth = 0.0f;
	m_ScreenViewport.MaxDepth = 1.0f;

	m_ScissorRect = { 0, 0, GetWindow()->GetClientWidth(), GetWindow()->GetClientHeight() };

	DirectX::XMMATRIX P = DirectX::XMMatrixPerspectiveFovLH(0.25f * MathHelper::Pi, GetWindow()->AspectRatio(), 1.0f, 1000.0f);
	XMStoreFloat4x4(&mProj, P);
}
D3D12_CPU_DESCRIPTOR_HANDLE Render::DepthStencilView()const
{
	return m_DsvHeap->GetCPUDescriptorHandleForHeapStart();
}

void Render::Update(const Timer& gt) {

}

void Render::Draw(const Timer& gt) {
	ThrowIfFailed(m_DirectCmdListAlloc->Reset());
	ThrowIfFailed(m_CommandList->Reset(m_DirectCmdListAlloc, nullptr));

	m_CommandList->RSSetViewports(1, &m_ScreenViewport);
	m_CommandList->RSSetScissorRects(1, &m_ScissorRect);

	CD3DX12_RESOURCE_BARRIER ResBar(CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(),
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));


	// Indicate a state transition on the resource usage.
	m_CommandList->ResourceBarrier(1, &ResBar);

	// Clear the back buffer and depth buffer.
	m_CommandList->ClearRenderTargetView(CurrentBackBufferView(), DirectX::Colors::LightBlue, 0, nullptr);
	m_CommandList->ClearDepthStencilView(DepthStencilView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);

	// Specify the buffers we are going to render to.
	D3D12_CPU_DESCRIPTOR_HANDLE dsv = DepthStencilView();
	D3D12_CPU_DESCRIPTOR_HANDLE cbbv = CurrentBackBufferView();

	m_CommandList->OMSetRenderTargets(1, &cbbv, true, &dsv);

	ID3D12DescriptorHeap* descriptorHeaps[] = { m_CbvHeap };
	m_CommandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);
	m_CommandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	/*for (int i = entityManager->mEntities.size() - 1; i >= 0; i--)
	{
		entityManager->mEntities.at(i)->draw();
	}*/

	m_CommandList->SetPipelineState(shad1->GetPso());
	m_CommandList->SetGraphicsRootSignature(shad1->GetRootSign());

	m_CommandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	D3D12_VERTEX_BUFFER_VIEW test = mesh1->GetGeometryTexture()->boxGeo->VertexBufferView();
	m_CommandList->IASetVertexBuffers(0, 1, &test);
	D3D12_INDEX_BUFFER_VIEW test2 = mesh1->GetGeometryTexture()->boxGeo->IndexBufferView();
	m_CommandList->IASetIndexBuffer(&test2);

	//if (mTexture != nullptr)
	//{
	//	//if (mIsCrosshair) {
	//	m_CommandList->SetGraphicsRootDescriptorTable(0, mTexture->mHDescriptorGPU);
	//	//}
	//	//else {
	//	//GetEngine()->mCommandList->SetGraphicsRootDescriptorTable(0, GetEngine()->graphicManager->mTextures[0]->mHDescriptorGPU);
	//	//}
	//}
	DirectX::XMFLOAT3 pos1;
	pos1.x = 0.f;
	pos1.y = 0.f;
	pos1.z = 0.f;
	DirectX::XMVECTOR pos = DirectX::XMVectorSet(0, 0, -5, 1.0f);
	DirectX::XMVECTOR target = DirectX::XMVectorZero();
	DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(pos, target, up);

	DirectX::XMFLOAT4X4 MId = MathHelper::Identity4x4();

	DirectX::XMMATRIX world = DirectX::XMLoadFloat4x4(&MId);
	DirectX::XMMATRIX proj = DirectX::XMLoadFloat4x4(&mProj);
	DirectX::XMMATRIX worldViewProj = world * view * proj;

	m_Buffer = std::make_unique<UploadBuffer<ObjectConstants>>(Getmd3dDevice(), 1, true);
	ObjectConstants objConstants;
	XMStoreFloat4x4(&objConstants.WorldViewProj, XMMatrixTranspose(worldViewProj));
	m_Buffer->CopyData(0, objConstants);
	m_CommandList->SetGraphicsRootConstantBufferView(/*shad1->m_Type ? 1 : 0*/0, m_Buffer->Resource()->GetGPUVirtualAddress());

	m_CommandList->DrawIndexedInstanced(
		mesh1->GetGeometryTexture()->boxGeo->DrawArgs["box"].IndexCount,
		1, 0, 0, 0);


	CD3DX12_RESOURCE_BARRIER ResBar2(CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

	m_CommandList->ResourceBarrier(1, &ResBar2);
	ThrowIfFailed(m_CommandList->Close());

	// Execute command list for the first shader draw
	ID3D12CommandList* cmdsLists[] = { m_CommandList };
	m_CommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	// Swap the back and front buffers
	ThrowIfFailed(m_SwapChain->Present(0, 0));
	m_CurrBackBuffer = (m_CurrBackBuffer + 1) % SwapChainBufferCount;

	// Wait until frame commands are complete.
	FlushCommandQueue();
}

ID3D12Resource* Render::CurrentBackBuffer()const
{
	return m_SwapChainBuffer[m_CurrBackBuffer];
}

D3D12_CPU_DESCRIPTOR_HANDLE Render::CurrentBackBufferView()const
{
	return CD3DX12_CPU_DESCRIPTOR_HANDLE(
		m_RtvHeap->GetCPUDescriptorHandleForHeapStart(),
		m_CurrBackBuffer,
		m_RtvDescriptorSize);
}

DXGI_FORMAT Render::GetBackBufferFormat() {
	return m_BackBufferFormat;
}


bool Render::Get4xMsaaState() {
	return m_4xMsaaState;
}


UINT Render::Get4xMsaaQuality() {
	return m_4xMsaaQuality;
}

DXGI_FORMAT Render::GetDepthStencilFormat() {
	return m_DepthStencilFormat;
}


ID3D12GraphicsCommandList* Render::GetCommandList() {
	return m_CommandList;
}