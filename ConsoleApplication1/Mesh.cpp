#include "Mesh.h"
Mesh::Mesh() {
}

Mesh::~Mesh() {
}

void Mesh::CreateBoxGeometry() 
{
	PrimitiveFactory* factory = new PrimitiveFactory();
	factory->Initialize(0);
	m_boxGeometry = factory->GetGeometry();
	m_boxGeometry->boxGeo->DrawArgs["box"] = m_boxGeometry->submesh;


}

void Mesh::CreateBoxGeometryTex()
{
	PrimitiveFactory* factory = new PrimitiveFactory();
	factory->Initialize(0);
	m_boxGeometryTex = factory->GetGeometryTexture();
	m_boxGeometryTex->boxGeo->DrawArgs["box"] = m_boxGeometryTex->submesh;


}

