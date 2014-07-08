/*
 * GlTfInstanceSkin.h
 *
 *  Created on: 08.07.2014
 *      Author: nopper
 */

#ifndef GLTFINSTANCESKIN_H_
#define GLTFINSTANCESKIN_H_

#include "../../UsedLibs.h"

#include "GlTfMesh.h"
#include "GlTfSkin.h"

class GlTfInstanceSkin
{

private:

	std::vector<std::string> allSkeletonNames;

	GlTfSkinSP skin;

	std::vector<GlTfMeshSP> allSources;

public:

	GlTfInstanceSkin();
	virtual ~GlTfInstanceSkin();

	void addSkeletonName(const std::string& skeletonName);

	const std::vector<std::string>& getAllSkeletonNames() const;

	const GlTfSkinSP& getSkin() const;
	void setSkin(const GlTfSkinSP& skin);

	void addSource(const GlTfMeshSP& source);

	const std::vector<GlTfMeshSP>& getAllSources() const;

};

typedef std::shared_ptr<GlTfInstanceSkin> GlTfInstanceSkinSP;

#endif /* GLTFINSTANCESKIN_H_ */
