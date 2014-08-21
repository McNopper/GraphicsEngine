/*
 * ModelEntity.cpp
 *
 *  Created on: 22.04.2011
 *      Author: Norbert Nopper
 */


#include "../../layer1/shader/ProgramManager.h"
#include "../../layer1/event/EventManager.h"
#include "../../layer2/debug/DebugDraw.h"
#include "../../layer2/environment/SkyManager.h"
#include "../../layer2/material/RefractiveIndices.h"
#include "../../layer3/camera/CameraManager.h"
#include "../../layer3/light/LightManager.h"
#include "../../layer4/shader/ProgramManagerProxy.h"

#include "ModelEntity.h"

using namespace std;

const string& ModelEntity::getCurrentProgramType() const
{
	return GeneralEntity::currentProgramType;
}

int32_t ModelEntity::getNumberJoints() const
{
	return model->getNumberJoints();
}

ModelEntity::ModelEntity(const string& name, const ModelSP& model, float scaleX, float scaleY, float scaleZ) :
		GeneralEntity(name, scaleX, scaleY, scaleZ), NodeOwner(), model(model), time(0.0f), animStackIndex(-1), animLayerIndex(-1), rootInstanceNode(), jointIndex(-1), dirty(true), ambientLightColor()
{
	float maxScale = glusMathMaxf(scaleX, scaleY);
	maxScale = glusMathMaxf(maxScale, scaleZ);

	setBoundingSphere(BoundingSphere(model->getBoundingSphere().getCenter(), model->getBoundingSphere().getRadius() * maxScale));

	setUpdateable(model->isAnimated());

	if (model->isSkinned())
	{
		jointIndex = model->getRootNode()->getRootJointIndex();

		model->getRootNode()->updateInverseBindMatrix(inverseBindMatrices, inverseBindNormalMatrices);
		model->getRootNode()->updateBindMatrix(bindMatrices, bindNormalMatrices, Matrix4x4(), 0.0f, animStackIndex, animLayerIndex);
	}
	rootInstanceNode = InstanceNodeSP(new InstanceNode(model->getRootNode().get()));
	model->getRootNode()->updateInstanceNode(*this, rootInstanceNode);

	updateBoundingSphereCenter(true);
}

ModelEntity::~ModelEntity()
{
}

void ModelEntity::setAnimation(int32_t animStackIndex, int32_t animLayerIndex)
{
	this->animStackIndex = animStackIndex;
	this->animLayerIndex = animLayerIndex;
}

void ModelEntity::updateBoundingSphereCenter(bool force)
{
	bool doUpdateBoundingSphereCenter = force;

	if (model->isAnimated())
	{
		doUpdateBoundingSphereCenter = true;
	}

	if (doUpdateBoundingSphereCenter)
	{
		Matrix4x4 skinningMatrix;
		if (model->isSkinned())
		{
			skinningMatrix = bindMatrices[jointIndex] * inverseBindMatrices[jointIndex];
		}

		Matrix4x4 renderingMatrix;
		model->getRootNode()->updateBoundingSphereMatrix(renderingMatrix, getModelMatrix(), time, animStackIndex, animLayerIndex);

		Point4 center = renderingMatrix * skinningMatrix * Point4();

		setBoundingSphereCenter(center);
	}
}

void ModelEntity::update()
{
	if (model->isAnimated())
	{
		time += ModelEntity::currentDeltaTime;

		float stopTime = model->getRootNode()->getStopTime(animStackIndex, animLayerIndex);
		if (time > stopTime)
		{
			time -= stopTime;
		}

		// Calculate skinning and pass later to shader
		if (model->isSkinned() && animStackIndex >= 0 && animLayerIndex >= 0)
		{
			model->getRootNode()->updateBindMatrix(bindMatrices, bindNormalMatrices, Matrix4x4(), time, animStackIndex, animLayerIndex);
		}

		dirty = true;
	}

	if (dirty)
	{
		model->getRootNode()->updateRenderMatrix(*this, *rootInstanceNode, getModelMatrix(), time, animStackIndex, animLayerIndex);

		dirty = false;
	}
}

