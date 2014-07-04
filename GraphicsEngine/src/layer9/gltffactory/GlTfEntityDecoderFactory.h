/*
 * GlTfEntityDecoderFactory.h
 *
 *  Created on: 02.07.2014
 *      Author: nopper
 */

#ifndef GLTFENTITYDECODERFACTORY_H_
#define GLTFENTITYDECODERFACTORY_H_

#include "../../UsedLibs.h"

#include "../../layer0/color/Color.h"
#include "../../layer0/json/JSONarray.h"
#include "../../layer0/json/JSONobject.h"
#include "../../layer0/json/JSONnumber.h"
#include "../../layer0/json/JSONstring.h"
#include "../../layer0/json/JSONvalue.h"
#include "../../layer0/math/Matrix3x3.h"
#include "../../layer0/math/Matrix4x4.h"
#include "../../layer8/modelentity/ModelEntity.h"

#include "GlTfAccessor.h"
#include "GlTfBufferView.h"
#include "GlTfSampler.h"

class GlTfEntityDecoderFactory
{

private:

	std::map<std::string, GLUSbinaryfile> allBuffers;
	std::map<std::string, GlTfBufferViewSP> allBufferViews;
	std::map<std::string, GlTfAccessorSP> allAccessors;

	std::map<std::string, GLUStgaimage> allTgaImages;
	std::map<std::string, GLUShdrimage> allHdrImages;
	std::map<std::string, GlTfSamplerSP> allSamplers;

	bool decodeBuffers(const JSONobjectSP& jsonGlTf, const std::string& folderName);
	bool decodeBufferViews(const JSONobjectSP& jsonGlTf);
	bool decodeAccessors(const JSONobjectSP& jsonGlTf);

	bool decodeImages(const JSONobjectSP& jsonGlTf, const std::string& folderName);
	bool decodeSamplers(const JSONobjectSP& jsonGlTf);

	//

	bool decodeFloat(float& number, const JSONvalueSP& jsonValue) const;

	bool decodeInteger(int32_t& number, const JSONvalueSP& jsonValue) const;

	bool decodeString(std::string& value, const JSONvalueSP& jsonValue) const;

	bool decodeMatrix4x4(Matrix4x4& matrix, const JSONvalueSP& jsonValue) const;

	bool decodeMatrix3x3(Matrix3x3& matrix, const JSONvalueSP& jsonValue) const;

	bool decodeColor(Color& color, const JSONvalueSP& jsonValue) const;

	//

	void cleanUp();

public:

	GlTfEntityDecoderFactory();

	virtual ~GlTfEntityDecoderFactory();

	ModelEntitySP loadGlTfModelFile(const std::string& identifier, const std::string& fileName, const std::string& folderName, float scale);

};

#endif /* GLTFENTITYDECODERFACTORY_H_ */
