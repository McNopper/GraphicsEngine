/*
 * GridPlaneShape.cpp
 *
 *  Created on: 09.05.2013
 *      Author: nopper
 */

#include "GridPlaneShape.h"

using namespace boost;

GridPlaneShape::GridPlaneShape(float horizontalExtend, float verticalExtend, uint32_t rows, uint32_t columns) :
		Shape()
{
	glusCreateRectangularGridPlanef(&shape, horizontalExtend, verticalExtend, rows, columns, GLUS_FALSE);
}

GridPlaneShape::~GridPlaneShape()
{
}

