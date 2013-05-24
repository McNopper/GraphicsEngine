/*
 * SubMesh.h
 *
 *  Created on: 29.05.2011
 *      Author: Norbert Nopper
 */

#ifndef SUBMESH_H_
#define SUBMESH_H_

#include "../../UsedLibs.h"

#include "SubMeshVAO.h"

class SubMesh
{

	friend class Mesh;
	friend class MeshFactory;

private:

    boost::uint32_t indicesOffset;
    boost::uint32_t triangleCount;

	std::map<std::string, SubMeshVAOSP> allVAOs;

	void addVAO(const SubMeshVAOSP& vao);

public:

	SubMesh(boost::uint32_t indicesOffset, boost::uint32_t triangleCount);

	virtual ~SubMesh();

	boost::uint32_t getIndicesOffset() const;

	boost::uint32_t getTriangleCount() const;

	bool containsVAOByProgramType(const std::string& type) const;

	const SubMeshVAOSP& getVAOByProgramType(const std::string& type) const;

};

typedef boost::shared_ptr<SubMesh> SubMeshSP;

#endif /* SUBMESH_H_ */
