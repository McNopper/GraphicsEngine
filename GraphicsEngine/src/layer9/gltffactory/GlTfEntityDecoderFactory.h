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

class GlTfEntityDecoderFactory
{

private:

	bool decodeFloat(float& number, const JSONvalueSP& jsonValue) const;

	bool decodeInteger(int32_t& number, const JSONvalueSP& jsonValue) const;

	bool decodeString(std::string& value, const JSONvalueSP& jsonValue) const;

	bool decodeMatrix4x4(Matrix4x4& matrix, const JSONvalueSP& jsonValue) const;

	bool decodeMatrix3x3(Matrix3x3& matrix, const JSONvalueSP& jsonValue) const;

	bool decodeColor(Color& color, const JSONvalueSP& jsonValue) const;


	NodeSP createNode(const JSONstringSP& nodeName, const JSONobjectSP& jsonGlTf) const;

public:

	GlTfEntityDecoderFactory();

	virtual ~GlTfEntityDecoderFactory();

	ModelEntitySP loadGlTfModelFile(const std::string& identifier, const std::string& fileName, const std::string& folderName, float scale) const;

};

#endif /* GLTFENTITYDECODERFACTORY_H_ */
