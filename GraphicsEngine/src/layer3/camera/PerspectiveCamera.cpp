/*
 * PerspectiveCamera.cpp
 *
 *  Created on: 14.09.2012
 *      Author: nopper
 */

#include "../../UsedLibs.h"

#include "PerspectiveCamera.h"

using namespace std;

PerspectiveCamera::PerspectiveCamera(const string& name) : Camera(name), fovy(40.0f)
{
}

PerspectiveCamera::PerspectiveCamera(const PerspectiveCamera& other) : Camera(other), fovy(other.fovy)
{
}

PerspectiveCamera::~PerspectiveCamera()
{
}

void PerspectiveCamera::updateProjectionMatrix()
{
	perspective(fovy, viewport, zNear, zFar);
}

float PerspectiveCamera::getNearWidth() const
{
	return (float)viewport.getWidth() / (float)viewport.getHeight() * getNearHeight();
}

float PerspectiveCamera::getNearHeight() const
{
	return tanf(2.0f * fovy * GLUS_PI / 360.0f) * zNear;
}

float PerspectiveCamera::getFarWidth() const
{
	return (float)viewport.getWidth() / (float)viewport.getHeight() * getFarHeight();
}

float PerspectiveCamera::getFarHeight() const
{
	return tanf(2.0f * fovy * GLUS_PI / 360.0f) * zFar;
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

