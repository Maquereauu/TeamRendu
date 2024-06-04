#include "Mesh.h"
#include "PrimitiveFactory.h"

Mesh::Mesh() {
}

Mesh::~Mesh() {
}

void Mesh::CreateBoxGeometry() 
{
	PrimitiveFactory factory;
	factory.Initialize(0);
	Geometry boxGeometry = factory.GetGeometry();

	boxGeometry.boxGeo->DrawArgs["box"] = boxGeometry.submesh;
}