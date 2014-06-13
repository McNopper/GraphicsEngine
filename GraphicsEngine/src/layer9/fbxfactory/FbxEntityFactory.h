/*
 * FbxEntityFactory.h
 *
 *  Created on: 17.05.2011
 *      Author: Norbert Nopper
 */

#ifndef FBXENTITYFACTORY_H_
#define FBXENTITYFACTORY_H_

#include <fbxsdk.h>

#include "../../UsedLibs.h"

#include "../../layer1/texture/Texture2D.h"
#include "../../layer2/material/SurfaceMaterial.h"
#include "../../layer3/animation/AnimationStack.h"
#include "../../layer3/camera/Camera.h"
#include "../../layer3/light/Light.h"
#include "../../layer3/mesh/Mesh.h"
#include "../../layer5/node/Node.h"
#include "../../layer5/node/NodeTreeFactory.h"
#include "../../layer8/modelentity/ModelEntity.h"

class FbxEntityFactory
{

private:

	static const char* CHANNELS[];

	FbxManager* manager;
	FbxIOSettings* ioSettings;
	FbxGeometryConverter* geometryConverter;
	FbxArray<FbxString*> animStackNameArray;

	NodeTreeFactory nodeTreeFactory;

	std::map<std::int32_t, SurfaceMaterialSP> currentSurfaceMaterials;
	std::vector<SurfaceMaterialSP> allSurfaceMaterials;
	std::vector<AnimationStackSP> allAnimationStacks;
	std::vector<MeshSP> allMeshes;
	std::vector<CameraSP> allCameras;
	std::vector<LightSP> allLights;
	std::int32_t currentNumberJoints;
	std::int32_t currentNumberAnimationStacks;
	bool currentEntityAnimated;
	bool currentEntitySkinned;

	bool anisotropic;

	bool doReset;

	float minX, maxX, minY, maxY, minZ, maxZ;

	SurfaceMaterialSP currentSurfaceMaterial;

	bool loadCamera;

	bool loadLight;

	bool loadMesh;

private:

	bool traverseScene(FbxScene* scene);

	void processTexture(FbxTexture* texture);

	void processSurfaceMaterial(std::int32_t materialIndex, FbxSurfaceMaterial* surfaceMaterial);

	FbxDouble3 processMaterialProperty(const FbxSurfaceMaterial* Material, const char* propertyName, const char* factorPropertyName, const FbxDouble3& defaultColor, Texture2DSP& texture) const;

	void traverseNode(FbxNode* node, const NodeSP& parentNode);

	AnimationStackSP processAnimation(FbxNode* node, std::int32_t animStackIndex);

	MeshSP processMesh(FbxMesh* mesh);

	LightSP processLight(FbxLight* light);

	CameraSP processCamera(FbxCamera* camera);

	void preTraverseIndexCreation(FbxNode* node, const NodeSP& nodeGE);

	void postTraverseNode(FbxNode* node, const NodeSP& nodeGE, const Matrix4x4& parentMatrix);

	void processMinMax(const float* vertices, std::int32_t numberVertices, const Matrix4x4& matrix);

	void postProcessMesh(FbxMesh* mesh, const MeshSP& currentMesh);

	void traverseDeleteUserPointer(FbxNode* node);

	ModelEntitySP loadFbxFile(const std::string& name, const std::string& filename, float scale, bool globalAnisotropic, const SurfaceMaterialSP& overwriteSurfaceMaterial);

public:

	FbxEntityFactory();
	virtual ~FbxEntityFactory();

	ModelEntitySP loadFbxModelFile(const std::string& name, const std::string& filename, float scale, bool globalAnisotropic = false, const SurfaceMaterialSP& overwriteSurfaceMaterial = SurfaceMaterialSP());

	ModelEntitySP loadFbxSceneFile(const std::string& name, const std::string& filename, float scale, bool globalAnisotropic = false);

};

#endif /* FBXENTITYFACTORY_H_ */
