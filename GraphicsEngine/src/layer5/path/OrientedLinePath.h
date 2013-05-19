/*
 * OrientedLinePath.h
 *
 *  Created on: 13.03.2013
 *      Author: nopper
 */

#ifndef ORIENTEDLINEPATH_H_
#define ORIENTEDLINEPATH_H_

#include "LinePath.h"

class OrientedLinePath : public LinePath
{

protected:

	virtual void start();

	/**
	 * @return true, if end of path reached. If looping, always false.
	 */
	virtual bool update(float deltaTime, const GeneralEntitySP& entity, bool updateOrientation = true);

public:

	OrientedLinePath(const Quaternion& baseRotation, const Point4& startLocation, const Point4& endLocation);
	virtual ~OrientedLinePath();

};

#endif /* ORIENTEDLINEPATH_H_ */
