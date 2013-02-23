/*
 * EventManager.cpp
 *
 *  Created on: 07.01.2013
 *      Author: nopper
 */

#include "EventManager.h"

using namespace std;

using namespace boost;

EventManager* EventManager::instance = nullptr;

EventManager::EventManager() : eventMutex(), allEvents(), allEventReceivers()
{
}

EventManager::~EventManager()
{
	lock_guard<mutex> eventLock(eventMutex);

	EventSP currentEvent;

	while(allEvents.take(currentEvent))
	{
		currentEvent.reset();
	}

	allEventReceivers.clear();
}

EventManager* EventManager::getInstance()
{
	if (!instance)
	{
		instance = new EventManager();
	}

	return instance;
}

void EventManager::terminate()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}

void EventManager::processEvents()
{
	lock_guard<mutex> eventLock(eventMutex);

	int32_t currentSize = allEvents.size();

	EventSP currentEvent;
	vector<EventReceiverSP>::const_iterator eventReceiver;
	for (int32_t i = 0; i < currentSize; i++)
	{
		if (allEvents.take(currentEvent))
		{
			eventReceiver = find(allEventReceivers.begin(), allEventReceivers.end(), currentEvent->getEventReceiver());

			if (eventReceiver != allEventReceivers.end())
			{
				(*eventReceiver)->processEvent(*currentEvent);
			}
			else
			{
				glusLogPrint(GLUS_LOG_WARNING, "Event receiver not found. Dropping event.");
			}
		}
		else
		{
			glusLogPrint(GLUS_LOG_WARNING, "Expected more events: %d", (currentSize - i));

			break;
		}
	}
}

void EventManager::addEventReceiver(const EventReceiverSP& receiver)
{
	lock_guard<mutex> eventLock(eventMutex);

	allEventReceivers.push_back(receiver);
}

void EventManager::removeEventReceiver(const EventReceiverSP& receiver)
{
	lock_guard<mutex> eventLock(eventMutex);

	auto element = find(allEventReceivers.begin(), allEventReceivers.end(), receiver);

	if (element != allEventReceivers.end())
	{
		allEventReceivers.erase(element);
	}
}

/**
 * This method is non-blocking by purpose. Also, events are handled asynchronous.
 */
void EventManager::sendEvent(const EventSP& event)
{
	allEvents.add(event);
}

const vector<EventReceiverSP>& EventManager::getEventReceivers() const
{
	lock_guard<mutex> eventLock(eventMutex);

	return allEventReceivers;
}
