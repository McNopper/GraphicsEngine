/*
 * TaskCounter.h
 *
 *  Created on: 28.09.2012
 *      Author: nopper
 */

#ifndef TASKCOUNTER_H_
#define TASKCOUNTER_H_

#include "../../UsedLibs.h"

class TaskCounter
{

private:

	boost::int32_t counter;

	mutable boost::mutex taskCounterMutex;

	mutable boost::condition_variable taskCounterConditionVariable;

public:
	TaskCounter();
	TaskCounter(const TaskCounter& other);
	~TaskCounter();

	void started();

	void finished();

	void waitAllFinished() const;
};

typedef boost::shared_ptr<TaskCounter> TaskCounterSP;

#endif /* TASKCOUNTER_H_ */
