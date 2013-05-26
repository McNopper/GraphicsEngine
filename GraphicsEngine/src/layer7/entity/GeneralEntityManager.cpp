/*
 * GeneralEntityManager.cpp
 *
 *  Created on: 30.04.2011
 *      Author: Norbert Nopper
 */

#include "../../layer1/command/WorkerManager.h"
#include "../../layer5/command/EntityCommandManager.h"

#include "GeneralEntityManager.h"

using namespace std;

GeneralEntityManager::GeneralEntityManager() :
	Singleton<GeneralEntityManager>(), allEntities(), allUpdatableEntities(), octree(), quicksort(), entityExcludeList()
{
}

GeneralEntityManager::~GeneralEntityManager()
{
	if (entityExcludeList.get())
	{
		entityExcludeList->clear();
	}

	vector<GeneralEntitySP>::iterator walker = allEntities.begin();

	while (walker != allEntities.end())
	{
		removeEntity(*walker);

		walker = allEntities.begin();
	}
}

void GeneralEntityManager::setOctree(const OctreeSP& octree)
{
	if (this->octree.get())
	{
		this->octree->removeAllEntities();
	}

	this->octree = octree;
	this->octree->removeAllEntities();
	this->octree->setEntityExcludeList(entityExcludeList);

	vector<GeneralEntitySP>::iterator walker = allEntities.begin();
	while (walker != allEntities.end())
	{
		octree->updateEntity(*walker);
		walker++;
	}
}

void GeneralEntityManager::update() const
{
	if (octree.get())
	{
		octree->update();
	}
	else
	{
		auto walker = allUpdatableEntities.begin();

		while (walker != allUpdatableEntities.end())
		{
			if (WorkerManager::getInstance()->getNumberWorkers() == 0)
			{
				(*walker)->update();
			}
			else
			{
				EntityCommandManager::getInstance()->publishUpdateCommand(walker->get());
			}

			walker++;
		}
	}

	if (WorkerManager::getInstance()->getNumberWorkers() > 0)
	{
		EntityCommandManager::getInstance()->waitUpdateAllFinished();
	}

	auto walker = allUpdatableEntities.begin();
	while (walker != allUpdatableEntities.end())
	{
		(*walker)->updateBoundingSphereCenter();

		walker++;
	}

	if (octree.get())
	{
		walker = allUpdatableEntities.begin();
		while (walker != allUpdatableEntities.end())
		{
			if (!(*walker)->insideVisitingOctant())
			{
				octree->updateEntity(*walker);
			}

			walker++;
		}
	}
}

void GeneralEntityManager::sort()
{
	if (octree.get())
	{
		octree->sort();
	}
	else
	{
		auto walker = allEntities.begin();
		while (walker != allEntities.end())
		{
			(*walker)->updateDistanceToCamera();

			walker++;
		}

		quicksort.sort(allEntities);
	}
}

void GeneralEntityManager::render(bool force) const
{
	if (octree.get())
	{
		octree->render(force);
	}
	else
	{
		if (GeneralEntity::isAscendingSortOrder())
		{
			auto walker = allEntities.begin();
			while (walker != allEntities.end())
			{
				if ((force || GeneralEntity::getCurrentCamera()->getViewFrustum().isVisible((*walker)->getBoundingSphere())) && !isEntityExcluded(*walker))
				{
					(*walker)->render();
				}

				walker++;
			}
		}
		else
		{
			auto walker = allEntities.rbegin();
			while (walker != allEntities.rend())
			{
				if ((force || GeneralEntity::getCurrentCamera()->getViewFrustum().isVisible((*walker)->getBoundingSphere())) && !isEntityExcluded(*walker))
				{
					(*walker)->render();
				}

				walker++;
			}
		}
	}
}

void GeneralEntityManager::updateEntity(const GeneralEntitySP& entity)
{
	vector<GeneralEntitySP>::iterator walker = find(allEntities.begin(), allEntities.end(), entity);
	if (walker == allEntities.end())
	{
		allEntities.push_back(entity);
		if (octree.get())
		{
			octree->updateEntity(entity);
		}
		entity->update();
	}
	walker = find(allUpdatableEntities.begin(), allUpdatableEntities.end(), entity);

	if (!entity->isUpdateable() && walker != allUpdatableEntities.end())
	{
		allUpdatableEntities.erase(walker);
	}
	else if (entity->isUpdateable() && walker == allUpdatableEntities.end())
	{
		allUpdatableEntities.push_back(entity);
	}
}

void GeneralEntityManager::removeEntity(const GeneralEntitySP& entity)
{
	vector<GeneralEntitySP>::iterator walker = find(allEntities.begin(), allEntities.end(), entity);
	if (walker != allEntities.end())
	{
		if (octree.get())
		{
			octree->removeEntity(entity);
		}
		allEntities.erase(walker);
	}
	walker = find(allUpdatableEntities.begin(), allUpdatableEntities.end(), entity);
	if (walker != allUpdatableEntities.end())
	{
		allUpdatableEntities.erase(walker);
	}
}

void GeneralEntityManager::setBrightColorEffect(bool writeBrightColor, float brightColorLimit) const
{
	auto walker = allEntities.begin();
	while (walker != allEntities.end())
	{
		(*walker)->setWriteBrightColor(writeBrightColor);
		(*walker)->setBrightColorLimit(brightColorLimit);
		walker++;
	}
}

GeneralEntitySP GeneralEntityManager::findEntity(const string& name) const
{
	auto walker = allEntities.begin();

	while (walker != allEntities.end())
	{
		if ((*walker)->getName().compare(name) == 0)
		{
			return *walker;
		}

		walker++;
	}

	return GeneralEntitySP();
}

void GeneralEntityManager::setEntityExcludeList(const EntityListSP& entityExcludeList)
{
	this->entityExcludeList = entityExcludeList;

	if (octree)
	{
		octree->setEntityExcludeList(entityExcludeList);
	}
}

bool GeneralEntityManager::isEntityExcluded(const GeneralEntitySP& generalEntity) const
{
	if (!entityExcludeList.get())
	{
		return false;
	}

	return entityExcludeList->containsEntity(generalEntity);
}

