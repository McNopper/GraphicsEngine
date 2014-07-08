/*
 * GlTfSkin.h
 *
 *  Created on: 08.07.2014
 *      Author: nopper
 */

#ifndef GLTFSKIN_H_
#define GLTFSKIN_H_

#include "../../UsedLibs.h"

#include "GlTfAccessor.h"

class GlTfSkin
{

private:

	GlTfAccessorSP inverseBindMatrices;

	std::vector<std::string> allJointNames;

public:

	GlTfSkin();
	virtual ~GlTfSkin();

	const GlTfAccessorSP& getInverseBindMatrices() const;
	void setInverseBindMatrices(const GlTfAccessorSP& inverseBindMatrices);


	void addJointName(const std::string& jointName);

	const std::vector<std::string>& getAllJointNames() const;

};

typedef std::shared_ptr<GlTfSkin> GlTfSkinSP;

#endif /* GLTFSKIN_H_ */
