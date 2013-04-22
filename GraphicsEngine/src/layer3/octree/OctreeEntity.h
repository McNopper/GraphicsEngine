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
	friend void boost::checked_delete<OctreeEntity>(OctreeEntity* x);

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

	bool insideVisitingOctant() const;

};

typedef boost::shared_ptr<OctreeEntity> OctreeEntitySP;

#endif /* OCTREEENTITY_H_ */
