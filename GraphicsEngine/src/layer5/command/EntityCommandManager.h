/*
 * EntityCommandManager.h
 *
 *  Created on: 28.09.2012
 *      Author: nopper
 */

#ifndef ENTITYCOMMANDMANAGER_H_
#define ENTITYCOMMANDMANAGER_H_

#include "../../layer0/concurrency/ThreadSafeCounter.h"
#include "../../layer0/stereotype/Singleton.h"
#include "../../layer4/entity/Entity.h"

#include "UpdateCommand.h"

class EntityCommandManager : public Singleton<EntityCommandManager>
{

	friend class Singleton<EntityCommandManager>;

private:

	UpdateCommandRecycleQueueSP updateCommandRecycleQueue;

	ThreadSafeCounterSP updateTaskCounter;

	EntityCommandManager();
	~EntityCommandManager();

public:

	void publishUpdateCommand(Entity* entity);

	void waitUpdateAllFinished();

};

#endif /* ENTITYCOMMANDMANAGER_H_ */
