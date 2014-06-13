/*
 * FbxSubMesh.cpp
 *
 *  Created on: 05.09.2012
 *      Author: nopper
 */

#include "FbxSubMesh.h"

using namespace std;

FbxSubMesh::FbxSubMesh() : indicesOffset(0), storedIndices(0), triangleCount(0)
{
}

FbxSubMesh::~FbxSubMesh()
{
}

void FbxSubMesh::setIndicesOffset(uint32_t indicesOffset)
{
	this->indicesOffset = indicesOffset;
}

uint32_t FbxSubMesh::getAndIncreaseStoredIndices()
{
	uint32_t result = storedIndices;

	storedIndices += 3;

	return result;
}

void FbxSubMesh::setTriangleCount(uint32_t triangleCount)
{
	this->triangleCount = triangleCount;
}

void FbxSubMesh::increaseTriangleCount()
{
	triangleCount++;
}

uint32_t FbxSubMesh::getIndicesOffset() const
{
	return indicesOffset;
}

uint32_t FbxSubMesh::getTriangleCount() const
{
	return triangleCount;
}

