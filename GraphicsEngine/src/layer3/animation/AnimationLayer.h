/*
 * AnimationLayer.h
 *
 *  Created on: 16.07.2012
 *      Author: nopper
 */

#ifndef ANIMATIONLAYER_H_
#define ANIMATIONLAYER_H_

#include "../../UsedLibs.h"

#include "../../layer2/interpolation/Interpolator.h"

class AnimationLayer
{

public:

	enum eCHANNELS_XYZ {X = 0, Y = 1, Z = 2};
	enum eCHANNELS_RGBA {R = 0, G = 1, B = 2, A = 3};
	enum eCHANNELS_SCALAR {S = 0};

private:

	std::map<float, float> allTranslationValues[3];
	std::map<float, const Interpolator*> allTranslationInterpolators[3];

	std::map<float, float> allRotationValues[3];
	std::map<float, const Interpolator*> allRotationInterpolators[3];

	std::map<float, float> allScalingValues[3];
	std::map<float, const Interpolator*> allScalingInterpolators[3];

	std::map<float, float> allEmissiveColorValues[4];
	std::map<float, const Interpolator*> allEmissiveColorInterpolators[4];

	std::map<float, float> allAmbientColorValues[4];
	std::map<float, const Interpolator*> allAmbientColorInterpolators[4];

	std::map<float, float> allDiffuseColorValues[4];
	std::map<float, const Interpolator*> allDiffuseColorInterpolators[4];

	std::map<float, float> allSpecularColorValues[4];
	std::map<float, const Interpolator*> allSpecularColorInterpolators[4];

	std::map<float, float> allReflectionColorValues[4];
	std::map<float, const Interpolator*> allReflectionColorInterpolators[4];

	std::map<float, float> allRefractionColorValues[4];
	std::map<float, const Interpolator*> allRefractionColorInterpolators[4];

	std::map<float, float> allShininessValues[1];
	std::map<float, const Interpolator*> allShininessInterpolators[1];

	std::map<float, float> allTransparencyValues[1];
	std::map<float, const Interpolator*> allTransparencyInterpolators[1];

	float getInterpolatedValue(const std::map<float, float>& currentTableValues, const std::map<float, const Interpolator*>& currentTableInterpolators, float time, float defaultValue = 0.0f) const;

public:

	AnimationLayer();
	virtual ~AnimationLayer();

	void addTranslationValue(enum eCHANNELS_XYZ channel, float time, float value, const Interpolator& interpolator);
	void addRotationValue(enum eCHANNELS_XYZ channel, float time, float value, const Interpolator& interpolator);
	void addScalingValue(enum eCHANNELS_XYZ channel, float time, float value, const Interpolator& interpolator);
	void addEmissiveColorValue(enum eCHANNELS_RGBA channel, float time, float value, const Interpolator& interpolator);
	void addAmbientColorValue(enum eCHANNELS_RGBA channel, float time, float value, const Interpolator& interpolator);
	void addDiffuseColorValue(enum eCHANNELS_RGBA channel, float time, float value, const Interpolator& interpolator);
	void addSpecularColorValue(enum eCHANNELS_RGBA channel, float time, float value, const Interpolator& interpolator);
	void addReflectionColorValue(enum eCHANNELS_RGBA channel, float time, float value, const Interpolator& interpolator);
	void addRefractionColorValue(enum eCHANNELS_RGBA channel, float time, float value, const Interpolator& interpolator);
	void addShininessValue(enum eCHANNELS_SCALAR channel, float time, float value, const Interpolator& interpolator);
	void addTransparencyValue(enum eCHANNELS_SCALAR channel, float time, float value, const Interpolator& interpolator);

	bool hasTranslationValue(enum eCHANNELS_XYZ channel) const;
	bool hasRotationValue(enum eCHANNELS_XYZ channel) const;
	bool hasScalingValue(enum eCHANNELS_XYZ channel) const;
	bool hasEmissiveColorValue(enum eCHANNELS_RGBA channel) const;
	bool hasAmbientColorValue(enum eCHANNELS_RGBA channel) const;
	bool hasDiffuseColorValue(enum eCHANNELS_RGBA channel) const;
	bool hasSpecularColorValue(enum eCHANNELS_RGBA channel) const;
	bool hasReflectionColorValue(enum eCHANNELS_RGBA channel) const;
	bool hasRefractionColorValue(enum eCHANNELS_RGBA channel) const;
	bool hasShininessValue(enum eCHANNELS_SCALAR channel) const;
	bool hasTransparencyValue(enum eCHANNELS_SCALAR channel) const;

	float getTranslationValue(enum eCHANNELS_XYZ channel, float time) const;
	float getRotationValue(enum eCHANNELS_XYZ channel, float time) const;
	float getScalingValue(enum eCHANNELS_XYZ channel, float time) const;
	float getEmissiveColorValue(enum eCHANNELS_RGBA channel, float time) const;
	float getAmbientColorValue(enum eCHANNELS_RGBA channel, float time) const;
	float getDiffuseColorValue(enum eCHANNELS_RGBA channel, float time) const;
	float getSpecularColorValue(enum eCHANNELS_RGBA channel, float time) const;
	float getReflectionColorValue(enum eCHANNELS_RGBA channel, float time) const;
	float getRefractionColorValue(enum eCHANNELS_RGBA channel, float time) const;
	float getShininessValue(enum eCHANNELS_SCALAR channel, float time) const;
	float getTransparencyValue(enum eCHANNELS_SCALAR channel, float time) const;

	const std::map<float, float>& getAllTranslationValues(enum eCHANNELS_XYZ channel) const;
	const std::map<float, float>& getAllRotationValues(enum eCHANNELS_XYZ channel) const;
	const std::map<float, float>& getAllScalingValues(enum eCHANNELS_XYZ channel) const;

	const std::map<float, const Interpolator*>& getAllTranslationInterpolators(enum eCHANNELS_XYZ channel) const;
	const std::map<float, const Interpolator*>& getAllRotationInterpolators(enum eCHANNELS_XYZ channel) const;
	const std::map<float, const Interpolator*>& getAllScalingInterpolators(enum eCHANNELS_XYZ channel) const;

};

typedef std::shared_ptr<AnimationLayer> AnimationLayerSP;

#endif /* ANIMATIONLAYER_H_ */
