/*
 * FbxEntityFactory.cpp
 *
 *  Created on: 17.05.2011
 *      Author: Norbert Nopper
 */

#include "../../layer1/texture/Texture2DManager.h"
#include "../../layer1/texture/TextureFactory.h"
#include "../../layer2/interpolation/ConstantInterpolator.h"
#include "../../layer2/interpolation/CubicInterpolator.h"
#include "../../layer2/interpolation/LinearInterpolator.h"
#include "../../layer3/animation/AnimationLayer.h"
#include "../../layer3/camera/OrthographicCamera.h"
#include "../../layer3/camera/PerspectiveCamera.h"
#include "../../layer3/light/DirectionalLight.h"
#include "../../layer3/light/PointLight.h"
#include "../../layer3/light/SpotLight.h"
#include "../../layer6/model/ModelManager.h"
#include "FbxSubMesh.h"

#include "FbxEntityFactory.h"

using namespace std;

const char* FbxEntityFactory::CHANNELS[] = { "X", "Y", "Z" };

FbxEntityFactory::FbxEntityFactory() :
		manager(0), ioSettings(0), geometryConverter(0), currentSurfaceMaterials(), allSurfaceMaterials(), allAnimationStacks(), allMeshes(), allCameras(), allLights(), currentNumberJoints(0), currentNumberAnimationStacks(0), currentEntityAnimated(false), currentEntitySkinned(false), anisotropic(false), doReset(true), minX(0.0f), maxX(0.0f), minY(0.0f), maxY(0.0f), minZ(0.0f), maxZ(0.0f), currentSurfaceMaterial(), loadCamera(false), loadLight(false), loadMesh(true)
{
	// Create the FBX SDK manager
	manager = FbxManager::Create();

	// Create an IOSettings object.
	ioSettings = FbxIOSettings::Create(manager, IOSROOT);
	manager->SetIOSettings(ioSettings);

	// Create a Geometry converter for triangulation
	geometryConverter = new FbxGeometryConverter(manager);
}

FbxEntityFactory::~FbxEntityFactory()
{
	currentSurfaceMaterials.clear();
	allSurfaceMaterials.clear();
	allAnimationStacks.clear();
	allMeshes.clear();
	allCameras.clear();
	allLights.clear();

	delete geometryConverter;
	ioSettings->Destroy();
	manager->Destroy();
}

ModelEntitySP FbxEntityFactory::loadFbxFile(const string& name, const string& filename, float scale, bool globalAnisotropic, const SurfaceMaterialSP& overwriteSurfaceMaterial)
{
	glusLogPrint(GLUS_LOG_INFO, "Loading FBX %s", filename.c_str());

	ModelSP model;

	// Check, if we have filename in cache
	if (ModelManager::getInstance()->containsModelByKey(filename))
	{
		model = ModelManager::getInstance()->getModelByKey(filename);

		return ModelEntitySP(new ModelEntity(name, model, scale, scale, scale));
	}

	// Create an importer.
	FbxImporter* importer = FbxImporter::Create(manager, "");

	// Initialize the importer.
	bool importStatus = importer->Initialize(filename.c_str(), -1, manager->GetIOSettings());

	if (!importStatus)
	{
		glusLogPrint(GLUS_LOG_ERROR, "Call to FbxImporter::Initialize() failed");

		return ModelEntitySP();
	}

	// Create a new scene so it can be populated by the imported file.
	FbxScene* scene = FbxScene::Create(manager, "myScene");

	// Import the contents of the file into the scene.
	importer->Import(scene);

	currentSurfaceMaterial = overwriteSurfaceMaterial;
	anisotropic = globalAnisotropic;
	currentNumberAnimationStacks = importer->GetAnimStackCount();
	currentSurfaceMaterials.clear();
	allSurfaceMaterials.clear();
	allAnimationStacks.clear();
	allMeshes.clear();
	allCameras.clear();
	allLights.clear();
	nodeTreeFactory.reset();
	currentNumberJoints = 0;
	currentEntityAnimated = false;
	currentEntitySkinned = false;
	doReset = true;

	// The file has been imported; we can get rid of the importer.
	importer->Destroy();

	// Convert to OpenGL
	FbxAxisSystem::OpenGL.ConvertScene(scene);

	//

	if (!traverseScene(scene))
	{
		glusLogPrint(GLUS_LOG_ERROR, "Traversing scene failed");

		return ModelEntitySP();
	}

	float absMaxX = glusMathMaxf(fabs(maxX), fabs(minX));
	float absMaxY = glusMathMaxf(fabs(maxY), fabs(minY));
	float absMaxZ = glusMathMaxf(fabs(maxZ), fabs(minZ));

	float newRadius = glusMathLengthf(absMaxX, absMaxY, absMaxZ);

	BoundingSphere boundingSphere;
	boundingSphere.setRadius(newRadius);

	model = ModelSP(new Model(boundingSphere, nodeTreeFactory.getRootNode(), currentNumberJoints, currentEntityAnimated, currentEntitySkinned));
	ModelManager::getInstance()->setModel(filename, model);

	//

	Color ambientLightColor;

	FbxColor globalAmbientColor = scene->GetGlobalSettings().GetAmbientColor();

	if (loadLight && globalAmbientColor.IsValid())
	{
		ambientLightColor.setR(static_cast<float>(globalAmbientColor.mRed));
		ambientLightColor.setG(static_cast<float>(globalAmbientColor.mGreen));
		ambientLightColor.setB(static_cast<float>(globalAmbientColor.mBlue));
		ambientLightColor.setA(static_cast<float>(globalAmbientColor.mAlpha));
	}

	//

	scene->Destroy(true);

	ModelEntitySP result = ModelEntitySP(new ModelEntity(name, model, scale, scale, scale));

	if (loadLight)
	{
		result->setAmbientLightColor(ambientLightColor);
	}

	glusLogPrint(GLUS_LOG_INFO, "Entity created: %s", filename.c_str());

	return result;
}

ModelEntitySP FbxEntityFactory::loadFbxModelFile(const string& name, const string& filename, float scale, bool globalAnisotropic, const SurfaceMaterialSP& overwriteSurfaceMaterial)
{
	loadCamera = false;
	loadLight = false;
	loadMesh = true;

	glusLogPrint(GLUS_LOG_INFO, "Loading mesh only");

	return loadFbxFile(name, filename, scale, globalAnisotropic, overwriteSurfaceMaterial);
}

ModelEntitySP FbxEntityFactory::loadFbxSceneFile(const string& name, const string& filename, float scale, bool globalAnisotropic)
{
	loadCamera = true;
	loadLight = true;
	loadMesh = true;

	glusLogPrint(GLUS_LOG_INFO, "Loading camera, light and mesh");

	ModelEntitySP result = loadFbxFile(name, filename, scale, globalAnisotropic, SurfaceMaterialSP());

	if (result.get())
	{
		result->setUsePositionAsBoundingSphereCenter(true);
	}

	return result;
}

bool FbxEntityFactory::traverseScene(FbxScene* scene)
{
	geometryConverter->Triangulate(scene, true);

	//

	scene->FillAnimStackNameArray(animStackNameArray);

	//

	for (int32_t i = 0; i < scene->GetTextureCount(); i++)
	{
		processTexture(scene->GetTexture(i));
	}

	if (currentSurfaceMaterial.get())
	{
		allSurfaceMaterials.push_back(currentSurfaceMaterial);
	}

	for (int32_t i = 0; i < scene->GetMaterialCount(); i++)
	{
		if (!currentSurfaceMaterial.get())
		{
			processSurfaceMaterial(i, scene->GetMaterial(i));
		}
		else
		{
			currentSurfaceMaterials[i] = currentSurfaceMaterial;
		}
	}

	FbxNode* node = scene->GetRootNode();

	if (node)
	{
		traverseNode(node, nodeTreeFactory.getRootNode());

		if (nodeTreeFactory.getRootNode().get())
		{
			preTraverseIndexCreation(node, nodeTreeFactory.getRootNode());

			currentNumberJoints = nodeTreeFactory.createIndex();

			if (currentNumberJoints >= MAX_MATRICES)
			{
				glusLogPrint(GLUS_LOG_ERROR, "Too many joints: %d", currentNumberJoints);

				nodeTreeFactory.reset();
				currentNumberJoints = 0;

				FbxArrayDelete(animStackNameArray);

				auto walker = currentSurfaceMaterials.begin();
				while (walker != currentSurfaceMaterials.end())
				{
					walker->second.reset();

					walker++;
				}
				currentSurfaceMaterials.clear();

				auto walkerAll = allSurfaceMaterials.begin();
				while (walkerAll != allSurfaceMaterials.end())
				{
					walkerAll->reset();

					walkerAll++;
				}
				allSurfaceMaterials.clear();

				auto walkerAnimationStack = allAnimationStacks.begin();
				while (walkerAnimationStack != allAnimationStacks.end())
				{
					walkerAnimationStack->reset();

					walkerAnimationStack++;
				}
				allAnimationStacks.clear();

				auto walkerMesh = allMeshes.begin();
				while (walkerMesh != allMeshes.end())
				{
					walkerMesh->reset();

					walkerMesh++;
				}
				allMeshes.clear();

				auto walkerCamera = allCameras.begin();
				while (walkerCamera != allCameras.end())
				{
					walkerCamera->reset();

					walkerCamera++;
				}
				allCameras.clear();

				auto walkerLight = allLights.begin();
				while (walkerLight != allLights.end())
				{
					walkerLight->reset();

					walkerLight++;
				}
				allLights.clear();

				traverseDeleteUserPointer(node);

				return false;
			}
		}

		postTraverseNode(node, nodeTreeFactory.getRootNode(), Matrix4x4());

		traverseDeleteUserPointer(node);
	}

	FbxArrayDelete(animStackNameArray);

	return true;
}

