/*
 * DomeShape.cpp
 *
 *  Created on: 09.11.2012
 *      Author: nopper
 */

#include "DomeShape.h"

using namespace boost;

DomeShape::DomeShape(float radius, uint32_t numberSlices) : Shape()
{
	glusCreateDomef(&shape, radius, numberSlices);
}

DomeShape::~DomeShape()
{
}

