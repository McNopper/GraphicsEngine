/*
 * GlTfAnimation.h
 *
 *  Created on: 08.07.2014
 *      Author: nopper
 */

#ifndef GLTFANIMATION_H_
#define GLTFANIMATION_H_

#include "../../UsedLibs.h"

#include "GlTfChannel.h"

class GlTfAnimation
{

private:

	std::vector<GlTfChannelSP> allChannels;

public:

	GlTfAnimation();
	virtual ~GlTfAnimation();

	void addChannel(const GlTfChannelSP& channel);

	const std::vector<GlTfChannelSP>& getAllChannels() const;

};

typedef std::shared_ptr<GlTfAnimation> GlTfAnimationSP;

#endif /* GLTFANIMATION_H_ */
