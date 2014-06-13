/*
 * ThreadsafeQueue.h
 *
 *  Created on: 28.09.2012
 *      Author: nopper
 */

#ifndef THREADSAFEQUEUE_H_
#define THREADSAFEQUEUE_H_

#include "../../UsedLibs.h"

template<class ELEMENT>
class ThreadsafeQueue
{

private:

	mutable std::mutex queueMutex;

	std::condition_variable queueConditionVariable;

	std::queue<ELEMENT> allElements;

public:

	ThreadsafeQueue()
	{
	}

	ThreadsafeQueue(const ThreadsafeQueue& other)
	{
		std::lock_guard<std::mutex> queueLock(other.queueMutex);

		allElements = other.allElements;
	}

	~ThreadsafeQueue()
	{
		std::lock_guard<std::mutex> queueLock(queueMutex);

		while (allElements.size() > 0)
		{
			allElements.pop();
		}
	}

	void add(const ELEMENT& command)
	{
		std::lock_guard<std::mutex> queueLock(queueMutex);

		allElements.push(command);

		queueConditionVariable.notify_one();
	}

	bool take(ELEMENT& result)
	{
		std::lock_guard<std::mutex> queueLock(queueMutex);

		if (!allElements.empty())
		{
			result = allElements.front();
			allElements.pop();

			return true;
		}

		return false;
	}

	void waitAndTake(ELEMENT& result)
	{
		std::unique_lock<std::mutex> queueLock(queueMutex);
		queueConditionVariable.wait(queueLock, [this] {return !allElements.empty();} );

		result = allElements.front();
		allElements.pop();
	}

	bool empty() const
	{
		std::lock_guard<std::mutex> queueLock(queueMutex);

		return allElements.empty();
	}

	std::int32_t size() const
	{
		std::lock_guard<std::mutex> queueLock(queueMutex);

		return allElements.size();
	}

};

#endif /* THREADSAFEQUEUE_H_ */
