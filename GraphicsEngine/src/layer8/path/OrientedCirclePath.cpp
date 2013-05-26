/*
 * OrientedCirclePath.cpp
 *
 *  Created on: 13.03.2013
 *      Author: nopper
 */

#include "OrientedCirclePath.h"

OrientedCirclePath::OrientedCirclePath(const Quaternion& baseRotation, const Point4& startPosition, const Point4& orbitPosition, bool clockWise) :
		CirclePath(baseRotation, startPosition, orbitPosition, clockWise)
{
}

OrientedCirclePath::OrientedCirclePath(const Quaternion& baseRotation, const Point4& startPosition, const Point4& orbitPosition, bool clockWise, const Vector3& rotationAxis) :
		CirclePath(baseRotation, startPosition, orbitPosition, clockWise, rotationAxis)
{
}

OrientedCirclePath::~OrientedCirclePath()
{
}

void OrientedCirclePath::start()
{
	CirclePath::start();

	Quaternion rotation(elapsedAngle, rotationAxis);

	setRotation(rotation * baseRotation);
}

bool OrientedCirclePath::update(float deltaTime, const GeneralEntitySP& entity, bool updateRotation)
{
	bool result = CirclePath::update(deltaTime, entity, false);

	Quaternion rotation(elapsedAngle, rotationAxis);

	setRotation(rotation * baseRotation);

	return result;
}
