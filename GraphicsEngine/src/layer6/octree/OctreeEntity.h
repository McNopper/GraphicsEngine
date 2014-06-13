/*
 * OctreeEntity.h
 *
 *  Created on: 23.04.2011
 *      Author: Norbert Nopper
 */

#ifndef OCTREEENTITY_H_
#define OCTREEENTITY_H_

#include "../../layer4/entity/Entity.h"

class Octant;

class OctreeEntity : public Entity
{

	friend class Octree;
	friend class Octant;

private:

	Octant* previousVisitingOctant;

	Octant* visitingOctant;

	Octant* getPreviousVisitingOctant() const;
	void setPreviousVisitingOctant(Octant *previousVisitingOctant);

	Octant* getVisitingOctant() const;
	void setVisitingOctant(Octant *visitingOctant);

protected:

	OctreeEntity();
	virtual ~OctreeEntity();

public:

	bool insideVisitingOctant() const;

};

typedef std::shared_ptr<OctreeEntity> OctreeEntitySP;

#endif /* OCTREEENTITY_H_ */
