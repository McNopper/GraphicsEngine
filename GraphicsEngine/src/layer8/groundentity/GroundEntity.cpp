/*
 * GroundEntity.cpp
 *
 *  Created on: 13.05.2013
 *      Author: nopper
 */

#include "../../layer1/shader/Variables.h"
#include "../../layer2/debug/DebugDraw.h"
#include "../../layer2/environment/Sky.h"
#include "../../layer2/environment/SkyManager.h"

#include "GroundEntity.h"

using namespace std;

GroundEntity::GroundEntity(const string& name, const GroundSP& ground, const SurfaceMaterialSP& surfaceMaterial, float scaleX, float scaleY, float scaleZ) :
		GeneralEntity(name, scaleX, scaleY, scaleZ), repeat(1.0f), displacementScale(1.0f), transparent(false), tessellate(true), screenDistance(8.0f), ground(ground), surfaceMaterial(surfaceMaterial)
{
	float maxScale = glusMathMaxf(scaleX, scaleY);
	maxScale = glusMathMaxf(maxScale, scaleZ);

	setBoundingSphere(BoundingSphere(ground->getBoundingSphere().getCenter(), ground->getBoundingSphere().getRadius() * maxScale));

	setUpdateable(false);

	updateBoundingSphereCenter(true);
}

GroundEntity::~GroundEntity()
{
}

void GroundEntity::updateBoundingSphereCenter(bool force)
{
	setBoundingSphereCenter(getPosition());
}

void GroundEntity::update()
{
	// Nothing to do
}

