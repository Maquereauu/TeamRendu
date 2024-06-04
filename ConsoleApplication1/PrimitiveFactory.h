#pragma once
#include "header.h"
#include "d3dUtil.h"

struct Vertex
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT4 Color;
};
struct VertexTexture
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT2 TexC;
};

struct Geometry
{
	std::string name;
	std::array<Vertex, 8> vertices;
	std::array<std::uint16_t, 36> indices;
	SubmeshGeometry submesh;
	std::unique_ptr<MeshGeometry> boxGeo;
};

class Render;

class PrimitiveFactory
{
public : 

	PrimitiveFactory();
	~PrimitiveFactory();
	void Initialize(int type);
	Geometry BuildBoxGeometry();
	Geometry GetGeometry();
	//void BuildSphereGeometry();

protected:

	int m_Type;
	Geometry m_BoxGeometry;
	//Geometry m_SphereGeometry;
};

