#pragma once
#include "header.h"
class Window;
class Shader;
class ShaderColor;
class ShaderTexture;
class Render
{
public:
	bool Initialize();
	bool InitDirect3D();
	void LogAdapters();
	void LogAdapterOutputs(IDXGIAdapter* adapter);
	void LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format);
	void CreateCommandObjects();
	void CreateRtvAndDsvDescriptorHeaps();
	void CreateSwapChain();
	void FlushCommandQueue();
	void BuildDescriptorHeaps();
	void BuildConstantBuffers();
	void BuildRootSignature();
	void BuildShadersAndInputLayout();
	void BuildBoxGeometry();
	void BuildPSO();
	void Update(const Timer& gt);
	void Draw(const Timer& gt);
	ID3D12Device* Getmd3dDevice();
	void OnResize();
	ID3D12Resource* CurrentBackBuffer()const;
	D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView()const;
	D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView()const;
	IDXGIFactory4* m_dxgiFactory;
	ID3D12Device* m_d3dDevice;
	ID3D12Fence* m_Fence;
	UINT64 m_CurrentFence = 0;
	ID3D12DescriptorHeap* m_RtvHeap;
	ID3D12DescriptorHeap* m_DsvHeap;
	ID3D12DescriptorHeap* m_SrvDescriptorHeap;
	UINT m_RtvDescriptorSize = 0;
	UINT m_DsvDescriptorSize = 0;
	UINT m_CbvSrvUavDescriptorSize = 0;
	static const int SwapChainBufferCount = 2;
	int m_CurrBackBuffer = 0;
	DXGI_FORMAT m_DepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	DXGI_FORMAT m_BackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	bool      m_4xMsaaState = false;    // 4X MSAA enabled
	UINT      m_4xMsaaQuality = 0;      // quality level of 4X MSAA
	ID3D12GraphicsCommandList* m_CommandList;
	IDXGISwapChain* m_SwapChain;
	ID3D12Resource* m_SwapChainBuffer[SwapChainBufferCount];
	ID3D12Resource* m_DepthStencilBuffer;
	ID3D12CommandQueue* m_CommandQueue;
	ID3D12CommandAllocator* m_DirectCmdListAlloc;
	bool canResize;
	D3D12_VIEWPORT m_ScreenViewport;
	D3D12_RECT m_ScissorRect;
	DirectX::XMFLOAT4X4 mWorld = MathHelper::Identity4x4();
	DirectX::XMFLOAT4X4 mView = MathHelper::Identity4x4();
	DirectX::XMFLOAT4X4 mProj = MathHelper::Identity4x4();
	CD3DX12_STATIC_SAMPLER_DESC staticSample;
	ID3D12DescriptorHeap* m_CbvHeap = nullptr;
	ShaderTexture* shad1;
	ShaderColor* shad2;
};

