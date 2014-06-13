/*
 * OctreeFactory.h
 *
 *  Created on: 22.04.2011
 *      Author: Norbert Nopper
 */

#ifndef OCTREEFACTORY_H_
#define OCTREEFACTORY_H_

#include "../../UsedLibs.h"

#include "../../layer0/math/Point4.h"
#include "Octree.h"

class OctreeFactory
{

public:

	OctreeFactory();
	virtual ~OctreeFactory();

	OctreeSP createOctree(std::uint32_t maxLevels, std::uint32_t maxElements, const Point4& center, float width, float height, float depth) const;

};

#endif /* OCTREEFACTORY_H_ */
