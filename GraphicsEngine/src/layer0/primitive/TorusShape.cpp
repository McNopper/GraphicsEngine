/*
 * TorusShape.cpp
 *
 *  Created on: 09.11.2012
 *      Author: nopper
 */

#include "TorusShape.h"

using namespace std;

TorusShape::TorusShape(float innerRadius, float outerRadius, uint32_t numberSlices, uint32_t numberStacks) : Shape()
{
	glusShapeCreateTorusf(&shape, innerRadius, outerRadius, numberSlices, numberStacks);
}

TorusShape::~TorusShape()
{
}
