/*
 * FbxSubMesh.h
 *
 *  Created on: 05.09.2012
 *      Author: nopper
 */

#ifndef FBXSUBMESH_H_
#define FBXSUBMESH_H_

#include "../../UsedLibs.h"

class FbxSubMesh
{

private:

    std::uint32_t indicesOffset;
    std::uint32_t storedIndices;
    std::uint32_t triangleCount;

public:
	FbxSubMesh();
	virtual ~FbxSubMesh();

	void setIndicesOffset(std::uint32_t indicesOffset);
	std::uint32_t getAndIncreaseStoredIndices();

	void setTriangleCount(std::uint32_t triangleCount);
	void increaseTriangleCount();

	std::uint32_t getIndicesOffset() const;

	std::uint32_t getTriangleCount() const;

};

typedef std::shared_ptr<FbxSubMesh> FbxSubMeshSP;

#endif /* FBXSUBMESH_H_ */