void ModelEntity::render() const
{
	model->getRootNode()->render(*this, *rootInstanceNode, time, animStackIndex, animLayerIndex);

	if (isDebug())
	{
		DebugDraw::drawer.draw(getBoundingSphere(), Color::RED, isDebugAsMesh());
	}
}

const ModelSP& ModelEntity::getModel() const
{
	return model;
}

const InstanceNodeSP& ModelEntity::getRootInstanceNode() const
{
	return rootInstanceNode;
}

InstanceNodeSP ModelEntity::findInstanceNodeRecursive(const string& name) const
{
	return rootInstanceNode->findChildRecursive(name);
}

ModelEntitySP ModelEntity::getNewInstance(const string& name) const
{
	return ModelEntitySP(new ModelEntity(name, model, getScaleX(), getScaleY(), getScaleZ()));
}

void ModelEntity::renderNode(const Node& node, const InstanceNode& instanceNode, float time, int32_t animStackIndex, int32_t animLayerIndex) const
{
	enum RenderFilter renderFilter = Entity::getRenderFilter();
	bool finalTransparent = (instanceNode.isTransparentActive() && instanceNode.isTransparent()) || (!instanceNode.isTransparentActive() && node.isTransparent());
	bool renderMesh = (renderFilter == RENDER_ALL) || (finalTransparent && renderFilter == RENDER_TRANSPARENT) || (!finalTransparent && renderFilter == RENDER_OPAQUE);

	if (isDebug())
	{
		if (node.getCamera().get())
		{
			node.getCamera()->debugDraw(instanceNode.getPosition(), instanceNode.getRotation(), true);
		}

		if (node.getLight().get())
		{
			node.getLight()->debugDraw(instanceNode.getPosition(), instanceNode.getRotation());
		}
	}

	if (isWireframe())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (node.getMesh().get() && renderMesh)
	{
		VAOSP currentVAO;
		ProgramSP currentProgram;
		SubMeshSP currentSubMesh;
		SurfaceMaterialSP currentSurfaceMaterial;

		const std::vector<std::shared_ptr<AnimationStack> >& allAnimStacks = node.getAllAnimStacks();

		for (uint32_t subMeshIndex = 0; subMeshIndex < node.getMesh()->getSubMeshesCount(); subMeshIndex++)
		{
			currentSubMesh = node.getMesh()->getSubMeshAt(subMeshIndex);

			if (subMeshIndex >= node.getMesh()->getSurfaceMaterialsCount())
			{
				break;
			}

			currentSurfaceMaterial = node.getMesh()->getSurfaceMaterialAt(subMeshIndex);

			float currentEmissive[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
			float currentAmbient[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
			float currentDiffuse[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
			float currentSpecular[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
			float currentReflection[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
			float currentRefraction[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
			float currentShininess = 0.0f;
			float currentTransparency = 0.0f;

			for (int32_t i = 0; i < 4; i++)
			{
				currentEmissive[i] = currentSurfaceMaterial->getEmissive().getRGBA()[i];
				currentAmbient[i] = currentSurfaceMaterial->getAmbient().getRGBA()[i];
				currentDiffuse[i] = currentSurfaceMaterial->getDiffuse().getRGBA()[i];
				currentSpecular[i] = currentSurfaceMaterial->getSpecular().getRGBA()[i];
				currentReflection[i] = currentSurfaceMaterial->getReflection().getRGBA()[i];
				currentRefraction[i] = currentSurfaceMaterial->getRefraction().getRGBA()[i];
			}
			currentShininess = currentSurfaceMaterial->getShininess();
			currentTransparency = currentSurfaceMaterial->getTransparency();

			if (animStackIndex >= 0 && animLayerIndex >= 0 && static_cast<decltype(allAnimStacks.size())>(animStackIndex) < allAnimStacks.size() && animLayerIndex < allAnimStacks[animStackIndex]->getAnimationLayersCount())
			{
				// Animate values depending on time
				const AnimationLayerSP& animLayer = allAnimStacks[animStackIndex]->getAnimationLayer(animLayerIndex);

				for (enum AnimationLayer::eCHANNELS_RGBA i = AnimationLayer::R; i <= AnimationLayer::A;
						i = static_cast<enum AnimationLayer::eCHANNELS_RGBA>(i + 1))
				{
					if (animLayer->hasEmissiveColorValue(i))
					{
						currentEmissive[i] = animLayer->getEmissiveColorValue(i, time);
					}
					if (animLayer->hasAmbientColorValue(i))
					{
						currentAmbient[i] = animLayer->getAmbientColorValue(i, time);
					}
					if (animLayer->hasDiffuseColorValue(i))
					{
						currentDiffuse[i] = animLayer->getDiffuseColorValue(i, time);
					}
					if (animLayer->hasSpecularColorValue(i))
					{
						currentSpecular[i] = animLayer->getSpecularColorValue(i, time);
					}
					if (animLayer->hasReflectionColorValue(i))
					{
						currentReflection[i] = animLayer->getReflectionColorValue(i, time);
					}
					if (animLayer->hasRefractionColorValue(i))
					{
						currentRefraction[i] = animLayer->getRefractionColorValue(i, time);
					}
				}

				if (animLayer->hasShininessValue(AnimationLayer::S))
				{
					currentShininess = animLayer->getShininessValue(AnimationLayer::S, time);
				}
				if (animLayer->hasTransparencyValue(AnimationLayer::S))
				{
					currentTransparency = animLayer->getTransparencyValue(AnimationLayer::S, time);
				}
			}

			currentVAO = currentSubMesh->getVAOByProgramType(getCurrentProgramType());

			currentProgram = currentVAO->getProgram();

			currentProgram->use();

			glUniformMatrix4fv(currentProgram->getUniformLocation(u_modelMatrix), 1, GL_FALSE, instanceNode.getModelMatrix().getM());

			// We have the inverse and transpose by setting the matrix
			glUniformMatrix3fv(currentProgram->getUniformLocation(u_normalModelMatrix), 1, GL_TRUE, instanceNode.getNormalModelMatrix().getM());

			currentVAO->bind();

			glUniform4fv(currentProgram->getUniformLocation(u_emissiveColor), 1, currentEmissive);
			glUniform4fv(currentProgram->getUniformLocation(u_ambientColor), 1, currentAmbient);

			if (currentSurfaceMaterial->getDiffuseTextureName() != 0)
			{
				glUniform1i(currentProgram->getUniformLocation(u_hasDiffuseTexture), 1);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, currentSurfaceMaterial->getDiffuseTextureName());
				glUniform1i(currentProgram->getUniformLocation(u_diffuseTexture), 0);
			}
			else
			{
				glUniform1i(currentProgram->getUniformLocation(u_hasDiffuseTexture), 0);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, 0);
				glUniform1i(currentProgram->getUniformLocation(u_diffuseTexture), 0);
			}
			glUniform4fv(currentProgram->getUniformLocation(u_diffuseColor), 1, currentDiffuse);

			if (currentSurfaceMaterial->getSpecularTextureName() != 0)
			{
				glUniform1i(currentProgram->getUniformLocation(u_hasSpecularTexture), 1);

				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, currentSurfaceMaterial->getSpecularTextureName());
				glUniform1i(currentProgram->getUniformLocation(u_specularTexture), 1);
			}
			else
			{
				glUniform1i(currentProgram->getUniformLocation(u_hasSpecularTexture), 0);

				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, 0);
				glUniform1i(currentProgram->getUniformLocation(u_specularTexture), 0);
			}
			glUniform4fv(currentProgram->getUniformLocation(u_specularColor), 1, currentSpecular);
			glUniform1f(currentProgram->getUniformLocation(u_shininess), currentShininess);

			glUniform1f(currentProgram->getUniformLocation(u_transparency), currentTransparency);

			if (currentSurfaceMaterial->getNormalMapTextureName() != 0)
			{
				glUniform1i(currentProgram->getUniformLocation(u_hasNormalMapTexture), 1);

				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_2D, currentSurfaceMaterial->getNormalMapTextureName());
				glUniform1i(currentProgram->getUniformLocation(u_normalMapTexture), 2);
				glActiveTexture(GL_TEXTURE0);
			}
			else
			{
				glUniform1i(currentProgram->getUniformLocation(u_hasNormalMapTexture), 0);

				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_2D, 0);
				glUniform1i(currentProgram->getUniformLocation(u_normalMapTexture), 2);
				glActiveTexture(GL_TEXTURE0);
			}

			glUniform1i(currentProgram->getUniformLocation(u_convertDirectX), currentSurfaceMaterial->isConvertDirectX());

			glUniform4fv(currentProgram->getUniformLocation(u_reflectionColor), 1, currentReflection);
			glUniform4fv(currentProgram->getUniformLocation(u_refractionColor), 1, currentRefraction);

			float environmentRefractiveIndex = refractiveIndex;

			if (environmentRefractiveIndex != RI_NOTHING)
			{
				float materialRefractiveIndex = currentSurfaceMaterial->getRefractiveIndex();

				float eta = environmentRefractiveIndex / materialRefractiveIndex;

				float reflectanceNormalIncidence = ((environmentRefractiveIndex - materialRefractiveIndex) * (environmentRefractiveIndex - materialRefractiveIndex)) / ((environmentRefractiveIndex + materialRefractiveIndex) * (environmentRefractiveIndex + materialRefractiveIndex));

				glUniform1f(currentProgram->getUniformLocation(u_eta), eta);
				glUniform1f(currentProgram->getUniformLocation(u_reflectanceNormalIncidence), reflectanceNormalIncidence);
			}
			else
			{
				glUniform1f(currentProgram->getUniformLocation(u_eta), 0.0f);
				glUniform1f(currentProgram->getUniformLocation(u_reflectanceNormalIncidence), 0.0f);
			}

			if (SkyManager::getInstance()->hasActiveSky())
			{
				glUniform1i(currentProgram->getUniformLocation(u_hasCubeMapTexture), 1);

				SkySP activeSky = SkyManager::getInstance()->getActiveSky();

				glActiveTexture(GL_TEXTURE3);
				glBindTexture(GL_TEXTURE_CUBE_MAP, activeSky->getSkyTextureName());
				glUniform1i(currentProgram->getUniformLocation(u_cubemap), 3);
				glActiveTexture(GL_TEXTURE0);
			}
			else
			{
				glUniform1i(currentProgram->getUniformLocation(u_hasCubeMapTexture), 0);

				glActiveTexture(GL_TEXTURE3);
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
				glUniform1i(currentProgram->getUniformLocation(u_cubemap), 3);
				glActiveTexture(GL_TEXTURE0);
			}

			// Only allow dynamic cube map, if also a sky cube map is available
			if (Entity::getDynamicCubeMaps() && currentSurfaceMaterial->getDynamicCubeMapTextureName() != 0 && SkyManager::getInstance()->hasActiveSky())
			{
				glUniform1i(currentProgram->getUniformLocation(u_hasDynamicCubeMapTexture), 1);
				glActiveTexture(GL_TEXTURE4);
				glBindTexture(GL_TEXTURE_CUBE_MAP, currentSurfaceMaterial->getDynamicCubeMapTextureName());
				glUniform1i(currentProgram->getUniformLocation(u_dynamicCubeMapTexture), 4);
				glActiveTexture(GL_TEXTURE0);
			}
			else
			{
				glUniform1i(currentProgram->getUniformLocation(u_hasDynamicCubeMapTexture), 0);
				glActiveTexture(GL_TEXTURE4);
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
				glUniform1i(currentProgram->getUniformLocation(u_dynamicCubeMapTexture), 4);
				glActiveTexture(GL_TEXTURE0);
			}

			if (!Entity::getDynamicCubeMaps())
			{
				glUniformMatrix4fv(currentProgram->getUniformLocation(u_cubeMapViewMatrix), 6, GL_FALSE, Entity::getCubeMapViewMatrices()[0].getM());
				glUniformMatrix4fv(currentProgram->getUniformLocation(u_cubeMapProjectionMatrix), 1, GL_FALSE, Entity::getCubeMapProjectionMatrix().getM());
			}

			// Skinning
			if (node.getMesh()->hasSkinning())
			{
				glUniform1i(currentProgram->getUniformLocation(u_hasSkinning), 1);

				glUniformMatrix4fv(currentProgram->getUniformLocation(u_bindMatrix), model->getNumberJoints(), GL_FALSE, bindMatrices[0].getM());
				glUniformMatrix3fv(currentProgram->getUniformLocation(u_bindNormalMatrix), model->getNumberJoints(), GL_TRUE, bindNormalMatrices[0].getM());

				glUniformMatrix4fv(currentProgram->getUniformLocation(u_inverseBindMatrix), model->getNumberJoints(), GL_FALSE, inverseBindMatrices[0].getM());
				glUniformMatrix3fv(currentProgram->getUniformLocation(u_inverseBindNormalMatrix), model->getNumberJoints(), GL_TRUE, inverseBindNormalMatrices[0].getM());
			}
			else
			{
				glUniform1i(currentProgram->getUniformLocation(u_hasSkinning), 0);

				glUniformMatrix4fv(currentProgram->getUniformLocation(u_bindMatrix), model->getNumberJoints(), GL_FALSE, Matrix4x4().getM());
				glUniformMatrix3fv(currentProgram->getUniformLocation(u_bindNormalMatrix), model->getNumberJoints(), GL_TRUE, Matrix3x3().getM());

				glUniformMatrix4fv(currentProgram->getUniformLocation(u_inverseBindMatrix), model->getNumberJoints(), GL_FALSE, Matrix4x4().getM());
				glUniformMatrix3fv(currentProgram->getUniformLocation(u_inverseBindNormalMatrix), model->getNumberJoints(), GL_TRUE, Matrix3x3().getM());
			}

			// Write bright color
			glUniform1i(currentProgram->getUniformLocation(u_writeBrightColor), writeBrightColor);
			glUniform1f(currentProgram->getUniformLocation(u_brightColorLimit), brightColorLimit);

			if (finalTransparent)
			{
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}

			glDrawElements(GL_TRIANGLES, currentSubMesh->getTriangleCount() * 3, GL_UNSIGNED_INT, reinterpret_cast<const GLvoid *>(currentSubMesh->getIndicesOffset() * sizeof(uint32_t)));

			if (finalTransparent)
			{
				glDisable(GL_BLEND);
			}

			if (currentSurfaceMaterial->getDiffuseTextureName() != 0)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, 0);
			}

			if (currentSurfaceMaterial->getSpecularTextureName() != 0)
			{
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, 0);
			}

			if (currentSurfaceMaterial->getNormalMapTextureName() != 0)
			{
				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_2D, 0);
			}

			if (SkyManager::getInstance()->hasActiveSky())
			{
				glActiveTexture(GL_TEXTURE3);
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
			}

			if (currentSurfaceMaterial->getDynamicCubeMapTexture() != 0)
			{
				glActiveTexture(GL_TEXTURE4);
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
			}

			glActiveTexture(GL_TEXTURE0);

			currentVAO->unbind();
		}
	}

	if (isWireframe())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void ModelEntity::addLightNode(const InstanceNodeSP& lightNode)
{
	allLights.push_back(lightNode);
}

