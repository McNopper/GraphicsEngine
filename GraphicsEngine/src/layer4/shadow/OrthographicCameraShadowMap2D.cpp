/*
 * OrthographicCameraShadowMap2D.cpp
 *
 *  Created on: 08.06.2013
 *      Author: nopper
 */

#include "OrthographicCameraShadowMap2D.h"

using namespace boost;

using namespace std;

OrthographicCameraShadowMap2D::OrthographicCameraShadowMap2D(int32_t size) :
		size(size), shadowMatrix()
{
	char buffer[256];
	sprintf(buffer, "%p", this);
	string uniqueID(buffer);

	orthographicCamera = OrthographicCameraSP(new OrthographicCamera("OthrographicCameraShadowMap2D" + uniqueID));
	orthographicCamera->setViewport(Viewport(0, 0, size, size));

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
}

void OrthographicCameraShadowMap2D::setCameraProperties(const ProgramSP& program, const Point4& position, const Quaternion& rotation)
{
	orthographicCamera->setCameraProperties(program, position, rotation, true);

	shadowMatrix = biasMatrix * orthographicCamera->getProjectionMatrix() * orthographicCamera->getViewMatrix();
}

const Matrix4x4& OrthographicCameraShadowMap2D::getShadowMatrix() const
{
	return shadowMatrix;
}

GLuint OrthographicCameraShadowMap2D::getDepthTextureName() const
{
	return shadowMap->getDepthTextureName(0);
}

int32_t OrthographicCameraShadowMap2D::getSize() const
{
	return size;
}
