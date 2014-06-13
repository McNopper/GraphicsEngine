/*
 * Entity.h
 *
 *  Created on: 12.09.2012
 *      Author: nopper
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include "../../layer1/collision/BoundingSphere.h"
#include "../../layer3/camera/Camera.h"

enum RenderFilter {RENDER_TRANSPARENT, RENDER_OPAQUE, RENDER_ALL};

class Entity {

private:

	float distanceToCamera;

protected:

	static CameraSP currentCamera;
	static bool ascendingSortOrder;
	static enum RenderFilter renderFilter;
	static bool dynamicCubeMaps;

	/**
	 * For dynamic cube map rendering.
	 */
	static Matrix4x4 viewMatrix[6];
	static Matrix4x4 projectionMatrix;

	Entity();
	virtual ~Entity();

	float getDistanceToCamera() const;
	void setDistanceToCamera(float distanceToCamera);

public:

    bool operator <=(const Entity& other) const;
	bool operator >=(const Entity& other) const;

    static void setCurrentValues(const CameraSP& currentCamera, bool ascendingSortOrder = false, enum RenderFilter renderFilter = RENDER_ALL, bool dynamicCubeMaps = false);

    static const CameraSP& getCurrentCamera();
    static bool isAscendingSortOrder();
    static enum RenderFilter getRenderFilter();
    static bool getDynamicCubeMaps();

    static void setCubeMapViewMatrix(std::int32_t face, const Matrix4x4& matrix);
    static void setCubeMapProjectionMatrix(const Matrix4x4& matrix);

    static const Matrix4x4* getCubeMapViewMatrices();
    static const Matrix4x4& getCubeMapProjectionMatrix();

	virtual const BoundingSphere& getBoundingSphere() const = 0;

	virtual void updateBoundingSphereCenter(bool initial = false) = 0;
	virtual void updateDistanceToCamera() = 0;

	virtual void update() = 0;
	virtual void render() const = 0;

};

typedef std::shared_ptr<Entity> EntitySP;

#endif /* ENTITY_H_ */
