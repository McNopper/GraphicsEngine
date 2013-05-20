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

	Point4 startPosition;

	Point4 endPosition;

	Vector3 direction;

	bool goToEnd;

protected:

	virtual void start();

	/**
	 * @return true, if end of path reached. If looping, always false.
	 */
	virtual bool update(float deltaTime, const GeneralEntitySP& entity, bool updateRotation = true);

public:

	LinePath(const Quaternion& baseRotation, const Point4& startPosition, const Point4& endPosition);
	virtual ~LinePath();

};

#endif /* LINEPATH_H_ */
