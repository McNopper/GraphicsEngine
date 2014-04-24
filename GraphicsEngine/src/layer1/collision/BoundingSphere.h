/*
 * BoundingSphere.h
 *
 *  Created on: 22.04.2011
 *      Author: Norbert Nopper
 */

#ifndef BOUNDINGSPHERE_H_
#define BOUNDINGSPHERE_H_

#include "../../layer0/math/Point4.h"
#include "../../layer0/math/Sphere.h"

class AxisAlignedBoundingBox;

class BoundingSphere: public Sphere
{

public:

	BoundingSphere();
	BoundingSphere(const Point4& center, float radius);
	virtual ~BoundingSphere();

	bool intersect(const BoundingSphere& boundingSphere) const;

	bool encloses(const Point4& point) const;

	bool encloses(const BoundingSphere& boundingSphere) const;

	bool encloses(const AxisAlignedBoundingBox& axisAlignedBox) const;

	bool inside(const AxisAlignedBoundingBox& axisAlignedBox) const;

};

#endif /* BOUNDINGSPHERE_H_ */
