/*
 * ViewFrustum.cpp
 *
 *  Created on: 24.04.2011
 *      Author: Norbert Nopper
 */

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
}

ViewFrustum::~ViewFrustum()
{
}

void ViewFrustum::transformToWorldSpace(const Matrix4x4& transposedViewProjectionMatrix)
{
	sides[NEAR_PLANE] = transposedViewProjectionMatrix * SIDES_NDC[NEAR_PLANE];
	sides[FAR_PLANE] = transposedViewProjectionMatrix * SIDES_NDC[FAR_PLANE];
	sides[LEFT_PLANE] = transposedViewProjectionMatrix * SIDES_NDC[LEFT_PLANE];
	sides[RIGHT_PLANE] = transposedViewProjectionMatrix * SIDES_NDC[RIGHT_PLANE];
	sides[BOTTOM_PLANE] = transposedViewProjectionMatrix * SIDES_NDC[BOTTOM_PLANE];
	sides[TOP_PLANE] = transposedViewProjectionMatrix * SIDES_NDC[TOP_PLANE];
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
