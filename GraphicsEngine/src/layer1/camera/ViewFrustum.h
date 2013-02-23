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
#include "../../layer0/math/Matrix4x4.h"
#include "../collision/BoundingSphere.h"

typedef enum _frustum_sides
{
	NEAR_PLANE,
	FAR_PLANE,
	LEFT_PLANE,
	RIGHT_PLANE,
	BOTTOM_PLANE,
	TOP_PLANE
} frustum_sides;

class ViewFrustum
{

private:

	static Plane SIDES_NDC[6];

	Plane sides[6];

public:

	ViewFrustum();
	ViewFrustum(const ViewFrustum& other);
	virtual ~ViewFrustum();

	void transformToWorldSpace(const Matrix4x4& transposedViewProjectionMatrix);

	bool isVisible(const BoundingSphere& boundingSphere) const;

};

typedef boost::shared_ptr<ViewFrustum> ViewFrustumSP;

#endif /* VIEWFRUSTUM_H_ */
