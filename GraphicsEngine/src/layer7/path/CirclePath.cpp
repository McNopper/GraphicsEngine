/*
 * CirclePath.cpp
 *
 *  Created on: 13.03.2013
 *      Author: nopper
 */

#include "CirclePath.h"

CirclePath::CirclePath(const Quaternion& baseRotation, const Point4& startPosition, const Point4& orbitPosition, bool clockWise) :
		Path(baseRotation), startPosition(startPosition), orbitPosition(orbitPosition), clockWise(clockWise)
{
	Vector3 orbitDirection = orbitPosition - startPosition;

	radius = orbitDirection.length();

	orbitDirection = orbitDirection.normalize();

	//

	rotationAxis = Vector3(1.0f, 0.0f, 0.0f).cross(orbitDirection);

	if (rotationAxis.length() == 0.0f)
	{
		rotationAxis = Vector3(0.0f, 1.0f, 0.0f);
	}

	elapsedAngle = 0.0f;
}

CirclePath::CirclePath(const Quaternion& baseRotation, const Point4& startPosition, const Point4& orbitPosition, bool clockWise, const Vector3& rotationAxis) :
		Path(baseRotation), startPosition(startPosition), orbitPosition(orbitPosition), clockWise(clockWise)
{
	Vector3 orbitDirection = orbitPosition - startPosition;

	radius = orbitDirection.length();

	orbitDirection = orbitDirection.normalize();

	//

	Vector3 normalizedRotationAxis = rotationAxis.normalize();

	Vector3 testAxis = orbitDirection.cross(normalizedRotationAxis);

	if (testAxis.length() == 0.0f)
	{
		testAxis = Vector3(1.0f, 0.0f, 0.0f).cross(orbitDirection);

		if (testAxis.length() == 0.0f)
		{
			this->rotationAxis = Vector3(0.0f, 1.0f, 0.0f);
		}
		else
		{
			this->rotationAxis = testAxis;
		}
	}
	else
	{
		this->rotationAxis = rotationAxis;
	}

	elapsedAngle = 0.0f;
}

CirclePath::~CirclePath()
{
}

float CirclePath::updateTransform()
{
	float pathLength = 2.0f * GLUS_PI * radius;

	if (pathLength == 0.0f)
	{
		return 0.0f;
	}

	float elapsedPath = getSpeed() * getElapsedTime();

	elapsedAngle = 360.0f * elapsedPath / pathLength;

	if (clockWise)
	{
		elapsedAngle = -elapsedAngle;
	}

	transform.identity();
	transform.translate(orbitPosition.getX(), orbitPosition.getY(), orbitPosition.getZ());
	Quaternion rotation(elapsedAngle, rotationAxis);
	transform *= rotation.getRotationMatrix4x4();
	transform.translate(-orbitPosition.getX(), -orbitPosition.getY(), -orbitPosition.getZ());

	return elapsedAngle;
}

void CirclePath::start()
{
	setPosition(startPosition);
}

bool CirclePath::update(float deltaTime, const GeneralEntitySP& entity, bool updateRotation)
{
	float elapsedAngle= updateTransform();

	if (!isLooping() && elapsedAngle >= 360.0f)
	{
		setPosition(startPosition);

		if (updateRotation)
		{
			setRotation(baseRotation);
		}

		return true;
	}

	setPosition(transform * startPosition);

	if (updateRotation)
	{
		setRotation(baseRotation);
	}

	return false;
}
