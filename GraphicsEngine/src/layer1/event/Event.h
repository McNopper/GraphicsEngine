/*
 * Event.h
 *
 *  Created on: 07.01.2013
 *      Author: nopper
 */

#ifndef EVENT_H_
#define EVENT_H_

#include "../../UsedLibs.h"

#include "EventReceiver.h"

class Event
{

private:

	const EventReceiverSP eventReceiver;

public:

	Event(const EventReceiverSP& eventReceiver);

	virtual ~Event();

	const EventReceiverSP& getEventReceiver() const;

};

typedef std::shared_ptr<Event> EventSP;

#endif /* EVENT_H_ */
