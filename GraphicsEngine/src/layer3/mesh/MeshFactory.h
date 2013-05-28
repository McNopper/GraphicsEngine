/*
 * MeshFactory.h
 *
 *  Created on: 04.09.2012
 *      Author: nopper
 */

#ifndef MESHFACTORY_H_
#define MESHFACTORY_H_

#include "../../UsedLibs.h"

#include "../../layer0/color/Color.h"
#include "../../layer2/material/SurfaceMaterial.h"
#include "Mesh.h"
#include "SubMesh.h"

class MeshFactory
{

public:

	MeshFactory();
	virtual ~MeshFactory();

	MeshSP createMesh(const std::string& name, const GLUSshape& shape, const SurfaceMaterialSP& surfaceMaterial) const;

};

#endif /* MESHFACTORY_H_ */
