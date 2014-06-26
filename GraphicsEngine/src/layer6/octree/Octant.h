/*
 * Octant.h
 *
 *  Created on: 22.04.2011
 *      Author: Norbert Nopper
 */

#ifndef OCTANT_H_
#define OCTANT_H_

#include "../../UsedLibs.h"

#include "../../layer0/algorithm/QuicksortPointer.h"
#include "../../layer0/math/Point4.h"
#include "../../layer1/collision/AxisAlignedBoundingBox.h"
#include "../../layer1/collision/BoundingSphere.h"
#include "../../layer3/camera/Camera.h"
#include "OctreeEntity.h"

class Octree;

class Octant : public AxisAlignedBoundingBox
{

	friend class Octree;

private:

	Octree* octree;

	Octant* parent;

	std::uint32_t level;
	std::uint32_t maxLevels;

	std::vector<Octant*> allChilds;
	std::vector<Octant*> allChildsPlusMe;

	std::vector<OctreeEntitySP> allOctreeEntities;

	BoundingSphere boundingSphere;

	QuicksortPointer<Octant*> quicksortOctant;
	QuicksortPointer<OctreeEntitySP> quicksortOctreeEntity;

	float distanceToCamera;

	bool debug;

private:

	Octant(Octree* octree);
	virtual ~Octant();

	void init(Octant* parent, std::uint32_t level, std::uint32_t numberLevels, const Point4& center, float halfWidth, float halfHeight, float halfDepth);

	void createChilds();

	bool releaseChilds();

	bool updateEntity(const OctreeEntitySP& octreeEntity);

	void removeEntity(const OctreeEntitySP& octreeEntity);

	void removeAllEntities();

	void setParent(Octant* octant);

	Octant* getParent() const;

	Octree* getOctree() const;

	void sort();

	void update() const;

	void render(bool force = false) const;

	void updateEntities() const;

	void renderEntities(bool ascending, bool force = false) const;

	void updateDistanceToCamera();

public:

    bool operator <=(const Octant& other) const;

	bool operator >=(const Octant& other) const;

	void setDebug(bool debug);

};

#endif /* OCTANT_H_ */
