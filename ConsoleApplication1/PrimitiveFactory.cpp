#include "PrimitiveFactory.h"

PrimitiveFactory::PrimitiveFactory() {
}

PrimitiveFactory::~PrimitiveFactory() {
}

void PrimitiveFactory::Initialize(int type)
{
	m_Type = type;
}

void PrimitiveFactory::BuildBoxGeometry()
{
	m_BoxGeometry.vertices =
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

	m_BoxGeometry.indices =
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

	/*const UINT vbByteSize = (UINT)m_BoxGeometry.vertices.size() * sizeof(VertexTexture);
	const UINT ibByteSize = (UINT)m_BoxGeometry.indices.size() * sizeof(std::uint16_t);
	mBoxGeo = std::make_unique<MeshGeometry>();
	mBoxGeo->Name = "boxGeo";

	ThrowIfFailed(D3DCreateBlob(vbByteSize, &mBoxGeo->VertexBufferCPU));
	CopyMemory(mBoxGeo->VertexBufferCPU->GetBufferPointer(), m_BoxGeometry.vertices.data(), vbByteSize);

	ThrowIfFailed(D3DCreateBlob(ibByteSize, &mBoxGeo->IndexBufferCPU));
	CopyMemory(mBoxGeo->IndexBufferCPU->GetBufferPointer(), m_BoxGeometry.indices.data(), ibByteSize);

	mBoxGeo->VertexBufferGPU = d3dUtil::CreateDefaultBuffer(GetEngine()->Getmd3dDevice(),
		GetEngine()->GetmCommandList(), m_BoxGeometry.vertices.data(), vbByteSize, mBoxGeo->VertexBufferUploader);

	mBoxGeo->IndexBufferGPU = d3dUtil::CreateDefaultBuffer(GetEngine()->Getmd3dDevice(),
		GetEngine()->GetmCommandList(), m_BoxGeometry.indices.data(), ibByteSize, mBoxGeo->IndexBufferUploader);

	mBoxGeo->VertexByteStride = sizeof(VertexTexture);
	mBoxGeo->VertexBufferByteSize = vbByteSize;
	mBoxGeo->IndexFormat = DXGI_FORMAT_R16_UINT;
	mBoxGeo->IndexBufferByteSize = ibByteSize;

	SubmeshGeometry submesh;
	submesh.IndexCount = (UINT)m_BoxGeometry.indices.size();
	submesh.StartIndexLocation = 0;
	submesh.BaseVertexLocation = 0;*/
}
