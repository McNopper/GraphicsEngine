/*
 * Entity.h
 *
 *  Created on: 12.09.2012
 *      Author: nopper
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include "../../layer1/camera/Camera.h"
#include "../../layer1/collision/BoundingSphere.h"

enum RenderFilter {RENDER_TRANSPARENT, RENDER_OPAQUE, RENDER_ALL};

class Entity {

	friend void boost::checked_delete<Entity>(Entity* x);

protected:

	static CameraSP currentCamera;
	static bool ascendingSortOrder;
	static enum RenderFilter renderFilter;
	static bool dynamicCubeMaps;

	float distanceToCamera;

	Entity();
	virtual ~Entity();

	float getDistanceToCamera() const;
	void setDistanceToCamera(float distanceToCamera);

public:

    static void setCurrentValues(const CameraSP& currentCamera, bool ascendingSortOrder = false, enum RenderFilter renderFilter = RENDER_ALL, bool dynamicCubeMaps = false);

    static const CameraSP& getCurrentCamera();
    static bool isAscendingSortOrder();
    static enum RenderFilter getRenderFilter();
    static bool getDynamicCubeMaps();

	virtual const BoundingSphere& getBoundingSphere() const = 0;

	virtual void updateBoundingSphereCenter(bool initial = false) = 0;
	virtual void updateDistanceToCamera() = 0;

	virtual void update() = 0;
	virtual void render() const = 0;

};

typedef boost::shared_ptr<Entity> EntitySP;

#endif /* ENTITY_H_ */
