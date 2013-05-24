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

	mutable boost::mutex queueMutex;

	boost::condition_variable queueConditionVariable;

	std::queue<ELEMENT> allElements;

public:

	ThreadsafeQueue()
	{
	}

	ThreadsafeQueue(const ThreadsafeQueue& other)
	{
		boost::lock_guard<boost::mutex> queueLock(other.queueMutex);

		allElements = other.allElements;
	}

	~ThreadsafeQueue()
	{
		boost::lock_guard<boost::mutex> queueLock(queueMutex);

		while (allElements.size() > 0)
		{
			allElements.pop();
		}
	}

	void add(const ELEMENT& command)
	{
		boost::lock_guard<boost::mutex> queueLock(queueMutex);

		allElements.push(command);

		queueConditionVariable.notify_one();
	}

	bool take(ELEMENT& result)
	{
		boost::lock_guard<boost::mutex> queueLock(queueMutex);

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
		boost::unique_lock<boost::mutex> queueLock(queueMutex);
		queueConditionVariable.wait(queueLock, [this] {return !allElements.empty();} );

		result = allElements.front();
		allElements.pop();
	}

	bool empty() const
	{
		boost::lock_guard<boost::mutex> queueLock(queueMutex);

		return allElements.empty();
	}

	boost::int32_t size() const
	{
		boost::lock_guard<boost::mutex> queueLock(queueMutex);

		return allElements.size();
	}

};

#endif /* THREADSAFEQUEUE_H_ */
