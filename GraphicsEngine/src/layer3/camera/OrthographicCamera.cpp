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

	glusMatrix4x4Orthof(result, -width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, zNear, zFar);

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

	glusMatrix4x4Orthof(result, -width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, zNear, zFar);

	projectionMatrix.setM(result);

	biasedProjectionMatrix = biasMatrix * projectionMatrix;

	updateViewFrustum();
}

void OrthographicCamera::adjustToFrustum(const ViewFrustum& viewFrustum, int32_t section, const Point4& lightPosition, const Quaternion& lightRotation)
{
	const vector<Point4>& frustumPoints = viewFrustum.getFrustumPoints();

	Vector3 lightForward = lightRotation * Vector3(1.0f, 0.0f, 0.0f);
	Vector3 lightRight = lightRotation * Vector3(0.0f, 0.0f, -1.0f);
	Vector3 lightUp = lightRotation * Vector3(0.0f, -1.0f, 0.0f);

	Vector3 min;
	Vector3 max;
	for (int32_t i = section * 4; i < section * 4 + 8; i++)
	{
		Vector3 v = frustumPoints[i] - Point4(0.0, 0.0, 0.0);

		Vector3 temp;

		temp[0] = lightRight.dot(v);
		temp[1] = lightUp.dot(v);
		temp[2] = lightForward.dot(v);

		if (i == section * 4)
		{
			for (int32_t k = 0; k < 3; k++)
			{
				min[k] = max[k] = temp[k];
			}
		}
		else
		{
			for (int32_t k = 0; k < 3; k++)
			{
				if (temp[k] < min[k])
				{
					min[k] = temp[k];
				}
				if (temp[k] > max[k])
				{
					max[k] = temp[k];
				}
			}
		}
	}

	//

	float orthographicScale = glusMathMaxf(abs(max[0] - min[0]), abs(max[1] - min[1]));

	orthographic(orthographicScale, orthographicScale, 0.1f, 1000.0f);

	//

	Vector3 offset(0.0f, 0.0f, 0.0f);

	offset += lightRight * ((max[0] + min[0]) / 2.0f);
	offset += lightUp * ((max[1] + min[1]) / 2.0f);

	if (min[2] <= 0.0)
	{
		offset += lightForward * min[2];
	}

	//

	transitionMatrix.identity();

	transitionMatrix.translate(lightPosition.getX() + offset.getX(), lightPosition.getY() + offset.getY(), lightPosition.getZ() + offset.getZ());

	transitionMatrix *= lightRotation.getRotationMatrix4x4();

	Point4 eye = transitionMatrix * Point4();
	Point4 center = transitionMatrix * Point4(1.0f, 0.0f, 0.0f);
	Vector3 up = transitionMatrix * Vector3(0.0f, 1.0f, 0.0f);

	lookAt(eye, center, up);

	lastPosition = lightPosition + offset;
	lastRotation = lightRotation;
}