void FbxEntityFactory::processTexture(FbxTexture* texture)
{
	FbxFileTexture* fileTexture = FbxCast<FbxFileTexture>(texture);
	if (fileTexture && !fileTexture->GetUserDataPtr())
	{
		TextureFactory textureFactory;

		GLint wrapModeS = GL_REPEAT;
		GLint wrapModeT = GL_REPEAT;

		if (texture->WrapModeU.Get() == FbxTexture::eClamp)
		{
			wrapModeS = GL_CLAMP;
		}
		if (texture->WrapModeV.Get() == FbxTexture::eClamp)
		{
			wrapModeT = GL_CLAMP;
		}

		Texture2DSP texture2D = Texture2DManager::getInstance()->createTexture(fileTexture->GetFileName(), true, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, wrapModeS, wrapModeT, 1.0f);

		if (!texture2D.get())
		{
			glusLogPrint(GLUS_LOG_WARNING, "Could not create file texture: %s", fileTexture->GetFileName());
		}
		else
		{
			texture2D->setAnisotropic(anisotropic);
		}
	}
	else
	{
		glusLogPrint(GLUS_LOG_WARNING, "Skipping texture");
	}
}

void FbxEntityFactory::processSurfaceMaterial(int32_t materialIndex, FbxSurfaceMaterial* surfaceMaterial)
{
	string materialName(surfaceMaterial->GetName());

	//

	auto walker = allSurfaceMaterials.begin();
	while (walker != allSurfaceMaterials.end())
	{
		if ((*walker)->getName().compare(materialName) == 0)
		{
			currentSurfaceMaterials[materialIndex] = (*walker);

			glusLogPrint(GLUS_LOG_INFO, "Reused material: %s", surfaceMaterial->GetName());

			return;
		}

		walker++;
	}

	//

	Color color;
	Texture2DSP texture2D;

	SurfaceMaterialSP currentSurfaceMaterial(new SurfaceMaterial(materialName));
	SurfaceMaterial defaultMaterial("default");
	FbxDouble3 defaultEmissive(defaultMaterial.getEmissive().getR(), defaultMaterial.getEmissive().getG(), defaultMaterial.getEmissive().getB());
	FbxDouble3 defaultAmbient(defaultMaterial.getAmbient().getR(), defaultMaterial.getAmbient().getG(), defaultMaterial.getAmbient().getB());
	FbxDouble3 defaultDiffuse(defaultMaterial.getAmbient().getR(), defaultMaterial.getAmbient().getG(), defaultMaterial.getAmbient().getB());
	FbxDouble3 defaultSpecular(defaultMaterial.getSpecular().getR(), defaultMaterial.getSpecular().getG(), defaultMaterial.getSpecular().getB());
	FbxDouble3 defaultReflection(defaultMaterial.getReflection().getR(), defaultMaterial.getReflection().getG(), defaultMaterial.getReflection().getB());

	texture2D.reset();
	const FbxDouble3 emissive = processMaterialProperty(surfaceMaterial, FbxSurfaceMaterial::sEmissive, FbxSurfaceMaterial::sEmissiveFactor, defaultEmissive, texture2D);
	color.setRGBA(static_cast<GLfloat>(emissive[0]), static_cast<GLfloat>(emissive[1]), static_cast<GLfloat>(emissive[2]), 1.0f);
	currentSurfaceMaterial->setEmissive(color);
	currentSurfaceMaterial->setEmissiveTexture(texture2D);

	texture2D.reset();
	const FbxDouble3 ambient = processMaterialProperty(surfaceMaterial, FbxSurfaceMaterial::sAmbient, FbxSurfaceMaterial::sAmbientFactor, defaultAmbient, texture2D);
	color.setRGBA(static_cast<GLfloat>(ambient[0]), static_cast<GLfloat>(ambient[1]), static_cast<GLfloat>(ambient[2]), 1.0f);
	currentSurfaceMaterial->setAmbient(color);
	currentSurfaceMaterial->setAmbientTexture(texture2D);

	texture2D.reset();
	const FbxDouble3 diffuse = processMaterialProperty(surfaceMaterial, FbxSurfaceMaterial::sDiffuse, FbxSurfaceMaterial::sDiffuseFactor, defaultDiffuse, texture2D);
	color.setRGBA(static_cast<GLfloat>(diffuse[0]), static_cast<GLfloat>(diffuse[1]), static_cast<GLfloat>(diffuse[2]), 1.0f);
	currentSurfaceMaterial->setDiffuse(color);
	currentSurfaceMaterial->setDiffuseTexture(texture2D);

	texture2D.reset();
	const FbxDouble3 specular = processMaterialProperty(surfaceMaterial, FbxSurfaceMaterial::sSpecular, FbxSurfaceMaterial::sSpecularFactor, defaultSpecular, texture2D);
	color.setRGBA(static_cast<GLfloat>(specular[0]), static_cast<GLfloat>(specular[1]), static_cast<GLfloat>(specular[2]), 1.0f);
	currentSurfaceMaterial->setSpecular(color);
	currentSurfaceMaterial->setSpecularTexture(texture2D);

	FbxProperty shininessProperty = surfaceMaterial->FindProperty(FbxSurfaceMaterial::sShininess);
	if (shininessProperty.IsValid())
	{
		double shininess = 0.0;
		shininess = shininessProperty.Get<double>();
		currentSurfaceMaterial->setShininess(static_cast<GLfloat>(shininess));
	}

	texture2D.reset();
	const FbxDouble3 reflection = processMaterialProperty(surfaceMaterial, FbxSurfaceMaterial::sReflection, FbxSurfaceMaterial::sReflectionFactor, defaultReflection, texture2D);
	color.setRGBA(static_cast<GLfloat>(reflection[0]), static_cast<GLfloat>(reflection[1]), static_cast<GLfloat>(reflection[2]), 1.0f);
	currentSurfaceMaterial->setReflection(color);
	currentSurfaceMaterial->setReflectionTexture(texture2D);

	// Refraction not supported by FBX, so set keep values

	// Only use the transparency factor.
	FbxProperty transparencyFactorProperty = surfaceMaterial->FindProperty(FbxSurfaceMaterial::sTransparencyFactor);
	if (transparencyFactorProperty.IsValid())
	{
		currentSurfaceMaterial->setTransparency(static_cast<float>(transparencyFactorProperty.Get<double>()));
	}

	FbxProperty normalMapProperty = surfaceMaterial->FindProperty(FbxSurfaceMaterial::sNormalMap);
	if (normalMapProperty.IsValid())
	{
		const int32_t textureCount = normalMapProperty.GetSrcObjectCount();
		if (textureCount)
		{
			const FbxFileTexture* fileTexture = static_cast<const FbxFileTexture*>(normalMapProperty.GetSrcObject(0));
			if (fileTexture)
			{
				texture2D = Texture2DManager::getInstance()->createTexture(fileTexture->GetFileName());

				if (!texture2D.get())
				{
					glusLogPrint(GLUS_LOG_WARNING, "Could not create file texture: %s", fileTexture->GetFileName());
				}
				else
				{
					texture2D->setAnisotropic(anisotropic);
				}

				currentSurfaceMaterial->setNormalMapTexture(texture2D);
			}
		}
	}

	currentSurfaceMaterials[materialIndex] = currentSurfaceMaterial;
	allSurfaceMaterials.push_back(currentSurfaceMaterial);

	glusLogPrint(GLUS_LOG_INFO, "Created material: %s", materialName.c_str());
}

