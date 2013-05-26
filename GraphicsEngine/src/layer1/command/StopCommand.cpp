/*
 * StopCommand.cpp
 *
 *  Created on: 28.09.2012
 *      Author: nopper
 */

#include "../../UsedLibs.h"

#include "StopCommand.h"

StopCommand::StopCommand(const StopCommandRecycleQueueSP& stopCommandRecycleQueue) : Command(), stopCommandRecycleQueue(stopCommandRecycleQueue)
{
}

StopCommand::~StopCommand()
{
}

bool StopCommand::execute()
{
	glusLogPrint(GLUS_LOG_INFO, "Requesting stopping worker thread");

	return false;
}

void StopCommand::recycle()
{
	stopCommandRecycleQueue->add(this);
}
