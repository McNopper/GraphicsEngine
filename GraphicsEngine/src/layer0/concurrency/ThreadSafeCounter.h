/*
 * ThreadSafeCounter.h
 *
 *  Created on: 28.09.2012
 *      Author: nopper
 */

#ifndef THREADSAFECOUNTER_H_
#define THREADSAFECOUNTER_H_

#include "../../UsedLibs.h"

class ThreadSafeCounter
{

private:

	std::int32_t counter;

	mutable std::mutex counterMutex;

	mutable std::condition_variable counterConditionVariable;

public:
	ThreadSafeCounter();
	ThreadSafeCounter(const ThreadSafeCounter& other);
	~ThreadSafeCounter();

	void increment();

	void decrement();

	void waitUntilZero() const;
};

typedef std::shared_ptr<ThreadSafeCounter> ThreadSafeCounterSP;

#endif /* THREADSAFECOUNTER_H_ */
