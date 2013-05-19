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
	virtual bool update(float deltaTime, const GeneralEntitySP& entity, bool updateOrientation = true);

public:

	OrientedCirclePath(const Quaternion& baseRotation, const Point4& startLocation, const Point4& orbitPoint, bool clockWise);
	OrientedCirclePath(const Quaternion& baseRotation, const Point4& startLocation, const Point4& orbitPoint, bool clockWise, const Vector3& rotationAxis);
	virtual ~OrientedCirclePath();

};

#endif /* ORIENTEDCIRCLEPATH_H_ */
