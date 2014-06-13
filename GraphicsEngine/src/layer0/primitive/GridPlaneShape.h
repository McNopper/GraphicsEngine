/*
 * GridPlaneSape.h
 *
 *  Created on: 09.05.2013
 *      Author: nopper
 */

#ifndef GRIDPLANESHAPE_H_
#define GRIDPLANESHAPE_H_

#include "Shape.h"

class GridPlaneShape : public Shape
{
public:
	GridPlaneShape(float horizontalExtend, float verticalExtend, std::uint32_t rows, std::uint32_t columns);
	virtual ~GridPlaneShape();
};

#endif /* GRIDPLANESHAPE_H_ */
