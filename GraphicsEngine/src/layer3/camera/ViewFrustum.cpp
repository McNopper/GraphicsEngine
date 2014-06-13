/*
 * ViewFrustum.cpp
 *
 *  Created on: 24.04.2011
 *      Author: Norbert Nopper
 */

#include "Camera.h"

#include "ViewFrustum.h"

using namespace std;

Plane ViewFrustum::SIDES_NDC[6] = { Plane(Vector3(0.0f, 0.0f, 1.0f), 1.0f), Plane(Vector3(0.0f, 0.0f, -1.0f), 1.0f), Plane(Vector3(1.0f, 0.0f, 0.0f), 1.0f), Plane(Vector3(-1.0f, 0.0f, .0f), 1.0f), Plane(Vector3(0.0f, 1.0f, 0.0f), 1.0f), Plane(Vector3(0.0f, -1.0f, 0.0f), 1.0f) };

ViewFrustum::ViewFrustum()
{
	setNumberSections(1);
}

ViewFrustum::ViewFrustum(const ViewFrustum& other)
{
	sides[NEAR_PLANE] = other.sides[NEAR_PLANE];
	sides[FAR_PLANE] = other.sides[FAR_PLANE];
	sides[LEFT_PLANE] = other.sides[LEFT_PLANE];
	sides[RIGHT_PLANE] = other.sides[RIGHT_PLANE];
	sides[BOTTOM_PLANE] = other.sides[BOTTOM_PLANE];
	sides[TOP_PLANE] = other.sides[TOP_PLANE];

	frustumPoints = other.frustumPoints;

	sections = other.sections;
}

ViewFrustum::~ViewFrustum()
{
	frustumPoints.clear();
}

void ViewFrustum::transformToWorldSpace(const Camera& camera)
{
	Matrix4x4 transposedViewProjectionMatrix = camera.getProjectionMatrix() * camera.getViewMatrix();
	transposedViewProjectionMatrix.transpose();

	sides[NEAR_PLANE] = transposedViewProjectionMatrix * SIDES_NDC[NEAR_PLANE];
	sides[FAR_PLANE] = transposedViewProjectionMatrix * SIDES_NDC[FAR_PLANE];
	sides[LEFT_PLANE] = transposedViewProjectionMatrix * SIDES_NDC[LEFT_PLANE];
	sides[RIGHT_PLANE] = transposedViewProjectionMatrix * SIDES_NDC[RIGHT_PLANE];
	sides[BOTTOM_PLANE] = transposedViewProjectionMatrix * SIDES_NDC[BOTTOM_PLANE];
	sides[TOP_PLANE] = transposedViewProjectionMatrix * SIDES_NDC[TOP_PLANE];

	//

	Vector3 right = camera.getDirection().cross(camera.getUp());

	Vector3 nearRight = right * (camera.getNearWidth() / 2.0f);
	Vector3 nearUp = camera.getUp() * (camera.getNearHeight() / 2.0f);
	Point4 nearCenter = camera.getEye() + camera.getDirection() * camera.getNearZ();

	Vector3 farRight = right * (camera.getFarWidth() / 2.0f);
	Vector3 farUp = camera.getUp() * (camera.getFarHeight() / 2.0f);
	Point4 farCenter = camera.getEye() + camera.getDirection() * camera.getFarZ();

	Point4 nearTopLeft = nearCenter + nearUp - nearRight;
	Point4 nearTopRight = nearCenter + nearUp + nearRight;
	Point4 nearBottomLeft = nearCenter - nearUp - nearRight;
	Point4 nearBottomRight = nearCenter - nearUp + nearRight;
	Point4 farTopLeft = farCenter + farUp - farRight;
	Point4 farTopRight = farCenter + farUp + farRight;
	Point4 farBottomLeft = farCenter - farUp - farRight;
	Point4 farBottomRight = farCenter - farUp + farRight;

	float sectionsDepth = 1.0f / static_cast<float>(sections);
	float currentSectionsDepth;

	for (int32_t i = 0; i <= getNumberSections(); i++)
	{
		currentSectionsDepth = sectionsDepth * static_cast<float>(i);

		frustumPoints[i * 4 + 0] = nearTopLeft + (farTopLeft - nearTopLeft) * currentSectionsDepth;
		frustumPoints[i * 4 + 1] = nearTopRight + (farTopRight - nearTopRight) * currentSectionsDepth;
		frustumPoints[i * 4 + 2] = nearBottomLeft + (farBottomLeft - nearBottomLeft) * currentSectionsDepth;
		frustumPoints[i * 4 + 3] = nearBottomRight + (farBottomRight - nearBottomRight) * currentSectionsDepth;
	}
}

bool ViewFrustum::isVisible(const BoundingSphere& boundingSphere) const
{
	float distance;

	for (int32_t i = 0; i < 6; i++)
	{
		distance = sides[i].distance(boundingSphere);

		if (distance + boundingSphere.getRadius() < 0.0f)
		{
			return false;
		}
	}

	return true;
}

void ViewFrustum::setNumberSections(int32_t sections)
{
	if (sections <= 0)
	{
		return;
	}

	this->sections = sections;

	frustumPoints.clear();

	for (int32_t i = 0; i < (sections + 1) * 4; i++)
	{
		frustumPoints.push_back(Point4());
	}
}

int32_t ViewFrustum::getNumberSections() const
{
	return sections;
}

const vector<Point4>& ViewFrustum::getFrustumPoints() const
{
	return frustumPoints;
}
