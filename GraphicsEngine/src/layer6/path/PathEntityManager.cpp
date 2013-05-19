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

void PathEntityManager::addEntity(const GeneralEntitySP& entity, const PathSP& path)
{
	allPaths[entity] = path;
}

PathSP PathEntityManager::findPath(const GeneralEntitySP& entity) const
{
	auto result = allPaths.find(entity);

	if (result != allPaths.end())
	{
		return result->second;
	}

	return PathSP();
}

bool PathEntityManager::updateEntity(const GeneralEntitySP& entity, float deltaTime)
{
	if (deltaTime == 0.0f)
	{
		return false;
	}

	if (!entity.get())
	{
		return false;
	}

	auto result = allPaths.find(entity);

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

	path->updatePath(deltaTime, entity);

	if (!path->isPaused())
	{
		entity->setPositionOrientation(path->getLocation(), path->getOrientation());
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
