/*
 * Octant.cpp
 *
 *  Created on: 22.04.2011
 *      Author: Norbert Nopper
 */

#include "../../layer0/color/Color.h"
#include "../../layer1/command/WorkerManager.h"
#include "../../layer2/debug/DebugDraw.h"
#include "../../layer5/command/EntityCommandManager.h"

#include "Octree.h"

#include "Octant.h"

using namespace std;

Octant::Octant(Octree* octree) :
	AxisAlignedBoundingBox(Point4(), 0.0f, 0.0f, 0.0f), octree(octree), parent(0), level(0), maxLevels(0), allChilds(), allChildsPlusMe(), allOctreeEntities(), boundingSphere(), quicksortOctant(), quicksortOctreeEntity(), distanceToCamera(0.0f), debug(false)
{
	allChildsPlusMe.push_back(this);
}

Octant::~Octant()
{
	vector<Octant*>::iterator walker = allChilds.begin();
	while (walker != allChilds.end())
	{
		delete *walker;
		walker++;
	}
	allChilds.clear();
	allChildsPlusMe.clear();
	// Do not delete entities, as handled by the entity manager
	allOctreeEntities.clear();
}

void Octant::init(Octant* parent, uint32_t level, uint32_t maxLevels, const Point4& center, float halfWidth, float halfHeight, float halfDepth)
{
	this->center = center;
	this->halfWidth = halfWidth;
	this->halfHeight = halfHeight;
	this->halfDepth = halfDepth;
	this->parent = parent;
	this->level = level;
	this->maxLevels = maxLevels;

	if (parent)
	{
		this->debug = parent->debug;
	}

	boundingSphere.setCenter(center);
	boundingSphere.setRadius(Vector3(halfWidth, halfHeight, halfDepth).length());

	glusLogPrint(GLUS_LOG_DEBUG, "Creating octant level %u at center (%f/%f/%f)", level, center.getX(), center.getY(), center.getZ());
}

bool Octant::operator <=(const Octant& other) const
{
	return distanceToCamera <= other.distanceToCamera;
}

bool Octant::operator >=(const Octant& other) const
{
	return distanceToCamera >= other.distanceToCamera;
}

void Octant::sort()
{
	if (!OctreeEntity::getCurrentCamera()->getViewFrustum().isVisible(boundingSphere))
	{
		return;
	}

	vector<Octant*>::iterator walkerChildsPlusMe = allChildsPlusMe.begin();
	while (walkerChildsPlusMe != allChildsPlusMe.end())
	{
		(*walkerChildsPlusMe)->updateDistanceToCamera();

		// Sort children, if available
		if (*walkerChildsPlusMe != this)
		{
			(*walkerChildsPlusMe)->sort();
		}

		walkerChildsPlusMe++;
	}
	quicksortOctant.sort(allChildsPlusMe);

	auto walker = allOctreeEntities.begin();
	while (walker != allOctreeEntities.end())
	{
		(*walker)->updateDistanceToCamera();

		walker++;
	}
	quicksortOctreeEntity.sort(allOctreeEntities);
}

void Octant::update() const
{
	auto walker = allChildsPlusMe.begin();
	while (walker != allChildsPlusMe.end())
	{
		if (*walker == this)
		{
			updateEntities();
		}
		else
		{
			(*walker)->update();
		}
		walker++;
	}
}

void Octant::render(bool force) const
{
	if (!force && !OctreeEntity::getCurrentCamera()->getViewFrustum().isVisible(boundingSphere))
	{
		return;
	}

	if (OctreeEntity::isAscendingSortOrder())
	{
		auto walker = allChildsPlusMe.begin();
		while (walker != allChildsPlusMe.end())
		{
			if (*walker == this)
			{
				renderEntities(true, force);
			}
			else
			{
				(*walker)->render(force);
			}
			walker++;
		}
	}
	else
	{
		auto walker = allChildsPlusMe.rbegin();
		while (walker != allChildsPlusMe.rend())
		{
			if (*walker == this)
			{
				renderEntities(false, force);
			}
			else
			{
				(*walker)->render(force);
			}
			walker++;
		}
	}

	if (debug)
	{
		DebugDraw::drawer.draw(*this, Color::BLUE);
	}
}

void Octant::updateEntities() const
{
	auto walkerEntities = allOctreeEntities.begin();
	while (walkerEntities != allOctreeEntities.end())
	{
		if (WorkerManager::getInstance()->getNumberWorkers() == 0)
		{
			(*walkerEntities)->update();
		}
		else
		{
			EntityCommandManager::getInstance()->publishUpdateCommand((*walkerEntities).get());
		}

		walkerEntities++;
	}
}

void Octant::renderEntities(bool ascending, bool force) const
{
	if (ascending)
	{
		auto walkerEntities = allOctreeEntities.begin();
		while (walkerEntities != allOctreeEntities.end())
		{
			if ((force || OctreeEntity::getCurrentCamera()->getViewFrustum().isVisible((*walkerEntities)->getBoundingSphere())) && !octree->isEntityExcluded(*walkerEntities))
			{
				(*walkerEntities)->render();
			}

			walkerEntities++;
		}
	}
	else
	{
		auto walkerEntities = allOctreeEntities.rbegin();
		while (walkerEntities != allOctreeEntities.rend())
		{
			if ((force || OctreeEntity::getCurrentCamera()->getViewFrustum().isVisible((*walkerEntities)->getBoundingSphere())) && !octree->isEntityExcluded(*walkerEntities))
			{
				(*walkerEntities)->render();
			}

			walkerEntities++;
		}
	}
}

