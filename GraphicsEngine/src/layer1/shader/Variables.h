/*
 * Variables.h
 *
 *  Created on: 08.05.2012
 *      Author: nopper
 */

#ifndef VARIABLES_H_
#define VARIABLES_H_

#define MAX_LIGHT_SECTIONS 3

#define u_projectionMatrix "u_projectionMatrix"
#define u_viewMatrix "u_viewMatrix"
#define u_modelMatrix "u_modelMatrix"
#define u_normalModelViewMatrix "u_normalModelViewMatrix"
#define u_normalModelMatrix "u_normalModelMatrix"

#define u_cubeMapProjectionMatrix "u_cubeMapProjectionMatrix"
#define u_cubeMapViewMatrix "u_cubeMapViewMatrix"

#define u_eyePosition "u_eyePosition"

#define u_ambientLightColor "u_ambientLightColor"

#define u_numberLights "u_numberLights"
#define u_light "u_light["
#define u_lightType "].lightType"
#define u_diffuseLightColor "].diffuseColor"
#define u_specularLightColor "].specularColor"
#define u_lightDirection "].direction"
#define u_lightPosition "].position"
#define u_lightConstantAttenuation "].constantAttenuation"
#define u_lightLinearAttenuation "].linearAttenuation"
#define u_lightQuadraticAttenuation "].quadraticAttenuation"
#define u_lightSpotDirection "].spotDirection"
#define u_lightSpotCosCutOff "].spotCosCutOff"
#define u_lightSpotCosCutOffOuter "].spotCosCutOffOuter"

#define u_emissiveColor "u_material.emissiveColor"
#define u_ambientColor "u_material.ambientColor"
#define u_diffuseColor "u_material.diffuseColor"
#define u_diffuseTexture "u_material.diffuseTexture"
#define u_specularColor "u_material.specularColor"
#define u_specularTexture "u_material.specularTexture"
#define u_shininess "u_material.shininess"
#define u_normalMapTexture "u_material.normalMapTexture"
#define u_reflectionColor "u_material.reflectionColor"
#define u_refractionColor "u_material.refractionColor"
#define u_transparency "u_material.transparency"
#define u_dynamicCubeMapTexture "u_material.dynamicCubeMapTexture"

#define u_hasSkinning "u_hasSkinning"
#define u_hasDiffuseTexture "u_hasDiffuseTexture"
#define u_hasSpecularTexture "u_hasSpecularTexture"
#define u_hasNormalMapTexture "u_hasNormalMapTexture"
#define u_hasCubeMapTexture "u_hasCubeMapTexture"
#define u_hasDynamicCubeMapTexture "u_hasDynamicCubeMapTexture"

#define u_convertDirectX "u_convertDirectX"
#define u_doTessellate "u_doTessellate"
#define u_repeat "u_repeat"
#define u_displacementScale "u_displacementScale"
#define u_width "u_width"
#define u_height "u_height"
#define u_screenDistance "u_screenDistance"

#define u_writeBrightColor "u_writeBrightColor"
#define u_brightColorLimit "u_brightColorLimit"

#define u_inverseBindMatrix "u_inverseBindMatrix"
#define u_inverseBindNormalMatrix "u_inverseBindNormalMatrix"
#define u_bindMatrix "u_bindMatrix"
#define u_bindNormalMatrix "u_bindNormalMatrix"

#define u_fontLeft "u_fontLeft"
#define u_fontTop "u_fontTop"
#define u_fontWidth "u_fontWidth"
#define u_fontHeight "u_fontHeight"
#define u_fontTexture "u_fontTexture"
#define u_fontColor "u_fontColor"

#define u_numberSamples "u_numberSamples"

#define u_useMS "u_useMS"

#define u_screenTexture "u_screenTexture"
#define u_screenTextureMS "u_screenTextureMS"
#define u_depthTexture "u_depthTexture"
#define u_depthTextureMS "u_depthTextureMS"
#define u_bloomTexture "u_bloomTexture"
#define u_bloomTextureMS "u_bloomTextureMS"
#define u_blurTexture "u_blurTexture"

#define u_useDoF "u_useDoF"
#define u_aperture "u_aperture"
#define u_focal "u_focal"
#define u_focusedObject "u_focusedObject"

#define u_useBlur "u_useBlur"
#define u_blurHorizontal "u_blurHorizontal"
#define u_blurVertical "u_blurVertical"
#define u_useBloom "u_useBloom"
#define u_bloomLevel "u_bloomLevel"
#define u_useGamma "u_useGamma"
#define u_gamma "u_gamma"
#define u_useExposure "u_useExposure"
#define u_exposure "u_exposure"

#define u_lineGeometryColor "u_lineGeometryColor"
#define u_lineGeometryOffset0 "u_lineGeometryOffset0"
#define u_lineGeometryOffset1 "u_lineGeometryOffset1"

#define u_cubemap "u_cubemap"

#define u_shadowType "u_shadowType["
#define u_shadowTexture "u_shadowTexture["
#define u_shadowSections "u_shadowSections["
#define u_shadowMatrix "u_shadowMatrix["
#define u_frustumZs "u_frustumZs"

#define u_eta "u_eta"
#define u_reflectanceNormalIncidence "u_reflectanceNormalIncidence"

#define a_vertex "a_vertex"
#define a_normal "a_normal"
#define a_tangent "a_tangent"
#define a_bitangent "a_bitangent"
#define a_texCoord "a_texCoord"

#define a_boneIndex_0 "a_boneIndex_0"
#define a_boneIndex_1 "a_boneIndex_1"
#define a_boneWeight_0 "a_boneWeight_0"
#define a_boneWeight_1 "a_boneWeight_1"
#define a_boneCounter "a_boneCounter"

#endif /* VARIABLES_H_ */
