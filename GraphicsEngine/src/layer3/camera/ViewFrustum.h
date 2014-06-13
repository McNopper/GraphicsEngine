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
#include "../../layer1/collision/BoundingSphere.h"

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

class ViewFrustum
{

private:

	static Plane SIDES_NDC[6];

	Plane sides[6];

	std::vector<Point4> frustumPoints;

	std::int32_t sections;

public:

	ViewFrustum();
	ViewFrustum(const ViewFrustum& other);
	virtual ~ViewFrustum();

	void transformToWorldSpace(const Camera& camera);

	bool isVisible(const BoundingSphere& boundingSphere) const;

	void setNumberSections(std::int32_t sections);

	std::int32_t getNumberSections() const;

	const std::vector<Point4>& getFrustumPoints() const;

};

typedef std::shared_ptr<ViewFrustum> ViewFrustumSP;

#endif /* VIEWFRUSTUM_H_ */