void ModelEntity::addCameraNode(const InstanceNodeSP& cameraNode)
{
	allCameras.push_back(cameraNode);
}

int32_t ModelEntity::setLights(int32_t lightNumber) const
{
	auto walker = allLights.begin();

	InstanceNodeSP instanceNode;

	while (walker != allLights.end())
	{
		instanceNode = *walker;

		ProgramManagerProxy::setLightByType(GeneralEntity::currentProgramType, lightNumber, instanceNode->getNode()->getLight(), instanceNode->getPosition(), instanceNode->getRotation());

		lightNumber++;
		walker++;
	}

	return lightNumber;
}

CameraSP ModelEntity::getCamera(const std::string& name) const
{
	auto walker = allCameras.begin();

	InstanceNodeSP instanceNode;

	while (walker != allCameras.end())
	{
		instanceNode = *walker;

		if (instanceNode->getNode()->getName().compare(name) == 0)
		{
			return instanceNode->getNode()->getCamera();
		}

		walker++;
	}

	return CameraSP();
}

bool ModelEntity::setCamera(const string& name) const
{
	auto walker = allCameras.begin();

	InstanceNodeSP instanceNode;

	while (walker != allCameras.end())
	{
		instanceNode = *walker;

		if (instanceNode->getNode()->getName().compare(name) == 0)
		{
			ProgramManagerProxy::setCameraByType(GeneralEntity::currentProgramType, instanceNode->getNode()->getCamera(), instanceNode->getPosition(), instanceNode->getRotation(), true);

			return true;
		}

		walker++;
	}

	return false;
}

