/*
 * Box.h
 *
 *  Created on: 23.04.2011
 *      Author: Norbert Nopper
 */

#ifndef AXISALIGNEDBOX_H_
#define AXISALIGNEDBOX_H_

#include "Point4.h"

class AxisAlignedBox
{

protected:

	Point4 center;

	float halfWidth;
	float halfHeight;
	float halfDepth;

public:

	AxisAlignedBox();
	AxisAlignedBox(const Point4& center, float halfWidth, float halfHeight, float halfDepth);
	virtual ~AxisAlignedBox();

    const Point4& getCenter() const;
    void setCenter(const Point4& center);
    float getHalfWidth() const;
    void setHalfWidth(float halfWidth);
    float getHalfHeight() const;
    void setHalfHeight(float halfHeight);
    float getHalfDepth() const;
    void setHalfDepth(float halfDepth);

};

#endif /* AXISALIGNEDBOX_H_ */
