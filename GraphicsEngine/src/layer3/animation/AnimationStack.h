/*
 * AnimationStack.h
 *
 *  Created on: 16.07.2012
 *      Author: nopper
 */

#ifndef ANIMATIONSTACK_H_
#define ANIMATIONSTACK_H_

#include "../../UsedLibs.h"

#include "AnimationLayer.h"

class AnimationStack
{

private:

	std::string name;

	float startTime;
	float stopTime;

	std::vector<AnimationLayerSP> allAnimationLayers;

public:
	AnimationStack(const std::string& name, float startTime, float stopTime);
	virtual ~AnimationStack();

	void addAnimationLayer(const AnimationLayerSP& animationLayer);

	std::int32_t getAnimationLayersCount() const;

	const AnimationLayerSP& getAnimationLayer(std::int32_t index) const;

	const std::string& getName() const;

	float getStartTime() const;

	float getStopTime() const;
};

typedef std::shared_ptr<AnimationStack> AnimationStackSP;

#endif /* ANIMATIONSTACK_H_ */
