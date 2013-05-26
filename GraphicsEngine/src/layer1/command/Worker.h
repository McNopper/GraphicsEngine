/*
 * Worker.h
 *
 *  Created on: 28.09.2012
 *      Author: nopper
 */

#ifndef WORKER_H_
#define WORKER_H_

#include "../../UsedLibs.h"

#include "Command.h"

class Worker
{

private:

	CommandQueueSP commandQueue;

	boost::thread* workerThread;

public:
	Worker(const CommandQueueSP& workerQueue);
	~Worker();

	void run() const;

	void join();

};

typedef boost::shared_ptr<Worker> WorkerSP;

#endif /* WORKER_H_ */
