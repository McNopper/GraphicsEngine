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

	float startTime;
	float stopTime;

	std::vector<AnimationLayerSP> allAnimationLayers;

public:
	AnimationStack(float startTime, float stopTime);
	virtual ~AnimationStack();

	void addAnimationLayer(const AnimationLayerSP& animationLayer);

	boost::int32_t getAnimationLayersCount() const;

	const AnimationLayerSP& getAnimationLayer(boost::int32_t index) const;

	float getStartTime() const;

	float getStopTime() const;
};

typedef boost::shared_ptr<AnimationStack> AnimationStackSP;

#endif /* ANIMATIONSTACK_H_ */
