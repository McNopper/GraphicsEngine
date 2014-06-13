/*
 * OrhtographicCameraShadowMap2D.h
 *
 *  Created on: 08.06.2013
 *      Author: nopper
 */

#ifndef ORTHOGRAPHICCAMERASHADOWMAP2D_H_
#define ORTHOGRAPHICCAMERASHADOWMAP2D_H_

#include "../../UsedLibs.h"

#include "../../layer0/math/Matrix4x4.h"
#include "../../layer3/camera/OrthographicCamera.h"
#include "../../layer3/shadow/ShadowMap2D.h"

class OrthographicCameraShadowMap2D
{

private:

	std::int32_t size;

	float orthographicScale;

	OrthographicCameraSP orthographicCamera;

	ShadowMap2DSP shadowMap;

	Matrix4x4 shadowMatrix;

	Matrix4x4 biasMatrix;

public:

	OrthographicCameraShadowMap2D(std::int32_t size, float orthographicScale);
	virtual ~OrthographicCameraShadowMap2D();

	void use(bool enable) const;

	void updateShadowMatrix();

	const OrthographicCameraSP& getOrthographicCamera() const;

	const Matrix4x4& getShadowMatrix() const;

	const ShadowMap2DSP& getShadowMap2D() const;

	std::int32_t getSize() const;

};

typedef std::shared_ptr<OrthographicCameraShadowMap2D> OrthographicCameraShadowMap2DSP;

#endif /* ORTHOGRAPHICCAMERASHADOWMAP2D_H_ */
