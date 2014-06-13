/*
 * Camera.h
 *
 *  Created on: 23.04.2011
 *      Author: Norbert Nopper
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "../../UsedLibs.h"

#include "../../layer0/math/Point4.h"
#include "../../layer0/math/Quaternion.h"
#include "../../layer0/math/Vector3.h"
#include "../../layer0/math/Matrix4x4.h"
#include "../../layer1/shader/Program.h"
#include "ViewFrustum.h"
#include "Viewport.h"

class Camera
{

private:

	std::string name;

	bool dirty;

protected:

	Point4 eye;
	Point4 center;
	Vector3 up;
	Vector3 direction;
	Matrix4x4 viewMatrix;

	Viewport viewport;
	float zNear;
	float zFar;
	Matrix4x4 projectionMatrix;
	Matrix4x4 biasedProjectionMatrix;
	Matrix4x4 biasMatrix;

	ViewFrustum viewFrustum;

	Point4 lastPosition;
	Quaternion lastRotation;

	Matrix4x4 transitionMatrix;

	float width;

	float height;

	/*
	 * Stored as NDC.
	 */
	std::vector<float> frustumZs;

	void updateViewFrustum();

public:

	Camera(const std::string& name);
	Camera(const Camera& other);
	virtual ~Camera();

	static const float getDebugRadius();

	const std::string& getName() const;

	void lookAt(const Point4& eye, const Point4& center, const Vector3& up);

	virtual void updateProjectionMatrix() = 0;

	void updateWindowViewport(const Viewport& viewport);

	void setViewport(const Viewport& viewport);

	const Point4& getEye() const;

	const Vector3& getDirection() const;

	const Vector3& getUp() const;

	void setNearZ(float zNear);
	float getNearZ() const;

	void setFarZ(float zFar);
	float getFarZ() const;

	const Viewport& getViewport() const;

	virtual float getNearWidth() const = 0;

	virtual float getNearHeight() const = 0;

	virtual float getFarWidth() const = 0;

	virtual float getFarHeight() const = 0;

	const Matrix4x4& getViewMatrix() const;

	const Matrix4x4& getProjectionMatrix() const;

	const Matrix4x4& getBiasedProjectionMatrix() const;

	/**
	 * View Frustum is in world space.
	 */
	const ViewFrustum& getViewFrustum() const;

	const std::vector<float>& getFrustumZs() const;

	void setNumberSections(std::int32_t sections);

	float distanceToCamera(const BoundingSphere& boundingSphere) const;

	void setCameraProperties(const ProgramSP& program, const Point4& position, const Quaternion& rotation, bool useLocation = false);

	virtual void debugDraw(const Point4& position, const Quaternion& rotation, bool useLocation = false) const;

};

typedef std::shared_ptr<Camera> CameraSP;

#endif /* CAMERA_H_ */
