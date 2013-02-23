/*
 * TaskCounter.cpp
 *
 *  Created on: 28.09.2012
 *      Author: nopper
 */

#include "TaskCounter.h"

using namespace std;

using namespace boost;

TaskCounter::TaskCounter() : counter(0)
{
}

TaskCounter::TaskCounter(const TaskCounter& other)
{
	lock_guard<mutex> taskCounterLock(other.taskCounterMutex);

	counter = other.counter;
}

TaskCounter::~TaskCounter()
{
}

void TaskCounter::started()
{
	lock_guard<mutex> taskCounterLock(taskCounterMutex);

	counter++;
}

void TaskCounter::finished()
{
	lock_guard<mutex> taskCounterLock(taskCounterMutex);

	counter--;

	BOOST_ASSERT(counter >= 0);

	taskCounterConditionVariable.notify_all();
}

void TaskCounter::waitAllFinished() const
{
	unique_lock<mutex> taskCounterLock(taskCounterMutex);
	taskCounterConditionVariable.wait(taskCounterLock, [this] {return counter == 0;} );
}