FbxDouble3 FbxEntityFactory::processMaterialProperty(const FbxSurfaceMaterial * surfaceMaterial, const char * propertyName, const char * factorPropertyName, const FbxDouble3& defaultColor, Texture2DSP& texture2D) const
{
	FbxDouble3 result(defaultColor[0], defaultColor[1], defaultColor[2]);
	const FbxProperty property = surfaceMaterial->FindProperty(propertyName);
	const FbxProperty factorProperty = surfaceMaterial->FindProperty(factorPropertyName);
	if (property.IsValid())
	{
		result = property.Get<FbxDouble3>();

		if (factorProperty.IsValid())
		{
			double factor = factorProperty.Get<double>();
			if (factor != 1)
			{
				result[0] *= factor;
				result[1] *= factor;
				result[2] *= factor;
			}
		}
	}

	if (property.IsValid())
	{
		const int32_t textureCount = property.GetSrcObjectCount();
		if (textureCount)
		{
			const FbxFileTexture* fileTexture = static_cast<const FbxFileTexture*>(property.GetSrcObject(0));
			if (fileTexture)
			{
				texture2D = Texture2DManager::getInstance()->createTexture(fileTexture->GetFileName());

				if (!texture2D.get())
				{
					glusLogPrint(GLUS_LOG_WARNING, "Could not create file texture: %s", fileTexture->GetFileName());
				}
				else
				{
					texture2D->setAnisotropic(anisotropic);
				}
			}
		}
	}

	return result;
}

void FbxEntityFactory::traverseNode(FbxNode* node, const NodeSP& parentNode)
{
	NodeSP newParentNode = parentNode;

	FbxNodeAttribute::EType attributeType;

	if (node->GetNodeAttribute())
	{
		attributeType = node->GetNodeAttribute()->GetAttributeType();
	}
	else
	{
		attributeType = FbxNodeAttribute::eNull;
	}

	bool createNode = false;

	MeshSP newMesh;
	CameraSP newCamera;
	LightSP newLight;

	switch (attributeType)
	{
		case FbxNodeAttribute::eUnknown:
		break;
		case FbxNodeAttribute::eNull:
			createNode = true;
		break;
		case FbxNodeAttribute::eMarker:
		break;
		case FbxNodeAttribute::eSkeleton:
			currentEntitySkinned = true;

			createNode = true;
		break;
		case FbxNodeAttribute::eMesh:
			if (loadMesh)
			{
				currentSurfaceMaterials.clear();

				for (int32_t i = 0; i < node->GetMaterialCount(); i++)
				{
					if (!currentSurfaceMaterial.get())
					{
						processSurfaceMaterial(i, node->GetMaterial(i));
					}
					else
					{
						currentSurfaceMaterials[i] = currentSurfaceMaterial;
					}
				}

				newMesh = processMesh(node->GetMesh());

				glusLogPrint(GLUS_LOG_INFO, "Created mesh in node: %s", node->GetName());

				createNode = true;
			}
		break;
		case FbxNodeAttribute::eNurbs:
		break;
		case FbxNodeAttribute::ePatch:
		break;
		case FbxNodeAttribute::eCamera:
			if (loadCamera)
			{
				newCamera = processCamera(node->GetCamera());

				glusLogPrint(GLUS_LOG_INFO, "Created camera in node: %s", node->GetName());

				createNode = true;
			}
		break;
		case FbxNodeAttribute::eCameraStereo:
		break;
		case FbxNodeAttribute::eCameraSwitcher:
		break;
		case FbxNodeAttribute::eLight:
			if (loadLight)
			{
				newLight = processLight(node->GetLight());

				glusLogPrint(GLUS_LOG_INFO, "Created light in node: %s", node->GetName());

				createNode = true;
			}
		break;
		case FbxNodeAttribute::eOpticalReference:
		break;
		case FbxNodeAttribute::eOpticalMarker:
		break;
		case FbxNodeAttribute::eNurbsCurve:
		break;
		case FbxNodeAttribute::eTrimNurbsSurface:
		break;
		case FbxNodeAttribute::eBoundary:
		break;
		case FbxNodeAttribute::eNurbsSurface:
		break;
		case FbxNodeAttribute::eShape:
		break;
		case FbxNodeAttribute::eLODGroup:
		break;
		case FbxNodeAttribute::eSubDiv:
		break;
		case FbxNodeAttribute::eCachedEffect:
		break;
		case FbxNodeAttribute::eLine:
		break;
	};

	if (createNode)
	{
		float translate[3] = { 0.0f, 0.0f, 0.0f };
		float postRotate[3] = { 0.0f, 0.0f, 0.0f };
		float rotate[3] = { 0.0f, 0.0f, 0.0f };
		float preRotate[3] = { 0.0f, 0.0f, 0.0f };
		float rotatePivot[3] = { 0.0f, 0.0f, 0.0f };
		float rotateOffset[3] = { 0.0f, 0.0f, 0.0f };
		float scale[3] = { 1.0f, 1.0f, 1.0f };
		float scalePivot[3] = { 0.0f, 0.0f, 0.0f };
		float scaleOffset[3] = { 0.0f, 0.0f, 0.0f };

		float geoTranslate[3] = { 0.0f, 0.0f, 0.0f };
		float geoRotate[3] = { 0.0f, 0.0f, 0.0f };
		float geoScale[3] = { 1.0f, 1.0f, 1.0f };

		translate[0] = static_cast<float>(node->LclTranslation.Get()[0]);
		translate[1] = static_cast<float>(node->LclTranslation.Get()[1]);
		translate[2] = static_cast<float>(node->LclTranslation.Get()[2]);

		geoTranslate[0] = static_cast<float>(node->GeometricTranslation.Get()[0]);
		geoTranslate[1] = static_cast<float>(node->GeometricTranslation.Get()[1]);
		geoTranslate[2] = static_cast<float>(node->GeometricTranslation.Get()[2]);

		//

		rotateOffset[0] = static_cast<float>(node->RotationOffset.Get()[0]);
		rotateOffset[1] = static_cast<float>(node->RotationOffset.Get()[1]);
		rotateOffset[2] = static_cast<float>(node->RotationOffset.Get()[2]);

		rotatePivot[0] = static_cast<float>(node->RotationPivot.Get()[0]);
		rotatePivot[1] = static_cast<float>(node->RotationPivot.Get()[1]);
		rotatePivot[2] = static_cast<float>(node->RotationPivot.Get()[2]);

		preRotate[0] = static_cast<float>(node->PreRotation.Get()[0]);
		preRotate[1] = static_cast<float>(node->PreRotation.Get()[1]);
		preRotate[2] = static_cast<float>(node->PreRotation.Get()[2]);

		postRotate[0] = static_cast<float>(node->PostRotation.Get()[0]);
		postRotate[1] = static_cast<float>(node->PostRotation.Get()[1]);
		postRotate[2] = static_cast<float>(node->PostRotation.Get()[2]);

		rotate[0] = static_cast<float>(node->LclRotation.Get()[0]);
		rotate[1] = static_cast<float>(node->LclRotation.Get()[1]);
		rotate[2] = static_cast<float>(node->LclRotation.Get()[2]);

		geoRotate[0] = static_cast<float>(node->GeometricRotation.Get()[0]);
		geoRotate[1] = static_cast<float>(node->GeometricRotation.Get()[1]);
		geoRotate[2] = static_cast<float>(node->GeometricRotation.Get()[2]);

		//

		scaleOffset[0] = static_cast<float>(node->ScalingOffset.Get()[0]);
		scaleOffset[1] = static_cast<float>(node->ScalingOffset.Get()[1]);
		scaleOffset[2] = static_cast<float>(node->ScalingOffset.Get()[2]);

		//scalePivot[0] = static_cast<float>(node->ScalingPivot.Get()[0]);
		scalePivot[1] = static_cast<float>(node->ScalingPivot.Get()[1]);
		scalePivot[2] = static_cast<float>(node->ScalingPivot.Get()[2]);

		scale[0] = static_cast<float>(node->LclScaling.Get()[0]);
		scale[1] = static_cast<float>(node->LclScaling.Get()[1]);
		scale[2] = static_cast<float>(node->LclScaling.Get()[2]);

		geoScale[0] = static_cast<float>(node->GeometricScaling.Get()[0]);
		geoScale[1] = static_cast<float>(node->GeometricScaling.Get()[1]);
		geoScale[2] = static_cast<float>(node->GeometricScaling.Get()[2]);

		//

		// Animation
		vector<AnimationStackSP> allAnimationStacks;
		AnimationStackSP currentAnimationStack;
		for (int32_t i = 0; i < currentNumberAnimationStacks; i++)
		{
			currentAnimationStack = processAnimation(node, i);

			if (currentAnimationStack.get())
			{
				allAnimationStacks.push_back(currentAnimationStack);
			}
		}

		string parentNodeName = parentNode.get() ? parentNode->getName() : "[NULL]";

		NodeSP newNode = nodeTreeFactory.createNode(node->GetName(), parentNodeName, translate, rotateOffset, rotatePivot, preRotate, rotate, postRotate, scaleOffset, scalePivot, scale, geoTranslate, geoRotate, geoScale, newMesh, newCamera, newLight, allAnimationStacks);

		glusLogPrint(GLUS_LOG_INFO, "Created node: %s", node->GetName());

		newParentNode = newNode;
	}

	for (int i = 0; i < node->GetChildCount(); i++)
	{
		traverseNode(node->GetChild(i), newParentNode);
	}
}

