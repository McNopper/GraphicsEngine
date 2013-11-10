/*
 * OrthographicCameraCascadedShadowMap2D.h
 *
 *  Created on: 07.11.2013
 *      Author: nopper
 */

#ifndef ORTHOGRAPHICCAMERACASCADEDSHADOWMAP2D_H_
#define ORTHOGRAPHICCAMERACASCADEDSHADOWMAP2D_H_

#include "../../UsedLibs.h"

#include "../../layer0/math/Matrix4x4.h"
#include "../../layer3/camera/OrthographicCamera.h"
#include "../../layer3/shadow/ShadowMap2D.h"

class OrthographicCameraCascadedShadowMap2D
{

private:

	boost::int32_t size;

	boost::int32_t sections;

	ShadowMap2DSP shadowMap;

	Matrix4x4 biasMatrix;

	std::vector<OrthographicCameraSP> allOrthographicCameras;
	std::vector<Matrix4x4> allShadowMatrices;

public:

	OrthographicCameraCascadedShadowMap2D(boost::int32_t size, boost::int32_t sections);
	virtual ~OrthographicCameraCascadedShadowMap2D();

	void use(bool enable, boost::int32_t section) const;

	void updateShadowMatrices();

	const OrthographicCameraSP& getOrthographicCamera(boost::int32_t section) const;

	const Matrix4x4& getShadowMatrix(boost::int32_t section) const;

	const std::vector<Matrix4x4>& getShadowMatrices() const;

	const ShadowMap2DSP& getShadowMap2D() const;

	boost::int32_t getSize() const;

	boost::int32_t getSections() const;

};

typedef boost::shared_ptr<OrthographicCameraCascadedShadowMap2D> OrthographicCameraCascadedShadowMap2DSP;

#endif /* ORTHOGRAPHICCAMERACASCADEDSHADOWMAP2D_H_ */
