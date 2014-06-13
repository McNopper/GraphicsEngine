/*
 * MeshFactory.cpp
 *
 *  Created on: 04.09.2012
 *      Author: nopper
 */

#include "../../layer1/shader/Program.h"
#include "../../layer1/shader/ProgramManager.h"
#include "../../layer2/material/SurfaceMaterialFactory.h"
#include "SubMeshVAO.h"

#include "MeshFactory.h"

using namespace std;

MeshFactory::MeshFactory()
{
}

MeshFactory::~MeshFactory()
{
}

MeshSP MeshFactory::createMesh(const string& name, const GLUSshape& shape, const SurfaceMaterialSP& surfaceMaterial) const
{
	SurfaceMaterialFactory surfaceMaterialFactory;

	std::map<int32_t, SubMeshSP> subMeshes;
	subMeshes[0] = SubMeshSP(new SubMesh(0, shape.numberIndices / 3));

	std::map<int32_t, SurfaceMaterialSP> surfaceMaterials;
	surfaceMaterials[0] = surfaceMaterial;

	MeshSP mesh = MeshSP(new Mesh(name, shape.numberVertices, shape.vertices, shape.normals, shape.bitangents, shape.tangents, shape.texCoords, shape.numberIndices, shape.indices, subMeshes, surfaceMaterials));

	return mesh;
}
