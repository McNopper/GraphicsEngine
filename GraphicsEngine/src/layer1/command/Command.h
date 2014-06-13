/*
 * Command.h
 *
 *  Created on: 28.09.2012
 *      Author: nopper
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include "../../UsedLibs.h"

#include "../../layer0/concurrency/ThreadsafeQueue.h"

class Command
{

	friend class WorkerManager;

protected:

	Command() {}
	virtual ~Command() {}

public:

	virtual bool execute() = 0;

	virtual void recycle() = 0;
};

typedef std::shared_ptr<ThreadsafeQueue<Command*> > CommandQueueSP;

#endif /* COMMAND_H_ */
