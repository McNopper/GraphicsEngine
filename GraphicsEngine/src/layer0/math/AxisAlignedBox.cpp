/*
 * AxisAlignedBox.cpp
 *
 *  Created on: 23.04.2011
 *      Author: Norbert Nopper
 */

#include "AxisAlignedBox.h"

AxisAlignedBox::AxisAlignedBox() :
	center(), halfWidth(0.0f), halfHeight(0.0f), halfDepth(0.0f)
{
}

AxisAlignedBox::AxisAlignedBox(const Point4& center, float halfWidth, float halfHeight, float halfDepth) :
			center(center), halfWidth(halfWidth), halfHeight(halfHeight), halfDepth(halfDepth)
{
}

AxisAlignedBox::~AxisAlignedBox()
{
}

const Point4& AxisAlignedBox::getCenter() const
{
    return center;
}

void AxisAlignedBox::setCenter(const Point4& center)
{
    this->center = center;
}

float AxisAlignedBox::getHalfWidth() const
{
    return halfWidth;
}

void AxisAlignedBox::setHalfWidth(float halfWidth)
{
    this->halfWidth = halfWidth;
}

float AxisAlignedBox::getHalfHeight() const
{
    return halfHeight;
}

void AxisAlignedBox::setHalfHeight(float halfHeight)
{
    this->halfHeight = halfHeight;
}

float AxisAlignedBox::getHalfDepth() const
{
    return halfDepth;
}

void AxisAlignedBox::setHalfDepth(float halfDepth)
{
    this->halfDepth = halfDepth;
}
