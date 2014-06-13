/*
 * DynamicEnvironment.h
 *
 *  Created on: 27.04.2013
 *      Author: nopper
 */

#ifndef DYNAMICENVIRONMENT_H_
#define DYNAMICENVIRONMENT_H_

#include "../../UsedLibs.h"

#include "../../layer2/framebuffer/FrameBufferCubeMap.h"
#include "../../layer3/camera/PerspectiveCamera.h"
#include "../../layer3/camera/Viewport.h"

class DynamicEnvironment
{

private:

	FrameBufferCubeMapSP frameBufferCubeMap;

	PerspectiveCameraSP camera[6];
	ViewportSP viewport;

	Point4 lastPosition;

	void init(const Point4& position);

public:
	DynamicEnvironment(const Point4& position, const FrameBufferCubeMapSP& frameBufferCubeMap);
	virtual ~DynamicEnvironment();

	const FrameBufferCubeMapSP& getFrameBufferCubeMap() const;

	const PerspectiveCameraSP& getCamera(std::int32_t index) const;

	bool use(const Point4& position);

	bool unuse();

};

typedef std::shared_ptr<DynamicEnvironment> DynamicEnvironmentSP;

#endif /* DYNAMICENVIRONMENT_H_ */
