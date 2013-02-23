/*
 * EventManager.h
 *
 *  Created on: 07.01.2013
 *      Author: nopper
 */

#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

#include "../../UsedLibs.h"

#include "../../layer0/algorithm/ThreadsafeQueue.h"

#include "Event.h"
#include "EventReceiver.h"

class EventManager
{

private:

	static EventManager* instance;

	mutable boost::mutex eventMutex;

	ThreadsafeQueue<EventSP> allEvents;

	std::vector<EventReceiverSP> allEventReceivers;

	EventManager();
	virtual ~EventManager();

public:

	static EventManager* getInstance();

	static void terminate();

	void processEvents();

	void addEventReceiver(const EventReceiverSP& receiver);

	void removeEventReceiver(const EventReceiverSP& receiver);

	//

	void sendEvent(const EventSP& event);

	const std::vector<EventReceiverSP>& getEventReceivers() const;

};

#endif /* EVENTMANAGER_H_ */
