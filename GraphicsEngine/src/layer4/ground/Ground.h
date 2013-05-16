/*
 * Ground.h
 *
 *  Created on: 16.05.2013
 *      Author: nopper
 */

#ifndef GROUND_H_
#define GROUND_H_

#include "../../UsedLibs.h"

#include "../../layer1/collision/BoundingSphere.h"

class Ground
{

private:

	BoundingSphere boundingSphere;

public:

	// TODO Pass ground plane.
	Ground(const BoundingSphere& boundingSphere);
	virtual ~Ground();

	const BoundingSphere& getBoundingSphere() const;

};

typedef boost::shared_ptr<Ground> GroundSP;

#endif /* GROUND_H_ */
