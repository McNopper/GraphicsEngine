/*
 * EventManager.h
 *
 *  Created on: 07.01.2013
 *      Author: nopper
 */

#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

#include "../../UsedLibs.h"

#include "../../layer0/concurrency/ThreadsafeQueue.h"
#include "../../layer0/stereotype/Singleton.h"
#include "../../layer0/stereotype/ValueVector.h"

#include "Event.h"
#include "EventReceiver.h"

class EventManager : public Singleton<EventManager>
{

	friend class Singleton<EventManager>;

private:

	mutable std::mutex eventMutex;

	ThreadsafeQueue<EventSP> allEvents;

	ValueVector<EventReceiverSP> allEventReceivers;

	EventManager();
	virtual ~EventManager();

public:

	void processEvents();

	void addEventReceiver(const EventReceiverSP& receiver);

	void removeEventReceiver(const EventReceiverSP& receiver);

	//

	void sendEvent(const EventSP& event);

	const ValueVector<EventReceiverSP>& getEventReceivers() const;

};

#endif /* EVENTMANAGER_H_ */
