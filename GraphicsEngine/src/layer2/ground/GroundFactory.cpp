/*
 * GroundFactory.cpp
 *
 *  Created on: 18.05.2013
 *      Author: nopper
 */

#include "../../layer0/math/Point4.h"
#include "../../layer0/primitive/GridPlaneShape.h"
#include "../../layer1/collision/BoundingSphere.h"

#include "GroundFactory.h"

using namespace std;

GroundFactory::GroundFactory()
{
}

GroundFactory::~GroundFactory()
{
}

GroundSP GroundFactory::createGround(float horizontalExtend, float verticalExtend, uint32_t rows, uint32_t columns) const
{
	float radius = glusMathLengthf(horizontalExtend / 2.0f, verticalExtend / 2.0f, 0.0f);

	BoundingSphere boundingSphere(Point4(), radius);

	GridPlaneShape gridPlaneShape(horizontalExtend, verticalExtend, rows, columns);

	return GroundSP(new Ground(boundingSphere, gridPlaneShape));
}
