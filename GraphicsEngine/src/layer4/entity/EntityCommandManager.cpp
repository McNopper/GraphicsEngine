/*
 * EntityCommandManager.cpp
 *
 *  Created on: 28.09.2012
 *      Author: nopper
 */

#include "../../layer1/worker/WorkerManager.h"

#include "EntityCommandManager.h"

EntityCommandManager* EntityCommandManager::instance;

EntityCommandManager::EntityCommandManager()
{
	updateTaskCounter = ThreadSafeCounterSP(new ThreadSafeCounter());

	updateCommandRecycleQueue = UpdateCommandRecycleQueueSP(new ThreadsafeQueue<UpdateCommand*>());
}

EntityCommandManager::~EntityCommandManager()
{
	UpdateCommand* currentStopCommand = nullptr;
	bool available = updateCommandRecycleQueue->take(currentStopCommand);
	while(available)
	{
		delete currentStopCommand;

		available = updateCommandRecycleQueue->take(currentStopCommand);
	}
	updateCommandRecycleQueue.reset();

	updateTaskCounter.reset();
}

EntityCommandManager* EntityCommandManager::getInstance()
{
	if (!instance)
	{
		instance = new EntityCommandManager();
	}

	return instance;
}

void EntityCommandManager::terminate()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}

void EntityCommandManager::publishUpdateCommand(Entity* entity)
{
	UpdateCommand* currentUpdateCommand = nullptr;
	bool available = updateCommandRecycleQueue->take(currentUpdateCommand);

	if (!available)
	{
		currentUpdateCommand = new UpdateCommand(updateCommandRecycleQueue, updateTaskCounter);
	}

	currentUpdateCommand->init(entity);

	WorkerManager::getInstance()->sendCommand(currentUpdateCommand);
}

void EntityCommandManager::waitUpdateAllFinished()
{
	updateTaskCounter->waitUntilZero();
}
