/*
 * WorkerManager.h
 *
 *  Created on: 28.09.2012
 *      Author: nopper
 */

#ifndef WORKERMANAGER_H_
#define WORKERMANAGER_H_

#include "../../UsedLibs.h"

#include "../../layer0/stereotype/Singleton.h"
#include "../../layer0/stereotype/ValueVector.h"

#include "StopCommand.h"
#include "Worker.h"

class WorkerManager : public Singleton<WorkerManager>
{

	friend class Singleton<WorkerManager>;

private:

	StopCommandRecycleQueueSP stopCommandRecycleQueue;

	CommandQueueSP commandQueue;

	ValueVector<WorkerSP> allWorker;

	WorkerManager();
	virtual ~WorkerManager();

public:

	void addWorker();

	void removeAllWorker();

	uint32_t getNumberWorkers() const;

	void sendCommand(Command* command);

};

#endif /* WORKERMANAGER_H_ */
