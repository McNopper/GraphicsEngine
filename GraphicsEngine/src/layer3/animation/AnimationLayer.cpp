/*
 * AnimationLayer.cpp
 *
 *  Created on: 16.07.2012
 *      Author: nopper
 */

#include "../../layer0/stl/Helper.h"

#include "AnimationLayer.h"

using namespace std;

AnimationLayer::AnimationLayer()
{
}

AnimationLayer::~AnimationLayer()
{
	for (enum eCHANNELS_XYZ i = X; i <= Z; i = static_cast<enum eCHANNELS_XYZ>(i + 1))
	{
		allTranslationValues[i].clear();
		allTranslationInterpolators[i].clear();

		allRotationValues[i].clear();
		allRotationInterpolators[i].clear();

		allScalingValues[i].clear();
		allScalingInterpolators[i].clear();
	}

	for (enum eCHANNELS_RGBA i = R; i <= A; i = static_cast<enum eCHANNELS_RGBA>(i + 1))
	{
		allEmissiveColorValues[i].clear();
		allEmissiveColorInterpolators[i].clear();

		allAmbientColorValues[i].clear();
		allAmbientColorInterpolators[i].clear();

		allDiffuseColorValues[i].clear();
		allDiffuseColorInterpolators[i].clear();

		allSpecularColorValues[i].clear();
		allSpecularColorInterpolators[i].clear();

		allReflectionColorValues[i].clear();
		allReflectionColorInterpolators[i].clear();

		allRefractionColorValues[i].clear();
		allRefractionColorInterpolators[i].clear();
	}

	for (enum eCHANNELS_SCALAR i = S; i <= S; i = static_cast<enum eCHANNELS_SCALAR>(i + 1))
	{
		allShininessValues[i].clear();
		allShininessInterpolators[i].clear();
	}

}

void AnimationLayer::addTranslationValue(enum eCHANNELS_XYZ channel, float time, float value, const Interpolator& interpolator)
{
	allTranslationValues[channel][time] = value;
	allTranslationInterpolators[channel][time] = &interpolator;
}

void AnimationLayer::addRotationValue(enum eCHANNELS_XYZ channel, float time, float value, const Interpolator& interpolator)
{
	allRotationValues[channel][time] = value;
	allRotationInterpolators[channel][time] = &interpolator;
}

void AnimationLayer::addScalingValue(enum eCHANNELS_XYZ channel, float time, float value, const Interpolator& interpolator)
{
	allScalingValues[channel][time] = value;
	allScalingInterpolators[channel][time] = &interpolator;
}

void AnimationLayer::addEmissiveColorValue(enum eCHANNELS_RGBA channel, float time, float value, const Interpolator& interpolator)
{
	allEmissiveColorValues[channel][time] = value;
	allEmissiveColorInterpolators[channel][time] = &interpolator;
}

void AnimationLayer::addAmbientColorValue(enum eCHANNELS_RGBA channel, float time, float value, const Interpolator& interpolator)
{
	allAmbientColorValues[channel][time] = value;
	allAmbientColorInterpolators[channel][time] = &interpolator;
}

void AnimationLayer::addDiffuseColorValue(enum eCHANNELS_RGBA channel, float time, float value, const Interpolator& interpolator)
{
	allDiffuseColorValues[channel][time] = value;
	allDiffuseColorInterpolators[channel][time] = &interpolator;
}

void AnimationLayer::addSpecularColorValue(enum eCHANNELS_RGBA channel, float time, float value, const Interpolator& interpolator)
{
	allSpecularColorValues[channel][time] = value;
	allSpecularColorInterpolators[channel][time] = &interpolator;
}

void AnimationLayer::addReflectionColorValue(enum eCHANNELS_RGBA channel, float time, float value, const Interpolator& interpolator)
{
	allReflectionColorValues[channel][time] = value;
	allReflectionColorInterpolators[channel][time] = &interpolator;
}

void AnimationLayer::addRefractionColorValue(enum eCHANNELS_RGBA channel, float time, float value, const Interpolator& interpolator)
{
	allRefractionColorValues[channel][time] = value;
	allRefractionColorInterpolators[channel][time] = &interpolator;
}

