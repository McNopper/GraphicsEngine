/*
 * Event.cpp
 *
 *  Created on: 07.01.2013
 *      Author: nopper
 */

#include "Event.h"

#include "EventReceiver.h"

Event::Event(const EventReceiverSP& eventReceiver) :
	eventReceiver(eventReceiver)
{
}

Event::~Event()
{
}

const EventReceiverSP& Event::getEventReceiver() const
{
	return eventReceiver;
}
