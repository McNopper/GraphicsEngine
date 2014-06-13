/*
 * OrthographicCameraShadowMap2D.cpp
 *
 *  Created on: 08.06.2013
 *      Author: nopper
 */

#include "../../layer3/camera/CameraManager.h"

#include "OrthographicCameraShadowMap2D.h"

using namespace std;

OrthographicCameraShadowMap2D::OrthographicCameraShadowMap2D(int32_t size, float orthographicScale) :
		size(size), orthographicScale(orthographicScale), shadowMatrix()
{
	char buffer[256];
	sprintf(buffer, "%p", this);
	string uniqueID(buffer);

	orthographicCamera = OrthographicCameraSP(new OrthographicCamera("OthrographicCameraShadowMap2D" + uniqueID));
	orthographicCamera->orthographic(orthographicScale, orthographicScale, 0.1f, 1000.0f);

	CameraManager::getInstance()->setCamera(orthographicCamera->getName(), orthographicCamera, false);

	shadowMap = ShadowMap2DSP(new ShadowMap2D(size, 1));

	const float bias[] = { 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f };

	biasMatrix = Matrix4x4(bias);
}

OrthographicCameraShadowMap2D::~OrthographicCameraShadowMap2D()
{
	orthographicCamera.reset();

	shadowMap.reset();
}

void OrthographicCameraShadowMap2D::use(bool enable) const
{
	shadowMap->use(enable, 0);

	if (enable)
	{
		glViewport(0, 0, size, size);
	}
}

void OrthographicCameraShadowMap2D::updateShadowMatrix()
{
	shadowMatrix = biasMatrix * orthographicCamera->getProjectionMatrix() * orthographicCamera->getViewMatrix();
}

const OrthographicCameraSP& OrthographicCameraShadowMap2D::getOrthographicCamera() const
{
	return orthographicCamera;
}

const Matrix4x4& OrthographicCameraShadowMap2D::getShadowMatrix() const
{
	return shadowMatrix;
}

const ShadowMap2DSP& OrthographicCameraShadowMap2D::getShadowMap2D() const
{
	return shadowMap;
}

int32_t OrthographicCameraShadowMap2D::getSize() const
{
	return size;
}