void AnimationLayer::addShininessValue(enum eCHANNELS_SCALAR channel, float time, float value, const Interpolator& interpolator)
{
	allShininessValues[channel][time] = value;
	allShininessInterpolators[channel][time] = &interpolator;
}

void AnimationLayer::addTransparencyValue(enum eCHANNELS_SCALAR channel, float time, float value, const Interpolator& interpolator)
{
	allTransparencyValues[channel][time] = value;
	allTransparencyInterpolators[channel][time] = &interpolator;
}

float AnimationLayer::getInterpolatedValue(const std::map<float, float>& currentTableValues, const std::map<float, const Interpolator*>& currentTableInterpolators, float time, float defaultValue) const
{
	if (currentTableInterpolators.size() == 0)
	{
		return defaultValue;
	}

	auto walker = less_equal_bound<float, const Interpolator*>(currentTableInterpolators, time);

	if (walker == currentTableInterpolators.end())
	{
		return currentTableValues.begin()->second;
	}

	const Interpolator* currentInterpolator = walker->second;

	return currentInterpolator->interpolate(currentTableValues, time);
}

bool AnimationLayer::hasTranslationValue(enum eCHANNELS_XYZ channel) const
{
	return allTranslationValues[channel].size() > 0;
}

bool AnimationLayer::hasRotationValue(enum eCHANNELS_XYZ channel) const
{
	return allRotationValues[channel].size() > 0;
}

bool AnimationLayer::hasScalingValue(enum eCHANNELS_XYZ channel) const
{
	return allScalingValues[channel].size() > 0;
}

bool AnimationLayer::hasEmissiveColorValue(enum eCHANNELS_RGBA channel) const
{
	return allEmissiveColorValues[channel].size() > 0;
}

bool AnimationLayer::hasAmbientColorValue(enum eCHANNELS_RGBA channel) const
{
	return allAmbientColorValues[channel].size() > 0;
}

bool AnimationLayer::hasDiffuseColorValue(enum eCHANNELS_RGBA channel) const
{
	return allDiffuseColorValues[channel].size() > 0;
}

bool AnimationLayer::hasSpecularColorValue(enum eCHANNELS_RGBA channel) const
{
	return allSpecularColorValues[channel].size() > 0;
}

bool AnimationLayer::hasReflectionColorValue(enum eCHANNELS_RGBA channel) const
{
	return allReflectionColorValues[channel].size() > 0;
}

bool AnimationLayer::hasRefractionColorValue(enum eCHANNELS_RGBA channel) const
{
	return allRefractionColorValues[channel].size() > 0;
}

bool AnimationLayer::hasShininessValue(enum eCHANNELS_SCALAR channel) const
{
	return allShininessValues[channel].size() > 0;
}

bool AnimationLayer::hasTransparencyValue(enum eCHANNELS_SCALAR channel) const
{
	return allTransparencyValues[channel].size() > 0;
}

float AnimationLayer::getTranslationValue(enum eCHANNELS_XYZ channel, float time) const
{
	const std::map<float, float>& currentTableValues = allTranslationValues[channel];
	const std::map<float, const Interpolator*>& currentTableInterpolators = allTranslationInterpolators[channel];

	return getInterpolatedValue(currentTableValues, currentTableInterpolators, time);
}

float AnimationLayer::getRotationValue(enum eCHANNELS_XYZ channel, float time) const
{
	const std::map<float, float>& currentTableValues = allRotationValues[channel];
	const std::map<float, const Interpolator*>& currentTableInterpolators = allRotationInterpolators[channel];

	return getInterpolatedValue(currentTableValues, currentTableInterpolators, time);
}

float AnimationLayer::getScalingValue(enum eCHANNELS_XYZ channel, float time) const
{
	const std::map<float, float>& currentTableValues = allScalingValues[channel];
	const std::map<float, const Interpolator*>& currentTableInterpolators = allScalingInterpolators[channel];

	return getInterpolatedValue(currentTableValues, currentTableInterpolators, time, 1.0f);
}

