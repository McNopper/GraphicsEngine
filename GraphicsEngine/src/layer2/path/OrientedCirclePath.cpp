/*
 * OrientedCirclePath.cpp
 *
 *  Created on: 13.03.2013
 *      Author: nopper
 */

#include "OrientedCirclePath.h"

OrientedCirclePath::OrientedCirclePath(const Quaternion& baseRotation, const Point4& startLocation, const Point4& orbitPoint, bool clockWise) :
	CirclePath(baseRotation, startLocation, orbitPoint, clockWise)
{
}

OrientedCirclePath::~OrientedCirclePath()
{
}

void OrientedCirclePath::start()
{
	CirclePath::start();

	Quaternion orientation(elapsedAngle, rotationAxis);

	setOrientation(orientation * baseRotation);
}

bool OrientedCirclePath::update(float deltaTime, Geometry& geometry, bool updateOrientation)
{
	bool result = CirclePath::update(deltaTime, geometry, false);

	Quaternion orientation(elapsedAngle, rotationAxis);

	setOrientation(orientation * baseRotation);

	return result;
}
