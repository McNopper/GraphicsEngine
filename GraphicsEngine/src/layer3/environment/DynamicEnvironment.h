/*
 * DynamicEnvironment.h
 *
 *  Created on: 27.04.2013
 *      Author: nopper
 */

#ifndef DYNAMICENVIRONMENT_H_
#define DYNAMICENVIRONMENT_H_

#include "../../UsedLibs.h"

#include "../../layer1/camera/PerspectiveCamera.h"
#include "../../layer1/camera/Viewport.h"
#include "../../layer2/framebuffer/FrameBufferCubeMap.h"

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

	const PerspectiveCameraSP& getCamera(boost::int32_t index) const;

	bool use(const Point4& position);

	bool unuse();

};

typedef boost::shared_ptr<DynamicEnvironment> DynamicEnvironmentSP;

#endif /* DYNAMICENVIRONMENT_H_ */
