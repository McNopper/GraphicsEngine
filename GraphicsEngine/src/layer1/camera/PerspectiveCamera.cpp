/*
 * PerspectiveCamera.cpp
 *
 *  Created on: 14.09.2012
 *      Author: nopper
 */

#include "../../UsedLibs.h"

#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera() : Camera(), fovy(40.0f)
{
	updateProjectionMatrix();
}

PerspectiveCamera::PerspectiveCamera(const PerspectiveCamera& other) : Camera(other), fovy(other.fovy)
{
	updateProjectionMatrix();
}

PerspectiveCamera::~PerspectiveCamera()
{
}

void PerspectiveCamera::updateProjectionMatrix()
{
	perspective(fovy, viewport, zNear, zFar);
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

	updateViewFrustum();
}

