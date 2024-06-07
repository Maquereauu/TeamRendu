#pragma once

#include "d3dUtil.h"

class GCRender;

class GCTexture
{
public:
    GCTexture();
    ~GCTexture();

    void Initialize(std::string fileName, GCGraphics* pGraphics);
    void Render();

    // Getters
    inline CD3DX12_GPU_DESCRIPTOR_HANDLE GetHandleDescriptorGPU() const { return m_handleDescriptorGPU; }
    inline const std::string& GetNamePath() const { return m_namePath; }
    inline int GetSrvHeapIndex() const { return m_srvHeapIndex; }
    inline Microsoft::WRL::ComPtr<ID3D12Resource> GetTextureBuffer() const { return m_textureBuffer; }
    inline Microsoft::WRL::ComPtr<ID3D12Resource> GetUploadTexture() const { return m_uploadTexture; }
    inline Microsoft::WRL::ComPtr<ID3D12Resource> GetResource() const { return m_resource; }
    inline Microsoft::WRL::ComPtr<ID3D12Resource> GetUploadHeap() const { return m_uploadHeap; }
    inline UINT GetHeapDescSize() const { return m_heapDescSize; }
    inline UINT GetCbvSrvUavDescriptorSize() const { return m_CbvSrvUavDescriptorSize; }
    inline CD3DX12_GPU_DESCRIPTOR_HANDLE GetTextureAdress() const { return m_textureAdress; }

private:
    std::string m_namePath;

    // Offset index #TODO
    int m_srvHeapIndex;

    // #TODO Remove Com ptr
    Microsoft::WRL::ComPtr<ID3D12Resource> m_textureBuffer;
    Microsoft::WRL::ComPtr<ID3D12Resource> m_uploadTexture;
    Microsoft::WRL::ComPtr<ID3D12Resource> m_resource = nullptr;
    Microsoft::WRL::ComPtr<ID3D12Resource> m_uploadHeap = nullptr;

    UINT m_heapDescSize;
    UINT m_CbvSrvUavDescriptorSize;

    CD3DX12_GPU_DESCRIPTOR_HANDLE m_handleDescriptorGPU;
    CD3DX12_GPU_DESCRIPTOR_HANDLE m_textureAdress;
};
