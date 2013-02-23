/*
 * AxisAlignedBoundingBox.h
 *
 *  Created on: 23.04.2011
 *      Author: Norbert Nopper
 */

#ifndef AXISALIGNEDBOUNDINGBOX_H_
#define AXISALIGNEDBOUNDINGBOX_H_

#include "../../layer0/math/AxisAlignedBox.h"
#include "../../layer0/math/Point4.h"
#include "BoundingSphere.h"

class AxisAlignedBoundingBox : public AxisAlignedBox
{

public:

	AxisAlignedBoundingBox();
	AxisAlignedBoundingBox(const Point4& center, float halfWidth, float halfHeight, float halfDepth);
	virtual ~AxisAlignedBoundingBox();

	bool intersect(const AxisAlignedBoundingBox& axisAlignedBoundingBox) const;

	bool encloses(const Point4& point) const;

	bool encloses(const AxisAlignedBoundingBox& axisAlignedBoundingBox) const;

	bool encloses(const BoundingSphere& boundingSphere) const;

	bool inside(const BoundingSphere& boundingSphere) const;

};

#endif /* AXISALIGNEDBOUNDINGBOX_H_ */
