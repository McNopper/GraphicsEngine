/*
 * ConeShape.cpp
 *
 *  Created on: 09.11.2012
 *      Author: nopper
 */

#include "ConeShape.h"

using namespace boost;

ConeShape::ConeShape(float halfExtend, float radius, uint32_t numberSlices, uint32_t numberStacks) : Shape()
{
	glusCreateConef(&shape, halfExtend, radius, numberSlices, numberStacks);
}

ConeShape::~ConeShape()
{
}
