/*
 * Octree.cpp
 *
 *  Created on: 22.04.2011
 *      Author: Norbert Nopper
 */

#include "Octree.h"

using namespace std;

Octree::Octree(uint32_t maxLevels, uint32_t maxElements, const Point4& center, float halfWidth, float halfHeight, float halfDepth):
	entityExcludeList()
{
	assert(maxElements > 0);

	Octant* walker = 0;

	pool = new Octant(this);

	walker = pool;

	for (uint32_t i = 1; i < maxElements; i++)
	{
		walker->setParent(new Octant(this));

		walker = walker->getParent();
	}

	root = createOctant(0, 0, maxLevels, center, halfWidth, halfHeight, halfDepth);
}

Octree::~Octree()
{
	delete root;

	Octant* walker = pool;
	while (walker)
	{
		pool = pool->getParent();

		delete walker;

		walker = pool;
	}
}

Octant* Octree::createOctant(Octant* parent, uint32_t level, uint32_t maxLevels, const Point4& center, float halfWidth, float halfHeight, float halfDepth)
{
	Octant* octant = pool;

	if (octant)
	{
		pool = octant->getParent();

		octant->init(parent, level, maxLevels, center, halfWidth, halfHeight, halfDepth);

		return octant;
	}

	return 0;
}

void Octree::recycleOctant(Octant* octant)
{
	if (octant)
	{
		octant->setParent(pool);

		pool = octant;
	}
}

bool Octree::updateEntity(const OctreeEntitySP& octreeEntity) const
{
	bool result = root->updateEntity(octreeEntity);

	if (!result && octreeEntity->getVisitingOctant())
	{
		glusLogPrint(GLUS_LOG_WARNING, "Entity does not fit into octree anymore.");

		octreeEntity->getVisitingOctant()->removeEntity(octreeEntity);
	}

	return result;
}

void Octree::removeEntity(const OctreeEntitySP& octreeEntity) const
{
	root->removeEntity(octreeEntity);
}

void Octree::removeAllEntities() const
{
	root->removeAllEntities();
}

void Octree::sort() const
{
	root->sort();
}

void Octree::update() const
{
	root->update();
}

void Octree::render(bool force) const
{
	root->render(force);
}

void Octree::setDebug(bool debug)
{
	root->setDebug(debug);
}

void Octree::setEntityExcludeList(const EntityListSP& entityExcludeList)
{
	this->entityExcludeList = entityExcludeList;
}

bool Octree::isEntityExcluded(const OctreeEntitySP& octreeEntity) const
{
	if (!entityExcludeList.get())
	{
		return false;
	}

	return entityExcludeList->containsEntity(octreeEntity);
}
