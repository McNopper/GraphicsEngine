/*
 * SubMesh.cpp
 *
 *  Created on: 29.05.2011
 *      Author: Norbert Nopper
 */

#include "SubMesh.h"

using namespace std;

SubMesh::SubMesh(uint32_t indicesOffset, uint32_t triangleCount) :
	indicesOffset(indicesOffset), triangleCount(triangleCount), allVAOs()
{
}

SubMesh::~SubMesh()
{
	map<string, SubMeshVAOSP>::iterator walker = allVAOs.begin();
	while (walker != allVAOs.end())
	{
		walker->second.reset();

		walker++;
	}
	allVAOs.clear();
}

uint32_t SubMesh::getIndicesOffset() const
{
	return indicesOffset;
}

uint32_t SubMesh::getTriangleCount() const
{
	return triangleCount;
}

void SubMesh::addVAO(const SubMeshVAOSP& vao)
{
	allVAOs[vao->getProgramType()] = vao;
}

bool SubMesh::containsVAOByProgramType(const string& type) const
{
	return allVAOs.find(type) != allVAOs.end();
}

const SubMeshVAOSP& SubMesh::getVAOByProgramType(const string& type) const
{
	return allVAOs.at(type);
}
