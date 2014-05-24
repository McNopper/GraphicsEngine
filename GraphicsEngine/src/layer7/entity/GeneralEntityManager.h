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
#include "../../layer0/stereotype/Singleton.h"
#include "../../layer0/stereotype/ValueVector.h"
#include "../../layer4/entity/EntityList.h"
#include "../../layer6/octree/Octree.h"
#include "GeneralEntity.h"

class GeneralEntityManager : public Singleton<GeneralEntityManager>
{

	friend class Singleton<GeneralEntityManager>;

private:

	std::vector<GeneralEntitySP> allEntities;
	std::vector<GeneralEntitySP> allUpdatableEntities;

	OctreeSP octree;

	Quicksort<GeneralEntitySP> quicksort;

	EntityListSP entityExcludeList;

protected:

	GeneralEntityManager();
	virtual ~GeneralEntityManager();

public:

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
