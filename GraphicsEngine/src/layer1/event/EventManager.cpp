/*
 * EventManager.cpp
 *
 *  Created on: 07.01.2013
 *      Author: nopper
 */

#include "EventManager.h"

EventManager::EventManager() :
		Singleton<EventManager>(), eventMutex(), allEvents(), allEventReceivers()
{
}

EventManager::~EventManager()
{
	std::lock_guard<std::mutex> eventLock(eventMutex);

	EventSP currentEvent;

	while (allEvents.take(currentEvent))
	{
		currentEvent.reset();
	}

	allEventReceivers.clear();
}

void EventManager::processEvents()
{
	std::lock_guard<std::mutex> eventLock(eventMutex);

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
	std::lock_guard<std::mutex> eventLock(eventMutex);

	allEventReceivers.add(receiver);
}

void EventManager::removeEventReceiver(const EventReceiverSP& receiver)
{
	std::lock_guard<std::mutex> eventLock(eventMutex);

	allEventReceivers.remove(receiver);
}

/**
 * This method is non-blocking by purpose. Also, events are handled asynchronous.
 */
void EventManager::sendEvent(const EventSP& event)
{
	allEvents.add(event);
}

const ValueVector<EventReceiverSP>& EventManager::getEventReceivers() const
{
	std::lock_guard<std::mutex> eventLock(eventMutex);

	return allEventReceivers;
}
