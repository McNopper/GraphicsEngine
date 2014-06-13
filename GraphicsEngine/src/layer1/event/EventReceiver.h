/*
 * EventReceiver.h
 *
 *  Created on: 07.01.2013
 *      Author: nopper
 */

#ifndef EVENTRECEIVER_H_
#define EVENTRECEIVER_H_

#include "../../UsedLibs.h"

class Event;

class EventReceiver
{

	friend class EventManager;

private:

	virtual void activate() = 0;

	virtual void deactivate() = 0;

	virtual bool processEvent(const Event& event) = 0;

public:

	EventReceiver()
	{
	}

	virtual ~EventReceiver()
	{
	}

};

typedef std::shared_ptr<EventReceiver> EventReceiverSP;

#endif /* EVENTRECEIVER_H_ */
