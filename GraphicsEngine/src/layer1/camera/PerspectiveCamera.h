/*
 * PerspectiveCamera.h
 *
 *  Created on: 14.09.2012
 *      Author: nopper
 */

#ifndef PERSPECTIVECAMERA_H_
#define PERSPECTIVECAMERA_H_

#include "Camera.h"

class PerspectiveCamera : public Camera
{

private:

	float fovy;

public:
	PerspectiveCamera();
	PerspectiveCamera(const PerspectiveCamera& other);
	virtual ~PerspectiveCamera();

	virtual void updateProjectionMatrix();

	virtual float getNearWidth() const;

	virtual float getNearHeight() const;

	virtual float getFarWidth() const;

	virtual float getFarHeight() const;

	void perspective(float fovy, const Viewport& viewport, float zNear, float zFar);
};

typedef boost::shared_ptr<PerspectiveCamera> PerspectiveCameraSP;

#endif /* PERSPECTIVECAMERA_H_ */
