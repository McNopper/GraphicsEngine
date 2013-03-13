/*
 * OrientedCirclePath.h
 *
 *  Created on: 13.03.2013
 *      Author: nopper
 */

#ifndef ORIENTEDCIRCLEPATH_H_
#define ORIENTEDCIRCLEPATH_H_

#include "CirclePath.h"

class OrientedCirclePath : public CirclePath
{

protected:

	virtual void start();

	/**
	 * @return true, if end of path reached. If looping, always false.
	 */
	virtual bool update(float deltaTime, Geometry& geometry, bool updateOrientation = true);

public:

	OrientedCirclePath(const Quaternion& baseRotation, const Point4& startLocation, const Point4& orbitPoint, bool clockWise);

	virtual ~OrientedCirclePath();

};

#endif /* ORIENTEDCIRCLEPATH_H_ */
