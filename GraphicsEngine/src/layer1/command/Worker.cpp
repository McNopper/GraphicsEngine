/*
 * Worker.cpp
 *
 *  Created on: 28.09.2012
 *      Author: nopper
 */

#include "Worker.h"

using namespace std;

Worker::Worker(const CommandQueueSP& workerQueue) : commandQueue(workerQueue)
{
	workerThread = new thread(&Worker::run, this);
}

Worker::~Worker()
{
}

void Worker::run() const
{
	glusLogPrint(GLUS_LOG_INFO, "Worker thread started");

	bool execute = true;

	Command* currentCommand = nullptr;

	while (execute)
	{
		commandQueue->waitAndTake(currentCommand);

		if (currentCommand)
		{
			execute = currentCommand->execute();

			currentCommand->recycle();
		}
		else
		{
			glusLogPrint(GLUS_LOG_WARNING, "Empty command");
		}
	}

	glusLogPrint(GLUS_LOG_INFO, "Worker thread stopped");
}

void Worker::join()
{
	workerThread->join();

	delete workerThread;

	workerThread = nullptr;
}
