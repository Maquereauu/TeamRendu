#pragma once

#include "d3dUtil.h"

class GCTexture;
class GCRender;
class GCGraphics;





class GCMaterial
{
public:
    GCMaterial();
    ~GCMaterial();

    void Initialize();
    void SetColor(const DirectX::XMFLOAT4& color);
    void AddTexture(std::string name, GCGraphics* pGraphics);

    inline GCTexture* GetTexture() const { return m_pTexture; }
    inline DirectX::XMFLOAT4 GetColor() const { return m_color; }

private:
    GCTexture* m_pTexture;
    DirectX::XMFLOAT4 m_color;
};
