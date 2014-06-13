/*
 * OrthographicCameraCascadedShadowMap2D.cpp
 *
 *  Created on: 07.11.2013
 *      Author: nopper
 */

#include "../../layer3/camera/CameraManager.h"

#include "OrthographicCameraCascadedShadowMap2D.h"

using namespace std;

OrthographicCameraCascadedShadowMap2D::OrthographicCameraCascadedShadowMap2D(int32_t size, int32_t sections) :
		size(size), sections(sections)
{
	char buffer[256];
	sprintf(buffer, "%p", this);
	string uniqueID(buffer);

	OrthographicCameraSP orthographicCamera;

	for (int32_t i = 0; i < sections; i++)
	{
		orthographicCamera = OrthographicCameraSP(new OrthographicCamera("OthrographicCameraCascadedShadowMap2D" + uniqueID + "-" + to_string(i)));

		allOrthographicCameras.push_back(orthographicCamera);
		allShadowMatrices.push_back(Matrix4x4());

		CameraManager::getInstance()->setCamera(orthographicCamera->getName(), orthographicCamera, false);
	}

	shadowMap = ShadowMap2DSP(new ShadowMap2D(size, sections));

	const float bias[] = { 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f };

	biasMatrix = Matrix4x4(bias);
}

OrthographicCameraCascadedShadowMap2D::~OrthographicCameraCascadedShadowMap2D()
{
	allOrthographicCameras.clear();
	allShadowMatrices.clear();
}

void OrthographicCameraCascadedShadowMap2D::use(bool enable, int32_t section) const
{
	shadowMap->use(enable, section);

	if (enable)
	{
		glViewport(0, 0, size, size);
	}
}

void OrthographicCameraCascadedShadowMap2D::updateShadowMatrices()
{
	OrthographicCameraSP orthographicCamera;

	for (int32_t i = 0; i < sections; i++)
	{
		orthographicCamera = allOrthographicCameras[i];

		allShadowMatrices[i] = biasMatrix * orthographicCamera->getProjectionMatrix() * orthographicCamera->getViewMatrix();
	}
}

const OrthographicCameraSP& OrthographicCameraCascadedShadowMap2D::getOrthographicCamera(int32_t section) const
{
	return allOrthographicCameras[section];
}

const Matrix4x4& OrthographicCameraCascadedShadowMap2D::getShadowMatrix(int32_t section) const
{
	return allShadowMatrices[section];
}

const vector<Matrix4x4>& OrthographicCameraCascadedShadowMap2D::getShadowMatrices() const
{
	return allShadowMatrices;
}

const ShadowMap2DSP& OrthographicCameraCascadedShadowMap2D::getShadowMap2D() const
{
	return shadowMap;
}

int32_t OrthographicCameraCascadedShadowMap2D::getSize() const
{
	return size;
}

int32_t OrthographicCameraCascadedShadowMap2D::getSections() const
{
	return sections;
}
