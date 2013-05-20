/*
 * LinePath.cpp
 *
 *  Created on: 12.03.2013
 *      Author: nopper
 */

#include "LinePath.h"

LinePath::LinePath(const Quaternion& baseRotation, const Point4& startPosition, const Point4& endPosition) :
		Path(baseRotation), startPosition(startPosition), endPosition(endPosition), direction(), goToEnd(true)
{
}

LinePath::~LinePath()
{
}

void LinePath::start()
{
	setPosition(startPosition);

	direction = (endPosition - startPosition).normalize();

	goToEnd = true;
}

bool LinePath::update(float deltaTime, const GeneralEntitySP& entity, bool updateRotation)
{
	bool result = false;

	Point4 currentPosition = getPosition();

	if (goToEnd)
	{
		currentPosition += direction * getSpeed() * deltaTime;
	}
	else
	{
		currentPosition -= direction * getSpeed() * deltaTime;
	}

	float checkStart = (currentPosition - startPosition).dot(direction);

	bool reversed = false;

	if (checkStart < 0.0f)
	{
		if (isLooping())
		{
			currentPosition = startPosition - direction * checkStart;

			goToEnd = true;

			reversed = false;
		}
		else
		{
			currentPosition = startPosition;

			result = true;
		}
	}

	float checkEnd = (currentPosition - endPosition).dot(direction);

	if (checkEnd > 0.0f)
	{
		if (isLooping())
		{
			// Always keep inside, so check if we already did reverse
			if (!reversed)
			{
				currentPosition = endPosition - direction * checkEnd;
			}
			else
			{
				currentPosition = endPosition;
			}

			goToEnd = false;
		}
		else
		{
			currentPosition = endPosition;

			result = true;
		}
	}

	setPosition(currentPosition);

	if (updateRotation)
	{
		setRotation(baseRotation);
	}

	return result;
}
