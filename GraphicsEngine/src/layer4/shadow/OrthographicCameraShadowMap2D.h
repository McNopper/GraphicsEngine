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

	boost::int32_t size;

	OrthographicCameraSP orthographicCamera;

	ShadowMap2DSP shadowMap;

	Matrix4x4 shadowMatrix;

	Matrix4x4 biasMatrix;

public:

	OrthographicCameraShadowMap2D(boost::int32_t size);
	virtual ~OrthographicCameraShadowMap2D();

	void use(bool enable) const;

	void setCameraProperties(const ProgramSP& program, const Point4& position, const Quaternion& rotation);

	const Matrix4x4& getShadowMatrix() const;

	GLuint getDepthTextureName() const;

	boost::int32_t getSize() const;

};

#endif /* ORTHOGRAPHICCAMERASHADOWMAP2D_H_ */
