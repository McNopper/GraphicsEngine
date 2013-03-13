/*
 * OrientedLinePath.cpp
 *
 *  Created on: 13.03.2013
 *      Author: nopper
 */

#include "OrientedLinePath.h"

OrientedLinePath::OrientedLinePath(const Quaternion& baseRotation, const Point4& startLocation, const Point4& endLocation) :
	LinePath(baseRotation, startLocation, endLocation)
{
}

OrientedLinePath::~OrientedLinePath()
{
}

void OrientedLinePath::start()
{
	LinePath::start();
}

bool OrientedLinePath::update(float deltaTime, Geometry& geometry, bool updateOrientation)
{
	bool result = LinePath::update(deltaTime, geometry, false);

	float rotY = -glusRadToDegf(asinf(direction.getX()));
	float rotX = glusRadToDegf(asinf(direction.getY()));

	Quaternion orientation;
	orientation.rotateRzRyRxf(0.0f, rotY, rotX);
	setOrientation(orientation * baseRotation);

	return result;
}

