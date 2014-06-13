/*
 * DynamicEnvironment.cpp
 *
 *  Created on: 27.04.2013
 *      Author: nopper
 */

#include "../../layer3/camera/ViewportManager.h"
#include "../../layer4/entity/Entity.h"

#include "DynamicEnvironment.h"

using namespace std;

DynamicEnvironment::DynamicEnvironment(const Point4& position, const FrameBufferCubeMapSP& frameBufferCubeMap) :
		frameBufferCubeMap(frameBufferCubeMap), lastPosition(position)
{
	char buffer[256];
	sprintf(buffer, "%p", this);
	string uniqueID(buffer);

	viewport = ViewportSP(new Viewport(0, 0, frameBufferCubeMap->getWidth(), frameBufferCubeMap->getHeight()));
	ViewportManager::getInstance()->setViewport("DynamicEnvironment" + uniqueID, viewport);

	for (int32_t face = 0; face < 6; face++)
	{
		camera[face] = PerspectiveCameraSP(new PerspectiveCamera("DynamicEnvironment" + to_string(face)));
	}

	init(position);
}

DynamicEnvironment::~DynamicEnvironment()
{
	for (int32_t face = 0; face < 6; face++)
	{
		camera[face].reset();
	}
}

const FrameBufferCubeMapSP& DynamicEnvironment::getFrameBufferCubeMap() const
{
	return frameBufferCubeMap;
}

const PerspectiveCameraSP& DynamicEnvironment::getCamera(int32_t index) const
{
	return camera[index];
}

void DynamicEnvironment::init(const Point4& position)
{
	for (int32_t face = 0; face < 6; face++)
	{
		Vector3 direction;
		Vector3 up;
		Point4 center;

		switch (face)
		{
			case 0:
				direction = Vector3(1.0f, 0.0f, 0.0f);
				up = Vector3(0.0f, 1.0f, 0.0f);
			break;
			case 1:
				direction = Vector3(-1.0f, 0.0f, 0.0f);
				up = Vector3(0.0f, 1.0f, 0.0f);
			break;
			case 2:
				direction = Vector3(0.0f, 1.0f, 0.0f);
				up = Vector3(0.0f, 0.0f, -1.0f);
			break;
			case 3:
				direction = Vector3(0.0f, -1.0f, 0.0f);
				up = Vector3(0.0f, 0.0f, 1.0f);
			break;
			case 4:
				direction = Vector3(0.0f, 0.0f, 1.0f);
				up = Vector3(0.0f, 1.0f, 0.0f);
			break;
			case 5:
				direction = Vector3(0.0f, 0.0f, -1.0f);
				up = Vector3(0.0f, 1.0f, 0.0f);
			break;
		}

		camera[face]->lookAt(position, position + direction, up);
		camera[face]->perspective(90.0f, *(viewport.get()), 0.001f, 1000.0f);
	}
}

bool DynamicEnvironment::use(const Point4& position)
{
	if (!frameBufferCubeMap.get())
	{
		return false;
	}

	frameBufferCubeMap->use(true);

	if (lastPosition != position)
	{
		lastPosition = position;

		init(position);
	}

	Matrix4x4 mirrorMatrix;
	mirrorMatrix.scale(-1.0f, -1.0f, 1.0f);

	for (int32_t face = 0; face < 6; face++)
	{
		Entity::setCubeMapViewMatrix(face, mirrorMatrix * camera[face]->getViewMatrix());
	}
	Entity::setCubeMapProjectionMatrix(camera[0]->getProjectionMatrix());

	return true;
}

bool DynamicEnvironment::unuse()
{
	if (!frameBufferCubeMap.get())
	{
		return false;
	}

	frameBufferCubeMap->use(false);

	return true;
}
