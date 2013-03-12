/*
 * LinePath.cpp
 *
 *  Created on: 12.03.2013
 *      Author: nopper
 */

#include "LinePath.h"

LinePath::LinePath(const Point4& startLocation, const Point4& endLocation) :
		Path(), startLocation(startLocation), endLocation(endLocation), direction(), goToEnd(true)
{
}

LinePath::~LinePath()
{
}

void LinePath::start()
{
	setLocation(startLocation);

	direction = (endLocation - startLocation).normalize();

	goToEnd = true;
}

bool LinePath::update(float deltaTime, Geometry& geometry)
{
	bool result = false;

	Point4 currentLocation = getLocation();

	if (goToEnd)
	{
		currentLocation += direction * getSpeed() * deltaTime;
	}
	else
	{
		currentLocation -= direction * getSpeed() * deltaTime;
	}

	float checkStart = (currentLocation - startLocation).dot(direction);

	bool reversed = false;

	if (checkStart < 0.0f)
	{
		if (isLooping())
		{
			currentLocation = startLocation - direction * checkStart;

			goToEnd = true;

			reversed = false;
		}
		else
		{
			currentLocation = startLocation;

			result = true;
		}
	}

	float checkEnd = (currentLocation - endLocation).dot(direction);

	if (checkEnd > 0.0f)
	{
		if (isLooping())
		{
			// Always keep inside, so check if we already did reverse
			if (!reversed)
			{
				currentLocation = endLocation - direction * checkEnd;
			}
			else
			{
				currentLocation = endLocation;
			}

			goToEnd = false;
		}
		else
		{
			currentLocation = endLocation;

			result = true;
		}
	}

	setLocation(currentLocation);

	return result;
}
