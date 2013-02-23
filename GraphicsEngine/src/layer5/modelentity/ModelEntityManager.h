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

private:

	ModelEntityManager();
	virtual ~ModelEntityManager();

public:

	static ModelEntityManager* getInstance();

	static void terminate();

	void setOctree(const OctreeSP& octree);

	void updateMetrics() const;

	void sort();

	void update() const;

	void render() const;

	void updateEntity(const ModelEntitySP& entity);

	void removeEntity(const ModelEntitySP& entity);

	void setBrightColorEffect(bool writeBrightColor, float brightColorLimit) const;

};

#endif /* MODELENTITYMANAGER_H_ */
