/*
 * ViewFrustum.h
 *
 *  Created on: 24.04.2011
 *      Author: Norbert Nopper
 */

#ifndef VIEWFRUSTUM_H_
#define VIEWFRUSTUM_H_

#include "../../UsedLibs.h"

#include "../../layer0/math/Plane.h"
#include "../../layer0/math/Point4.h"
#include "../../layer0/math/Matrix4x4.h"
#include "../../layer0/math/Vector3.h"
#include "../collision/BoundingSphere.h"

class Camera;

typedef enum _frustum_sides
{
	NEAR_PLANE,
	FAR_PLANE,
	LEFT_PLANE,
	RIGHT_PLANE,
	BOTTOM_PLANE,
	TOP_PLANE
} frustum_sides;

typedef enum _frustum_points
{
	NEAR_TOP_LEFT,
	NEAR_TOP_RIGHT,
	NEAR_BOTTOM_LEFT,
	NEAR_BOTTOM_RIGHT,
	FAR_TOP_LEFT,
	FAR_TOP_RIGHT,
	FAR_BOTTOM_LEFT,
	FAR_BOTTOM_RIGHT
} frustum_points;

class ViewFrustum
{

private:

	static Plane SIDES_NDC[6];

	Plane sides[6];

	Point4 points[8];

public:

	ViewFrustum();
	ViewFrustum(const ViewFrustum& other);
	virtual ~ViewFrustum();

	void transformToWorldSpace(const Camera& camera);

	bool isVisible(const BoundingSphere& boundingSphere) const;

};

typedef boost::shared_ptr<ViewFrustum> ViewFrustumSP;

#endif /* VIEWFRUSTUM_H_ */
