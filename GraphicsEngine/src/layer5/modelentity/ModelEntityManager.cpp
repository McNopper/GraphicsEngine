/*
 * ModelEntityManager.cpp
 *
 *  Created on: 30.04.2011
 *      Author: Norbert Nopper
 */

#include "../../layer1/worker/WorkerManager.h"
#include "../../layer2/entity/EntityCommandManager.h"

#include "ModelEntityManager.h"

using namespace std;

ModelEntityManager* ModelEntityManager::instance = nullptr;

ModelEntityManager::ModelEntityManager() :
	allEntities(), allUpdatableEntities(), octree(), quicksort(), entityExcludeList()
{
}

ModelEntityManager::~ModelEntityManager()
{
	if (entityExcludeList.get())
	{
		entityExcludeList->clear();
	}

	vector<ModelEntitySP>::iterator walker = allEntities.begin();

	while (walker != allEntities.end())
	{
		removeEntity(*walker);

		walker = allEntities.begin();
	}
}

ModelEntityManager* ModelEntityManager::getInstance()
{
	if (!instance)
	{
		instance = new ModelEntityManager();
	}

	return instance;
}

void ModelEntityManager::terminate()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}

void ModelEntityManager::setOctree(const OctreeSP& octree)
{
	if (this->octree.get())
	{
		this->octree->removeAllEntities();
	}

	this->octree = octree;
	this->octree->removeAllEntities();
	this->octree->setEntityExcludeList(entityExcludeList);

	vector<ModelEntitySP>::iterator walker = allEntities.begin();
	while (walker != allEntities.end())
	{
		octree->updateEntity(*walker);
		walker++;
	}
}

void ModelEntityManager::updateMetrics() const
{
	auto walker = allUpdatableEntities.begin();
	while (walker != allUpdatableEntities.end())
	{
		(*walker)->updateBoundingSphereCenter();

		walker++;
	}

	walker = allEntities.begin();
	while (walker != allEntities.end())
	{
		(*walker)->updateDistanceToCamera();

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

void ModelEntityManager::sort()
{
	if (octree.get())
	{
		octree->sort();
	}
	else
	{
		quicksort.sort(allEntities);
	}
}

void ModelEntityManager::update() const
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
}

void ModelEntityManager::render(bool force) const
{
	if (octree.get())
	{
		octree->render(force);
	}
	else
	{
		if (ModelEntity::isAscendingSortOrder())
		{
			auto walker = allEntities.begin();
			while (walker != allEntities.end())
			{
				if ((force || ModelEntity::getCurrentCamera()->getViewFrustum().isVisible((*walker)->getBoundingSphere())) && !isEntityExcluded(*walker))
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
				if ((force || ModelEntity::getCurrentCamera()->getViewFrustum().isVisible((*walker)->getBoundingSphere())) && !isEntityExcluded(*walker))
				{
					(*walker)->render();
				}

				walker++;
			}
		}
	}
}

void ModelEntityManager::updateEntity(const ModelEntitySP& entity)
{
	vector<ModelEntitySP>::iterator walker = find(allEntities.begin(), allEntities.end(), entity);
	if (walker == allEntities.end())
	{
		allEntities.push_back(entity);
		if (octree.get())
		{
			octree->updateEntity(entity);
		}
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

void ModelEntityManager::removeEntity(const ModelEntitySP& entity)
{
	vector<ModelEntitySP>::iterator walker = find(allEntities.begin(), allEntities.end(), entity);
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

void ModelEntityManager::setBrightColorEffect(bool writeBrightColor, float brightColorLimit) const
{
	auto walker = allEntities.begin();
	while (walker != allEntities.end())
	{
		(*walker)->setWriteBrightColor(writeBrightColor);
		(*walker)->setBrightColorLimit(brightColorLimit);
		walker++;
	}
}

ModelEntitySP ModelEntityManager::findEntity(const string& name) const
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

	return ModelEntitySP();
}

void ModelEntityManager::setEntityExcludeList(const EntityListSP& entityExcludeList)
{
	this->entityExcludeList = entityExcludeList;

	if (octree)
	{
		octree->setEntityExcludeList(entityExcludeList);
	}
}

bool ModelEntityManager::isEntityExcluded(const ModelEntitySP& modelEntity) const
{
	if (!entityExcludeList.get())
	{
		return false;
	}

	return entityExcludeList->containsEntity(modelEntity);
}

