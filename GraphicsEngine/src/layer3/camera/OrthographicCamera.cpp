/*
 * OrthographicCamera.cpp
 *
 *  Created on: 14.09.2012
 *      Author: nopper
 */

#include "../../UsedLibs.h"

#include "OrthographicCamera.h"

using namespace std;

OrthographicCamera::OrthographicCamera(const string& name) :
		Camera(name)
{
}

OrthographicCamera::OrthographicCamera(const OrthographicCamera& other) :
		Camera(other)
{
}

OrthographicCamera::~OrthographicCamera()
{
}

void OrthographicCamera::updateProjectionMatrix()
{
	orthographic(viewport, zNear, zFar);
}

float OrthographicCamera::getNearWidth() const
{
	return width;
}

float OrthographicCamera::getNearHeight() const
{
	return height;
}

float OrthographicCamera::getFarWidth() const
{
	return width;
}

float OrthographicCamera::getFarHeight() const
{
	return height;
}

void OrthographicCamera::orthographic(const Viewport& viewport, float zNear, float zFar)
{
	float result[16];

	this->viewport = viewport;
	this->zNear = zNear;
	this->zFar = zFar;
	this->width = static_cast<float>(viewport.getWidth());
	this->height = static_cast<float>(viewport.getHeight());

	glusOrthof(result, -width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, zNear, zFar);

	projectionMatrix.setM(result);

	biasedProjectionMatrix = biasMatrix * projectionMatrix;

	updateViewFrustum();
}

void OrthographicCamera::orthographic(float width, float height, float zNear, float zFar)
{
	float result[16];

	this->zNear = zNear;
	this->zFar = zFar;
	this->width = width;
	this->height = height;

	glusOrthof(result, -width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, zNear, zFar);

	projectionMatrix.setM(result);

	biasedProjectionMatrix = biasMatrix * projectionMatrix;

	updateViewFrustum();
}
