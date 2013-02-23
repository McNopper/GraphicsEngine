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

    boost::uint32_t indicesOffset;
    boost::uint32_t storedIndices;
    boost::uint32_t triangleCount;

public:
	FbxSubMesh();
	virtual ~FbxSubMesh();

	void setIndicesOffset(boost::uint32_t indicesOffset);
	boost::uint32_t getAndIncreaseStoredIndices();

	void setTriangleCount(boost::uint32_t triangleCount);
	void increaseTriangleCount();

	boost::uint32_t getIndicesOffset() const;

	boost::uint32_t getTriangleCount() const;

};

typedef boost::shared_ptr<FbxSubMesh> FbxSubMeshSP;

#endif /* FBXSUBMESH_H_ */
