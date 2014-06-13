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

	void orthographic(const Viewport& viewport, float zNear, float zFar);

	void orthographic(float width, float height, float zNear, float zFar);

	void adjustToFrustum(const ViewFrustum& viewFrustum, std::int32_t section, const Point4& lightPosition, const Quaternion& lightRotation);

};

typedef std::shared_ptr<OrthographicCamera> OrthographicCameraSP;

#endif /* ORTHOGRAPHICCAMERA_H_ */
