/*
 * EntityList.h
 *
 *  Created on: 04.04.2013
 *      Author: nopper
 */

#ifndef ENTITYLIST_H_
#define ENTITYLIST_H_

#include "../../UsedLibs.h"

#include "Entity.h"

class EntityList
{

private:

	std::vector<EntitySP> allEntities;

public:

	EntityList();

	virtual ~EntityList();

	void addEntity(const EntitySP& entity);

	void removeEntity(const EntitySP& entity);

	bool containsEntity(const EntitySP& entity) const;

	std::int32_t size() const;

	void clear();

};

typedef std::shared_ptr<EntityList> EntityListSP;

#endif /* ENTITYLIST_H_ */
