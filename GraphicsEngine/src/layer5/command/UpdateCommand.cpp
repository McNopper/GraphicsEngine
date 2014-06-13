/*
 * UpdateCommand.cpp
 *
 *  Created on: 28.09.2012
 *      Author: nopper
 */

#include "UpdateCommand.h"

using namespace std;

UpdateCommand::UpdateCommand(const UpdateCommandRecycleQueueSP& updateCommandRecycleQueue, const ThreadSafeCounterSP& taskCounter) : Command(), updateCommandRecycleQueue(updateCommandRecycleQueue), taskCounter(taskCounter), entity(nullptr)
{
}

UpdateCommand::~UpdateCommand()
{
}

bool UpdateCommand::execute()
{
	assert(this->taskCounter.get() != nullptr);
	assert(this->entity != nullptr);

	entity->update();

	taskCounter->decrement();

	return true;
}

void UpdateCommand::recycle()
{
	entity = nullptr;
	updateCommandRecycleQueue->add(this);
}

void UpdateCommand::init(Entity* entity)
{
	assert(this->taskCounter.get() != nullptr);
	assert(this->entity == nullptr);

	taskCounter->increment();

	this->entity = entity;
}
