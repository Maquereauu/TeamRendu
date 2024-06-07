#pragma once
#include "header.h"
#include "UploadBuffer.h"

class Window;

#include "Shader.h"
#include "ShaderColor.h"
#include "ShaderTexture.h"


class GCMaterial;
class GCGraphics;
class GCMesh;
class GCTexture;

struct ObjectConstants
{
	DirectX::XMFLOAT4X4 WorldViewProj = MathHelper::Identity4x4();
};



class GCRender
{
public:
	GCRender(){}

	bool Initialize(GCGraphics* graphicsManager);
	bool InitDirect3D();


	//void BuildConstantBuffers();

	void LogAdapters();
	void LogAdapterOutputs(IDXGIAdapter* adapter);
	void LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format);

	void EnableDebugController();



	// Resize 
	void CreateCommandObjects();
	void CreateRtvAndDsvDescriptorHeaps();
	void CreateCbvSrvUavDescriptorHeaps();
	void CreateSwapChain();




	void ReleasePreviousResources();
	void ResizeSwapChain();
	void CreateRenderTargetViews();
	void CreateDepthStencilBufferAndView();
	void ExecuteResizeCommands();
	void UpdateViewport();


	// Draw Part
	void ResetCommandList();
	void ExecuteCommandList();
	void CloseCommandList();

	void FlushCommandQueue();
	void Update(const Timer& gt);

	void PrepareDraw();
	void PostDraw();

	void DrawOneObject(GCMesh* pMesh, DirectX::XMMATRIX worldViewProj ,GCShader* pShader);
	

	void OnResize();

	// Getter
	inline bool Get4xMsaaState() { return m_4xMsaaState; }
	inline ID3D12Device* Getmd3dDevice() { return m_d3dDevice; }
	inline ID3D12Resource* CurrentBackBuffer() const { return m_SwapChainBuffer[m_CurrBackBuffer]; }
	inline D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView() const { return CD3DX12_CPU_DESCRIPTOR_HANDLE(m_rtvHeap->GetCPUDescriptorHandleForHeapStart(), m_CurrBackBuffer, m_rtvDescriptorSize); }
	inline D3D12_CPU_DESCRIPTOR_HANDLE GetDepthStencilView() const { return m_dsvHeap->GetCPUDescriptorHandleForHeapStart(); }
	inline UINT Get4xMsaaQuality() { return m_4xMsaaQuality; }
	inline DXGI_FORMAT GetBackBufferFormat() { return m_BackBufferFormat; }
	inline DXGI_FORMAT GetDepthStencilFormat() { return m_DepthStencilFormat; }
	inline ID3D12GraphicsCommandList* GetCommandList() { return m_CommandList; }
	inline ID3D12CommandQueue* GetCommandQueue() const { return m_CommandQueue; }
	inline ID3D12CommandAllocator* GetCommandAllocator() const { return m_DirectCmdListAlloc; }
	inline ID3D12Fence* GetFence() { return m_Fence; }
	inline ID3D12DescriptorHeap* GetRtvHeap() { return m_rtvHeap; }
	inline ID3D12DescriptorHeap* GetDsvHeap() { return m_dsvHeap; }
	inline ID3D12DescriptorHeap* GetCbvSrvUavSrvDescriptorHeap() { return m_cbvSrvUavDescriptorHeap; }
	inline UINT GetRtvDescriptorSize() const { return m_rtvDescriptorSize; }
	inline UINT GetDsvDescriptorSize() const { return m_dsvDescriptorSize; }
	inline UINT GetCbvSrvUavDescriptorSize() const { return m_cbvSrvUavDescriptorSize; }



	GCGraphics* m_pGraphicsManager;
private:
	// Swap chain size
	static const int SwapChainBufferCount = 2;

	// DirectX12 3D instances
	IDXGIFactory4* m_dxgiFactory;
	ID3D12Device* m_d3dDevice;

	IDXGISwapChain* m_SwapChain;
	ID3D12Resource* m_SwapChainBuffer[SwapChainBufferCount];
	ID3D12Resource* m_DepthStencilBuffer;

	ID3D12GraphicsCommandList* m_CommandList;
	ID3D12CommandQueue* m_CommandQueue;
	ID3D12CommandAllocator* m_DirectCmdListAlloc;

	// Fence
	ID3D12Fence* m_Fence;
	UINT64 m_CurrentFence = 0;

	// Descriptor heaps
	ID3D12DescriptorHeap* m_rtvHeap;
	ID3D12DescriptorHeap* m_dsvHeap;
	ID3D12DescriptorHeap* m_cbvSrvUavDescriptorHeap;

	// Descriptors size
	UINT m_rtvDescriptorSize = 0;
	UINT m_dsvDescriptorSize = 0;
	UINT m_cbvSrvUavDescriptorSize = 0;

	// State variables
	bool m_canResize;
	int m_CurrBackBuffer = 0;

	// Format
	DXGI_FORMAT m_DepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	DXGI_FORMAT m_BackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

	// MSAA
	bool m_4xMsaaState = false; // 4X MSAA enabled
	UINT m_4xMsaaQuality = 0;   // Quality level of 4X MSAA

	// Screen properties
	D3D12_VIEWPORT m_ScreenViewport;
	D3D12_RECT m_ScissorRect;

	// Static Sampler
	CD3DX12_STATIC_SAMPLER_DESC staticSample;



	// Buffer for Object Constants
	std::unique_ptr<UploadBuffer<ObjectConstants>> m_Buffer;
};

