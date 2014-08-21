/*
 * PerspectiveCamera.cpp
 *
 *  Created on: 14.09.2012
 *      Author: nopper
 */

#include "../../UsedLibs.h"

#include "PerspectiveCamera.h"

using namespace std;

PerspectiveCamera::PerspectiveCamera(const string& name) : Camera(name), fovx(40.0f), fovy(40.0f), fovxDirty(false), fovyDirty(false)
{
}

PerspectiveCamera::PerspectiveCamera(const PerspectiveCamera& other) : Camera(other), fovx(other.fovx), fovy(other.fovy), fovxDirty(other.fovxDirty), fovyDirty(other.fovyDirty)
{
}

PerspectiveCamera::~PerspectiveCamera()
{
}

void PerspectiveCamera::updateProjectionMatrix()
{
	if (fovxDirty)
	{
		float d = static_cast<float>(viewport.getHeight()) / tanf(glusMathDegToRadf(fovy / 2.0f));

		fovx = glusMathRadToDegf(atanf(static_cast<float>(viewport.getWidth()) / d)) * 2.0f;

		fovxDirty = false;
	}
	else if (fovyDirty)
	{
		float d = static_cast<float>(viewport.getWidth()) / tanf(glusMathDegToRadf(fovx / 2.0f));

		fovy = glusMathRadToDegf(atanf(static_cast<float>(viewport.getHeight()) / d)) * 2.0f;

		fovyDirty = false;
	}

	perspective(fovy, viewport, zNear, zFar);
}

float PerspectiveCamera::getNearWidth() const
{
	return width / height * getNearHeight();
}

float PerspectiveCamera::getNearHeight() const
{
	return 2.0f * tanf(fovy * GLUS_PI / 360.0f) * zNear;
}

float PerspectiveCamera::getFarWidth() const
{
	return width / height * getFarHeight();
}

float PerspectiveCamera::getFarHeight() const
{
	return 2.0f * tanf(fovy * GLUS_PI / 360.0f) * zFar;
}

void PerspectiveCamera::perspective(float fovy, const Viewport& viewport, float zNear, float zFar)
{
	float result[16];

	this->fovy = fovy;
	this->viewport = viewport;
	this->zNear = zNear;
	this->zFar = zFar;
	this->width = static_cast<float>(viewport.getWidth());
	this->height = static_cast<float>(viewport.getHeight());

	glusMatrix4x4Perspectivef(result, fovy, width / height, zNear, zFar);

	projectionMatrix.setM(result);

	biasedProjectionMatrix = biasMatrix * projectionMatrix;

	updateViewFrustum();
}

void PerspectiveCamera::perspective(float fovy, float width, float height, float zNear, float zFar)
{
	float result[16];

	this->fovy = fovy;
	this->zNear = zNear;
	this->zFar = zFar;
	this->width = width;
	this->height = height;

	glusMatrix4x4Perspectivef(result, fovy, width / height, zNear, zFar);

	projectionMatrix.setM(result);

	biasedProjectionMatrix = biasMatrix * projectionMatrix;

	updateViewFrustum();
}

void PerspectiveCamera::setFovx(float fovx)
{
	this->fovx = fovx;

	fovxDirty = false;
	fovyDirty = true;
}

void PerspectiveCamera::setFovy(float fovy)
{
	this->fovy = fovy;

	fovxDirty = true;
	fovyDirty = false;
}
