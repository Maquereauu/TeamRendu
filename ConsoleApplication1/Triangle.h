#pragma once

#include "header.h"

class Graphics;

using namespace DirectX;

class Triangle {
public:
    Triangle(Graphics* graphics);
    ~Triangle();
    void Initialize();
    void PopulateCommandList();
    void WaitForPreviousFrame();
    void Render();

private:
    struct Vertex
    {
        XMFLOAT4 Pos;
        XMFLOAT4 Color;
    };


    int renderCallNum = 0;
    ID3D12Resource* vertexBuffer;
    D3D12_VERTEX_BUFFER_VIEW vertexBufferView;

    Graphics* renderer;

};
