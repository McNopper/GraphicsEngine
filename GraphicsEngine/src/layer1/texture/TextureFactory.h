/*
 * TextureFactory.h
 *
 *  Created on: 31.05.2011
 *      Author: Norbert Nopper
 */

#ifndef TEXTUREFACTORY_H_
#define TEXTUREFACTORY_H_

#ifndef GE_NO_DEVIL
#include "TextureFactory_DevIL.h"
#else
#include "TextureFactory_GLUS.h"
#endif

#endif /* TEXTUREFACTORY_H_ */
