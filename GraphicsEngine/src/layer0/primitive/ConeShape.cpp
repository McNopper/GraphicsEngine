/*
 * ConeShape.cpp
 *
 *  Created on: 09.11.2012
 *      Author: nopper
 */

#include "ConeShape.h"

using namespace std;

ConeShape::ConeShape(float halfExtend, float radius, uint32_t numberSlices, uint32_t numberStacks) : Shape()
{
	glusShapeCreateConef(&shape, halfExtend, radius, numberSlices, numberStacks);
}

ConeShape::~ConeShape()
{
}
