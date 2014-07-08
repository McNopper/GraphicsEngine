/*
 * GlTfMesh.h
 *
 *  Created on: 07.07.2014
 *      Author: nopper
 */

#ifndef GLTFMESH_H_
#define GLTFMESH_H_

#include "../../UsedLibs.h"

#include "GlTfPrimitive.h"

class GlTfMesh
{

private:

	std::string name;

	std::vector<GlTfPrimitiveSP> allPrimitives;

public:

	GlTfMesh(const std::string& name);
	virtual ~GlTfMesh();

	const std::string& getName() const;

	void addPrimitive(const GlTfPrimitiveSP& primitive);

	const std::vector<GlTfPrimitiveSP>& getAllPrimitives() const;

};

typedef std::shared_ptr<GlTfMesh> GlTfMeshSP;

#endif /* GLTFMESH_H_ */
