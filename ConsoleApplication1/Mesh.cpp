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
