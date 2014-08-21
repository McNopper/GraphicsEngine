/*
 * SphereShape.cpp
 *
 *  Created on: 07.11.2012
 *      Author: nopper
 */

#include "SphereShape.h"

using namespace std;

SphereShape::SphereShape(float radius, uint32_t numberSlices) : Shape()
{
	glusShapeCreateSpheref(&shape, radius, numberSlices);
}

SphereShape::~SphereShape()
{
}