AnimationStackSP FbxEntityFactory::processAnimation(FbxNode* node, int32_t animStackIndex)
{
	FbxAnimStack* animStack = node->GetScene()->FindMember<FbxAnimStack>(animStackNameArray[animStackIndex]->Buffer());

	if (animStack)
	{
		string animStackName(animStack->GetName());

		//

		auto walker = allAnimationStacks.begin();
		while (walker != allAnimationStacks.end())
		{
			if ((*walker)->getName().compare(animStackName) == 0)
			{
				glusLogPrint(GLUS_LOG_INFO, "Reused animation stack: %s", animStack->GetName());

				return *walker;
			}

			walker++;
		}

		//
		node->GetScene()->SetCurrentAnimationStack(animStack);

		float currentStartTime = static_cast<float>(animStack->ReferenceStart.Get().GetSecondDouble());
		float currentStopTime = static_cast<float>(animStack->ReferenceStop.Get().GetSecondDouble());

		currentEntityAnimated = true;

		AnimationStack* newAnimStack = new AnimationStack(animStackName, currentStartTime, currentStopTime);

		int32_t numberAnimationLayers = animStack->GetMemberCount();

		FbxAnimLayer* animLayer = 0;
		AnimationLayerSP newAnimLayer;
		FbxAnimCurve* animCurve = 0;
		enum AnimationLayer::eCHANNELS_XYZ currentChannel = AnimationLayer::X;
		float time;
		float value;

		bool minTranslation[3];
		bool maxTranslation[3];
		bool minRotation[3];
		bool maxRotation[3];
		bool minScaling[3];
		bool maxScaling[3];
		float limitedValue;

		if (node->GetTranslationLimits().GetActive())
		{
			node->GetTranslationLimits().GetMinActive(minTranslation[0], minTranslation[1], minTranslation[2]);
			node->GetTranslationLimits().GetMaxActive(maxTranslation[0], maxTranslation[1], maxTranslation[2]);
		}
		if (node->GetRotationLimits().GetActive())
		{
			node->GetRotationLimits().GetMinActive(minRotation[0], minRotation[1], minRotation[2]);
			node->GetRotationLimits().GetMaxActive(maxRotation[0], maxRotation[1], maxRotation[2]);
		}
		if (node->GetScalingLimits().GetActive())
		{
			node->GetScalingLimits().GetMinActive(minScaling[0], minScaling[1], minScaling[2]);
			node->GetScalingLimits().GetMaxActive(maxScaling[0], maxScaling[1], maxScaling[2]);
		}

		for (int32_t i = 0; i < numberAnimationLayers; i++)
		{
			animLayer = static_cast<FbxAnimLayer*>(animStack->GetMember(i));

			newAnimLayer = AnimationLayerSP(new AnimationLayer());

			for (int32_t k = 0; k < 3; k++)
			{
				// Translation
				animCurve = node->LclTranslation.GetCurve(animLayer, CHANNELS[k]);

				if (strcmp(CHANNELS[k], CHANNELS[0]) == 0)
				{
					currentChannel = AnimationLayer::X;
				}
				else if (strcmp(CHANNELS[k], CHANNELS[1]) == 0)
				{
					currentChannel = AnimationLayer::Y;
				}
				else if (strcmp(CHANNELS[k], CHANNELS[2]) == 0)
				{
					currentChannel = AnimationLayer::Z;
				}

				if (animCurve && animCurve->KeyGetCount())
				{
					for (int32_t m = 0; m < animCurve->KeyGetCount(); m++)
					{
						time = static_cast<float>(animCurve->KeyGetTime(m).GetSecondDouble());

						value = static_cast<float>(animCurve->KeyGetValue(m));

						if (node->GetTranslationLimits().GetActive())
						{
							if (minTranslation[k])
							{
								limitedValue = static_cast<float>(node->GetTranslationLimits().GetMin()[k]);

								if (limitedValue < value)
								{
									value = limitedValue;
								}
							}

							if (maxTranslation[k])
							{
								limitedValue = static_cast<float>(node->GetTranslationLimits().GetMax()[k]);

								if (limitedValue > value)
								{
									value = limitedValue;
								}
							}
						}

						switch (animCurve->KeyGetInterpolation(m))
						{
							case FbxAnimCurveDef::eInterpolationConstant:
								newAnimLayer->addTranslationValue(currentChannel, time, value, ConstantInterpolator::interpolator);
							break;
							case FbxAnimCurveDef::eInterpolationLinear:
								newAnimLayer->addTranslationValue(currentChannel, time, value, LinearInterpolator::interpolator);
							break;
							case FbxAnimCurveDef::eInterpolationCubic:
								newAnimLayer->addTranslationValue(currentChannel, time, value, CubicInterpolator::interpolator);
							break;
						}
					}
				}

				// Rotation
				animCurve = node->LclRotation.GetCurve(animLayer, CHANNELS[k]);

				if (animCurve && animCurve->KeyGetCount())
				{
					for (int32_t m = 0; m < animCurve->KeyGetCount(); m++)
					{
						time = static_cast<float>(animCurve->KeyGetTime(m).GetSecondDouble());

						value = static_cast<float>(animCurve->KeyGetValue(m));

						if (node->GetRotationLimits().GetActive())
						{
							if (minRotation[k])
							{
								limitedValue = static_cast<float>(node->GetRotationLimits().GetMin()[k]);

								if (limitedValue < value)
								{
									value = limitedValue;
								}
							}

							if (maxRotation[k])
							{
								limitedValue = static_cast<float>(node->GetRotationLimits().GetMax()[k]);

								if (limitedValue > value)
								{
									value = limitedValue;
								}
							}
						}

						switch (animCurve->KeyGetInterpolation(m))
						{
							case FbxAnimCurveDef::eInterpolationConstant:
								newAnimLayer->addRotationValue(currentChannel, time, value, ConstantInterpolator::interpolator);
							break;
							case FbxAnimCurveDef::eInterpolationLinear:
								newAnimLayer->addRotationValue(currentChannel, time, value, LinearInterpolator::interpolator);
							break;
							case FbxAnimCurveDef::eInterpolationCubic:
								newAnimLayer->addRotationValue(currentChannel, time, value, CubicInterpolator::interpolator);
							break;
						}
					}
				}

				// Scaling
				animCurve = node->LclScaling.GetCurve(animLayer, CHANNELS[k]);

				if (animCurve && animCurve->KeyGetCount())
				{
					for (int32_t m = 0; m < animCurve->KeyGetCount(); m++)
					{
						time = static_cast<float>(animCurve->KeyGetTime(m).GetSecondDouble());

						value = static_cast<float>(animCurve->KeyGetValue(m));

						if (node->GetScalingLimits().GetActive())
						{
							if (minScaling[k])
							{
								limitedValue = static_cast<float>(node->GetScalingLimits().GetMin()[k]);

								if (limitedValue < value)
								{
									value = limitedValue;
								}
							}

							if (maxScaling[k])
							{
								limitedValue = static_cast<float>(node->GetScalingLimits().GetMax()[k]);

								if (limitedValue > value)
								{
									value = limitedValue;
								}
							}
						}

						switch (animCurve->KeyGetInterpolation(m))
						{
							case FbxAnimCurveDef::eInterpolationConstant:
								newAnimLayer->addScalingValue(currentChannel, time, value, ConstantInterpolator::interpolator);
							break;
							case FbxAnimCurveDef::eInterpolationLinear:
								newAnimLayer->addScalingValue(currentChannel, time, value, LinearInterpolator::interpolator);
							break;
							case FbxAnimCurveDef::eInterpolationCubic:
								newAnimLayer->addScalingValue(currentChannel, time, value, CubicInterpolator::interpolator);
							break;
						}
					}
				}
			}

			newAnimStack->addAnimationLayer(newAnimLayer);
		}

		return AnimationStackSP(newAnimStack);
	}

	return AnimationStackSP();
}

