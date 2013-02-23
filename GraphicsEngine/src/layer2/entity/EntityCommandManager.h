/*
 * EntityCommandManager.h
 *
 *  Created on: 28.09.2012
 *      Author: nopper
 */

#ifndef ENTITYCOMMANDMANAGER_H_
#define ENTITYCOMMANDMANAGER_H_

#include "../../layer0/algorithm/TaskCounter.h"

#include "Entity.h"
#include "UpdateCommand.h"

class EntityCommandManager
{

private:

	static EntityCommandManager* instance;

	UpdateCommandRecycleQueueSP updateCommandRecycleQueue;

	TaskCounterSP updateTaskCounter;

	EntityCommandManager();
	~EntityCommandManager();

public:

	static EntityCommandManager* getInstance();

	static void terminate();

	void publishUpdateCommand(Entity* entity);

	void waitUpdateAllFinished();

};

#endif /* ENTITYCOMMANDMANAGER_H_ */
