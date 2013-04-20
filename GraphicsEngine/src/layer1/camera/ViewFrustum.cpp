/*
 * ViewFrustum.cpp
 *
 *  Created on: 24.04.2011
 *      Author: Norbert Nopper
 */

#include "Camera.h"

#include "ViewFrustum.h"

using namespace std;

using namespace boost;

Plane ViewFrustum::SIDES_NDC[6] = { Plane(Vector3(0.0f, 0.0f, 1.0f), 1.0f),
								Plane(Vector3(0.0f, 0.0f, -1.0f), 1.0f),
								Plane(Vector3(1.0f, 0.0f, 0.0f), 1.0f),
								Plane(Vector3(-1.0f, 0.0f, .0f), 1.0f),
								Plane(Vector3(0.0f, 1.0f, 0.0f), 1.0f),
								Plane(Vector3(0.0f, -1.0f, 0.0f), 1.0f)
							  };

ViewFrustum::ViewFrustum()
{
}

ViewFrustum::ViewFrustum(const ViewFrustum& other)
{
	sides[NEAR_PLANE] = other.sides[NEAR_PLANE];
	sides[FAR_PLANE] = other.sides[FAR_PLANE];
	sides[LEFT_PLANE] = other.sides[LEFT_PLANE];
	sides[RIGHT_PLANE] = other.sides[RIGHT_PLANE];
	sides[BOTTOM_PLANE] = other.sides[BOTTOM_PLANE];
	sides[TOP_PLANE] = other.sides[TOP_PLANE];

	points[NEAR_TOP_LEFT] = other.points[NEAR_TOP_LEFT];
	points[NEAR_TOP_RIGHT] = other.points[NEAR_TOP_RIGHT];
	points[NEAR_BOTTOM_LEFT] = other.points[NEAR_BOTTOM_LEFT];
	points[NEAR_BOTTOM_RIGHT] = other.points[NEAR_BOTTOM_RIGHT];
	points[FAR_TOP_LEFT] = other.points[FAR_TOP_LEFT];
	points[FAR_TOP_RIGHT] = other.points[FAR_TOP_RIGHT];
	points[FAR_BOTTOM_LEFT] = other.points[FAR_BOTTOM_LEFT];
	points[FAR_BOTTOM_RIGHT] = other.points[FAR_BOTTOM_RIGHT];
}

ViewFrustum::~ViewFrustum()
{
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

	Vector3 right = camera.getDirection().cross(camera.getUp());

	Vector3 nearRight = right * (camera.getNearWidth() / 2.0f);
	Vector3 nearUp = camera.getUp() * (camera.getNearHeight() / 2.0f);
	Vector3 farRight = right * (camera.getFarWidth() / 2.0f);
	Vector3 farUp = camera.getUp() * (camera.getFarHeight() / 2.0f);

	Point4 nearCenter = camera.getEye() + camera.getDirection() * camera.getNearZ();
	Point4 farCenter = camera.getEye() + camera.getDirection() * camera.getFarZ();

	points[NEAR_TOP_LEFT] = nearCenter + nearUp - nearRight;
	points[NEAR_TOP_RIGHT] = nearCenter + nearUp + nearRight;
	points[NEAR_BOTTOM_LEFT] = nearCenter - nearUp - nearRight;
	points[NEAR_BOTTOM_RIGHT] = nearCenter - nearUp + nearRight;
	points[FAR_TOP_LEFT] = farCenter + farUp - farRight;
	points[FAR_TOP_RIGHT] = farCenter + farUp + farRight;
	points[FAR_BOTTOM_LEFT] = farCenter - farUp - farRight;
	points[FAR_BOTTOM_RIGHT] = farCenter - farUp + farRight;
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
