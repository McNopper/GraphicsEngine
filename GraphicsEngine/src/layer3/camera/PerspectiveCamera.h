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

	float fovx;

	float fovy;

	bool fovxDirty;

	bool fovyDirty;

public:
	PerspectiveCamera(const std::string& name);
	PerspectiveCamera(const PerspectiveCamera& other);
	virtual ~PerspectiveCamera();

	virtual void updateProjectionMatrix();

	virtual float getNearWidth() const;

	virtual float getNearHeight() const;

	virtual float getFarWidth() const;

	virtual float getFarHeight() const;

	void perspective(float fovy, const Viewport& viewport, float zNear, float zFar);

	void perspective(float fovy, float width, float height, float zNear, float zFar);

	void setFovx(float fovx);

	void setFovy(float fovy);
};

typedef std::shared_ptr<PerspectiveCamera> PerspectiveCameraSP;

#endif /* PERSPECTIVECAMERA_H_ */
