/*
 * PathEntityManager.cpp
 *
 *  Created on: 11.03.2013
 *      Author: nopper
 */

#include "PathEntityManager.h"

PathEntityManager* PathEntityManager::instance = nullptr;

PathEntityManager::PathEntityManager() :
	allPaths()
{
}

PathEntityManager::~PathEntityManager()
{
	auto walker = allPaths.begin();

	while (walker != allPaths.end())
	{
		walker->second.reset();

		walker++;
	}

	allPaths.clear();
}

PathEntityManager* PathEntityManager::getInstance()
{
	if (!instance)
	{
		instance = new PathEntityManager();
	}

	return instance;
}

void PathEntityManager::terminate()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}

void PathEntityManager::addEntity(Geometry* geometry, const PathSP& path)
{
	allPaths[geometry] = path;
}

PathSP PathEntityManager::findPath(Geometry* geometry) const
{
	auto result = allPaths.find(geometry);

	if (result != allPaths.end())
	{
		return result->second;
	}

	return PathSP();
}

bool PathEntityManager::updateEntity(Geometry* geometry, float deltaTime)
{
	if (deltaTime == 0.0f)
	{
		return false;
	}

	if (!geometry)
	{
		return false;
	}

	auto result = allPaths.find(geometry);

	if (result == allPaths.end())
	{
		return false;
	}

	PathSP path = result->second;

	if (!path.get())
	{
		return false;
	}

	if (path->isEnded())
	{
		return false;
	}

	path->updatePath(deltaTime, *geometry);

	if (!path->isPaused())
	{
		geometry->updateLocationOrientation(path->getLocation(), path->getOrientation());
	}

	return true;
}

void PathEntityManager::updateEntities(float deltaTime)
{
	auto walker = allPaths.begin();

	while (walker != allPaths.end())
	{
		updateEntity(walker->first, deltaTime);

		walker++;
	}
}