bool ModelEntity::setOrthographicCameraShadowMap(const string& lightName, const OrthographicCameraShadowMap2DSP& orthographicCameraShadowMap2D) const
{
	Quaternion baseRotation(-90.0f, Vector3(1.0f, 0.0f, 0.0f));

	baseRotation *= Quaternion(90.0f, Vector3(0.0f, 1.0f, 0.0f));

	auto walker = allLights.begin();

	InstanceNodeSP instanceNode;

	while (walker != allLights.end())
	{
		instanceNode = *walker;

		if (instanceNode->getNode()->getName().compare(lightName) == 0)
		{
			ProgramManagerProxy::setCameraByType(GeneralEntity::currentProgramType, orthographicCameraShadowMap2D->getOrthographicCamera(), instanceNode->getPosition(), instanceNode->getRotation() * baseRotation, true);

			return true;
		}

		walker++;
	}

	return false;
}

bool ModelEntity::setOrthographicCameraCascadedShadowMap(const string& lightName, const CameraSP& camera, const OrthographicCameraCascadedShadowMap2DSP& orthographicCameraCascadedShadowMap2D, int32_t section) const
{
	Quaternion baseRotation(-90.0f, Vector3(1.0f, 0.0f, 0.0f));

	baseRotation *= Quaternion(90.0f, Vector3(0.0f, 1.0f, 0.0f));

	auto walker = allLights.begin();

	InstanceNodeSP instanceNode;

	while (walker != allLights.end())
	{
		instanceNode = *walker;

		if (instanceNode->getNode()->getName().compare(lightName) == 0)
		{
			orthographicCameraCascadedShadowMap2D->getOrthographicCamera(section)->adjustToFrustum(camera->getViewFrustum(), section, instanceNode->getPosition(), instanceNode->getRotation() * baseRotation);

			ProgramManagerProxy::setCameraByType(GeneralEntity::currentProgramType, orthographicCameraCascadedShadowMap2D->getOrthographicCamera(section), Point4(), Quaternion(), false);

			return true;
		}

		walker++;
	}

	return false;
}

