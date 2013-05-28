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
	OrthographicCamera(const std::string& name);
	OrthographicCamera(const OrthographicCamera& other);
	virtual ~OrthographicCamera();

	virtual void updateProjectionMatrix();

	virtual float getNearWidth() const;

	virtual float getNearHeight() const;

	virtual float getFarWidth() const;

	virtual float getFarHeight() const;

	void orthographic(const Viewport& viewport, float nearVal, float farVal);
};

typedef boost::shared_ptr<OrthographicCamera> OrthographicCameraSP;

#endif /* ORTHOGRAPHICCAMERA_H_ */
