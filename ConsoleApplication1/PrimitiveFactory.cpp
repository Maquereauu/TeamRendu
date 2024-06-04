#include "PrimitiveFactory.h"
#include "Global.h"
#include "Render.h"

PrimitiveFactory::PrimitiveFactory() {
}

PrimitiveFactory::~PrimitiveFactory() {
}

void PrimitiveFactory::Initialize(int type)
{
	m_Type = type;
}

Geometry* PrimitiveFactory::BuildBoxGeometry()
{
	Geometry* boxGeometry = new Geometry();
	boxGeometry->vertices =
	{
		Vertex({ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT4(DirectX::Colors::White) }),
		Vertex({ DirectX::XMFLOAT3(-1.0f, +1.0f, -1.0f), DirectX::XMFLOAT4(DirectX::Colors::Black) }),
		Vertex({ DirectX::XMFLOAT3(+1.0f, +1.0f, -1.0f), DirectX::XMFLOAT4(DirectX::Colors::Red) }),
		Vertex({ DirectX::XMFLOAT3(+1.0f, -1.0f, -1.0f), DirectX::XMFLOAT4(DirectX::Colors::Green) }),
		Vertex({ DirectX::XMFLOAT3(-1.0f, -1.0f, +1.0f), DirectX::XMFLOAT4(DirectX::Colors::Blue) }),
		Vertex({ DirectX::XMFLOAT3(-1.0f, +1.0f, +1.0f), DirectX::XMFLOAT4(DirectX::Colors::Yellow) }),
		Vertex({ DirectX::XMFLOAT3(+1.0f, +1.0f, +1.0f), DirectX::XMFLOAT4(DirectX::Colors::Cyan) }),
		Vertex({ DirectX::XMFLOAT3(+1.0f, -1.0f, +1.0f), DirectX::XMFLOAT4(DirectX::Colors::Magenta) }),
	};

	boxGeometry->indices =
	{
		//front face
		0, 1, 2,
		0, 2, 3,

		//back face
		4, 6, 5,
		4, 7, 6,

		//left face
		4, 5, 1,
		4, 1, 0,

		//right face
		3, 2, 6,
		3, 6, 7,

		//top face
		1, 5, 6,
		1, 6, 2,

		//bottom face
		4, 0, 3,
		4, 3, 7,
	};

	const UINT vbByteSize = (UINT)boxGeometry->vertices.size() * sizeof(Vertex);
	const UINT ibByteSize = (UINT)boxGeometry->indices.size() * sizeof(std::uint16_t);
	boxGeometry->boxGeo = std::make_unique<MeshGeometry>();
	boxGeometry->boxGeo->Name = "boxGeo";

	ThrowIfFailed(D3DCreateBlob(vbByteSize, &boxGeometry->boxGeo->VertexBufferCPU));
	CopyMemory(boxGeometry->boxGeo->VertexBufferCPU->GetBufferPointer(), boxGeometry->vertices.data(), vbByteSize);

	ThrowIfFailed(D3DCreateBlob(ibByteSize, &boxGeometry->boxGeo->IndexBufferCPU));
	CopyMemory(boxGeometry->boxGeo->IndexBufferCPU->GetBufferPointer(), boxGeometry->indices.data(), ibByteSize);

	boxGeometry->boxGeo->VertexBufferGPU = d3dUtil::CreateDefaultBuffer(GetRender()->Getmd3dDevice(),
		GetRender()->GetCommandList(), boxGeometry->vertices.data(), vbByteSize, boxGeometry->boxGeo->VertexBufferUploader);

	boxGeometry->boxGeo->IndexBufferGPU = d3dUtil::CreateDefaultBuffer(GetRender()->Getmd3dDevice(),
		GetRender()->GetCommandList(), boxGeometry->indices.data(), ibByteSize, boxGeometry->boxGeo->IndexBufferUploader);

	boxGeometry->boxGeo->VertexByteStride = sizeof(Vertex);
	boxGeometry->boxGeo->VertexBufferByteSize = vbByteSize;
	boxGeometry->boxGeo->IndexFormat = DXGI_FORMAT_R16_UINT;
	boxGeometry->boxGeo->IndexBufferByteSize = ibByteSize;

	SubmeshGeometry submesh;
	submesh.IndexCount = (UINT)boxGeometry->indices.size();
	submesh.StartIndexLocation = 0;
	submesh.BaseVertexLocation = 0;

	boxGeometry->submesh = submesh;

	return boxGeometry;
}

Geometry* PrimitiveFactory::GetGeometry()
{
	switch (m_Type) {
		case 0:
			Geometry* primitiveGeometry = BuildBoxGeometry();
			return primitiveGeometry;
			break;
	}

}