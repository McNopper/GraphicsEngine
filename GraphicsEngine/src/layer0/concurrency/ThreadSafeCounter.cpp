/*
 * TaskCounter.cpp
 *
 *  Created on: 28.09.2012
 *      Author: nopper
 */

#include "ThreadSafeCounter.h"

using namespace std;

using namespace boost;

ThreadSafeCounter::ThreadSafeCounter() : counter(0)
{
}

ThreadSafeCounter::ThreadSafeCounter(const ThreadSafeCounter& other)
{
	lock_guard<mutex> taskCounterLock(other.counterMutex);

	counter = other.counter;
}

ThreadSafeCounter::~ThreadSafeCounter()
{
}

void ThreadSafeCounter::increment()
{
	lock_guard<mutex> taskCounterLock(counterMutex);

	counter++;
}

void ThreadSafeCounter::decrement()
{
	lock_guard<mutex> taskCounterLock(counterMutex);

	counter--;

	BOOST_ASSERT(counter >= 0);

	counterConditionVariable.notify_all();
}

void ThreadSafeCounter::waitUntilZero() const
{
	unique_lock<mutex> taskCounterLock(counterMutex);
	counterConditionVariable.wait(taskCounterLock, [this] {return counter == 0;} );
}
