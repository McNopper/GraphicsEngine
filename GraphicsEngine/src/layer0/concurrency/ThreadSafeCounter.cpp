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
	std::lock_guard<std::mutex> taskCounterLock(other.counterMutex);

	counter = other.counter;
}

ThreadSafeCounter::~ThreadSafeCounter()
{
}

void ThreadSafeCounter::increment()
{
	std::lock_guard<std::mutex> taskCounterLock(counterMutex);

	counter++;
}

void ThreadSafeCounter::decrement()
{
	std::lock_guard<std::mutex> taskCounterLock(counterMutex);

	counter--;

	assert(counter >= 0);

	counterConditionVariable.notify_all();
}

void ThreadSafeCounter::waitUntilZero() const
{
	std::unique_lock<std::mutex> taskCounterLock(counterMutex);
	counterConditionVariable.wait(taskCounterLock, [this] {return counter == 0;} );
}
