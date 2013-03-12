/*
 * PathEntityManager.h
 *
 *  Created on: 11.03.2013
 *      Author: nopper
 */

#ifndef PATHENTITYMANAGER_H_
#define PATHENTITYMANAGER_H_

#include "../../layer0/math/Geometry.h"
#include "../../layer2/path/Path.h"
#include "../../layer5/modelentity/ModelEntity.h"

class PathEntityManager
{

private:

	static PathEntityManager* instance;

	std::map<Geometry*, PathSP> allPaths;

	PathEntityManager();
	virtual ~PathEntityManager();

public:

	static PathEntityManager* getInstance();

	static void terminate();

	void addEntity(Geometry* geometry, const PathSP& path);

	PathSP findPath(Geometry* geometry) const;

	bool updateEntity(Geometry* geometry, float deltaTime);

	void updateEntities(float deltaTime);

};

#endif /* PATHENTITYMANAGER_H_ */
