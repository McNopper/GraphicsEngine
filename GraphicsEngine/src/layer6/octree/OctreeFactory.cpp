/*
 * OctreeFactory.cpp
 *
 *  Created on: 22.04.2011
 *      Author: Norbert Nopper
 */

#include "../../UsedLibs.h"

#include "OctreeFactory.h"

using namespace std;

OctreeFactory::OctreeFactory()
{
}

OctreeFactory::~OctreeFactory()
{
}

OctreeSP OctreeFactory::createOctree(uint32_t maxLevels, uint32_t maxElements, const Point4& center, float width, float height, float depth) const
{
	return OctreeSP(new Octree(maxLevels, maxElements, center, width / 2.0f, height / 2.0f, depth / 2.0f), std::default_delete<Octree>());
}


