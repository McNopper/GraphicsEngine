/*
 * UpdateCommand.h
 *
 *  Created on: 28.09.2012
 *      Author: nopper
 */

#ifndef UPDATECOMMAND_H_
#define UPDATECOMMAND_H_

#include "../../layer0/concurrency/ThreadSafeCounter.h"
#include "../../layer1/command/Command.h"
#include "../../layer4/entity/Entity.h"

class UpdateCommand: public Command
{

	friend class EntityCommandManager;

private:

	std::shared_ptr<ThreadsafeQueue<UpdateCommand*> > updateCommandRecycleQueue;

	ThreadSafeCounterSP taskCounter;

	Entity* entity;

	UpdateCommand(const std::shared_ptr<ThreadsafeQueue<UpdateCommand*> >& updateCommandRecycleQueue, const ThreadSafeCounterSP& taskCounter);

	virtual ~UpdateCommand();

public:

	virtual bool execute();

	virtual void recycle();

	void init(Entity* entity);

};

typedef std::shared_ptr<ThreadsafeQueue<UpdateCommand*> > UpdateCommandRecycleQueueSP;

#endif /* UPDATECOMMAND_H_ */