void ModelEntity::passCamerasToManager() const
{
	auto walker = allCameras.begin();

	InstanceNodeSP instanceNode;

	while (walker != allCameras.end())
	{
		instanceNode = *walker;

		CameraManager::getInstance()->setCamera(instanceNode->getNode()->getCamera()->getName(), instanceNode->getNode()->getCamera(), true);

		walker++;
	}
}

void ModelEntity::passLightsToManager() const
{
	auto walker = allLights.begin();

	InstanceNodeSP instanceNode;

	while (walker != allLights.end())
	{
		instanceNode = *walker;

		LightManager::getInstance()->setLight(instanceNode->getNode()->getLight()->getName(), instanceNode->getNode()->getLight());

		walker++;
	}

	LightManager::getInstance()->setAmbientLightColor(ambientLightColor);
}

const Color& ModelEntity::getAmbientLightColor() const
{
	return ambientLightColor;
}

void ModelEntity::setAmbientLightColor(const Color& ambientLightColor)
{
	this->ambientLightColor = ambientLightColor;
}

const Matrix4x4& ModelEntity::getInverseBindMatrix(int32_t index) const
{
	return inverseBindMatrices[index];
}

const Matrix3x3& ModelEntity::getInverseBindNormalMatrix(int32_t index) const
{
	return inverseBindNormalMatrices[index];
}