// See example in SceneCache.cxx
MeshSP FbxEntityFactory::processMesh(FbxMesh* mesh)
{
	//

	string meshName(mesh->GetName());

	if (meshName.compare("") == 0)
	{
		meshName = mesh->GetNode()->GetName();
	}

	//

	auto walkerMesh = allMeshes.begin();
	while (walkerMesh != allMeshes.end())
	{
		if ((*walkerMesh)->getName().compare(meshName) == 0)
		{
			glusLogPrint(GLUS_LOG_INFO, "Reused mesh: %s", meshName.c_str());

			return *walkerMesh;
		}

		walkerMesh++;
	}

	//

	map<int32_t, FbxSubMeshSP> currentFbxSubMeshes;

	// Sub meshes

	currentFbxSubMeshes[0] = FbxSubMeshSP(new FbxSubMesh());
	currentFbxSubMeshes[0]->setTriangleCount(mesh->GetPolygonCount());
	FbxLayerElementArrayTemplate<int32_t>* materialIndice = 0;
	FbxGeometryElement::EMappingMode materialMappingMode = FbxGeometryElement::eNone;
	if (mesh->GetElementMaterial())
	{
		materialIndice = &mesh->GetElementMaterial()->GetIndexArray();

		materialMappingMode = mesh->GetElementMaterial()->GetMappingMode();
		if (materialIndice && materialMappingMode == FbxGeometryElement::eByPolygon)
		{
			currentFbxSubMeshes[0]->setTriangleCount(0);
			// Count the triangles of each material
			for (int32_t polygonIndex = 0; polygonIndex < mesh->GetPolygonCount(); ++polygonIndex)
			{
				const int32_t materialIndex = materialIndice->GetAt(polygonIndex);

				if (currentFbxSubMeshes[materialIndex].get() == 0)
				{
					currentFbxSubMeshes[materialIndex] = FbxSubMeshSP(new FbxSubMesh());
				}
				currentFbxSubMeshes[materialIndex]->increaseTriangleCount();
			}

			// Calculate the offset for each sub mesh
			uint32_t currentIndexOffset = 0;
			for (uint32_t materialIndex = 0; materialIndex < currentFbxSubMeshes.size(); ++materialIndex)
			{
				currentFbxSubMeshes[materialIndex]->setIndicesOffset(currentIndexOffset);

				currentIndexOffset += currentFbxSubMeshes[materialIndex]->getTriangleCount() * 3;
			}
		}
	}
	else
	{
		glusLogPrint(GLUS_LOG_WARNING, "Mesh '%s' has no material.", meshName.c_str());
	}

	bool allByControlPoint = true;
	bool hasNormal = mesh->GetElementNormalCount() > 0;
	bool hasTangent = mesh->GetElementTangentCount() > 0;
	bool hasBinormal = mesh->GetElementBinormalCount() > 0;
	bool hasUV = mesh->GetElementUVCount() > 0;
	FbxGeometryElement::EMappingMode normalMappingMode = FbxGeometryElement::eNone;
	FbxGeometryElement::EMappingMode tangentMappingMode = FbxGeometryElement::eNone;
	FbxGeometryElement::EMappingMode binormalMappingMode = FbxGeometryElement::eNone;
	FbxGeometryElement::EMappingMode uvMappingMode = FbxGeometryElement::eNone;
	if (hasNormal)
	{
		normalMappingMode = mesh->GetElementNormal(0)->GetMappingMode();
		if (normalMappingMode == FbxGeometryElement::eNone)
		{
			hasNormal = false;
		}
		if (hasNormal && normalMappingMode != FbxGeometryElement::eByControlPoint)
		{
			allByControlPoint = false;
		}
	}
	if (hasTangent)
	{
		tangentMappingMode = mesh->GetElementTangent(0)->GetMappingMode();
		if (tangentMappingMode == FbxGeometryElement::eNone)
		{
			hasTangent = false;
		}
		if (hasTangent && tangentMappingMode != FbxGeometryElement::eByControlPoint)
		{
			allByControlPoint = false;
		}
	}
	if (hasBinormal)
	{
		binormalMappingMode = mesh->GetElementBinormal(0)->GetMappingMode();
		if (binormalMappingMode == FbxGeometryElement::eNone)
		{
			hasBinormal = false;
		}
		if (hasBinormal && binormalMappingMode != FbxGeometryElement::eByControlPoint)
		{
			allByControlPoint = false;
		}
	}
	if (hasUV)
	{
		uvMappingMode = mesh->GetElementUV(0)->GetMappingMode();
		if (uvMappingMode == FbxGeometryElement::eNone)
		{
			hasUV = false;
		}
		if (hasUV && uvMappingMode != FbxGeometryElement::eByControlPoint)
		{
			allByControlPoint = false;
		}
	}

	// Vertices etc.

	uint32_t polygonCount;
	uint32_t numberVertices;

	float* vertices = 0;
	float* normals = 0;
	float* tangents = 0;
	float* binormals = 0;
	float* texCoords = 0;

	uint32_t numberIndices;

	uint32_t* indices = 0;
	uint32_t* indicesToOrgIndices = 0;

	polygonCount = mesh->GetPolygonCount();
	numberVertices = mesh->GetControlPointsCount();
	if (!allByControlPoint)
	{
		numberVertices = polygonCount * 3;

		hasTangent = false;
		hasBinormal = false;
	}

	vertices = new float[numberVertices * 4];
	if (hasNormal)
	{
		normals = new float[numberVertices * 3];
	}
	if (hasTangent)
	{
		tangents = new float[numberVertices * 3];
	}
	if (hasBinormal)
	{
		binormals = new float[numberVertices * 3];
	}
	FbxStringList uvNames;
	mesh->GetUVSetNames(uvNames);
	const char * uvName = 0;
	if (hasUV && uvNames.GetCount())
	{
		texCoords = new float[numberVertices * 2];
		uvName = uvNames[0];
	}
	else
	{
		hasUV = false;
	}

	numberIndices = polygonCount * 3;
	indices = new uint32_t[numberIndices];

	// Populate the array with vertex attribute
	const FbxVector4 * controlPoints = mesh->GetControlPoints();
	FbxVector4 currentVertex;
	FbxVector4 currentNormal;
	FbxVector4 currentTangent;
	FbxVector4 currentBinormal;
	FbxVector2 currentUV;
	if (allByControlPoint)
	{
		const FbxGeometryElementNormal* normalElement = 0;
		const FbxGeometryElementTangent* tangentElement = 0;
		const FbxGeometryElementBinormal* binormalElement = 0;
		const FbxGeometryElementUV* uvElement = 0;
		if (hasNormal)
		{
			normalElement = mesh->GetElementNormal(0);
		}
		if (hasTangent)
		{
			tangentElement = mesh->GetElementTangent(0);
		}
		if (hasBinormal)
		{
			binormalElement = mesh->GetElementBinormal(0);
		}
		if (hasUV)
		{
			uvElement = mesh->GetElementUV(0);
		}
		for (int32_t index = 0; index < mesh->GetControlPointsCount(); ++index)
		{
			// Save the vertex position.
			currentVertex = controlPoints[index];
			vertices[index * 4 + 0] = static_cast<float>(currentVertex[0]);
			vertices[index * 4 + 1] = static_cast<float>(currentVertex[1]);
			vertices[index * 4 + 2] = static_cast<float>(currentVertex[2]);
			vertices[index * 4 + 3] = 1;

			// Save the normal.
			if (mesh->GetElementNormalCount() > 0)
			{
				int32_t normalIndex = index;
				if (normalElement->GetReferenceMode() != FbxGeometryElement::eDirect)
				{
					normalIndex = normalElement->GetIndexArray().GetAt(index);
				}
				currentNormal = normalElement->GetDirectArray().GetAt(normalIndex);
				normals[index * 3 + 0] = static_cast<float>(currentNormal[0]);
				normals[index * 3 + 1] = static_cast<float>(currentNormal[1]);
				normals[index * 3 + 2] = static_cast<float>(currentNormal[2]);
			}

			// Save the tangent.
			if (mesh->GetElementTangentCount() > 0)
			{
				int32_t tangentIndex = index;
				if (tangentElement->GetReferenceMode() != FbxGeometryElement::eDirect)
				{
					tangentIndex = tangentElement->GetIndexArray().GetAt(index);
				}
				currentTangent = tangentElement->GetDirectArray().GetAt(tangentIndex);
				tangents[index * 3 + 0] = static_cast<float>(currentTangent[0]);
				tangents[index * 3 + 1] = static_cast<float>(currentTangent[1]);
				tangents[index * 3 + 2] = static_cast<float>(currentTangent[2]);
			}

			// Save the binormal.
			if (mesh->GetElementBinormalCount() > 0)
			{
				int32_t binormalIndex = index;
				if (binormalElement->GetReferenceMode() != FbxGeometryElement::eDirect)
				{
					binormalIndex = binormalElement->GetIndexArray().GetAt(index);
				}
				currentBinormal = binormalElement->GetDirectArray().GetAt(binormalIndex);
				binormals[index * 3 + 0] = static_cast<float>(currentBinormal[0]);
				binormals[index * 3 + 1] = static_cast<float>(currentBinormal[1]);
				binormals[index * 3 + 2] = static_cast<float>(currentBinormal[2]);
			}

			// Save the UV.
			if (mesh->GetElementUVCount() > 0)
			{
				int32_t uvIndex = index;
				if (uvElement->GetReferenceMode() != FbxGeometryElement::eDirect)
				{
					uvIndex = uvElement->GetIndexArray().GetAt(index);
				}
				currentUV = uvElement->GetDirectArray().GetAt(uvIndex);
				texCoords[index * 2 + 0] = static_cast<float>(currentUV[0]);
				texCoords[index * 2 + 1] = static_cast<float>(currentUV[1]);
			}
		}
	}

	if (!allByControlPoint)
	{
		indicesToOrgIndices = new uint32_t[numberIndices];

		mesh->SetUserDataPtr(indicesToOrgIndices);
	}
	else
	{
		mesh->SetUserDataPtr(0);
	}

	// Populate the array with indices
	uint32_t vertexCount = 0;
	for (int32_t polygonIndex = 0; polygonIndex < mesh->GetPolygonCount(); ++polygonIndex)
	{
		int32_t materialIndex = 0;
		if (materialIndice && materialMappingMode == FbxGeometryElement::eByPolygon)
		{
			materialIndex = materialIndice->GetAt(polygonIndex);
		}

		// Store indices with same material together
		uint32_t indexOffset = currentFbxSubMeshes[materialIndex]->getIndicesOffset() + currentFbxSubMeshes[materialIndex]->getAndIncreaseStoredIndices();

		for (int32_t verticeIndex = 0; verticeIndex < 3; ++verticeIndex)
		{
			const int controlPointIndex = mesh->GetPolygonVertex(polygonIndex, verticeIndex);

			if (allByControlPoint)
			{
				indices[indexOffset + verticeIndex] = static_cast<uint32_t>(controlPointIndex);
			}
			else
			{
				indices[indexOffset + verticeIndex] = vertexCount;
				indicesToOrgIndices[indexOffset + verticeIndex] = static_cast<uint32_t>(controlPointIndex);

				currentVertex = controlPoints[controlPointIndex];
				vertices[vertexCount * 4 + 0] = static_cast<float>(currentVertex[0]);
				vertices[vertexCount * 4 + 1] = static_cast<float>(currentVertex[1]);
				vertices[vertexCount * 4 + 2] = static_cast<float>(currentVertex[2]);
				vertices[vertexCount * 4 + 3] = 1.0f;

				if (hasNormal)
				{
					mesh->GetPolygonVertexNormal(polygonIndex, verticeIndex, currentNormal);
					normals[vertexCount * 3 + 0] = static_cast<float>(currentNormal[0]);
					normals[vertexCount * 3 + 1] = static_cast<float>(currentNormal[1]);
					normals[vertexCount * 3 + 2] = static_cast<float>(currentNormal[2]);
				}

				if (hasUV)
				{
					bool unmapped;

					mesh->GetPolygonVertexUV(polygonIndex, verticeIndex, uvName, currentUV, unmapped);
					texCoords[vertexCount * 2 + 0] = static_cast<float>(currentUV[0]);
					texCoords[vertexCount * 2 + 1] = static_cast<float>(currentUV[1]);
				}
			}
			vertexCount++;
		}
	}

	map<int32_t, SubMeshSP> currentSubMeshes;

	auto walker = currentFbxSubMeshes.begin();

	while (walker != currentFbxSubMeshes.end())
	{
		currentSubMeshes[walker->first] = SubMeshSP(new SubMesh(walker->second->getIndicesOffset(), walker->second->getTriangleCount()));

		walker->second.reset();
		walker++;
	}
	currentFbxSubMeshes.clear();

	// Create tangents and bitangents when not already created
	if (!tangents)
	{
		GLUSshape meshShape;
		meshShape.mode = GL_TRIANGLES;
		meshShape.numberVertices = numberVertices;
		meshShape.vertices = vertices;
		meshShape.normals = normals;
		meshShape.bitangents = binormals;
		meshShape.tangents = tangents;
		meshShape.texCoords = texCoords;
		meshShape.numberIndices = numberIndices;
		meshShape.indices = indices;
		meshShape.allAttributes = 0;

		glusShapeCalculateTangentBitangentf(&meshShape);

		binormals = meshShape.bitangents;
		tangents = meshShape.tangents;
	}

	glusLogPrint(GLUS_LOG_INFO, "Created mesh: %s", meshName.c_str());

	return MeshSP(new Mesh(meshName, numberVertices, vertices, normals, binormals, tangents, texCoords, numberIndices, indices, currentSubMeshes, currentSurfaceMaterials));
}

