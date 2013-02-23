/*
 * OctreeEntity.h
 *
 *  Created on: 23.04.2011
 *      Author: Norbert Nopper
 */

#ifndef OCTREEENTITY_H_
#define OCTREEENTITY_H_

#include "../../layer2/entity/Entity.h"

class Octant;

class OctreeEntity : public Entity
{

	friend class Octree;
	friend class Octant;

private:

	Octant* previousVisitingOctant;

	Octant* visitingOctant;

private:

	Octant* getPreviousVisitingOctant() const;
	void setPreviousVisitingOctant(Octant *previousVisitingOctant);

	Octant* getVisitingOctant() const;
	void setVisitingOctant(Octant *visitingOctant);

protected:

	OctreeEntity();
	virtual ~OctreeEntity();

public:

    bool operator <=(const OctreeEntity& other) const;
	bool operator >=(const OctreeEntity& other) const;

	bool insideVisitingOctant() const;

};

#endif /* OCTREEENTITY_H_ */
