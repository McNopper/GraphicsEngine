/*
 * ModelEntityManager.h
 *
 *  Created on: 30.04.2011
 *      Author: Norbert Nopper
 */

#ifndef MODELENTITYMANAGER_H_
#define MODELENTITYMANAGER_H_

#include "../../UsedLibs.h"

#include "../../layer0/algorithm/Quicksort.h"
#include "../../layer2/entity/EntityList.h"
#include "../../layer3/octree/Octree.h"
#include "ModelEntity.h"

class ModelEntityManager
{

private:

	static ModelEntityManager* instance;

	std::vector<ModelEntitySP> allEntities;
	std::vector<ModelEntitySP> allUpdatableEntities;

	OctreeSP octree;

	Quicksort<ModelEntitySP> quicksort;

	EntityListSP entityExcludeList;

private:

	ModelEntityManager();
	virtual ~ModelEntityManager();

public:

	static ModelEntityManager* getInstance();

	static void terminate();

	void setOctree(const OctreeSP& octree);

	void update() const;

	void sort();

	/**
	 * @param force True, if render everything. Exclude list is still excluding.
	 */
	void render(bool force = false) const;

	void updateEntity(const ModelEntitySP& entity);

	void removeEntity(const ModelEntitySP& entity);

	void setBrightColorEffect(bool writeBrightColor, float brightColorLimit) const;

	ModelEntitySP findEntity(const std::string& name) const;

	void setEntityExcludeList(const EntityListSP& entityExcludeList);

	bool isEntityExcluded(const ModelEntitySP& modelEntity) const;

};

#endif /* MODELENTITYMANAGER_H_ */