LightSP FbxEntityFactory::processLight(FbxLight* light)
{
	//

	string lightName(light->GetName());

	if (lightName.compare("") == 0)
	{
		lightName = light->GetNode()->GetName();
	}

	//

	auto walkerLight = allLights.begin();
	while (walkerLight != allLights.end())
	{
		if ((*walkerLight)->getName().compare(lightName) == 0)
		{
			glusLogPrint(GLUS_LOG_INFO, "Reused light: %s", lightName.c_str());

			return *walkerLight;
		}

		walkerLight++;
	}

	//

	FbxLight::EType lightType = light->LightType.Get();

	LightSP currentLight;

	Color diffuse;
	Color specular;

	float intensity = static_cast<float>(light->Intensity.Get() / 100.0f);

	diffuse.setR(static_cast<float>(light->Color.Get()[0]) * intensity);
	diffuse.setG(static_cast<float>(light->Color.Get()[1]) * intensity);
	diffuse.setB(static_cast<float>(light->Color.Get()[2]) * intensity);

	specular = diffuse;

	float constantAttenuation = 1.0f;
	float linearAttenuation = 0.0f;
	float quadraticAttenuation = 0.0f;

	float farAttenuation = 2.0f;

	if (light->EnableFarAttenuation.Get() && light->FarAttenuationEnd.IsValid() && light->FarAttenuationEnd.Get() > 0.0f)
	{
		farAttenuation = static_cast<float>(light->FarAttenuationEnd.Get());
	}

	switch (light->DecayType)
	{
		case FbxLight::eNone:
		break;
		case FbxLight::eLinear:
			linearAttenuation = 1.0f / (farAttenuation * 0.5f);
		break;
		case FbxLight::eQuadratic:
			quadraticAttenuation = 1.0f / (farAttenuation * farAttenuation * 0.25f);
		break;
		case FbxLight::eCubic:
			glusLogPrint(GLUS_LOG_WARNING, "Cubic attenuation not supported.");
		break;
	}

	if (lightType == FbxLight::eDirectional)
	{
		DirectionalLightSP directionalLight = DirectionalLightSP(new DirectionalLight(lightName, diffuse, specular));

		currentLight = directionalLight;
	}
	else if (lightType == FbxLight::ePoint)
	{
		PointLightSP pointLight = PointLightSP(new PointLight(lightName, constantAttenuation, linearAttenuation, quadraticAttenuation, diffuse, specular));

		currentLight = pointLight;
	}
	else if (lightType == FbxLight::eSpot)
	{
		float spotCosCutOff = cosf(glusMathDegToRadf(static_cast<float>(light->InnerAngle.Get())));
		float spotCosCutOffOuter = cosf(glusMathDegToRadf(static_cast<float>(light->OuterAngle.Get())));

		SpotLightSP spotLight = SpotLightSP(new SpotLight(lightName, spotCosCutOff, spotCosCutOffOuter, constantAttenuation, linearAttenuation, quadraticAttenuation, diffuse, specular));

		currentLight = spotLight;
	}
	else
	{
		return LightSP();
	}

	allLights.push_back(currentLight);

	glusLogPrint(GLUS_LOG_INFO, "Created light: %s", lightName.c_str());

	return currentLight;
}

CameraSP FbxEntityFactory::processCamera(FbxCamera* camera)
{
	//

	string cameraName(camera->GetName());

	if (cameraName.compare("") == 0)
	{
		cameraName = camera->GetNode()->GetName();
	}

	//

	auto walkerCamera = allCameras.begin();
	while (walkerCamera != allCameras.end())
	{
		if ((*walkerCamera)->getName().compare(cameraName) == 0)
		{
			glusLogPrint(GLUS_LOG_INFO, "Reused camera: %s", cameraName.c_str());

			return *walkerCamera;
		}

		walkerCamera++;
	}

	//

	FbxCamera::EProjectionType projectionType = camera->ProjectionType.Get();

	CameraSP currentCamera;

	if (projectionType == FbxCamera::ePerspective)
	{
		PerspectiveCameraSP perspectiveCamera = PerspectiveCameraSP(new PerspectiveCamera(cameraName));

		FbxDouble fovx = -1.0f;
		FbxDouble fovy = -1.0f;

		switch (camera->GetApertureMode())
		{
			case FbxCamera::eHorizAndVert:
				fovx = camera->FieldOfViewX.Get();
				fovy = camera->FieldOfViewY.Get();
			break;
			case FbxCamera::eHorizontal:
				fovx = camera->FieldOfView.Get();
			break;
			case FbxCamera::eVertical:
				fovy = camera->FieldOfView.Get();
			break;
			case FbxCamera::eFocalLength:
				fovx = camera->ComputeFieldOfView(camera->FocalLength.Get());
			break;
		}

		if (fovx > 0.0f)
		{
			perspectiveCamera->setFovx(static_cast<float>(fovx));
		}
		else if (fovy > 0.0f)
		{
			perspectiveCamera->setFovy(static_cast<float>(fovy));
		}

		currentCamera = perspectiveCamera;
	}
	else if (projectionType == FbxCamera::eOrthogonal)
	{
		OrthographicCameraSP orthographicCamera = OrthographicCameraSP(new OrthographicCamera(cameraName));

		currentCamera = orthographicCamera;
	}
	else
	{
		return CameraSP();
	}

	currentCamera->setNearZ(static_cast<float>(camera->NearPlane.Get()));
	currentCamera->setFarZ(static_cast<float>(camera->FarPlane.Get()));

	allCameras.push_back(currentCamera);

	glusLogPrint(GLUS_LOG_INFO, "Created camera: %s", cameraName.c_str());

	return currentCamera;
}

