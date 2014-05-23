/*
 * PathEntityManager.h
 *
 *  Created on: 11.03.2013
 *      Author: nopper
 */

#ifndef PATHENTITYMANAGER_H_
#define PATHENTITYMANAGER_H_

#include "../../layer0/stereotype/KeyValueManager.h"
#include "../../layer0/stereotype/Singleton.h"
#include "../../layer7/entity/GeneralEntity.h"

#include "Path.h"

class PathEntityManager : public Singleton<PathEntityManager>, private KeyValueManager<GeneralEntitySP, PathSP>
{

	friend class Singleton<PathEntityManager>;

protected:

	PathEntityManager();
	virtual ~PathEntityManager();

public:

	void addEntity(const GeneralEntitySP& entity, const PathSP& path);

	PathSP findPath(const GeneralEntitySP& entity) const;

	bool updateEntity(const GeneralEntitySP& entity, float deltaTime);

	void updateEntities(float deltaTime);

};

#endif /* PATHENTITYMANAGER_H_ */
