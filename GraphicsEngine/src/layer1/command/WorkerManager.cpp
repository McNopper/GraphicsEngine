/*
 * WorkerManager.cpp
 *
 *  Created on: 28.09.2012
 *      Author: nopper
 */

#include "Command.h"
#include "StopCommand.h"

#include "WorkerManager.h"

using namespace std;

WorkerManager::WorkerManager() :
		Singleton<WorkerManager>()
{
	stopCommandRecycleQueue = StopCommandRecycleQueueSP(new ThreadsafeQueue<StopCommand*>());
	commandQueue = CommandQueueSP(new ThreadsafeQueue<Command*>());
}

WorkerManager::~WorkerManager()
{
	removeAllWorker();

	StopCommand* currentStopCommand = nullptr;
	bool available = stopCommandRecycleQueue->take(currentStopCommand);
	while (available)
	{
		delete currentStopCommand;

		available = stopCommandRecycleQueue->take(currentStopCommand);
	}
	stopCommandRecycleQueue.reset();

	Command* currentCommand = nullptr;
	available = commandQueue->take(currentCommand);
	while (available)
	{
		delete currentCommand;

		available = commandQueue->take(currentCommand);
	}
	commandQueue.reset();
}

void WorkerManager::addWorker()
{
	WorkerSP currentWorker = WorkerSP(new Worker(commandQueue));

	allWorker.add(currentWorker);
}

void WorkerManager::removeAllWorker()
{
	bool available;

	StopCommand* currentCommand = nullptr;

	glusLogPrint(GLUS_LOG_INFO, "Sending stop commands to worker threads");
	auto walker = allWorker.begin();
	while (walker != allWorker.end())
	{
		available = stopCommandRecycleQueue->take(currentCommand);

		if (!available)
		{
			currentCommand = new StopCommand(stopCommandRecycleQueue);
		}

		commandQueue->add(currentCommand);

		walker++;
	}

	glusLogPrint(GLUS_LOG_INFO, "Waiting for stopping worker threads");
	walker = allWorker.begin();
	while (walker != allWorker.end())
	{
		(*walker)->join();

		glusLogPrint(GLUS_LOG_INFO, "Worker thread stopped running");

		walker++;
	}

	glusLogPrint(GLUS_LOG_INFO, "Removing worker threads");
	walker = allWorker.begin();
	while (walker != allWorker.end())
	{
		(*walker).reset();
		walker++;
	}
	allWorker.clear();
}

uint32_t WorkerManager::getNumberWorkers() const
{
	return allWorker.size();
}

void WorkerManager::sendCommand(Command* command)
{
	commandQueue->add(command);
}