void FbxEntityFactory::preTraverseIndexCreation(FbxNode* node, const NodeSP& nodeGE)
{
	FbxNodeAttribute::EType attributeType;

	if (node->GetNodeAttribute())
	{
		attributeType = node->GetNodeAttribute()->GetAttributeType();
	}
	else
	{
		attributeType = FbxNodeAttribute::eNull;
	}

	switch (attributeType)
	{
		case FbxNodeAttribute::eMesh:
		{
			int32_t numberDeformers = node->GetMesh()->GetDeformerCount(FbxDeformer::eSkin);

			for (int32_t deformerIndex = 0; deformerIndex < numberDeformers; deformerIndex++)
			{
				FbxSkin* skinDeformer = (FbxSkin*)node->GetMesh()->GetDeformer(deformerIndex, FbxDeformer::eSkin);

				int32_t numberClusters = skinDeformer->GetClusterCount();

				for (int32_t clusterIndex = 0; clusterIndex < numberClusters; clusterIndex++)
				{
					FbxCluster* cluster = skinDeformer->GetCluster(clusterIndex);

					FbxNode* linkNode = cluster->GetLink();

					if (!linkNode)
					{
						glusLogPrint(GLUS_LOG_WARNING, "No link node");

						continue;
					}

					nodeTreeFactory.setJoint(linkNode->GetName());
				}
			}
		}

		break;

		default:
			// Do nothing
		break;
	};

	for (int i = 0; i < node->GetChildCount(); i++)
	{
		try
		{
			NodeSP currentChild = nodeGE->getChild(node->GetChild(i)->GetName());
			preTraverseIndexCreation(node->GetChild(i), currentChild);
		} catch (...)
		{
		}
	}
}

void FbxEntityFactory::postTraverseNode(FbxNode* node, const NodeSP& nodeGE, const Matrix4x4& parentMatrix)
{
	static float vertices[2 * 4];

	Matrix4x4 newParentMatrix(parentMatrix);

	FbxNodeAttribute::EType attributeType;

	if (node->GetNodeAttribute())
	{
		attributeType = node->GetNodeAttribute()->GetAttributeType();
	}
	else
	{
		attributeType = FbxNodeAttribute::eNull;
	}

	switch (attributeType)
	{
		case FbxNodeAttribute::eMesh:
			if (loadMesh)
			{
				Matrix4x4 matrix;
				Matrix4x4 localMatrix;

				nodeGE->calculateLocalMatrix(localMatrix);

				newParentMatrix = newParentMatrix * localMatrix;

				matrix = newParentMatrix * nodeGE->getGeometricTransformMatrix();

				// Update the min max for the final bounding sphere
				processMinMax(nodeGE->getMesh()->getVertices(), nodeGE->getMesh()->getNumberVertices(), matrix);

				postProcessMesh(node->GetMesh(), nodeGE->getMesh());
			}
		break;

		case FbxNodeAttribute::eLight:
			if (loadLight)
			{
				Matrix4x4 matrix;
				Matrix4x4 localMatrix;

				nodeGE->calculateLocalMatrix(localMatrix);

				newParentMatrix = newParentMatrix * localMatrix;

				matrix = newParentMatrix * nodeGE->getGeometricTransformMatrix();

				for (int32_t i = 0; i < 2; i++)
				{
					vertices[4 * i + 0] = (i == 0) ? -Light::getDebugRadius() : Light::getDebugRadius();
					vertices[4 * i + 1] = (i == 0) ? -Light::getDebugRadius() : Light::getDebugRadius();
					vertices[4 * i + 2] = (i == 0) ? -Light::getDebugRadius() : Light::getDebugRadius();
					vertices[4 * i + 3] = 1.0f;
				}

				// Update the min max for the final bounding sphere
				processMinMax(vertices, 2, matrix);
			}
		break;

		case FbxNodeAttribute::eCamera:
			if (loadCamera)
			{
				Matrix4x4 matrix;
				Matrix4x4 localMatrix;

				nodeGE->calculateLocalMatrix(localMatrix);

				newParentMatrix = newParentMatrix * localMatrix;

				matrix = newParentMatrix * nodeGE->getGeometricTransformMatrix();

				for (int32_t i = 0; i < 2; i++)
				{
					vertices[4 * i + 0] = (i == 0) ? -Camera::getDebugRadius() : Camera::getDebugRadius();
					vertices[4 * i + 1] = (i == 0) ? -Camera::getDebugRadius() : Camera::getDebugRadius();
					vertices[4 * i + 2] = (i == 0) ? -Camera::getDebugRadius() : Camera::getDebugRadius();
					vertices[4 * i + 3] = 1.0f;
				}

				// Update the min max for the final bounding sphere
				processMinMax(vertices, 2, matrix);
			}
		break;

		default:
			// Do nothing
		break;
	};

	for (int i = 0; i < node->GetChildCount(); i++)
	{
		try
		{
			NodeSP currentChild = nodeGE->getChild(node->GetChild(i)->GetName());
			postTraverseNode(node->GetChild(i), currentChild, newParentMatrix);
		} catch (...)
		{
		}
	}
}

void FbxEntityFactory::processMinMax(const float* vertices, int32_t numberVertices, const Matrix4x4& matrix)
{
	GLfloat vertex[4];

	// Calculate bounding sphere from existing vertices in mesh
	for (int32_t i = 0; i < numberVertices; i++)
	{
		glusMatrix4x4MultiplyPoint4f(vertex, matrix.getM(), &vertices[i * 4]);

		if (doReset)
		{
			minX = vertex[0];
			maxX = vertex[0];
			minY = vertex[1];
			maxY = vertex[1];
			minZ = vertex[2];
			maxZ = vertex[2];

			doReset = false;
		}
		else
		{
			if (vertex[0] < minX)
			{
				minX = vertex[0];
			}
			if (vertex[0] > maxX)
			{
				maxX = vertex[0];
			}
			if (vertex[1] < minY)
			{
				minY = vertex[1];
			}
			if (vertex[1] > maxY)
			{
				maxY = vertex[1];
			}
			if (vertex[2] < minZ)
			{
				minZ = vertex[2];
			}
			if (vertex[2] > maxZ)
			{
				maxZ = vertex[2];
			}
		}
	}
}

