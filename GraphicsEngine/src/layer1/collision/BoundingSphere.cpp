/*
 * BoundingSphere.cpp
 *
 *  Created on: 22.04.2011
 *      Author: Norbert Nopper
 */

#include "../../UsedLibs.h"

#include "AxisAlignedBoundingBox.h"

#include "BoundingSphere.h"

BoundingSphere::BoundingSphere() :
	Sphere()
{
}

BoundingSphere::BoundingSphere(const Point4& center, float radius) :
	Sphere(center, radius)
{
}

BoundingSphere::~BoundingSphere()
{
}

bool BoundingSphere::intersect(const BoundingSphere & boundingSphere) const
{
	return center.distance(boundingSphere.center) <= radius + boundingSphere.radius;
}

bool BoundingSphere::encloses(const Point4& point) const
{
	return center.distance(point) <= radius;
}

bool BoundingSphere::encloses(const BoundingSphere& boundingSphere) const
{
	return center.distance(boundingSphere.center) + boundingSphere.radius <= radius;
}

bool BoundingSphere::encloses(const AxisAlignedBoundingBox& axisAlignedBox) const
{
	float halfDiagonal = glusLengthf(axisAlignedBox.getHalfWidth(), axisAlignedBox.getHalfHeight(), axisAlignedBox.getHalfDepth());

	float distance = center.distance(axisAlignedBox.getCenter());

	return distance + halfDiagonal <= radius;
}

bool BoundingSphere::inside(const AxisAlignedBoundingBox& axisAlignedBox) const
{
	return axisAlignedBox.encloses(*this);
}

bool BoundingSphere::save(FILE* f) const
{
	if (!f)
	{
		return false;
	}

	if (fprintf(f, "BoubdingSphere\n\n") < 0)
	{
		return false;
	}

	if (!Sphere::save(f))
	{
		return false;
	}

	return true;
}