void GroundEntity::render() const
{
	if (isWireframe())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	GroundVAOSP currentVAO = ground->getVAOByProgramType(GeneralEntity::currentProgramType);

	ProgramSP currentProgram = currentVAO->getProgram();

	// We process triangle patches
	glPatchParameteri(GL_PATCH_VERTICES, 3);

	currentProgram->use();

	currentVAO->bind();

	glUniformMatrix4fv(currentProgram->getUniformLocation(u_modelMatrix), 1, GL_FALSE, getModelMatrix().getM());

	// We have the inverse and transpose by setting the matrix
	glUniformMatrix3fv(currentProgram->getUniformLocation(u_normalModelMatrix), 1, GL_TRUE, getNormalModelMatrix().getM());

	glUniform4fv(currentProgram->getUniformLocation(u_emissiveColor), 1, surfaceMaterial->getEmissive().getRGBA());
	glUniform4fv(currentProgram->getUniformLocation(u_ambientColor), 1, surfaceMaterial->getAmbient().getRGBA());

	if (surfaceMaterial->getDiffuseTextureName() != 0)
	{
		glUniform1i(currentProgram->getUniformLocation(u_hasDiffuseTexture), 1);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, surfaceMaterial->getDiffuseTextureName());
		glUniform1i(currentProgram->getUniformLocation(u_diffuseTexture), 0);
	}
	else
	{
		glUniform1i(currentProgram->getUniformLocation(u_hasDiffuseTexture), 0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glUniform1i(currentProgram->getUniformLocation(u_diffuseTexture), 0);
	}
	glUniform4fv(currentProgram->getUniformLocation(u_diffuseColor), 1, surfaceMaterial->getDiffuse().getRGBA());

	if (surfaceMaterial->getSpecularTextureName() != 0)
	{
		glUniform1i(currentProgram->getUniformLocation(u_hasSpecularTexture), 1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, surfaceMaterial->getSpecularTextureName());
		glUniform1i(currentProgram->getUniformLocation(u_specularTexture), 1);
	}
	else
	{
		glUniform1i(currentProgram->getUniformLocation(u_hasSpecularTexture), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
		glUniform1i(currentProgram->getUniformLocation(u_specularTexture), 0);
	}
	glUniform4fv(currentProgram->getUniformLocation(u_specularColor), 1, surfaceMaterial->getSpecular().getRGBA());
	glUniform1f(currentProgram->getUniformLocation(u_shininess), surfaceMaterial->getShininess());

	glUniform1f(currentProgram->getUniformLocation(u_transparency), surfaceMaterial->getTransparency());

	if (surfaceMaterial->getDisplacementMapTextureName() != 0)
	{
		glUniform1i(currentProgram->getUniformLocation(u_hasNormalMapTexture), 1);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, surfaceMaterial->getDisplacementMapTextureName());
		glUniform1i(currentProgram->getUniformLocation(u_normalMapTexture), 2);
		glActiveTexture(GL_TEXTURE0);
	}
	else if (surfaceMaterial->getNormalMapTextureName() != 0)
	{
		glUniform1i(currentProgram->getUniformLocation(u_hasNormalMapTexture), 1);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, surfaceMaterial->getNormalMapTextureName());
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

	//

	glUniform1f(currentProgram->getUniformLocation(u_repeat), repeat);

	glUniform1f(currentProgram->getUniformLocation(u_screenDistance), screenDistance);
	glUniform1i(currentProgram->getUniformLocation(u_doTessellate), tessellate);

	const Viewport& currentViewport = currentCamera->getViewport();

	glUniform1f(currentProgram->getUniformLocation(u_width), static_cast<float>(currentViewport.getWidth()));
	glUniform1f(currentProgram->getUniformLocation(u_height), static_cast<float>(currentViewport.getHeight()));

	glUniform1f(currentProgram->getUniformLocation(u_displacementScale), displacementScale);

	glUniform1i(currentProgram->getUniformLocation(u_convertDirectX), surfaceMaterial->isConvertDirectX());

	//

	glUniform4fv(currentProgram->getUniformLocation(u_reflectionColor), 1, surfaceMaterial->getReflection().getRGBA());
	glUniform4fv(currentProgram->getUniformLocation(u_refractionColor), 1, surfaceMaterial->getRefraction().getRGBA());

	float environmentRefractiveIndex = refractiveIndex;

	if (environmentRefractiveIndex != RI_NOTHING)
	{
		float materialRefractiveIndex = surfaceMaterial->getRefractiveIndex();

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
	if (Entity::getDynamicCubeMaps() && surfaceMaterial->getDynamicCubeMapTextureName() != 0 && SkyManager::getInstance()->hasActiveSky())
	{
		glUniform1i(currentProgram->getUniformLocation(u_hasDynamicCubeMapTexture), 1);
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_CUBE_MAP, surfaceMaterial->getDynamicCubeMapTextureName());
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

	// No Skinning
	glUniform1i(currentProgram->getUniformLocation(u_hasSkinning), 0);

	glUniformMatrix4fv(currentProgram->getUniformLocation(u_bindMatrix), 0, GL_FALSE, Matrix4x4().getM());
	glUniformMatrix3fv(currentProgram->getUniformLocation(u_bindNormalMatrix), 0, GL_TRUE, Matrix3x3().getM());

	glUniformMatrix4fv(currentProgram->getUniformLocation(u_inverseBindMatrix), 0, GL_FALSE, Matrix4x4().getM());
	glUniformMatrix3fv(currentProgram->getUniformLocation(u_inverseBindNormalMatrix), 0, GL_TRUE, Matrix3x3().getM());

	// Write bright color
	glUniform1i(currentProgram->getUniformLocation(u_writeBrightColor), writeBrightColor);
	glUniform1f(currentProgram->getUniformLocation(u_brightColorLimit), brightColorLimit);

	if (transparent)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	glDrawElements(GL_PATCHES, ground->getNumberIndices(), GL_UNSIGNED_INT, 0);

	if (transparent)
	{
		glDisable(GL_BLEND);
	}

	if (surfaceMaterial->getDiffuseTextureName() != 0)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if (surfaceMaterial->getSpecularTextureName() != 0)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if (surfaceMaterial->getDisplacementMapTextureName() != 0 || surfaceMaterial->getNormalMapTextureName() != 0)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if (SkyManager::getInstance()->hasActiveSky())
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	if (surfaceMaterial->getDynamicCubeMapTexture() != 0)
	{
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	glActiveTexture(GL_TEXTURE0);

	currentVAO->unbind();

	//

	if (isWireframe())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	//

	if (isDebug())
	{
		DebugDraw::drawer.draw(getBoundingSphere(), Color::RED, isDebugAsMesh());
	}
}

const SurfaceMaterialSP& GroundEntity::getSurfaceMaterial() const
{
	return surfaceMaterial;
}

void GroundEntity::setSurfaceMaterial(const SurfaceMaterialSP& surfaceMaterial)
{
	this->surfaceMaterial = surfaceMaterial;
}

float GroundEntity::getRepeat() const
{
	return repeat;
}

void GroundEntity::setRepeat(float repeat)
{
	this->repeat = repeat;
}

float GroundEntity::getDisplacementScale() const
{
	return displacementScale;
}

void GroundEntity::setDisplacementScale(float displacementScale)
{
	this->displacementScale = displacementScale;
}

bool GroundEntity::isTransparent() const
{
	return transparent;
}

void GroundEntity::setTransparent(bool transparent)
{
	this->transparent = transparent;
}

bool GroundEntity::isTessellate() const
{
	return tessellate;
}

void GroundEntity::setTessellate(bool tessellate)
{
	this->tessellate = tessellate;
}

float GroundEntity::getScreenDistance() const
{
	return screenDistance;
}

void GroundEntity::setScreenDistance(float screenDistance)
{
	this->screenDistance = screenDistance;
}
