#pragma once
#include "header.h"
#include "d3dUtil.h"

struct GCVERTEX
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT4 Color;
};


struct GCVERTEXTEXTURE
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT2 TexC; // Normal
};



struct GCGEOMETRY
{
	std::string name;
	std::vector<GCVERTEX> vertices;
	std::vector<std::uint16_t> indices;
	SubmeshGeometry submesh;
	std::unique_ptr<MeshGeometry> boxGeo;
	//modif les structs
};

struct GCGEOMETRYTEXTURE
{
	std::string name;
	std::vector<GCVERTEXTEXTURE> vertices;
	std::vector<std::uint16_t> indices;
	SubmeshGeometry submesh;
	std::unique_ptr<MeshGeometry> boxGeo;
	//a suppr
};

class Render;

class PrimitiveFactory
{
public : 

	PrimitiveFactory();
	~PrimitiveFactory();
	void Initialize(int type);
	GCGEOMETRY* BuildBoxGeometry();
	GCGEOMETRY* GetGeometry();
	GCGEOMETRYTEXTURE* GetGeometryTexture();
	GCGEOMETRYTEXTURE* BuildBoxGeometryTexture();
	//void BuildSphereGeometry();
protected:

	int m_Type;
	GCGEOMETRY m_BoxGeometry;
	//Geometry m_SphereGeometry;
};

