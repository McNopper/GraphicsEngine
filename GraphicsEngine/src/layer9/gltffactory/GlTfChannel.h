/*
 * GlTfChannel.h
 *
 *  Created on: 08.07.2014
 *      Author: nopper
 */

#ifndef GLTFCHANNEL_H_
#define GLTFCHANNEL_H_

#include "../../UsedLibs.h"

#include "GlTfAccessor.h"
#include "GlTfNode.h"

class GlTfChannel
{

private:

	GlTfAccessorSP time;
	GlTfAccessorSP interpolator;
	GlTfAccessorSP value;

	GlTfNodeSP targetNode;
	std::string targetPath;
	std::string targetElement;

public:

	GlTfChannel();
	virtual ~GlTfChannel();

	const GlTfAccessorSP& getTime() const;
	void setTime(const GlTfAccessorSP& time);

	const GlTfAccessorSP& getInterpolator() const;
	void setInterpolator(const GlTfAccessorSP& interpolator);

	const GlTfAccessorSP& getValue() const;
	void setValue(const GlTfAccessorSP& value);

	const GlTfNodeSP& getTargetNode() const;
	void setTargetNode(const GlTfNodeSP& targetNode);

	const std::string& getTargetPath() const;
	void setTargetPath(const std::string& targetPath);

	const std::string& getTargetElement() const;
	void setTargetElement(const std::string& targetElement);

};

typedef std::shared_ptr<GlTfChannel> GlTfChannelSP;

#endif /* GLTFCHANNEL_H_ */
