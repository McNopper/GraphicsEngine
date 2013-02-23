/*
 * StopCommand.h
 *
 *  Created on: 28.09.2012
 *      Author: nopper
 */

#ifndef STOPCOMMAND_H_
#define STOPCOMMAND_H_


#include "../../layer0/algorithm/ThreadsafeQueue.h"
#include "Command.h"

class StopCommand: public Command
{

	friend class WorkerManager;

private:

	boost::shared_ptr<ThreadsafeQueue<StopCommand*> > stopCommandRecycleQueue;

	StopCommand(const boost::shared_ptr<ThreadsafeQueue<StopCommand*> >& stopCommandRecycleQueue);
	virtual ~StopCommand();

public:

	virtual bool execute();

	virtual void recycle();
};

typedef boost::shared_ptr<ThreadsafeQueue<StopCommand*> > StopCommandRecycleQueueSP;

#endif /* STOPCOMMAND_H_ */