void FbxEntityFactory::postProcessMesh(FbxMesh* mesh, const MeshSP& currentMesh)
{
	if (!currentMesh.get())
	{
		return;
	}

	float* allBoneIndices0 = new float[4 * currentMesh->getNumberVertices()];

	if (!allBoneIndices0)
	{
		glusLogPrint(GLUS_LOG_ERROR, "Out of memory");

		return;
	}

	float* allBoneIndices1 = new float[4 * currentMesh->getNumberVertices()];

	if (!allBoneIndices1)
	{
		glusLogPrint(GLUS_LOG_ERROR, "Out of memory");

		delete[] allBoneIndices0;

		return;
	}

	float* allBoneWeights0 = new float[4 * currentMesh->getNumberVertices()];

	if (!allBoneWeights0)
	{
		glusLogPrint(GLUS_LOG_ERROR, "Out of memory");

		delete[] allBoneIndices0;

		delete[] allBoneIndices1;

		return;
	}

	float* allBoneWeights1 = new float[4 * currentMesh->getNumberVertices()];

	if (!allBoneWeights1)
	{
		glusLogPrint(GLUS_LOG_ERROR, "Out of memory");

		delete[] allBoneIndices0;

		delete[] allBoneIndices1;

		delete[] allBoneWeights0;

		return;
	}

	float* allBoneCounters = new float[currentMesh->getNumberVertices()];

	if (!allBoneCounters)
	{
		glusLogPrint(GLUS_LOG_ERROR, "Out of memory");

		delete[] allBoneIndices0;

		delete[] allBoneIndices1;

		delete[] allBoneWeights0;

		delete[] allBoneWeights0;

		return;
	}

	for (uint32_t i = 0; i < 4 * currentMesh->getNumberVertices(); i++)
	{
		allBoneIndices0[i] = 0.0f;
		allBoneIndices1[i] = 0.0f;
		allBoneWeights0[i] = 0.0f;
		allBoneWeights1[i] = 0.0f;
	}

	for (uint32_t i = 0; i < currentMesh->getNumberVertices(); i++)
	{
		allBoneCounters[i] = 0.0f;
	}

	//

	int32_t numberDeformers = mesh->GetDeformerCount(FbxDeformer::eSkin);

	if (numberDeformers == 0 || numberDeformers > 1)
	{
		if (numberDeformers > 1)
		{
			glusLogPrint(GLUS_LOG_ERROR, "Number of deformers not supported: %d", numberDeformers);
		}

		delete[] allBoneIndices0;
		delete[] allBoneIndices1;

		delete[] allBoneWeights0;
		delete[] allBoneWeights1;

		delete[] allBoneCounters;

		return;
	}

	for (int32_t deformerIndex = 0; deformerIndex < numberDeformers; deformerIndex++)
	{
		FbxSkin* skinDeformer = (FbxSkin*)mesh->GetDeformer(deformerIndex, FbxDeformer::eSkin);

		int32_t numberClusters = skinDeformer->GetClusterCount();

		for (int32_t clusterIndex = 0; clusterIndex < numberClusters; clusterIndex++)
		{
			FbxCluster* cluster = skinDeformer->GetCluster(clusterIndex);

			FbxNode* linkNode = cluster->GetLink();

			if (!linkNode)
			{
				glusLogPrint(GLUS_LOG_WARNING, "No link node");

				continue;
			}

			int32_t boneIndex = nodeTreeFactory.getIndex(linkNode->GetName());

			if (boneIndex == -1)
			{
				glusLogPrint(GLUS_LOG_WARNING, "No bone found: %s", linkNode->GetName());

				continue;
			}

			int32_t numberIndices = cluster->GetControlPointIndicesCount();

			for (int32_t indicesIndex = 0; indicesIndex < numberIndices; indicesIndex++)
			{
				int32_t controlPointIndex = cluster->GetControlPointIndices()[indicesIndex];

				if (controlPointIndex < 0)
				{
					continue;
				}

				if (mesh->GetUserDataPtr())
				{
					uint32_t* indicesToOrgIndices = static_cast<uint32_t*>(mesh->GetUserDataPtr());

					for (uint32_t newIndex = 0; newIndex < currentMesh->getNumberIndices(); newIndex++)
					{
						if (indicesToOrgIndices[newIndex] != static_cast<uint32_t>(controlPointIndex))
						{
							continue;
						}

						int32_t mappedControlPointIndex = newIndex;

						if (static_cast<int32_t>(allBoneCounters[mappedControlPointIndex]) + 1 == MAX_SKIN_INDICES)
						{
							glusLogPrint(GLUS_LOG_ERROR, "Too many indices: %d", (static_cast<int32_t>(allBoneCounters[mappedControlPointIndex]) + 1));

							delete[] allBoneIndices0;
							delete[] allBoneIndices1;

							delete[] allBoneWeights0;
							delete[] allBoneWeights1;

							delete[] allBoneCounters;

							return;
						}

						double boneWeight = cluster->GetControlPointWeights()[indicesIndex];

						int32_t offset = static_cast<int32_t>(allBoneCounters[mappedControlPointIndex]);

						if (static_cast<int32_t>(allBoneCounters[mappedControlPointIndex]) < 4)
						{
							allBoneIndices0[4 * mappedControlPointIndex + offset] = static_cast<float>(boneIndex);
							allBoneWeights0[4 * mappedControlPointIndex + offset] = static_cast<float>(boneWeight);
						}
						else
						{
							allBoneIndices1[4 * mappedControlPointIndex + offset] = static_cast<float>(boneIndex);
							allBoneWeights1[4 * mappedControlPointIndex + offset] = static_cast<float>(boneWeight);
						}

						allBoneCounters[mappedControlPointIndex] += 1.0f;
					}
				}
				else
				{
					if (static_cast<int32_t>(allBoneCounters[controlPointIndex]) + 1 == MAX_SKIN_INDICES)
					{
						glusLogPrint(GLUS_LOG_ERROR, "Too many indices: %d", (static_cast<int32_t>(allBoneCounters[controlPointIndex]) + 1));

						delete[] allBoneIndices0;

						delete[] allBoneIndices1;

						delete[] allBoneWeights0;

						delete[] allBoneWeights1;

						delete[] allBoneCounters;

						return;
					}

					double boneWeight = cluster->GetControlPointWeights()[indicesIndex];

					int32_t offset = static_cast<int32_t>(allBoneCounters[controlPointIndex]);

					if (static_cast<int32_t>(allBoneCounters[controlPointIndex]) < 4)
					{
						allBoneIndices0[4 * controlPointIndex + offset] = static_cast<float>(boneIndex);
						allBoneWeights0[4 * controlPointIndex + offset] = static_cast<float>(boneWeight);
					}
					else
					{
						allBoneIndices1[4 * controlPointIndex + offset] = static_cast<float>(boneIndex);
						allBoneWeights1[4 * controlPointIndex + offset] = static_cast<float>(boneWeight);
					}

					allBoneCounters[controlPointIndex] += 1.0f;
				}
			}

			// Pose / Link Matrix

			FbxAMatrix matrix;


			cluster->GetTransformMatrix(matrix);

			float tm[16] = { static_cast<float>(matrix.Get(0, 0)), static_cast<float>(matrix.Get(0, 1)), static_cast<float>(matrix.Get(0, 2)), static_cast<float>(matrix.Get(0, 3)), static_cast<float>(matrix.Get(1, 0)), static_cast<float>(matrix.Get(1, 1)), static_cast<float>(matrix.Get(1, 2)), static_cast<float>(matrix.Get(1, 3)), static_cast<float>(matrix.Get(2, 0)), static_cast<float>(matrix.Get(2, 1)), static_cast<float>(matrix.Get(2, 2)), static_cast<float>(matrix.Get(2, 3)), static_cast<float>(matrix.Get(3, 0)), static_cast<float>(matrix.Get(3, 1)), static_cast<float>(matrix.Get(3, 2)), static_cast<float>(matrix.Get(3, 3)) };

			Matrix4x4 transformMatrix(tm);
			cluster->GetTransformLinkMatrix(matrix);

			float tlm[16] = { static_cast<float>(matrix.Get(0, 0)), static_cast<float>(matrix.Get(0, 1)), static_cast<float>(matrix.Get(0, 2)), static_cast<float>(matrix.Get(0, 3)), static_cast<float>(matrix.Get(1, 0)), static_cast<float>(matrix.Get(1, 1)), static_cast<float>(matrix.Get(1, 2)), static_cast<float>(matrix.Get(1, 3)), static_cast<float>(matrix.Get(2, 0)), static_cast<float>(matrix.Get(2, 1)), static_cast<float>(matrix.Get(2, 2)), static_cast<float>(matrix.Get(2, 3)), static_cast<float>(matrix.Get(3, 0)), static_cast<float>(matrix.Get(3, 1)), static_cast<float>(matrix.Get(3, 2)), static_cast<float>(matrix.Get(3, 3)) };

			Matrix4x4 transformLinkMatrix(tlm);

			//

			Matrix4x4 inverseTransformLinkMatrix = transformLinkMatrix;
			inverseTransformLinkMatrix.inverseRigidBody();

			nodeTreeFactory.setInverseBindMatrix(linkNode->GetName(), inverseTransformLinkMatrix * transformMatrix);
		}
	}

	currentMesh->addSkinningData(allBoneIndices0, allBoneIndices1, allBoneWeights0, allBoneWeights1, allBoneCounters);
}

void FbxEntityFactory::traverseDeleteUserPointer(FbxNode* node)
{
	FbxNodeAttribute::EType attributeType;

	if (node->GetNodeAttribute())
	{
		attributeType = node->GetNodeAttribute()->GetAttributeType();
	}
	else
	{
		attributeType = FbxNodeAttribute::eNull;
	}

	switch (attributeType)
	{
		case FbxNodeAttribute::eMesh:
		{
			FbxMesh* mesh = node->GetMesh();

			if (mesh && mesh->GetUserDataPtr())
			{
				uint32_t* indicesToOrgIndices = static_cast<uint32_t*>(mesh->GetUserDataPtr());

				delete[] indicesToOrgIndices;

				mesh->SetUserDataPtr(0);
			}
		}
		break;

		default:
			// Do nothing
		break;
	};

	for (int i = 0; i < node->GetChildCount(); i++)
	{
		traverseDeleteUserPointer(node->GetChild(i));
	}
}
