/*
 * PathEntityManager.cpp
 *
 *  Created on: 11.03.2013
 *      Author: nopper
 */

#include "PathEntityManager.h"

PathEntityManager::PathEntityManager() :
	Singleton<PathEntityManager>(), KeyValueManager<GeneralEntitySP, PathSP>()
{
}

PathEntityManager::~PathEntityManager()
{
}

void PathEntityManager::addEntity(const GeneralEntitySP& entity, const PathSP& path)
{
	add(entity, path);
}

PathSP PathEntityManager::findPath(const GeneralEntitySP& entity) const
{
	return find(entity);
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

	PathSP path = find(entity);

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
		entity->setPositionRotation(path->getPosition(), path->getRotation());
	}

	return true;
}

void PathEntityManager::updateEntities(float deltaTime)
{
	auto walker = begin();

	while (walker != end())
	{
		updateEntity(walker->first, deltaTime);

		walker++;
	}
}
