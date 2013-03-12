/*
 * Geometry.h
 *
 *  Created on: 11.03.2013
 *      Author: nopper
 */

#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "Point4.h"
#include "Quaternion.h"

class Geometry
{

protected:

	Geometry()
	{
	}

	virtual ~Geometry()
	{
	}

public:

	virtual void updateLocation(const Point4& location) = 0;

	virtual void updateOrientation(const Quaternion& orientation) = 0;

	virtual void updateLocationOrientation(const Point4& location, const Quaternion& orientation) = 0;

};

#endif /* GEOMETRY_H_ */
