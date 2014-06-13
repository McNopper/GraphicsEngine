/*
 * EntityList.cpp
 *
 *  Created on: 04.04.2013
 *      Author: nopper
 */

#include "EntityList.h"

using namespace std;

EntityList::EntityList() :
	allEntities()
{
}

EntityList::~EntityList()
{
	allEntities.clear();
}

void EntityList::addEntity(const EntitySP& entity)
{
	if (!containsEntity(entity))
	{
		allEntities.push_back(entity);
	}
}

void EntityList::removeEntity(const EntitySP& entity)
{
	auto walker = find(allEntities.begin(), allEntities.end(), entity);

	if (walker != allEntities.end())
	{
		allEntities.erase(walker);
	}
}

bool EntityList::containsEntity(const EntitySP& entity) const
{
	auto walker = find(allEntities.begin(), allEntities.end(), entity);

	return walker != allEntities.end();
}

int32_t EntityList::size() const
{
	return allEntities.size();
}

void EntityList::clear()
{
	allEntities.clear();
}
