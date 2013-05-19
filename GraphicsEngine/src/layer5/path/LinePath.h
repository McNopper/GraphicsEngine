/*
 * LinePath.h
 *
 *  Created on: 12.03.2013
 *      Author: nopper
 */

#ifndef LINEPATH_H_
#define LINEPATH_H_

#include "../../layer0/math/Point4.h"

#include "Path.h"

class LinePath : public Path
{

protected:

	Point4 startLocation;

	Point4 endLocation;

	Vector3 direction;

	bool goToEnd;

protected:

	virtual void start();

	/**
	 * @return true, if end of path reached. If looping, always false.
	 */
	virtual bool update(float deltaTime, const GeneralEntitySP& entity, bool updateOrientation = true);

public:

	LinePath(const Quaternion& baseRotation, const Point4& startLocation, const Point4& endLocation);
	virtual ~LinePath();

};

#endif /* LINEPATH_H_ */
