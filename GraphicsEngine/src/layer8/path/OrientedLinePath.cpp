/*
 * OrientedLinePath.cpp
 *
 *  Created on: 13.03.2013
 *      Author: nopper
 */

#include "OrientedLinePath.h"

OrientedLinePath::OrientedLinePath(const Quaternion& baseRotation, const Point4& startPosition, const Point4& endPosition) :
	LinePath(baseRotation, startPosition, endPosition)
{
}

OrientedLinePath::~OrientedLinePath()
{
}

void OrientedLinePath::start()
{
	LinePath::start();
}

bool OrientedLinePath::update(float deltaTime, const GeneralEntitySP& entity, bool updateRotation)
{
	bool result = LinePath::update(deltaTime, entity, false);

	float rotY = -glusMathRadToDegf(asinf(direction.getX()));
	float rotX = glusMathRadToDegf(asinf(direction.getY()));

	Quaternion rotation;
	rotation.rotateRzRyRxf(0.0f, rotY, rotX);
	setRotation(rotation * baseRotation);

	return result;
}

