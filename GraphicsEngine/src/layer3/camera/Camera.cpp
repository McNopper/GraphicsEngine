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
	dirty(true), eye(0.0f, 0.0f, 5.0f), center(0.0f, 0.0f, 0.0f), up(0.0f, 1.0f, 0.0f), direction(0.0f, 0.0f, -1.0f), viewport(), zNear(0.1f), zFar(1000.0f), biasMatrix(), viewFrustum()
{
	// Needed to range values between 0 and 1
	biasMatrix.identity();
	biasMatrix.translate(0.5f, 0.5f, 0.5f);
	biasMatrix.scale(0.5f, 0.5f, 0.5f);
}

Camera::Camera(const Camera& other) :
	dirty(other.dirty), eye(other.eye), center(other.center), up(other.up), viewport(other.viewport), zNear(other.zNear), zFar(other.zFar), biasMatrix(), viewFrustum(other.viewFrustum)
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

void Camera::setPosition(const Point4& position)
{
	this->eye = position;
	this->center = position + direction;

	lookAt(this->eye, this->center, this->up);
}

void Camera::setRotation(float angleZ, float angleY, float angleX)
{
	Matrix4x4 rotationMatrix;
	Vector3 direction(0.0f, 0.0f, -1.0f);
	Vector3 up(0.0f, 1.0f, 0.0f);

	rotationMatrix.rotateRzRyRx(angleZ, angleY, angleX);

	this->center = this->eye + rotationMatrix * direction;
	this->up = rotationMatrix * up;

	lookAt(this->eye, this->center, this->up);
}

void Camera::setRotation(const Quaternion& rotation)
{
	Vector3 direction(0.0f, 0.0f, -1.0f);
	Vector3 up(0.0f, 1.0f, 0.0f);

	this->center = this->eye + rotation * direction;
	this->up = rotation * up;

	lookAt(this->eye, this->center, this->up);
}

void Camera::setPositionRotation(const Point4& position, const Quaternion& rotation)
{
	Vector3 direction(0.0f, 0.0f, -1.0f);
	Vector3 up(0.0f, 1.0f, 0.0f);

	this->eye = position;
	this->center = this->eye + rotation * direction;
	this->up = rotation * up;

	lookAt(this->eye, this->center, this->up);
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

	dirty = false;
}

void Camera::updateViewport(const Viewport& viewport)
{
	this->viewport = viewport;

	if (dirty)
	{
		lookAt(this->eye, this->center, this->up);
	}

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

void Camera::setCameraProperties(const ProgramSP& program) const
{
	glUniformMatrix4fv(program->getUniformLocation(u_projectionMatrix), 1, GL_FALSE, projectionMatrix.getM());

	glUniformMatrix4fv(program->getUniformLocation(u_viewMatrix), 1, GL_FALSE, viewMatrix.getM());

	glUniform4fv(program->getUniformLocation(u_eyePosition), 1, eye.getP());
}

Quaternion Camera::getRotation() const
{
	Vector3 left = up.cross(direction);

	return  Quaternion(Matrix3x3(-left, up, -direction));
}

void Camera::debugDraw() const
{
	Quaternion baseRotation(90.0f, Vector3(1.0f, 0.0f, 0.0f));

	DebugDraw::drawer.drawPyramid(eye, Vector3(0.0f, -0.5f, 0.0f), getRotation() * baseRotation, getNearWidth() / zNear * 0.5f, getNearHeight() / zNear * 0.5f, 0.5f, Color::BLUE);
}
