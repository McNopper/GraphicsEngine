/*
 * PathEntityManager.h
 *
 *  Created on: 11.03.2013
 *      Author: nopper
 */

#ifndef PATHENTITYMANAGER_H_
#define PATHENTITYMANAGER_H_

#include "../../layer4/entity/GeneralEntity.h"
#include "Path.h"

class PathEntityManager
{

private:

	static PathEntityManager* instance;

	std::map<GeneralEntitySP, PathSP> allPaths;

	PathEntityManager();
	virtual ~PathEntityManager();

public:

	static PathEntityManager* getInstance();

	static void terminate();

	void addEntity(const GeneralEntitySP& entity, const PathSP& path);

	PathSP findPath(const GeneralEntitySP& entity) const;

	bool updateEntity(const GeneralEntitySP& entity, float deltaTime);

	void updateEntities(float deltaTime);

};

#endif /* PATHENTITYMANAGER_H_ */
