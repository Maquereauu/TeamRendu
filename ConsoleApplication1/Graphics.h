#pragma once

#include "header.h"

class Window;

class Graphics
{
    enum
    {
        FRAME_COUNT = 2,
    };

public:
        Graphics(Window* window);
        ~Graphics();

        void InitializeDirectX12Instances();
        void CreateFactory();
        void CreateSwapChain();
        void CreateDevice();
        void CreateCommandQueue();
        void CreateCommandAllocator();
        void CreateCommandList();
        void CreateFence();
        void CreateDescriptorHeap();
        void CreatePipelineState();
        void CreateRootSignature();

        //inline static UINT FRAME_COUNT = 2;
        int frameIndex;
        HANDLE fenceEvent;
        UINT64 fenceValue;

        Microsoft::WRL::ComPtr<IDXGIAdapter1> pAdapter;
        Microsoft::WRL::ComPtr<ID3D12Device> pDevice;
        Microsoft::WRL::ComPtr<IDXGIFactory4> pFactory;
        Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
        Microsoft::WRL::ComPtr<ID3D12CommandQueue> pCommandQueue;
        Microsoft::WRL::ComPtr<ID3D12CommandAllocator> pCommandAllocator;
        Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> pCommandList;
        Microsoft::WRL::ComPtr<ID3D12Fence> pFence;
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> pDescriptorHeap;
        UINT rtvDescriptorSize;

        Microsoft::WRL::ComPtr<ID3D12Resource> pRenderTargets[FRAME_COUNT];

        D3D12_VIEWPORT* pViewport;
        D3D12_RECT* pScissorRect;

        Microsoft::WRL::ComPtr<ID3DBlob> vertexShaderBlob;
        Microsoft::WRL::ComPtr<ID3DBlob> pixelShaderBlob;

        Microsoft::WRL::ComPtr<ID3D12PipelineState> pPipelineState;
        Microsoft::WRL::ComPtr<ID3D12RootSignature> pRootSignature;

        Microsoft::WRL::ComPtr<ID3D12Debug> debugController;
        UINT dxgiFactoryFlags = 0;

        Window* mWindow;
};


