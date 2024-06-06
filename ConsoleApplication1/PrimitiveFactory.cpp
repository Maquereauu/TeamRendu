#include "PrimitiveFactory.h"
#include "Global.h"
#include "Render.h"
#include "Mesh.h"

PrimitiveFactory::PrimitiveFactory() {
}

PrimitiveFactory::~PrimitiveFactory() {
}

void PrimitiveFactory::Initialize(int type, GCRender* pRender)
{
	m_pRender = pRender;
}

GCGeometryColor* PrimitiveFactory::BuildBoxGeometryColor()
{
    GCGeometryColor* boxGeometry = new GCGeometryColor();

    boxGeometry->vertices = {
        { DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT4(DirectX::Colors::White) },
        { DirectX::XMFLOAT3(-1.0f, +1.0f, -1.0f), DirectX::XMFLOAT4(DirectX::Colors::Black) },
        { DirectX::XMFLOAT3(+1.0f, +1.0f, -1.0f), DirectX::XMFLOAT4(DirectX::Colors::Red) },
        { DirectX::XMFLOAT3(+1.0f, -1.0f, -1.0f), DirectX::XMFLOAT4(DirectX::Colors::Green) },
        { DirectX::XMFLOAT3(-1.0f, -1.0f, +1.0f), DirectX::XMFLOAT4(DirectX::Colors::Blue) },
        { DirectX::XMFLOAT3(-1.0f, +1.0f, +1.0f), DirectX::XMFLOAT4(DirectX::Colors::Yellow) },
        { DirectX::XMFLOAT3(+1.0f, +1.0f, +1.0f), DirectX::XMFLOAT4(DirectX::Colors::Cyan) },
        { DirectX::XMFLOAT3(+1.0f, -1.0f, +1.0f), DirectX::XMFLOAT4(DirectX::Colors::Magenta) },
    };

    boxGeometry->indices = {
        0, 1, 2, 0, 2, 3,
        4, 6, 5, 4, 7, 6,
        4, 5, 1, 4, 1, 0,
        3, 2, 6, 3, 6, 7,
        1, 5, 6, 1, 6, 2,
        4, 0, 3, 4, 3, 7,
    };

    boxGeometry->vertexNumber = boxGeometry->vertices.size();
    boxGeometry->indiceNumber = boxGeometry->indices.size();

    

    return boxGeometry;
}


GCGeometryTexture* PrimitiveFactory::BuildBoxGeometryTexture()
{
	GCGeometryTexture* boxGeometry = new GCGeometryTexture();

	boxGeometry->vertices = {
		GCVERTEXTEXTURE({ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f),DirectX::XMFLOAT2(0, 1) }), // Bottom-left
		GCVERTEXTEXTURE({DirectX::XMFLOAT3(-1.0f, +1.0f, -1.0f),DirectX::XMFLOAT2(0, 0) }), // Top-left
		GCVERTEXTEXTURE({DirectX::XMFLOAT3(+1.0f, +1.0f, -1.0f),DirectX::XMFLOAT2(1, 0) }), // Top-right
		GCVERTEXTEXTURE({DirectX::XMFLOAT3(+1.0f, -1.0f, -1.0f),DirectX::XMFLOAT2(1, 1) }), // Bottom-right

		// Back face
		GCVERTEXTEXTURE({DirectX::XMFLOAT3(-1.0f, -1.0f, +1.0f),DirectX::XMFLOAT2(0, 1) }), // Bottom-left
		GCVERTEXTEXTURE({DirectX::XMFLOAT3(-1.0f, +1.0f, +1.0f),DirectX::XMFLOAT2(0, 0) }), // Top-left
		GCVERTEXTEXTURE({DirectX::XMFLOAT3(+1.0f, +1.0f, +1.0f),DirectX::XMFLOAT2(1, 0) }), // Top-right
		GCVERTEXTEXTURE({DirectX::XMFLOAT3(+1.0f, -1.0f, +1.0f),DirectX::XMFLOAT2(1, 1) }), // Bottom-right

		// Left face
		GCVERTEXTEXTURE({DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f),DirectX::XMFLOAT2(0, 1) }), // Bottom-front
		GCVERTEXTEXTURE({DirectX::XMFLOAT3(-1.0f, +1.0f, -1.0f),DirectX::XMFLOAT2(0, 0) }), // Top-front
		GCVERTEXTEXTURE({DirectX::XMFLOAT3(-1.0f, +1.0f, +1.0f),DirectX::XMFLOAT2(1, 0) }), // Top-back
		GCVERTEXTEXTURE({DirectX::XMFLOAT3(-1.0f, -1.0f, +1.0f),DirectX::XMFLOAT2(1, 1) }), // Bottom-back

		// Right face
		GCVERTEXTEXTURE({DirectX::XMFLOAT3(+1.0f, -1.0f, -1.0f),DirectX::XMFLOAT2(0, 1) }), // Bottom-front
		GCVERTEXTEXTURE({DirectX::XMFLOAT3(+1.0f, +1.0f, -1.0f),DirectX::XMFLOAT2(0, 0) }), // Top-front
		GCVERTEXTEXTURE({DirectX::XMFLOAT3(+1.0f, +1.0f, +1.0f),DirectX::XMFLOAT2(1, 0) }), // Top-back
		GCVERTEXTEXTURE({DirectX::XMFLOAT3(+1.0f, -1.0f, +1.0f),DirectX::XMFLOAT2(1, 1) }), // Bottom-back

		// Top face
		GCVERTEXTEXTURE({DirectX::XMFLOAT3(-1.0f, +1.0f, -1.0f),DirectX::XMFLOAT2(0, 1) }), // Bottom-left
		GCVERTEXTEXTURE({DirectX::XMFLOAT3(-1.0f, +1.0f, +1.0f),DirectX::XMFLOAT2(0, 0) }), // Top-left
		GCVERTEXTEXTURE({DirectX::XMFLOAT3(+1.0f, +1.0f, +1.0f),DirectX::XMFLOAT2(1, 0) }), // Top-right
		GCVERTEXTEXTURE({DirectX::XMFLOAT3(+1.0f, +1.0f, -1.0f),DirectX::XMFLOAT2(1, 1) }), // Bottom-right

		// Bottom face
		GCVERTEXTEXTURE({DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f),DirectX::XMFLOAT2(0, 1) }), // Bottom-left
		GCVERTEXTEXTURE({DirectX::XMFLOAT3(-1.0f, -1.0f, +1.0f),DirectX::XMFLOAT2(0, 0) }), // Top-left
		GCVERTEXTEXTURE({DirectX::XMFLOAT3(+1.0f, -1.0f, +1.0f),DirectX::XMFLOAT2(1, 0) }), // Top-right
		GCVERTEXTEXTURE({DirectX::XMFLOAT3(+1.0f, -1.0f, -1.0f),DirectX::XMFLOAT2(1, 1) })  // Bottom-right
	};


	boxGeometry->indices =
	{
		// Front face
		0, 1, 2,
		0, 2, 3,

		// Back face
		4, 6, 5,
		4, 7, 6,

		// Left face
		8, 10, 9,
		8, 11, 10,

		// Right face
		12, 13, 14,
		12, 14, 15,

		// Top face
		16, 17, 18,
		16, 18, 19,

		// Bottom face
		20, 22, 21,
		20, 23, 22
	};

	

	return boxGeometry;
}

