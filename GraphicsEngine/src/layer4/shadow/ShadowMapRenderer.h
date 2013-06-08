/*
 * ShadowMapRenderer.h
 *
 *  Created on: 06.06.2013
 *      Author: nopper
 */

#ifndef SHADOWMAPRENDERER_H_
#define SHADOWMAPRENDERER_H_

#include "../../UsedLibs.h"

// TODO Create orthographic camera used for each render step
// TODO Pass light - overloaded methods - to render the shadow maps

class ShadowMapRenderer
{
public:
	ShadowMapRenderer();
	virtual ~ShadowMapRenderer();
};

typedef boost::shared_ptr<ShadowMapRenderer> ShadowMapRendererSP;

#endif /* SHADOWMAPRENDERER_H_ */
