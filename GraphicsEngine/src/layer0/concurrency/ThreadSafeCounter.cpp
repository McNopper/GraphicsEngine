/*
 * TaskCounter.cpp
 *
 *  Created on: 28.09.2012
 *      Author: nopper
 */

#include "ThreadSafeCounter.h"

ThreadSafeCounter::ThreadSafeCounter() : counter(0)
{
}

ThreadSafeCounter::ThreadSafeCounter(const ThreadSafeCounter& other)
{
	boost::lock_guard<boost::mutex> taskCounterLock(other.counterMutex);

	counter = other.counter;
}

ThreadSafeCounter::~ThreadSafeCounter()
{
}

void ThreadSafeCounter::increment()
{
	boost::lock_guard<boost::mutex> taskCounterLock(counterMutex);

	counter++;
}

void ThreadSafeCounter::decrement()
{
	boost::lock_guard<boost::mutex> taskCounterLock(counterMutex);

	counter--;

	BOOST_ASSERT(counter >= 0);

	counterConditionVariable.notify_all();
}

void ThreadSafeCounter::waitUntilZero() const
{
	boost::unique_lock<boost::mutex> taskCounterLock(counterMutex);
	counterConditionVariable.wait(taskCounterLock, [this] {return counter == 0;} );
}
