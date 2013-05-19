/*
 * Path.cpp
 *
 *  Created on: 11.03.2013
 *      Author: nopper
 */

#include "Path.h"

Path::Path(const Quaternion& baseRotation) :
	baseRotation(baseRotation), paused(true), looping(false), ended(false), elapsedTime(0.0f), speed(1.0f), location(), orientation()
{
}

Path::~Path()
{
}

void Path::startPath()
{
	paused = false;
	ended = false;

	elapsedTime = 0.0f;

	start();
}

void Path::stopPath()
{
	paused = true;
}

void Path::continuePath()
{
	paused = false;
}

bool Path::updatePath(float deltaTime, const GeneralEntitySP& entity)
{
	if (!paused && !ended)
	{
		elapsedTime += deltaTime;

		ended = update(deltaTime, entity);
	}

	return ended;
}

bool Path::isPaused() const
{
	return paused;
}

bool Path::isLooping() const
{
	return looping;
}

void Path::setLooping(bool looping)
{
	this->looping = looping;

	ended = (ended && !looping);
}

bool Path::isEnded() const
{
	return ended;
}

float Path::getElapsedTime() const
{
	return elapsedTime;
}

const Point4& Path::getLocation() const
{
	return location;
}

void Path::setLocation(const Point4& location)
{
	this->location = location;
}

void Path::setOrientation(const Quaternion& orientation)
{
	this->orientation = orientation;
}

const Quaternion& Path::getOrientation() const
{
	return orientation;
}

float Path::getSpeed() const
{
	return speed;
}

void Path::setSpeed(float speed)
{
	this->speed = speed;
}