float AnimationLayer::getEmissiveColorValue(enum eCHANNELS_RGBA channel, float time) const
{
	const std::map<float, float>& currentTableValues = allEmissiveColorValues[channel];
	const std::map<float, const Interpolator*>& currentTableInterpolators = allEmissiveColorInterpolators[channel];

	return getInterpolatedValue(currentTableValues, currentTableInterpolators, time);
}

float AnimationLayer::getAmbientColorValue(enum eCHANNELS_RGBA channel, float time) const
{
	const std::map<float, float>& currentTableValues = allAmbientColorValues[channel];
	const std::map<float, const Interpolator*>& currentTableInterpolators = allAmbientColorInterpolators[channel];

	return getInterpolatedValue(currentTableValues, currentTableInterpolators, time);
}

float AnimationLayer::getDiffuseColorValue(enum eCHANNELS_RGBA channel, float time) const
{
	const std::map<float, float>& currentTableValues = allDiffuseColorValues[channel];
	const std::map<float, const Interpolator*>& currentTableInterpolators = allDiffuseColorInterpolators[channel];

	return getInterpolatedValue(currentTableValues, currentTableInterpolators, time);
}

float AnimationLayer::getSpecularColorValue(enum eCHANNELS_RGBA channel, float time) const
{
	const std::map<float, float>& currentTableValues = allSpecularColorValues[channel];
	const std::map<float, const Interpolator*>& currentTableInterpolators = allSpecularColorInterpolators[channel];

	return getInterpolatedValue(currentTableValues, currentTableInterpolators, time);
}

float AnimationLayer::getReflectionColorValue(enum eCHANNELS_RGBA channel, float time) const
{
	const std::map<float, float>& currentTableValues = allReflectionColorValues[channel];
	const std::map<float, const Interpolator*>& currentTableInterpolators = allReflectionColorInterpolators[channel];

	return getInterpolatedValue(currentTableValues, currentTableInterpolators, time);
}

float AnimationLayer::getRefractionColorValue(enum eCHANNELS_RGBA channel, float time) const
{
	const std::map<float, float>& currentTableValues = allRefractionColorValues[channel];
	const std::map<float, const Interpolator*>& currentTableInterpolators = allRefractionColorInterpolators[channel];

	return getInterpolatedValue(currentTableValues, currentTableInterpolators, time);
}

float AnimationLayer::getShininessValue(enum eCHANNELS_SCALAR channel, float time) const
{
	const std::map<float, float>& currentTableValues = allShininessValues[channel];
	const std::map<float, const Interpolator*>& currentTableInterpolators = allShininessInterpolators[channel];

	return getInterpolatedValue(currentTableValues, currentTableInterpolators, time);
}

float AnimationLayer::getTransparencyValue(enum eCHANNELS_SCALAR channel, float time) const
{
	const std::map<float, float>& currentTableValues = allTransparencyValues[channel];
	const std::map<float, const Interpolator*>& currentTableInterpolators = allTransparencyInterpolators[channel];

	return getInterpolatedValue(currentTableValues, currentTableInterpolators, time);
}

const map<float, float>& AnimationLayer::getAllTranslationValues(enum eCHANNELS_XYZ channel) const
{
	return allTranslationValues[channel];
}

const map<float, float>& AnimationLayer::getAllRotationValues(enum eCHANNELS_XYZ channel) const
{
	return allRotationValues[channel];
}

const map<float, float>& AnimationLayer::getAllScalingValues(enum eCHANNELS_XYZ channel) const
{
	return allScalingValues[channel];
}

const std::map<float, const Interpolator*>& AnimationLayer::getAllTranslationInterpolators(enum eCHANNELS_XYZ channel) const
{
	return allTranslationInterpolators[channel];
}

const std::map<float, const Interpolator*>& AnimationLayer::getAllRotationInterpolators(enum eCHANNELS_XYZ channel) const
{
	return allRotationInterpolators[channel];
}

const std::map<float, const Interpolator*>& AnimationLayer::getAllScalingInterpolators(enum eCHANNELS_XYZ channel) const
{
	return allScalingInterpolators[channel];
}
