/*
 * OrthographicCamera.h
 *
 *  Created on: 14.09.2012
 *      Author: nopper
 */

#ifndef ORTHOGRAPHICCAMERA_H_
#define ORTHOGRAPHICCAMERA_H_

#include "Camera.h"

class OrthographicCamera : public Camera
{
public:
	OrthographicCamera();
	OrthographicCamera(const OrthographicCamera& other);
	virtual ~OrthographicCamera();

	virtual void updateProjectionMatrix();

	void orthographic(const Viewport& viewport, float nearVal, float farVal);
};

#endif /* ORTHOGRAPHICCAMERA_H_ */
