/*
 * Camera.cpp
 *
 *  Created on: 23.04.2011
 *      Author: Norbert Nopper
 */

#include "../../layer1/shader/Variables.h"
#include "../../layer2/debug/DebugDraw.h"

#include "Camera.h"

Camera::Camera() :
	dirty(true), eye(0.0f, 0.0f, 0.0f), center(0.0f, 0.0f, -1.0f), up(0.0f, 1.0f, 0.0f), direction(0.0f, 0.0f, -1.0f), viewport(), zNear(0.1f), zFar(1000.0f), biasMatrix(), viewFrustum(), lastPosition(), lastRotation(), transitionMatrix()
{
	// Needed to range values between 0 and 1
	biasMatrix.identity();
	biasMatrix.translate(0.5f, 0.5f, 0.5f);
	biasMatrix.scale(0.5f, 0.5f, 0.5f);
}

Camera::Camera(const Camera& other) :
	dirty(other.dirty), eye(other.eye), center(other.center), up(other.up), viewport(other.viewport), zNear(other.zNear), zFar(other.zFar), biasMatrix(), viewFrustum(other.viewFrustum), lastPosition(other.lastPosition), lastRotation(other.lastRotation), transitionMatrix(transitionMatrix)
{
	viewMatrix = other.viewMatrix;
	projectionMatrix = other.projectionMatrix;
	biasedProjectionMatrix = other.projectionMatrix;
	biasMatrix = other.biasMatrix;
}

Camera::~Camera()
{
}

void Camera::updateViewFrustum()
{
	viewFrustum.transformToWorldSpace(*this);
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

	glusLookAtf(result, eye.getX(), eye.getY(), eye.getZ(), center.getX(), center.getY(), center.getZ(), up.getX(), up.getY(), up.getZ());

	viewMatrix.setM(result);

	updateViewFrustum();
}

void Camera::updateViewport(const Viewport& viewport)
{
	this->viewport = viewport;

	lookAt(this->eye, this->center, this->up);

	updateProjectionMatrix();
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

float Camera::getNearZ() const
{
	return zNear;
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
		Point4 center = transitionMatrix * Point4(0.0f, 0.0f, -1.0f);
		Vector3 up = transitionMatrix * Vector3(0.0f, 1.0f, 0.0f);

		lookAt(eye, center, up);

		lastPosition = position;
		lastRotation = rotation;

		dirty = true;
	}

	glUniformMatrix4fv(program->getUniformLocation(u_projectionMatrix), 1, GL_FALSE, projectionMatrix.getM());

	glUniformMatrix4fv(program->getUniformLocation(u_viewMatrix), 1, GL_FALSE, viewMatrix.getM());

	glUniform4fv(program->getUniformLocation(u_eyePosition), 1, eye.getP());
}

void Camera::debugDraw(const Point4& position, const Quaternion& rotation, bool useLocation) const
{
	Quaternion baseRotation(90.0f, Vector3(1.0f, 0.0f, 0.0f));

	if (useLocation)
	{
		DebugDraw::drawer.drawPyramid(position, Vector3(0.0f, -0.5f, 0.0f), rotation * baseRotation, getNearWidth() / zNear * 0.5f, getNearHeight() / zNear * 0.5f, 0.5f, Color::BLUE);
	}
	else
	{
		Vector3 right = direction.cross(up);
		Matrix3x3 rotationMatrix(right, up, -direction);
		Quaternion cameraRotation(rotationMatrix);

		DebugDraw::drawer.drawPyramid(eye, Vector3(0.0f, -0.5f, 0.0f), cameraRotation * baseRotation, getNearWidth() / zNear * 0.5f, getNearHeight() / zNear * 0.5f, 0.5f, Color::BLUE);
	}
}
