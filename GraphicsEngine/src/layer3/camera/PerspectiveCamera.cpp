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
		float d = static_cast<float>(viewport.getHeight()) / tanf(glusDegToRadf(fovy / 2.0f));

		fovx = glusRadToDegf(atanf(static_cast<float>(viewport.getWidth()) / d)) * 2.0f;

		fovxDirty = false;
	}
	else if (fovyDirty)
	{
		float d = static_cast<float>(viewport.getWidth()) / tanf(glusDegToRadf(fovx / 2.0f));

		fovy = glusRadToDegf(atanf(static_cast<float>(viewport.getHeight()) / d)) * 2.0f;

		fovyDirty = false;
	}

	perspective(fovy, viewport, zNear, zFar);
}

float PerspectiveCamera::getNearWidth() const
{
	return (float)viewport.getWidth() / (float)viewport.getHeight() * getNearHeight();
}

float PerspectiveCamera::getNearHeight() const
{
	return 2.0f * tanf(fovy * GLUS_PI / 360.0f) * zNear;
}

float PerspectiveCamera::getFarWidth() const
{
	return (float)viewport.getWidth() / (float)viewport.getHeight() * getFarHeight();
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

	glusPerspectivef(result, fovy, (float)viewport.getWidth() / (float)viewport.getHeight(), zNear, zFar);

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