void Octant::updateDistanceToCamera()
{
	distanceToCamera = OctreeEntity::getCurrentCamera()->distanceToCamera(boundingSphere);
}

void Octant::createChilds()
{
	assert(octree != nullptr);
	assert(allChilds.size() == 0);

	if (level + 1 < maxLevels)
	{
		Point4 currentCenter;

		for (int32_t z = -1; z <= 1; z += 2)
		{
			for (int32_t y = -1; y <= 1; y += 2)
			{
				for (int32_t x = -1; x <= 1; x += 2)
				{
					currentCenter.setX(center.getX() + float(x) * halfWidth / 2.0f);
					currentCenter.setY(center.getY() + float(y) * halfHeight / 2.0f);
					currentCenter.setZ(center.getZ() + float(z) * halfDepth / 2.0f);

					Octant* currentOctant = octree->createOctant(this, level + 1, maxLevels, currentCenter, halfWidth / 2.0f, halfHeight / 2.0f, halfDepth / 2.0f);

					allChilds.push_back(currentOctant);
					allChildsPlusMe.push_back(currentOctant);
				}
			}
		}
	}

	// Not enough elements left
	if (allChilds.size() != 8)
	{
		releaseChilds();
	}
}

bool Octant::releaseChilds()
{
	assert(octree != nullptr);

	// Check if empty
	vector<Octant*>::iterator walker = allChilds.begin();
	while (walker != allChilds.end())
	{
		// If there is an entity or has own children - break and return.
		if ((*walker)->allOctreeEntities.size() > 0 || (*walker)->allChilds.size() > 0)
		{
			return false;
		}

		walker++;
	}

	walker = allChilds.begin();
	while (walker != allChilds.end())
	{
		octree->recycleOctant(*walker);

		walker++;
	}

	allChilds.clear();
	allChildsPlusMe.clear();
	allChildsPlusMe.push_back(this);
	// Own entities still there

	return true;
}

bool Octant::updateEntity(const OctreeEntitySP& octreeEntity)
{
	assert(octreeEntity.get() != nullptr);

	// Immediately return, if the bounding sphere does not fit
	if (!encloses(octreeEntity->getBoundingSphere()))
	{
		return false;
	}

	// Check, if we can make a finer level
	if (allChilds.size() == 0)
	{
		createChilds();
	}

	// It does fit, but first check, if we can get a finer adding
	vector<Octant*>::iterator walker = allChilds.begin();
	while (walker != allChilds.end())
	{
		if ((*walker)->updateEntity(octreeEntity))
		{
			return true;
		}

		walker++;
	}

	// If we did get so far, none of our children does enclose the bounding sphere

	// Check if nothing changed
	if (octreeEntity->getVisitingOctant() == this)
	{
		return true;
	}

	// Remove the entity
	if (octreeEntity->getVisitingOctant())
	{
		octreeEntity->getVisitingOctant()->removeEntity(octreeEntity);
	}

	// Add the entity
	octreeEntity->setVisitingOctant(this);
	allOctreeEntities.push_back(octreeEntity);

	glusLogPrint(GLUS_LOG_DEBUG, "Adding entity at level %u with center (%f/%f/%f)", level, center.getX(), center.getY(), center.getZ());

	return true;
}

void Octant::removeEntity(const OctreeEntitySP& octreeEntity)
{
	assert(octreeEntity.get() != nullptr);

	if (octreeEntity->getVisitingOctant() == this)
	{
		allOctreeEntities.erase(remove(allOctreeEntities.begin(), allOctreeEntities.end(), octreeEntity));
		octreeEntity->setVisitingOctant(0);
	}
	else if (octreeEntity->getVisitingOctant())
	{
		octreeEntity->getVisitingOctant()->removeEntity(octreeEntity);

		if (octreeEntity->getPreviousVisitingOctant())
		{
			octreeEntity->getPreviousVisitingOctant()->releaseChilds();
			octreeEntity->setPreviousVisitingOctant(0);
		}
	}
}

void Octant::removeAllEntities()
{
	vector<Octant*>::iterator walker = allChilds.begin();
	while (walker != allChilds.end())
	{
		(*walker)->removeAllEntities();
		walker++;
	}
	releaseChilds();

	allOctreeEntities.clear();
}

void Octant::setParent(Octant* octant)
{
	parent = octant;
}

Octant* Octant::getParent() const
{
	return parent;
}

Octree* Octant::getOctree() const
{
	return octree;
}

void Octant::setDebug(bool debug)
{
	vector<Octant*>::iterator walker = allChildsPlusMe.begin();
	while (walker != allChildsPlusMe.end())
	{
		if (*walker == this)
		{
			this->debug = debug;
		}
		else
		{
			(*walker)->setDebug(debug);
		}
		walker++;
	}
}
