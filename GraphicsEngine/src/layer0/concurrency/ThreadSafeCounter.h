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

	boost::int32_t counter;

	mutable boost::mutex counterMutex;

	mutable boost::condition_variable counterConditionVariable;

public:
	ThreadSafeCounter();
	ThreadSafeCounter(const ThreadSafeCounter& other);
	~ThreadSafeCounter();

	void increment();

	void decrement();

	void waitUntilZero() const;
};

typedef boost::shared_ptr<ThreadSafeCounter> ThreadSafeCounterSP;

#endif /* THREADSAFECOUNTER_H_ */
