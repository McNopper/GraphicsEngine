/*
 * CirclePath.h
 *
 *  Created on: 13.03.2013
 *      Author: nopper
 */

#ifndef CIRCLEPATH_H_
#define CIRCLEPATH_H_

#include "../../layer0/math/Matrix4x4.h"
#include "../../layer0/math/Point4.h"
#include "../../layer0/math/Vector3.h"

#include "Path.h"

class CirclePath : public Path
{

protected:

	Point4 startLocation;

	Point4 orbitPoint;

	bool clockWise;

	Vector3 rotationAxis;

	float radius;

	Matrix4x4 transform;

	float elapsedAngle;

protected:

	virtual void start();

	/**
	 * @return true, if end of path reached. If looping, always false.
	 */
	virtual bool update(float deltaTime, Geometry& geometry, bool updateOrientation = true);

	float updateTransform();

public:

	CirclePath(const Quaternion& baseRotation, const Point4& startLocation, const Point4& orbitPoint, bool clockWise);
	virtual ~CirclePath();

};

#endif /* CIRCLEPATH_H_ */
