/*
 * DebugDrawFactory.h
 *
 *  Created on: 21.09.2012
 *      Author: nopper
 */

#ifndef DEBUGDRAWFACTORY_H_
#define DEBUGDRAWFACTORY_H_

class DebugDrawFactory
{
public:
	DebugDrawFactory();
	virtual ~DebugDrawFactory();

	void createDefaultDebugGeometry() const;
};

#endif /* DEBUGDRAWFACTORY_H_ */
