/*
 * GeneralEntityManager.h
 *
 *  Created on: 11.05.2013
 *      Author: nopper
 */

#ifndef GENERALENTITYMANAGER_H_
#define GENERALENTITYMANAGER_H_

#include "../../UsedLibs.h"

#include "../../layer0/algorithm/Quicksort.h"
#include "../../layer2/entity/EntityList.h"
#include "../../layer3/octree/Octree.h"
#include "GeneralEntity.h"

class GeneralEntityManager
{
private:

	static GeneralEntityManager* instance;

	std::vector<GeneralEntitySP> allEntities;
	std::vector<GeneralEntitySP> allUpdatableEntities;

	OctreeSP octree;

	Quicksort<GeneralEntitySP> quicksort;

	EntityListSP entityExcludeList;

private:

	GeneralEntityManager();
	virtual ~GeneralEntityManager();

public:

	static GeneralEntityManager* getInstance();

	static void terminate();

	void setOctree(const OctreeSP& octree);

	void update() const;

	void sort();

	/**
	 * @param force True, if render everything. Exclude list is still excluding.
	 */
	void render(bool force = false) const;

	void updateEntity(const GeneralEntitySP& entity);

	void removeEntity(const GeneralEntitySP& entity);

	void setBrightColorEffect(bool writeBrightColor, float brightColorLimit) const;

	GeneralEntitySP findEntity(const std::string& name) const;

	void setEntityExcludeList(const EntityListSP& entityExcludeList);

	bool isEntityExcluded(const GeneralEntitySP& modelEntity) const;
};

#endif /* GENERALENTITYMANAGER_H_ */
