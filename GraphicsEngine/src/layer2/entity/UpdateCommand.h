/*
 * UpdateCommand.h
 *
 *  Created on: 28.09.2012
 *      Author: nopper
 */

#ifndef UPDATECOMMAND_H_
#define UPDATECOMMAND_H_

#include "../../layer0/algorithm/TaskCounter.h"
#include "../../layer1/worker/Command.h"
#include "Entity.h"

class UpdateCommand: public Command
{

	friend class EntityCommandManager;

private:

	boost::shared_ptr<ThreadsafeQueue<UpdateCommand*> > updateCommandRecycleQueue;

	TaskCounterSP taskCounter;

	Entity* entity;

	UpdateCommand(const boost::shared_ptr<ThreadsafeQueue<UpdateCommand*> >& updateCommandRecycleQueue, const TaskCounterSP& taskCounter);

	virtual ~UpdateCommand();

public:

	virtual bool execute();

	virtual void recycle();

	void init(Entity* entity);

};

typedef boost::shared_ptr<ThreadsafeQueue<UpdateCommand*> > UpdateCommandRecycleQueueSP;

#endif /* UPDATECOMMAND_H_ */
