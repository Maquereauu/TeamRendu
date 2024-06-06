#pragma once
#include "header.h"
#include "d3dUtil.h"


class GCMesh;
class GCGeometry;
class GCGeometryColor;
class GCGeometryTexture;



class GCRender;

//struct GCVERTEX
//{
//	DirectX::XMFLOAT3 Pos;
//	DirectX::XMFLOAT4 Color;
//};
//
//
//struct GCVERTEXTEXTURE
//{
//	DirectX::XMFLOAT3 Pos;
//	DirectX::XMFLOAT2 TexC; // Normal
//};
//
//
//
//struct GCGEOMETRY
//{
//	std::string name;
//	std::vector<GCVERTEX> vertices;
//	std::vector<std::uint16_t> indices;
//	SubmeshGeometry submesh;
//	std::unique_ptr<MeshGeometry> boxGeo;
//};
//
//struct GCGEOMETRYTEXTURE
//{
//	std::string name;
//	std::vector<GCVERTEXTEXTURE> vertices;
//	std::vector<std::uint16_t> indices;
//	SubmeshGeometry submesh;
//	std::unique_ptr<MeshGeometry> boxGeo;
//	//modif les structs
//};



class Render;

class PrimitiveFactory
{
public : 

	PrimitiveFactory();
	~PrimitiveFactory();
	void Initialize(int id, GCRender* pRender);

	GCGeometryColor* BuildGeometryColor();
	GCGeometryTexture* BuildGeometryTexture();

	GCGeometryColor* BuildBoxGeometryColor();
	GCGeometryTexture* BuildBoxGeometryTexture();
	GCGeometryTexture* BuildPlaneGeometryTexture();

	// 
	//void BuildSphereGeometry();
protected:

	int m_Id;
	//GCGEOMETRY m_BoxGeometry;
	//Geometry m_SphereGeometry;

	GCRender* m_pRender;
};

