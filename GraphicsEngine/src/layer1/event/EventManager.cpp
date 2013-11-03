/*
 * EventManager.cpp
 *
 *  Created on: 07.01.2013
 *      Author: nopper
 */

#include "EventManager.h"

EventManager* EventManager::instance = nullptr;

EventManager::EventManager() : eventMutex(), allEvents(), allEventReceivers()
{
}

EventManager::~EventManager()
{
	boost::lock_guard<boost::mutex> eventLock(eventMutex);

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
	boost::lock_guard<boost::mutex> eventLock(eventMutex);

	int32_t currentSize = allEvents.size();

	EventSP currentEvent;
	std::vector<EventReceiverSP>::const_iterator eventReceiver;
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
	boost::lock_guard<boost::mutex> eventLock(eventMutex);

	allEventReceivers.push_back(receiver);
}

void EventManager::removeEventReceiver(const EventReceiverSP& receiver)
{
	boost::lock_guard<boost::mutex> eventLock(eventMutex);

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

const std::vector<EventReceiverSP>& EventManager::getEventReceivers() const
{
	boost::lock_guard<boost::mutex> eventLock(eventMutex);

	return allEventReceivers;
}
