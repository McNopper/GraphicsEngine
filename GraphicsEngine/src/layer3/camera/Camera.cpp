/*
 * Camera.cpp
 *
 *  Created on: 23.04.2011
 *      Author: Norbert Nopper
 */

#include "../../layer1/shader/Variables.h"
#include "../../layer2/debug/DebugDraw.h"

#include "Camera.h"

using namespace std;

const float Camera::getDebugRadius()
{
	return 2.0f;
}

Camera::Camera(const string& name) :
	name(name), dirty(true), eye(0.0f, 0.0f, 0.0f), center(1.0f, 0.0f, 0.0f), up(0.0f, 1.0f, 0.0f), direction(1.0f, 0.0f, 0.0f), viewport(), zNear(0.1f), zFar(1000.0f), biasMatrix(), viewFrustum(), lastPosition(), lastRotation(), transitionMatrix(), width(1.0f), height(1.0f), frustumZs()
{
	// Needed to range values between 0 and 1
	biasMatrix.identity();
	biasMatrix.translate(0.5f, 0.5f, 0.5f);
	biasMatrix.scale(0.5f, 0.5f, 0.5f);
}

Camera::Camera(const Camera& other) :
	name(other.name), dirty(other.dirty), eye(other.eye), center(other.center), up(other.up), direction(other.direction), viewport(other.viewport), zNear(other.zNear), zFar(other.zFar), viewFrustum(other.viewFrustum), lastPosition(other.lastPosition), lastRotation(other.lastRotation), width(other.width), height(other.height), frustumZs(other.frustumZs)
{
	viewMatrix = other.viewMatrix;
	projectionMatrix = other.projectionMatrix;
	biasedProjectionMatrix = other.projectionMatrix;
	biasMatrix = other.biasMatrix;
	transitionMatrix = other.transitionMatrix;
}

Camera::~Camera()
{
	frustumZs.clear();
}

const string& Camera::getName() const
{
	return name;
}

void Camera::updateViewFrustum()
{
	viewFrustum.transformToWorldSpace(*this);

	frustumZs.clear();

	float zNDC, zCurrent;
	for (int32_t i = 0; i <= viewFrustum.getNumberSections(); i++)
	{
		zCurrent = -(zNear + (zFar - zNear) * static_cast<float>(i) / static_cast<float>(viewFrustum.getNumberSections()));

		// see http://www.songho.ca/opengl/gl_projectionmatrix.html
		zNDC = (-(zFar + zNear) / (zFar - zNear) * zCurrent + (-2.0f * zFar * zNear) / (zFar - zNear)) / -zCurrent;

		frustumZs.push_back(glusMathClampf(zNDC, -1.0f, 1.0f));
	}
}

void Camera::lookAt(const Point4& eye, const Point4& center, const Vector3& up)
{
	float result[16];

	this->eye = eye;
	this->center = center;
	this->up = up;
	this->direction = (center - eye).normalize();

	Vector3 left = up.cross(direction).normalize();

	this->up = direction.cross(left).normalize();

	glusMatrix4x4LookAtf(result, eye.getX(), eye.getY(), eye.getZ(), center.getX(), center.getY(), center.getZ(), up.getX(), up.getY(), up.getZ());

	viewMatrix.setM(result);

	updateViewFrustum();
}

void Camera::updateWindowViewport(const Viewport& viewport)
{
	this->viewport = viewport;

	lookAt(this->eye, this->center, this->up);

	updateProjectionMatrix();
}

void Camera::setViewport(const Viewport& viewport)
{
	this->viewport = viewport;
}

const Point4& Camera::getEye() const
{
	return eye;
}

const Vector3& Camera::getDirection() const
{
	return direction;
}

const Vector3& Camera::getUp() const
{
	return up;
}

void Camera::setNearZ(float zNear)
{
	this->zNear = zNear;
}

float Camera::getNearZ() const
{
	return zNear;
}

void Camera::setFarZ(float zFar)
{
	this->zFar = zFar;
}

float Camera::getFarZ() const
{
	return zFar;
}

const Viewport& Camera::getViewport() const
{
	return viewport;
}

const Matrix4x4& Camera::getViewMatrix() const
{
	return viewMatrix;
}

const Matrix4x4& Camera::getProjectionMatrix() const
{
	return projectionMatrix;
}

const Matrix4x4& Camera::getBiasedProjectionMatrix() const
{
	return biasedProjectionMatrix;
}

const ViewFrustum& Camera::getViewFrustum() const
{
	return viewFrustum;
}

const vector<float>& Camera::getFrustumZs() const
{
	return frustumZs;
}

void Camera::setNumberSections(int32_t sections)
{
	viewFrustum.setNumberSections(sections);
}

float Camera::distanceToCamera(const BoundingSphere& boundingSphere) const
{
	return (boundingSphere.getCenter() - eye).length();
}

void Camera::setCameraProperties(const ProgramSP& program, const Point4& position, const Quaternion& rotation, bool useLocation)
{
	if (useLocation && (position != lastPosition || rotation != lastRotation || dirty))
	{
		transitionMatrix.identity();

		transitionMatrix.translate(position.getX(), position.getY(), position.getZ());

		transitionMatrix *= rotation.getRotationMatrix4x4();

		Point4 eye = transitionMatrix * Point4();
		Point4 center = transitionMatrix * Point4(1.0f, 0.0f, 0.0f);
		Vector3 up = transitionMatrix * Vector3(0.0f, 1.0f, 0.0f);

		lookAt(eye, center, up);

		lastPosition = position;
		lastRotation = rotation;

		dirty = false;
	}

	glUniformMatrix4fv(program->getUniformLocation(u_projectionMatrix), 1, GL_FALSE, projectionMatrix.getM());

	glUniformMatrix4fv(program->getUniformLocation(u_viewMatrix), 1, GL_FALSE, viewMatrix.getM());

	glUniform4fv(program->getUniformLocation(u_eyePosition), 1, eye.getP());

	//

	glUniform4fv(program->getUniformLocation(u_frustumZs), 1, &frustumZs[0]);
}

void Camera::debugDraw(const Point4& position, const Quaternion& rotation, bool useLocation) const
{
	if (useLocation)
	{
		Quaternion baseRotation(-90.0f, Vector3(0.0f, 1.0f, 0.0f));

		baseRotation *= Quaternion(90.0f, Vector3(1.0f, 0.0f, 0.0f));

		DebugDraw::drawer.drawPyramid(position, Vector3(0.0f, -0.5f, 0.0f), rotation * baseRotation, getNearWidth() / zNear * 0.5f, getNearHeight() / zNear * 0.5f, 0.5f, Color::BLUE);
	}
	else
	{
		Vector3 right = direction.cross(up);
		Matrix3x3 rotationMatrix(right, up, -direction);
		Quaternion cameraRotation(rotationMatrix);

		Quaternion baseRotation(90.0f, Vector3(1.0f, 0.0f, 0.0f));

		DebugDraw::drawer.drawPyramid(eye, Vector3(0.0f, -0.5f, 0.0f), cameraRotation * baseRotation, getNearWidth() / zNear * 0.5f, getNearHeight() / zNear * 0.5f, 0.5f, Color::BLUE);
	}
}
