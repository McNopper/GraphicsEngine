/*
 * AxisAlignedBoundingBox.cpp
 *
 *  Created on: 23.04.2011
 *      Author: Norbert Nopper
 */

#include "../../UsedLibs.h"

#include "AxisAlignedBoundingBox.h"

AxisAlignedBoundingBox::AxisAlignedBoundingBox() :
	AxisAlignedBox()
{
}

AxisAlignedBoundingBox::AxisAlignedBoundingBox(const Point4& center, float halfWidth, float halfHeight, float halfDepth) :
	AxisAlignedBox(center, halfWidth, halfHeight, halfDepth)
{
}

AxisAlignedBoundingBox::~AxisAlignedBoundingBox()
{
}

bool AxisAlignedBoundingBox::intersect(const AxisAlignedBoundingBox& axisAlignedBoundingBox) const
{
	float xDistance = fabs(center.getX() - axisAlignedBoundingBox.center.getX()) - halfWidth - axisAlignedBoundingBox.halfWidth;
	if (xDistance > 0.0f)
	{
		return false;
	}

	float yDistance = fabs(center.getY() - axisAlignedBoundingBox.center.getY()) - halfHeight - axisAlignedBoundingBox.halfHeight;
	if (yDistance > 0.0f)
	{
		return false;
	}

	float zDistance = fabs(center.getZ() - axisAlignedBoundingBox.center.getZ()) - halfDepth - axisAlignedBoundingBox.halfDepth;
	if (zDistance > 0.0f)
	{
		return false;
	}

	return true;
}

bool AxisAlignedBoundingBox::encloses(const Point4& point) const
{
	return (point.getX() <= center.getX() + halfWidth) &&
		   (point.getX() >= center.getX() - halfWidth) &&
		   (point.getY() <= center.getY() + halfHeight) &&
		   (point.getY() >= center.getY() - halfHeight) &&
		   (point.getZ() <= center.getZ() + halfDepth) &&
		   (point.getZ() >= center.getZ() - halfDepth);
}

bool AxisAlignedBoundingBox::encloses(const AxisAlignedBoundingBox& axisAlignedBoundingBox) const
{
	float xDistance = halfWidth - (fabs(center.getX() - axisAlignedBoundingBox.center.getX()) + axisAlignedBoundingBox.halfWidth);
	if (xDistance < 0.0f)
	{
		return false;
	}

	float yDistance = halfHeight - (fabs(center.getY() - axisAlignedBoundingBox.center.getY()) + axisAlignedBoundingBox.halfHeight);
	if (yDistance < 0.0f)
	{
		return false;
	}

	float zDistance = halfDepth - (fabs(center.getZ() - axisAlignedBoundingBox.center.getZ()) + axisAlignedBoundingBox.halfDepth);
	if (zDistance < 0.0f)
	{
		return false;
	}

	return true;
}

bool AxisAlignedBoundingBox::encloses(const BoundingSphere& boundingSphere) const
{
	return (boundingSphere.getCenter().getX() + boundingSphere.getRadius() <= center.getX() + halfWidth) &&
		   (boundingSphere.getCenter().getX() - boundingSphere.getRadius() >= center.getX() - halfWidth) &&
		   (boundingSphere.getCenter().getY() + boundingSphere.getRadius() <= center.getY() + halfHeight) &&
		   (boundingSphere.getCenter().getY() - boundingSphere.getRadius() >= center.getY() - halfHeight) &&
		   (boundingSphere.getCenter().getZ() + boundingSphere.getRadius() <= center.getZ() + halfDepth) &&
		   (boundingSphere.getCenter().getZ() - boundingSphere.getRadius() >= center.getZ() - halfDepth);
}

bool AxisAlignedBoundingBox::inside(const BoundingSphere& boundingSphere) const
{
	return boundingSphere.encloses(*this);
}
